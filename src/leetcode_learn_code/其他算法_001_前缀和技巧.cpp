// 力扣
// https://leetcode-cn.com/problems/subarray-sum-equals-k/
// 学习
// https://labuladong.gitbook.io/algo/suan-fa-si-wei-xi-lie/3.3-qi-ta-suan-fa-pian/qian-zhui-he-ji-qiao
// 记录前缀和的做法
#include<vector>
using std::vector;

#include<unordered_map>
using std::unordered_map;

class Solution {
public:
	int subarraySum(vector<int>& nums, int k) {
		unordered_map<int, int> sum_2_count_map;
		sum_2_count_map[0] = 1;
		int sum_big = 0;
		int ans = 0;
		for (int i = 0; i < nums.size(); ++i)
		{
			sum_big += nums[i];
			int sum_samll = sum_big - k;
			if (sum_2_count_map.count(sum_samll))
				ans += sum_2_count_map[sum_samll];
			++sum_2_count_map[sum_big];
		}
		return ans;
	}
};