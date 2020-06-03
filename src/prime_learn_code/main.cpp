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



int main()
{
	cout << __func__ << __LINE__ << __FILE__ << endl;

	int a[10] = { 0 };
	f();
	EXIT_FAILURE;
	EXIT_SUCCESS;
}
// 这段程序会输出 1-10 的值