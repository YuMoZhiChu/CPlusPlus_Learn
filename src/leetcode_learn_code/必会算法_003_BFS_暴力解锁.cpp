// 力扣
// https://leetcode-cn.com/problems/sliding-puzzle/
// 题解做法
// 用了很多位运算操作, 看上去很省, 但是花了我很多时间

#include<vector>
using std::vector;

#include<queue>
using std::queue;

#include<unordered_set>
using std::unordered_set;

// 0,1,2
// 3,4,5
// tonari:
// 0 : 1,3
// 1 : 0,2,4
// 2 : 1,5
// 3 : 0,4
// 4 : 1,3,5
// 5 : 2,4
const vector<vector<int>> tonari = {
	{1,3},
	{0,2,4},
	{1,5},
	{0,4},
	{1,3,5},
	{2,4}
};

const int target = 1 | (2 << 3) | (3 << 6) | (4 << 9) | (5 << 12);

// 状态记录, 用一个 int 来记录
// 555 444 333 222 111 000
// 获取当前这个面板的key
inline int get_key_by_vecotr(vector<vector<int>>& board)
{
	return board[0][0] |
		(board[0][1] << 3) |
		(board[0][2] << 6) |
		(board[1][0] << 9) |
		(board[1][1] << 12) |
		(board[1][2] << 15);
}

class Solution {
public:
	int slidingPuzzle(vector<vector<int>>& board) {
		unordered_set<int> key_set;
		struct CNode
		{
			CNode(int _key, int _time) :key(_key), time(_time) {}
			int key;
			int time;
		};
		queue<CNode> q;
		int start_key = get_key_by_vecotr(board);
		q.emplace(start_key, 0);
		while (!q.empty())
		{
			CNode temp = q.front();
			q.pop();
			int temp_key = temp.key;
			if (temp_key == target) return temp.time;
			if (key_set.count(temp_key)) continue;
			key_set.insert(temp_key);
			// 找到 temp.key 中代表的 0 的位置
			int zero_pos = 0;
			for (; zero_pos < 18; ++zero_pos)
			{
				//int k = (temp_key & (7 << (zero_pos * 3))) >> (zero_pos * 3);
				//cout << k << endl;
				if ((temp_key & (7 << (zero_pos * 3))) >> (zero_pos * 3) == 0) break;
			}
			for (int swap_pos : tonari[zero_pos])
			{
				//cout << "swap_pos :" << swap_pos << endl;
				// 交换 swap_pos 和 zero_pos 的值
				// 在 swap_pos 上的 block_id 是?
				int block_id = (temp_key & (7 << (swap_pos * 3))) >> (swap_pos * 3);
				int new_key = (temp_key & (~(7 << (swap_pos * 3)))) | (block_id << (zero_pos * 3));
				q.emplace(new_key, temp.time + 1);
			}
		}
		return -1;
	}
};