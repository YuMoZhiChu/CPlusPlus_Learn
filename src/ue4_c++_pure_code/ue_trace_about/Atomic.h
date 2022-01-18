// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include <atomic>
//#if PLATFORM_CPU_X86_FAMILY
// 这个宏是机器相关的, 本机是默认开启就可以了
#include <immintrin.h>

namespace Trace {
namespace Private {

////////////////////////////////////////////////////////////////////////////////
template <typename Type> Type	AtomicLoadRelaxed(Type volatile* Source);
template <typename Type> Type	AtomicLoadAcquire(Type volatile* Source);
template <typename Type> void	AtomicStoreRelaxed(Type volatile* Target, Type Value);
template <typename Type> void	AtomicStoreRelease(Type volatile* Target, Type Value);
template <typename Type> bool	AtomicCompareExchangeRelaxed(Type volatile* Target, Type New, Type Expected);
template <typename Type> bool	AtomicCompareExchangeAcquire(Type volatile* Target, Type New, Type Expected);
template <typename Type> bool	AtomicCompareExchangeRelease(Type volatile* Target, Type New, Type Expected);
template <typename Type> Type	AtomicAddRelaxed(Type volatile* Target, Type Value);
template <typename Type> Type	AtomicAddRelease(Type volatile* Target, Type Value);
template <typename Type> Type	AtomicAddAcquire(Type volatile* Target, Type Value);
void							PlatformYield();

////////////////////////////////////////////////////////////////////////////////
inline void PlatformYield()
{
// #if PLATFORM_CPU_X86_FAMILY
// 这是一个等待指令, 对于多线程同步的情况, 能有很大的提升(依赖机器
	_mm_pause();
}

/*

参考
https://zh.cppreference.com/w/cpp/atomic/memory_order#.E5.AE.BD.E6.9D.BE.E9.A1.BA.E5.BA.8F

每个 std::atomic 模板的实例化和全特化定义一个原子类型。若一个线程写入原子对象，同时另一线程从它读取，则行为良好定义（数据竞争的细节见内存模型）。

另外，对原子对象的访问可以建立线程间同步，并按 std::memory_order 所对非原子内存访问定序。

std::atomic 既不可复制亦不可移动。

在下面出现的顺序

memory_order_relaxed	宽松操作：没有同步或顺序制约，仅对此操作要求原子性（见下方宽松顺序）。

memory_order_acquire	有此内存顺序的加载操作，在其影响的内存位置进行获得操作：当前线程中读或写不能被重排到此加载前。其他释放同一原子变量的线程的所有写入，能为当前线程所见（见下方释放获得顺序）。
memory_order_release	有此内存顺序的存储操作进行释放操作：当前线程中的读或写不能被重排到此存储后。当前线程的所有写入，可见于获得该同一原子变量的其他线程（见下方释放获得顺序），并且对该原子变量的带依赖写入变得对于其他消费同一原子对象的线程可见（见下方释放消费顺序）。

*/

////////////////////////////////////////////////////////////////////////////////
template <typename Type>
inline Type AtomicLoadRelaxed(Type volatile* Source)
{
	std::atomic<Type>* T = (std::atomic<Type>*) Source;
	return T->load(std::memory_order_relaxed);
}

////////////////////////////////////////////////////////////////////////////////
template <typename Type>
inline Type AtomicLoadAcquire(Type volatile* Source)
{
	std::atomic<Type>* T = (std::atomic<Type>*) Source;
	return T->load(std::memory_order_acquire);
}

////////////////////////////////////////////////////////////////////////////////
template <typename Type>
inline void AtomicStoreRelaxed(Type volatile* Target, Type Value)
{
	std::atomic<Type>* T = (std::atomic<Type>*) Target;
	T->store(Value, std::memory_order_relaxed);
}

////////////////////////////////////////////////////////////////////////////////
template <typename Type>
inline void AtomicStoreRelease(Type volatile* Target, Type Value)
{
	std::atomic<Type>* T = (std::atomic<Type>*) Target;
	T->store(Value, std::memory_order_release);
}

/*

参考
https://zh.cppreference.com/w/cpp/atomic/atomic/compare_exchange

参考运行代码
```
#include <atomic>
#include <iostream>

template <typename Type>
inline bool AtomicCompareExchangeRelaxed(Type volatile* Target, Type New, Type Expected)
{
	std::atomic<Type>* T = (std::atomic<Type>*) Target;
	return T->compare_exchange_strong(Expected, New, std::memory_order_relaxed);
}

int main()
{
	int a = 1;
	if (AtomicCompareExchangeRelaxed(&a, 2, 1))
	{
		std::cout << "True, a = " << a << std::endl;
	} else {
		std::cout << "False, a = " << a << std::endl;
	}
}
```

CAS(Compare and Swap)
是个原子操作，保证了如果需要更新的地址没有被他人改动多，那么它可以安全的写入。
而这也是我们对于某个数据或者数据结构加锁要保护的内容，保证读写的一致性，不出现dirty data.
现在几乎所有的CPU指令都支持CAS的原子操作。

compare_exchange_weak 

weak 版和 strong 版的区别：
weak 版本的 CAS 允许偶然出乎意料的返回（比如在字段值和期待值一样的时候却返回了 false ），不过在一些循环算法中，这是可以接受的。通常它比起 strong 有更高的性能。

*/
////////////////////////////////////////////////////////////////////////////////
template <typename Type>
inline bool AtomicCompareExchangeRelaxed(Type volatile* Target, Type New, Type Expected)
{
	std::atomic<Type>* T = (std::atomic<Type>*) Target;
	return T->compare_exchange_weak(Expected, New, std::memory_order_relaxed);
}

////////////////////////////////////////////////////////////////////////////////
template <typename Type>
inline bool AtomicCompareExchangeAcquire(Type volatile* Target, Type New, Type Expected)
{
	std::atomic<Type>* T = (std::atomic<Type>*) Target;
	return T->compare_exchange_weak(Expected, New, std::memory_order_acquire);
}

////////////////////////////////////////////////////////////////////////////////
template <typename Type>
inline bool AtomicCompareExchangeRelease(Type volatile* Target, Type New, Type Expected)
{
	std::atomic<Type>* T = (std::atomic<Type>*) Target;
	return T->compare_exchange_weak(Expected, New, std::memory_order_release);
}

/*
https://zh.cppreference.com/w/cpp/atomic/atomic/fetch_add
原子地以值和 arg 的算术加法结果替换当前值。运算是读修改写操作。按照 order 的值影响内存。
*/

////////////////////////////////////////////////////////////////////////////////
template <typename Type>
inline Type AtomicAddRelaxed(Type volatile* Target, Type Value)
{
	std::atomic<Type>* T = (std::atomic<Type>*) Target;
	return T->fetch_add(Value, std::memory_order_relaxed);
}

////////////////////////////////////////////////////////////////////////////////
template <typename Type>
inline Type AtomicAddAcquire(Type volatile* Target, Type Value)
{
	std::atomic<Type>* T = (std::atomic<Type>*) Target;
	return T->fetch_add(Value, std::memory_order_acquire);
}

////////////////////////////////////////////////////////////////////////////////
template <typename Type>
inline Type AtomicAddRelease(Type volatile* Target, Type Value)
{
	std::atomic<Type>* T = (std::atomic<Type>*) Target;
	return T->fetch_add(Value, std::memory_order_release);
}

} // namespace Private
} // namespace Trace
