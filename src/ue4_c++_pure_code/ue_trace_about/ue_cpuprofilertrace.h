#pragma once
#include "trace.h"
#include "../ue_basic_typedef.h"
#include "ue_channel.h"
#include "ue_trace.h"

// 直接定义了
TRACE_PRIVATE_CHANNEL(CpuChannel);

/*
 * Facilities for tracing timed cpu events. Two types of events are supported, static events where the identifier is
 * known at compile time, and dynamic event were identifiers can be constructed in runtime. Static events have lower overhead
 * so always prefer to use them if possible.
 *
 * Events are tracked per thread, so begin/end calls must be matched and called on the same thread. It is possible to use any channel
 * to emit the events, but both that channel and the CpuChannel must then be enabled.
 *
 * Usage of the scope macros is highly encouraged in order to avoid mistakes.
 * 
 * 跟踪定时CPU事件的结构。
 * 支持两种时间类型
 *     在编译时就已知的, static event
 *     在运行时根据标志符，动态生成的 event
 * static 的开销更低, 非常推荐使用
 * 每一个事件 是根据线程进行跟踪的，所以对应的 开始和结束 的调用, 都必须在同一个线程上。
 * 虽然任意通道(Channel)都能发出事件, 但前提是通道要启用
 * 这里强烈建议范围宏来避免错误
 * 
 */
struct FCpuProfilerTrace
{
	static void Shutdown();

	/*
	 * Output cpu event definition (spec).
	 * @param Name Event name
	 * @return Event definition id
	 */
	static uint32 OutputEventType(const ANSICHAR* Name);

	/*
	 * Output cpu event definition (spec).
	 * @param Name Event name
	 * @return Event definition id
	 */
	static uint32 OutputEventType(const TCHAR_UE* Name);

	/*
	 * Output begin event marker for a given spec. Must always be matched with an end event.
	 * @param SpecId Event definition id.
	 */
	static void OutputBeginEvent(uint32 SpecId);

	/*
	 * Output begin event marker for a dynamic event name. This is more expensive than statically known event
	 * names using \ref OutputBeginEvent. Must always be matched with an end event.
	 * @param Name Name of event
	 */
	static void OutputBeginDynamicEvent(const ANSICHAR* Name);

	/*
	 * Output begin event marker for a dynamic event name. This is more expensive than statically known event
	 * names using \ref OutputBeginEvent. Must always be matched with an end event.
	 * @param Name Name of event
	 */
	static void OutputBeginDynamicEvent(const TCHAR_UE* Name);

	/*
	 * Output end event marker for static or dynamic event for the currently open scope.
	 * 结束一个 event(static or dynamic)
	 */
	static void OutputEndEvent();

	struct FEventScope
	{
		FEventScope(uint32 InSpecId, const Trace::FChannel& Channel)
			: bEnabled(Channel | CpuChannel)
		{
			if (bEnabled)
			{
				OutputBeginEvent(InSpecId);
			}
		}

		~FEventScope()
		{
			if (bEnabled)
			{
				OutputEndEvent();
			}
		}

		bool bEnabled;
	};

	struct FDynamicEventScope
	{
		FDynamicEventScope(const ANSICHAR* InEventName, const Trace::FChannel& Channel)
			: bEnabled(Channel | CpuChannel)
		{
			if (bEnabled)
			{
				OutputBeginDynamicEvent(InEventName);
			}
		}

		FDynamicEventScope(const TCHAR_UE* InEventName, const Trace::FChannel& Channel)
			: bEnabled(Channel | CpuChannel)
		{
			if (bEnabled)
			{
				OutputBeginDynamicEvent(InEventName);
			}
		}

		~FDynamicEventScope()
		{
			if (bEnabled)
			{
				OutputEndEvent();
			}
		}

		bool bEnabled;
	};
};

#define TRACE_CPUPROFILER_SHUTDOWN() \
	FCpuProfilerTrace::Shutdown();

// Trace a scoped cpu timing event providing a static string (const ANSICHAR* or const TCHAR*)
// as the scope name and a trace channel.
// Example: TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL_STR("My Scoped Timer A", CpuChannel)
// Note: The event will be emitted only if both the given channel and CpuChannel is enabled.
/*
#define TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL_STR(NameStr, Channel) \
	static uint32 PREPROCESSOR_JOIN(__CpuProfilerEventSpecId, __LINE__); \
		一个局部静态变量 __CpuProfilerEventSpecId + 具体在哪一行
	if (bool(Channel|CpuChannel) && PREPROCESSOR_JOIN(__CpuProfilerEventSpecId, __LINE__) == 0) { \
		PREPROCESSOR_JOIN(__CpuProfilerEventSpecId, __LINE__) = FCpuProfilerTrace::OutputEventType(NameStr); \
		初始化事件, 并且用 __CpuProfilerEventSpecId__LINE__ 记录这个事件的 ID
	} \
	// 定义一个局部变量 __CpuProfilerEventScope+__LINE__ 是 EventScope 的名字, 参数是 __CpuProfilerEventSpecId, __LINE__ + Channel
	FCpuProfilerTrace::FEventScope PREPROCESSOR_JOIN(__CpuProfilerEventScope, __LINE__)(PREPROCESSOR_JOIN(__CpuProfilerEventSpecId, __LINE__), Channel);

*/
#define TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL_STR(NameStr, Channel) \
	static uint32 PREPROCESSOR_JOIN(__CpuProfilerEventSpecId, __LINE__); \
	if (bool(Channel|CpuChannel) && PREPROCESSOR_JOIN(__CpuProfilerEventSpecId, __LINE__) == 0) { \
		PREPROCESSOR_JOIN(__CpuProfilerEventSpecId, __LINE__) = FCpuProfilerTrace::OutputEventType(NameStr); \
	} \
	FCpuProfilerTrace::FEventScope PREPROCESSOR_JOIN(__CpuProfilerEventScope, __LINE__)(PREPROCESSOR_JOIN(__CpuProfilerEventSpecId, __LINE__), Channel);

// Trace a scoped cpu timing event providing a scope name (plain text) and a trace channel.
// Example: TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL(MyScopedTimer::A, CpuChannel)
// Note: Do not use this macro with a static string because, in that case, additional quotes will
//       be added around the event scope name.
// Note: The event will be emitted only if both the given channel and CpuChannel is enabled.
// 直接把内容转成字符 Name -> #Name 就不需要输出 "" 的参数了
#define TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL(Name, Channel) \
	TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL_STR(#Name, Channel)

// Trace a scoped cpu timing event providing a static string (const ANSICHAR* or const TCHAR*)
// as the scope name. It will use the Cpu trace channel.
// Example: TRACE_CPUPROFILER_EVENT_SCOPE_STR("My Scoped Timer A")
// 默认 CpuChannel
#define TRACE_CPUPROFILER_EVENT_SCOPE_STR(NameStr) \
	TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL_STR(NameStr, CpuChannel)

// Trace a scoped cpu timing event providing a scope name (plain text) and a trace channel.
// It will use the Cpu trace channel.
// Example: TRACE_CPUPROFILER_EVENT_SCOPE(MyScopedTimer::A)
// Note: Do not use this macro with a static string because, in that case, additional quotes will
//       be added around the event scope name.
// 默认 CpuChannel + 省去字符转换
#define TRACE_CPUPROFILER_EVENT_SCOPE(Name) \
	TRACE_CPUPROFILER_EVENT_SCOPE_ON_CHANNEL(Name, CpuChannel)

// Trace a scoped cpu timing event providing a dynamic string (const ANSICHAR* or const TCHAR*)
// as the scope name and a trace channel.
// Example: TRACE_CPUPROFILER_EVENT_SCOPE_TEXT_ON_CHANNEL(*MyScopedTimerNameString, CpuChannel)
// Note: This macro has a larger overhead compared to macro that accepts a plain text name
//       or a static string. Use it only if scope name really needs to be a dynamic string.
// 生成的是 FDynamicEventScope
#define TRACE_CPUPROFILER_EVENT_SCOPE_TEXT_ON_CHANNEL(Name, Channel) \
	FCpuProfilerTrace::FDynamicEventScope PREPROCESSOR_JOIN(__CpuProfilerEventScope, __LINE__)(Name, Channel);

// Trace a scoped cpu timing event providing a dynamic string (const ANSICHAR* or const TCHAR*)
// as the scope name. It will use the Cpu trace channel.
// Example: TRACE_CPUPROFILER_EVENT_SCOPE_TEXT(*MyScopedTimerNameString)
// Note: This macro has a larger overhead compared to macro that accepts a plain text name
//       or a static string. Use it only if scope name really needs to be a dynamic string.
// 默认 CpuChannel, FDynamicEventScope
#define TRACE_CPUPROFILER_EVENT_SCOPE_TEXT(Name) \
	TRACE_CPUPROFILER_EVENT_SCOPE_TEXT_ON_CHANNEL(Name, CpuChannel)
