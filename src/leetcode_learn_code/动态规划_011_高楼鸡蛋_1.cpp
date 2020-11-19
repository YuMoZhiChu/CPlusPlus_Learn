#include<vector>
using std::vector;

#include<algorithm>
using std::sort;

// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.2-zi-xu-lie-lei-xing-wen-ti/xin-feng-qian-tao-wen-ti 有一个非常巧妙的解法, 但不是通解, 略过

bool two_int_vector_compare(vector<int> &left, vector<int> &right)
{
	if (left[0] < right[0]) return true;
	if (left[0] == right[0])
		return left[1] < right[1];
	return false;
}

class Solution {
public:
	int maxEnvelopes(vector<vector<int>>& envelopes) {
		if (envelopes.empty()) return 0;
		sort(envelopes.begin(), envelopes.end(), two_int_vector_compare);

		// 动归合集, 只可能去装下前面的内容
		int *dp = new int[envelopes.size()]();
		dp[0] = 0; // 默认为 1
		for (int i = 1; i < envelopes.size(); ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (envelopes[j][0] < envelopes[i][0] && envelopes[j][1] < envelopes[i][1])
				{
					dp[i] = dp[i] > dp[j] + 1 ? dp[i] : dp[j] + 1;
				}
			}
		}
		// 遍历所有解法
		int result = 0;
		for (int i = 0; i < envelopes.size(); ++i)
			if (dp[i] > result) result = dp[i];

		return result + 1;
	}
};