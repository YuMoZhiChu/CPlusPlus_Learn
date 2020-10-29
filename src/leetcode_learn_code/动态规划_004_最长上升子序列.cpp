#include<vector>
using std::vector;

class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty()) return 0;
		// dp[i] 以 nums[i] 结尾, 最大的上升子序列 的 长度
		const int nums_size = nums.size();
		int *dp = new int[nums_size]();
		// 一个数结尾, 长度是 1 - 1, 所有长度应该初始化为 1, 这里为了方便
		dp[0] = 0;
		// n ^ 2 消耗的遍历
		for (int i = 1; i < nums_size; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (nums[j] < nums[i])
				{
					dp[i] = dp[j] + 1 > dp[i] ? dp[j] + 1 : dp[i];
				}
			}
		}

		// 遍历dp 取最大值
		int max = 0;
		for (int i = 0; i < nums_size; ++i)
		{
			max = dp[i] > max ? dp[i] : max;
		}
		delete[] dp;
		// 补上丢失的 1
		return max + 1;
	}
};