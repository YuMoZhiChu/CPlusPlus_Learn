//#include "ue_cpuprofilertrace.h"
//#include "trace.h"
//#include "ue_trace.h"
//#include "ue_event.h"
//#include "ue_channel.h"
//#include "../ue_basic_typedef.h"
//
//UE_TRACE_CHANNEL_DEFINE(CpuChannel)
//
///*
//Trace::FCpuProfilerEventSpecFields
//	Id_Field
//	CharSize_Field
//*/
//UE_TRACE_EVENT_BEGIN(CpuProfiler, EventSpec, Important)
//UE_TRACE_EVENT_FIELD(uint32, Id)
//UE_TRACE_EVENT_FIELD(uint8, CharSize)
//UE_TRACE_EVENT_END()
//
//UE_TRACE_EVENT_BEGIN(CpuProfiler, EventBatch, NoSync)
//UE_TRACE_EVENT_END()
//
//UE_TRACE_EVENT_BEGIN(CpuProfiler, EndCapture, Important)
//UE_TRACE_EVENT_END()
//
//UE_TRACE_EVENT_BEGIN(CpuProfiler, EndThread, NoSync)
//UE_TRACE_EVENT_END()
//
//template <>
//inline uint32 Strihash_DEPRECATED(const ANSICHAR* Data)
//{
//	// make sure table is initialized
//	check(CRCTable_DEPRECATED[1] != 0);
//
//	uint32 Hash = 0;
//	while (*Data)
//	{
//		ANSICHAR Ch;// = TChar<ANSICHAR>::ToUpper(*Data++);
//		uint8 B = Ch;
//		Hash = ((Hash >> 8) & 0x00FFFFFF) ^ CRCTable_DEPRECATED[(Hash ^ B) & 0x000000FF];
//	}
//	return Hash;
//}
//
//struct FCpuProfilerTraceInternal
//{
//	enum
//	{
//		MaxBufferSize = 256,
//		MaxEncodedEventSize = 15, // 10 + 5
//		FullBufferThreshold = MaxBufferSize - MaxEncodedEventSize,
//	};
//
//	template<typename CharType>
//	struct FDynamicScopeNameMapKeyFuncs
//	{
//		typedef const char* KeyType;
//		typedef const char* KeyInitType;
//		typedef const TPairInitializer<const CharType*, uint32>& ElementInitType;
//
//		enum { bAllowDuplicateKeys = false };
//
//		static bool Matches(const CharType* A, const CharType* B)
//		{
//			return TCString<CharType>::Stricmp(A, B) == 0;
//		}
//
//		static uint32 GetKeyHash(const CharType* Key)
//		{
//			return Strihash_DEPRECATED(Key);
//		}
//	}
//
//};