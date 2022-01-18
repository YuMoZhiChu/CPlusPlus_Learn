#pragma once

#include "Atomic.h"
#include "Protocol.h"
#include "_all_header.h"

namespace Trace {
namespace Private {

////////////////////////////////////////////////////////////////////////////////
void Field_WriteAuxData(uint32, const uint8*, int32);
void Field_WriteStringAnsi(uint32, const ANSICHAR*, int32);
void Field_WriteStringAnsi(uint32, const TCHAR_UE*, int32);
void Field_WriteStringWide(uint32, const TCHAR_UE*, int32);

} // namespace Private

////////////////////////////////////////////////////////////////////////////////
// 模板编程, Type, 是需要转化的数据类型
// Tid 是对应的数据类型, 映射到 EFieldType 的 ID, 他们可能因为大小相等, 比如 Bool 和 Int8, 所以是一样的 Tid
// Size 是对应 Byte 大小, 就是 SizeOf 的值
template <typename Type> struct TFieldType;

template <> struct TFieldType<bool> { enum { Tid = int(EFieldType::Bool), Size = sizeof(bool) }; };
template <> struct TFieldType<int8> { enum { Tid = int(EFieldType::Int8), Size = sizeof(int8) }; };
template <> struct TFieldType<int16> { enum { Tid = int(EFieldType::Int16), Size = sizeof(int16) }; };
template <> struct TFieldType<int32> { enum { Tid = int(EFieldType::Int32), Size = sizeof(int32) }; };
template <> struct TFieldType<int64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(int64) }; };
template <> struct TFieldType<uint8> { enum { Tid = int(EFieldType::Int8), Size = sizeof(uint8) }; };
template <> struct TFieldType<uint16> { enum { Tid = int(EFieldType::Int16), Size = sizeof(uint16) }; };
template <> struct TFieldType<uint32> { enum { Tid = int(EFieldType::Int32), Size = sizeof(uint32) }; };
template <> struct TFieldType<uint64> { enum { Tid = int(EFieldType::Int64), Size = sizeof(uint64) }; };
template <> struct TFieldType<float> { enum { Tid = int(EFieldType::Float32), Size = sizeof(float) }; };
template <> struct TFieldType<double> { enum { Tid = int(EFieldType::Float64), Size = sizeof(double) }; };
// 对应的 class 指针模板
// 定义对应的变量写法
// TFieldType<MyClass*> d;
template <class T> struct TFieldType<T*> { enum { Tid = int(EFieldType::Pointer), Size = sizeof(void*) }; };

// 对应数组指针模板
// 定义对应的变量写法
// TFieldType<int[]> e;
template <typename T>
struct TFieldType<T[]>
{
	enum
	{
		Tid = int(TFieldType<T>::Tid) | int(EFieldType::Array),
		Size = 0,
	};
};

template <> struct TFieldType<Trace::AnsiString> { enum { Tid = int(EFieldType::AnsiString), Size = 0, }; };
template <> struct TFieldType<Trace::WideString> { enum { Tid = int(EFieldType::WideString), Size = 0, }; };

////////////////////////////////////////////////////////////////////////////////
// 构造如下
// auto a = FLiteralName("abed");
struct FLiteralName
{
	// 这是一个模板的构造函数
	// 代表了很多个的构造函数
	// 比如 FLiteralName(const ANSICHAR(&Name)[0]), FLiteralName(const ANSICHAR(&Name)[1]), FLiteralName(const ANSICHAR(&Name)[2]) 等
	// 作用就是在编译前, 解析出字符串长度
	template <uint32 Size>
	explicit FLiteralName(const ANSICHAR(&Name)[Size])
		: Ptr(Name)
		, Length(Size - 1)
	{
		static_assert(Size < 256, "Field name is too large");
	}

	const ANSICHAR* Ptr;
	uint8 Length;
};

////////////////////////////////////////////////////////////////////////////////
struct FFieldDesc
{
	FFieldDesc(const FLiteralName& Name, uint8 Type, uint16 Offset, uint16 Size)
		: Name(Name.Ptr)
		, ValueOffset(Offset)
		, ValueSize(Size)
		, NameSize(Name.Length)
		, TypeInfo(Type)
	{
	}

	const ANSICHAR* Name;
	uint16			ValueOffset;
	uint16			ValueSize;
	uint8			NameSize;
	uint8			TypeInfo;
};

////////////////////////////////////////////////////////////////////////////////
// Trace 的一个 Field 模板, 这个模板的定义是
// 从 Index 位置开始, 到 InOffset 偏移, 表示类型是 Type 的内容, 是一种模板
template <int InIndex, int InOffset, typename Type> struct TField;

enum class EIndexPack
{
	FieldCountMask = 0xff,
	MaybeHasAux = 0x100,
};

////////////////////////////////////////////////////////////////////////////////
/*
#define TRACE_PRIVATE_FIELD(InIndex, InOffset, Type) \
		enum \
		{ \
			Index	= InIndex, \ 预先利用模板, 直接在枚举中设置参数, 在使用的时候直接用 InIndex 就能获取参数
			Offset	= InOffset, \
			Tid		= TFieldType<Type>::Tid, \
			Size	= TFieldType<Type>::Size, \
		}; \
		static_assert((Index & int(EIndexPack::FieldCountMask)) <= 127, "Trace events may only have up to a maximum of 127 fields"); \
	private: \
		FFieldDesc FieldDesc; \ 一条 Desc
	public: \
		TField(const FLiteralName& Name) \
		: FieldDesc(Name, Tid, Offset, Size) \
		{ \
		}
*/
#define TRACE_PRIVATE_FIELD(InIndex, InOffset, Type) \
		enum \
		{ \
			Index	= InIndex, \
			Offset	= InOffset, \
			Tid		= TFieldType<Type>::Tid, \
			Size	= TFieldType<Type>::Size, \
		}; \
		static_assert((Index & int(EIndexPack::FieldCountMask)) <= 127, "Trace events may only have up to a maximum of 127 fields"); \
	private: \
		FFieldDesc FieldDesc; \
	public: \
		TField(const FLiteralName& Name) \
		: FieldDesc(Name, Tid, Offset, Size) \
		{ \
		}

////////////////////////////////////////////////////////////////////////////////
// 对数组类型的 Type 的模板特例化
template <int InIndex, int InOffset, typename Type>
struct TField<InIndex, InOffset, Type[]>
{
	TRACE_PRIVATE_FIELD(InIndex | int(EIndexPack::MaybeHasAux), InOffset, Type[]);

	// 主要是 Set 数据时的特殊处理
	static void Set(uint8*, Type const* Data, int32 Count)
	{
		if (Count > 0)
		{
			int32 Size = (Count * sizeof(Type)) & (FAuxHeader::SizeLimit - 1) & ~(sizeof(Type) - 1);
			Private::Field_WriteAuxData(Index, (const uint8*)Data, Size);
		}
	}
};

////////////////////////////////////////////////////////////////////////////////
// 对 字符 的处理 
template <int InIndex, int InOffset>
struct TField<InIndex, InOffset, Trace::AnsiString>
{
	TRACE_PRIVATE_FIELD(InIndex | int(EIndexPack::MaybeHasAux), InOffset, Trace::AnsiString);

	static void Set(uint8*, const TCHAR_UE* String, int32 Length = -1)
	{
		if (Length < 0)
		{
			Length = 0;
			if (String)
			{
				for (const TCHAR_UE* c = String; *c; ++c, ++Length);
			}
		}

		Private::Field_WriteStringAnsi(Index, String, Length);
	}

	static void Set(uint8*, const ANSICHAR* String, int32 Length = -1)
	{
		if (Length < 0)
		{
			Length = String ? int32(strlen(String)) : 0;
		}

		if (Length)
		{
			Private::Field_WriteStringAnsi(Index, String, Length);
		}
	}
};

////////////////////////////////////////////////////////////////////////////////
template <int InIndex, int InOffset>
struct TField<InIndex, InOffset, Trace::WideString>
{
	TRACE_PRIVATE_FIELD(InIndex | int(EIndexPack::MaybeHasAux), InOffset, Trace::WideString);

	static void Set(uint8*, const TCHAR_UE* String, int32 Length = -1)
	{
		if (Length < 0)
		{
			Length = 0;
			for (const TCHAR_UE* c = String; *c; ++c, ++Length);
		}

		if (Length)
		{
			Private::Field_WriteStringWide(Index, String, Length);
		}
	}
};

////////////////////////////////////////////////////////////////////////////////
// 通用处理方案
template <int InIndex, int InOffset, typename Type>
struct TField
{
	TRACE_PRIVATE_FIELD(InIndex, InOffset, Type);

	/*
	restrict 的含义是
		由编程者向编译器声明，在这个指针的生命周期中，只有这个指针本身或者直接由它产生的指针(如 ptr + 1)能够用来访问该指针指向的对象.
		他的作用是限制指针别名，帮助编译器做优化.
		如果该指针与另外一个指针指向同一对象，那么结果是未定义的.
	
	restrict 可能是 restrict, __restrict__, __restrict
	*/
	static void Set(uint8* Dest, const Type& __restrict Value)
	{
		::memcpy(Dest + Offset, &Value, Size);
	}
};

////////////////////////////////////////////////////////////////////////////////
// Used to terminate the field list and determine an event's size.
// 用于终止字段列表并确定事件的大小.
enum EventProps {};
// 即有一个特殊的模板, 用来做结束符, 而且更恰当的是, 可以直接拿到 Count 和 Size
template <int InFieldCount, int InSize>
struct TField<InFieldCount, InSize, EventProps>
{
	enum : uint16
	{
		FieldCount = (InFieldCount & int(EIndexPack::FieldCountMask)),
		Size = InSize,
		MaybeHasAux = !!(InFieldCount & int(EIndexPack::MaybeHasAux)),
	};
};

////////////////////////////////////////////////////////////////////////////////
// Access to additional data that can be included along with a logged event.
// [TODO] 特殊的消息处理, 目的是在 InOffset 后面增加一些自定义的消息
enum Attachment {};
template <int InOffset>
struct TField<0, InOffset, Attachment>
{
	template <typename LambdaType>
	static void Set(uint8* Dest, LambdaType&& Lambda)
	{
		Lambda(Dest + InOffset);
	}

	static void Set(uint8* Dest, const void* Data, uint32 Size)
	{
		::memcpy(Dest + InOffset, Data, Size);
	}
};

}