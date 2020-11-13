// 贪心思路
// https://leetcode-cn.com/problems/non-overlapping-intervals/
// 解题思路
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.4-tan-xin-lei-xing-wen-ti/tan-xin-suan-fa-zhi-qu-jian-tiao-du-wen-ti


#include<vector>
using std::vector;

#include<algorithm>
using std::sort;

class Solution {
public:
	int eraseOverlapIntervals(vector<vector<int>>& intervals) {
		if (intervals.size() <= 1) return 0;
		sort(intervals.begin(), intervals.end(), []
		(vector<int> &lhs, vector<int> &rhs)
		{ return lhs[1] < rhs[1]; });
		int count = 1;
		int x_end_pos = intervals[0][1];
		// 或者可以这么理解, 我们要让 区间, 尽可能的紧凑
		// 碰到不好处理的提型，可以试一下贪心算法
		for (int i = 1; i < intervals.size(); ++i)
		{
			if (intervals[i][0] >= x_end_pos)
			{
				x_end_pos = intervals[i][1];
				++count;
			}
		}
		return intervals.size() - count;
	}
};