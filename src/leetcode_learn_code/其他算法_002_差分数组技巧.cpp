// 力扣
// https://leetcode-cn.com/problems/corporate-flight-bookings/
// 学习
// https://labuladong.gitbook.io/algo/suan-fa-si-wei-xi-lie/3.3-qi-ta-suan-fa-pian/cha-fen-ji-qiao
// 构建差分数组 diff
// 对于 nums[i]
// diff[i] = nums[i]-nums[i-1] // nums[-1] = 0
#include<vector>
using std::vector;

class Solution {
public:
	vector<int> corpFlightBookings(vector<vector<int>>& bookings, int n) {
		// 这里用 n+1 个, 初始位是 0
		vector<int> diff(n + 1, 0);
		// 首先 nums[i] = {0, 0, 0, 0}
		for (auto booking : bookings)
		{
			diff[booking[0]] += booking[2]; // 前缀 + booking[2]
			if (booking[1] != n)
			{
				diff[booking[1] + 1] -= booking[2];
			}
		}
		// diff 还原成 nums
		vector<int> nums(n, 0);
		for (int i = 1; i <= n; ++i)
		{
			diff[i] += diff[i - 1];
		}
		return vector<int>(diff.begin() + 1, diff.end());
	}
};