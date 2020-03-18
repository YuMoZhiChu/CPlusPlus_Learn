//#include<iostream>
//using namespace std;
//
//// 函数模板
//template <typename AnyType>
//void Swap(AnyType& a, AnyType& b)
//{
//	AnyType c;
//	c = a;
//	a = b;
//	b = c;
//}
//
//int intR_f() { return 0; }
//
//// 因为decltype 在参数声明后面, 所以在 a,b 的作用区内, 返回指定的返回值类型
//template <typename T>
//auto Sum(T& a, T& b) -> decltype(a + b)
//{
//	return a + b;
//}
//
//int main()
//{
//	{
//		int x;
//		decltype(x) y; // decltype 能让y的类型为 (表达式) 中的类型
//		cout << "This is a test" << endl;
//	}
//
//	{
//		int x = 0;
//		float y = 1;
//		decltype(x + y) xpy = x + y;// 这里因为是 x+y 会转换为 float, 所以 xpy 的类型为 float
//		cout << "This is a test" << endl;
//	}
//
//	{
//		double x;
//		double y;
//		double & rx = x;
//		const double * pd;
//		decltype(x) w;
//		decltype(rx) u = y;
//		decltype(pd) v;
//		cout << "This is a test" << endl;
//	}
//
//	{
//		decltype(intR_f()) x;
//		cout << "This is a test" << endl;
//	}
//	{
//		double x;
//		decltype((x)) y = x;
//		cout << "This is a test" << endl;
//	}
//	{
//		int j = 3;
//		int &k = j;
//		int &n = j;
//		decltype(j + 6) i1;
//		decltype(100L) i2;
//		decltype(k + n) i3;// 这里 k 和 n 虽然都是引用, 但是他们加起来的表达式不是, 是int
//		cout << "This is a test" << endl;
//	}
//}
