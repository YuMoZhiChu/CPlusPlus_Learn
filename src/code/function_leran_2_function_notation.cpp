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
//		// ���ﴫһ�� ʵ���� operator()() ����Ҳ����, ע�⺯����־Ҫһ��
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
//		// ���ƵĹ����� bind1st
//		list_1.remove_if(bind2nd(greater<int>(),3));
//		cout << "" << endl;
//	}
//}
