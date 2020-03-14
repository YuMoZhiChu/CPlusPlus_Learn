#include<iostream>
#include<utility>
using namespace std;

class Useless
{
public:
	int n; // 
	char * pc; //
	static int ct;
	void ShowObject() const;

	Useless();
	explicit Useless(int k);
	Useless(int k, char ch);
	Useless(const Useless & f); // ����Ŀ������캯��
	Useless(Useless && f); // �ƶ����캯��
	~Useless();
	Useless operator+(const Useless & f) const;
	void ShowData() const;

	// �������ø�ֵ �� �ƶ���ֵ
	Useless & operator=(const Useless & f);
	Useless & operator=(Useless && f);

};

int Useless::ct = 0;

Useless::Useless()
{
	++ct;
	n = 0;
	pc = nullptr;
	cout << "ʹ��  ��ʼ  �������ĵ���, ��ǰ Useless �ĸ��� " << ct << endl;
	ShowObject();
}

Useless::Useless(int k): n(k)
{
	++ct;
	cout << "ʹ��  int  �������ĵ���, ��ǰ Useless �ĸ��� " << ct << endl;
	pc = new char[n];
	ShowObject();
}

Useless::Useless(int k, char ch) : n(k)
{
	++ct;
	cout << "ʹ��  int,char  �������ĵ���, ��ǰ Useless �ĸ��� " << ct << endl;
	pc = new char[n];
	for (int i = 0; i < n; ++i)
		pc[i] = ch;
	ShowObject();
}

Useless::Useless(const Useless & f) : n(f.n)
{
	++ct;
	cout << "ʹ��  ����  �������ĵ���, ��ǰ Useless �ĸ��� " << ct << endl;
	pc = new char[n];
	for (int i = 0; i < n; ++i)
		pc[i] = f.pc[i];
	ShowObject();
}

Useless::Useless(Useless && f) : n(f.n)
{
	++ct;
	cout << "ʹ��  ��ֵ  �������ĵ���, ��ǰ Useless �ĸ��� " << ct << endl;
	pc = f.pc;
	f.pc = nullptr;
	f.n = 0;
	ShowObject();
}

Useless::~Useless()
{
	cout << "������������, ʣ��������� " << --ct << endl;
	cout << "ɾ������: " << endl;
	ShowObject();
	delete[] pc;
}

Useless Useless::operator+(const Useless & f) const
{
	cout << " ���붨��� + ����" << endl;
	Useless temp = Useless(n + f.n);
	for (int i = 0; i < n; i++)
		temp.pc[i] = pc[i];
	for (int i = n; i < temp.n; i++)
		temp.pc[i] = f.pc[i - n];
	cout << "temp object:\n";
	cout << " �뿪����� + ����" << endl;
	return temp;
}

void Useless::ShowObject() const
{
	cout << "�ж��ٸ�Ԫ��" << n;
	cout << " ���ݵ�ַ  " << (void*)pc << endl;
}

void Useless::ShowData() const
{
	if (n == 0)
		cout << "�յ� object";
	else
		for (int i = 0; i < n; i++)
			cout << pc[i];
	cout << endl;
}

Useless & Useless::operator=(const Useless & f)
{
	cout << "=========�������ø�ֵ����" << endl;
	if (this == &f)
		return *this;
	delete[]pc;
	n = f.n;
	pc = new char[n];
	for (int i = 0; i < n; i++)
		pc[i] = f.pc[i];
	return *this;
}

Useless & Useless::operator=(Useless && f)
{
	cout << "=========�����ƶ���ֵ����" << endl;
	if (this == &f)
		return *this;
	delete[]pc;
	n = f.n;
	pc = f.pc;
	f.pc = nullptr;
	f.n = 0;
	return *this;
}

int main()
{
	//{
	//	Useless one(10, 'x');
	//	Useless two = one;      // ������õ��� �������캯�� Ҳ��������
	//	Useless three(20, 'o');
	//	Useless four(one + three); // 1. ���� operator+ 2. �����ķ���ֵ��Ϊ��ֵ ������ֵ���캯��

	//	// ������� C++98 �Ķ�����, ���߰� �ƶ�����ע��
	//	// Useless four(one + three) �ĵڶ��� �������ù��캯�� ��Ϊ const ���û���, ������Ͳ�ƥ��, �ͻ����� ��ʱ����
	//	// �ھɰ�� C++98 ��, ������ֶ�һ�� Useless ����ʱ����, ����Ӧ���Ǳ༭����æ�Ż���

	//	cout << "              " << endl;

	//}
	//{
	//	Useless one(10, 'x');
	//	Useless two;
	//	two = one; // ���ø�ֵ
	//	Useless three;
	//	three = one + two; // �ƶ���ֵ
	//}
	{
		Useless one(10, 'x');
		Useless two;
		two = one; // ���ø�ֵ
		one.ShowData();
		two = move(one); // ǿ���ƶ���ֵ
		// ���û�ж��� �ƶ���ֵ ����, ��������ø�ֵ ��Ϊ const ���û���, ������Ͳ�ƥ��, �ͻ����� ��ʱ����
		one.ShowData();
	}
}
