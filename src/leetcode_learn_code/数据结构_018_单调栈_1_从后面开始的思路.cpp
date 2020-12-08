// 力扣
// https://leetcode-cn.com/problems/next-greater-element-i/
// 思路
// https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.4-shou-ba-shou-she-ji-shu-ju-jie-gou/dan-tiao-zhan
// 单调栈
// 有意思的是, 这里应该从后面开始算单调栈

#include<unordered_map>
using std::unordered_map;

#include<stack>
using std::stack;

#include<vector>
using std::vector;

class Solution {
public:
	vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
		unordered_map<int, int> search_map;
		stack<int> s;
		for (int i = nums2.size() - 1; i >= 0; --i)
		{
			// 单调弹出
			while (!s.empty() && s.top() < nums2[i])
			{
				s.pop();
			}
			search_map[nums2[i]] = s.empty() ? -1 : s.top();
			s.push(nums2[i]);
		}

		vector<int> result;
		for (int &n : nums1)
		{
			result.push_back(search_map[n]);
		}

		return result;
	}
};