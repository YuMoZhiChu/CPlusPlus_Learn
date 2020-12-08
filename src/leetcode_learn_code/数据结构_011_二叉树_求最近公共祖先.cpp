/**
 * Definition for a binary tree node.
 * struct TreeNode_LCA {
 *     int val;
 *     TreeNode_LCA *left;
 *     TreeNode_LCA *right;
 *     TreeNode_LCA(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
 // 力扣
 // https://leetcode-cn.com/problems/lowest-common-ancestor-of-a-binary-tree/
 // 思路
 // https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.3-shou-ba-shou-shua-er-cha-shu-xun-lian-di-gui-si-wei/gong-gong-zu-xian
 // 思路, 这种二叉树问题
 // 框架一定是 
 // do(root, xxx)
 //     do(root->left, xxx)
 //     do(root->right, xxx)
 // 他们一定存在一个类似 dp 的递推关系
 // 完善之后, 就能解出这道题

struct TreeNode_LCA {
	int val;
	TreeNode_LCA *left;
	TreeNode_LCA *right;
	TreeNode_LCA(int x) : val(x), left(nullptr), right(nullptr) {}
};

class Solution {
public:
	TreeNode_LCA* lowestCommonAncestor(TreeNode_LCA* root, TreeNode_LCA* p, TreeNode_LCA* q) {
		if (!root) return nullptr;
		if (root == p || root == q) return root;
		TreeNode_LCA *left_result = lowestCommonAncestor(root->left, p, q);
		TreeNode_LCA *right_result = lowestCommonAncestor(root->right, p, q);
		if (left_result && right_result)
		{
			return root;
		}
		if (!left_result && !right_result)
		{
			return nullptr;
		}
		return left_result ? left_result : right_result;
	}
};