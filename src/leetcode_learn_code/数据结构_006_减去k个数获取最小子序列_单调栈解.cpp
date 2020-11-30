// 力扣
// https://leetcode-cn.com/problems/find-the-most-competitive-subsequence/
// 思路, 跟 力扣 402 很像
// 核心
// 单调栈

#include<vector>
using std::vector;

#include<stack>
using std::stack;

class Solution {
public:
	vector<int> mostCompetitive(vector<int>& nums, int k) {
		stack<int> st;
		int pop_num = nums.size() - k; // 最多可以弹出 pop_num 次
		for (int i = 0; i < nums.size(); ++i)
		{
			while (!st.empty() && st.top() > nums[i] && pop_num)
			{
				st.pop();
				--pop_num;
			}
			st.push(nums[i]);
		}
		vector<int> result(st.size(), 0);
		for (int i = result.size() - 1; i >= 0; --i)
		{
			result[i] = st.top();
			st.pop();
		}
		return vector<int>(result.begin(), result.begin() + k);
	}
};