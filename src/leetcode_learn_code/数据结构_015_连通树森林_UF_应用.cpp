// 力扣
// https://leetcode-cn.com/problems/satisfiability-of-equality-equations/
// 学习
// https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.4-shou-ba-shou-she-ji-shu-ju-jie-gou/unionfind-suan-fa-ying-yong

#include<string>
using std::string;

#include<vector>
using std::vector;

class UnionFind
{
	int cap; // 联通的区域数
	int *parent;
	int *size;
public:
	UnionFind(int _cap) :cap(_cap)
	{
		parent = new int[cap];
		size = new int[cap];
		for (int i = 0; i < cap; ++i)
		{
			parent[i] = i; // 初始化, 自己指向自己
			size[i] = 1; // 初始化大小
		}
	}
	~UnionFind()
	{
		delete[] parent;
		delete[] size;
	}
	int find_parent(int p)
	{
		while (parent[p] != p)
		{
			parent[p] = parent[parent[p]]; // 压缩列表
			p = parent[p];
		}
		return p;
	}
	// 连接
	void connect(int p, int q)
	{
		int root_p = find_parent(p);
		int root_q = find_parent(q);
		if (root_p == root_q) return;
		if (size[root_p] > size[root_q])
		{
			// 小的连大的
			parent[root_q] = root_p;
			size[root_p] += size[root_q];
		}
		else {
			parent[root_p] = root_q;
			size[root_q] += size[root_p];
		}
		--cap;
	}
	// 判断是否连接
	bool is_connect(int p, int q)
	{
		int root_p = find_parent(p);
		int root_q = find_parent(q);
		return root_p == root_q;
	}
};

class Solution {
public:
	bool equationsPossible(vector<string>& equations) {
		UnionFind UF(26); // 26 个字母
		vector<string> not_equal_vec;
		for (string &equation : equations)
		{
			if (equation[1] == '=')
			{
				// 连接两个数组
				UF.connect(equation[0] - 'a', equation[3] - 'a');
			}
			else {
				not_equal_vec.push_back(equation);
			}
		}
		for (string &equation : not_equal_vec)
		{
			if (UF.is_connect(equation[0] - 'a', equation[3] - 'a'))
				return false;
		}
		return true;
	}
};