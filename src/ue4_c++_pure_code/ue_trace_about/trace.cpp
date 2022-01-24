#include"trace.h"
#include "ue_channel.h"
#include "../ue_basic_typedef.h"
#include "ue_trace.h"
#include "ue_event.h"

namespace Trace
{

	////////////////////////////////////////////////////////////////////////////////
	template <int DestSize>
	static uint32 ToAnsiCheap(ANSICHAR(&Dest)[DestSize], const WIDECHAR* Src)
	{
		const WIDECHAR* Cursor = Src;
		for (ANSICHAR& Out : Dest)
		{
			Out = ANSICHAR(*Cursor++ & 0x7f);
			if (Out == '\0')
			{
				break;
			}
		}
		Dest[DestSize - 1] = '\0';
		return uint32(UPTRINT(Cursor - Src));
	};

	void SetMemoryHooks(AllocFunc Alloc, FreeFunc Free)
	{
		// Private::Writer_MemorySetHooks(Alloc, Free);
	}

	void Initialize(const FInitializeDesc& Desc)
	{
		// Private::Writer_Initialize(Desc);
		// FChannel::Initialize();
	}

	void Shutdown()
	{
		// Private::Writer_Shutdown();
	}

	void Update()
	{
		// Private::Writer_Update();
	}

	bool SendTo(const TCHAR_UE* Host, uint32 Port /*= 0*/)
	{
		/*char Host[256];
		ToAnsiCheap(Host, Host);
		return Private::Writer_SendTo(Host, Port);*/
		return true;
	}

	bool WriteTo(const TCHAR_UE* Path)
	{
		/*char Path[512];
		ToAnsiCheap(Path, InPath);
		return Private::Writer_WriteTo(Path);*/
		return true;
	}

	bool IsTracing()
	{
		// return Private::Writer_IsTracing();
		return true;
	}

	bool IsChannel(const TCHAR_UE* ChanneName)
	{
		ANSICHAR ChannelNameA[64];
		ToAnsiCheap(ChannelNameA, ChanneName);
		// return FChannel::FindChannel(ChannelNameA) != nullptr;
		return true;
	}

	bool ToggleChannel(const TCHAR_UE* ChannelName, bool bEnabled)
	{
		ANSICHAR ChannelNameA[64];
		ToAnsiCheap(ChannelNameA, ChannelName);
		// return FChannel::Toggle(ChannelNameA, bEnabled);
		return true;
	}

	// [TODO] 这一句好像没有, 1 是没用到, 2 是用一个 静态全局变量 就应该是 只在定义的文件中是可见的
	UE_TRACE_CHANNEL_EXTERN(TraceLogChannel)

	// $Trace 可以作为变量设置进去
	/*
	Trace::F$TraceThreadInfoFields
		SystemId_Field        Trace::TField<0,0,unsigned int>
		SortHint_Field        Trace::TField<1,4,int>
		Name_Field            Trace::TField<2,8,enum Trace::AnsiString>
		EventProps_Private    Trace::TField<259(没用的),8,enum Trace::EventProps>
		Attachment_Field      Trace::TField<0,8,enum Trace::Attachment>
	*/
	UE_TRACE_EVENT_BEGIN($Trace, ThreadInfo)
	UE_TRACE_EVENT_FIELD(uint32, SystemId)
	UE_TRACE_EVENT_FIELD(int32, SortHint)
	UE_TRACE_EVENT_FIELD(Trace::AnsiString, Name)
	UE_TRACE_EVENT_END()

	UE_TRACE_EVENT_BEGIN($Trace, ThreadGroupBegin)
	UE_TRACE_EVENT_FIELD(Trace::AnsiString, Name)
	UE_TRACE_EVENT_END()

	UE_TRACE_EVENT_BEGIN($Trace, ThreadGroupEnd)
	UE_TRACE_EVENT_END()

	void ThreadRegister(const TCHAR_UE* Name, uint32 SystemId, int32 SortHint)
	{
		/*UE_TRACE_LOG($Trace, ThreadInfo, TraceLogChannel)
			<< ThreadInfo.SystemId(SystemId)
			<< ThreadInfo.SortHint(SortHint)
			<< ThreadInfo.Name(Name);*/
	}

	void ThreadGroupBegin(const TCHAR_UE* Name)
	{
		/*UE_TRACE_LOG($Trace, ThreadGroupBegin, TraceLogChannel)
			<< ThreadGroupBegin.Name(Name);*/
	}

}