//#include<iostream>
//using namespace std;
//
//struct Point
//{
//	int x; int y;
//	Point(int _x, int _y):x(_x),y(_y){}
//};
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
//// ����ģ������
//template <typename AnyType>
//void Swap(AnyType& a, AnyType& b, int delta)
//{
//	AnyType c;
//	c = a;
//	a = b + delta;
//	b = c + delta;
//}
//
//// ����ģ����ʾʵ����
//// ��ֻ��һ�������� ����Ҫ����Ĵ���ʵ��
//template void Swap<float>(float & a, float & b);
//
//// ������Ҫ������������ʵ�� -- ������ܵ������ƺ�������, ���þ�����ǰ������
//void Swap(float & a, float & b)
//{
//	cout << "���� ����ģ����ʾʵ����" << endl;
//}
//
//// ����ģ����ʾ���廯
//// template<> void Swap<Point>(Point & a, Point & b) �����д������
//template<> void Swap(Point & a, Point & b)	
//{
//	cout << "���� ����ģ����ʾ���廯" << endl;
//}
//
//template <typename Type>
//class MyStack
//{
//public:
//	void push(const Type& item);
//};
//
//template <typename Type>
//void MyStack<Type>::push(const Type& item)
//{
//	cout << item << endl;
//	cout << "A Implatement of template function" << endl;
//}
//
//int main()
//{
//	
//	{
//		int a = 1;
//		int b = 2;
//		Swap(a, b);
//		cout << a << b << endl;
//
//		// ����ģ������
//		Swap(a, b, 1);
//		cout << a << b << endl;
//
//		// ���� ����ģ�� ��ʾ���廯
//		Point aPoint(1, 2);
//		Point bPoint(3, 4);
//		Swap(aPoint, bPoint);
//
//		float c = 1.0f;
//		float d = 1.0f;
//		Swap(c, d);
//
//		// 1. ���ڸ���������, ������: ��ģ�庯��(��ͨ����) ģ�庯�� ģ����ʾ���廯����
//		// 2. ģ����ʾ���廯���� �� template<> ��ͷ����ͨ������ָ������
//		// 3. ���ȼ�  ��ģ�庯��(��ͨ����) >  ģ����ʾ���廯����  >  ģ�庯��
//
//	}
//
//	//{
//	//	std::cout << "hello world" << std::endl;
//
//	//	MyStack<int> my;
//	//	my.push(2);
//	//}
//
//}
