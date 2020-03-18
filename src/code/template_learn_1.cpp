//#include<iostream>
//using namespace std;
//
//struct Point
//{
//	int x; int y;
//	Point(int _x, int _y):x(_x),y(_y){}
//};
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
//// 函数模板重载
//template <typename AnyType>
//void Swap(AnyType& a, AnyType& b, int delta)
//{
//	AnyType c;
//	c = a;
//	a = b + delta;
//	b = c + delta;
//}
//
//// 函数模板显示实例化
//// 这只是一个声明， 还需要下面的代码实现
//template void Swap<float>(float & a, float & b);
//
//// 还是需要这样子来具体实现 -- 这个功能的意义似乎并不大, 作用就是提前做声明
//void Swap(float & a, float & b)
//{
//	cout << "调用 函数模板显示实例化" << endl;
//}
//
//// 函数模板显示具体化
//// template<> void Swap<Point>(Point & a, Point & b) 下面的写法更简单
//template<> void Swap(Point & a, Point & b)	
//{
//	cout << "调用 函数模板显示具体化" << endl;
//}
//
//template <typename Type>
//class MyStack
//{
//public:
//	void push(const Type& item);
//};
//
//template <typename Type>
//void MyStack<Type>::push(const Type& item)
//{
//	cout << item << endl;
//	cout << "A Implatement of template function" << endl;
//}
//
//int main()
//{
//	
//	{
//		int a = 1;
//		int b = 2;
//		Swap(a, b);
//		cout << a << b << endl;
//
//		// 函数模板重载
//		Swap(a, b, 1);
//		cout << a << b << endl;
//
//		// 调用 函数模板 显示具体化
//		Point aPoint(1, 2);
//		Point bPoint(3, 4);
//		Swap(aPoint, bPoint);
//
//		float c = 1.0f;
//		float d = 1.0f;
//		Swap(c, d);
//
//		// 1. 对于给定函数名, 可以有: 非模板函数(普通函数) 模板函数 模板显示具体化函数
//		// 2. 模板显示具体化函数 用 template<> 开头，并通过名称指出类型
//		// 3. 优先级  非模板函数(普通函数) >  模板显示具体化函数  >  模板函数
//
//	}
//
//	//{
//	//	std::cout << "hello world" << std::endl;
//
//	//	MyStack<int> my;
//	//	my.push(2);
//	//}
//
//}
