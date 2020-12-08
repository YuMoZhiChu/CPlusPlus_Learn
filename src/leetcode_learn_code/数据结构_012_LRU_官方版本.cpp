// 力扣
// https://leetcode-cn.com/problems/lru-cache/solution/
// 思路
// https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.4-shou-ba-shou-she-ji-shu-ju-jie-gou/lru-suan-fa
// 主要思路
// 哈希链表
// 获取 get 哈希表 -> 链表节点 该节点移到链表尾部
// put - 已存在, 更改数据, 并移动该节点到链表尾部
//     - 插入, 如果超过容量, 移出链表头, 插入链表尾

#include<unordered_map>
using std::unordered_map;

#include<list>
using std::list;

class LRUCache {
public:
	struct CNode
	{
		CNode(int _key, int _value) :key(_key), value(_value) {}
		int key;
		int value;
	};

	LRUCache(int capacity) {
		cap = capacity;
		size = 0;
		value_list.clear();
		key_it_map.clear();
	}

	// 尾部是最旧的
	void remove_least_recently()
	{
		CNode temp = value_list.back();
		value_list.pop_back();
		key_it_map.erase(temp.key);
	}

	int get(int key) {
		auto it = key_it_map.find(key);
		if (it == key_it_map.end())
		{
			return -1;
		}
		else {
			CNode result = *it->second;
			value_list.erase(it->second);
			value_list.push_front(result);
			it->second = value_list.begin(); // 这里最新的改成 头部
			return result.value;
		}
	}

	void put(int key, int value) {
		auto it = key_it_map.find(key);
		if (it != key_it_map.end())
		{
			value_list.erase(it->second);
			value_list.emplace_front(key, value);
			it->second = value_list.begin();
		}
		else {
			if (size < cap)
			{
				value_list.emplace_front(key, value);
				key_it_map.emplace(key, value_list.begin());
				++size;
			}
			else {
				remove_least_recently();
				value_list.emplace_front(key, value);
				key_it_map.emplace(key, value_list.begin());
			}
		}
	}

private:
	list<CNode> value_list;
	unordered_map<int, list<CNode>::iterator> key_it_map;
	int cap;
	int size;
};

/**
 * Your LRUCache object will be instantiated and called as such:
 * LRUCache* obj = new LRUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */