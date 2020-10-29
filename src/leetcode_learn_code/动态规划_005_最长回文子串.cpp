#include<vector>
using std::vector;

#include<string>
using std::string;

class Solution {
public:
	// 动归做法
	string longestPalindrome(string s) {
		if (s == "") return "";
		// 结果取一个大的即可
		const int size = s.size();
		// dp 的意义, 是以第i个词结尾, 存在的 可能的回文子序列 的长度
		vector<vector<int>> dp;
		// 初始化, 每个变量都是 1 的长度
		for (int i = 0; i < size; ++i)
		{
			dp.push_back({ 1 });
		}

		for (int i = 1; i < size; ++i)
		{
			// 从 i 开始, 做假设遍历
			if (s[i] == s[i - 1])
			{
				dp[i].push_back(2);
			}
			// 如果和对称的一个相等
			for (int parlin_leght : dp[i - 1])
			{
				if (i - 1 - parlin_leght >= 0 && s[i] == s[i - 1 - parlin_leght])
				{
					dp[i].push_back(parlin_leght + 2);
				}
			}
		}

		// TODO 优化, 可以把这个遍历的过程, 直接放在上面的比较流程中
		// 遍历, 取最大值
		int result = 0;
		int pos = 0;
		for (int i = 0; i < size; ++i)
		{
			for (int& parlin_leght : dp[i])
			{
				if (parlin_leght > result)
				{
					result = parlin_leght;
					pos = i;
				}
			}
		}

		return s.substr(pos - result + 1, result);
	}
};