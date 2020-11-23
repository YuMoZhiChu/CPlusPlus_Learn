// 力扣
// https://leetcode-cn.com/problems/house-robber/

// 学习
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/qiang-fang-zi

#include<vector>
using std::vector;

#include<algorithm>
using std::max;

class Solution {
public:
	int rob(vector<int>& nums) {
		if (nums.empty()) return 0;
		// 这是系列的第一题, 是一个标准的动归
		// nums[i] 偷不偷 的选择
		// dp[i] = max(dp[i-2] + nums[i], dp[i-1])
		// dp[-1] = 0
		// dp[0] = nums[0] 
		int dp_pre = 0;
		int dp_i = nums[0];
		int temp;
		for (int i = 1; i < nums.size(); ++i)
		{
			temp = dp_i;
			dp_i = max(dp_pre + nums[i], dp_i);
			dp_pre = temp;
		}
		return dp_i;
	}
};