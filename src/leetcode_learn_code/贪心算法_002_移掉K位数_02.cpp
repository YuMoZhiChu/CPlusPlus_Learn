// https://leetcode-cn.com/problems/remove-k-digits/
// 自己写的方法, 缺点在于增序的时候, 会被劣化成 On^2
// 再加上答案的 Stack 思路

#include<string>
using std::string;

#include<deque>
using std::deque;

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

		// 在这里, 我们用栈的思路去做遍历
		deque<NumberNode*> s;
		// 当前遍历节点
		it = head;
		while (k--)
		{
			// 尽力压入栈中
			while (s.empty() || (it && s.back()->num_char <= it->num_char))
			{
				s.push_back(it);
				it = it->next;
			}
			// 弹出栈中的元素
			--s.back()->time;
			if (s.back()->time == 0) s.pop_back();
		}
		// 再次压入
		while (it)
		{
			s.push_back(it);
			it = it->next;
		}
		// 这样处理的 stack 就是结果 -> 因为要从底下开始输出, 改为 deque

		string result = "";
		while (!s.empty())
		{
			NumberNode *front = s.front();
			if (result == "" && front->num_char == '0')
			{
				s.pop_front();
				continue;
			}
			while (front->time--)
			{
				result += front->num_char;
			}
			s.pop_front();
		}
		if (result == "") result = "0";
		return result;
	}
};