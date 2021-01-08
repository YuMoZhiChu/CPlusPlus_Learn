// 力扣
// https://leetcode-cn.com/problems/perfect-rectangle/
// 学习
// https://labuladong.gitbook.io/algo/suan-fa-si-wei-xi-lie/3.3-qi-ta-suan-fa-pian/wan-mei-ju-xing
// 线段树思路
// https://www.cnblogs.com/xenny/p/9801703.html
// 1. 算出最小的 左下角 和 最大的右上角
// 2. 把二维的转成一维的数据，用线段树，看看有没有相交的，有相交的直接false
// 线段树不行, 我们改成 2D 的田块树, 面积树的方法 gg
// 3. 如果没有相交的，那比较累加面积和，和最小最大的面积和，看有没有空缺的
// 这是一个超时的失败的思路, 单纯用面积树不行

#include<vector>
using std::vector;

#include<algorithm>
using std::max;
using std::min;

class Solution {
	int min_x, min_y, max_x, max_y;
	int area_sum; // 面积总和
	int per_row;

	// 2D树节点, 面积树节点
	struct CNode
	{
		CNode(int _min_x, int _min_y, int _max_x, int _max_y) :min_x(_min_x), min_y(_min_y), max_x(_max_x), max_y(_max_y)
		{
			is_paint = false;
			son_list.clear();
		}
		int min_x, min_y, max_x, max_y;
		// 是否染色, 如果重复染色, 就是false
		bool is_paint;
		// 我们分9块子节点
		// 6 7 8
		// 3 4 5
		// 0 1 2
		vector<CNode*> son_list;
	};

public:
	// 线段树染色
	bool paint(CNode *root, int start_x, int start_y, int end_x, int end_y)
	{
		// 如果在一个已经染色的区间上染色, 必然是不符合情况的
		if (root->is_paint) return false;
		// 子节点是空, 这一块一定是第一次染色
		if (root->son_list.empty())
		{
			// 看看是否全部覆盖了 root
			if (root->min_x >= start_x && root->max_x <= end_x &&
				root->min_y >= start_y && root->max_y <= end_y)
			{
				root->is_paint = true; // 将这一块染色
				return true;
			}

			// 分为 4 个节点
			for (int i = 0; i < 4; ++i)
			{
				int son_start_x = i % 2 == 0 ? root->min_x : (root->min_x + root->max_x) / 2;
				int son_end_x = i % 2 == 0 ? (root->min_x + root->max_x) / 2 : root->max_x;
				int son_start_y = i < 2 ? root->min_y : (root->min_y + root->max_y) / 2;
				int son_end_y = i < 2 ? (root->min_y + root->max_y) / 2 : root->max_y;
				// 新建一个子节点
				CNode *son = new CNode(son_start_x, son_start_y, son_end_x, son_end_y);

				// 如果没有交集
				if (son_start_x >= end_x || son_end_x <= start_x ||
					son_start_y >= end_y || son_end_y <= start_y)
				{
					// 直接加一个不涂色的
					root->son_list.push_back(son);
					continue;
				}
				// 求交集
				int left_x = max(son_start_x, start_x);
				int right_x = min(son_end_x, end_x);
				int down_y = max(son_start_y, start_y);
				int up_y = min(son_end_y, end_y);
				// 对子集染色, 这里一定是 true, 所以直接染色即可
				paint(son, left_x, down_y, right_x, up_y);
				root->son_list.push_back(son);
			}
			return true;
		}
		// 如果有子节点, 那么我们去子节点的分支找
		for (CNode *node : root->son_list)
		{
			// // 如果这个子节点是没有面积的, 就不费心了
			// if (node->min_x == node->max_x || node->min_y == node->max_y) continue;
			// 如果有交集, 首先, 我们保证 start-end 一定在 root 的范围内
			// x 上没有交集
			if (node->min_x >= end_x || node->max_x <= start_x) continue;
			// y 上没有交集
			if (node->min_y >= end_y || node->max_y <= start_y) continue;
			// 求交集的 left_x, right_x, down_y, up_y
			int left_x = max(node->min_x, start_x);
			int right_x = min(node->max_x, end_x);
			int down_y = max(node->min_y, start_y);
			int up_y = min(node->max_y, end_y);
			if (!paint(node, left_x, down_y, right_x, up_y))
			{
				return false;
			}
		}
		return true;
	}

	bool isRectangleCover(vector<vector<int>>& rectangles) {
		// 初始化
		min_x = min_y = INT_MAX;
		max_x = max_y = INT_MIN;
		area_sum = 0;
		for (auto rectangle : rectangles)
		{
			area_sum += (rectangle[2] - rectangle[0]) * (rectangle[3] - rectangle[1]);
			min_x = min_x < rectangle[0] ? min_x : rectangle[0];
			min_y = min_y < rectangle[1] ? min_y : rectangle[1];
			max_x = max_x > rectangle[2] ? max_x : rectangle[2];
			max_y = max_y > rectangle[3] ? max_y : rectangle[3];
		}
		// 如果面积都不相等, -> 有空格, 那么就 false
		if ((max_y - min_y) * (max_x - min_x) != area_sum) return false;
		// 存在情况, 有空格, 但是有重复, 那么面积也可能相等
		// 用 面积树 来判断有没有重复
		CNode *root = new CNode(min_x, min_y, max_x, max_y);// 初始化线段树
		for (auto rectangle : rectangles)
		{
			if (!paint(root, rectangle[0], rectangle[1], rectangle[2], rectangle[3]))
			{
				return false;
			}
		}
		return true;
	}
};