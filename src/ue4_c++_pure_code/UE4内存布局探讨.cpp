#include <iostream>
#include <string.h>

using std::cout;
using std::cin;
using std::endl;

class ClassA
{
public:
	void PrintF1()
	{
		cout << "Hello" << endl;
	}
};

class ClassB
{
public:
	
	int A;
	char B;
	short int C;
	char D;
	char E;
	float F;
	char G;

	// 初始化, 通过地址偏移的方式访问
	ClassB()
	{
		A = 123;
		B = 'B';
		C = 223;
		D = 'D';
		E = 'E';
		F = 3.33f;
		G = 'G';
	}

	void PrintF1()
	{
		cout << "Hello" << endl;
	}
};

// 这其实是使用 cast 做强转
template<typename TypeA, typename TypeB>
TypeA ACast(TypeB src)
{
	return *static_cast<TypeA*>(static_cast<void*>(&src));
}

// 利用 Union 做强转
template<typename TypeA, typename TypeB>
TypeA UnionCast(TypeB src)
{
	union
	{
		TypeA A;
		TypeB B;
	} F;
	F.B = src;
	return F.A;
}

// 这一块代码只有 32 位才能使用
//// C Declaration
////（1）参数从右向左依次压入堆栈.
////（2）由调用者恢复堆栈，称为手动清栈。
////（3）函数名自动加前导下划线。
//// __asm 调用内联的汇编代码
//// __declspec(naked) 声明为裸函数, 在使用内联汇编时要用到
//__declspec(naked) void* __cdecl CCast(...)
//{
//	__asm {
//		mov eax, dword ptr[esp+4]
//		ret
//	}
//}

// 64位不支持内联汇编
//// offset 获取操作数的偏移地址
//#define DCast(var, addr) \
//{ \
//	__asm{ \
//		mov var,offset addr \
//	} \
//}

int main()
{
	ClassA* p_a = nullptr;
	p_a->PrintF1();
	// p_a 是一个空的指针, 但是这段指令甚至能正确打印出 Hello
	// 因为 PrintF1 是存储在代码区的, 所以可以访问, 但是不能访问的是我们的变量

	// 利用内存偏移, 来获取具体的值(UE 中最常用的技巧
	ClassB b;

	cout << sizeof(b) << endl; // 20 个字节

	int* A = (int*)&b;
	cout << *A << endl;

	// 也可以通过地址去修改
	char* B = (char*)&b + sizeof(int);
	cout << *B << endl;
	*B = 'b';
	cout << *B << endl;

	// 正确的转换, 并获取对应的地址位置, 记得优先转成最通用的 char*, 在 UE 中就是 uint8*
	short int* C = (short int*)((char*)&b + sizeof(int) + 2*sizeof(char));
	cout << *C << endl;

	// 尝试获取函数位置
	void* F1 = ACast<void*>(&ClassB::PrintF1);
	cout << F1 << endl; // 打印出来得到函数指针的地址

	// 可以强转成函数类型, 然后去调用
	((void(*)())F1)();

	void* F2 = UnionCast<void*>(&ClassB::PrintF1);
	((void(*)())F2)();

	/*void* F3 = CCast(&ClassB::PrintF1);
	((void(*)())F3)();*/

	/*void* F4 = 0;
	DCast(F4, &ClassB::PrintF1);
	((void(*)())F4)();*/

	int bk = 1;
	++bk;
}

// 内存四区概念
// stack 栈 : 由编译器自动分配释放, 比如存放函数的参数, 局部变量的值
// heap 堆 : 一般由程序员分配释放, 比如动态内存申请和释放, 如果程序员不释放, 会在程序结束时由操作系统收回
// 数据区, 全局/静态区 static : 全局变量和静态变量. 初始化的放在一起, 未初始化的放在一起. 程序结束时由操作系统收回
// 数据区, 常量区 static : 字符串常量和其他常量存储位置. 程序结束时由操作系统收回
// 代码区 : 代码本体的二进制文件
