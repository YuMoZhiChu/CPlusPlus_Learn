// 参考思路, hash_table
// STL源码剖析 5.7
#include<vector>
using std::vector;

#include<algorithm>
using std::lower_bound;

#include<cstdlib>
using std::rand;

// 用对质数取模实现哈希函数
static const int __num_primes = 28;
static const size_t __primes_list[__num_primes] = {
	53, 97, 193, 389, 769,
	1543, 3079, 6151, 12289, 24593,
	49157, 98317, 196613, 393241, 786433,
	1572869, 3145739, 6291469, 12582917, 25165843,
	// 50331653, 100663319, 201326611, 402653189, 805306457,
	// 1610612741, 3221225473ul, 4294967291ul
};
// 最多可以多少个 buckets
static const size_t max_bucket_count = __primes_list[__num_primes - 1];

// 找到上述 28 个质数之中, 最接近并大于或者等于 n 的那个质数
inline size_t __next_prime(size_t n)
{
	const size_t* first = __primes_list;
	const size_t* last = __primes_list + __num_primes;
	const size_t* pos = lower_bound(first, last, n);
	return pos == last ? *(last - 1) : *pos;
}

struct HashTableNode {
	HashTableNode *next;
	int val;
};

class HashTable {
public:
	HashTable() {
		// 初始化, 先给53个值
		buckets = vector<HashTableNode*>(__primes_list[0], NULL);
		buckets_counter = vector<size_t>(__primes_list[0], 0);
		num_elements = 0; // 元素个数是 0
	}

	// 新建节点
	inline HashTableNode* new_node(const int& obj)
	{
		HashTableNode *n = new HashTableNode();
		n->next = NULL;
		n->val = obj;
		return n;
	}

	// 删除节点
	inline void delete_node(HashTableNode *n)
	{
		delete n;
	}

	// 取模函数
	// 坑点, 十分注意, 这里一定要转成 int, 不然一个负数对 size_t 取模, 会导致得到不同的结果
	inline size_t get_bucket_num(const int &val, int n)
	{
		int result = val % n;
		return result >= 0 ? result : result + n;
	}

	void resize(const size_t &num_elements_hint)
	{
		const size_t old_n = buckets.size();
		// 当 +1 后的元素数量, 大于我们的 bucket 的列表长度时, 就重建表格
		if (num_elements_hint > old_n)
		{
			const size_t n = __next_prime(num_elements_hint); // 找到下一个质数
			vector<HashTableNode*> tmp_buckets(n, NULL); // 新建新的 buckets
			vector<size_t> tmp_buckets_counter(n, 0); // 新建新的 counter 记录
			for (size_t bucket = 0; bucket < old_n; ++bucket)
			{
				// 获得第一个串行的节点
				HashTableNode *first = buckets[bucket];
				while (first) // 串行还没结束时
				{
					// 这个过程, 相当于
					// 从 旧 bucket 链表头 取出第一个
					// 向 tmp_buckets 新链表头 插入第一个

					// 获得这个 val, 在新的 bucket 中的位置
					size_t new_bucket = get_bucket_num(first->val, n);

					// 令旧 bucket 指向下一个
					buckets[bucket] = first->next;
					// 新的独立元素, 插入到新的串行节点的第一个
					first->next = tmp_buckets[new_bucket];
					tmp_buckets[new_bucket] = first;
					++tmp_buckets_counter[new_bucket];
					// first 指回下一个
					first = buckets[bucket];
				}
			}
			// 使用 swap 做交换即可
			buckets.swap(tmp_buckets);
			buckets_counter.swap(tmp_buckets_counter);
		}
	}

	bool insert(int val)
	{
		resize(num_elements + 1);
		// 这里写支持重复的插入, 所以直接做插入工作即可
		const size_t n = get_bucket_num(val, buckets.size());
		HashTableNode *first = buckets[n]; // 头部串行指针
		HashTableNode *tmp = new_node(val);
		++num_elements;
		++buckets_counter[n]; // 记录 +1
		for (HashTableNode *cur = first; cur; cur = cur->next)
		{
			if (cur->val == val)
			{
				// 如果发现键值相同, 插在一起, 然后返回
				tmp->next = cur->next;
				cur->next = tmp;
				return false;
			}
		}
		// 如果没有, 直接插在头部
		tmp->next = first;
		buckets[n] = tmp;
		return true;
	}

	bool remove(const int &val)
	{
		const size_t n = get_bucket_num(val, buckets.size());
		HashTableNode *first = buckets[n]; // 头部串行指针
		if (!first) {
			return false; // 可能这个数就没有
		}

		for (HashTableNode *cur = first, *pre = first; cur; cur = cur->next)
		{
			if (cur->val == val)
			{
				// 如果发现键值相同, 删除该指针
				if (pre == first)
				{
					buckets[n] = cur->next;
				}
				else {
					pre->next = cur->next;
				}
				delete_node(cur);
				--buckets_counter[n];
				--num_elements;
				return true;
			}
			// pre迭代慢一步
			if (cur != first)
			{
				pre = pre->next;
			}
		}
		return false;
	}

	int getRandom()
	{
		size_t random_num = rand() % num_elements;
		for (size_t i = 0; i < buckets_counter.size(); ++i)
		{
			size_t this_count = buckets_counter[i];
			if (random_num < this_count)
			{
				size_t start_pos = 0;
				HashTableNode *it = buckets[i];
				while (start_pos != random_num)
				{
					it = it->next;
					++start_pos;
				}
				return it->val;
			}
			random_num -= this_count;
		}
		return -1;
	}

private:
	vector<HashTableNode*> buckets;
	vector<size_t> buckets_counter; // 记录每个 bucket 目前装了几个元素 -> getRandom O(1) 需要的记录内容
	size_t num_elements; // 记录总共有多少个元素
};

class RandomizedCollection {
public:
	/** Initialize your data structure here. */
	RandomizedCollection() {
		p = new HashTable();
	}

	/** Inserts a value to the collection. Returns true if the collection did not already contain the specified element. */
	bool insert(int val) {
		return p->insert(val);
	}

	/** Removes a value from the collection. Returns true if the collection contained the specified element. */
	bool remove(int val) {
		return p->remove(val);
	}

	/** Get a random element from the collection. */
	int getRandom() {
		return p->getRandom();
	}
private:
	HashTable *p;
};

/**
 * Your RandomizedCollection object will be instantiated and called as such:
 * RandomizedCollection* obj = new RandomizedCollection();
 * bool param_1 = obj->insert(val);
 * bool param_2 = obj->remove(val);
 * int param_3 = obj->getRandom();
 */