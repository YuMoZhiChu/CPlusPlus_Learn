//#include<iostream>
//using namespace std;
//
//class A {
//public:
//	A(int a, int b, int c)
//	{
//		cout << a << b << c << endl;
//	}
//};
//
//template<typename T, typename... Ts>
//unique_ptr<T> my_make_unique(Ts&&... params)
//{
//	return unique_ptr<T>(new T(forward<Ts>(params)...));
//}
//
//void cout3int(int a,float b,int c)
//{
//	cout << a << b << c << endl;
//}
//
//template<typename... Ts>
//void test_unpack(Ts... params)
//{
//	cout3int(params...);
//}
//
//int main()
//{
//	{
//		//make_unique<A>(1, 2, 3);
//		// my_make_unique<A>(2, 3, 4);
//
//		test_unpack(1, 2, 3);
//	}
//}
