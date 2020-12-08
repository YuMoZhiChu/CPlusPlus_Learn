/**
 * // This is the interface that allows for creating nested lists.
 * // You should not implement it, or speculate about its implementation
 * class NestedInteger {
 *   public:
 *     // Return true if this NestedInteger holds a single integer, rather than a nested list.
 *     bool isInteger() const;
 *
 *     // Return the single integer that this NestedInteger holds, if it holds a single integer
 *     // The result is undefined if this NestedInteger holds a nested list
 *     int getInteger() const;
 *
 *     // Return the nested list that this NestedInteger holds, if it holds a nested list
 *     // The result is undefined if this NestedInteger holds a single integer
 *     const vector<NestedInteger> &getList() const;
 * };
 */
// 核心思路, 就是把这个看成一颗 N 维度的树, 用树的思想来做遍历即可

#include<vector>
using std::vector;

#include<list>
using std::list;

struct NestedInteger
{
	int val;
	list<NestedInteger> nest_list;
	NestedInteger(int _val)
	{
		val = _val;
		nest_list.clear();
	}

	NestedInteger(list<NestedInteger> _nest_list)
	{
		val = INT_MAX;
		nest_list.swap(_nest_list);
	}

	bool isInteger()
	{
		return nest_list.empty();
	}

	int getInteger()
	{
		return val;
	}

	list<NestedInteger> getList()
	{
		return nest_list;
	}
};


class NestedIterator {
public:
	vector<int> result;
	vector<int>::iterator it;

	NestedIterator(vector<NestedInteger> &nestedList) {
		result.clear();
		// n叉树的遍历, 并把结果存进 result 中
		// todo 用堆栈的思路, 不去遍历整个流程
		// 或者找到类似 python yield 的语法糖
		for (NestedInteger &node : nestedList)
		{
			traverse(node);
		}
		it = result.begin();
	}

	void traverse(NestedInteger &root)
	{
		if (root.isInteger())
		{
			result.push_back(root.getInteger());
			return;
		}
		for (NestedInteger &node : root.getList())
		{
			traverse(node);
		}
	}

	int next() {
		return *it++;
	}

	bool hasNext() {
		return it != result.end();
	}
};

/**
 * Your NestedIterator object will be instantiated and called as such:
 * NestedIterator i(nestedList);
 * while (i.hasNext()) cout << i.next();
 */
