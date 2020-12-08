// 力扣
// https://leetcode-cn.com/problems/split-array-into-fibonacci-sequence/
// DFS
// 深搜回溯思路

#include<vector>
using std::vector;

#include<string>
using std::string;

class Solution {
public:
	// sum : 这一次遍历 cur 应该要匹配的值
	// prev : cur 的前一个值
	bool dfs(vector<int> &result, string &S, int &length, int index, long long sum, int prev)
	{
		if (index == length)
		{
			return result.size() >= 3;
		}
		long cur = 0;
		for (int i = index; i < length; ++i)
		{
			// 数字不能以 0 开始
			if (i > index && S[index] == '0')
				break;
			cur = cur * 10 + S[i] - '0';
			if (cur > INT_MAX) {
				break;
			}
			// 如果有 2 个的情况
			if (result.size() >= 2)
			{
				if (cur > sum)
				{
					// 大于了, 之后也会大于
					break;
				}
				if (cur < sum)
				{
					// 小于, 说明还要进行下一次循环
					continue;
				}
			}
			// 先压入
			result.push_back(cur);
			if (dfs(result, S, length, i + 1, prev + cur, cur))
			{
				// 如果这一次深搜ok
				return true;
			}
			// 这种情况不行
			result.pop_back();
		}
		return false;
	}

	vector<int> splitIntoFibonacci(string S) {
		vector<int> result;
		int length = S.size();
		dfs(result, S, length, 0, 0, 0);
		return result;
	}
};