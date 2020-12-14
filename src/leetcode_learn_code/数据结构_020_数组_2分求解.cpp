// 力扣
// https://leetcode-cn.com/problems/koko-eating-bananas/
// 学习资料
// https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.5-shou-ba-shou-shua-shu-zu-ti-mu/koko-tou-xiang-jiao
// 2分法

#include<vector>
using std::vector;

class Solution {
public:
	// k 是当前速度
	// max_time 是 H
	inline bool can_eat(vector<int>& piles, const int &k, const int &max_time)
	{
		int time = 0;
		for (auto &pile : piles)
		{
			time += (pile + k - 1) / k;
		}
		return time <= max_time;
	}


	int minEatingSpeed(vector<int>& piles, int H) {
		// 先求出最大值
		int max = piles[0];
		for (int i = 1; i < piles.size(); ++i)
		{
			max = piles[i] > max ? piles[i] : max;
		}
		// 解从 1 ~ max 出
		int left = 1;
		int right = max; // 最大值
		while (left < right)
		{
			int mid = (left + right) / 2;
			if (can_eat(piles, mid, H))
			{
				right = mid;
			}
			else {
				left = mid + 1;
			}
		}
		return left;
	}
};