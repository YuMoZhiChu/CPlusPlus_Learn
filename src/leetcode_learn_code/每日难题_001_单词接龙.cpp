// https://leetcode-cn.com/problems/word-ladder/

#include<string>
using std::string;

#include<vector>
using std::vector;

#include<unordered_map>
using std::unordered_map;

#include<queue>
using std::queue;

class Solution {
public:
	// 直接递归会超时
	// int helper_find(string beginWord, string endWord, vector<string>& wordList, unordered_map<string, int> &m) {
	//     cout << beginWord << "-->" << endWord << endl;
	//     if (beginWord == endWord) return 1; // 初始流程 + 1
	//     if (m.count(beginWord + '-' + endWord)) return m[beginWord + '-' + endWord];
	//     if (is_near(beginWord, endWord))
	//     {
	//         // 记录
	//         m[beginWord + '-' + endWord] = 1;
	//         m[endWord + '-' + beginWord] = 1;
	//         return 1;
	//     }
	//     int result = 0;
	//     m[beginWord + '-' + endWord] = 0;
	//     m[endWord + '-' + beginWord] = 0;
	//     for (string &mid_string:wordList)
	//     {
	//         if (mid_string == beginWord || mid_string == endWord) continue;
	//         int r1 = helper_find(beginWord, mid_string, wordList, m);
	//         int r2 = helper_find(mid_string, endWord, wordList, m);
	//         if (r1 != 0 && r2 != 0)
	//         {
	//             if (result == 0)
	//             {
	//                 result = r1 + r2;
	//             } else {
	//                 result = result < (r1 + r2) ? result : r1 + r2;
	//             }
	//         }
	//     }
	//     m[beginWord + '-' + endWord] = result;
	//     m[endWord + '-' + beginWord] = result;
	//     return result;
	// }

	// int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
	//     // 检查 endWord 在不在
	//     bool endWordIn = false;
	//     for (string &s:wordList)
	//     {
	//         if (s == endWord) {
	//             endWordIn = true;
	//             break;
	//         }
	//     }
	//     if (!endWordIn) return 0;

	//     // 递归做法, 不行
	//     // unordered_map<string, int> m; // 记录本
	//     // int result = helper_find(beginWord, endWord, wordList, m);
	//     // return result == 0 ? 0 : result + 1;

	//     struct node {
	//         node(string _str, vector<string> _step):str(_str),step(_step){}
	//         string str;
	//         vector<string> step;
	//         bool can_next(string next)
	//         {
	//             if (next == str) return false;
	//             // 不做重复
	//             for (string &s:step)
	//             {
	//                 if (next == s) return false;
	//             }
	//             int count = 0;
	//             for (int i = 0; i < next.size(); ++i)
	//             {
	//                 if (str[i] != next[i]) ++count;
	//                 if (count >= 2) return false;
	//             }
	//             return true;
	//         }
	//     };

	//     // 纯 bfs 也不行
	//     queue<node> q;
	//     q.push(node(beginWord, vector<string>(1, beginWord)));
	//     while(!q.empty())
	//     {
	//         node front = q.front();
	//         q.pop();
	//         if (front.str == endWord)
	//         {
	//             // 因为是广搜, 所以第一个找到的, 一定是最小的
	//             return front.step.size();
	//         }

	//         for(string &s:wordList)
	//         {
	//             if (front.can_next(s))
	//             {
	//                 node temp(s, front.step);
	//                 temp.step.push_back(s);
	//                 q.push(temp);
	//             }
	//         }

	//     }
	//     return 0;
	// }

	int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
		// 建立映射关系, 方便快速查找相同的单词是否在表中
		unordered_map<string, int> word_2_int;
		int wordList_size = wordList.size();
		for (int i = 0; i < wordList_size; ++i)
		{
			word_2_int[wordList[i]] = i;
		}

		int from_word_id = -1;
		int to_word_id = -1;
		// 找不到, return 0
		if (word_2_int.find(endWord) == word_2_int.end()) return 0;
		to_word_id = word_2_int[endWord];
		// 找 from word
		if (word_2_int.find(beginWord) != word_2_int.end())
		{
			from_word_id = word_2_int[beginWord];
		}
		else {
			// 把 beginWord 加入
			word_2_int[beginWord] = wordList_size;
			from_word_id = wordList_size;
			++wordList_size;
			wordList.push_back(beginWord);
		}


		// 把目前的关系, 转换成 dp 表格, dp[i][j] 表示 i 到 j 的联通
		int **dp = new int*[wordList_size];
		for (int i = 0; i < wordList_size; ++i)
		{
			dp[i] = new int[wordList_size](); // 0 表示没有连接
		}

		// 找可能的联通路径, 填表格
		for (int i = 0; i < wordList_size; ++i)
		{
			string temp = wordList[i];
			for (int j = 0; j < temp.size(); ++j)
			{
				// 因为26个字母, 所以把其他 25 中可能打印出来即可
				for (int k = 1; k < 26; ++k)
				{
					string change = temp;
					// 要改变的字符
					char change_char = ((int(temp[j] - 'a') + k) % 26) + 'a';
					change[j] = change_char;
					// change 是搜索内容
					if (word_2_int.find(change) != word_2_int.end())
					{
						// 基础记录, 是双向的
						dp[i][word_2_int[change]] = 1;
						dp[word_2_int[change]][i] = 1;
					}
				}
			}
		}

		// // 进行 弗洛伊德算法 这个算法 时间不行
		// for (int i = 0; i < wordList_size; ++i)
		// {
		//     for (int j = 0; j < wordList_size; ++j)
		//     {
		//         for (int k = 0; k < wordList_size; ++k)
		//         {
		//             if (i == j || j == k || i == k) continue;

		//             if (dp[i][k] != 0 && dp[k][j] != 0)
		//             {
		//                 if (dp[i][j] == 0)
		//                 {
		//                     dp[i][j] = dp[i][k] + dp[k][j];
		//                 } else {
		//                     dp[i][j] = dp[i][j] < dp[i][k] + dp[k][j] ? dp[i][j] : dp[i][k] + dp[k][j];
		//                 }
		//                 dp[j][i] = dp[i][j];
		//             }
		//         }
		//     }
		// }

		// Dijkstra 算法, 求已知起点的最小值
		vector<bool> is_visit(wordList_size, false);
		is_visit[from_word_id] = true;
		for (int i = 0; i < wordList_size; ++i)
		{
			if (i == from_word_id) continue;

			// 首先, 遍历出当前的集合的最短距离, 初始状态是 {S}
			int min_distance = 0;
			int min_pos = -1;
			for (int j = 0; j < wordList_size; ++j)
			{
				if (is_visit[j]) continue; // 这是在集合中的
				if (dp[from_word_id][j] == 0) continue; // 显然, 这里是不连通的
				// 记录距离最小值, 并且记录 最小值点
				if (min_distance == 0 || min_distance > dp[from_word_id][j])
				{
					min_distance = dp[from_word_id][j];
					min_pos = j;
				}
			}
			if (min_pos == -1)
			{
				// 找不到进一步扩充集合时, 就可以直接退出了
				break;
			}
			is_visit[min_pos] = true; // 加入集合
			for (int k = 0; k < wordList_size; ++k)
			{
				// 因为集合中新加入了元素 min_pos 所以我们要进行一波更新
				// dp[from_word_id][k] 的一个可能更新项 dp[from_word_id][min_pos] + dp[min_pos][k]
				if (k == from_word_id || k == min_pos) continue;
				if (dp[min_pos][k] != 0) // dp[from_word_id][min_pos] 这个一定是非0, 值是 min_distance
				{
					int temp = min_distance + dp[min_pos][k];
					if (dp[from_word_id][k] == 0)
					{
						dp[from_word_id][k] = temp;
					}
					else {
						if (dp[from_word_id][k] > temp) dp[from_word_id][k] = temp;
					}
				}
			}
		}

		return dp[from_word_id][to_word_id] == 0 ? 0 : dp[from_word_id][to_word_id] + 1;
	}
};