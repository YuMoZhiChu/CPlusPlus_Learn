// https://leetcode-cn.com/problems/queue-reconstruction-by-height/comments/
// 自己想的方法, 先用 一次标准排序
// 然后从 遍历 1,2.... 出现次数, 依次插入

#include<vector>
using std::vector;

#include<algorithm>
using std::sort;

#include<list>
using std::list;

class Solution {
public:
	vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
		sort(people.begin(), people.end(), [](
			vector<int> &lhs, vector<int> &rhs
			) {
			if (lhs[1] == rhs[1]) return lhs[0] < rhs[0];
			return lhs[1] < rhs[1];
		}); // 先按照, 升序-0 升序-1 ... 做一次排序
		// 这里用 list 方便插入操作
		list<vector<int>*> pointer_list; // 尽量减少使用的空间, 我们直接存指针即可
		list<decltype(pointer_list.begin())> zero_it_list; // 这里存的是, list 中指向 X-0 的指针的位置, 这个好处是, 插入不变
		for (int i = 0; i < people.size(); ++i)
		{
			if (people[i][1] == 0)
			{
				// 压入 0
				pointer_list.push_back(&people[i]);
				// 压入最后一个迭代器的位置
				auto zero_it = pointer_list.end();
				--zero_it;
				zero_it_list.push_back(zero_it);
				continue;
			}
			// 开始插入
			auto find_zero_it = zero_it_list.begin();
			// 因为肯定能够插入
			while ((***find_zero_it)[0] < people[i][0])
			{
				++find_zero_it;
			}
			// 从 find_zero_it 的位置顺序插入
			auto it_in_pointer_list = *find_zero_it;
			// 因为一定有解, 所以这里是一定能正确插入的
			int j = 0;
			while (j < people[i][1])
			{
				if ((**it_in_pointer_list)[0] >= people[i][0])
				{
					++j;
				}
				++it_in_pointer_list;
			}
			// 然而, 这个位置不完全正确, 我们要经历遍历到 比它小的数
			while (it_in_pointer_list != pointer_list.end() &&
				(**it_in_pointer_list)[0] < people[i][0])
			{
				++it_in_pointer_list;
			}
			pointer_list.insert(it_in_pointer_list, &people[i]);
		}
		vector<vector<int>> result;
		for (auto &point : pointer_list)
		{
			result.push_back(*point);
		}
		return result;
	}
};