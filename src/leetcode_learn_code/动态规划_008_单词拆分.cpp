#include<string>
using std::string;

#include<queue>
using std::queue;

#include<unordered_map>
using std::unordered_map;

#include<unordered_set>
using std::unordered_set;

#include<vector>
using std::vector;

struct ResultNode {
	ResultNode(string _answer, string _nokori) :answer(_answer), nokori(_nokori) {}
	string answer;
	string nokori;
};

// 这道题, 是 动归 + 记录本 的递归写法, 如果使用广搜, 会被重复节点耗死
// 标准答案, 是从顶向下 的东西

class Solution {
public:
	vector<string> wordBreak(string s, vector<string>& wordDict) {
		// 做特殊处理
		for (char &c : s)
		{
			bool is_in = false;
			for (string &word : wordDict)
			{
				if (word.find(c) != -1)
				{
					is_in = true;
					break;
				}
			}
			if (!is_in)
				return vector<string>();
		}


		// 自底向上的解法 -> 缺点, 不能快速的过度到不符合预期的特例, 会导致展开过大, -> 失败
		// dp 的含义 s 的对应解法 []
		unordered_map<string, vector<string>> dp;
		// base 情况
		dp[""] = vector<string>(1, "");

		for (int i = 0; i < s.size(); ++i)
		{
			// 这里 的 s, 是长度大小, 所以要 i + 1
			dp[s.substr(0, i + 1)] = vector<string>();
			for (string &word : wordDict)
			{
				// base 小于 word 大小的, 都是空
				if ((i + 1) < word.size())
					continue;
				if (s.substr((i + 1) - word.size(), word.size()) == word)
				{
					string head_string = s.substr(0, (i + 1) - word.size());
					if (dp.count(head_string))
					{
						for (string &answer : dp[head_string])
						{
							// 像这种情况, 确实存在一定会超时的情况
							// 就算是使用深搜, 虽然能过 aaaaaaaaaaaaaaaaaaaabaaaaaaaaaaaaa 的测试样例
							// 但是如果样例改成 aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
							// 就也一样过不了, 个人认为, 这道题用深搜能解决的原因是
							// 深搜能快速过度到我们 aaaaaaaaaaaabaaaaaaaaaaa 中不符合预期的情况, 并且把整个逻辑链给断了
							if (answer != "")
								dp[s.substr(0, i + 1)].push_back(answer + " " + word);
							else
								dp[s.substr(0, i + 1)].push_back(word);
						}
					}
				}
			}
		}

		// 返回最终结果
		return dp[s];
	}
};