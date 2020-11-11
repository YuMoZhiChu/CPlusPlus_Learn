// 力扣地址
// https://leetcode-cn.com/problems/freedom-trail/

// 尝试解法, 递归深搜解 - 果然深搜不行
// 尝试动归解

// 动归解可行, 核心在于, 让递归，只跟上一次有关 （利用位置的特性 -> 不需要全局遍历

// map unorder_map 的自定义 key 写法

#include<string>
using std::string;

#include<unordered_map>
using std::unordered_map;

#include<vector>
using std::vector;

// struct loc {
//     int x;
//     int y;
//     int val;

//     bool operator<(const loc &l1) const{  // 注意重载<时的这里两个const都不能少 这个是 map 的写法
//         if (this->x == l1.x) {
//             return this->y < l1.y;
//         } else {
//             return this->x < l1.x;
//         }
//     }

// };
// map<loc, int> m;

// CNode 节点
struct CNode {
	CNode(int _pos_start, int _pos_end) :
		pos_start(_pos_start), pos_end(_pos_end) {}
	int pos_start;
	int pos_end;
	friend struct std::hash<CNode>;
	bool operator==(const CNode &other) const
	{
		return pos_start == other.pos_start && pos_end == other.pos_end;
	}
};

namespace std
{
	template <>
	struct std::hash<CNode>
	{
		int operator()(const CNode& v) const
		{
			return std::hash<int>{}(v.pos_start) ^ std::hash<int>{}(v.pos_end) << 1;
		}
	};
}

class Solution {
public:
	int findRotateSteps(string ring, string key) {
		int ring_size = ring.size();
		// 构建一个查询字典
		unordered_map<char, vector<int>> key_map;
		for (int i = 0; i < ring_size; ++i)
		{
			key_map[ring[i]].push_back(i); // 记录位置
		}
		// 动归思路
		// dp[i][j] 代表从 ring[i] - ring[j] 播出的最短距离
		// 这需要注意的是, dp[i][j] 会存储一系列的结果, 长度是 i_pos_size * j_pos_size, 即我们需要考虑每个的大小
		// 只有 dp[0][1] 有意义
		// dp[i][i] 是没有意义的
		vector<vector<unordered_map<int, int>>> dp;
		for (int i = 0; i < key.size() + 1; ++i)
		{
			// 创建dp[i]
			dp.push_back(vector<unordered_map<int, int>>());
			for (int j = 0; j < key.size() + 1; ++j)
			{
				// dp[i][j] 其实是一组数据
				dp[i].push_back(unordered_map<int, int>());
			}
		}
		// base 状态
		// dp[0][1] 表示从开始状态, 转到 ring[0] 的起始状态
		for (int pos : key_map[key[0]])
		{
			// 因为可以左右转动
			int min_step = (-pos + ring_size) % ring_size;
			min_step = min_step < pos ? min_step : pos;
			dp[0][1].emplace(pos, min_step);
		}
		// 开始递归
		// dp[i][j] = dp[i][k] + dp[k][j]
		for (int j = 2; j < key.size() + 1; ++j)
		{
			int i = j - 1;
			// 我们只用接尾即可
			for (int &j_pos : key_map[key[j - 1]])
			{
				int min_step = INT_MAX;
				for (auto &temp : dp[0][i])
				{
					int temp_pos = temp.first;
					int delta = (j_pos - temp_pos + ring_size) % ring_size;
					int rdelta = (-delta + ring_size) % ring_size;
					delta = delta < rdelta ? delta : rdelta;
					min_step = min_step < temp.second + delta ? min_step : temp.second + delta;
				}
				dp[0][j].emplace(j_pos, min_step);
			}


			// for (int i = j - 1; i >= 0; --i)
			// {
			//     if (i == j-1)
			//     {
			//         // 这种情况, 新入节点 j-1 ~ j
			//         for (int &i_pos:key_map[key[i-1]])
			//         {
			//             for (int &j_pos:key_map[key[j-1]])
			//             {
			//                 int temp = (j_pos - i_pos + ring_size) % ring_size;
			//                 int rtemp = (-temp + ring_size) % ring_size;
			//                 temp = temp < rtemp ? temp : rtemp;
			//                 dp[i][j].emplace(CNode(i_pos, j_pos), temp);
			//             }
			//         }
			//     } else {
			//         // 这时, 求 i-j 的最小值, 所以我们用 k 来描述, 并且更新, k != i, k != j
			//         for (int k = i + 1; k < j; ++k)
			//         {
			//             // dp[i][k] + dp[k][j] -> 首先遍历 i,j 的可能位置
			//             // i = 0 时, 我们做特殊处理, 因为是起点
			//             if (i == 0)
			//             {
			//                 int i_pos = 0;
			//                 for (int j_pos:key_map[key[j-1]])
			//                 {
			//                     int temp = INT_MAX;
			//                     for (int k_pos:key_map[key[k-1]])
			//                     {
			//                         // 这些位置, 肯定是存在的, 因为我们会考虑每一种可能
			//                         CNode ik = CNode(i_pos, k_pos);
			//                         CNode kj = CNode(k_pos, j_pos);
			//                         int result = dp[i][k][ik] + dp[k][j][kj];
			//                         temp = temp < result ? temp : result;
			//                     }
			//                     dp[i][j].emplace(CNode(i_pos, j_pos), temp);
			//                 }
			//             } else {
			//                 for (int i_pos:key_map[key[i-1]])
			//                 {
			//                     for (int j_pos:key_map[key[j-1]])
			//                     {
			//                         int temp = INT_MAX;
			//                         for (int k_pos:key_map[key[k-1]])
			//                         {
			//                             // 这些位置, 肯定是存在的, 因为我们会考虑每一种可能
			//                             CNode ik = CNode(i_pos, k_pos);
			//                             CNode kj = CNode(k_pos, j_pos);
			//                             int result = dp[i][k][ik] + dp[k][j][kj];
			//                             temp = temp < result ? temp : result;
			//                         }
			//                         dp[i][j].emplace(CNode(i_pos, j_pos), temp);
			//                     }
			//                 }
			//             }
			//         }
			//     }

			// }
		}
		int result = INT_MAX;
		for (auto &temp : dp[0][key.size()])
		{
			result = result < temp.second ? result : temp.second;
		}
		return result + key.size();
	}
};