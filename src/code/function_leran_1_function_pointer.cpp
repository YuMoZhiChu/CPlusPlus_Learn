//#include<iostream>
//using namespace std;
//
//double fun_prototype(int); // ������ԭ��
//
//// ������ʵ��
//double fun_prototype(int a)
//{
//	cout << a << endl;
//	return 1.0;
//}
//
//int fun_prototype2(int b)
//{
//	return 2;
//}
//
//// ����ָ�������õĲ���
//// ����ڶ����������Ǻ���ָ��
//void estimate(int lines, double(*pf)(int)){}
//
//int main()
//{
//	{
//		// ����һ������ָ��
//		// pf ��һ��ָ������ָ�� ��Ҫһ�� int���� ����double ����
//		double(*pf)(int);
//
//		pf = fun_prototype; // ����ָ�븳ֵ
//		// pf = fun_prototype2; // ������ֵ�ʹ�����
//	}
//	{
//		// ����ָ�������, ����Ҫ������
//		double *pf1 (int); // ����һ������ double* �ĺ���
//		double(*pf2)(int); // ������Ǻ���ָ��
//	}
//	{
//		// ֱ�ӽ����������������뼴��
//		// ���������Ǻ���ָ��
//		estimate(1, fun_prototype);
//	}
//	{
//		// ʹ�ú���ָ����ú���  fun_prototype �� ���� , pf �Ǻ���ָ��, *pf �Ǻ��� ����ʹ���ϣ�������
//		auto pf = fun_prototype;
//		fun_prototype(1);
//		(*fun_prototype)(2);
//		pf(3);
//		(*pf)(4);
//		cout << "" << endl;
//	}
//}
