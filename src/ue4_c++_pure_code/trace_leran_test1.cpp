#include <iostream>
#include <string.h>
#include <vector>

using namespace std;

#define TestVA(...) \
	enum TestVA\
	{ \
	Important = 0, \
	NoSync = 1, \
	PartialEventFlags = (0, ##__VA_ARGS__) & ~Important, \
	}; \

#define TestVA2(...) \
	int TestVA2_Value = (1, 123, 446, 789);\
	/*int TestVA2_Value2 = (1, ##__VA_ARGS__); \
	int TestVA2_Value3 = (0, ##__VA_ARGS__); \*/

int main()
{
	TestVA2(123, 446, 789);

	int a = (1, 2, 3);

	int bk = 1;
	++bk;
}