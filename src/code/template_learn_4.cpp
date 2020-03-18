//#include<iostream>
//using namespace std;
//
//// C++11 提供了用省略号表示一个参数包, 通过递归定义的方式进行解包读取
//template<typename T, typename... Args>
//void show_list(const T& value, const Args&... args)
//{
//	cout << value << " ";
//	show_list(args...); // 递归调用
//}
//
//// 最后调用解包
//template<typename T>
//void show_list(const T& value)
//{
//	cout << value << endl;
//}
//
//int main()
//{
//	{
//		show_list(1, 2.0, "123123");
//	}
//}
