// 力扣
// https://leetcode-cn.com/problems/n-queens/
// 学习
// https://labuladong.gitbook.io/algo/suan-fa-si-wei-xi-lie/3.1-hui-su-suan-fa-dfs-suan-fa-pian/hui-su-suan-fa-xiang-jie-xiu-ding-ban
// 回溯(dps)解题框架
// result = []
// def backtrack(路径, 选择列表):
//     if 满足结束条件:
//         result.add(路径)
//         return

//     for 选择 in 选择列表:
//         做选择
//         backtrack(路径, 选择列表)
//         撤销选择
// 如果是求单解的过程, 那么把 backtrack 做成 bool 函数, 在深搜不满足条件时, 才跳出进行新的分支, 否则直接跳出
// 函数找到一个答案后就返回 true
//bool backtrack(vector<string>& board, int row) {
//	// 触发结束条件
//	if (row == board.size()) {
//		res.push_back(board);
//		return true;
//	}
//	...
//		for (int col = 0; col < n; col++) {
//			...
//				board[row][col] = 'Q';
//
//			if (backtrack(board, row + 1))
//				return true;
//
//			board[row][col] = '.';
//		}
//
//	return false;
//}


#include<vector>
using std::vector;

#include<string>
using std::string;

class Solution {
	
	void dps(vector<vector<string>> &result, vector<vector<int>> &enable, int &target,
		int now_it)
	{
		// 成功放置
		if (now_it == target)
		{
			result.push_back({});
			int last_pos = result.size() - 1;
			for (int i = 0; i < target; ++i)
			{
				string temp = "";
				for (int j = 0; j < target; ++j)
				{
					if (enable[i][j] == target + 1)
					{
						temp.push_back('Q');
					}
					else {
						temp.push_back('.');
					}
				}
				result[last_pos].push_back(temp);
			}
			return;
		}
		for (int it = 0; it < target; ++it)
		{
			// 找到一个可以放置的位置
			if (enable[now_it][it] == 0)
			{
				enable[now_it][it] = target + 1; // 记录这一行的位置
				// 这个皇后可以移动到的位置, 我们不用考虑 now_it 这一行(因为就是拿这个递进的)
				// 这一列, 都记录了
				for (int x = now_it + 1; x < target; ++x) ++enable[x][it];
				// 斜对角记录
				for (int delta = 1; now_it + delta < target && it + delta < target; ++delta)
					++enable[now_it + delta][it + delta];
				for (int delta = 1; now_it + delta < target && it - delta >= 0; ++delta)
					++enable[now_it + delta][it - delta];

				dps(result, enable, target, now_it + 1);

				// 回溯原来状态
				enable[now_it][it] = 0;
				for (int x = now_it + 1; x < target; ++x) --enable[x][it];
				for (int delta = 1; now_it + delta < target && it + delta < target; ++delta)
					--enable[now_it + delta][it + delta];
				for (int delta = 1; now_it + delta < target && it - delta >= 0; ++delta)
					--enable[now_it + delta][it - delta];
			}
		}
	}

public:
	vector<vector<string>> solveNQueens(int n) {
		vector<vector<string>> result;
		vector<vector<int>> enable;
		// 初始化, 记录位置
		for (int i = 0; i < n; ++i)
		{
			enable.push_back(vector<int>(n, 0));
		}
		dps(result, enable, n, 0);
		return result;
	}
};