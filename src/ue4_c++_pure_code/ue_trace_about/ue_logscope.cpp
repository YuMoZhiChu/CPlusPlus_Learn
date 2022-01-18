#include"ue_logscope.h"
#include "Atomic.h"
#include "ue_writer.h"

namespace Trace {
namespace Private {

	extern uint32 volatile	GLogSerial;

	template <uint32 Flags>
	FLogScope FLogScope::Enter(uint32 Uid, uint32 Size)
	{
		FLogScope Ret;
		bool bMaybeHasAux = (Flags & FEventInfo::Flag_MaybeHasAux) != 0;
		if ((Flags & FEventInfo::Flag_NoSync) != 0)
		{
			Ret.EnterNoSync(Uid, Size, bMaybeHasAux);
		}
		else
		{
			Ret.Enter(Uid, Size, bMaybeHasAux);
		}
		return Ret;
	}


	void FLogScope::Enter(uint32 Uid, uint32 Size, bool bMaybeHasAux)
	{

	}


	void FLogScope::EnterNoSync(uint32 Uid, uint32 Size, bool bMaybeHasAux)
	{

	}

	uint8* FLogScope::GetPointer() const
	{
		return Instance.Ptr;
	}


	void FLogScope::Commit() const
	{
		FWriteBuffer* Buffer = Instance.Buffer;
		AtomicStoreRelease((uint8**)&(Buffer->Committed), Buffer->Cursor);
	}


	void FLogScope::operator+=(const FLogScope&) const
	{
		Commit();
	}

	template <class T>
	void FLogScope::EnterPrelude(uint32 Size, bool bMaybeHasAux)
	{
		//uint32 AllocSize = sizeof(HeaderType) + Size + int(bMaybeHasAux);

		//FWriteBuffer* Buffer = Writer_GetBuffer();
		//Buffer->Cursor += AllocSize;
		//if (UNLIKELY(Buffer->Cursor > (uint8*)Buffer))
		//{
		//	Buffer = Writer_NextBuffer(AllocSize);
		//}

		//// The auxilary data null terminator.
		//if (bMaybeHasAux)
		//{
		//	Buffer->Cursor[-1] = 0;
		//}

		//uint8* Cursor = Buffer->Cursor - Size - int(bMaybeHasAux);
		//Instance = { Cursor, Buffer };
	}

	FScopedLogScope::~FScopedLogScope()
	{

	}


	void FScopedLogScope::SetActive()
	{

	}


	FScopedStampedLogScope::~FScopedStampedLogScope()
	{

	}


	void FScopedStampedLogScope::SetActive()
	{

	}

	template <bool>	struct TLogScopeSelector;
	template <>		struct TLogScopeSelector<false> { typedef FLogScope Type; };
	template <>		struct TLogScopeSelector<true> { typedef FImportantLogScope Type; };

	template <class T>
	auto TLogScope<T>::Enter(uint32 ExtraSize /*= 0*/)
	{
		uint32 Size = T::GetSize() + ExtraSize;
		uint32 Uid = T::GetUid();

		using LogScopeType = typename TLogScopeSelector<T::bIsImportant>::Type;
		return LogScopeType::template Enter<T::EventFlags>(Uid, Size);
	}

	template <class T>
	FLogScope TLogScope<T>::ScopedStampedEnter(uint32 ExtraSize /*= 0*/)
	{
		static_assert(!T::bIsImportant, "Important events cannot be logged with scope");

		uint64 Stamp;

		FWriteBuffer* Buffer = Writer_GetBuffer();
		if (UNLIKELY(int32((uint8*)Buffer - Buffer->Cursor) < int32(sizeof(Stamp))))
		{
			Buffer = Writer_NextBuffer(0);
		}

		Stamp = Writer_GetTimestamp(Buffer);
		Stamp <<= 8;
		Stamp += uint8(EKnownEventUids::EnterScope_T << EKnownEventUids::_UidShift);
		memcpy((uint64*)(Buffer->Cursor), &Stamp, sizeof(Stamp));
		Buffer->Cursor += sizeof(Stamp);

		AtomicStoreRelease((uint8**)&(Buffer->Committed), Buffer->Cursor);

		return Enter(ExtraSize);
	}

	template <class T>
	FLogScope TLogScope<T>::ScopedEnter(uint32 ExtraSize /*= 0*/)
	{
		static_assert(!T::bIsImportant, "Important events cannot be logged with scope");

		uint8 EnterUid = uint8(EKnownEventUids::EnterScope << EKnownEventUids::_UidShift);

		FWriteBuffer* Buffer = Writer_GetBuffer();
		if (UNLIKELY(int32((uint8*)Buffer - Buffer->Cursor)) < int32(sizeof(EnterUid)))
		{
			Buffer = Writer_NextBuffer(0);
		}

		Buffer->Cursor[0] = EnterUid;
		Buffer->Cursor += sizeof(EnterUid);

		AtomicStoreRelease((uint8**)&(Buffer->Committed), Buffer->Cursor);

		return Enter(ExtraSize);
	}
}
}