# 第二章

第二章分三部分
- 第一部分是一些基础知识，这里做一些知识记录即可
- 第二部分是 引用，指针，const 的汇总，需要详细记录
- 第三部分是 剩下的内容，做下知识记录即可

# 第一部分 基础知识点

```c++
wchar_t,char16_t,char32_t
```
- 这些数据类型是 char 的变种，目的是满足自然语言中的字符标准需求
- long long 是 C++11 的标准
- 当给一个**无符号类型**赋一个超过其范围的值时，结果会是对总数做取模，把 -1 赋值给 8比特的 unsigned int 的结果是 255
- 当给一个**带符号类型**赋一个超过其范围的值时，结果是 **未定义的(undefined)**
```c++
unsigned u = 10;
int i = -42;
cout << u+i << endl;
// result: 4294967264
```
- 这里做计算时，-42会被转换成很大的正数
```c++
int i = 09;
```
- 这里会报错，因为 0 开头表示八进制
```c++
'a' // 字面值常量
"Hello World!" // 字符串常量，末尾有个看不见的 \0
'\x1234' // 1234是一个16进制数，表示一个字符
'\1234' // \123 表示一个字符 和 4
```
- 这里是一些字符字面值的
- **初始化不是赋值**，初始化的含义是创建变量时，赋予一个初始值
```c++
int a = 0;
int a = {0};
int a{0};
int a(0);

int a{1.1} // 列表初始化，如果存在信息丢失的风险，会报错
```
- 用花括号的被称为列表初始化
```c++
extern int ix = 1024; // 这是定义, 不是声明
int iy; // 定义
extern int iz; // 声明
```
- 使用 extern 来获得其他文件中，定义的变量
- 在函数体内 extern int x = 1，会报错。
``` c++
int reused = 1;
int main()
{
	int reused = 2;
	cout << ::reused << endl;
}
```
- 通过 **::** 来访问全局变量

# 第二部分，引用，指针 和 const 的搭配 [复合类型]

```c++
int & x;
// int 是 基本数据类型
// & 是 声明符
```

### 引用
```c++
int &refVal;
```
- 这一句话会报错，因为引用必须被初始化，它会和 **初始值绑定_bind** 在一起
```c++
int i = 0;
int &i1 = 1; // 错误, 引用只能绑对象
double d = 1.0;
int &i2 = d; // 错误，类型不匹配
```
- 引用的初始化限定：只能绑 **类型匹配的对象**
```c++
int i = 0, &ri = i;
float f = 1.0, &rf = f;
ri = 1.0;
ri = f;
rf = 0;
rf = i;
```
- 后面4行都是赋值操作，除了精度丢失，没别的问题。

### 指针

指针的两个特点

- 指针本身就是一个对象，它可以赋值和拷贝
- 指针无须在定义时赋初值。如果在定义时未初始化，那么会拥有一个不确定的值。

```c++
int *ip1, *ip2;
double dp, *dp2; // dp 是double对象，dp2 是指向double型对象的指针
```
- 指针的定义，使用声明符 *

```c++
int i = 1, &ir = i;
int *ip = &ir; // 这里的 ir 其实是 i 这个 int 对象
```
- 获取变量的地址，使用取地址符 & （这个跟声明符 & 虽然长得一样，但是意义不同
- 不存在指向引用的指针，因为引用不是对象，但是我们看到的，都是指向对象的指针

```c++
double dval;
double *pd = &dval

int *pi = pd; // 类型不匹配，错误
pi = &dval; // 类型不匹配，错误
```
- 指针的类型，都要和它所指向的对象**严格匹配**，除了两种特殊情况。

指针值（即地址）的状态，应该是下面4个之一：
- 指向一个对象
- 指向紧邻对象所占空间的下一个位置 （个人理解，类似指针的 ++ 操作
- 空指针，没有指向任何对象
- 无效指针

**空指针**
- nullptr, C++11 标准，特殊类型的字面值 - **最优**
- 0 同样是字面值
- NULL，预处理变量，会在预处理时替换成 0

**指针比较**
- 任何非 0 指针，对应的条件值都是 true
- 指针做比较是，比较的是他们存放的 地址值
- **void*** 从视角来看就是一块内存空间，除非做类型转换。

**复合类型**
```c++
int i = 1024;
int *ip = &i;
int **ipp = &ip; // ipp 是一个指向指针的指针

int i = 1024;
int *p = &i;
int *&r = p; // r 是一个对指针p的引用
```
- 学会 从右往左 的阅读，距离变量名越近，声明符的影响越直接。*&r 说明r是一个引用。再说明引用的是一个指针。

### const 限定符
**初始化和const**
```c++
const int k; // 错误，必须初始化
int i = 42;
const int ci = i;
ci = 43; // 错误，ci 不能写值
```
- 必须初始化
- 不能修改

**多文件情况**
- 多文件出现同名的const变量时，等同于在不同文件中分别定义了独立的变量。
```c++
extern const int buffSize = 32;
---
extern const int buffSize;
```
- 解决方案，不管是定义还是声明，都加上 extern

**常量引用**
```c++
float i = 1.0;
const int &r = i; // 正确
const int &r2 = 123; // 正确
```
- 这两语句是成立的，因为会绑定一个临时值，这个临时值因为 float 可以转换为 int，也可以直接创建出来。
```c++
string a = "123";
const int &r = a; // 错误
```
- 这一语句不成立，因为 string 不能转换为 int

**指向常量的指针**
```c++
const double *pi;
double v = 1.0f;
pi = &v; // 正确，指向常量的指针 可以指向一个 非常量
```
- **特殊情况1** 一个指向常量的指针，可以指向同类型的 非常量

**const指针**
```c++
int *const ip; // 错误，const指针必须初始化
int a = 1, *const ip = &a;
*ip = 2; // 正确，因为指向的内容不是 const 所以可以改
int b = 2;
const int *const ip2 = &b;
*ip2 = 3; // 错误，因为指向的也是 const 的内容
```
- const 指针必须初始化，其实跟 const 内容一致
- 如果指向的内容不是 const，就可以修改

**顶层const**

顶层const更像是一个定义，它把 const 分为两种
- 顶层const： 变量本身是 const
- 底层const：变量指向的内容，或者引用的内容 是const

所以我们记住，底层const有：
- const 引用（const int * p，不是在 *后面的 const
- const 指针

**执行对象的拷贝操作时，顶层const不受影响**
```c++
int i = 1, *ip, *const ip2 = &i;
const int i2 = 2;
i = i2; // 正确 顶层const不受影响
i2 = i; // 错误 const不能修改
ip = ip2; // 正确 顶层const不受影响
ip2 = ip; // 错误 const不能修改
```
- 一定要注意，不受影响，但是const本身不能修改

**执行对象的拷贝操作是，底层const不能忽略**
```c++
int i = 1, *ip = &i, &ir = i;
const int ic = 2, *ipc = &ic, &irc = ic;
ipc = ip; // 正确，因为 const int* 可以指向 int*
ip = ipc; // 错误，因为底层const不匹配
// 引用也是同理
const int &irc2 = ir; // 正确，因为 int 可以转换为 const int
ir = irc; // 正确，这里的 irc，是引用，所以就是ic，ic是顶层const
irc = ic; // 错误，const不能修改
ic = irc; // 错误，const不能修改
```
需要满足2个条件之一即可：
- 必须有相同的底层const
- 可以转换，一般来说，非常量const可以转换成常量const，这里指的是 const int* 可以指向 int*，其实就是指针的可以不遵守严格匹配的第一个**特殊点**

**constexpr和常量表达式**

常量表达式是指不会改变，并且在编译过程就能得到计算结果
```c++
const int max_files = 20; // 是常量表达式
const int limit = max_files + 1; // 是常量表达式
int staff_size = 27; // 不是常量表达式
const int sz = get_size(); // 不是常量表达式，是常量，但是要运行才能获取
```
- c++11 规定，允许将变量声明为 **constexpr** 类型，让编译器来检测是否是常量表达式
```c++
constexpr int mf = 20;
constexpr int limit = mf + 1;
constexpr int sz = size(); // 如果size不是 constexpr 函数，就会报错
```
- constexpr 对于确定的表达一个常量来说，会比const更优，尽量使用。
- 只有字面值类型才能使用 constexpr，自定义类，std库都不行。（指针和引用尽管可以，但他们只能是 nullptr 或者存储于某个固定地址中的对象
- constexpr 指针，一定是常量指针
```
const int *p = nullptr; // 指向常量的指针
constexpr int *p = nullptr; // 指向int的 常量指针

// ij在函数体外时成立
int j = 0;
constexpr int i = 1;
constexpr int *p = &j;
constexpr const int *q = &i;
// 复习一波底层 const
constexpr int *p = &i; // 错误，底层const不一致，且不能转换
constexpr const int *q = &j; // 正确 const* 可以指向 非const的对应类型
```

### 处理类型

**typedef**

typedef 用于指定类型的别名，但是它有一点会跟我们的主观印象里面，直接替换是不一样的：
```c++
typedef char *pstring;
const pstring cstr = 0; // cstr 的类型是 char *const --- 指向char 的 常量指针
const char *const_char_p = 0; // const_char_p 的类型是 const char*
const pstring *ps = 0; // ps 的类型是 char *const * --- 指向char 的 常量指针 的指针

using ustring = char *;
const ustring ucstr = 0; // ucstr 的类型是 char *const
const ustring *ucstr_p = 0; // ucstr_p 的类型是 char *const *
```
- 这么理解，const pstring 中，const 修饰的是 pstring，而 pstring 是一个指针

**auto**

auto会去推断数据的类型，所以
- auto定义的变量一定有初始值
- 对于基本数据类型，会做两点
- - 忽略 引用
- - 忽略 顶层const
- - 如果想要引用，顶层const，在 auto 附近加即可
```c++
const int i = 42;
auto j = i; // j: int
const auto &k = i; // k: const int&
auto *p = &i; // i: 这里的 &i 其实可以看做是引用，这里是底层const，或者是理解成，一个指向它的指针，那必须const
// p: const int*
const auto j2 = i; &k2 = i// j2: const int, k2: const int&
```

**decltype**

decltype 支持两种输入
- 表达式，表达式不会计算，但会得到它的类型
- 变量，**保留**顶层const和引用（引用都是作为对象的别名出现，只有在这里是例外
```c++
int i = 42, *p = &i;
decltype(*p) a; // 出错，因为这里的结果是 int&
decltype((i)) b; // 出错，因为 双层括号 的结果 永远是引用
```

# 第三部分

```
#define
```
- 预处理变量 无视 C++语言中关于作用域的规则
