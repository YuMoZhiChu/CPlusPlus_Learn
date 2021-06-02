#include <iostream>
#include <string.h>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;


class A
{

};

class B:public A
{
};

//int main()
//{
//	vector<A> a1;
//	vector<class A> a2;
//
//	B b1 = B();
//	B b2 = B();
//
//	a1.push_back(b1);
//
//	a2.push_back(b2);
//
//	// 好像并没有什么区别, 验证了一个屁, 继续工作
//	int bk = 1;
//
//}