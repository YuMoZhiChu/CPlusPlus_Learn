/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

 // 力扣
 // https://leetcode-cn.com/problems/house-robber/

 // 学习
 // https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/qiang-fang-zi


struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
	TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
};

#include<algorithm>
using std::max;

#include<unordered_map>
using std::unordered_map;

class Solution {
public:
	// 这是系列的第3题, 是一个动归, 但是二叉树结构
	// 那么我们的动态递归就是
	// 这个 root 不选(两个儿子节点的dp), 和 这个 root 选(该root和 4个孙子节点的 dp)
	// dp[root] = max( dp[root->left]+dp[root->right], val[root] + dp[root->left->left+right]+dp[root->right->left+right])
	// 显然, 递归更合适遍历, 我们用一个 map 作为 memo 来表示
	int dp_search(TreeNode* root, unordered_map<TreeNode*, int> &memo)
	{
		if (!root) return 0;
		auto find_it = memo.find(root);
		if (find_it != memo.end())
		{
			return find_it->second;
		}
		int left_sub_result = 0;
		if (root->left)
		{
			left_sub_result = dp_search(root->left->left, memo) + dp_search(root->left->right, memo);
		}
		int right_sub_result = 0;
		if (root->right)
		{
			right_sub_result = dp_search(root->right->left, memo) + dp_search(root->right->right, memo);
		}
		int result = max(left_sub_result + right_sub_result + root->val,
			dp_search(root->left, memo) + dp_search(root->right, memo)
		);
		memo[root] = result; // memo 记录
		return result;
	}

	int rob(TreeNode* root) {
		unordered_map<TreeNode*, int> memo;
		return dp_search(root, memo);
	}
};