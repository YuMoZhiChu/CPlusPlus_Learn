// 力扣
// https://leetcode-cn.com/problems/sliding-window-maximum/
// 学习
// https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.4-shou-ba-shou-she-ji-shu-ju-jie-gou/dan-tiao-dui-lie
// 虽然说, 这个可以用一个 二叉树实现
// 但这里使用单调队列, 在常数范围内解决
// 题解的动归解法, 非常牛逼

#include<deque>
using std::deque;

#include<vector>
using std::vector;

// 单调队列
class MonoQueue
{
	deque<int> mq;
public:
	MonoQueue() {}
	void push(int val)
	{
		// 从尾部压入, 把小于 val 都弹出即可
		// = 号要注意, 不能有
		while (!mq.empty() && mq[mq.size() - 1] < val)
		{
			mq.pop_back();
		}
		mq.push_back(val);
	}

	void pop(int val)
	{
		// 如果弹出, 因为 mq 也带有顺序, 所以尝试弹出第一个即可
		if (val == mq[0])
		{
			mq.pop_front();
		}
	}

	int top()
	{
		return mq[0];
	}

};

class Solution {
public:
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		vector<int> result;
		MonoQueue mq;
		for (int i = 0; i < nums.size(); ++i)
		{
			if (i < k - 1)
			{
				mq.push(nums[i]);
			}
			else {
				mq.push(nums[i]); // 压入 nums[k-1] 就是 k 个
				result.push_back(mq.top());
				mq.pop(nums[i - k + 1]); // 弹出 第一个
			}
		}
		return result;
	}
};