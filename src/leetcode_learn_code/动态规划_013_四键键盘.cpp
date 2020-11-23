// 力扣地址
// https://leetcode-cn.com/problems/4-keys-keyboard/
// 学习地址
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/dong-tai-gui-hua-zhi-si-jian-jian-pan
// 思路
// 使用 1D 的动归来解决这个问题 dp[N]
// 显然 dp[0-4] = i+1
// 那么, 我们解一个比较大的 dp[n]
// 他肯定是某个结果上, 然后一直做 赋值黏贴 所以是   xxxxxx 选中 复制 黏贴 黏贴 黏贴
// i + 1 + j 就是他的拆解 得到的挤过是 i*j


class Solution {
public:
	int maxA(int N) {
		int *dp = new int[N]();
		for (int i = 0; i < N; ++i)
		{
			if (i < 6)
			{
				dp[i] = i + 1;
			}
			else {
				// dp[i] = a * b // a + b + 1 = i
				// 至少是 2 1 2 = 4
				int max = i + 1;
				// j + 1 + k = i + 1 , k >= 2
				for (int j = 2; j + 2 <= i; ++j)
				{
					int temp = i - j;
					temp = dp[j - 1] * temp;
					max = temp > max ? temp : max;
				}
				dp[i] = max;
			}
		}
		return dp[N - 1];
	}
};