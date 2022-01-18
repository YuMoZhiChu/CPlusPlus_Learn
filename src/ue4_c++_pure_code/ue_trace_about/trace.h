#pragma once
#include "../ue_basic_typedef.h"

namespace Trace
{

	struct FInitializeDesc
	{
		bool			bUseWorkerThread = true;
	};

	// 定义函数指针类型
	typedef void*		AllocFunc(SIZE_T, uint32);
	typedef void		FreeFunc(void*, SIZE_T);

	// 设置内存钩子
	void	SetMemoryHooks(AllocFunc Alloc, FreeFunc Free);

	void	Initialize(const FInitializeDesc& Desc);

	void	Shutdown();

	void	Update();

	bool	SendTo(const TCHAR_UE* Host, uint32 Port = 0);

	bool	WriteTo(const TCHAR_UE* Path);

	bool	IsTracing();

	bool	IsChannel(const TCHAR_UE* ChanneName);

	bool	ToggleChannel(const TCHAR_UE* ChannelName, bool bEnabled);

	void	ThreadRegister(const TCHAR_UE* Name, uint32 SystemId, int32 SortHint);

	void	ThreadGroupBegin(const TCHAR_UE* Name);
};

////////////////////////////////////////////////////////////////////////////////
// 宏的重命名
#define UE_TRACE_EVENT_DEFINE(LoggerName, EventName)					TRACE_PRIVATE_EVENT_DEFINE(LoggerName, EventName)
#define UE_TRACE_EVENT_BEGIN(LoggerName, EventName, ...)				TRACE_PRIVATE_EVENT_BEGIN(LoggerName, EventName, ##__VA_ARGS__)
#define UE_TRACE_EVENT_BEGIN_EXTERN(LoggerName, EventName, ...)			TRACE_PRIVATE_EVENT_BEGIN_EXTERN(LoggerName, EventName, ##__VA_ARGS__)
#define UE_TRACE_EVENT_FIELD(FieldType, FieldName)						TRACE_PRIVATE_EVENT_FIELD(FieldType, FieldName)
#define UE_TRACE_EVENT_END()											TRACE_PRIVATE_EVENT_END()
#define UE_TRACE_LOG(LoggerName, EventName, ChannelsExpr, ...)			TRACE_PRIVATE_LOG(LoggerName, EventName, ChannelsExpr, ##__VA_ARGS__)
#define UE_TRACE_LOG_SCOPED(LoggerName, EventName, ChannelsExpr, ...)	TRACE_PRIVATE_LOG_SCOPED(LoggerName, EventName, ChannelsExpr, ##__VA_ARGS__)
#define UE_TRACE_LOG_SCOPED_T(LoggerName, EventName, ChannelsExpr, ...)	TRACE_PRIVATE_LOG_SCOPED_T(LoggerName, EventName, ChannelsExpr, ##__VA_ARGS__)

////////////////////////////////////////////////////////////////////////////////
#define UE_TRACE_CHANNEL(ChannelName, ...)				TRACE_PRIVATE_CHANNEL(ChannelName, ##__VA_ARGS__)
#define UE_TRACE_CHANNEL_EXTERN(ChannelName, ...)		TRACE_PRIVATE_CHANNEL_EXTERN(ChannelName, ##__VA_ARGS__)
#define UE_TRACE_CHANNEL_MODULE_EXTERN(ModuleApi, ChannelName)	TRACE_PRIVATE_CHANNEL_MODULE_EXTERN(ModuleApi, ChannelName)
#define UE_TRACE_CHANNEL_DEFINE(ChannelName, ...)		TRACE_PRIVATE_CHANNEL_DEFINE(ChannelName, ##__VA_ARGS__)
#define UE_TRACE_CHANNELEXPR_IS_ENABLED(ChannelsExpr)	TRACE_PRIVATE_CHANNELEXPR_IS_ENABLED(ChannelsExpr)
