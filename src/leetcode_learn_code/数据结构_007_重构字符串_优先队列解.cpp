// 力扣
// https://leetcode-cn.com/problems/reorganize-string/
// 优先队列解法

#include<queue>
using std::priority_queue;

#include<string>
using std::string;

#include<vector>
using std::vector;

class Solution {
public:
	string reorganizeString(string S) {
		struct CNode {
			CNode(int _char_num, int _time) :char_num(_char_num), time(_time) {}
			int char_num;
			int time;
		};
		vector<int> record(26, 0);
		for (char &c : S)
		{
			++record[c - 'a'];
		}
		auto cmp = [](const CNode &lhs, const CNode &rhs) {
			if (lhs.time == rhs.time) return lhs.char_num > rhs.char_num;
			return lhs.time < rhs.time;
		};
		priority_queue<CNode, vector<CNode>, decltype(cmp)> pq(cmp);
		for (int i = 0; i < 26; ++i)
		{
			if (record[i] != 0)
				pq.emplace(i, record[i]);
		}
		if (pq.top().time > (S.size() + 1) / 2) return "";
		string result;
		while (!pq.empty())
		{
			CNode temp = pq.top();
			pq.pop();
			if (pq.empty()) return result + char(temp.char_num + 'a');
			CNode next = pq.top();
			pq.pop();
			result += char(temp.char_num + 'a');
			result += char(next.char_num + 'a');
			--temp.time;
			if (temp.time > 0)
				pq.push(temp);
			--next.time;
			if (next.time > 0)
				pq.push(next);
		}
		return result;
	}
};