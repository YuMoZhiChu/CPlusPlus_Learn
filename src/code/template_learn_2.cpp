//#include<iostream>
//using namespace std;
//
//// ����ģ��
//template <typename AnyType>
//void Swap(AnyType& a, AnyType& b)
//{
//	AnyType c;
//	c = a;
//	a = b;
//	b = c;
//}
//
//int intR_f() { return 0; }
//
//// ��Ϊdecltype �ڲ�����������, ������ a,b ����������, ����ָ���ķ���ֵ����
//template <typename T>
//auto Sum(T& a, T& b) -> decltype(a + b)
//{
//	return a + b;
//}
//
//int main()
//{
//	{
//		int x;
//		decltype(x) y; // decltype ����y������Ϊ (���ʽ) �е�����
//		cout << "This is a test" << endl;
//	}
//
//	{
//		int x = 0;
//		float y = 1;
//		decltype(x + y) xpy = x + y;// ������Ϊ�� x+y ��ת��Ϊ float, ���� xpy ������Ϊ float
//		cout << "This is a test" << endl;
//	}
//
//	{
//		double x;
//		double y;
//		double & rx = x;
//		const double * pd;
//		decltype(x) w;
//		decltype(rx) u = y;
//		decltype(pd) v;
//		cout << "This is a test" << endl;
//	}
//
//	{
//		decltype(intR_f()) x;
//		cout << "This is a test" << endl;
//	}
//	{
//		double x;
//		decltype((x)) y = x;
//		cout << "This is a test" << endl;
//	}
//	{
//		int j = 3;
//		int &k = j;
//		int &n = j;
//		decltype(j + 6) i1;
//		decltype(100L) i2;
//		decltype(k + n) i3;// ���� k �� n ��Ȼ��������, �������Ǽ������ı��ʽ����, ��int
//		cout << "This is a test" << endl;
//	}
//}
