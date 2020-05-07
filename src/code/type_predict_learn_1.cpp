#include<iostream>
using namespace std;

void f_const_int(const int x)
{
	// 打印地址
	cout << &x << endl;
}

void f_const_int_ref(const int& x)
{
	// 打印地址
	cout << &x << endl;
}

void f_const_int_right_ref(const int&& x)
{
	// 打印地址
	cout << &x << endl;
}

int main()
{
	{
		const int ci = 1;
		cout << &ci << endl;
		f_const_int(ci); // 可以看到这里是新建了一个 const int
		f_const_int_ref(ci);
		f_const_int_right_ref(move(ci));
		cout << ci << endl;
	}
}
