// 力扣
// https://leetcode-cn.com/problems/best-time-to-buy-and-sell-stock-iv/

// 思路
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/tuan-mie-gu-piao-wen-ti

#include<vector>
using std::vector;

#include<algorithm>
using std::max;
using std::min;

class Solution {
public:
	int maxProfit(int k, vector<int>& prices) {
		// 每一个连续递增的子序列, 都表示了一次操作的收益
		// 当然, 收益次数 是有上限的
		// 当我们要获得收益时, 可以尝试合并 2 次操作
		// 合并操作中, 损失的收益最小, 那就是我们的解
		// 然后合并之后, 这次收益看成是 1 次操作
		if (prices.size() <= 1) return 0;
		if (k == 0) return 0;

		struct oper_msg
		{
			oper_msg(int _min, int _max) :min(_min), max(_max) {}
			int min;
			int max;
		};
		vector<oper_msg> oper_vec;
		oper_msg temp(-1, 0);
		for (int i = 0; i < prices.size() - 1; ++i)
		{
			if (prices[i] <= prices[i + 1])
			{
				if (temp.min == -1) temp.min = prices[i];
				temp.max = prices[i + 1];
			}
			else {
				if (temp.min != -1) oper_vec.push_back(temp);
				temp.min = -1;
				temp.max = 0;
			}
		}
		if (temp.min != -1) oper_vec.push_back(temp);
		if (oper_vec.empty()) return 0;
		while (oper_vec.size() > k)
		{
			// 两个递增序列合并, 他们的结果, 最好是 0
			int minus_val = INT_MAX; // 记录减少的值
			int record_pos = -1;
			oper_msg temp(0, 0);
			int new_min, new_max;
			for (int i = 0; i < oper_vec.size() - 1; ++i)
			{
				if (oper_vec[i].min <= oper_vec[i + 1].min)
				{
					new_min = oper_vec[i].min;
					new_max = max(oper_vec[i].max, oper_vec[i + 1].max);
				}
				else {
					// 如果不能合并, 就选一个
					if ((oper_vec[i].max - oper_vec[i].min) > (oper_vec[i + 1].max - oper_vec[i + 1].min))
					{
						new_min = oper_vec[i].min;
						new_max = oper_vec[i].max;
					}
					else {
						new_min = oper_vec[i + 1].min;
						new_max = oper_vec[i + 1].max;
					}
				}
				// 两段长度, 变成一段长度, 少了多少
				int minus_temp = (oper_vec[i].max - oper_vec[i].min) + (oper_vec[i + 1].max - oper_vec[i + 1].min) - (new_max - new_min);
				if (minus_val > minus_temp)
				{
					minus_val = minus_temp;
					// 我们找到一个减少长度更少的解法
					record_pos = i;
					temp.min = new_min;
					temp.max = new_max;
				}
			}
			// 将 oper_vec[record_pos], oper_vec[record_pos+1] 替换成 temp
			oper_vec.erase(oper_vec.begin() + record_pos);
			oper_vec[record_pos] = temp;
		}
		int result = 0;
		for (auto it : oper_vec)
		{
			result += it.max - it.min;
		}
		return result;
	}
};