#include<iostream>

using namespace std;

double refcube(double & ra)
{
	ra = ra * ra;
	return ra;
}

double refcube_const_param(const double & ra)
{
	return ra * ra;
}

struct Vector
{
	int x;
	int y;
	Vector() { x = y = 0; }
	explicit Vector(const Vector& vector)
	{
		x = vector.x;
		y = vector.y;
	}

	// 推荐的做法
	Vector & operator+=(const Vector& vector)
	{
		// 在这里 *this 和 引用是等价的
		// 多用于 += -= 等处理
		x += vector.x;
		y += vector.y;
		return *this;
	}
};

// 返回结构体引用的做法
Vector & clone(const Vector& vector)
{
	Vector new_vector(vector);
	cout << "new vector address : " << &new_vector << endl;
	// 不推荐使用这种做法, 相当于返回了 临时变量的引用， 同样应该避免返回临时变量的指针
	return new_vector;
}

int main()
{
	double x = 1.0;
	// refcube(x + 3.0); // 无法如此调用, 因为如果实参和引用参数不匹配时, C++会生成临时变量
	// 非常量引用的初始值 必须为 非常量左值

	// 1. 左值的分类
	// 左值分为 变量左值 和 常量左值, 左值是可以取得到地址的变量,可被引用的数据对象,即 &(左值表达式) 通过
	// 变量左值 例如, 变量,数组元素，结构成员，引用，解除引用的指针等等
	// 常量左值 即为 const 变量
	// 引用的分类, 引用分为 左值引用 和 右值引用, 这里只看左值引用
	// 左值引用分 变量左值引用 常量左值引用 : TypeName & 和 const TypeName &
	// 引用的修饰 TypeName & const 后面的 const 设定无效, 等价于 TypeName &

	int int_var = 1;
	const double double_const_var = 1.0;
	// double & ra_ref = ra_const_var; // 变量左值引用的初始化, 只能引用, 变量左值, 这里编译不通过
	// double & ra_ref = double_const_var; // 这样不可以， 类型不一样
	// double & ra_ref = int_var; // 这里类型不一致, 也不可以
	// double & ra_ref = (double)int_var; // 这里也不行, 因为 (double)int_var 不是左值, 而是右值
	double int_var_conver_to_double = (double)int_var;
	double & ra_ref = int_var_conver_to_double; // 这相当于一般的引用使用

	// const 引用机制, 在赋值时, 如果不匹配，在下面2种情况下，会生成临时变量
	// 0. const 引用 支持引用 变量左值 常量左值 变量右值 常量右值
	// 1. 类型正确, 但不是左值
	// 2. 类型不正确, 但可以转换为正确的类型
	double side = 3.0;
	double * pd = &side;
	double & rd = side;
	long edge = 5L;
	double lens[4] = { 2.0, 5.0, 10.0, 12.0 };
	// 等价于
	double c1 = refcube_const_param(side);
	double c2 = refcube_const_param(lens[2]);
	double c3 = refcube_const_param(rd);
	double c4 = refcube_const_param(*pd);
	// side, lens[2], rd, *pd 都是有名称的, double类型的变量, 因此直接创建引用
	const double & c_const_ref_1 = side;
	const double & c_const_ref_2 = lens[2];
	const double & c_const_ref_3 = rd;
	const double & c_const_ref_4 = *pd;

	// 这里生成了临时变量
	// 对于使用const引用的C++函数, 如果实参不匹配, 类似于值传递，为了确保原始数据不被修改，使用临时变量来存储值
	double c5 = refcube_const_param(edge); // 类型不正确, 但可以转换
	double c6 = refcube_const_param(7.0); // 类型正确, 但不是左值
	double c7 = refcube_const_param(side+10.0); // 类型正确, 但不是左值
	const double & c_const_ref_5 = edge;
	const double & c_const_ref_6 = 7.0;
	const double & c_const_ref_7 = side + 10.0;

	// 总结
	// 1. 使用const, 可以利用const来防止数据的修改
	// 2. 使用const引用能处理const和非const实参，否则引用只能接受非const数据
	// 3. 使用const引用能使函数正确生成并使用临时变量

	// 引用用于结构体
	Vector vector;
	Vector & vector_clone_ref = clone(vector);
	cout << "vector address: " << &vector << "  vector_clone address: " << &vector_clone_ref << endl;

	vector += Vector();
	cout << "vector address: " << &vector << "  vector_add address: " << &vector << endl;
}
