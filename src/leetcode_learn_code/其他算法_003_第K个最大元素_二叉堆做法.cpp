// 力扣
// https://leetcode-cn.com/problems/kth-largest-element-in-an-array/submissions/
// 学习
// https://labuladong.gitbook.io/algo/suan-fa-si-wei-xi-lie/3.3-qi-ta-suan-fa-pian/kuai-su-xuan-ze
// 二叉堆思路

#include<vector>
using std::vector;

#include<queue>
using std::priority_queue;

#include<functional>
using std::greater;

class Solution {
public:
	int findKthLargest(vector<int>& nums, int k) {
		priority_queue<int, vector<int>, greater<int>> pq;
		for (int &num : nums)
		{
			if (pq.size() < k)
			{
				pq.push(num);
			}
			else {
				pq.push(num);
				pq.pop();
			}
		}
		return pq.top();
	}
};