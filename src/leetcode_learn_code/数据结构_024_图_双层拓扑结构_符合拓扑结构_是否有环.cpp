// 力扣
// https://leetcode-cn.com/problems/sort-items-by-groups-respecting-dependencies/
// 思路, 先处理 组的拓扑
// 再处理组内拓扑

#include<vector>
using std::vector;

#include<stack>
using std::stack;

class Solution {
public:
	vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
		// 组和组的 边
		// 对于 -1 都作为一个单独的组来表示
		// 组内对 它拥有的组员的映射
		vector<vector<int>> group_to_item_vec(n + m, vector<int>());
		// 首先更新组的数量
		for (int i = 0; i < n; ++i)
		{
			if (group[i] == -1)
			{
				// 更新成1个新的组
				group[i] = m;
				++m; // 每有一个 -1 就新加 1 组
			}
			// 组 -> 拥有组员
			group_to_item_vec[group[i]].push_back(i);
		}

		// 组组拓扑
		// 组与组的连线
		vector<vector<int>> group_edges(m, vector<int>());
		// 组的入度记录
		vector<int> group_in_record(m, 0);

		// 组内拓扑
		// 组内的 item 连线
		// 这里记录的是 item 间的连线, 而且他们一定在一个组内
		vector<vector<int>> item_edges(n, vector<int>());
		// item 的入度记录
		vector<int> item_in_record(n, 0);

		for (int b = 0; b < n; ++b)
		{
			for (int a : beforeItems[b])
			{
				// a->b
				if (group[b] == group[a])
				{
					// 加入组内记录
					item_edges[a].push_back(b);
					++item_in_record[b];
				}
				else {
					// 加入组外记录
					group_edges[group[a]].push_back(group[b]);
					++group_in_record[group[b]];
				}
			}
		}

		// 处理组组关系
		vector<int> group_result;
		stack<int> group_can_visit;
		for (int i = 0; i < m; ++i)
		{
			if (group_in_record[i] == 0) group_can_visit.push(i);
		}
		while (!group_can_visit.empty())
		{
			int it = group_can_visit.top();
			group_can_visit.pop();
			group_result.push_back(it);
			for (int unlock : group_edges[it])
			{
				--group_in_record[unlock];
				if (group_in_record[unlock] == 0)
				{
					group_can_visit.push(unlock);
				}
			}
		}
		if (group_result.size() != m) return {};

		// 处理组内关系
		vector<int> result;
		for (int group : group_result)
		{
			// 处理组 group
			vector<int> item_result;
			stack<int> item_can_visit;
			for (int i = 0; i < group_to_item_vec[group].size(); ++i)
			{
				if (item_in_record[group_to_item_vec[group][i]] == 0)
					item_can_visit.push(group_to_item_vec[group][i]);
			}

			while (!item_can_visit.empty())
			{
				int it = item_can_visit.top();
				item_can_visit.pop();
				item_result.push_back(it);
				for (int unlock : item_edges[it])
				{
					--item_in_record[unlock];
					if (item_in_record[unlock] == 0)
					{
						item_can_visit.push(unlock);
					}
				}
			}
			if (item_result.size() != group_to_item_vec[group].size()) return {};
			for (int item : item_result)
			{
				result.push_back(item);
			}
		}
		return result;
	}
};