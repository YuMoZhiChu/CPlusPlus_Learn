//#include<iostream>
//using namespace std;
//
//double fun_prototype(int); // 函数的原型
//
//// 函数的实现
//double fun_prototype(int a)
//{
//	cout << a << endl;
//	return 1.0;
//}
//
//int fun_prototype2(int b)
//{
//	return 2;
//}
//
//// 函数指针做调用的参数
//// 这里第二个参数就是函数指针
//void estimate(int lines, double(*pf)(int)){}
//
//int main()
//{
//	{
//		// 声明一个函数指针
//		// pf 是一个指向函数的指针 需要一个 int参数 返回double 类型
//		double(*pf)(int);
//
//		pf = fun_prototype; // 函数指针赋值
//		// pf = fun_prototype2; // 这样赋值就错误了
//	}
//	{
//		// 函数指针的声明, 必须要用括号
//		double *pf1 (int); // 这是一个返回 double* 的函数
//		double(*pf2)(int); // 这个才是函数指针
//	}
//	{
//		// 直接将函数名做参数传入即可
//		// 函数名即是函数指针
//		estimate(1, fun_prototype);
//	}
//	{
//		// 使用函数指针调用函数  fun_prototype 是 函数 , pf 是函数指针, *pf 是函数 但是使用上，都可以
//		auto pf = fun_prototype;
//		fun_prototype(1);
//		(*fun_prototype)(2);
//		pf(3);
//		(*pf)(4);
//		cout << "" << endl;
//	}
//}
