// 力扣
// https://leetcode-cn.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/

// 学习
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/dong-tai-gui-hua-zhi-kmp-zi-fu-pi-pei-suan-fa

// 解法
// 动归解

#include<string>
using std::string;

#include<algorithm>
using std::min;

class Solution {
public:
	int minInsertions(string s) {
		int **dp = new int*[s.size()];
		for (int i = 0; i < s.size(); ++i)
		{
			dp[i] = new int[s.size() - i]();
		}
		// dp[i][j] 表示 i ~ i+j 的解
		for (int j = 0; j < s.size(); ++j)
		{
			for (int i = 0; i + j < s.size(); ++i)
			{
				if (j == 0)
				{
					dp[i][0] = 0;
					continue;
				}
				if (j == 1)
				{
					if (s[i] == s[i + 1]) dp[i][1] = 0;
					else dp[i][1] = 1;
					continue;
				}
				if (s[i] == s[i + j])
					dp[i][j] = dp[i + 1][j - 2];
				else
					dp[i][j] = min(dp[i + 1][j - 1], dp[i][j - 1]) + 1;
			}
		}
		return dp[0][s.size() - 1];
	}
};