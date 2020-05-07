//#include<iostream>
//#include<list>
//#include<iterator>
//#include<algorithm>
//#include<functional>
//
//using namespace std;
//
//bool CutOff(int x)
//{
//	if (x > 4)
//		return false;
//	return true;
//}
//
//int main()
//{
//	{
//		list<int> list_1 = { 1,2,3,4,5,6 };
//		// 这里传一个 实现了 operator()() 的类也可以, 注意函数标志要一致
//		list_1.remove_if(CutOff);
//		cout << "" << endl;
//	}
//	{
//		list<int> list_1 = { 1,2,3,4,5,6 };
//		list_1.sort(greater<int>());
//		cout << "" << endl;
//	}
//	{
//		list<int> list_1 = { 1,2,3,4,5,6 };
//		// 类似的功能有 bind1st
//		list_1.remove_if(bind2nd(greater<int>(),3)); // list_1 = 1,2,3
//		// list_1.remove_if(bind1st(greater<int>(), 3)); // list_1 = 3,4,5,6
//		cout << "" << endl;
//	}
//}
