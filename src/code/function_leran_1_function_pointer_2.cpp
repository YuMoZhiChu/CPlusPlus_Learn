//#include<iostream>
//using namespace std;
//
//
//// ����3������ԭ��
//const double * f1(const double ar[], int n);
//const double * f2(const double [], int);
//const double * f3(const double *, int);
//// ��Щ������������־���Ʋ�ͬ, ���ڱ����������� ���Ƕ���һ����
//// ���� 1 �����Կ��� const double *
//
//// ʹ�� using ����(typedef Ҳ����)
//typedef const double * (*p_fun)(const double *, int);
//using p_fun2 = const double * (*)(const double *, int);
//
//int main()
//{
//	double av[6] = { 11111.1, 22222.2, 33333.3, 0, 0, 0};
//
//	// ���Ǻ���ָ��ĳ�ʼ�� �� ��ֵ
//	const double * (*p1) (const double *, int) = f1;
//	// �� auto ����͵��
//	auto p2 = f2;
//
//	// �����ǵ��� f1(), ��ʾ���Ƿ���ֵ Ҳ���� const double*, Ȼ���Ƕ� ���ص�ָ�� ��ȡ����
//	cout << (*p1)(av, 3) << ": " << *(*p1)(av, 3) << endl;
//	// ͬ��, �����ǵ��� f2()
//	cout << p2(av, 3) << ": " << *p2(av, 3) << endl;
//
//	cout << "����ָ�� ���� �淨" << endl;
//
//	// �����Ƕ���һ������ָ������, ��Ϊ auto ����������ʼ���б� ���Բ����� auto ͵��
//	const double * (*pa[3]) (const double *, int) = { f1, f2, f3 };
//	auto pb = pa; // ��������ͬ��������, �ͺܼ���
//	// �������
//	for (int i = 0; i < 3; ++i)
//		cout << pa[i](av, 3) << ": " << *pa[i](av, 3) << endl;
//
//	cout << "����ָ�� �Ի� �淨" << endl;
//	// ���� pa ��Ȼ��һ��ָ��, �������� ������������, ���� ���ǿ�����һ��ָ��, ��ָ���������
//	auto pc = &pa;
//	// ��ȻҲ�����Լ���һ������, ���һ�� * , �� pc ���� (*pd)
//	const double * (*(*pd)[3]) (const double *, int) = &pa;
//	// ʹ�� pc �����е���
//	cout << (*pc)[0](av, 3) << ": " << *(*pc)[0](av, 3) << endl;
//	// ������ pa ��������, &pa ��pa��һ��Ԫ�صĵ�ַ, �����ӡ, ���ǵ�ֵ��һ����
//	cout << pa << " " << &pa << endl;
//	// ���� pa+1 ����������һ��Ԫ�صĵ�ַ, &pa+1 ������pa����, һ���ڴ��ĵ�ַ, �����������ʾ�� +16
//	cout << pa + 1 << " " << &pa + 1 << endl;
//	// ����ȡ��ַ��ȡ���� ��    **&pa == *pa == pa[0]
//	// ���� pc, *pc �Ǻ���, ���� *(*pc)[i] Ҳ�ǿ�������������
//	cout << (*(*pd)[2])(av, 3) << ": " << *(*(*pd)[2])(av, 3) << endl;
//
//	cout << "����ָ�� �� �淨" << endl;
//	// ʹ��type ���� using
//	p_fun pe = f1;
//	cout << pe(av, 3) << ": " << *(pe(av, 3)) << endl;
//	p_fun2 pf = f2;
//	cout << pf(av, 3) << ": " << *(pf(av, 3)) << endl;
//}
//
//// ����ԭ�͵�ʵ��
//const double * f1(const double * ar, int n) {
//	return ar;
//}
//const double * f2(const double ar[], int n) {
//	return ar + 1;
//}
//const double * f3(const double ar[], int n) {
//	return ar + 2;
//}
