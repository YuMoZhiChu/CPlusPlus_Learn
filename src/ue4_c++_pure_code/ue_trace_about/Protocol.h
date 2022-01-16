// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once


////////////////////////////////////////////////////////////////////////////////
#define TRACE_PRIVATE_PROTOCOL_4

// [TODO] 盲猜这里这一套应该是用于传递数据的, 暂时让它编译成功即可
// 应该是 Protocol 是逐步迭代的几个数据传输版本, 所以会有不同的 Protocol 版本, 目前用的是 第 4 版

// #pragma warning(push) 保存当前编译器的警告状态
// 4200 这个警告将不会出现
#if defined(_MSC_VER)
	#pragma warning(push)
	#pragma warning(disable : 4200) // non-standard zero-sized array
#endif

#include "Protocols/Protocol0.h"
#include "Protocols/Protocol1.h"
#include "Protocols/Protocol2.h"
#include "Protocols/Protocol3.h"
#include "Protocols/Protocol4.h"

#if defined(_MSC_VER)
	#pragma warning(pop)
#endif

////////////////////////////////////////////////////////////////////////////////
namespace Trace
{

enum ETransport : uint8
{
	_Unused		= 0,
	Raw			= 1,
	Packet		= 2,
	TidPacket	= 3,
};

enum ETransportTid : uint32
{
	Internal	= 0,
	Bias		= 1,
};

} // namespace Trace
