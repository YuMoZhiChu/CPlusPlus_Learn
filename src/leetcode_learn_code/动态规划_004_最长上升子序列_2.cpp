#include<vector>
using std::vector;

class Solution {
public:

	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty()) return 0;
		// dp[i] 以 nums[i] 结尾, 最大的上升子序列 的 长度
		// stack_table 是 耐心排序 的牌堆表, 存的是, 牌堆最下面的一张
		int *stack_table = new int[nums.size()]();
		int stack_size = 0;// 牌堆真正的大小
		// n ^ 2 消耗的遍历
		for (int i = 0; i < nums.size(); ++i)
		{
			// 这里用二分查找, 加速, 找到这张牌应该放的位置
			// 因为, 我们是维护, 牌堆最下面的一张牌, 一定是一个递增的顺序
			// 插入一张牌, 或者新建一个牌堆
			int left = 0;
			int right = stack_size; // 左闭右开
			while (left < right)
			{
				int mid = (left + right) / 2;
				// 如果中间数, 大于当前卡, 那么我们应该找 左半边
				if (stack_table[mid] > nums[i])
					right = mid;
				// 如果中间数, 小于当前卡, 这里的做法是, 找右半边, 因为左边是闭区间, 所以+1
				else if (stack_table[mid] < nums[i])
					left = mid + 1;
				// 出现相等的情况, 因为rihgt是闭区间, 所以通过直接排除right, 逼迫 left 与 right 相等
				else
					right = mid;
			}
			// 增加一个新的牌堆
			if (left == stack_size) stack_size++;
			// 这张牌放在牌堆的最下面
			stack_table[left] = nums[i];
		}
		delete[] stack_table;
		// 牌堆的个数, 就是最长上升子序列
		return stack_size;
	}
};