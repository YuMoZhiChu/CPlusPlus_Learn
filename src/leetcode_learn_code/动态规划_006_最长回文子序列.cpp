#include<string>
using std::string;

#include<hash_set>

class Solution {
public:
	int longestPalindromeSubseq(string s) {
		if (s.empty()) return 0;
		const int size = s.size();
		// dp 的意义, 是以第i个字符开头, 以第j个字符结尾, 其 最长的回文子序列 的长度
		// 所以 dp 是一个二维的数组
		// 当然我们不需要为其完全分配空间, 因为第 j 个字符结尾, 开头只可能是 0-j
		int **dp = new int*[size];
		for (int j = 0; j < size; ++j)
		{
			// 因为 i 的范围是 0-j, 所以大小应该是 j+1
			dp[j] = new int[j + 1]();
		}

		// 我们通过初始内容, 进行递推
		// base: dp[k][k] = 1 ;dp[k][k-1] = 2(if s[k]==s[k-1])
		dp[0][0] = 1; // 第一个开始, 第一个结束, 是1
		for (int j = 1; j < size; ++j)
		{
			for (int i = j; i >= 0; --i)
			{
				if (i == j)
				{
					dp[j][i] = 1; // 初始大小 1
				}
				else if (i == j - 1) {
					if (s[j] == s[i]) {
						dp[j][i] = 2; // 重复的两个数 是 2
					}
					else {
						dp[j][i] = 1;
					}
				}
				else {
					// {X[.....]} 情况, 取右边
					dp[j][i] = dp[j][i + 1]; // 这是默认初值, 等于上一个结果
					// {[.....]X} 情况, 取左边
					if (dp[j - 1][i] > dp[j][i])
						dp[j][i] = dp[j - 1][i];
					// {X[.....]X} 情况, 取中间+2
					if (s[j] == s[i])
						if (dp[j - 1][i + 1] + 2 > dp[j][i])
							dp[j][i] = dp[j - 1][i + 1] + 2;
				}
			}
		}

		// 我们求的值, 就是 [0, size-1] 部分的内容即可
		int result = dp[size - 1][0];
		// 释放内存
		for (int j = 0; j < size; ++j)
		{
			delete[] dp[j];
		}
		delete[] dp;
		return result;
	}
};