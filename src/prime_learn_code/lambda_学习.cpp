//#include <iostream>
//#include <functional>
//using namespace std;
//
//void TestLambda_value_get_1()
//{
//	int v1 = 42;
//	auto f = [v1]() mutable {return ++v1; }; // 默认是一个 const 或者是，默认不改变拷贝的值
//	v1 = 0;
//	auto j = f();
//	v1 = 1; // 跟上面的区别是，这里 v1 改了，但是 j 本质是一个拷贝，所以还是 43
//}
//
//void TestLambda_ref_get_1()
//{
//	int v1 = 42;
//	auto f = [&v1]() {return ++v1; }; // 默认是一个 const 或者是，默认不改变拷贝的值
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
//class TestA
//{
//public:
//	TestA() { aa = 11; }
//	void lambdaTest()
//	{
//		auto f = [this]() {
//			aa = 12; // 显示this能自动获取，也能修改, 用=全部获取也行
//			// this = null; this 是不能修改的哦, 这是一个 const 指针
//		};
//		f();
//		return;
//	}
//private:
//	int aa;
//};
//
//int main(void)
//{
//	TestLambda_value_get_1();
//	TestLambda_ref_get_1();
//
//	int a = 1;
//	int b = 2;
//	auto f1 = [&a](){
//		a = 3; // &a 可以修改 a 不能修改
//	};
//	TestA ta;
//	ta.lambdaTest();
//
//	// bind(TestLambda_ref_get_1, placeholders::_1, 1); // placeholders::_1 表示第一个占位符
//}