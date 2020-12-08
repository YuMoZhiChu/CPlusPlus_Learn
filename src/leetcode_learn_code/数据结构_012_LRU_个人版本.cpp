// 力扣
// https://leetcode-cn.com/problems/lru-cache/solution/
// 思路
// https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.4-shou-ba-shou-she-ji-shu-ju-jie-gou/lru-suan-fa
// 主要思路
// 哈希链表
// 获取 get 哈希表 -> 链表节点 该节点移到链表尾部
// put - 已存在, 更改数据, 并移动该节点到链表尾部
//     - 插入, 如果超过容量, 移出链表头, 插入链表尾
// 官方的版本: 我们可以简化, 不需要一个多余的链表结构, 直接用 map 指向链表即可


#include<unordered_map>
using std::unordered_map;

struct DLinkedNode_LRU {
	int key, value;
	DLinkedNode_LRU* prev;
	DLinkedNode_LRU* next;
	DLinkedNode_LRU() : key(0), value(0), prev(nullptr), next(nullptr) {}
	DLinkedNode_LRU(int _key, int _value) : key(_key), value(_value), prev(nullptr), next(nullptr) {}
};

class LRUCache {
private:
	unordered_map<int, DLinkedNode_LRU*> cache;
	DLinkedNode_LRU* head;
	DLinkedNode_LRU* tail;
	int size;
	int capacity;

public:
	LRUCache(int _capacity) : capacity(_capacity), size(0) {
		// 使用伪头部和伪尾部节点
		head = new DLinkedNode_LRU();
		tail = new DLinkedNode_LRU();
		head->next = tail;
		tail->prev = head;
	}

	int get(int key) {
		if (!cache.count(key)) {
			return -1;
		}
		// 如果 key 存在，先通过哈希表定位，再移到头部
		DLinkedNode_LRU* node = cache[key];
		moveToHead(node);
		return node->value;
	}

	void put(int key, int value) {
		if (!cache.count(key)) {
			// 如果 key 不存在，创建一个新的节点
			DLinkedNode_LRU* node = new DLinkedNode_LRU(key, value);
			// 添加进哈希表
			cache[key] = node;
			// 添加至双向链表的头部
			addToHead(node);
			++size;
			if (size > capacity) {
				// 如果超出容量，删除双向链表的尾部节点
				DLinkedNode_LRU* removed = removeTail();
				// 删除哈希表中对应的项
				cache.erase(removed->key);
				// 防止内存泄漏
				delete removed;
				--size;
			}
		}
		else {
			// 如果 key 存在，先通过哈希表定位，再修改 value，并移到头部
			DLinkedNode_LRU* node = cache[key];
			node->value = value;
			moveToHead(node);
		}
	}

	void addToHead(DLinkedNode_LRU* node) {
		node->prev = head;
		node->next = head->next;
		head->next->prev = node;
		head->next = node;
	}

	void removeNode(DLinkedNode_LRU* node) {
		node->prev->next = node->next;
		node->next->prev = node->prev;
	}

	void moveToHead(DLinkedNode_LRU* node) {
		removeNode(node);
		addToHead(node);
	}

	DLinkedNode_LRU* removeTail() {
		DLinkedNode_LRU* node = tail->prev;
		removeNode(node);
		return node;
	}
};