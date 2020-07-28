//#include <algorithm>
//#include <iostream>
//#include <vector>
//#include <list>
//using namespace std;
//
//int main()
//{
//	char c1[10] = "eipi10";
//	char c2[10] = "eipi10";
//	std::vector<char*> roster1{ c1 };
//	std::list<char*> roster2{ c2 };
//
//	// 可能会相等，但他们比较的是地址，不是内容，C风格字符串要用 strcmp
//	std::cout << std::equal(c1, c1+10, c2) << endl;
//
//	std::cout << std::equal(roster1.cbegin(), roster1.cend(), roster2.cbegin()) << endl;
//
//	string str1 = "test1";
//	string str2 = "test1";
//	std::cout << std::equal(str1.cbegin(), str1.cend(), str2.cbegin()) << endl;
//
//	vector<int> v = { 0,1,2,3,4,0 };
//	vector<int> v2;
//	replace_copy(v.cbegin(), v.cend(), back_inserter(v2), 0, 42); // 不用 back_insert 会报错
//
//}
