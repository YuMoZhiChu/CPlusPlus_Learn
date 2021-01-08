// 力扣
// https://leetcode-cn.com/problems/ways-to-split-array-into-three-subarrays/submissions/
// 二分法的思想！！！！！！
// 还有写法细节！

#include<vector>
using std::vector;

class Solution {
public:
	int waysToSplit(vector<int>& nums) {
		const int M = 1e9 + 7;
		int n = nums.size();
		// 前缀和
		vector<int> pre_sum(n + 1, 0);
		pre_sum[0] = 0;
		for (int i = 1; i <= n; ++i)
		{
			pre_sum[i] = pre_sum[i - 1] + nums[i - 1];
		}
		int result = 0;
		// left [0, i) mid [i, j), right [j, n)
		// left = pre_sum[i] - pre_sum[0]
		// mid = pre_sum[j] - pre_sum[i]
		// right = pre_sum[n] - pre_sum[j]
		for (int i = 1; i <= n - 2; ++i)
		{
			int left = pre_sum[i] - pre_sum[0];
			int mid, right;

			// 二分查找, 找 j_min 满足 mid > left 即可
			int j_min_left = i + 1;
			int j_min_right = n - 1;
			while (j_min_left <= j_min_right)
			{
				int j_min_mid = (j_min_left + j_min_right) / 2;
				mid = pre_sum[j_min_mid] - pre_sum[i];
				if (mid >= left)
				{
					// 还可以向左找
					j_min_right = j_min_mid - 1;
				}
				else {
					// 一定得向右
					j_min_left = j_min_mid + 1;
				}
			}
			int j_min = j_min_left;

			// 二分查找 j_max 满足 right > mid
			int j_max_left = j_min;
			int j_max_right = n - 1;
			while (j_max_left <= j_max_right)
			{
				int j_max_mid = (j_max_left + j_max_right) / 2;
				mid = pre_sum[j_max_mid] - pre_sum[i];
				right = pre_sum[n] - pre_sum[j_max_mid];
				if (right >= mid)
				{
					// 还可以向右找
					j_max_left = j_max_mid + 1;
				}
				else {
					// 一定得向左
					j_max_right = j_max_mid - 1;
				}
			}
			int j_max = j_max_left;
			result += (j_max - j_min);
			if (result > M) result -= M;
		}
		return result;
	}
};