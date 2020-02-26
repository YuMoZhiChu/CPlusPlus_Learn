//#include <iostream>
//#include <memory>
//#include <string>
//using namespace std;
//
//class Report
//{
//public:
//	string str;
//	Report(const string& s) :str(s)
//	{
//		cout << "Report Object Create" << endl;
//	}
//	~Report()
//	{
//		cout << "Report Object Delete" << endl;
//	}
//	void comment()
//	{
//		cout << str << endl;
//	}
//};
//
//void throw_test() noexcept
//{
//	throw 1;
//}
//
//void normal_ptr_1()
//{
//	double * pd = new double; // 为pd和一个double值分配存储空间, 保存地址
//	*pd = 1.0;                // 将值复制到动态内存中
//	return;                   // 删除pd, 动态内存保留, 值保留
//}
//
//void auto_ptr_1()
//{
//	auto_ptr<double> ap(new double); // 为ap和一个double值分配存储空间, 保存地址
//	*ap = 1.0;                       // 将值复制到动态内存中
//	return;                          // 删除pd, ap的析构函数释放动态内存
//}
//
//unique_ptr<string> demo(const char* s)
//{
//	unique_ptr<string> temp(new string(s));
//	return temp;
//}
//
//unique_ptr<int> make_int(int n)
//{
//	return unique_ptr<int>(new int(n));
//}
//
//int main()
//{
//	// 有内存泄露的写法
//	/*normal_ptr_1();
//	_CrtDumpMemoryLeaks();*/
//	// 使用智能指针, 没有内存泄露的写法
//	/*auto_ptr_1();
//	_CrtDumpMemoryLeaks();*/
//
//	//{
//	//	Report* ptr = new Report("using auto_ptr");
//	//	auto_ptr<Report> ps = ptr; // 不允许隐式类型转换
//	//	auto_ptr<Report> ps(ptr);  // 正确写法
//	//	ps->comment();
//	//}
//
//	//{
//	//	auto_ptr<Report> ps(new Report("using auto_ptr"));
//	//	ps->comment();
//	//}
//
//	//{
//	//	shared_ptr<Report> ps(new Report("using shared_ptr"));
//	//	ps->comment();
//	//}
//
//	//{
//	//	unique_ptr<Report> ps(new Report("using unique_ptr"));
//	//	ps->comment();
//	//}
//
//	/*{
//		string teststr("teststr");
//		auto_ptr<string> ps(&teststr);
//	}*/
//
//	//{
//	//	auto_ptr<string> film[2] = 
//	//	{
//	//		auto_ptr<string> (new string("1")),
//	//		auto_ptr<string>(new string("2"))
//	//	};
//	//	auto_ptr<string> ps;
//	//	ps = film[1];
//	//	// film[1].reset();
//	//	
//	//	// cout << *film[1] << endl; // 这一句会出错
//	//	// 在语句 ps = film[1] 中, film[1] 的所有权转让给了 ps， 其实跟 film[1].reset() 本质上的效果一样
//	//	// 虽然还可以用来访问，但是因为里面是空的，所以打印会出错
//
//	//	// 但是我们对它重新赋值, 相当于抢了一个新的 auto_ptr 的所有权
//	//	film[1] = (auto_ptr<string>)(new string("3"));
//	//	cout << *film[1] << endl;
// //	}
//
//	// shared_ptr 因为使用的是引用计数机制, 所以就没有问题
//	//{
//	//	shared_ptr<string> film[2] =
//	//	{
//	//		shared_ptr<string>(new string("1")),
//	//		shared_ptr<string>(new string("2"))
//	//	};
//	//	shared_ptr<string> ps;
//	//	ps = film[1];
//
//	//	cout << *film[1] << endl;
//	//	cout << ps.use_count() << " " << ps.unique() << endl; 
//	//	cout << film[1].use_count() << " " << film[1].unique() << endl;
//	//	cout << film[0].use_count() << " " << film[0].unique() << endl;
//	//}
//
//	/*{
//		unique_ptr<string> film[2] = 
//		{
//			unique_ptr<string> (new string("1")),
//			unique_ptr<string>(new string("2"))
//		};
//		unique_ptr<string> ps;
//		ps = film[1];
// 	}*/
//
//	//// unique 支持右值赋值
//	//// 因为右值很快能被销毁
//	//{
//	//	unique_ptr<string> ps;
//	//	ps = demo("demo");
//	//	cout << *ps << endl;
//
//	//	unique_ptr<string> ps2(new string("123"));
//	//	cout << *ps2 << endl;
//	//}
//
//	//// unique_ptr 还支持 new[] 操作, 对应的代码中有 delete[] 操作
//	//{
//	//	unique_ptr<double[]> pdouble(new double[4] {1,2,3,4});
//	//	cout << pdouble[3] << endl;
//
//	//	// auto_ptr<double[]> auto_p(new double[4]{ 1,2,3,4 }); // 这样写直接会编译不通过
//
//	//	double* double_array = new double[4]{ 100,200,300,400 };
//	//	auto_ptr<double> auto_p = auto_ptr<double>(double_array); // 虽然这么强行转是可行的
//	//	// cout << auto_p[0] << endl; 1. 没办法作为数组使用, 这里其实就相当于一个 double 的指针
//	//	// delete[] double_array; // 因为 double_array 的其他内容需要删除, 要么重复删除, 要么内存泄露
//	//	// 但是 new[] 似乎 _Crt 测不出来
//	//}
//
//	//{
//	//	unique_ptr<int> pup(make_int(123));
//	//	//shared_ptr<int> pup2(pup); 这一句不能通过, 因为 shared_ptr 不支持该赋值操作
//	//	shared_ptr<int> pup3(make_int(123));
//	//}
//}
//
//
