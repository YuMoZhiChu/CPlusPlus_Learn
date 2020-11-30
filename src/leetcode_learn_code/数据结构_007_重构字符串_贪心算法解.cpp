// 力扣
// https://leetcode-cn.com/problems/reorganize-string/
// 贪心解法, 参考题解

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
		string result(S.size(), '|');
		int even_index = 0;
		int odd_index = 1;
		// 之所以先填奇数位置, 因为偶数位置要留给恰好是一半的值备用
		for (int i = 0; i < 26; ++i)
		{
			if (record[i] == 0) continue;
			if (record[i] > (S.size() + 1) / 2) return "";
			while (record[i] > 0 && odd_index < result.size() && record[i] <= S.size() / 2)
			{
				result[odd_index] = char(i + 'a');
				odd_index += 2;
				--record[i];
			}
			while (record[i] > 0 && even_index < result.size())
			{
				result[even_index] = char(i + 'a');
				even_index += 2;
				--record[i];
			}
		}
		return result;
	}
};