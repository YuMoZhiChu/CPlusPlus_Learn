
# 标准库 vector

- vector是模板而非类型，由vector生成的类型必须包含其元素类型
- 引用不是对象，不存在包含引用的vector
- vector 的初始化分为
- - 默认初始化，不含任何元素
- - 拷贝初始化
- - 列表初始化（使用花括号
- - 值初始化
- - - 元素的类能提供初始值
- - - 提供初始的元素值
```c++
vector<string> v7{10}; // 10 个默认初始化的元素
vector<string> v8{10, "hi"}; // 10 个"hi"
```
- 在这里，列表提供的值不能作为元素的初始值，会尝试用默认值初始化类别 （兼容花括号
- range for 语句体内，不应该改变其所遍历的大小 **TODO 为什么呢**
```c++
vector<int>::size_type; // 正确
vector::size_type; // 正确
```
- size_type 也是一个跟机器相关的变量

# 迭代器
- v.end() 得到的是**尾后迭代器**，如果v是空，那么empty也是
```c++
vector<int> a;
auto it = a.end();
it++; // 运行报错
```
- end迭代器，并不实际指示某个元素，所以不能递增，或者解引用（会报错
```c++
vector<int>::const_iterator it;
string::const_iterator it2;
```
- 如果元素对象是常量，我们用使用常量迭代器，对于常量对象，begin和end也会返回 const_iterator
```c++
vector<int> a;
auto e = a.end();
auto s = a.begin();
auto delta = e-s;
```
- 这里 delta 的类型是 difference_type，机器相关的，表示两个迭代器的位置
```c++
vector<int> a;
auto e = a.end();
auto s = a.begin();
auto sun = e + s; // 报错，没有这种实现
```
 - 迭代器相加是没有意义的，也没有这类的实现

# 数组
```c++
constexpr int g_z()
{
	return 2;
}

int a[g_z()];
```
- 数组的维度，必须是一个常量表达式（可以是常量函数返回值
```c++
constexpr int g_z()
{
	return 2;
}

int a[g_z()]; // 2 个 0

int main()
{
	int b[g_z()]; // 2 个 未定义
}
```
- 和内置变量一样，如果在函数外定义，会有初始值，在函数内，是**未定义**。
- 字符数组需要多一个 \0 的位置
```c++
int *ptrs[10]; // ptrs 是含有 10个整型指针的数组
int &refs[10]; // 错误：不存在引用的数组
int (*Parray)[10]; // Parray 指向 一个含有10整型的数组
int (&Rarray)[10]; // Rarray 指向 一个含有10整型的数组
```
- 类型修饰符，应该从右往左读，括号从内向外读
```c++
string nums[] = {"1", "2", "3"};
string *p = &nums[0];
string *p2 = nums;
```
- p 和 p2 是等价的
```c++
int a[2]; // a 类型 int[2]
auto p(a); // p 类型 int*
decltype(a) a2; // a2 类型 int[2]
```
- 注意，decltype会保留数组的类型
```c++
int a[2];
auto b = begin(a); // b 类型 int*
auto b2 = cbegin(a); // b2 类型 const int*
auto delta = b2 - b; // delta 类型 ptrdiff_t
```
- begin和end是一个获取数组的迭代器的，非常好用的函数，他们做减法的差值，就是带符号的距离
```c++
int a[2] = { 0,1 };
auto e = end(a); // e 是尾后指针
auto b = e[-1]; // *b = 1
```
- 内置的下标运算符允许负数下标（标准库的不行！
- C风格字符串的函数 strcat,strcpy 等系列，请参考CPP的例子写，非常容易出错！
```c++
const char ca[] = {'h','e','l','l','o'};
const char s[] = "world";
cout << ca << endl;
```
- 结果会输出到 world 的 d 为止，因为他们在内存上是连起来的，中间是否有乱码，得看机器
```c++
char *c_s = "hello world";
string s_s(c_s);
const char *cc_s = s_s.c_str();
```
- C风格字符串和string的相互转换，注意 c_str() 返回的是 const char*

# 多维数组
```c++
#include <iostream>

using std::cout;
using std::endl;

using int_array = int[4];
typedef int int_array2[4];

int main()
{
	int ia[3][4] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11 };

	// a range for to manage the iteration
	for (const int(&p)[4] : ia)
		for (int q : p) cout << q << " ";
	cout << endl;

	// ordinary for loop using subscripts
	for (size_t i = 0; i != 3; ++i)
		for (size_t j = 0; j != 4; ++j) cout << ia[i][j] << " ";
	cout << endl;

	// using pointers.
	for (int(*p)[4] = ia; p != ia + 3; ++p)
		for (int* q = *p; q != *p + 4; ++q) cout << *q << " ";
	cout << endl;

	// using typedef.
	for (int_array2 *p = ia; p != ia + 3; ++p)
		for (int* q = *p; q != *p + 4; ++q) cout << *q << " ";
	cout << endl;

	return 0;
}
```
- 多维数组的遍历处理要点
- - 如果使用 range for，除了最内层，其他循环都应该用 引用类型
- - 使用指针时，记得用括号，区别是 int* 的数组，还是 int[] 的指针
- - typedef 和 using 的声明是等价的，但是前者需要多看理解
 
