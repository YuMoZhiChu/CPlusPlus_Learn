//#include<iostream>
//using namespace std;
//
//
//// 这是3个函数原型
//const double * f1(const double ar[], int n);
//const double * f2(const double [], int);
//const double * f3(const double *, int);
//// 这些函数的特征标志看似不同, 但在编译器上来看 他们都是一样的
//// 参数 1 都可以看做 const double *
//
//// 使用 using 来简化(typedef 也可以)
//typedef const double * (*p_fun)(const double *, int);
//using p_fun2 = const double * (*)(const double *, int);
//
//int main()
//{
//	double av[6] = { 11111.1, 22222.2, 33333.3, 0, 0, 0};
//
//	// 这是函数指针的初始化 和 赋值
//	const double * (*p1) (const double *, int) = f1;
//	// 用 auto 可以偷懒
//	auto p2 = f2;
//
//	// 这里是调用 f1(), 显示的是返回值 也就是 const double*, 然后是对 返回的指针 做取内容
//	cout << (*p1)(av, 3) << ": " << *(*p1)(av, 3) << endl;
//	// 同理, 这里是调用 f2()
//	cout << p2(av, 3) << ": " << *p2(av, 3) << endl;
//
//	cout << "函数指针 数组 玩法" << endl;
//
//	// 这里是定义一个函数指针数组, 因为 auto 不能用来初始化列表 所以不能用 auto 偷懒
//	const double * (*pa[3]) (const double *, int) = { f1, f2, f3 };
//	auto pb = pa; // 但是声明同样的类型, 就很简单了
//	// 逐个调用
//	for (int i = 0; i < 3; ++i)
//		cout << pa[i](av, 3) << ": " << *pa[i](av, 3) << endl;
//
//	cout << "函数指针 迷惑 玩法" << endl;
//	// 首先 pa 虽然是一个指针, 不过它是 代表整个数组, 所以 我们可以用一个指针, 来指向这个数组
//	auto pc = &pa;
//	// 当然也可以自己做一个声明, 多加一个 * , 把 pc 换成 (*pd)
//	const double * (*(*pd)[3]) (const double *, int) = &pa;
//	// 使用 pc 来进行调用
//	cout << (*pc)[0](av, 3) << ": " << *(*pc)[0](av, 3) << endl;
//	// 在这里 pa 是数组名, &pa 是pa第一个元素的地址, 如果打印, 他们的值是一样的
//	cout << pa << " " << &pa << endl;
//	// 但是 pa+1 是数组中下一个元素的地址, &pa+1 是数组pa后面, 一个内存块的地址, 这里输出是显示了 +16
//	cout << pa + 1 << " " << &pa + 1 << endl;
//	// 对于取地址和取引用 有    **&pa == *pa == pa[0]
//	// 对于 pc, *pc 是函数, 所以 *(*pc)[i] 也是可以做函数调用
//	cout << (*(*pd)[2])(av, 3) << ": " << *(*(*pd)[2])(av, 3) << endl;
//
//	cout << "函数指针 简化 玩法" << endl;
//	// 使用type 或者 using
//	p_fun pe = f1;
//	cout << pe(av, 3) << ": " << *(pe(av, 3)) << endl;
//	p_fun2 pf = f2;
//	cout << pf(av, 3) << ": " << *(pf(av, 3)) << endl;
//}
//
//// 函数原型的实现
//const double * f1(const double * ar, int n) {
//	return ar;
//}
//const double * f2(const double ar[], int n) {
//	return ar + 1;
//}
//const double * f3(const double ar[], int n) {
//	return ar + 2;
//}
