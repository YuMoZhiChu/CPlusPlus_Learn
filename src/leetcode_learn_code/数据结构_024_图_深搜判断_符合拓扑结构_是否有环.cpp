// 力扣
// https://leetcode-cn.com/problems/course-schedule/
// 图相关
// 广搜和深搜 2 种做法
// 使用出度和入度的两种做法

#include<vector>
using std::vector;

#include<stack>
using std::stack;

class Solution {
public:
	// 深搜做法
	bool dfs(vector<vector<int>> &edges, vector<int> &out_record, vector<int> &visit_state, int now_pos)
	{
		if (visit_state[now_pos] == 2) return true;
		// 出度为 0 终点
		if (out_record[now_pos] == 0)
		{
			visit_state[now_pos] = 2;
			return true;
		}
		for (int &to_pos : edges[now_pos])
		{
			if (visit_state[to_pos] == 2) continue;
			if (visit_state[to_pos] == 1) return false;
			--out_record[now_pos];
			visit_state[now_pos] = 1;
			if (!dfs(edges, out_record, visit_state, to_pos))
			{
				return false;
			}
		}
		visit_state[now_pos] = 2;
		return true;
	}

	bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
		vector<vector<int>> edges(numCourses, vector<int>());
		vector<int> out_record(numCourses, 0);
		for (auto &pq : prerequisites)
		{
			edges[pq[1]].push_back(pq[0]); // 记录 a -> b
			++out_record[pq[1]]; // 出度+1
		}

		vector<int> visit_state(numCourses, 0);

		for (int i = 0; i < numCourses; ++i)
		{
			if (!dfs(edges, out_record, visit_state, i)) return false;
		}
		return true;
	}
};