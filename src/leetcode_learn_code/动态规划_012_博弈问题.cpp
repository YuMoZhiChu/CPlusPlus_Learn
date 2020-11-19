// 力扣地址
// https://leetcode-cn.com/problems/stone-game/

// 学习地址
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/dong-tai-gui-hua-zhi-bo-yi-wen-ti

// 个人思路
// 因为2人,都是尽最大可能获得胜利, 所以他们最后拿到的分数, 是固定的, 假设先手是 a, 后手是 b
// 那么就是 a+b = sum, 且 a > b 的情况下, 先手获胜
// 定义 dp[i][j] = set(a, b) 其中, i <= j 表示从 i 开始 到 j 下标的 子序列
// 那么我们的 dp[i][j] 可以有 2 种情况推演归来 dp[i+1][j] 和 dp[i][j-1], 那么先手就会变成后手
// 因为这个游戏, 先手优势, 所以先手的 dp[i][j][a] = max{ dp[i+1][j][b]+p[i], dp[i][j-1][b]+p[j] }
// 是这么理解的, 因为这一次的结果, 可以由 两种情况演变而来, 先手的话, 我想要最多, 就一定是选择多一种的情况
// [而且再次变成后手时, 机会也是更大]
// 进一步优化, 我们只需要在 dp[i][j] 记录 先手-后手 的最大可能差
// 那么 dp[i][j] = max{ -dp[i+1][j]+p[i] , -dp[i][j-1]+p[j] }
// 显然, 初始情况是, dp[i][i] = p[i];

#include<vector>
using std::vector;

#include<algorithm>
using std::max;

class Solution {
public:
	bool stoneGame(vector<int>& piles) {
		int piles_size = piles.size();
		int **dp = new int*[piles_size];
		for (int i = 0; i < piles_size; ++i)
			dp[i] = new int[i + 1](); // 只需要搞一半即可
		// 注意这里, 搞了对换
		for (int j = 0; j < piles_size; ++j)
		{
			for (int i = j; i >= 0; --i)
			{
				if (i == j)
				{
					dp[j][i] = piles[i];
				}
				else {
					dp[j][i] = max(piles[i] - dp[j][i + 1], piles[j] - dp[j - 1][i]);
				}
			}
		}
		return dp[piles_size - 1][0] > 0;
	}
};