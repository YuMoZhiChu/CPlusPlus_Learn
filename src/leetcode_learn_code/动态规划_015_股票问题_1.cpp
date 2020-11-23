// 力扣
// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/

// 学习链接
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/tuan-mie-gu-piao-wen-ti

#include<vector>
using std::vector;

#include<algorithm>
using std::max;
using std::min;

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		// 把问题拆分出来, 2 次交易
		// 必定是 1 次 [a-b] 和 1 次 [c-d]
		// 因为 1 次交易的所有情况, 可以用 动归 遍历处理
		// 那么 2 次交易, 就是把 prices 拆分成两段即可, 这就只是一个 On 的操作

		// 优化, 我们在第一次东动归中, 代价是 O n^2 但是实际上, 我们只需要 以 0 开头的 1 次代价
		// 和 以 n-1 结尾的一次代价, 然后综合计算即可

		int nums = prices.size();

		int *left_dp = new int[nums];
		int min_count = prices[0];
		left_dp[0] = 0;
		for (int i = 1; i < nums; ++i)
		{
			min_count = min_count < prices[i] ? min_count : prices[i];
			left_dp[i] = max(left_dp[i - 1], prices[i] - min_count);
		}

		int *right_dp = new int[nums];
		int max_count = prices[nums - 1]; // 这里应该记最大值, 从后玩前减
		right_dp[nums - 1] = 0; // 这里倒叙
		for (int i = nums - 2; i >= 0; --i)
		{
			max_count = max_count > prices[i] ? max_count : prices[i];
			right_dp[i] = max(right_dp[i + 1], max_count - prices[i]);
		}

		// 最后左右互相加
		int result = right_dp[0]; // 应该和 left_dp[nums-1] 相等
		// k 表示左边有几个, 从 1 个开始
		for (int k = 1; k < nums; ++k)
		{
			result = max(result,
				left_dp[k - 1] + right_dp[k]);
		}
		return result;
	}
};