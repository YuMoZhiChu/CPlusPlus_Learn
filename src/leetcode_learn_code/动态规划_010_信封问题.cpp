#include<vector>
using std::vector;

#include<algorithm>
using std::max;

// 直接的动态规划, 时间过不了
// 力扣地址
// https://leetcode-cn.com/problems/super-egg-drop/submissions/

class Solution {
public:
	int superEggDrop(int K, int N) {
		// K 个 鸡蛋, N 层楼 , 需要最少移动次数 move, 得到 最大的 F
		// 在 i [1,N] 之间, 进行一次 move
		// 如果 i 层碎了 dp[k][n] = dp[k-1][i-1] + 1// 少了一个鸡蛋
		// 如果 i 层没碎 dp[k][n] = dp[k][n-i] + 1 // 等价于 i+1 ~ N 的楼层, 依然是 K 个鸡蛋 这里的起点是 n-1
		// 因为我们需要考虑的是, 所有的情况, 所以 dp[k][n] 是 i 做遍历的, 最大值(因为要找出所有的可能的解)
		// 这里的 i, 指的是策略, 相当于, 第一次在哪个地方扔
		// 所以我们要考虑的是, dp[k-1][i-1] + 1 和 dp[k][n-i] + 1 的最大值, 
		// 遍历 i 得到的最小值
		// 边界条件是 , k 鸡蛋数, 到 1 就直接有结果了
		//              n 楼层数, 到 1 就有结果(结果是1), 所以呢, 子条件是从 n-1 开始的
		// 显然基础条件是, 只有一个鸡蛋, 只能一层一层的扔, 所以 dp[1][x] = x;
		if (K > N) K = N; // 每层楼丢一个就够了呀
		vector<vector<int>> dp;
		dp.push_back({});
		// 如果只有一个鸡蛋
		for (int n = 0; n < N; ++n)
		{
			dp[0].push_back(n + 1);
		}
		// 这里都是 -1 的情况
		// 从2个鸡蛋开始算
		for (int k = 1; k < K; ++k)
		{
			// 默认第一层楼, 解法是 1
			dp.push_back({ 1 });
			for (int n = 1; n < N; ++n)
			{
				int min_result = n + 1; // 最小的初始值, 每层楼丢一次即可
				// 这个流程, 有优化的过程, 可以用二分法来做
				for (int i = 1; i <= n - 1; ++i)
				{
					// dp[k][n - i - 1] 相关于 i 单调递减
					// dp[k - 1][i - 1] 相关于 i 单调递增
					// 2 分法找出 谷底即可
					int temp = max(dp[k][n - i - 1], dp[k - 1][i - 1]) + 1; // 因为包含了 0 起点, 所以要改成 n-i-1
					min_result = min_result < temp ? min_result : temp;
				}
				dp[k].push_back(min_result);
			}
		}
		return dp[K - 1][N - 1];
	}
};