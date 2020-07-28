//#include <iostream>
//#include <functional>
//using namespace std;
//
//void TestLambda_value_get_1()
//{
//	int v1 = 42;
//	auto f = [v1]() mutable {return ++v1; }; // 默认是一个 const？或者是，默认不改变拷贝的值
//	v1 = 0;
//	auto j = f();
//	v1 = 1; // 跟上面的区别是，这里 v1 改了，但是 j 本质是一个拷贝，所以还是 43
//}
//
//void TestLambda_ref_get_1()
//{
//	int v1 = 42;
//	auto f = [&v1]() {return ++v1; }; // 默认是一个 const？或者是，默认不改变拷贝的值
//	v1 = 0;
//	auto j = f();
//	v1 = 1; // 跟上面的区别是，这里的 j 因为 v1 改了，也变成了 1
//}
//
////void TestLambda_value_get_2()
////{
////	int v1 = 42;
////	auto f = [v1]() {return ++v1; }; // 这里会直接编译不通过
////	v1 = 0;
////	auto j = f();
////}
//
//int main(void)
//{
//	TestLambda_value_get_1();
//	TestLambda_ref_get_1();
//	// bind(TestLambda_ref_get_1, placeholders::_1, 1); // placeholders::_1 表示第一个占位符
//}