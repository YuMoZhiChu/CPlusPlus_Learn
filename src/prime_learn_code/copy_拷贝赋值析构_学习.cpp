//#include <iostream>
//using namespace std;
//
//class numbered {
//public:
//	numbered()
//	{
//		// 这个静态变量，只声明一次
//		static int unique = 10;
//		mysn = unique++;
//	}
//
//	int mysn;
//};
//
//void f(numbered s)
//{
//	std::cout << s.mysn << std::endl;
//}
//
//int main()
//{
//	// 这是拷贝构造，
//	numbered a, b = a, c = b;
//	f(a);
//	f(b);
//	f(c);
//
//	// 这里默认初始化，会调用一次
//	numbered d;
//}