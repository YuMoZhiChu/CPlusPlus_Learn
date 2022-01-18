// 这里是 macro 定义

#pragma once

namespace Trace
{
	class FChannel;
};

// 默认展开参数定义
#define TRACE_PRIVATE_CHANNEL_DEFAULT_ARGS false, "None"

// 声明一个 Trace::FChannel , static 变量, 并且可以根据 LinkageType 是否向其他模块导出, 或者只是作为 extern 声明
/*
static Trace::FChannel ChannelName##Object;
	定义一个 Static 的 Channel
LinkageType Trace::FChannel& ChannelName = ChannelName##Object; 
	LinkageType 表示的是链接方式, 可能出现的有, 在 UE 中需要导出的 _dllexport_ 以及在外部需要前提声明的 extern
*/
#define TRACE_PRIVATE_CHANNEL_DECLARE(LinkageType, ChannelName) \
	static Trace::FChannel ChannelName##Object;\
	LinkageType Trace::FChannel& ChannelName = ChannelName##Object;

// 定义一个 Registrator, static 变量
/*
struct F##ChannelName##Registrator \
{ \
	F##ChannelName##Registrator() \
	{ \
		// 这里第一个参数是一个字符串, 也就是 ChannelName
		ChannelName##Object.Setup(#ChannelName, { __VA_ARGS__ } ); \
	} \
};\
	注意到, 这个注册函数其实是空的, 它真正的作用是, 在初始化的时候, 调用 ChannelName##Object.Setup 并且传入多参数

static F##ChannelName##Registrator ChannelName##Reg = F##ChannelName##Registrator();
	这里就已经调用了 `ChannelName##Object.Setup(#ChannelName, { __VA_ARGS__ } );`
	[TODO] 这里为什么不直接用宏 ChannelName##Object.Setup(#ChannelName, { __VA_ARGS__ } ) 即可? 一定要包一层 `struct F##ChannelName##Registrator` ? 有点绕
*/
#define TRACE_PRIVATE_CHANNEL_IMPL(ChannelName, ...) \
	struct F##ChannelName##Registrator \
	{ \
		F##ChannelName##Registrator() \
		{ \
			ChannelName##Object.Setup(#ChannelName, { __VA_ARGS__ } ); \
		} \
	};\
	static F##ChannelName##Registrator ChannelName##Reg = F##ChannelName##Registrator();

// 复合宏, 声明创建一个 Channel 并且执行 Setup
// 不过这里的 引用也是 static
#define TRACE_PRIVATE_CHANNEL(ChannelName, ...) \
	TRACE_PRIVATE_CHANNEL_DECLARE(static, ChannelName) \
	TRACE_PRIVATE_CHANNEL_IMPL(ChannelName, ##__VA_ARGS__)

// 带 extern 的 FChannel 定义宏
#define TRACE_PRIVATE_CHANNEL_MODULE_EXTERN(ModuleApi, ChannelName) \
	TRACE_PRIVATE_CHANNEL_DECLARE(ModuleApi extern, ChannelName)

// 复合宏, 声明创建一个 Channel 并且执行 Setup
#define TRACE_PRIVATE_CHANNEL_DEFINE(ChannelName, ...) \
	TRACE_PRIVATE_CHANNEL_DECLARE(, ChannelName) \
	TRACE_PRIVATE_CHANNEL_IMPL(ChannelName, ##__VA_ARGS__)

// extern 声明宏, 这里的 __VA_ARGS__ 可能是 _dll_export_ static 等
#define TRACE_PRIVATE_CHANNEL_EXTERN(ChannelName, ...) \
	__VA_ARGS__ extern Trace::FChannel& ChannelName;

// 下面函数的使用宏, 就是尝试转 bool
#define TRACE_PRIVATE_CHANNELEXPR_IS_ENABLED(ChannelsExpr) \
	bool(ChannelsExpr)

// 定义一个 Event
#define TRACE_PRIVATE_EVENT_DEFINE(LoggerName, EventName) \
	Trace::Private::FEventNode LoggerName##EventName##Event;

// 这里是定义一个 static 的 事件, 并实现对应的 struct Fields
#define TRACE_PRIVATE_EVENT_BEGIN(LoggerName, EventName, ...) \
	TRACE_PRIVATE_EVENT_BEGIN_IMPL(static, LoggerName, EventName, ##__VA_ARGS__)

// 这里是定义一个 extern 的 事件, 并实现对应的 Fields
#define TRACE_PRIVATE_EVENT_BEGIN_EXTERN(LoggerName, EventName, ...) \
	TRACE_PRIVATE_EVENT_BEGIN_IMPL(extern, LoggerName, EventName, ##__VA_ARGS__)

/*

#define TRACE_PRIVATE_EVENT_BEGIN_IMPL(LinkageType, LoggerName, EventName, ...) \
	LinkageType TRACE_PRIVATE_EVENT_DEFINE(LoggerName, EventName) \
		这是根据 LinkageType 做一次 Trace::Private::FEventNode 的定义
	struct F##LoggerName##EventName##Fields \
		这是一个复合 XXXFields 的 Struct, 表示的是 多个字段(TField) 的集合
	{ \
		enum \
		{ \
			Important			= Trace::Private::FEventInfo::Flag_Important, \
			NoSync				= Trace::Private::FEventInfo::Flag_NoSync, \
			PartialEventFlags	= (0, ##__VA_ARGS__) & ~Important, \
				(0, ##__VA_ARGS__) 是一个 C++ 新的语法特性 a = (1, 2, 3, 4) 结果是 a = 4, 就是最后一个值的大小
				但是如果 ##__VA_ARGS__ 是 0, 那么这里就是 0 (其实理解成 0 即可
		}; \
		enum : bool { bIsImportant = ((0, ##__VA_ARGS__) & Important) != 0, }; \
		static constexpr uint32 GetSize() { return decltype(EventProps_Private)::Size; } \
		大小直接是用 Trace::EventProps 计算得到来获取
		static uint32 GetUid() { static uint32 Uid = 0; return (Uid = Uid ? Uid : Initialize()); } \
		static uint32 FORCENOINLINE Initialize() \
		{ \
			static const uint32 Uid_ThreadSafeInit = [] () \
			{ \
				using namespace Trace; \
				static F##LoggerName##EventName##Fields Fields; \
				static Trace::Private::FEventInfo Info = \
				{ \
					FLiteralName(#LoggerName), \
					FLiteralName(#EventName), \
					(FFieldDesc*)(&Fields), \
					uint16(sizeof(Fields) / sizeof(FFieldDesc)), \
					uint16(EventFlags), \
				}; \
				return LoggerName##EventName##Event.Initialize(&Info); \
			}(); \
			return Uid_ThreadSafeInit; \
		} \

		这个宏是要和 下面的 END 宏，以及使用场景来看的，我们看下使用的场景
		```
		UE_TRACE_EVENT_BEGIN($Trace, WorkerThread)
			UE_TRACE_EVENT_FIELD(uint32, Cycles)
			UE_TRACE_EVENT_FIELD(uint32, BytesReaped)
			UE_TRACE_EVENT_FIELD(uint32, BytesSent)
		UE_TRACE_EVENT_END()
		```
		可以看见, 这里的使用场景, 是用 3 段宏, 完成了一次重复编码, 首尾是一段宏, 然后中间是一部分可以重复的
			Trace::TField<0 Index, 0 Offset, Type> Trace::FLiteralName 非常有意思

		然后重复的部分完了, 就是结束的一些内容了

#define TRACE_PRIVATE_EVENT_FIELD(FieldType, FieldName) \
		FieldType> const FieldName##_Field = Trace::FLiteralName(#FieldName); \
		template <typename... Ts> auto FieldName(Ts... ts) const { FieldName##_Field.Set((uint8*)this, Forward<Ts>(ts)...); return true; } \
		Trace::TField< \
			decltype(FieldName##_Field)::Index + 1, \
			decltype(FieldName##_Field)::Offset + decltype(FieldName##_Field)::Size,

#define TRACE_PRIVATE_EVENT_END() \
		Trace::EventProps> const EventProps_Private = {}; \
		Trace::TField<0, decltype(EventProps_Private)::Size, Trace::Attachment> const Attachment_Field = {}; \
		template <typename... Ts> auto Attachment(Ts... ts) const { Attachment_Field.Set((uint8*)this, Forward<Ts>(ts)...); return true; } \
		explicit operator bool () const { return true; } \
		enum { EventFlags = PartialEventFlags|(decltype(EventProps_Private)::MaybeHasAux ? Trace::Private::FEventInfo::Flag_MaybeHasAux : 0), }; \
	};
*/

#define TRACE_PRIVATE_EVENT_BEGIN_IMPL(LinkageType, LoggerName, EventName, ...) \
	LinkageType TRACE_PRIVATE_EVENT_DEFINE(LoggerName, EventName) \
	struct F##LoggerName##EventName##Fields \
	{ \
		enum \
		{ \
			Important			= Trace::Private::FEventInfo::Flag_Important, \
			NoSync				= Trace::Private::FEventInfo::Flag_NoSync, \
			PartialEventFlags	= (0, ##__VA_ARGS__) & ~Important, \
		}; \
		enum : bool { bIsImportant = ((0, ##__VA_ARGS__) & Important) != 0, }; \
		static constexpr uint32 GetSize() { return decltype(EventProps_Private)::Size; } \
		static uint32 GetUid() { static uint32 Uid = 0; return (Uid = Uid ? Uid : Initialize()); } \
		static uint32 Initialize() \
		{ \
			static const uint32 Uid_ThreadSafeInit = [] () \
			{ \
				using namespace Trace; \
				static F##LoggerName##EventName##Fields Fields; \
				static Trace::Private::FEventInfo Info = \
				{ \
					FLiteralName(#LoggerName), \
					FLiteralName(#EventName), \
					(FFieldDesc*)(&Fields), \
					uint16(sizeof(Fields) / sizeof(FFieldDesc)), \
					uint16(EventFlags), \
				}; \
				return LoggerName##EventName##Event.Initialize(&Info); \
			}(); \
			return Uid_ThreadSafeInit; \
		} \
		Trace::TField<0 /*Index*/, 0 /*Offset*/,

#define TRACE_PRIVATE_EVENT_FIELD(FieldType, FieldName) \
		FieldType> const FieldName##_Field = Trace::FLiteralName(#FieldName); \
		template <typename... Ts> auto FieldName(Ts... ts) const { FieldName##_Field.Set((uint8*)this, Forward<Ts>(ts)...); return true; } \
		Trace::TField< \
			decltype(FieldName##_Field)::Index + 1, \
			decltype(FieldName##_Field)::Offset + decltype(FieldName##_Field)::Size,

#define TRACE_PRIVATE_EVENT_END() \
		Trace::EventProps> const EventProps_Private = {}; \
		Trace::TField<0, decltype(EventProps_Private)::Size, Trace::Attachment> const Attachment_Field = {}; \
		template <typename... Ts> auto Attachment(Ts... ts) const { Attachment_Field.Set((uint8*)this, Forward<Ts>(ts)...); return true; } \
		explicit operator bool () const { return true; } \
		enum { EventFlags = PartialEventFlags|(decltype(EventProps_Private)::MaybeHasAux ? Trace::Private::FEventInfo::Flag_MaybeHasAux : 0), }; \
	};


// 简化代码宏, 
/*
#define TRACE_PRIVATE_LOG_PRELUDE(EnterFunc, LoggerName, EventName, ChannelsExpr, ...) \
	EnterFunc 是一个可执行的函数，参数是 ...
	这里涉及到一个 TLogScope 的模板
	if (TRACE_PRIVATE_CHANNELEXPR_IS_ENABLED(ChannelsExpr)) \
		if (auto LogScope = Trace::Private::TLogScope<F##LoggerName##EventName##Fields>::EnterFunc(__VA_ARGS__)) \
			if (const auto& __restrict EventName = *(F##LoggerName##EventName##Fields*)LogScope.GetPointer())

*/
#define TRACE_PRIVATE_LOG_PRELUDE(EnterFunc, LoggerName, EventName, ChannelsExpr, ...) \
	if (TRACE_PRIVATE_CHANNELEXPR_IS_ENABLED(ChannelsExpr)) \
		if (auto LogScope = Trace::Private::TLogScope<F##LoggerName##EventName##Fields>::EnterFunc(__VA_ARGS__)) \
			if (const auto& __restrict EventName = *(F##LoggerName##EventName##Fields*)LogScope.GetPointer())


// 简化代码宏, LogScope 做递增
#define TRACE_PRIVATE_LOG_EPILOG() \
				LogScope += LogScope

// 简化代码宏,
#define TRACE_PRIVATE_LOG(LoggerName, EventName, ChannelsExpr, ...) \
	TRACE_PRIVATE_LOG_PRELUDE(Enter, LoggerName, EventName, ChannelsExpr, ##__VA_ARGS__) \
		TRACE_PRIVATE_LOG_EPILOG()

// 简化代码宏,
#define TRACE_PRIVATE_LOG_SCOPED(LoggerName, EventName, ChannelsExpr, ...) \
	Trace::Private::FScopedLogScope PREPROCESSOR_JOIN(TheScope, __LINE__); \
	TRACE_PRIVATE_LOG_PRELUDE(ScopedEnter, LoggerName, EventName, ChannelsExpr, ##__VA_ARGS__) \
		PREPROCESSOR_JOIN(TheScope, __LINE__).SetActive(), \
		TRACE_PRIVATE_LOG_EPILOG()

// 简化代码宏,
#define TRACE_PRIVATE_LOG_SCOPED_T(LoggerName, EventName, ChannelsExpr, ...) \
	Trace::Private::FScopedStampedLogScope PREPROCESSOR_JOIN(TheScope, __LINE__); \
	TRACE_PRIVATE_LOG_PRELUDE(ScopedStampedEnter, LoggerName, EventName, ChannelsExpr, ##__VA_ARGS__) \
		PREPROCESSOR_JOIN(TheScope, __LINE__).SetActive(), \
		TRACE_PRIVATE_LOG_EPILOG()