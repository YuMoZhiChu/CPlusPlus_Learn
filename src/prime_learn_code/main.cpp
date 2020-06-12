#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Example {
public:
	static constexpr double rate = 6.5;
	static string str;
	static int vecSize;
	static vector<double> vec;
	static const double array[];
};

//constexpr double Example::rate;
//int Example::vecSize = 20;
//vector<double> Example::vec(Example::vecSize);
//const double Example::array[] = { 1,2,3 };

class Y {
public:
	Y(int _i1, int _i2): i1(_i1),i2(_i2){
		// 先执行
		cout << "call Y(int _i1, int _i2)" << endl;
	}
	Y(): Y(1, 2) { // 委托
		// 后执行
		cout << "call Y()" << endl;
	}
private:
	int i1;
	int i2;
};

static int a = 2;

int main()
{
	a = 3;
	Y y;
	Example;
}
// 这段程序会输出 1-10 的值