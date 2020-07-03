#include <iostream>
#include <vector>
#include <cstdlib>
#include <time.h>
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


int main()
{
	Point2<float> p1(1.0, 2.0);
	Point2<float> p2(3.0, 4.0);

	std::swap(p1.x, p2.x);

}
