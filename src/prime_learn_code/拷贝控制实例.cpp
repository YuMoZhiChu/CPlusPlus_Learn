//#include <iostream>
//using namespace std;
//
//class numbered {
//public:
//	// 这是默认构造
//	numbered()
//	{
//		// 这个静态变量，只声明一次
//		static int unique = 10;
//		// 这里第二次调用，还是 d，还是 11
//		mysn = unique++;
//		cout << "调用了默认构造函数" << endl;
//	}
//
//	// 如果定义了 拷贝构造，那么 a = b 会进这里
//	numbered(const numbered& n)
//	{
//		mysn = n.mysn + 1;
//		cout << "调用了拷贝构造函数" << endl;
//	}
//
//	int mysn;
//};
//
//// 如果不传入引用，这里会多调用一次， 拷贝构造
//// 如果是用引用，则不会传入
//void f(numbered s)
//{
//	std::cout << s.mysn << std::endl;
//}
//
//int main()
//{
//	// 这是拷贝构造，b = a，c = b
//	numbered a, b = a, c = b;
//	f(a);
//	f(b);
//	f(c);
//
//	// 这里默认初始化，会调用一次
//	numbered d;
//}