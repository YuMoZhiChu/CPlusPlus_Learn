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
		if (nums.size() == 1) return nums[0];
		// 这是系列的第二题, 是一个动归, 但是带环形
		// nums[i] 偷不偷 的选择
		// dp[i] = max(dp[i-2] + nums[i], dp[i-1])
		// dp[-1] = 0
		// dp[0] = nums[0]
		// 但这是非环形的情况, 那么, 现在我们退一步考虑
		// 我们 dp[i] 不抢, 那么结果就是 dp[i-1] (这一定是, dp[0]~dp[i-1] 的最优解)
		// 如果 dp[i] 一定要抢, 那么 dp[0] 肯定不抢, 那么算出 (dp[1]~dp[i] 的最优解即可)
		// 如果问, dp[1]~dp[i] 之间, 存在 dp[i] 其实不抢的解, 那么这个解等于 dp[1]~dp[i-1] 一定比 dp[0]~dp[i-1] 小

		int dp_pre = 0;
		int dp_i = nums[0];
		int temp;
		for (int i = 1; i < nums.size() - 1; ++i)
		{
			temp = dp_i;
			dp_i = max(dp_pre + nums[i], dp_i);
			dp_pre = temp;
		}
		int dp_i_minus_1 = dp_i;
		// 算 dp_1 ~ dp_i
		dp_pre = 0;
		dp_i = nums[1];
		for (int i = 2; i < nums.size(); ++i)
		{
			temp = dp_i;
			dp_i = max(dp_pre + nums[i], dp_i);
			dp_pre = temp;
		}
		return max(dp_i, dp_i_minus_1);
	}
};