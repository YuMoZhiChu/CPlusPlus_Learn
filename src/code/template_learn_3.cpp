//#include<iostream>
//using namespace std;
//
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
//// ģ����, ���Զ��һ�� �����ͻ��߱��ʽ����
//template <typename Type, int n>
//class A
//{};
//
//// ģ��Ҳ�����趨Ĭ�ϲ�������
//template <typename Type, typename Type2 = float>
//class B
//{};
//
//// ʹ�� sort_for_A ������ģ���ʹ��, using �� C++11 �����÷�, ��һ���̶��� = typedef
//template <typename Type>
//using sort_for_A = A<Type, 10>;
//
//int main()
//{
//	{
//		A<double, 12> a1;
//		A<double, 13> a2;
//		// ������ a1 �� a2 ������������ͬ����
//		// ������ܾͱȽϼ�����
//	}
//	{
//		// �൱�� A<int, 10> a;
//		sort_for_A<int> a;
//	}
//}
