// 力扣
// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iii/

// 学习链接
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/tuan-mie-gu-piao-wen-ti
// 这个版本是超时版本

#include<vector>
using std::vector;

#include<algorithm>
using std::max;
using std::min;

struct node_msg {
	node_msg() {}
	node_msg(int _min, int _result) :min(_min), result(_result) {}
	int min;
	int result;
};

class Solution {
public:
	int maxProfit(vector<int>& prices) {
		// 把问题拆分出来, 2 次交易
		// 必定是 1 次 [a-b] 和 1 次 [c-d]
		// 因为 1 次交易的所有情况, 可以用 动归 遍历处理
		// 那么 2 次交易, 就是把 prices 拆分成两段即可, 这就只是一个 On 的操作

		int nums = prices.size();

		node_msg **dp = new node_msg*[nums];
		for (int i = 0; i < nums; ++i)
		{
			dp[i] = new node_msg[nums - i]();
		}
		// dp[i][j] 表示 i- (i+j) 的最大收益
		for (int i = 0; i < nums; ++i)
		{
			for (int j = 0; i + j < nums; ++j)
			{
				if (j == 0)
				{
					// 动归初始状态
					dp[i][j].min = prices[i];
					dp[i][j].result = 0;
				}
				else {
					// 递归状态
					// 注意先算结果
					dp[i][j].result = max(dp[i][j - 1].result, prices[i + j] - dp[i][j - 1].min);
					dp[i][j].min = min(dp[i][j - 1].min, prices[i + j]);
				}
			}
		}
		// 递归的 dp[i][j] 已经搞定, i~i+j j 可以为 0
		int result_2 = 0;
		int left, right = 0;
		for (int k = 0; k < nums; ++k)
		{
			// k 表示左边的个数
			if (k == 0)
			{
				left = 0;
			}
			else {
				// 注意这里是 k-1 因为 dp[0][0] 就是左边有一个数了
				left = dp[0][k - 1].result;
			}
			right = dp[k][nums - 1 - k].result;
			result_2 = max(result_2, left + right);
		}
		return result_2;
	}
};