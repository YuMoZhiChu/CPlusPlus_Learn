//#include <iostream>
//#include <functional>
//using namespace std;
//
//class MyInt
//{
//public:
//	friend int operator+(const MyInt& lhs, const MyInt& rhs);
//
//	MyInt(int _v) :v(_v) {}
//
//	// ��Ա���������ȼ� ����  ��Ԫ����
//	// rhs �ĵ�ַ �ʹ��� �� B �ĵ�ַ��һ���� ����û�з���һ�����¹��죬�������Ż���
//	int operator+(const MyInt& rhs)
//	{
//		return v + rhs.v;
//	}
//
//private:
//	int v;
//};
//
//int operator+(const MyInt& lhs, const MyInt& rhs)
//{
//	return lhs.v + rhs.v;
//}
//
//int main(void)
//{
//	MyInt A(1);
//	MyInt B(2);
//	cout << A + B << endl;
//}