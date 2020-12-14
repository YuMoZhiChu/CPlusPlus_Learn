/**
 * Definition for singly-linked list.
 * struct ListNode_slow_fast_1 {
 *     int val;
 *     ListNode_slow_fast_1 *next;
 *     ListNode_slow_fast_1(int x) : val(x), next(NULL) {}
 * };
 */

 // 力扣
 // https://leetcode-cn.com/problems/linked-list-cycle/
 // 学习
 // https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.5-shou-ba-shou-shua-shu-zu-ti-mu/shuang-zhi-zhen-ji-qiao
 // 经典双链表

struct ListNode_slow_fast_1 {
	int val;
	ListNode_slow_fast_1 *next;
	ListNode_slow_fast_1(int x) : val(x), next(nullptr) {}

};

class Solution {
public:
	bool hasCycle(ListNode_slow_fast_1 *head) {
		ListNode_slow_fast_1 *slow, *fast;
		slow = fast = head;
		while (fast != nullptr && fast->next != nullptr)
		{
			fast = fast->next->next;
			slow = slow->next;
			if (slow == fast) return true;
		}
		return false;
	}
};