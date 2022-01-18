#pragma once

// 实现 TField 对字符串的处理 [TODO]
#include "Atomic.h"
#include "Protocol.h"


namespace Trace {

namespace Private {

	////////////////////////////////////////////////////////////////////////////////
	// 基础模板函数, 根据 Callback 可调用函数(这里填入的还是一个右值), 完成对字符串的处理
	template <typename CallbackType>
	static void Field_WriteAuxData(uint32 Index, int32 Size, CallbackType&& Callback)
	{
		//static_assert(sizeof(Private::FWriteBuffer::Overflow) >= sizeof(FAuxHeader), "FWriteBuffer::Overflow is not large enough");

		//// Header
		//const int bMaybeHasAux = true;
		//FWriteBuffer* Buffer = Writer_GetBuffer();
		//Buffer->Cursor += sizeof(FAuxHeader) - bMaybeHasAux;

		//auto* Header = (FAuxHeader*)(Buffer->Cursor - sizeof(FAuxHeader));
		//Header->Size = Size << 8;
		//Header->FieldIndex = uint8(0x80 | (Index & int(EIndexPack::FieldCountMask)));

		//bool bCommit = ((uint8*)Header + bMaybeHasAux == Buffer->Committed);

		//// Array data
		//while (true)
		//{
		//	if (Buffer->Cursor >= (uint8*)Buffer)
		//	{
		//		if (bCommit)
		//		{
		//			AtomicStoreRelease(&(uint8* volatile&)(Buffer->Committed), Buffer->Cursor);
		//		}

		//		Buffer = Writer_NextBuffer(0);
		//		bCommit = true;
		//	}

		//	int32 Remaining = int32((uint8*)Buffer - Buffer->Cursor);
		//	int32 SegmentSize = (Remaining < Size) ? Remaining : Size;
		//	Callback(Buffer->Cursor, SegmentSize);
		//	Buffer->Cursor += SegmentSize;

		//	Size -= SegmentSize;
		//	if (Size <= 0)
		//	{
		//		break;
		//	}
		//}

		//// The auxiliary data null terminator.
		//Buffer->Cursor[0] = 0;
		//Buffer->Cursor++;

		//if (bCommit)
		//{
		//	AtomicStoreRelease(&(uint8* volatile&)(Buffer->Committed), Buffer->Cursor);
		//}
	}

	void Field_WriteAuxData(uint32, const uint8*, int32)
	{

	}

	void Field_WriteStringAnsi(uint32, const ANSICHAR*, int32)
	{

	}

	void Field_WriteStringAnsi(uint32, const TCHAR_UE*, int32)
	{

	}

	void Field_WriteStringWide(uint32, const TCHAR_UE*, int32)
	{

	}

} // namespace Private

} // namespace Trace