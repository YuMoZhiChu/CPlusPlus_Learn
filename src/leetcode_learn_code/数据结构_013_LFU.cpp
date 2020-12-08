// 力扣
// https://leetcode-cn.com/problems/lfu-cache/submissions/
// LFU 框架


#include<unordered_map>
using std::unordered_map;

#include<list>
using std::list;

struct LFUNode
{
	LFUNode(int _key, int _val, int _freq = 1) :key(_key), val(_val), freq(_freq) {}
	int key;
	int val;
	int freq;
};

class LFUCache {
	int minfreq;
	int capacity;
	unordered_map<int, list<LFUNode>::iterator> key2node;
	unordered_map<int, list<LFUNode>> freq2node; // freq 是主页面
	// 我们理想状态下, LFUNode 是应该按着 freq 是一条 LRU 链
public:
	LFUCache(int _capacity) {
		capacity = _capacity;
		minfreq = 0;
		key2node.clear();
		freq2node.clear();
	}

	int get(int key) {
		if (capacity == 0) return -1;
		auto find_it = key2node.find(key);
		if (find_it == key2node.end())
		{
			return -1;
		}
		else {
			int val = find_it->second->val;
			int freq = find_it->second->freq;
			// 这里用 List 去删除一个带位置的 node, 代价是 O(1)
			freq2node[freq].erase(find_it->second);
			if (freq2node[freq].empty())
			{
				freq2node.erase(freq); // 删除 freq 整个链
				// 如果没了, freq + 1 就是新的最小值了
				if (minfreq == freq) minfreq = freq + 1;
			}
			auto freq_it = freq2node.find(freq + 1);
			if (freq_it == freq2node.end())
			{
				// 如果是空的, 新开一条路
				freq2node[freq + 1] = list<LFUNode>({ LFUNode(key, val, freq + 1) });
			}
			else {
				// 插头是 O1
				// 最新的在插头, 老的在后面
				freq2node[freq + 1].push_front(LFUNode(key, val, freq + 1));
			}
			// 记得把 key2node 回溯回来
			find_it->second = freq2node[freq + 1].begin();
			return val;
		}
	}

	void put(int key, int value) {
		if (capacity == 0) return;
		auto find_it = key2node.find(key);
		if (find_it == key2node.end())
		{
			// 满了, 我们要删除一个
			if (key2node.size() == capacity)
			{
				LFUNode temp = freq2node[minfreq].back();
				key2node.erase(temp.key);
				freq2node[minfreq].pop_back();
				if (freq2node[minfreq].empty())
				{
					freq2node.erase(minfreq);
				}
			}
			auto freq_it = freq2node.find(1);
			if (freq_it == freq2node.end())
			{
				freq2node[1] = list<LFUNode>({ LFUNode(key, value, 1) });
			}
			else {
				freq2node[1].push_front({ LFUNode(key, value, 1) });
			}
			minfreq = 1; // 刚刚塞入, 所以一定是 1
			key2node[key] = freq2node[1].begin();
		}
		else {
			int freq = find_it->second->freq;
			freq2node[freq].erase(find_it->second);
			if (freq2node[freq].empty())
			{
				freq2node.erase(freq); // 删除 freq 整个链
				// 如果没了, freq + 1 就是新的最小值了
				if (minfreq == freq) minfreq = freq + 1;
			}
			auto freq_it = freq2node.find(freq + 1);
			if (freq_it == freq2node.end())
			{
				// 如果是空的, 新开一条路
				freq2node[freq + 1] = list<LFUNode>({ LFUNode(key, value, freq + 1) });
			}
			else {
				// 插头是 O1
				// 最新的在插头, 老的在后面
				freq2node[freq + 1].push_front(LFUNode(key, value, freq + 1));
			}
			// 记得把 key2node 回溯回来
			find_it->second = freq2node[freq + 1].begin();
		}
	}
};

/**
 * Your LFUCache object will be instantiated and called as such:
 * LFUCache* obj = new LFUCache(capacity);
 * int param_1 = obj->get(key);
 * obj->put(key,value);
 */