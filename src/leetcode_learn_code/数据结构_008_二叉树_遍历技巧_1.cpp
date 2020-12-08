// 力扣
// https://leetcode-cn.com/problems/populating-next-right-pointers-in-each-node/
// 学习
// https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.3-shou-ba-shou-shua-er-cha-shu-xun-lian-di-gui-si-wei/er-cha-shu-xi-lie-1

// 非常巧妙的二叉树技巧


// Definition for a Node.
class Node {
public:
	int val;
	Node* left;
	Node* right;
	Node* next;

	Node() : val(0), left(nullptr), right(nullptr), next(nullptr) {}

	Node(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}

	Node(int _val, Node* _left, Node* _right, Node* _next)
		: val(_val), left(_left), right(_right), next(_next) {}
};


class Solution {
public:
	void connect_2_node(Node *root1, Node *root2)
	{
		if (root1 == nullptr || root2 == nullptr) return;
		root1->next = root2;
		connect_2_node(root1->left, root1->right);
		connect_2_node(root1->right, root2->left);
		connect_2_node(root2->left, root2->right);
	}

	Node* connect(Node* root) {
		if (!root) return root;
		connect_2_node(root->left, root->right);
		return root;
	}
};