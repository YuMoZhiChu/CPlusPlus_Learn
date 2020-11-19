#include<vector>
using std::vector;

#include<algorithm>
using std::max;

// 改良的动归
// 力扣地址
// https://leetcode-cn.com/problems/super-egg-drop/submissions/
// 思路
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/gao-lou-reng-ji-dan-wen-ti

class Solution {
public:
	int superEggDrop(int K, int N) {
		// K 个 鸡蛋, 扔 N 次, 最多可以测量的楼层数 // 这一定包含了所有的情况
		// 就是, 我们将要求的 move 次数, 修改成 状态变化, 求我们最多可以测出的 楼层熟练
		// 在 i [1,N] 之间, 进行一次 move
		// 如果 i 层碎了 剩下的情况是 dp[k-1][n-1] 剩下 k-1 个鸡蛋, 还可以丢 n-1 次
		// 如果 i 层没碎 剩下的情况是 dp[k][n-1] 剩下 k 个鸡蛋,还可以丢 n-1 次
		// dp[k][n] = dp[k][n-1] + dp[k-1][n-1] + 1(丢的这一层楼)
		// 初始情况, 如果 k = 1 那么扔 n 次, 只能测出 N 层楼
		// 如果 只扔 1 次, 无论几个鸡蛋, 只能测出 1 层楼

		vector<vector<unsigned int>> dp;
		dp.push_back({});
		// 如果只有一个鸡蛋
		for (int n = 0; n < N; ++n)
		{
			dp[0].push_back(n + 1);
		}

		// 这里都是 -1 的情况
		// 从 2 个鸡蛋开始算
		for (int k = 1; k < K; ++k)
		{
			// 默认1次, 就是 1 层楼 的 解
			dp.push_back({ 1 });
			// 这里的次数是 n + 1 哦
			// 这里可以搞状态压缩
			for (int n = 1; n < N; ++n)
			{
				int temp = dp[k][n - 1] + dp[k - 1][n - 1] + 1;
				dp[k].push_back(temp);
				// 可以通过省略来加速
				if (temp >= N) {
					break;
				}
			}
		}
		for (int i = 0; i < N; ++i)
		{
			if (dp[K - 1][i] >= N) return i + 1;
		}
		return 0;
	}
};