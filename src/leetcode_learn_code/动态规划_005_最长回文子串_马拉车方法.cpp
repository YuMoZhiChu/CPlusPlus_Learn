#include<string>
using std::string;

class Solution {
public:
	// 获得以该位置为中心的半径
	// 这里如果用 const string S, stirng S, 内存会爆炸, 使用引用来优化内存，const string &s 能被编译器优化，不需要新建一个 temp string
	int getRadius(const string &S, const int &pos)
	{
		int result = 0;
		int left = pos - 1;
		int right = pos + 1;
		while (left >= 0 && right < S.size())
		{
			if (S[left] == S[right])
			{
				++result;
				--left;
				++right;
			}
			else {
				break;
			}

		}
		return result;
	}

	// 马拉车做法
	string longestPalindrome(string s) {
		if (s == "") return "";

		// 预处理字符串, 间隔都加一个 #
		string S = "#";

		for (char c : s)
		{
			S += c;
			S += '#';
		}

		// 马拉车, 计算辅助数组, 或者是 回文半径数组
		const int size = S.size();
		int *mrh = new int[size]();
		int max_radius = 1;
		int start_pos = 0;
		for (int i = 0; i < size; ++i)
		{
			int cur_radius = getRadius(S, i);
			if (cur_radius > max_radius)
			{
				max_radius = cur_radius;
				start_pos = (i - max_radius) / 2;
			}
		}
		// 辅助数组中的最大半径, 就是结果
		return s.substr(start_pos, max_radius);
	}
};