# 第三章

### using 声明

这里的using声明是指
```c++
#include <iostream>
using std::cin; // 这个被称为声明
```
- 每个名字都需要独立的using
- 头文件不应包含using（会引起冲突

**using 指示**
```c++
using namespace std;
```
- 该命名空间中所有成员的名字可见
- using指示，在使用了成员才可能发生冲突，非常不可查

### string

**直接初始化和拷贝初始化**
```
class A {};
A a = A(); // 直接初始化
A b = a; // 拷贝初始化
```
- 直接初始化是优于拷贝的，因为拷贝会有一个临时对象，然后再复制的过程
- 看上去是拷贝初始化的内容（用=初始化），如果给出了公有的拷贝构造函数，编译器有可能优化成直接初始化，[详细链接](https://blog.csdn.net/ljianhui/article/details/9245661)

```c++
string s;
cin >> s;
```
- s 的读取规则是，忽略开头的空白，读到下一处空白为止

```c++
string line;
getline(cin, line);
```
- getline 的读取规则是，读取一行，直到读到换行符

**string::size_type**
```c++
auto len = len.size(); // len 的类型是 string::size_type
```
- 为什么不是 int 或者 usigned int 呢，因为这里要做到与 机器无关
- 为了避免一个负数的int导致 len.size() < n 判断成立，对于size的属性，不去使用 int

**使用C++版本的C标准库头文件**
- C++为了兼容C，把一些 name.h 的 C 文件命名为 cname，所以尽量使用 cname 形式的库文件

**range for**
```
for (declaration : expression)
	statement
```
这是 c++11 的特性，可以用 range 进行遍历
```c++
string s("hello world");
for (auto &c : s)
	c = toupper(c);
```
- declaration 中可以加修饰符，比如引用，来遍历修改
