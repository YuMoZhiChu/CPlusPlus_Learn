#include<algorithm>
using std::sort;

#include<vector>
using std::vector;

struct SumNode
{
	SumNode(long _value, int _index) :value(_value), index(_index) {}
	long value;
	int index;
};

bool SumNodeCompare(SumNode &lhs, SumNode &rhs)
{
	return lhs.value < rhs.value;
}

class Solution {
public:
	int countRangeSum(vector<int>& nums, int lower, int upper) {
		if (nums.empty()) return 0;
		// S[i][j] 可以表示成 sum[0~j] - sum[0~(i-1)] sum[-1] = 0
		// 那么问题转换成 sum[0~j] - sum[0~i-1] // i = -1 的时候 就是每个 sum 的值
		// 求sum
		int nums_size = nums.size();
		vector<SumNode> sum_vector;
		long sum_temp = 0;
		for (int i = 0; i < nums_size; ++i)
		{
			sum_temp += nums[i];
			sum_vector.emplace_back(sum_temp, i); // 压入
		}
		// 对 sum 进行排序
		sort(sum_vector.begin(), sum_vector.end(), SumNodeCompare);
		// 因为我们保证了 sum_vector 的顺序
		// 且 sum[j] - sum[i] in [lower, upper]
		// sum[j] in [lower+sum[i], upper+sum[i]]
		// 对于 sum_vector[0] -> min_sum
		// find the index in sum_vector -> 满足 
		//      -> sum_vector[left_index] <= [lower+sum[i], upper+sum[i]] <= sum_vector[right_index]
		// 当我们对 sum_vector 排序后, 那么, sum[i] 递增, 我们的 left_index 和 right_index 只需要往右移动即可
		// 当然, 我们要注意, 需要满足 -> j > i (找到的 sum_vector 的满足验证)
		//  j == i 这种情况不能验证 !!!!
		//  我们还需要单独验证每个 sum_vector

		SumNode min_sum = sum_vector[0]; // 至少有一个
		int left_index = -1; // -1 表示没找到 nums_size 表示在整个序列的右边
		int right_index = 0; // 初始就在 第一个数的左边
		// 确实存在一种情况, 遍历之后, 全在-1(这个还有可能), 全在nums_size(可以直接退出了)
		long lower_0 = lower + min_sum.value;
		long upper_0 = upper + min_sum.value;
		for (int i = 0; i < nums_size; ++i)
		{
			if (left_index == -1) // 找 left_index
			{
				if (lower_0 <= sum_vector[i].value)
					left_index = i;
			}
			// right_index 是贪心的算法, 因为后面一个也可能有情况
			if (upper_0 >= sum_vector[i].value)
			{
				right_index = i + 1; // +1 因为我们要把右边界, 表示在 sum_vector[i] 的右边
			}
			else {
				break; // 如果找到了右边界,那左边界肯定已经找到了,所以退出
			}
		}
		if (left_index == -1) return 0; // 这个就绝对找不到了

		int result = 0;
		// 先把 0 的情况算一遍
		for (int i = left_index; i < right_index; ++i)
		{
			if (sum_vector[i].index > sum_vector[0].index)
				++result;
		}

		// 然后遍历一次 n, 也就是 sum_vector 本身
		for (int i = 0; i < nums_size; ++i)
		{
			if (sum_vector[i].value >= lower && sum_vector[i].value <= upper)
				++result;
		}

		// 遍历, 并尝试同时移动 [left_index, right_index]
		for (int i = 1; i < nums_size; ++i)
		{
			// get new upper, lower
			long new_lower = lower + sum_vector[i].value;
			long new_upper = upper + sum_vector[i].value;

			// get new left_index, right_index;
			// 尽力往前挪
			bool find_new_left_index = false;
			for (int j = left_index; j < nums_size; ++j)
			{
				if (sum_vector[j].value >= new_lower)
				{
					left_index = j;
					find_new_left_index = true;
					break;
				}
			}
			// 找不到前面的数了, 可以直接返回了
			if (!find_new_left_index) return result;

			// right 没这个要求, right 可以一直往前
			for (int j = right_index; j < nums_size; ++j)
			{
				if (sum_vector[j].value > new_upper)
				{
					break;
				}
				right_index = j + 1;
			}

			// 根据 left_index, right_index 算答案
			for (int j = left_index; j < right_index; ++j)
			{
				if (sum_vector[j].index > sum_vector[i].index)
					++result;
			}
		}
		return result;
	}
};