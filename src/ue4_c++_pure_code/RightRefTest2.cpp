#include <iostream>
#include <string.h>

using namespace std;

class A
{
public:

	A(int InA = 1)
	{
		a = InA;
	}

	int* GetAPtr()
	{
		return &a;
	}

private:

	int a = 1;

};


A BuildAObject()
{
	return A(1);
}

inline bool TestAnd()
{
	return false && true;
}

int main()
{
	int* x = nullptr;
	{
		x = BuildAObject().GetAPtr();
	}

	int bk = 1;
	++bk;

	/*while (true)
	{
		++bk;
	}*/
	
	bool testResult = !TestAnd();

	++bk;

}