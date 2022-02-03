// 这是一个纯 Windows 的多线程示例
// 用的是 win 的接口
// UE 是在这个基础之上完成的

/*
* https://docs.microsoft.com/en-us/windows/win32/sync/using-event-objects
* 
Applications can use event objects in a number of situations to 
notify a waiting thread of the occurrence of an event.
应用程序可以在各种情况下, 使用事件, 去通知一个等待中的线程运行。

For example, overlapped I/O operations on files, named pipes, 
and communications devices use an event object to signal their completion.
比如, 文件IO, 命名管道, 和通信设备的交互, 都会使用一个 event 去通知他们的完成。

For more information about the use of event objects in overlapped I/O operations,
see Synchronization and Overlapped Input and Output.
微软的官方平台上, 有更多相关于 IO 的事件同步的示例.

The following example uses event objects to prevent several threads from reading from a shared memory buffer
while a master thread is writing to that buffer.
下面给出的实例, 演示了在一个主线程写入一块内存时, 有多个线程在尝试读取这块内存, 如何使用 event 来保证竞争.

First, the master thread uses the CreateEvent function to create a manual-reset event object 
whose initial state is nonsignaled.
首先, 我们的主线程, 使用 CreateEvent 函数, 创建了一个 手动重置 的 event, 这个 event 在初始化的时候是未激活的.

Then it creates several reader threads.
然后主线程创建了几个 读取线程.

The master thread performs a write operation and then sets the event object to the signaled state
when it has finished writing.
主线程进行的是写操作, 并且再完成写入后, 将 event 设置为激活.

Before starting a read operation, each reader thread uses WaitForSingleObject to wait for
the manual-reset event object to be signaled.
在开始一个读取线程时, 每个读取器会使用 WaitForSingleObject 去等待 手动重置 event 被激活.

When WaitForSingleObject returns, this indicates that the main thread is ready for it to begin its read operation.
当 WaitForSingleObject 返回时, 这表示主线程已经准备好了, 可以读取共享内存中的内容.

*/

#include <windows.h>
#include <stdio.h>

#define THREADCOUNT 4 

HANDLE ghWriteEvent;
HANDLE ghThreads[THREADCOUNT];

// 线程函数的 前置声明
DWORD WINAPI ThreadProc(LPVOID);

void CreateEventsAndThreads(void)
{
	int i;
	DWORD dwThreadID;

	// Create a manual-reset event object. The write thread sets this
	// object to the signaled state when it finishes writing to a 
	// shared buffer. 
	// 创建一个 手动重置 event, 当主线程完成对共享内存的写入时, state 会变成 true

	ghWriteEvent = CreateEvent(
		NULL,               // default security attributes
		TRUE,               // manual-reset event
		FALSE,              // initial state is nonsignaled
		TEXT("WriteEvent")  // object name
	);

	if (ghWriteEvent == NULL)
	{
		printf("CreateEvent failed (%d)\n", GetLastError());
		return;
	}

	// Create multiple threads to read from the buffer.
	// 创建多个读取线程

	for (i = 0; i < THREADCOUNT; i++)
	{
		// TODO: More complex scenarios may require use of a parameter
		//   to the thread procedure, such as an event per thread to  
		//   be used for synchronization.
		// 在更复杂的情况下, 我们需要更多的参数, 比如我们要给每个线程分配一个单独的 event 去激活
		ghThreads[i] = CreateThread(
			NULL,              // default security
			0,                 // default stack size
			ThreadProc,        // name of the thread function 线程函数的名字
			NULL,              // no thread parameters 并没有其他的线程函数
			0,                 // default startup flags 初始标记
			&dwThreadID);

		if (ghThreads[i] == NULL)
		{
			printf("CreateThread failed (%d)\n", GetLastError());
			return;
		}
	}
}

void WriteToBuffer(VOID)
{
	// TODO: Write to the shared buffer.

	printf("Main thread writing to the shared buffer...\n");

	// Set ghWriteEvent to signaled
	// SetEvent 就是 Windows 的接口, 直接把 ghWriteEvent 设置为信号 OK
	if (!SetEvent(ghWriteEvent))
	{
		printf("SetEvent failed (%d)\n", GetLastError());
		return;
	}
}

void CloseEvents()
{
	// Close all event handles (currently, only one global handle).
	// 关闭事件
	CloseHandle(ghWriteEvent);
}

int main(void)
{
	DWORD dwWaitResult;

	// TODO: Create the shared buffer

	// Create events and THREADCOUNT threads to read from the buffer
	// 创建 Event 和 线程
	CreateEventsAndThreads();

	// At this point, the reader threads have started and are most
	// likely waiting for the global event to be signaled. However, 
	// it is safe to write to the buffer because the event is a 
	// manual-reset event.
	// 在这一刻, 读取线程已经全部开始了, 并且可能在等待全局的 event 激活
	// 然而现在是安全的, 因为这个事件是一个 手动重置事件
	WriteToBuffer();

	printf("Main thread waiting for threads to exit...\n");

	// The handle for each thread is signaled when the thread is
	// terminated.
	// 这个句柄, 会在所有线程完成后, 才会激活
	dwWaitResult = WaitForMultipleObjects(
		THREADCOUNT,   // number of handles in array
		ghThreads,     // array of thread handles
		TRUE,          // wait until all are signaled, 直到所有的线程都完成了
		INFINITE);

	switch (dwWaitResult)
	{
		// All thread objects were signaled
	case WAIT_OBJECT_0:
		printf("All threads ended, cleaning up for application exit...\n");
		break;

		// An error occurred
	default:
		printf("WaitForMultipleObjects failed (%d)\n", GetLastError());
		return 1;
	}

	// Close the events to clean up

	CloseEvents();

	return 0;
}

DWORD WINAPI ThreadProc(LPVOID lpParam)
{
	// lpParam not used in this example.
	UNREFERENCED_PARAMETER(lpParam);

	DWORD dwWaitResult;

	printf("Thread %d waiting for write event...\n", GetCurrentThreadId());

	// 等待 event 被激活
	dwWaitResult = WaitForSingleObject(
		ghWriteEvent, // event handle
		INFINITE);    // indefinite wait

	switch (dwWaitResult)
	{
		// Event object was signaled
	case WAIT_OBJECT_0:
		//
		// TODO: Read from the shared buffer
		//
		printf("Thread %d reading from buffer\n",
			GetCurrentThreadId());
		break;

		// An error occurred
	default:
		printf("Wait error (%d)\n", GetLastError());
		return 0;
	}

	// Now that we are done reading the buffer, we could use another
	// event to signal that this thread is no longer reading. This
	// example simply uses the thread handle for synchronization (the
	// handle is signaled when the thread terminates.)

	printf("Thread %d exiting\n", GetCurrentThreadId());
	return 1;
}