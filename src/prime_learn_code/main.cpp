#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <stack>
#include <vector>
using namespace std;

template <typename T>
void Shuffle(T *samp, int count, int nDimensions) {
	srand(time(NULL));
	for (int i = 0; i < count; ++i) {
		int other = i + rand() % (count - i);
		for (int j = 0; j < nDimensions; ++j)
			std::swap(samp[nDimensions * i + j], samp[nDimensions * other + j]);
	}
}

// Point Declarations
template <typename T>
class Point2 {
public:
	// Point2 Public Methods
	Point2() { x = y = 0; }
	Point2(T xx, T yy) : x(xx), y(yy) {}

	template <typename U>
	explicit Point2(const Point2<U> &p) {
		x = (T)p.x;
		y = (T)p.y;
	}


	Point2(const Point2<T> &p) {
		DCHECK(!p.HasNaNs());
		x = p.x;
		y = p.y;
	}

	Point2<T> &operator=(const Point2<T> &p) {
		DCHECK(!p.HasNaNs());
		x = p.x;
		y = p.y;
		return *this;
	}
	Point2<T> operator-() const { return Point2<T>(-x, -y); }
	Point2<T> &operator+=(const Point2<T> &p) {
		DCHECK(!p.HasNaNs());
		x += p.x;
		y += p.y;
		return *this;
	}
	Point2<T> operator+(const Point2<T> &p) const {
		DCHECK(!p.HasNaNs());
		return Point2<T>(x + p.x, y + p.y);
	}
	template <typename U>
	Point2<T> operator*(U f) const {
		return Point2<T>(f * x, f * y);
	}
	template <typename U>
	Point2<T> &operator*=(U f) {
		x *= f;
		y *= f;
		return *this;
	}
	template <typename U>
	Point2<T> operator/(U f) const {
		CHECK_NE(f, 0);
		Float inv = (Float)1 / f;
		return Point2<T>(inv * x, inv * y);
	}
	template <typename U>
	Point2<T> &operator/=(U f) {
		CHECK_NE(f, 0);
		Float inv = (Float)1 / f;
		x *= inv;
		y *= inv;
		return *this;
	}
	T operator[](int i) const {
		DCHECK(i >= 0 && i <= 1);
		if (i == 0) return x;
		return y;
	}

	T &operator[](int i) {
		DCHECK(i >= 0 && i <= 1);
		if (i == 0) return x;
		return y;
	}
	bool operator==(const Point2<T> &p) const { return x == p.x && y == p.y; }
	bool operator!=(const Point2<T> &p) const { return x != p.x || y != p.y; }

	// Point2 Public Data
	T x, y;
};

template <typename T>
inline T Mod(T a, T b) {
	T result = a - (a / b) * b;
	return (T)((result < 0) ? result + b : result);
}

// HaltonSampler Utility Functions
static void extendedGCD(uint64_t a, uint64_t b, int64_t *x, int64_t *y);
static uint64_t multiplicativeInverse(int64_t a, int64_t n) {
	int64_t x, y;
	extendedGCD(a, n, &x, &y);
	return Mod(x, n);
}

static void extendedGCD(uint64_t a, uint64_t b, int64_t *x, int64_t *y) {
	if (b == 0) {
		*x = 1;
		*y = 0;
		return;
	}
	int64_t d = a / b, xp, yp;
	cout << a << " " << b << endl;
	extendedGCD(b, a % b, &xp, &yp);
	*x = yp;
	*y = xp - (d * yp);
}

//
//int main()
//{
//	//Point2<float> p1(1.0, 2.0);
//	//Point2<float> p2(3.0, 4.0);
//
//	//std::swap(p1.x, p2.x);
//
//	//uint8_t a = 240;
//	//uint8_t b = (a << 4) | (a >> 4);
//	//uint8_t c = a << 4;
//
//	//int baseScales[2] = { 2,3 };
//	//int baseExponents[2] = { 0,0 };
//
//	//for (int i = 0; i < 2; ++i) {
//	//	int base = (i == 0) ? 2 : 3;
//	//	int scale = 1, exp = 0;
//	//	while (scale < 128) {
//	//		scale *= base;
//	//		++exp;
//	//	}
//	//	baseScales[i] = scale;
//	//	baseExponents[i] = exp;
//	//}
//
//	//uint64_t result = multiplicativeInverse(baseScales[1], baseScales[0]);
//
//
//	//uint64_t result2 = multiplicativeInverse(baseScales[0], baseScales[1]);
//
//	///*float a = 0x1p-64;
//	//std::cout << a << std::endl;*/
//
//
//	//uint32_t a = 6;
//	//a ^= 1;
//
//	//std::string::size_type;
//
//	//std::string str = "123456";
//	//auto find_result = str.find_first_of("24680");
//	//std::cout << find_result << std::endl;
//	//std::string &str2 = str;
//	//
//	//stack<int, vector<int>> s;
//	//s.push(4);
//	//s.push(2);
//	//s.pop();
//
//	/*auto swap_lambda = [](vector<int>& va, vector<int>& vb) {
//		swap(va, vb);
//	};
//	vector<int> va = { 1,2,3 };
//	swap_lambda(va, vector<int>());
//	int bk = 1;*/
//
//}
