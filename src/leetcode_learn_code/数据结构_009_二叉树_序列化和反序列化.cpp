/**
 * Definition for a binary tree node.
 * struct TreeNode_SD {
 *     int val;
 *     TreeNode_SD *left;
 *     TreeNode_SD *right;
 *     TreeNode_SD(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */

 // 力扣
 // https://leetcode-cn.com/problems/serialize-and-deserialize-binary-tree/
 // 学习
 // https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.3-shou-ba-shou-shua-er-cha-shu-xun-lian-di-gui-si-wei/er-cha-shu-de-xu-lie-hua

#include<string>
using std::string;

struct TreeNode_SD {
	int val;
	TreeNode_SD *left;
	TreeNode_SD *right;
	TreeNode_SD(int x) : val(x), left(NULL), right(NULL) {}
};

class Codec {
public:

	// Encodes a tree to a single string.
	string serialize(TreeNode_SD* root) {
		if (!root) return "#,";
		string result = std::to_string(root->val) + ",";
		result += serialize(root->left);
		result += serialize(root->right);
		return result;
	}

	void deserialize_root(TreeNode_SD *&root, string &data, int &index)
	{
		if (data[index] == '#')
		{
			index += 2;
			return;
		}
		int next_comma = data.find(',', index);
		root = new TreeNode_SD(atoi(data.substr(index, next_comma - index).c_str()));
		index = next_comma + 1;
		deserialize_root(root->left, data, index);
		deserialize_root(root->right, data, index);
	}

	// Decodes your encoded data to tree.
	TreeNode_SD* deserialize(string data) {
		TreeNode_SD *Root = nullptr;
		int index = 0;
		deserialize_root(Root, data, index);
		return Root;
	}
};

// Your Codec object will be instantiated and called as such:
// Codec ser, deser;
// TreeNode_SD* ans = deser.deserialize(ser.serialize(root));