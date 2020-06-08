#include<iostream>
#include<string>
#include<vector>
using namespace std;

vector<string> f()
{
	cout << __func__ << __LINE__ << __FILE__ << endl;

	if (true)
		return {}; // 返回空
	else
		return { "123", "222" }; // 返回列表初始化对象
}

int f1(int a, int b)
{
	return a + b;
}

int main()
{
	vector<int(*)(int, int)> v;
	v.push_back(&f1);
}
// 这段程序会输出 1-10 的值