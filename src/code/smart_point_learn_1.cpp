#include <iostream>
#include <memory>
#include <string>
using namespace std;

class Report
{
public:
	string str;
	Report(const string& s) :str(s)
	{
		cout << "Report Object Create" << endl;
	}
	~Report()
	{
		cout << "Report Object Delete" << endl;
	}
	void comment()
	{
		cout << str << endl;
	}
};

void throw_test() noexcept
{
	throw 1;
}

void normal_ptr_1()
{
	double * pd = new double; // 为pd和一个double值分配存储空间, 保存地址
	*pd = 1.0;                // 将值复制到动态内存中
	return;                   // 删除pd, 动态内存保留, 值保留
}

void auto_ptr_1()
{
	auto_ptr<double> ap(new double); // 为ap和一个double值分配存储空间, 保存地址
	*ap = 1.0;                       // 将值复制到动态内存中
	return;                          // 删除pd, ap的析构函数释放动态内存
}

int main()
{
	// 有内存泄露的写法
	/*normal_ptr_1();
	_CrtDumpMemoryLeaks();*/
	// 使用智能指针, 没有内存泄露的写法
	/*auto_ptr_1();
	_CrtDumpMemoryLeaks();*/

	//{
	//	Report* ptr = new Report("using auto_ptr");
	//	auto_ptr<Report> ps = ptr; // 不允许隐式类型转换
	//	auto_ptr<Report> ps(ptr);  // 正确写法
	//	ps->comment();
	//}

	//{
	//	auto_ptr<Report> ps(new Report("using auto_ptr"));
	//	ps->comment();
	//}

	//{
	//	shared_ptr<Report> ps(new Report("using shared_ptr"));
	//	ps->comment();
	//}

	//{
	//	unique_ptr<Report> ps(new Report("using unique_ptr"));
	//	ps->comment();
	//}

	/*{
		string teststr("teststr");
		auto_ptr<string> ps(&teststr);
	}*/

	{
		auto_ptr<string> film[2] = 
		{
			auto_ptr<string> (new string("1")),
			auto_ptr<string>(new string("2"))
		};
		auto_ptr<string> ps;
		ps = film[1];
		
		// cout << *film[1] << endl; // 这一句会出错
		// 在语句 ps = film[1] 中, film[1] 的所有权转让给了 ps, 虽然还可以用来访问，但是因为里面是空的，所以打印会出错

		// 但是我们对它重新赋值, 在
		film[1] = (auto_ptr<string>)(new string("3"));
		cout << *film[1] << endl;
 	}

}


