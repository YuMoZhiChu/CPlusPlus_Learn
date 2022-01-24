#include "ue_channel.h"
#include "string.h"
#include "Atomic.h"


namespace Trace {

	///////////////////////////////////////////////////////////////////////////////
	struct FTraceChannel : public FChannel
	{
		bool IsEnabled() const { return true; }
		explicit operator bool() const { return true; }
	};

	// 这是一个一定会显示的 TraceChannel, 直接用继承并重写两个判断函数实现
	static FTraceChannel	TraceLogChannelDetail;
	// 将静态全局变量, 开放给外部使用 代码版本迭代问题
	FChannel& TraceLogChannel = TraceLogChannelDetail;

	///////////////////////////////////////////////////////////////////////////////

	////////////////////////////////////////////////////////////////////////////////
	// 获取一个字符串的哈希值
	static uint32 GetChannelHash(const ANSICHAR* Input, int32 Length)
	{
		// 去除最后一个 s
		// Make channel names tolerant to ending 's' (or 'S').
		// Example: "Log", "log", "logs", "LOGS" and "LogsChannel" will all match as being the same channel.
		if (Length > 0 && (Input[Length - 1] | 0x20) == 's')
		{
			--Length;
		}

		uint32 Result = 0x811c9dc5;
		for (; Length; ++Input, --Length)
		{
			Result ^= *Input | 0x20; // a cheap ASCII-only case insensitivity. | 0x20 是一个非常取巧的转小写的判断
			Result *= 0x01000193; // 显然, 这是一个用于 Hash 的 Magic Number
		}
		return Result;
	}
	///////////////////////////////////////////////////////////////////////////////

	///////////////////////////////////////////////////////////////////////////////
	// 去除尾部的 String
	static uint32 GetChannelNameLength(const ANSICHAR* ChannelName)
	{
		// Strip "Channel" suffix if it exists
		size_t Len = uint32(strlen(ChannelName));
		if (Len > 7)
		{
			if (strcmp(ChannelName + Len - 7, "Channel") == 0)
			{
				Len -= 7;
			}
		}

		return Len;
	}
	///////////////////////////////////////////////////////////////////////////////

	FChannel::Iter::~Iter()
	{
		if (Inner[2] == nullptr)
		{
			return;
		}

		/*for (auto* Node = (FChannel*)Inner[2];; PlatformYield())
		{
			Node->Next = AtomicLoadRelaxed(&GHeadChannel);
			if (AtomicCompareExchangeRelaxed(&GHeadChannel, (FChannel*)Inner[1], Node->Next))
			{
				break;
			}
		}*/
	}

};