//#include<iostream>
//using namespace std;
//
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
//// 模板中, 可以多带一个 非类型或者表达式参数
//template <typename Type, int n>
//class A
//{};
//
//// 模板也可以设定默认参数类型
//template <typename Type, typename Type2 = float>
//class B
//{};
//
//// 使用 sort_for_A 来代替模板的使用, using 是 C++11 的新用法, 在一定程度上 = typedef
//template <typename Type>
//using sort_for_A = A<Type, 10>;
//
//int main()
//{
//	{
//		A<double, 12> a1;
//		A<double, 13> a2;
//		// 在这里 a1 和 a2 是属于两个不同的类
//		// 这个功能就比较鸡肋了
//	}
//	{
//		// 相当于 A<int, 10> a;
//		sort_for_A<int> a;
//	}
//}
