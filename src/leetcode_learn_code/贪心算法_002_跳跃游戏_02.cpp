// https://leetcode-cn.com/problems/jump-game-ii/comments/ 
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.4-tan-xin-lei-xing-wen-ti/tiao-yue-you-xi
// 力扣上给出的是正向遍历

#include<vector>
using std::vector;

class Solution {
public:
	int jump(vector<int>& nums) {
		int n = nums.size();
		int end = 0, farthest = 0; // end 是当前这次跳跃的终点 , farthest 是最远记录
		int count = 0;
		for (int i = 0; i < n - 1; ++i)
		{
			farthest = i + nums[i] > farthest ? i + nums[i] : farthest;
			if (i == end)
			{
				end = farthest;
				++count;
			}
		}
		return count;
	}
};