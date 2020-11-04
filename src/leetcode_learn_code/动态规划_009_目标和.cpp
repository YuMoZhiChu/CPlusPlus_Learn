// 动归做法
#include<vector>
using std::vector;

class Solution {
public:
	int findTargetSumWays(vector<int>& nums, int S) {
		// 题目中就有提示, S 的最大值和最小值
		if (S > 1000) return 0;
		if (S < -1000) return 0;

		// 首先是问题的转换
		// 如果把所有的 nums, 以加号和负号, 分为两个集合
		// 有 sum(A) - sum(B) = target
		// sum(A) = target + sum(B)
		// sum(A) * 2 = target + sum(ALL)
		// sum(A) = ( target + sum(ALL) ) / 2
		// 这就转换成了经典的背包问题 可选的内容是 nums, 目标是 sum(A)
		int target = 0;
		for (int &num : nums)
		{
			target += num;
		}
		if ((target + S) % 2) return 0; // 显然, 如果是个小数, 永远完不成
		if ((target + S) < 0) return 0; // 如果是负数, 也不可能
		target = (target + S) / 2;

		// 动归问题, 使用 nums 中, 恰好+满足 target
		// dp[i][j] 使用 nums 的 i 个数, 恰好满足 j
		// int **dp = new int*[nums.size()+1]; // 恰好是 0-nums.size()
		int **dp = new int*[2]; // 压缩到 2 行的做法
		// for (int i = 0; i <= nums.size(); ++i)
		for (int i = 0; i <= 1; ++i)
		{
			dp[i] = new int[target + 1]; // 目标是 0.....target 所以总共 target+1 个位置
		}

		// base 状态
		// dp[0][0] = 1 // 什么都不装, 恰好是 0
		// dp[....][0] = 1 // 什么都不装, 恰好是 0
		// dp[0][1...n] = 0 // 什么都没有, 没有解决方案
		// 这里因为 base 状态中, 存在 00000 , 0 的示例, 所以要预先处理 base
		// 记住了, 这真的别贪
		for (int i = 0; i <= 1; ++i)
			dp[i][0] = 1;
		for (int j = 1; j <= target; ++j)
			dp[0][j] = 0;

		// 因为 target 可能很大, 这里是通过不了
		// 但发现, 这里的 i 只跟 i-1 有关, 所以可以压缩到 2 行即可
		for (int i = 1; i <= nums.size(); ++i)
		{
			for (int j = 0; j <= target; ++j)
			{
				// 动归推导
				// dp[i][j] = 
				//     dp[i-1][j-nums[i-1]] // 使用 nums[i-1]
				//    +dp[i-1][j] // 不使用 nums[i-1]
				if (j < nums[i - 1])
				{
					dp[(i % 2)][j] = dp[(i - 1) % 2][j];
				}
				else {
					dp[(i % 2)][j] = dp[(i - 1) % 2][j] + dp[(i - 1) % 2][j - nums[i - 1]];
				}
			}
		}

		return dp[nums.size() % 2][target];
	}
};