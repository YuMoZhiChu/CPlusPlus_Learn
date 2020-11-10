// 力扣地址
// https://leetcode-cn.com/problems/count-of-range-sum/submissions/
// 线段树学习
// https://www.cnblogs.com/xenny/p/9801703.html

#include<vector>
using std::vector;

struct CNode {
	CNode(long _left, long _right, int _count) :
		left(_left), right(_right), count(_count),
		left_node(nullptr), right_node(nullptr) {}
	long left;
	long right;
	int count;
	CNode *left_node;
	CNode *right_node;
	inline bool is_leaf()
	{
		return count == 1; // 之所以不用 left==right 判断, 因为有可能出现重复的点
	}
};

inline bool judge_in(const long &value, const long &left, const long &upper)
{
	return value >= left && value <= upper;
}

// 传入根节点的意义, 方便拓展
CNode* InsertNode(CNode *root, CNode *now_node, long value)
{
	if (now_node->is_leaf())
	{
		// 如果这是一个叶子节点, 那么直接拓展成一个Y型节点即可
		now_node->count = 2;
		long left, right;
		if (value <= now_node->left)
		{
			left = value;
			right = now_node->left;
		}
		else {
			left = now_node->left;
			right = value;
		}
		now_node->left = left;
		now_node->right = right;
		// 建立两个子节点
		now_node->left_node = new CNode(left, left, 1);
		now_node->right_node = new CNode(right, right, 1);
		return now_node;
	}
	else {
		// 否则, 我们递归建立子树

		// 在当前节点的范围内
		if (judge_in(value, now_node->left, now_node->right))
		{
			// 直接插入即可
			++now_node->count;
			// 左右插入
			// 处理重叠问题, 只会插入其中一个子节点
			if (judge_in(value, now_node->left_node->left, now_node->left_node->right))
			{
				InsertNode(root, now_node->left_node, value);
				return now_node;
			}
			if (judge_in(value, now_node->right_node->left, now_node->right_node->right))
			{
				InsertNode(root, now_node->right_node, value);
				return now_node;
			}
			// 如果2个都不在, 说明存在叶子节点, 选择叶子节点插入
			// 如果是两个都是叶子节点, 选择第一个
			// if (now_node->left_node->is_leaf())
			// {
			//     InsertNode(root, now_node->left_node, value);
			//     return now_node;
			// }
			// if (now_node->right_node->is_leaf())
			// {
			//     InsertNode(root, now_node->right_node, value);
			//     return now_node;
			// }
			// 如果都不是, 那说明是这样的情形 [] a [] , [] 可以是叶子节点 的情况也包含在这里
			// 选一个小的插入
			CNode *small_ptr;
			bool is_right = now_node->right_node->count < now_node->left_node->count;
			small_ptr = is_right ? now_node->right_node : now_node->left_node;
			small_ptr = InsertNode(small_ptr, small_ptr, value);
			// 接回到 now_node 上
			if (is_right)
				now_node->right_node = small_ptr;
			else
				now_node->left_node = small_ptr;
			return now_node;
		}
		else {
			// 如果不在范围内, 除非是根节点标志设置 当前节点 一样, 说明是对这个节点做拓展, 否则不管
			if (now_node == root)
			{
				// 根节点拓展
				// 新的value节点
				CNode *new_value_node = new CNode(value, value, 1);
				// 新的根节点
				CNode *new_root_node = new CNode(0, 0, root->count + 1);

				if (root->left > value)
				{
					// root 节点在右边
					new_root_node->left = value;
					new_root_node->left_node = new_value_node;
					new_root_node->right = root->right;
					new_root_node->right_node = root;
				}
				else {
					// root 节点在左边
					new_root_node->left = root->left;
					new_root_node->left_node = root;
					new_root_node->right = value;
					new_root_node->right_node = new_value_node;
				}
				return new_root_node;
			}
		}
	}
	return now_node;
}

// 查询的方法
int SearchIn(CNode *root, long lower, long upper)
{
	// 如果整个线段都在, 直接返回
	if (root->left >= lower && root->right <= upper) return root->count;
	// 拆分
	if (lower > root->right) return 0;
	if (upper < root->left) return 0;
	// 求且
	long new_lower = lower > root->left ? lower : root->left;
	long new_upper = upper > root->right ? root->right : upper;
	// 求子集的和
	return SearchIn(root->left_node, new_lower, new_upper) +
		SearchIn(root->right_node, new_lower, new_upper);
}

class Solution {
public:
	int countRangeSum(vector<int>& nums, int lower, int upper) {
		if (nums.empty()) return 0;
		// S[i][j] 可以表示成 sum[0~j] - sum[0~(i-1)] sum[-1] = 0
		// 那么问题转换成 sum[0~j] - sum[0~i-1] // i = -1 的时候 就是每个 sum 的值
		// 求sum
		int nums_size = nums.size();
		vector<long> sum_vector;
		long sum_temp = 0;
		for (int i = 0; i < nums_size; ++i)
		{
			sum_temp += nums[i];
			sum_vector.emplace_back(sum_temp); // 压入
		}
		// 在这里, 我们用 sum 建立一个线段树, 这颗线段树是最终应该是这样的
		//        root: [l, r] - 记录:n
		// 叶子节点就是: [a,a] - 1 表示这个区间只有 1 个点
		// 我们读入一个点 sum[j] 因为 s[j] - {0~s[j-1]} in [lower, upper]
		// 那么我们直接查询, 1 - sum[j] 是否在 [l,u] 中
		//                  2 - 查询 sum[0~j-1] 是否在 [sum[j]-upper, sum[j]-lower] 内
		// 所以线段树的操作就是: 
		// 读入一个树 -  1. 查询自身
		//              2. 线段树查询
		//             3. 插入这个节点

		// 建立根节点
		CNode *root = new CNode(sum_vector[0], sum_vector[0], 1);
		// 第一个数判断
		int result = 0;
		if (judge_in(sum_vector[0], lower, upper)) ++result;
		for (int i = 1; i < nums_size; ++i)
		{
			// 自身检查
			if (judge_in(sum_vector[i], lower, upper)) ++result;

			// 线段查询
			long new_lower = sum_vector[i] - upper;
			long new_upper = sum_vector[i] - lower;
			result += SearchIn(root, new_lower, new_upper);

			// 新节点插入
			root = InsertNode(root, root, sum_vector[i]);
		}
		return result;
	}
};