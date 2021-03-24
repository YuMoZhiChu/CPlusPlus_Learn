//#include<iostream>
//#include<string>
//#include<vector>
//#include<unordered_map>
//#include<queue>
//#include<set>
//#include<map>
//#include<algorithm>
//#include<numeric>

using namespace std;

class A {
public:
	virtual void f(){}
	int a;
};

class B : virtual public A{
public:
	virtual void f() override {}
	int b;
};

class C : public virtual A{};

class D : public B, C{};

int main()
{
	int b_size = sizeof B;

	D d;
	int d_size = sizeof D;

	//auto p = A::f;
	auto ref_p = &A::f;


	int bk = 0;
}

