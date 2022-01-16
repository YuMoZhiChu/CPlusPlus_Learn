#pragma once

#include "../ue_basic_typedef.h"

namespace Trace {
/*
	A named channel which can be used to filter trace events. Channels can be
	combined using the '|' operator which allows expressions like

	Channel 是用来过滤一些 Trace 事件的, 通过 '|' 操作符, 来支持 Channel 的合并

	```
	UE_TRACE_LOG(FooWriter, FooEvent, FooChannel|BarChannel);
	```

	Note that this works as an AND operator, similar to how a bitmask is constructed.
	这其实就是一个 并 操作, 所以类似掩码一样进行构造

	Channels are by default enabled until this method is called. This is to allow
	events to be emitted during static initialization. In fact all events during
	this phase are always emitted. In this method we disable all channels except
	those specified on the command line using -tracechannels argument.
*/
class FChannel
{
public:
	struct Iter
	{
		~Iter();
		const FChannel* GetNext();
		void* Inner[3];
	};

	struct InitArgs
	{
		const ANSICHAR*     Desc;		// User facing description string
		bool				bReadOnly;	// If set, channel cannot be changed during a run, only set through command line.

	};

	void	            Setup(const ANSICHAR* InChannelName, const InitArgs& Args);
	static void         Initialize();
	static Iter			ReadNew();
	void				Announce() const;
	static bool			Toggle(const ANSICHAR* ChannelName, bool bEnabled);
	static void			ToggleAll(bool bEnabled);
	static FChannel*    FindChannel(const ANSICHAR* ChannelName);
	bool				Toggle(bool bEnabled);
	bool				IsEnabled() const;
	explicit			operator bool() const;
	bool				operator | (const FChannel& Rhs) const;

private:
	FChannel* Next;
	struct
	{
		const ANSICHAR* Ptr;
		uint32			Len;
		uint32			Hash;
	}					Name;
	volatile int32		Enabled;
	InitArgs			Args;
};

} // namespace Trace