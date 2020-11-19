// https://leetcode-cn.com/problems/remove-k-digits/
// 自己写的方法, 缺点在于增序的时候, 会被劣化成 On^2

#include<string>
using std::string;

// 记录每一个节点的信息，重复的压缩起来
struct NumberNode
{
	NumberNode(char _num_char, int _time) :num_char(_num_char), time(_time) { next = nullptr; }
	char num_char;
	int time;
	NumberNode *next; // 指向下一个内容
};

void try_merge(NumberNode *head)
{
	// 尝试合并头两个数, 因为会出现 2 个数相同的情形
	while (head->next != nullptr && head->num_char == head->next->num_char)
	{
		head->time += head->next->time;
		head->next = head->next->next;
	}
}

class Solution {
public:
	string removeKdigits(string num, int k) {
		if (num.size() <= k) return "0";
		NumberNode *head = nullptr; // 记录头指针
		// 假设 num[0] 一定存在
		head = new NumberNode(num[0], 1);
		NumberNode *it = head;
		for (int i = 1; i < num.size(); ++i)
		{
			if (it->num_char != num[i])
			{
				// 新建一个 char
				it->next = new NumberNode(num[i], 1);
				it = it->next;
			}
			else {
				++it->time; // 否则计数+1
			}
		}
		// 我们现在得到这样一串序列  出现的字符 + 出现的时机，然后我们只需要遍历 k 做删除即可

		while (k--) // 贪心算法, 如果删除 k - 1 是最小的, 那么我们只需要在 k-1 的基础上, 再获得删除得到最小的即可
		{
			if (head->next == nullptr)
			{
				// 因为只有 1 种数字了
				head->time -= (k + 1);
				break;
			}

			// 从 head 和 head->next 选出小的一个, 并且-1time, 并且压缩数组
			if (head->num_char <= head->next->num_char)
			{
				// 这里是一个递增序列, 所以我们应该找到这个递增序列的最大值, 然后减去
				auto iter = head;
				while (iter->next->next && iter->next->num_char <= iter->next->next->num_char)
				{
					iter = iter->next;
				}

				// 给 iter 减少
				--iter->next->time;
				if (iter->next->time == 0)
				{
					iter->next = iter->next->next;
					try_merge(iter);
				}
			}
			else {
				--head->time;
				if (head->time == 0)
				{
					head = head->next; // 跳跃, 内存暂时不考虑释放
					try_merge(head);
				}
			}
		}
		string result = "";
		while (head)
		{
			if (head->num_char == '0' && result == "")
			{
				// 跳过开始的 0
				head = head->next;
				continue;
			}
			while (head->time--)
			{
				result += head->num_char;
			}
			head = head->next; // 下一个
		}
		if (result == "") result = "0";
		return result;
	}
};