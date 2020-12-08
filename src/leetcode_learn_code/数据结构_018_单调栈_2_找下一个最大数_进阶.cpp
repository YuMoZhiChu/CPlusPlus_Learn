// 力扣
// https://leetcode-cn.com/problems/next-greater-element-ii/submissions/
// 学习
// https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.4-shou-ba-shou-she-ji-shu-ju-jie-gou/dan-tiao-zhan
// 我这里是先花了 On 去找最大值
// 链接是直接将数组弄成 2 倍的长度, 都可以

#include<vector>
using std::vector;

#include<stack>
using std::stack;

class Solution {
public:
	vector<int> nextGreaterElements(vector<int>& nums) {
		if (nums.empty()) return {};
		// 其实是一样的, 只是我们先找到最大值的位置
		int max_num = nums[0];
		int max_pos = 0;
		for (int i = 1; i < nums.size(); ++i)
		{
			if (nums[i] > max_num)
			{
				max_num = nums[i];
				max_pos = i;
			}
		}
		// 然后我们从 max_pos 开始推
		vector<int> result(nums.size(), 0);
		result[max_pos] = -1; // 这里一定是 -1
		stack<int> s;
		s.push(max_num); // 直接推入即可
		for (int i = max_pos - 1; i != max_pos; --i)
		{
			if (i < 0)
			{
				i += nums.size();
				if (i == max_pos) break;
			}
			while (!s.empty() && s.top() <= nums[i])
			{
				s.pop();
			}
			result[i] = s.empty() ? -1 : s.top();
			s.push(nums[i]);
		}

		return result;
	}
};