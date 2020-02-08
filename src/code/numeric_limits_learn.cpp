#include <limits>
#include <cstddef>
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <iostream>
#include <type_traits>
#include <algorithm>

template<class T>
typename std::enable_if<!std::numeric_limits<T>::is_integer, bool>::type
almost_equal(T x, T y, int ulp)
{
	// ???? 这里的 epsilon 为什么要乘上 std::abs(x + y)
	// the machine epsilon has to be scaled to the magnitude of the values used
	// and multiplied by the desired precision in ULPs (units in the last place)
	return std::abs(x - y) <= std::numeric_limits<T>::epsilon() * std::abs(x + y) * ulp
		// unless the result is subnormal
		|| std::abs(x - y) < std::numeric_limits<T>::min();
}

int main()
{
	//// 输出最大有限值
	//std::cout << "short: " << std::dec << std::numeric_limits<short>::max()
	//	<< " or " << std::hex << std::showbase << std::numeric_limits<short>::max() << '\n'
	//	<< "int: " << std::dec << std::numeric_limits<int>::max()
	//	<< " or " << std::hex << std::numeric_limits<int>::max() << '\n' << std::dec
	//	<< "streamsize: " << std::dec << std::numeric_limits<std::streamsize>::max()
	//	<< " or " << std::hex << std::numeric_limits<std::streamsize>::max() << '\n'
	//	<< "size_t: " << std::dec << std::numeric_limits<std::size_t>::max()
	//	<< " or " << std::hex << std::numeric_limits<std::size_t>::max() << '\n'
	//	<< "float: " << std::numeric_limits<float>::max()
	//	<< " or " << std::hexfloat << std::numeric_limits<float>::max() << '\n'
	//	<< "double: " << std::defaultfloat << std::numeric_limits<double>::max()
	//	<< " or " << std::hexfloat << std::numeric_limits<double>::max() << '\n';

	//// 输出无穷大值
	//std::cout 
	//	<< "float " << std::defaultfloat << std::numeric_limits<float>::infinity() << '\n'
	//	<< "double: " << std::defaultfloat << std::numeric_limits<double>::infinity() << '\n'
	//	<< "long double: " << std::defaultfloat << std::numeric_limits<long double>::infinity() << '\n';


	double d1 = 0.2;
	double d2 = 1 / std::sqrt(5) / std::sqrt(5);
	std::cout << std::fixed << std::setprecision(20)
		<< "d1=" << d1 << "\nd2=" << d2 << '\n';

	if (d1 == d2)
		std::cout << "d1 == d2\n";
	else
		std::cout << "d1 != d2\n";

	if (almost_equal(d1, d2, 2))
		std::cout << "d1 almost equals d2\n";
	else
		std::cout << "d1 does not almost equal d2\n";
}