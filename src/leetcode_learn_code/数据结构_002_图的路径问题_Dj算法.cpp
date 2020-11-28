// 力扣
// https://leetcode-cn.com/problems/cheapest-flights-within-k-stops/

// 学习

// 思路
// Bellman-Ford - 其实就是动归
// https://www.cnblogs.com/fsmly/p/10224616.html
// 第二遍, Dj算法


#include<vector>
using std::vector;

#include<queue>
using std::priority_queue;

#include<map>
using std::map;

struct CNode {
	CNode(int _time, int _cost, int _pos) :time(_time), cost(_cost), pos(_pos) {}
	int time; // 对应 k
	int cost; // 对应消耗
	int pos; // 对应位置
	// 自定义比较函数
	// 必须要友元函数, 内置不行
	friend bool operator<(const CNode &lhs, const CNode &rhs)
	{
		// 优先考虑 cost
		// 这里, 我们要小的放前面
		if (lhs.cost == rhs.cost) return lhs.time > rhs.time;
		return lhs.cost > rhs.cost;
	}
	// bool operator<(const CNode &rhs)
	// {
	//     if (time != rhs.time) return time < rhs.time;
	//     return cost < rhs.cost;
	// }
};

struct RecordNode
{
	RecordNode(int _time, int _pos) :time(_time), pos(_pos) {}
	int time;
	int pos;
	// bool operator<(const RecordNode &other)
	// {
	//     if (time == other.time) return pos < other.pos;
	//     return time < other.time;
	// }
	friend bool operator<(const RecordNode &lhs, const RecordNode &rhs)
	{
		if (lhs.time == rhs.time) return lhs.pos < rhs.pos;
		return lhs.time < rhs.time;
	}
};

class Solution {
public:
	int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int K) {
		// 先转换图
		vector<vector<int>> graph(n, vector<int>(n, -1));
		for (auto &flight : flights)
		{
			graph[flight[0]][flight[1]] = flight[2];
		}

		// Dj 算法, 为了减少消耗, 我们会使用一个 优先队列
		// 因为 Dj 算法要时刻保证, 我们并入集合的是最小的那个

		priority_queue<CNode, vector<CNode>> pq;
		pq.emplace(-1, 0, src); // 压入, 我们初始次数设置为 -1
		int result = INT_MAX;
		map<RecordNode, int> record; // 记录已经访问的最小集合
		record[RecordNode(-1, src)] = 0; // 记录起点
		while (!pq.empty())
		{
			CNode temp = pq.top();
			pq.pop();
			if (temp.time > K) continue; // 可能有混合的情况, 所以不能直接break
			// 如果这次记录, 已经存在比它小的内容了, 可以直接跳过
			auto find_it = record.find(RecordNode(temp.time, temp.pos));
			if (find_it != record.end() && temp.cost > find_it->second) continue;
			if (temp.pos == dst)
			{
				return temp.cost;
				// if (temp.cost < result) result = temp.cost;
				// continue;
			}
			// 尝试合并每个点
			for (int i = 0; i < n; ++i)
			{
				// temp.pos --> i
				if (graph[temp.pos][i] > 0)
				{
					// 查 经过 time+1 次, 到达 i, 和这次比较
					auto find_it = record.find(RecordNode(temp.time + 1, i));
					int now_cost = temp.cost + graph[temp.pos][i];
					if (find_it == record.end() || now_cost < find_it->second)
					{
						record[RecordNode(temp.time + 1, i)] = now_cost;
						pq.emplace(temp.time + 1, now_cost, i);
					}
				}
			}

		}
		return -1;
	}
};