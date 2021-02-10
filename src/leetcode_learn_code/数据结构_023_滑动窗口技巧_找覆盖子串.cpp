// 力扣
// https://leetcode-cn.com/problems/minimum-window-substring/
// 学习
// https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/shou-ba-shou-shua-shu-zu-ti-mu/hua-dong-chuang-kou-ji-qiao-jin-jie#yi-zui-xiao-fu-gai-zi-chuan
// 滑动窗口技巧

#include<vector>
using std::vector;

#include<unordered_map>
using std::unordered_map;

#include<string>
using std::string;

class Solution {
public:
	string minWindow(string s, string t) {
		unordered_map<char, int> answer_map, record_map;
		for (char &c : t)
		{
			++answer_map[c];
			record_map[c] = 0;
		}

		// [left, right)
		int left = 0;
		int right = 0;
		int now_right = 0;
		int start = 0, len = INT_MAX;
		while (right < s.size())
		{
			char c = s[right]; // 判断这个读不读入
			// 右移
			++right;
			// 碰到一个在 answer_map 中的字符, 那么就尝试记录
			if (answer_map.count(c))
			{
				++record_map[c];
				if (record_map[c] == answer_map[c])
				{
					++now_right;
				}
			}

			// 如果我们每个记录都OK, 那么尽可能左边缩短
			while (now_right == answer_map.size())
			{
				if (right - left < len)
				{
					start = left;
					len = right - left;
				}
				// d 是移出字符
				char d = s[left];
				++left;
				if (answer_map.count(d))
				{
					// 看看会不会有影响
					if (record_map[d] == answer_map[d]) --now_right;
					--record_map[d];
				}
			}
		}

		return len == INT_MAX ? "" : s.substr(start, len);
	}
};