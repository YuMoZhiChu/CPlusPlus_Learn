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
	double * pd = new double; // Ϊpd��һ��doubleֵ����洢�ռ�, �����ַ
	*pd = 1.0;                // ��ֵ���Ƶ���̬�ڴ���
	return;                   // ɾ��pd, ��̬�ڴ汣��, ֵ����
}

void auto_ptr_1()
{
	auto_ptr<double> ap(new double); // Ϊap��һ��doubleֵ����洢�ռ�, �����ַ
	*ap = 1.0;                       // ��ֵ���Ƶ���̬�ڴ���
	return;                          // ɾ��pd, ap�����������ͷŶ�̬�ڴ�
}

int main()
{
	// ���ڴ�й¶��д��
	/*normal_ptr_1();
	_CrtDumpMemoryLeaks();*/
	// ʹ������ָ��, û���ڴ�й¶��д��
	/*auto_ptr_1();
	_CrtDumpMemoryLeaks();*/

	//{
	//	Report* ptr = new Report("using auto_ptr");
	//	auto_ptr<Report> ps = ptr; // ��������ʽ����ת��
	//	auto_ptr<Report> ps(ptr);  // ��ȷд��
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
		
		// cout << *film[1] << endl; // ��һ������
		// ����� ps = film[1] ��, film[1] ������Ȩת�ø��� ps, ��Ȼ�������������ʣ�������Ϊ�����ǿյģ����Դ�ӡ�����

		// �������Ƕ������¸�ֵ, ��
		film[1] = (auto_ptr<string>)(new string("3"));
		cout << *film[1] << endl;
 	}

}


