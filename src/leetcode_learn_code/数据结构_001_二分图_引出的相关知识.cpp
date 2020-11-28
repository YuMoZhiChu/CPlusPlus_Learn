// 力扣
// https://leetcode-cn.com/problems/is-graph-bipartite/

// 学习
// https://blog.csdn.net/qq_40061421/article/details/82751020
// https://www.cnblogs.com/graytido/p/10809211.html
// 这是图相关的基础知识, 当然, 这道题只是用于判断是否是二分图, 深搜或广搜可以搞定
// 拓展知识
// 二分图的 最大匹配 凶算法-交换增光路
// 最大流计算 - 最大流算法-增加返边（允许反悔）(一次发一次流, 但是可以反悔)
//              Dinc https://www.zhihu.com/question/263856769 
//              相比于 增加返边, 多了2点, 1-给s-t排序(一次广搜 N) 2-(一次多次发送流)

#include<vector>
using std::vector;

#include<stack>
using std::stack;

class Solution {
public:
	bool isBipartite(vector<vector<int>>& graph) {
		if (graph.empty()) return true;
		// 染色法
		vector<int> record_array(graph.size(), 0); // 0 表示没染色, 1,-1 表示染色
		stack<int> s;
		for (int i = 0; i < record_array.size(); ++i) {
			if (record_array[i] != 0) continue;
			s.push(i);
			record_array[i] = 1;
			while (!s.empty())
			{
				int top = s.top();
				s.pop();
				for (auto to_point : graph[top])
				{
					if (record_array[to_point] == 0)
					{
						record_array[to_point] = -record_array[top];
						s.push(to_point);
						continue;
					}
					if (record_array[to_point] == record_array[top])
						return false;
				}
			}
		}
		return true;
	}
};