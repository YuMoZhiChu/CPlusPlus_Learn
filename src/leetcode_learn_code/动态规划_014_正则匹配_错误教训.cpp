// 力扣地址
// https://leetcode-cn.com/problems/regular-expression-matching/
// 学习地址
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/dong-tai-gui-hua-zhi-zheng-ze-biao-da

// 这道题, 一个非常深刻的教训, 动归, 元素的顺序一定是有序的！！！


#include<string>
using std::string;

#include<vector>
using std::vector;

#include<unordered_set>
using std::unordered_set;

class Solution {
public:
	bool isMatch(string s, string p) {
		// dp[i][j] 表示遍历到 s[i-1] p[j-1] 时, 是否匹配成功
		// i , j 的范围是 0-size
		// bool **dp; // 初始都是 false
		// dp = new bool*[s.size()+1];
		// for (int i = 0; i <= s.size(); ++i)
		// {
		//     dp[i] = new bool[p.size()+1]();
		// }
		// dp[0][0] = true;

		vector<vector<bool>> dp;
		for (int i = 0; i <= s.size(); ++i)
		{
			dp.push_back(vector<bool>(p.size() + 1, false));
		}
		dp[0][0] = true;

		// 初始情况
		// dp[0][0] = true
		// dp[x][0] = dp[0][x] = false

		int i = 1, j = 1;
		while (i <= s.size() || j <= p.size())
		{
			// 处理 *
			if (j < p.size() && p[j] == '*')
			{
				// 第一次处理 * 时, 都需要处理 0 个的情况
				dp[i - 1][j + 1] = dp[i - 1][j - 1];
				// 我们移动 j 的位置
				++j;
				continue;
			}
			if (p[j - 1] == '*')
			{
				if (p[j - 2] != '.' && p[j - 2] != s[i - 1])
				{
					++j; // 查j的下一个位置, 如果到尾了, 说明没有匹配完, 得断开
				}
				else {
					if (i <= s.size())
					{
						dp[i][j] = dp[i - 1][j];
						++i;
					}
					else {
						++j; // 匹配到末尾了
					}
				}
				continue;
			}
			// 处理相同的值
			if (s[i - 1] == p[j - 1] || p[j - 1] == '.')
			{
				// 同质
				dp[i][j] = dp[i - 1][j - 1];
				++i;
				++j;
				continue;
			}
			// 处理边界情况, i 读完了, j 没读完
			if (i == s.size() + 1 && j <= p.size())
			{
				if (!dp[i - 1][j]) break;
				--i; // 直接回溯来判断
				continue;
			}
			// j 的情况同理
			if (j == p.size() + 1 && i <= s.size())
			{
				if (!dp[i][j - 1]) break;
				--j;
				if (p[j - 1] == '*') --j;
				continue;
			}
		}
		return dp[s.size()][p.size()];
	}
};