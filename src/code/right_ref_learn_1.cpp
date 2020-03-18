#include<iostream>
#include<utility>
using namespace std;

class Useless
{
public:
	int n; // 
	char * pc; //
	static int ct;
	void ShowObject() const;

	Useless();
	explicit Useless(int k);
	Useless(int k, char ch);
	Useless(const Useless & f); // 常规的拷贝构造函数
	Useless(Useless && f); // 移动构造函数
	~Useless();
	Useless operator+(const Useless & f) const;
	void ShowData() const;

	// 定义引用赋值 和 移动赋值
	Useless & operator=(const Useless & f);
	Useless & operator=(Useless && f);

};

int Useless::ct = 0;

Useless::Useless()
{
	++ct;
	n = 0;
	pc = nullptr;
	cout << "使用  初始  构造器的调用, 当前 Useless 的个数 " << ct << endl;
	ShowObject();
}

Useless::Useless(int k): n(k)
{
	++ct;
	cout << "使用  int  构造器的调用, 当前 Useless 的个数 " << ct << endl;
	pc = new char[n];
	ShowObject();
}

Useless::Useless(int k, char ch) : n(k)
{
	++ct;
	cout << "使用  int,char  构造器的调用, 当前 Useless 的个数 " << ct << endl;
	pc = new char[n];
	for (int i = 0; i < n; ++i)
		pc[i] = ch;
	ShowObject();
}

Useless::Useless(const Useless & f) : n(f.n)
{
	++ct;
	cout << "使用  引用  构造器的调用, 当前 Useless 的个数 " << ct << endl;
	pc = new char[n];
	for (int i = 0; i < n; ++i)
		pc[i] = f.pc[i];
	ShowObject();
}

Useless::Useless(Useless && f) : n(f.n)
{
	++ct;
	cout << "使用  右值  构造器的调用, 当前 Useless 的个数 " << ct << endl;
	pc = f.pc;
	f.pc = nullptr;
	f.n = 0;
	ShowObject();
}

Useless::~Useless()
{
	cout << "析构函数调用, 剩下物体个数 " << --ct << endl;
	cout << "删除物体: " << endl;
	ShowObject();
	delete[] pc;
}

Useless Useless::operator+(const Useless & f) const
{
	cout << " 进入定义的 + 函数" << endl;
	Useless temp = Useless(n + f.n);
	for (int i = 0; i < n; i++)
		temp.pc[i] = pc[i];
	for (int i = n; i < temp.n; i++)
		temp.pc[i] = f.pc[i - n];
	cout << "temp object:\n";
	cout << " 离开定义的 + 函数" << endl;
	return temp;
}

void Useless::ShowObject() const
{
	cout << "有多少个元素" << n;
	cout << " 数据地址  " << (void*)pc << endl;
}

void Useless::ShowData() const
{
	if (n == 0)
		cout << "空的 object";
	else
		for (int i = 0; i < n; i++)
			cout << pc[i];
	cout << endl;
}

Useless & Useless::operator=(const Useless & f)
{
	cout << "=========进入引用赋值函数" << endl;
	if (this == &f)
		return *this;
	delete[]pc;
	n = f.n;
	pc = new char[n];
	for (int i = 0; i < n; i++)
		pc[i] = f.pc[i];
	return *this;
}

Useless & Useless::operator=(Useless && f)
{
	cout << "=========进入移动赋值函数" << endl;
	if (this == &f)
		return *this;
	delete[]pc;
	n = f.n;
	pc = f.pc;
	f.pc = nullptr;
	f.n = 0;
	return *this;
}

int main()
{
	//{
	//	Useless one(10, 'x');
	//	Useless two = one;      // 这里调用的是 拷贝构造函数 也就是引用
	//	Useless three(20, 'o');
	//	Useless four(one + three); // 1. 调用 operator+ 2. 函数的返回值作为右值 调用右值构造函数

	//	// 如果是在 C++98 的定义中, 或者把 移动构造注释
	//	// Useless four(one + three) 的第二步 会走引用构造函数 因为 const 引用机制, 如果类型不匹配, 就会生成 临时变量
	//	// 在旧版的 C++98 中, 还会出现多一次 Useless 的临时构造, 这里应该是编辑器帮忙优化了

	//	cout << "              " << endl;

	//}
	//{
	//	Useless one(10, 'x');
	//	Useless two;
	//	two = one; // 引用赋值
	//	Useless three;
	//	three = one + two; // 移动赋值
	//}
	{
		Useless one(10, 'x');
		Useless two;
		two = one; // 引用赋值
		one.ShowData();
		two = move(one); // 强制移动赋值
		// 如果没有定义 移动赋值 函数, 会调用引用赋值 因为 const 引用机制, 如果类型不匹配, 就会生成 临时变量
		one.ShowData();
	}
}
