// 力扣
// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-with-transaction-fee/submissions/

// 思路
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/tuan-mie-gu-piao-wen-ti

// 这里开始, 使用教程上的标准思路做处理
// 我们的动归思路是
// dp[i][k][0-1] i 表示 第几天, k 表示最多交易次数, 0-1 表示是否持有股票
// dp 表示我们当前获得的利润
// 我们买卖股票的操作, 只有 buy, sell, keep
// 假设 i 天, 没有持有股票
// 上一天 keep, 或者上一天 卖了
// dp[i][k][0] = max{dp[i-1][k][0], dp[i-1][k-1][1] + prices[i]}
// 假设 i 天, 持有股票
// 上一天 keep, 或者上一天 买了
// dp[i][k][1] = max{dp[i-1][k][1], dp[i-1][k-1][0] - prices[i]}
// 这个框架的 求解
// dp[i][k][0] - 因为只有把股票卖出了, 才能获得最大利润
// 这个框架的 base 状态
// dp[i][0][0] = 0 如果不允许操作, 那么 不持股利润 为 0
// dp[i][0][1] = INT_MIN 因为持股是可以出现负数的(比如第一天买入股票, 目前利润就是负数), 所以是负无穷
// dp[0][k][0] = 0 第一天不持有股票, 当前利润是 0
// dp[0][k][1] = -prices[0] 第一天买入股票, 一定是直接买入的利润, 当前负数
// 所有股票问题都基于这个框架

#include<vector>
using std::vector;

#include<algorithm>
using std::max;

class Solution {
public:
	int maxProfit(vector<int>& prices, int fee) {
		if (prices.empty()) return 0;

		// dp 关系做处理
		// k 尽可能多, 所以这里的k的最大值是 (prices.size()+1)/3 - 因为卖出是在第二次操作
		// 但是不用计算, 因为我们的 k 是无穷大的, 所以直接递推即可
		// 因为存在 fee , 我们的持有递推关系变为
		// 上一天 keep, 或者今天 卖了, 我们把 fee 计算在卖出中即可, 因为最终算的也是卖出
		// dp[i][k][0] = max{dp[i-1][k][0], dp[i-1][k-1][1] + prices[i] - fee}
		// 假设 i 天, 持有股票
		// 上一天 keep, 或者今天 买了
		// dp[i][k][1] = max{dp[i-1][k][1], dp[i-2][k-1][0] - prices[i]}

		// 我们再把 k 简化(因为 k 可以无限, 所以没必要计算)
		// dp[i][0] = max{dp[i-1][0], dp[i-1][1]+prices[i]}
		// dp[i][1] = max{dp[i-1][1], dp[i-1][0]-prices[i]}

		// 这里, 因为递推关系, 所以甚至不需要数组
		int dp_i_0 = 0; // 第一天不持股, 0
		int dp_i_1 = -prices[0]; // 第一天就买入, -p[0]
		for (int i = 1; i < prices.size(); ++i)
		{
			int temp = dp_i_0;
			dp_i_0 = max(dp_i_0, dp_i_1 + prices[i] - fee);
			dp_i_1 = max(dp_i_1, temp - prices[i]);
		}

		return dp_i_0;
	}
};