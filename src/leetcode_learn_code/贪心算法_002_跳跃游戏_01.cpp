// https://leetcode-cn.com/problems/jump-game-ii/comments/ 
// 自己写的 On 的解法
// 尝试一次跳跃，然后在跳跃点，和上一个跳跃点之间，找下一个跳跃点(最远的),然后累计次数

#include<vector>
using std::vector;

class Solution {
public:
	int jump(vector<int>& nums) {
		if (nums.size() <= 1) return 0;
		int count = 1;
		int max_length = 0 + nums[0]; // 跳跃一次
		if (max_length >= nums.size() - 1) return 1;
		int old_max_length = max_length;
		int pre = 0; // 记录上一次跳跃的位置
		int i = max_length; // 遍历的位置
		while (max_length < nums.size() - 1)
		{
			if (i == pre)
			{
				pre = old_max_length;
				i = max_length;
				//old_max_length = max_length;
				++count;
			}
			else {
				if (i == max_length)
				{
					old_max_length = max_length; // 更新 max_length
				}
				// 逆向, 尽可能的搜
				if (i + nums[i] > max_length)
				{
					max_length = i + nums[i];
				}
				--i;
			}
		}

		return count + 1;
	}
};