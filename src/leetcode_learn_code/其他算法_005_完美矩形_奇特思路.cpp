// 力扣
// https://leetcode-cn.com/problems/perfect-rectangle/
// 学习
// https://labuladong.gitbook.io/algo/suan-fa-si-wei-xi-lie/3.3-qi-ta-suan-fa-pian/wan-mei-ju-xing
// 线段树思路
// https://www.cnblogs.com/xenny/p/9801703.html
// 1. 算出最小的 左下角 和 最大的右上角
// 求奇数次出现的点

#include<vector>
using std::vector;

#include<unordered_set>
using std::unordered_set;


struct Point
{
	Point(int _x, int _y) :x(_x), y(_y) {}
	int x;
	int y;
};

struct Point_Hash
{
	size_t operator()(const Point &p) const
	{
		// 这里 x,y 权重要设置成不一样
		return std::hash<int>()(p.x) ^ std::hash<int>()(p.y) << 1;
	}
};

struct Point_equal
{
	bool operator()(const Point &p1, const Point &p2) const noexcept
	{
		return p1.x == p2.x && p1.y == p2.y;
	}
};

class Solution {
	int min_x, min_y, max_x, max_y;
	int area_sum; // 面积总和

public:

	bool isRectangleCover(vector<vector<int>>& rectangles) {
		// 初始化
		min_x = min_y = INT_MAX;
		max_x = max_y = INT_MIN;
		area_sum = 0;

		unordered_set<Point, Point_Hash, Point_equal> point_set;

		for (auto rectangle : rectangles)
		{
			area_sum += (rectangle[2] - rectangle[0]) * (rectangle[3] - rectangle[1]);
			min_x = min_x < rectangle[0] ? min_x : rectangle[0];
			min_y = min_y < rectangle[1] ? min_y : rectangle[1];
			max_x = max_x > rectangle[2] ? max_x : rectangle[2];
			max_y = max_y > rectangle[3] ? max_y : rectangle[3];

			// 只存奇数点的思路
			for (int i = 0; i < 4; ++i)
			{
				int p_x = i % 2 == 0 ? rectangle[0] : rectangle[2];
				int p_y = i < 2 ? rectangle[1] : rectangle[3];
				Point p(p_x, p_y);
				if (point_set.count(p))
				{
					point_set.erase(p);
				}
				else {
					point_set.insert(p);
				}
			}

		}
		// 如果面积都不相等, -> 有空格, 那么就 false
		if ((max_y - min_y) * (max_x - min_x) != area_sum) return false;
		// 如果超出4个数, 也是错误的
		if (point_set.size() != 4) return false;
		for (int i = 0; i < 4; ++i)
		{
			int p_x = i % 2 == 0 ? min_x : max_x;
			int p_y = i < 2 ? min_y : max_y;
			Point p(p_x, p_y);
			if (!point_set.count(p)) return false;
		}

		return true;
	}
};