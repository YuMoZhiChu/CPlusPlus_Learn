// 力扣
// https://leetcode-cn.com/problems/find-minimum-time-to-finish-all-jobs/
// 标准的动归思路
// 需要将 jobs -> 2^12 的思路

#include<vector>
using std::vector;

class Solution {
public:
	int minimumTimeRequired(vector<int>& jobs, int k) {
		int n = jobs.size();
		// 我们用 2^n 来表示 jobs 的完成情况

		// dp[j][i] 表示有 j 个工人, 完成 i 情况的jobs 时, 所花费的时间
		// dp[0][i] 表示只有一个工人的情况, 最大是 第 k-1 号工人
		// dp[j][i] = dp[j-1][i-s] + dp[0][s];
		// 对于 该情况, 我们把 第 j 号工人, 让他单独完成一个子集 S
		// s 是 i 的一个子集, 即从 i 本身, 到 s->0 (11110011 这种存在1位的子集)

		vector<vector<int>> dp(k, vector<int>(1 << n, 0));
		// 初始化 dp[0][i] = i 表示的 jobs 为1, 做, 一个人做完的时间和
		// dp[0][0] = 0
		// dp[k][0] = 0 因为没有任何工作, 所以就是最小 最大工作时间就是 0
		for (int i = 1; i < (1 << n); ++i)
		{
			// 这里用位运算来处理, 总共 0~n-1 位
			for (int j = 0; j < n; ++j)
			{
				// i 的第 j 位是 0 , jobs[j] 不做, 不变
				if ((i & (1 << j)) == 0) continue;
				int left = i - (1 << j); // 这是小数位
				// 加上 jobs[j]
				dp[0][i] = dp[0][left] + jobs[j];
			}
		}

		// 开始dp
		for (int j = 1; j < k; ++j)
		{
			// 遍历情况 i, 从 1 开始即可
			for (int i = 1; i < (1 << n); ++i)
			{
				int min_time = INT_MAX;
				// dp[j][i] = max(dp[j-1][i-s] , dp[0][s]);
				// 我们遍历 i 的所有子集 s, 直到空集合
				// s = (s-1)&i 遍历 所有子集 的操作 (一个一个减, &i 做跳步)
				for (int s = i; s != 0; s = (s - 1)&i)
				{
					int left = i - s;
					int val = max(dp[j - 1][left], dp[0][s]);
					min_time = min(min_time, val);
				}

				dp[j][i] = min_time;
			}
		}

		return dp[k - 1][(1 << n) - 1];

	}
};