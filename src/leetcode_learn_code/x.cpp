//#include <iostream>
//#include <functional>
//using namespace std;
//
//class MyInt
//{
//public:
//	friend int operator+(const MyInt& lhs, const MyInt& rhs);
//
//	MyInt(int _v) :v(_v) {}
//
//	// 成员函数的优先级 大于  友元函数
//	// rhs 的地址 和传入 的 B 的地址是一样的 （并没有发生一次重新构造，可能是优化了
//	int operator+(const MyInt& rhs)
//	{
//		return v + rhs.v;
//	}
//
//private:
//	int v;
//};
//
//int operator+(const MyInt& lhs, const MyInt& rhs)
//{
//	return lhs.v + rhs.v;
//}
//
//int main(void)
//{
//	MyInt A(1);
//	MyInt B(2);
//	cout << A + B << endl;
//}