// 力扣
// https://leetcode-cn.com/problems/checking-existence-of-edge-length-limited-paths/
// 题解学习, 并查集思路
// 这里利用并查集做了思路转化, 非常的合理, 值得学习

#include<vector>
using std::vector;

#include<algorithm>
using std::sort;

#include<numeric>
using std::iota;

// 并查集模板，包含路径压缩（参考 findset 函数）以及按秩合并（参考 sz 变量）
class UF {
public:
	vector<int> fa;
	vector<int> sz;
	int n;
	int comp_cnt; // 连通域数量

public:
	UF(int _n) : n(_n), comp_cnt(_n), fa(_n), sz(_n, 1) {
		iota(fa.begin(), fa.end(), 0); // 批量赋值接口, value 也会递增
	}

	int findset(int x) {
		// 求森林的父节点
		while (fa[x] != x)
		{
			fa[x] = fa[fa[x]]; // 同时进行压缩
			x = fa[x];
		}
		return x;
	}

	bool unite(int x, int y) {
		x = findset(x);
		y = findset(y);
		// 如果是已经联通的, 就直接返回
		if (x == y) {
			return false;
		}
		// 选择对小的进行联通, 平衡树的左右大小
		if (sz[x] < sz[y]) {
			std::swap(x, y);
		}
		fa[y] = x;
		sz[x] += sz[y]; // 大小叠加
		--comp_cnt;
		return true;
	}

	bool connected(int x, int y) {
		x = findset(x);
		y = findset(y);
		return x == y;
	}
};



class Solution {
public:
	vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>>& edgeList, vector<vector<int>>& queries) {
		// 将 queries 按照边权限制从小到大排序
		vector<int> qid(queries.size());
		iota(qid.begin(), qid.end(), 0);
		sort(qid.begin(), qid.end(), [&](int i, int j) {
			return queries[i][2] < queries[j][2];
		});

		// 将 edgeList 按照边权从小到大排序
		sort(edgeList.begin(), edgeList.end(), [](const auto& e1, const auto& e2) {
			return e1[2] < e2[2];
		});

		// 并查集
		UF uf(n);

		int i = 0;
		vector<bool> ans(queries.size());
		for (int query : qid) {
			// 往并查集中添加边直到边权关系 dis_i < limit_j 不满足
			// 这里把问题转化成了, 在合理的情况下, 做一次联通
			// 而且这里 i 是递增的
			while (i < edgeList.size() && edgeList[i][2] < queries[query][2]) {
				uf.unite(edgeList[i][0], edgeList[i][1]);
				++i;
			}
			// 使用并查集判断连通性
			ans[query] = uf.connected(queries[query][0], queries[query][1]);
		}

		return ans;
	}
};
