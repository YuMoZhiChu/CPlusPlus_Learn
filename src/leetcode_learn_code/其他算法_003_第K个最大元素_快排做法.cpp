// 力扣
// https://leetcode-cn.com/problems/kth-largest-element-in-an-array/submissions/
// 学习
// https://labuladong.gitbook.io/algo/suan-fa-si-wei-xi-lie/3.3-qi-ta-suan-fa-pian/kuai-su-xuan-ze
// 快速选择思路
// 类似快排

#include<vector>
using std::vector;

class Solution {
public:
	// 划分区间,这是快排的函数
	int partition(vector<int> &nums, int lo, int hi)
	{
		if (lo == hi) return lo;
		int pivot = nums[lo];
		// 这里设置起点是 lo 和 hi+1, 后续的写法中, 第一个计算的是 lo+1 和 hi
		int i = lo, j = hi + 1;
		while (true)
		{
			// nums[lo+1 ~ i] 都小于 pivot
			while (nums[++i] < pivot)
			{
				if (i == hi) break;
			}
			// nums[j ~ hi] 都大于 pivot
			while (nums[--j] > pivot)
			{
				if (j == lo) break;
			}
			if (i >= j) break;
			// 如果走到这里
			// nums[i] > pivot && nums[j] < pivot
			// 所以交换 i,j
			std::swap(nums[i], nums[j]);
		}
		// 最后, pivot 交换到 j 指向的位置上
		std::swap(nums[j], nums[lo]);
		// 那么, 现在我们的换分为
		// nums[lo..j-1] < nums[j] < nums[j+1..hi]
		return j;
	}

	int findKthLargest(vector<int>& nums, int k) {
		int lo = 0, hi = nums.size() - 1;
		k = nums.size() - k;
		while (lo <= hi)
		{
			// 取划分
			int p = partition(nums, lo, hi);
			// p 是正确的位置
			if (p < k)
			{
				// 那么, k 应该在右边
				lo = p + 1;
			}
			else if (p > k)
			{
				// 那么, k 应该在左边
				hi = p - 1;
			}
			else {
				return nums[p];
			}
		}
		return -1;
	}
};