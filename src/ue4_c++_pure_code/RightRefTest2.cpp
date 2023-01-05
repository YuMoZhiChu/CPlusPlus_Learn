//#include <iostream>
//#include <string.h>
//
//using namespace std;
//
//class A
//{
//public:
//
//	A(int InA = 1)
//	{
//		a = InA;
//	}
//
//	int* GetAPtr()
//	{
//		return &a;
//	}
//
//private:
//
//	int a = 1;
//
//};
//
//
//A BuildAObject()
//{
//	return A(1);
//}
//
//
//
//__forceinline bool TestAnd()
//{
//	return true || true;
//}
//
//void ChangeTest(int&& right_value)
//{
//	static int TestCount = 0;
//	++TestCount;
//	right_value = TestCount;
//}
//
//int main()
//{
//	int* x = nullptr;
//	{
//		x = BuildAObject().GetAPtr();
//	}
//
//	int bk = 1;
//	++bk;
//
//	/*while (true)
//	{
//		++bk;
//	}*/
//	
//	bool testResult = !TestAnd();
//
//
//	int a = 999;
//	int& a_ref = a;
//	int&& a_right_ref = std::move(a);
//	ChangeTest(std::move(a));
//	ChangeTest(std::move(a_ref));
//	ChangeTest(std::move(a_right_ref));
//
//
//	++bk;
//
//}