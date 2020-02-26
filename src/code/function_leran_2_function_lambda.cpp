//#include<iostream>
//#include<vector>
//#include<algorithm>
//#include<cmath>
//using namespace std;
//
//bool f_mod3_0(int x) { return x % 3 == 0; }
//
//int main()
//{
//	{
//		vector<int> numbers(100);
//		srand(0);
//		generate(numbers.begin(), numbers.end(), rand);
//
//		// ʹ�ú���ָ��� number ��ɸѡ
//		cout << count_if(numbers.begin(), numbers.end(), f_mod3_0) << endl;
//		// ʹ�� lambda �����
//		cout << count_if(numbers.begin(), numbers.end(),
//			[](int x) {return x % 3 == 0; })
//			<< endl;
//		// ������, ��Ϊֻ��һ�����, ���Ա༭���� decltype() ���ƶϳ�����ֵ������ ��ȻҪд�� []->bool(){} ������
//	}
//	{
//		// lambda ����ֱ�Ӵ洢����
//		auto my_mod_lambda = [](int x) {return x % 3 == 0; };
//
//		vector<int> numbers(100);
//		srand(0);
//		generate(numbers.begin(), numbers.end(), rand);
//		cout << count_if(numbers.begin(), numbers.end(), my_mod_lambda) << endl;
//
//
//
//	}
//}
