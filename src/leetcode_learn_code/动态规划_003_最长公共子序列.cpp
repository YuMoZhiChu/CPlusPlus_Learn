#include<string>
using std::string;

#include<algorithm>
using std::max;

class Solution {
public:
	int longestCommonSubsequence(string text1, string text2) {
		const int text1_size = text1.size();
		const int text2_size = text2.size();
		// 构建 dp 表，并赋初值值 0
		// 貌似没有很好的快速构建数组的玩法，用1D
		int *dp = new int[(text1_size + 1)*(text2_size + 1)]();
		// dp 遍历
		// TODO 优化项，因为我们按顺序遍历，就可以得到整个表，所以可以把内存压缩到 2行/2列 选择最少的即可
		for (int i = 1; i <= text1_size; ++i)
		{
			for (int j = 1; j <= text2_size; ++j)
			{
				// 选择
				if (text1[i - 1] == text2[j - 1])
				{
					dp[i + (text1_size + 1) * j] = dp[(i - 1) + (text1_size + 1) * (j - 1)] + 1;
				}
				else {
					/*dp[i + (text1_size + 1) * j] = max(
						dp[i - 1 + (text1_size + 1) * j],
						dp[i + (text1_size + 1) * (j - 1)]
					);*/

					dp[i + (text1_size + 1) * j] = (
						dp[i - 1 + (text1_size + 1) * j] >
						dp[i + (text1_size + 1) * (j - 1)] ?
						dp[i - 1 + (text1_size + 1) * j] :
						dp[i + (text1_size + 1) * (j - 1)]
						);
				}
			}
		}
		return dp[text1_size + (text1_size + 1)*text2_size];
	}
};