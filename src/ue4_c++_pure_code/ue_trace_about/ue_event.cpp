#include "ue_event.h"
#include "Atomic.h"
#include "ue_writer.h"
#include "ue_logscope.h"


namespace Trace {
namespace Private {

	FEventNode* volatile	GNewEventList; // = nullptr;

	// 遍历器, 遍历下一个 FEventNode*
	const Trace::Private::FEventNode* FEventNode::FIter::GetNext()
	{
		auto* Ret = (const FEventNode*)Inner;
		if (Ret != nullptr)
		{
			Inner = Ret->Next;
		}
		return Ret;
	}

	// 原子操作, 读 GNewEventList 并返回一个从 GNewEventList 头部开始的 Iter
	Trace::Private::FEventNode::FIter FEventNode::ReadNew()
	{
		FEventNode* EventList = AtomicLoadRelaxed(&GNewEventList);
		if (EventList == nullptr)
		{
			return {};
		}

		// [TODO] 不知道为什么要多加这么一步的验证, 其实一个 Load 就够了
		while (!AtomicCompareExchangeAcquire(&GNewEventList, (FEventNode*)nullptr, EventList))
		{
			PlatformYield();
			EventList = AtomicLoadRelaxed(&GNewEventList);
		}

		// 这是一个构造函数的返回值, 直接返回一个 FIter 的构造参数
		return { EventList };
	}

	uint32 FEventNode::Initialize(const FEventInfo* InInfo)
	{
		if (Uid != 0)
		{
			return Uid;
		}

		// If we're initializing an event we're about to trace it
		Writer_InternalInitialize();

		// Assign a unique ID for this event
		// 这是一个局部 static 变量
		static uint32 volatile EventUidCounter; // = 0;
		uint32 NewUid = AtomicAddRelaxed(&EventUidCounter, 1u) + EKnownEventUids::User;
		if (NewUid >= uint32(EKnownEventUids::Max))
		{
			return Uid = EKnownEventUids::Invalid;
		}

		// Calculate Uid's flags and pack it.
		uint32 UidFlags = 0;
		if (NewUid >= (1 << (8 - EKnownEventUids::_UidShift)))
		{
			UidFlags |= EKnownEventUids::Flag_TwoByteUid;
		}

		NewUid <<= EKnownEventUids::_UidShift;
		NewUid |= UidFlags;

		Info = InInfo;
		Uid = uint16(NewUid);

		// Make this new event instance visible.
		// 效果: 将 this 指针插入到链表头出
		for (;; PlatformYield())
		{
			Next = AtomicLoadRelaxed(&GNewEventList);
			if (AtomicCompareExchangeRelease(&GNewEventList, this, Next))
			{
				break;
			}
		}

		return Uid;
	}

	void FEventNode::Describe() const
	{
		//const FLiteralName& LoggerName = Info->LoggerName;
		//const FLiteralName& EventName = Info->EventName;

		//// Calculate the number of fields and size of name data.
		//uint32 NamesSize = LoggerName.Length + EventName.Length;
		//for (uint32 i = 0; i < Info->FieldCount; ++i)
		//{
		//	NamesSize += Info->Fields[i].NameSize;
		//}

		//// Allocate the new event event in the log stream.
		//uint16 EventUid = EKnownEventUids::NewEvent << EKnownEventUids::_UidShift;

		//uint16 EventSize = sizeof(FNewEventEvent);
		//EventSize += sizeof(FNewEventEvent::Fields[0]) * Info->FieldCount;
		//EventSize += NamesSize;

		//FLogScope LogScope = FLogScope::Enter<FEventInfo::Flag_NoSync>(EventUid, EventSize);
		//auto& Event = *(FNewEventEvent*)(LogScope.GetPointer());

		//// Write event's main properties.
		//Event.EventUid = uint16(Uid) >> EKnownEventUids::_UidShift;
		//Event.LoggerNameSize = LoggerName.Length;
		//Event.EventNameSize = EventName.Length;
		//Event.Flags = 0;

		//uint32 Flags = Info->Flags;
		//if (Flags & FEventInfo::Flag_Important)		Event.Flags |= uint8(EEventFlags::Important);
		//if (Flags & FEventInfo::Flag_MaybeHasAux)	Event.Flags |= uint8(EEventFlags::MaybeHasAux);
		//if (Flags & FEventInfo::Flag_NoSync)		Event.Flags |= uint8(EEventFlags::NoSync);

		//// Write details about event's fields
		//Event.FieldCount = uint8(Info->FieldCount);
		//for (uint32 i = 0; i < Info->FieldCount; ++i)
		//{
		//	const FFieldDesc& Field = Info->Fields[i];
		//	auto& Out = Event.Fields[i];
		//	Out.Offset = Field.ValueOffset;
		//	Out.Size = Field.ValueSize;
		//	Out.TypeInfo = Field.TypeInfo;
		//	Out.NameSize = Field.NameSize;
		//}

		//// Write names
		//uint8* Cursor = (uint8*)(Event.Fields + Info->FieldCount);
		//auto WriteName = [&Cursor](const ANSICHAR* Data, uint32 Size)
		//{
		//	memcpy(Cursor, Data, Size);
		//	Cursor += Size;
		//};

		//WriteName(LoggerName.Ptr, LoggerName.Length);
		//WriteName(EventName.Ptr, EventName.Length);
		//for (uint32 i = 0; i < Info->FieldCount; ++i)
		//{
		//	const FFieldDesc& Field = Info->Fields[i];
		//	WriteName(Field.Name, Field.NameSize);
		//}

		//LogScope.Commit();
	}

}
}