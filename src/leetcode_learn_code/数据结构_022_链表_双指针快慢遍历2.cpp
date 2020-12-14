/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

 // 力扣
 // https://leetcode-cn.com/problems/linked-list-cycle-ii/
 // 学习
 // https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.5-shou-ba-shou-shua-shu-zu-ti-mu/shuang-zhi-zhen-ji-qiao
 // 经典双链表
 // 这个思路真的无敌

struct ListNode_slow_fast_2 {
	int val;
	ListNode_slow_fast_2 *next;
	ListNode_slow_fast_2(int x) : val(x), next(nullptr) {}

};

class Solution {
public:
	ListNode_slow_fast_2 *detectCycle(ListNode_slow_fast_2 *head) {
		ListNode_slow_fast_2 *slow, *fast;
		slow = fast = head;
		while (fast != nullptr && fast->next != nullptr)
		{
			fast = fast->next->next;
			slow = slow->next;
			if (slow == fast) break;;
		}
		if (fast == nullptr || fast->next == nullptr) return nullptr;

		slow = head;
		while (slow != fast)
		{
			fast = fast->next;
			slow = slow->next;
		}
		return slow;
	}
};