// struct ListNode{
//     int val;
//     ListNode *next;
// };
// 力扣
// https://leetcode-cn.com/problems/reverse-pairs/
// 思路, 用树优化, 这里我们先用普通的树
// 学习思路
// AVL 树
// https://blog.csdn.net/zhaohong_bo/article/details/90311112

#include<algorithm>
using std::max;

#include<vector>
using std::vector;

struct MyTreeNode {
	MyTreeNode(int _val) :val(_val), node_num(1), height(0), left(nullptr), right(nullptr) {}
	int val;
	int node_num; // 记录个数, 用于节省时间
	int height; // 平衡树, 高度记录
	MyTreeNode *left;
	MyTreeNode *right;
};

// 获取高度操作
inline int GetHeight(MyTreeNode *root)
{
	return root ? root->height : -1; // 空指针的高度是 -1
}

// 获取高度差, 我们这里是默认, 左边减去右边
inline int GetAVLValue(MyTreeNode *root)
{
	return GetHeight(root->left) - GetHeight(root->right);
}

// 获取节点个数, 因为AVl做旋转时, 会有节点个数的变化, 所以要重新修正一次
inline int GetNodeNum(MyTreeNode *root)
{
	return (root->left ? root->left->node_num : 0) + (root->right ? root->right->node_num : 0) + 1;
}

// 右旋操作 C:2 B:1
//      C
//     /
//    B          ->        B
//   /                    / \
//  A                    A   C
void RightRotation(MyTreeNode *&root)
{
	MyTreeNode *temp = root;
	root = root->left;
	temp->left = root->right;
	root->right = temp;

	// 高度修改
	root->right->height = max(GetHeight(root->right->left), GetHeight(root->right->right)) + 1;
	root->height = max(GetHeight(root->left), GetHeight(root->right)) + 1;
	// 为什么不影响更多的父亲节点呢?
	// 因为这里是 A 先插入, 导致不平衡的
	// 所以在插入之前是  D-C-B (这里的D是2, 只看左半边)
	// 插入之后 D-C-B-A 再平衡, D-(BAC) 所以还是 2
	// 因此不影响更多的父节点, 删除节点时, 也是同理

	// 节点数修改, 显然, 这里影响到了 B,C 的节点数, 要进行一次更新
	root->right->node_num = GetNodeNum(root->right);
	root->node_num = GetNodeNum(root);
}

// 左旋操作 A:-2 B:-1
//    A
//     \
//      B       ->        B
//       \               / \
//        C             A   C
void LeftRotation(MyTreeNode *&root)
{
	MyTreeNode *temp = root;
	root = root->right;
	temp->right = root->left;
	root->left = temp;

	// 高度修改
	root->left->height = max(GetHeight(root->left->left), GetHeight(root->left->right)) + 1;
	root->height = max(GetHeight(root->left), GetHeight(root->right)) + 1;
	// 节点数修改
	root->left->node_num = GetNodeNum(root->left);
	root->node_num = GetNodeNum(root);
}

// 先左旋, 再右旋 C:2 A:-1
//      C                   C  
//     /                   /
//    A      -A左旋->     B   -C右旋->
//     \                 / 
//      B               A   
void Left_RightRotation(MyTreeNode *&root)
{
	LeftRotation(root->left);
	RightRotation(root);
}

// 先右旋, 再左旋 A:-2 C:1
//    A                  A
//     \                  \
//      C   -C右旋->       B    -A左旋->
//     /                    \
//    B                      C
void Right_LeftRotation(MyTreeNode *&root)
{
	RightRotation(root->right);
	LeftRotation(root);
}

// 平衡树的插入
void Insert(MyTreeNode *&root, int val)
{
	if (root == nullptr)
	{
		root = new MyTreeNode(val);
		return;
	}
	if (val < root->val) {
		Insert(root->left, val);
		// 因为是插入左边, 所以只有可能是, 左边变高了的情况
		if (GetAVLValue(root) == 2)
		{
			if (GetAVLValue(root->left) > 0)
			{
				RightRotation(root);
			}
			else {
				Left_RightRotation(root);
			}
		}
		else {
			// 旋转会自动更新 node_num, 非旋转情况补上
			++root->node_num;
		}
	}
	else {
		Insert(root->right, val);
		// 因为是插入右边的情况
		if (GetAVLValue(root) == -2)
		{
			if (GetAVLValue(root->right) < 0)
			{
				LeftRotation(root);
			}
			else {
				Right_LeftRotation(root);
			}
		}
		else {
			// 旋转会自动更新 node_num, 非旋转情况补上
			++root->node_num;
		}
	}
	// 最后, 更新高度 - 在结尾更新即可
	root->height = max(GetHeight(root->left), GetHeight(root->right)) + 1;
}

// 平衡树的删除
void Delete(MyTreeNode *&root, int val)
{
	if (!root) return; // 空的直接删除
	if (val < root->val)
	{
		// 从左边删除
		Delete(root->left, val);
		// 因为左边删除了, 所以可能会-1 有可能变成 -2
		if (GetAVLValue(root) == -2)
		{
			if (GetAVLValue(root->right) < 0)
			{
				LeftRotation(root);
			}
			else {
				Right_LeftRotation(root);
			}
		}
		else {
			// 旋转会自动更新 node_num, 非旋转情况补上
			--root->node_num;
		}
	}
	else if (val > root->val)
	{
		// 从右边删除
		Delete(root->right, val);
		// 因为左边删除了, 所以可能会+1 有可能变成 +2
		if (GetAVLValue(root) == 2)
		{
			if (GetAVLValue(root->left) > 0)
			{
				RightRotation(root);
			}
			else {
				Left_RightRotation(root);
			}
		}
		else {
			// 旋转会自动更新 node_num, 非旋转情况补上
			--root->node_num;
		}
	}
	else if (root->left && root->right)
	{
		// 找到要删除的节点, 但是这个节点 左右都有节点
		// 我们把这个流程改成, 直接从右子树中, 获取最小的一个数据, 进行替换, 再删除右子树的数据
		MyTreeNode *it = root->right;
		while (it)
		{
			it = it->left;
		}
		root->val = it->val;
		Delete(root->right, root->val); // 删除右子树上的数据
		// 这一步非常巧妙, 因为已知, root->right 目前是平衡的, 删除它的一个子...子节点
		// root->right 肯定会做自平衡, 然而 AVL 树的特点就是, 子节点的自平衡, 不会影响到当前父节点
		// 同理, 因为影响不到, 所以这里的个数要手动减去1
		--root->node_num;
	}
	else {
		// 找到要删除的节点, 但这个节点只有一个孩子节点, 或者就是叶子节点
		// 这里直接替换, 不需要考虑 node_num 问题
		root = (root->left ? root->left : root->right);
	}

	// 注意更新高度
	if (root)
		root->height = GetHeight(root);
}

// 遍历找复合条件的值
int FindIfBigger(MyTreeNode *root, int &judge)
{
	if (root == nullptr) return 0;
	if (2 * long(root->val) < judge)
	{

		return 1 + FindIfBigger(root->right, judge) + (root->left ? root->left->node_num : 0);
	}
	else {
		return FindIfBigger(root->left, judge);
	}
}

class Solution {
public:
	int reversePairs(vector<int> nums) {
		if (nums.size() <= 1) return 0;
		int result = 0;
		MyTreeNode *root = nullptr;
		for (int i = nums.size() - 1; i >= 0; --i)
		{
			// 使用普通的树-也会超时
			result += FindIfBigger(root, nums[i]);
			Insert(root, nums[i]);
		}
		return result;
	}
};

// // 测试数据
// int main()
// {
// 	Solution().reversePairs({ 12,3,0,7,0,5 });
// }