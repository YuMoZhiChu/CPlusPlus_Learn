#include <iostream>
#include <map>
#include <memory>
#include <vector>
using namespace std;

int main(void)
{
	vector<string> b1;
	{
		vector<string> b2 = { "a1", "b2" };
		b1 = b2;
	}

	{
		allocator<int> alloc;
		auto p = alloc.allocate(5);
		cout << p << endl;
	}

	return 0;
}