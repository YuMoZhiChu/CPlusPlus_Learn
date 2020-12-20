﻿// 力扣
// https://leetcode-cn.com/problems/open-the-lock/submissions/
// 学习
// https://labuladong.gitbook.io/algo/suan-fa-si-wei-xi-lie/3.2-bfs-suan-fa-pian/bfs-kuang-jia
// bfs模板
//
// 计算从起点 start 到终点 target 的最近距离
// int BFS(Node start, Node target) {
//     Queue<Node> q; // 核心数据结构
//     Set<Node> visited; // 避免走回头路

//     q.offer(start); // 将起点加入队列
//     visited.add(start);
//     int step = 0; // 记录扩散的步数

//     while (q not empty) {
//         int sz = q.size();
//         /* 将当前队列中的所有节点向四周扩散 */
//         for (int i = 0; i < sz; i++) {
//             Node cur = q.poll();
//             /* 划重点：这里判断是否到达终点 */
//             if (cur is target)
//                 return step;
//             /* 将 cur 的相邻节点加入队列 */
//             for (Node x : cur.adj())
//                 if (x not in visited) {
//                     q.offer(x);
//                     visited.add(x);
//                 }
//         }
//         /* 划重点：更新步数在这里 */
//         step++;
//     }
// }
// 双向BFS技巧, 前提是要知道终点
// int openLock(String[] deadends, String target) {
//     Set<String> deads = new HashSet<>();
//     for (String s : deadends) deads.add(s);
//     // 用集合不用队列，可以快速判断元素是否存在
//     Set<String> q1 = new HashSet<>();
//     Set<String> q2 = new HashSet<>();
//     Set<String> visited = new HashSet<>();

//     int step = 0;
//     q1.add("0000");
//     q2.add(target);

//     while (!q1.isEmpty() && !q2.isEmpty()) {
//         // 哈希集合在遍历的过程中不能修改，用 temp 存储扩散结果
//         Set<String> temp = new HashSet<>();

//         /* 将 q1 中的所有节点向周围扩散 */
//         for (String cur : q1) {
//             /* 判断是否到达终点 */
//             if (deads.contains(cur))
//                 continue;
//             if (q2.contains(cur))
//                 return step;
//             visited.add(cur);

//             /* 将一个节点的未遍历相邻节点加入集合 */
//             for (int j = 0; j < 4; j++) {
//                 String up = plusOne(cur, j);
//                 if (!visited.contains(up))
//                     temp.add(up);
//                 String down = minusOne(cur, j);
//                 if (!visited.contains(down))
//                     temp.add(down);
//             }
//         }
//         /* 在这里增加步数 */
//         // 这里直接交换, 相当于交换之后, 处理交换的那一份
//         step++;
//         // temp 相当于 q1
//         // 这里交换 q1 q2，下一轮 while 就是扩散 q2
//         q1 = q2;
//         q2 = temp;
//     }
//     return -1;
// }
// ...
// 大小均衡优化, 优先处理大的
// while (!q1.isEmpty() && !q2.isEmpty()) {
//     if (q1.size() > q2.size()) {
//         // 交换 q1 和 q2
//         temp = q1;
//         q1 = q2;
//         q2 = temp;
//     }
//     // ...



#include<vector>
using std::vector;

#include<string>
using std::string;

#include<queue>
using std::queue;

#include<map>
using std::map;

class Solution {
public:
	int openLock(vector<string>& deadends, string target) {
		map<string, bool> is_visit;
		for (auto &s : deadends)
		{
			is_visit[s] = true;
		}
		struct CNode
		{
			CNode(string _str, int _time) :str(_str), time(_time) {}
			string str;
			int time;
		};
		queue<CNode> q;
		q.emplace("0000", 0);
		int result = -1;
		while (!q.empty())
		{
			auto top = q.front();
			q.pop();
			if (is_visit[top.str]) continue;
			if (top.str == target) return top.time;
			is_visit[top.str] = true;
			for (int i = 0; i < 4; ++i)
			{
				// +1
				auto temp = top.str;
				if (temp[i] == '9') temp[i] = '0';
				else ++temp[i];
				q.emplace(temp, top.time + 1);

				// -1
				temp = top.str;
				if (temp[i] == '0') temp[i] = '9';
				else --temp[i];
				q.emplace(temp, top.time + 1);
			}
		}
		return result;
	}
};