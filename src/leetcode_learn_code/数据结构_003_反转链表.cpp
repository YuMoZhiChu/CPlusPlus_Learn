// 力扣
// https://leetcode-cn.com/problems/reverse-linked-list-ii/
// 前面一题基础题
// https://leetcode-cn.com/problems/fan-zhuan-lian-biao-lcof/submissions/ (非常简单, 直接翻转即可)

// 这道题有比较多的参考解法, 非常值得一看, 涉及的操作比我写的精妙

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};
class Solution {
public:
	ListNode* reverseBetween(ListNode* head, int m, int n) {
		if (!head || !head->next) return head;
		ListNode *fake_head = new ListNode(0);
		fake_head->next = head;
		ListNode *it = fake_head;

		while (m > 1) // 恰好指向开头
		{
			it = it->next;
			--n;
			--m;
		}
		auto front_it = it;
		// if (!it || !it->next) return head;
		it = it->next; // 指向我们要开始交换的内容
		auto record_it = it;

		front_it->next = nullptr;
		while (n--)
		{
			auto temp = it->next;
			it->next = front_it->next;
			front_it->next = it;
			it = temp;
		}
		record_it->next = it;

		return fake_head->next;
	}
};