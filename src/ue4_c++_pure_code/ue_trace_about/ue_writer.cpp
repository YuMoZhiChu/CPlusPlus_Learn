#include "ue_writer.h"


#	define _WINSOCK_DEPRECATED_NO_WARNINGS  
#	include <winsock2.h>
#	include <ws2tcpip.h>
// https://stackoverflow.com/questions/3484434/what-does-pragma-comment-mean
// 表示链接 ws2_32.lib 这个库, 和在工程设置里写上链入 wpcap.lib 的效果一样
#	pragma comment(lib, "ws2_32.lib")

#include <thread>

#pragma warning(push)
#pragma warning(disable : 6031) // WSAStartup() return ignore  - we're error tolerant



namespace Trace {
namespace Private {



	void Writer_InternalInitialize()
	{
		// [TODO] 初始化 全局单例的 Writer
	}

	uint64 TimeGetTimestamp()
	{
		LARGE_INTEGER Value;
		// https://blog.csdn.net/lsmdiao0812/article/details/3173374
		// 精确计算执行时间
		QueryPerformanceCounter(&Value);
		return Value.QuadPart;
	}

	uint64 Writer_GetTimestamp(FWriteBuffer* Buffer)
	{
		uint64 Ret = TimeGetTimestamp() - Buffer->PrevTimestamp;
		Buffer->PrevTimestamp += Ret;
		return Ret;
	}

}
}