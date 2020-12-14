// 力扣
// https://leetcode-cn.com/problems/sudoku-solver/solution/
// 题解给出的 双100% 解法, 非常漂亮的解法, bitset的用法
#include<vector>
using std::vector;

#include<set>
using std::set;

const set<char> ENABLE_CHAR = { '1', '2', '3', '4', '5', '6', '7', '8', '9' };

class Solution {
	bool dfs(vector<vector<char>>& board, int &count, int start_pos)
	{
		if (count == 81)
		{
			return true;
		}

		for (int pos = start_pos; pos < 81; ++pos)
		{
			int x = pos / 9;
			int y = pos % 9;
			// 本来就有的位置
			if (board[x][y] != '.')
			{
				continue;
			}
			set<char> temp(ENABLE_CHAR);
			for (int i = 0; i < 9; ++i)
			{
				if (board[x][i] != '.')
				{
					temp.erase(board[x][i]);
				}
				if (board[i][y] != '.')
				{
					temp.erase(board[i][y]);
				}
			}
			int x_3 = (x / 3) * 3;
			int y_3 = (y / 3) * 3;
			for (int i = 0; i < 3; ++i)
			{
				for (int j = 0; j < 3; ++j)
				{
					if (board[x_3 + i][y_3 + j] != '.')
					{
						temp.erase(board[x_3 + i][y_3 + j]);
					}
				}
			}
			// pos 这个位置填不下了, 就要回溯了
			if (temp.empty()) return false;
			// temp 是可以填入的 char
			for (char temp_char : temp)
			{
				board[x][y] = temp_char;
				++count;
				if (dfs(board, count, pos + 1))
				{
					return true;
				}
				--count;
				board[x][y] = '.';
			}
			// temp 中的 char 都不行
			return false;
		}
		return false;
	}

public:
	void solveSudoku(vector<vector<char>>& board) {
		int count = 0;
		for (int i = 0; i < 9; ++i)
		{
			for (int j = 0; j < 9; ++j)
			{
				if (board[i][j] != '.') ++count;
			}
		}
		bool bk = dfs(board, count, 0);
	}
};