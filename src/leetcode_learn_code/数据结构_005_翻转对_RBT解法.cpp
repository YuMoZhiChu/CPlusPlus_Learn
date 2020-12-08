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
// 红黑树
// https://www.jianshu.com/p/e136ec79235c
// STL 源码剖析 第5章, 有 AVL 树 和 红黑树 的实现

#include<algorithm>
using std::max;

#include<vector>
using std::vector;

#include<queue>
using std::queue;

#include<string>
using std::string;

#include<iostream>
using std::cout;
using std::endl;

typedef bool _my_rb_tree_color_type;
const _my_rb_tree_color_type _my_rb_tree_red = false; // 红色为0
const _my_rb_tree_color_type _my_rb_tree_black = true; // 黑色为1

struct MyRBTreeNode {
	MyRBTreeNode(int _val) :val(_val), node_num(1), color(false), left(nullptr), right(nullptr), parent(nullptr) {}
	int val;
	int node_num; // 记录个数, 用于节省时间
	_my_rb_tree_color_type color; // 颜色, 默认的空节点是 红色 (因为加入一个新节点, 应该是红色, 根节点除外)
	MyRBTreeNode *left;
	MyRBTreeNode *right;
	MyRBTreeNode *parent;
};

// 获取节点个数, 因为做旋转时, 会有节点个数的变化, 所以要重新修正一次
inline int GetNodeNum(MyRBTreeNode *root)
{
	return (root->left ? root->left->node_num : 0) + (root->right ? root->right->node_num : 0) + 1;
}

// 获取是左边还是右边
// 注意, 这个对于 root 是叶子节点时, 是分辨不出来左右的
// 只有在 node 新建之后, 才能做出正确的判断
inline bool IsLeft(MyRBTreeNode *root, MyRBTreeNode *node)
{
	return node == root->left;
}

inline MyRBTreeNode* GetAnother(MyRBTreeNode *root, MyRBTreeNode *node)
{
	if (IsLeft(root, node)) return root->right;
	return root->left;
}

// 获取节点的颜色
inline _my_rb_tree_color_type GetColor(MyRBTreeNode *node)
{
	if (node == nullptr) return _my_rb_tree_black;
	return node->color;
}

// 相比 AVL 树, 我们还需要注意考量, parent 指针的位置
// 右旋操作
//      C
//     /
//    B          ->        B
//   /                    / \
//  A                    A   C
MyRBTreeNode* RightRotation(MyRBTreeNode *C)
{
	MyRBTreeNode *B = C->left;
	if (C->parent) {
		MyRBTreeNode *Head = C->parent;
		if (C == Head->left)
		{
			Head->left = B;
			B->parent = Head;
		}
		else {
			Head->right = B;
			B->parent = Head;
		}
	}
	else {
		B->parent = nullptr;
	}
	MyRBTreeNode *temp = B->right;
	B->right = C;
	C->parent = B;
	C->left = temp;
	if (temp) temp->parent = C;

	// 节点数修改, 显然, 这里影响到了 B,C 的节点数, 要进行一次更新
	C->node_num = GetNodeNum(C);
	B->node_num = GetNodeNum(B);

	return B;
}

// 相比 AVL 树, 我们还需要注意考量, parent 指针的位置
// 左旋操作
//    C
//     \
//      B       ->        B
//       \               / \
//        A             C   A
MyRBTreeNode* LeftRotation(MyRBTreeNode *C)
{
	MyRBTreeNode *B = C->right;
	if (C->parent) {
		MyRBTreeNode *Head = C->parent;
		if (C == Head->left)
		{
			Head->left = B;
			B->parent = Head;
		}
		else {
			Head->right = B;
			B->parent = Head;
		}
	}
	else {
		B->parent = nullptr;
	}

	MyRBTreeNode *temp = B->left;
	B->left = C;
	C->parent = B;
	C->right = temp;
	if (temp) temp->parent = C;

	// 节点数修改, 显然, 这里影响到了 B,C 的节点数, 要进行一次更新
	C->node_num = GetNodeNum(C);
	B->node_num = GetNodeNum(B);

	return B;
}

class MyRBTree
{
public:
	MyRBTree() :Root(nullptr) {}

	// 调整函数, 我们在插入之后的情况下, 对节点进行调整
	void Adjust(MyRBTreeNode *P, MyRBTreeNode *X)
	{
		// P 是 红节点, 不用担心越界的情况, 因为 红节点 不可能是 Root 节点, 所以 G 肯定存在
		MyRBTreeNode *G = P->parent;
		MyRBTreeNode *GG = G->parent; // 这个节点, 可能是空, 表明 G 就是 Root 节点
		MyRBTreeNode *S = GetAnother(G, P);
		if (GetColor(S) == _my_rb_tree_black)
		{
			// 如果 S 是黑色
			if (IsLeft(G, P))
			{
				// 左侧情况
				if (IsLeft(P, X))
				{
					// 同为左侧, 外侧情况
					// 一次右旋
					G = RightRotation(G); // P 和 G 的 node_num 记录在这里做了修改
					// 改变颜色
					G->color = _my_rb_tree_black;
					G->right->color = _my_rb_tree_red;
				}
				else {
					// 左右, 内侧情况
					// 一次左旋
					P = LeftRotation(P); // P - node_num 记录在这里做了修改
					// 变色
					P->color = _my_rb_tree_black;
					P->parent->color = _my_rb_tree_red;
					// 再一次右旋
					G = RightRotation(G);
				}
			}
			else {
				// 右侧情况
				if (IsLeft(P, X))
				{
					// 右左, 内侧情况
					// 一次右旋
					P = RightRotation(P);
					// 变色
					P->color = _my_rb_tree_black;
					P->parent->color = _my_rb_tree_red;
					// 再一次左旋
					G = LeftRotation(G);
				}
				else {
					// 右右, 一次左旋即可
					G = LeftRotation(G);
					G->color = _my_rb_tree_black;
					G->left->color = _my_rb_tree_red;
				}
			}
			// 在这些操作中, 有可能改动到 Root 节点, 所以这么处理
			if (GG == nullptr)
			{
				Root = G;
			}
			return;
		}
		else {
			// 如果 S 是红色
			// 那么 P,S 是红节点, G 是黑节点
			// 直接变色
			if (GG) G->color = _my_rb_tree_red; // 如果 G 是根节点的话, 应该是 黑色
			P->color = _my_rb_tree_black;
			S->color = _my_rb_tree_black;
			// 把 G 节点, 当成一个新的节点来调整
			if (GG && GG->color == _my_rb_tree_red)
			{
				if (P) P->node_num = GetNodeNum(P);
				if (G) G->node_num = GetNodeNum(G);
				Adjust(GG, G);
			}
		}
		// 因为我们修改了节点的顺序, 所以需要更新一波, 节点的 node_num 数据
		if (P) P->node_num = GetNodeNum(P);
		if (G) G->node_num = GetNodeNum(G);
	}

	// P 父节点位置, P 不可能为 nullptr 传入
	void Insert(MyRBTreeNode *P, int val)
	{
		if (Root == nullptr)
		{
			// 根节点初始化
			Root = new MyRBTreeNode(val);
			Root->color = _my_rb_tree_black; // 跟节点是黑色的
			return;
		}

		MyRBTreeNode *X = nullptr;
		if (val < P->val)
		{
			if (P->left)
			{
				Insert(P->left, val);
				if (P) P->node_num = GetNodeNum(P);
				return;
			}
			else {
				// 先插入一个红节点再说
				X = new MyRBTreeNode(val);
				X->parent = P;
				P->left = X;
			}
		}
		else {
			if (P->right)
			{
				Insert(P->right, val);
				if (P) P->node_num = GetNodeNum(P);
				return;
			}
			else {
				// 先插入一个红节点再说
				X = new MyRBTreeNode(val);
				X->parent = P;
				P->right = X;
			}
		}

		// 处理 X-P 关系
		// 黑节点自然插入
		if (P->color == _my_rb_tree_black) {
			P->node_num = GetNodeNum(P);
			return;
		}

		Adjust(P, X);
	}

	void PrintTree()
	{
		cout << "--------start---------" << endl;
		struct Msg {
			Msg(MyRBTreeNode *_node, int _level) :node(_node), level(_level) {}
			MyRBTreeNode *node;
			int level;
		};
		queue<Msg> q;
		q.emplace(Root, 0);
		int print_level = -1;
		while (!q.empty())
		{
			auto temp = q.front();
			q.pop();
			if (print_level != temp.level)
			{
				print_level = temp.level;
				cout << endl;
				cout << "LeveL " << print_level << " : ";
			}
			else {
				cout << " ";
			}
			if (temp.node == nullptr)
			{
				cout << "NULL";
			}
			else {
				cout << temp.node->val << "_" << temp.node->node_num << "_";
				string color_str;
				if (temp.node->color == _my_rb_tree_black) color_str = "B";
				else color_str = "R";
				cout << color_str;
				q.emplace(temp.node->left, temp.level + 1);
				q.emplace(temp.node->right, temp.level + 1);
			}
		}
		cout << endl << "######--end--######" << endl;
	}

	MyRBTreeNode *Root;
};

// RB树的删除
void Delete(MyRBTreeNode *&root, int val)
{

}

// 遍历找复合条件的值
int FindIfBigger(MyRBTreeNode *root, int &judge)
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
		MyRBTree tree;
		for (int i = nums.size() - 1; i >= 0; --i)
		{
			// 使用普通的树-也会超时
			result += FindIfBigger(tree.Root, nums[i]);
			tree.Insert(tree.Root, nums[i]);
			//cout << endl << "----------------> Insert " << nums[i] << endl;
			//tree.PrintTree();
		}
		return result;
	}
};

// 测试数据
//  int main()
//  {
//  	Solution().reversePairs({18,3,1,25,5,1,20,13,2,7,19,10,13,25,3,23,13,5,10,15,11,15,22,9,10,8,18,0 });
//  }

 //// 测试数据
 //int main()
 //{
 //	// Solution().reversePairs({ 12,3,0,7,0,5 });
	//MyRBTreeNode *root = nullptr;
	//Insert(root, root, 3);
	//Insert(root, root, 2);
	//Insert(root, root, 4);
	//Insert(root, root, 1);
	//// Delete(root, 3);

	///*MyTreeNode *root = nullptr;
	//Insert(root, 3);
	//Insert(root, 2);
	//Insert(root, 5);
	//Insert(root, 4);
	//Delete(root, 3);*/

	// int break_int = 0;
 //}