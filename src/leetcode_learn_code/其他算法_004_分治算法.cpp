// 力扣
// https://leetcode-cn.com/problems/different-ways-to-add-parentheses/submissions/
// 学习
// https://labuladong.gitbook.io/algo/suan-fa-si-wei-xi-lie/3.3-qi-ta-suan-fa-pian/fen-zhi-suan-fa
// 思路: 分类讨论的递归写法

#include<vector>
using std::vector;

#include<string>
using std::string;

class Solution {
	inline bool is_sign(char c)
	{
		if (c == '+' || c == '-' || c == '*') return true;
		return false;
	}

	int calculate(int a, int b, char c)
	{
		if (c == '+') return a + b;
		if (c == '-') return a - b;
		if (c == '*') return a * b;
		return 0;
	}

public:
	vector<int> recur_result(vector<char> &sign_vector, vector<int> &num_vector,
		int left, int right)
	{
		if (left == right)
		{
			// 直接返回
			return { num_vector[left] };
		}
		vector<int> result;
		for (int i = left; i < right; ++i)
		{
			auto left_results = recur_result(sign_vector, num_vector, left, i);
			auto right_results = recur_result(sign_vector, num_vector, i + 1, right);
			for (auto left_result : left_results)
			{
				for (auto right_result : right_results)
				{
					result.push_back(calculate(
						left_result, right_result, sign_vector[i]
					));
				}
			}
		}
		return result;
	}

	vector<int> diffWaysToCompute(string input) {
		vector<char> sign_vector;
		vector<int> num_vector;
		for (int i = 0; i < input.size(); ++i)
		{
			if (is_sign(input[i]))
			{
				sign_vector.push_back(input[i]);
			}
			else {
				// 找到下一个是 +-*
				int j = 0;
				while (i + j < input.size() && !is_sign(input[i + j])) ++j;
				num_vector.push_back(
					std::stoi(
						input.substr(i, j)
					)
				);
				i += (j - 1);
			}
		}
		return recur_result(sign_vector, num_vector, 0, num_vector.size() - 1);
	}
};