//#include<iostream>
//
//using namespace std;
//
//int main()
//{
//	// 基础引用玩法
//	int rats = 101;
//	int & rodents = rats;
//	cout << "rats = " << rats;
//	cout << ", rodents = " << rodents << endl;
//	rodents++;
//	cout << "rats = " << rats;
//	cout << ", rodents = " << rodents << endl;
//	cout << "rats address = " << &rats;
//	cout << ", rodents address = " << &rodents << endl;
//	// 特点:
//	// 1. rodents 的类型是 int &
//	// 2. rodents++ 该操作将一个拥有2个名称的变量加1
//	// 3. rodents 和 rat 取地址位置一样
//
//	int rats_2 = 101;
//	int & rodents_2 = rats_2;
//	int * prats_2 = &rats;
//	// 从表达式上来说
//	// 1. rodents_2 和 *prats_2 都能和 rats_2 互换
//	// 2. &rodents_2 和 prats_2 都能和 &rats_2 互换
//
//	int rats_3 = 101;
//	const int rats_3_const = 101;
//	int * prats_3 = &rats_3;
//	int * const prats_3_const_ptr = &rats_3; // const 指针, *prats_3_const_ptr 的类型是 int
//	const int * prats_3_const_val = &rats_3_const; // const int 的指针, *prats_3_const_val 的类型是 const int
//	cout << "prats_3_const_ptr : " << prats_3_const_ptr << " prats_3_const_val : " << prats_3_const_val << endl;
//	prats_3_const_val = &rats_3; // const int 的指针, 可以赋值非const的值
//	prats_3_const_val = &(const int)rats_3; // 等价于做了隐式类型转换
//	// prats_3_const_ptr = &rats_3; const 类型的变量无法修改
//	// int & rodents_3; // 在初始化时，必须与某个变量关联起来
//	// int * const prats_3_const_ptr; // 在初始化时, 因为这是 const 的指针, 所以必须有初始化
//	int & rodents_3 = *prats_3_const_ptr; // 引用在某种程度上和 const 引用相似
//
//	int rats_4 = 101;
//	int * pt_4 = &rats_4;
//	int & rodents_4 = *pt_4;
//	rodents_4 = 50;
//	cout << "rats_4 = " << rats_4 << endl; // 这是等同的修改, rodents_4 引用的就是 rats_4
//}
