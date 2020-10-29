//#include<iostream>
//using std::cin;
//using std::cout;
//using std::endl;
//
//
//struct ListNode {
//	int val;
//	ListNode *next;
//	ListNode(int x) : val(x), next(NULL) {}
//};
// 
//// 翻转链表
//ListNode* reverse(ListNode *head)
//{
//	ListNode *pre = NULL;
//	while (head->next)
//	{
//		ListNode* temp = head->next;
//		head->next = pre;
//		pre = head;
//		head = temp;
//	}
//	head->next = pre;
//	return head;
//}
//
//class Solution {
//public:
//	bool isPalindrome(ListNode* head) {
//		if (!head) return true;
//		if (!head->next) return true;
//		// 双指针遍历，迅速的找到中间指针
//		ListNode *slow = head, *fast = head;
//		while (fast && fast->next)
//		{
//			slow = slow->next;
//			fast = fast->next->next;
//		}
//		if (fast) slow = slow->next;
//		ListNode* right = reverse(slow);
//		while (right)
//		{
//			if (head->val != right->val)
//				return false;
//			head = head->next;
//			right = right->next;
//		}
//		return true;
//	}
//};
//
//int main()
//{
//	
//}
//
