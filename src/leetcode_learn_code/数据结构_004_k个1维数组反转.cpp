/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
 // 力扣
 // https://leetcode-cn.com/problems/reverse-nodes-in-k-group/

 // 学习
 // https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.2-shou-ba-shou-shua-lian-biao-ti-mu-xun-lian-di-gui-si-wei/k-ge-yi-zu-fan-zhuan-lian-biao
 // 递归写法, 个人不太喜欢
struct ListNode {
	int val;
	ListNode *next;
	ListNode(int x) : val(x), next(nullptr) {}
};
class Solution {
public:
	ListNode* reverseKGroup(ListNode* head, int k) {
		ListNode *fake_head = new ListNode(0);
		fake_head->next = head;
		ListNode *it = fake_head;
		while (it->next)
		{
			ListNode *pre = it;
			it = it->next;
			int temp = k - 1;
			while (temp > 0)
			{
				ListNode *nex = it->next;
				if (!nex)
				{
					// 如果发生了这种情况, 要做多一次翻转(因为pre开始的数,已经翻转了)
					// 再翻转过来即可
					temp = k - temp;
					it = pre->next;
					while (temp > 1) // 1 的时候不需要操作
					{
						ListNode *nex = it->next;
						it->next = nex->next;
						nex->next = pre->next;
						pre->next = nex;
						--temp;
					}
					break;
				}
				// 非常巧妙的翻转下一个 节点的思路
				it->next = nex->next;
				nex->next = pre->next;
				pre->next = nex;
				--temp;
			}

		}
		return fake_head->next;
	}
};