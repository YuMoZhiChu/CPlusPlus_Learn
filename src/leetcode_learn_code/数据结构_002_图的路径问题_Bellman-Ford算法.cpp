// 力扣
// https://leetcode-cn.com/problems/cheapest-flights-within-k-stops/

// 学习

// 思路
// Bellman-Ford - 其实就是动归
// https://www.cnblogs.com/fsmly/p/10224616.html

#include<vector>
using std::vector;

#include<algorithm>
using std::min;

class Solution {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		// dp[i] 表示, src 到 i 的距离
		int **dp = new int*[2];
		for (int i = 0; i < 2; ++i)
		{
			dp[i] = new int[n];
			for (int j = 0; j < n; ++j)
				dp[i][j] = INT_MAX; // 初始值是正无穷
		}
		// base
		dp[0][src] = 0;
		dp[1][src] = 0;

		for (int k = 0; k < K + 1; ++k)
		{
			// 每次都会遍历一遍所有的 航线, 看看有没有优化的点
			for (auto edges : flights)
			{
				// 用 k & 1 来压缩dp的内存
				// 如果 src 能到 edges[0] 就可以尝试优化
				if (dp[k & 1][edges[0]] != INT_MAX)
				{
					dp[(k + 1) & 1][edges[1]] = min(dp[(k + 1) & 1][edges[1]], dp[k & 1][edges[0]] + edges[2]);
				}
			}
		}
		return dp[(K + 1) & 1][dst] == INT_MAX ? -1 : dp[(K + 1) & 1][dst];
	}
};