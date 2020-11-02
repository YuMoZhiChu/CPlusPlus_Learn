#include<string>
using std::string;

class Solution {
public:
	int minDistance(string word1, string word2) {
		const int word1_size = word1.size();
		const int word2_size = word2.size();
		// dp 的意义, dp[i][j] 表示 word1[i](表示长度为i的word1子串) 变成 word2[j] 的需要的最少操作数
		// 
		int **dp = new int*[word1_size + 1](); // 初始为 0
		for (int i = 0; i <= word1_size; ++i)
		{
			dp[i] = new int[word2_size + 1]();
		}

		// base 基础情况, 当一条word是0长度时, 需要的操作数, 就是另一条的长度
		for (int i = 0; i <= word1_size; ++i)
			dp[i][0] = i;
		for (int j = 0; j <= word2_size; ++j)
			dp[0][j] = j;

		// 动归递归
		// dp[i][j]
		// if w1[i] == w2[j] -> dp[i-1][j-1]
		// if w1[i] != w2[j]
		//  min{
		//  dp[i][j-1] + 1 // 插入
		//  dp[i-1][j] + 1 // 删除
		//  dp[i-1][j-1] + 1 // 替换  
		// }
		for (int i = 1; i <= word1_size; ++i)
		{
			for (int j = 1; j <= word2_size; ++j)
			{
				if (word1[i - 1] == word2[j - 1])
				{
					dp[i][j] = dp[i - 1][j - 1];
				}
				else {
					dp[i][j] = dp[i][j - 1] + 1;
					if (dp[i - 1][j] + 1 < dp[i][j])
						dp[i][j] = dp[i - 1][j] + 1;
					if (dp[i - 1][j - 1] + 1 < dp[i][j])
						dp[i][j] = dp[i - 1][j - 1] + 1;
				}
			}
		}

		// 获取结果
		int result = dp[word1_size][word2_size];
		for (int i = 0; i <= word1_size; ++i)
		{
			delete[] dp[i];
		}
		delete[] dp;
		return result;
	}
};