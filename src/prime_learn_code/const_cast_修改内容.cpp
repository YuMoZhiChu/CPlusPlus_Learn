//#include <iostream>
//using namespace std;
//
//void Fun(int &value)
//{
//	cout << "Fun(val) = " << value << endl;
//}
//
//const int val_g = 1000;
//
//int main(void)
//{
//	const int val = 100;
//
//	int *ptr = const_cast<int *>(&val);
//	*ptr = 200;
//	cout << &val << endl;
//	cout << ptr << endl;
//	cout << "val = " << val << endl;
//	cout << "*ptr = " << *ptr << endl;
//
//	int &ref = const_cast<int &>(val);
//	ref = 300;
//	cout << "val = " << val << endl;
//	cout << "ref = " << ref << endl;
//	Fun(const_cast<int &>(val));
//	// 以上例子中，val 是 100，其他的值是修改过的值，在编译生成的指令中val就已经被替换成100
//
//
//	int *ptr_g = const_cast<int *>(&val_g);
//	*ptr_g = 2000; // 这里会报错，触发写权限冲突
//	cout << &val_g << endl;
//	cout << ptr_g << endl;
//	cout << "val = " << val_g << endl;
//	cout << "*ptr = " << *ptr_g << endl;
//
//	return 0;
//}