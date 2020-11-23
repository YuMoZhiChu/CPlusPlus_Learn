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
			oper_msg(int _min, int _max) :min(_min), max(_max), next(nullptr) {}
			int min;
			int max;
			oper_msg *next; // 改用链表
		};
		oper_msg *head = new oper_msg(-1, 0);
		oper_msg *it = head;
		oper_msg temp(-1, 0); // 临时变量
		int oper_msg_count = 0;
		for (int i = 0; i < prices.size() - 1; ++i)
		{
			if (prices[i] <= prices[i + 1])
			{
				if (temp.min == -1) temp.min = prices[i];
				temp.max = prices[i + 1];
			}
			else {
				if (temp.min != -1)
				{
					it->next = new oper_msg(temp);
					it = it->next;
					++oper_msg_count;
				}
				temp.min = -1;
				temp.max = 0;
			}
		}
		if (temp.min != -1)
		{
			it->next = new oper_msg(temp);
			it = it->next;
			++oper_msg_count;
		}
		head = head->next;
		if (!head) return 0;
		while (oper_msg_count > k)
		{
			// 两个递增序列合并, 他们的结果, 最好是 0
			int minus_val = INT_MAX; // 记录减少的值
			oper_msg temp(0, 0);
			int new_min, new_max;
			oper_msg *it = head;
			oper_msg *record_it = nullptr;
			while (it->next)
			{
				if (it->min <= it->next->min)
				{
					new_min = it->min;
					new_max = max(it->max, it->next->max);
				}
				else {
					// 如果不能合并, 就选一个
					if ((it->max - it->min) > (it->next->max - it->next->min))
					{
						new_min = it->min;
						new_max = it->max;
					}
					else {
						new_min = it->next->min;
						new_max = it->next->max;
					}
				}
				// 两段长度, 变成一段长度, 少了多少
				int minus_temp = (it->max - it->min) + (it->next->max - it->next->min) - (new_max - new_min);
				if (minus_val > minus_temp)
				{
					minus_val = minus_temp;
					// 我们找到一个减少长度更少的解法
					record_it = it;
					temp.min = new_min;
					temp.max = new_max;
				}
				it = it->next;
			}

			// 链表跨过
			record_it->next = record_it->next->next;
			record_it->min = temp.min;
			record_it->max = temp.max;
			--oper_msg_count;
		}
		int result = 0;
		while (head)
		{
			result += head->max - head->min;
			head = head->next;
		}
		return result;
	}
};