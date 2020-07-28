# IO类
整个IO类比较简单，这里做一下知识点要记

```c++
#include<iostream>

istream, wistream;
ostream, wostream;
iostream, wiostream;

#include<fstream>

ifstream, wifstream;
ofstream, wofstream;
fstream, wfstream;

#include<sstream>

istringstream, wistringstream;
ostringstream, wostringstream;
stringstream, wstringstream;

```
- IO 类都在这里，分别是 流，文件，字符串流的 IO，w开头的是 宽字符的处理。
- IO 操作通常用**引用**方式传递和返回流，因为读写IO会改变其状态，所以不能用 const
```c++
strm::iostate; // strm 是某种 IO 类型，iostate 是一种机器相关的类型
// 下面是 xiobase 文件中的定义
static constexpr _Iostate goodbit = (_Iostate)0x0;
static constexpr _Iostate eofbit = (_Iostate)0x1;
static constexpr _Iostate failbit = (_Iostate)0x2;
static constexpr _Iostate badbit = (_Iostate)0x4;
```
- 任何一种IO，都有这四种状态标志，来记录当前状态。
```
cin.tie(&cout); // 默认 cin
cin.tie(); // 不和其他的流
```
- 正常来说，一个输入流可以绑定一个输出流，或者空，一个输出流可以被多个输入流绑定，**TODO**，实用场景不知
- 当一个 fstream 对象（文件stream）被销毁时，close 会自动被调用。
```c++
in
out
app
ate
trunc
binary
```
- 保留 ofstream 打开的文件中已有数据的方法，是显示指定 in 或者 app，**TODO**，具体使用场景

# 泛型算法



