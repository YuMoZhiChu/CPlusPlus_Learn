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


		// 广搜记录, 总共记录这么多
		vector<vector<int>> edge_record(wordList_size);

		// 找可能的联通路径, 填表格
		for (int i = 0; i < wordList_size; ++i)
		{
			string temp = wordList[i];
			for (int j = 0; j < temp.size(); ++j)
			{
				// 标准思路的 *aa 算法是真的牛逼！！值得学习

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
						edge_record[i].push_back(word_2_int[change]);
						edge_record[word_2_int[change]].push_back(i);
					}
				}
			}
		}

		// 相对的广搜, 因为单词的本质, 所以广搜的时候, 我们去遍历边即可
		struct node {
			node(int _now_word_id, int _now_cost) :now_word_id(_now_word_id), now_cost(_now_cost) {}
			int now_word_id;
			int now_cost;
		};

		// 做一个记录, 记录当前最短 - 其实这就是 djis 的 深搜写法, 深搜的优势在于, 我们记录的是有限边, 所以更快
		vector<int> dis_from(wordList_size, 0);
		dis_from[from_word_id] = 0;

		queue<node> q_from;
		q_from.push(node(from_word_id, 0));

		// 标准答案思路, 双向深度遍历, 可以大量压缩空间
		vector<int> dis_to(wordList_size, 0);
		dis_to[to_word_id] = 0;
		queue<node> q_to;
		q_to.push(node(to_word_id, 0));

		while (!q_from.empty() && !q_to.empty())
		{
			node front = q_from.front();
			q_from.pop();
			// 这个之所以快, 是因为我们的可拓展项是有限的
			for (int &to_pos : edge_record[front.now_word_id])
			{
				if (to_pos == to_word_id)
					return front.now_cost + 1 + 1; // +1 迭代+1, +1 漏算的步骤+1

				if (dis_from[to_pos] == 0) // 下一步迭代
				{
					dis_from[to_pos] = front.now_cost + 1;
					q_from.push(node(to_pos, front.now_cost + 1));
				}

				if (dis_to[to_pos] != 0) // 找到相交的地方
				{
					return dis_from[to_pos] + dis_to[to_pos] + 1;
				}
			}

			// 反向bfs - 加了好像并没有快多少
			node front_to = q_to.front();
			q_to.pop();
			for (int &to_pos : edge_record[front_to.now_word_id])
			{
				if (to_pos == from_word_id)
					return front_to.now_cost + 1 + 1;

				if (dis_to[to_pos] == 0)
				{
					dis_to[to_pos] = front_to.now_cost + 1;
					q_to.push(node(to_pos, front_to.now_cost + 1));
				}

				if (dis_from[to_pos] != 0) // 找到相交的地方
				{
					return dis_from[to_pos] + dis_to[to_pos] + 1;
				}

			}
		}

		return 0;
	}
};