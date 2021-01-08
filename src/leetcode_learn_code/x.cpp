#include<iostream>
#include<string>
#include<vector>
#include<unordered_map>
#include<queue>
#include<set>
#include<map>

using namespace std;

class Solution {
public:
	int waysToSplit(vector<int> nums) {
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

		int last_j_for_left = 2; // 第一个 J 是 2 开始的
		int last_j_for_right = n - 1; // 最后一个 J 是从 n-1 开始的
		for (int i = 1; i <= n - 2; ++i)
		{
			int left, mid, right;

			int j = last_j_for_left;
			left = pre_sum[i] - pre_sum[0];
			mid = pre_sum[j] - pre_sum[i];
			if (mid < left)
			{
				for (; j <= n - 1; ++j)
				{
					mid = pre_sum[j] - pre_sum[i];
					if (mid < left) {
						last_j_for_left = j;
						continue;
					}
					break;
				}
			}
			else {
				for (; j >= i + 1; --j)
				{
					mid = pre_sum[j] - pre_sum[i];
					if (mid >= left) {
						last_j_for_left = j;
						continue;
					}
					++j;
					break;
				}
			}

			int j2 = last_j_for_right;
			mid = pre_sum[j2] - pre_sum[i];
			right = pre_sum[n] - pre_sum[j2];
			if (right < mid) {
				for (; j2 >= j; --j2)
				{
					mid = pre_sum[j2] - pre_sum[i];
					right = pre_sum[n] - pre_sum[j2];
					if (right < mid)
					{
						last_j_for_right = j2;
						continue;
					}
					break;
				}
			}
			else {
				for (; j2 <= n; ++j2)
				{
					mid = pre_sum[j2] - pre_sum[i];
					right = pre_sum[n] - pre_sum[j2];
					if (right >= mid)
					{
						last_j_for_right = j2;
						continue;
					}
					--j2;
					break;
				}
			}
			if (j2 >= j)
			{
				result += (j2 - j + 1);
				if (result >= 1000000007) result -= 1000000007;
			}
		}
		return result;
	}
};

int main()
{
	Solution().waysToSplit({ 1,1,1});
}