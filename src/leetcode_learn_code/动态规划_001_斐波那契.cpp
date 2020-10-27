//#include<iostream>
//using std::cin;
//using std::cout;
//using std::endl;
//
//int get_fibo(const int& number)
//{
//	if (number == 0)
//		return 0;
//	if (number == 1)
//		return 1;
//	int fibo_sub_1 = 0, fibo_sub_2 = 1;
//	int result = 0;
//	// 压缩状态
//	for (int i = 2; i <= number; ++i)
//	{
//		result = fibo_sub_1 + fibo_sub_2;
//		fibo_sub_1 = fibo_sub_2;
//		fibo_sub_2 = result;
//	}
//	return result;
//}
//
//int main()
//{
//	int n;
//	while (cin >> n)
//	{
//		int result = get_fibo(n);
//		cout << result << endl;
//	}
//}
//
