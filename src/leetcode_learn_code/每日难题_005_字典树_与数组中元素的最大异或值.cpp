// 力扣
// https://leetcode-cn.com/problems/maximum-xor-with-an-element-from-array/
// 题解思路
// 字典树"01"

#include<vector>
using std::vector;

#include<algorithm>
using std::min;

// 这颗树 总共用 31 个位置 (30~0)
// 最开始是高位
struct DictTreeNode
{
	DictTreeNode() { min_val = INT_MAX; }
	int min_val;
	// 初始化, 2 个空节点
	DictTreeNode* children[2]{ nullptr, nullptr };
};

// 注意, 根节点是不带 0-1 信息的
DictTreeNode *Root;

void Initial()
{
	Root = new DictTreeNode();
}

void Insert(DictTreeNode *root, int val)
{
	// 每个 val 都要走一次
	for (int i = 30; i >= 0; --i)
	{
		int val_at_i = (val & (1 << i)) ? 1 : 0;
		if (!root->children[val_at_i]) root->children[val_at_i] = new DictTreeNode();
		root = root->children[val_at_i];
		root->min_val = min(root->min_val, val); // 记录这条分支上的最小值
	}
}

// 在这里, Root 更新一下最小信息
inline void UpdateRootMinVal()
{
	if (Root->children[0]) Root->min_val = Root->children[0]->min_val;
	if (Root->children[1])
		Root->min_val = min(Root->min_val, Root->children[1]->min_val);
}

// 在 root 中检索 x 或者 m
void Search(DictTreeNode *root, int &result, int x, int m)
{
	if (m < root->min_val) return;
	result = 0; // 一定有一个解, 初始化为 0
	// 这是一定走 30 次, 所以不用递归
	for (int i = 30; i >= 0; --i)
	{
		if (x & (1 << i))
		{
			// 如果 x在第i个位置是 1, 那么我们做 XOR, 尽可能选择 0(这样的结果就会大)
			if (root->children[0])
			{
				// 这个选择, 是向小了走, 所以如果走到这一步有解, 就一定有解
				root = root->children[0];
				// result 的第 i 位设置为 1 (x 这一位是1, 我们取的 这一位是 0, XOR 结果是1))
				result ^= (1 << i);
			}
			else if (!root->children[1] || root->children[1]->min_val > m)
			{
				// 如果没有 1 节点, 或者 1 这边没有最小值的解
				result = -1; // 直接没解
				return;
			}
			else {
				// 只能走 1
				root = root->children[1];
				// result 的第 i 位设置为 0, 就不写了
			}
		}
		else {
			// 如果 x在第i个位置是 0, 那么我们做 XOR, 尽可能选择 1(这样的结果就会大)
			if (root->children[1] && root->children[1]->min_val <= m)
			{
				// 因为这一步是往大了走, 所以我们需要检测, 这一分支的最小值, 是否满足 不大于 m 的情况(这样才有解)
				root = root->children[1];
				result ^= (1 << i);
			}
			else if (root->children[0])
			{
				// 走0吧
				root = root->children[0];
			}
			else {
				result = -1; // 直接没解
				return;
			}
		}
	}
}

class Solution {
public:
	vector<int> maximizeXor(vector<int>& nums, vector<vector<int>>& queries) {
		Initial();
		for (int num : nums)
		{
			// 将 num 压入树中
			Insert(Root, num);
		}
		UpdateRootMinVal();
		vector<int> result_vec;
		for (auto q : queries)
		{
			int x = q[0];
			int m = q[1];
			int result = -1;
			Search(Root, result, x, m);
			result_vec.push_back(result);
		}
		return result_vec;
	}
};