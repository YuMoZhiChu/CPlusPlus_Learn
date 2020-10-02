#include <iostream>
using namespace std;

class numbered {
public:
	// 这是默认构造
	numbered()
	{
		// 这个静态变量，只声明一次
		static int unique = 10;
		// 这里第二次调用，还是 d，还是 11
		mysn = unique++;
		cout << "调用了默认构造函数" << endl;
	}

	// 如果定义了 拷贝构造，那么 a = b 会进这里
	numbered(const numbered &n)
	{
		mysn = n.mysn + 1;
		cout << "调用了拷贝构造函数" << endl;
	}

	// 为什么前后都是引用
	// 因为传入，和返回，如果不是引用，我们都会发生多一次的构造，这样很不利
	numbered& operator=(const numbered &rhs)
	{
		mysn = rhs.mysn;
		cout << "调用了拷贝赋值函数" << endl;
		return *this;
	};

	int mysn;
};

// 如果不传入引用，这里会多调用一次， 拷贝构造
// 如果是用引用，则不会传入
void f(numbered s)
{
	std::cout << s.mysn << std::endl;
}

// 返回一个实例
numbered get_a_numbered()
{
	numbered k;
	return k;
}

int main()
{
	// 这是拷贝构造，b = a，c = b
	numbered a, b = a, c = b;
	f(a);
	f(b);
	f(c);

	// 这里默认初始化，会调用一次
	cout << "默认初始化，会调用一次" << endl;
	numbered d;

	// 尝试用定义+函数返回
	cout << "尝试用定义+函数返回" << endl;
	// 为什么这里没有两次 构造，因为编译器优化了
	numbered e = get_a_numbered();

	// 这是拷贝赋值
	cout << "这是拷贝赋值" << endl;
	// 注意到，我们单独使用，get_a_numbered()，一样有构造，所以我们可以理解成构造返回值
	e = get_a_numbered();
}