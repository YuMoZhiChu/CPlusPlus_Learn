#pragma once
#include "../ue_basic_typedef.h"

namespace Trace {
namespace Private {

////////////////////////////////////////////////////////////////////////////////
struct FWriteBuffer
{
	uint32						Overflow;
	uint16						Size;
	uint16						ThreadId;
	uint64						PrevTimestamp;
	FWriteBuffer* __restrict	NextThread;
	FWriteBuffer* __restrict	NextBuffer;
	uint8* __restrict			Cursor;
	uint8* __restrict volatile	Committed;
	uint8* __restrict			Reaped;
	UPTRINT volatile			EtxOffset;
};

void Writer_InternalInitialize();

////////////////////////////////////////////////////////////////////////////////
uint64				TimeGetTimestamp();
//FWriteBuffer*       Writer_NextBuffer(int32);
//FWriteBuffer*       Writer_GetBuffer();

uint64 Writer_GetTimestamp(FWriteBuffer* Buffer);

}
};
