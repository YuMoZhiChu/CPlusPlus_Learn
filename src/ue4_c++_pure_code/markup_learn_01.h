#pragma once

// This pair of macros is used to help implement GENERATED_BODY() and GENERATED_USTRUCT_BODY()
// UE4 的 接续宏
#define BODY_MACRO_COMBINE_INNER(A,B,C,D) A##B##C##D
#define BODY_MACRO_COMBINE(A,B,C,D) BODY_MACRO_COMBINE_INNER(A,B,C,D)

// GENERATED_BODY 的目的，是生成具体的宏
#define GENERATED_BODY(...) BODY_MACRO_COMBINE(CURRENT_FILE_ID,_,__LINE__,_GENERATED_BODY);




// 这里直接写 类中的头文件


class UMyObject
{
	GENERATED_BODY() // 重点！将声明和元数据联系到一起
	// 该宏的最终目标，是生成一个

};

