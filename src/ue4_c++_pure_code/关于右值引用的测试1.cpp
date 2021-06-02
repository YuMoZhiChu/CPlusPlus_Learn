#include <iostream>
#include <string.h>
#include <vector>

using std::vector;
using std::cout;
using std::cin;
using std::endl;

class A
{
public:
	int num;
	A(int _n = 0)
	{
		num = _n;
	}
	A(const A& a)
	{
		num = a.num;
	}
	A(A&& a) noexcept
	{
		num = a.num;
	}

	A& A::operator=(A&& a) noexcept
	{
		cout << "A& A::operator=(A&& a) noexcept" << endl;
		num = a.num;
		return *this;
	}

	A& A::operator=(const A& a)
	{
		cout << "A& A::operator=(const A& a)" << endl;
		num = a.num;
		return *this;
	}

};

void f(const A& a)
{
	A b;
	b = a;
}

A f2()
{
	A a3;
	return a3;
}

int main()
{
	A a1;
	a1.num = 2000;
	A a2;
	a2 = std::move(a1);
	f(a1);

	int bk = 1;
}