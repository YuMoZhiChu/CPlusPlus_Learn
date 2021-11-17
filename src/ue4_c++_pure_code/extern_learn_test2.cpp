
#include "extern_learn_test2.h"

// 声明类型 也是在别处定义了
struct TestStruct123;
// 已经定义了, 这里只需要声明即可
extern TestStruct123 Struct123;

void f2_extern_test()
{
	Struct123;
	int bk = 1;
}
