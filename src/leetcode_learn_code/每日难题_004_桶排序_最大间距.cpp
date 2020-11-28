// 力扣
// https://leetcode-cn.com/problems/maximum-gap/
// 题解学习
// 学习桶排序的思路
// 学习基数排序的思路

#include<vector>
using std::vector;

#include<map>
using std::pair;

#include<algorithm>
using std::max_element;
using std::min_element;
using std::max;
using std::min;

class Solution {
public:
	int maximumGap(vector<int>& nums) {
		int n = nums.size();
		if (n < 2) {
			return 0;
		}
		int minVal = *min_element(nums.begin(), nums.end());
		int maxVal = *max_element(nums.begin(), nums.end());
		int d = max(1, (maxVal - minVal) / (n - 1));
		int bucketSize = (maxVal - minVal) / d + 1;

		vector<pair<int, int>> bucket(bucketSize, { -1, -1 });  // 存储 (桶内最小值，桶内最大值) 对，(-1, -1) 表示该桶是空的
		for (int i = 0; i < n; i++) {
			int idx = (nums[i] - minVal) / d;
			if (bucket[idx].first == -1) {
				bucket[idx].first = bucket[idx].second = nums[i];
			}
			else {
				bucket[idx].first = min(bucket[idx].first, nums[i]);
				bucket[idx].second = max(bucket[idx].second, nums[i]);
			}
		}

		int ret = 0;
		int prev = -1;
		for (int i = 0; i < bucketSize; i++) {
			if (bucket[i].first == -1) continue;
			if (prev != -1) {
				ret = max(ret, bucket[i].first - bucket[prev].second);
			}
			prev = i;
		}
		return ret;
	}
};