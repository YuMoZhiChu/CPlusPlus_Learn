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
//		// 使用函数指针对 number 做筛选
//		cout << count_if(numbers.begin(), numbers.end(), f_mod3_0) << endl;
//		// 使用 lambda 表达是
//		cout << count_if(numbers.begin(), numbers.end(),
//			[](int x) {return x % 3 == 0; })
//			<< endl;
//		// 在这里, 因为只有一行语句, 所以编辑器用 decltype() 来推断出返回值的类型 不然要写成 []->bool(){} 的形势
//	}
//	{
//		// lambda 可以直接存储起来
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
