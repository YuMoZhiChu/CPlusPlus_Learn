// 力扣
// https://leetcode-cn.com/problems/find-median-from-data-stream/
// 优先队列的底层, 是 堆的实现
// 我们在选取最大值后, 整个队列会重新调整

#include<queue>
using std::priority_queue;

#include<vector>
using std::vector;

#include<functional>
using std::less;
using std::greater;


class MedianFinder {
	priority_queue<int, vector<int>, less<int>> max_pq; // 第一个位置是最大值
	priority_queue<int, vector<int>, greater<int>> min_pq; // 第一个位置是最小值
public:
	/** initialize your data structure here. */
	MedianFinder() {
	}

	void addNum(int num) {
		if (min_pq.size() >= max_pq.size())
		{
			// 永远是, 在 min_pq 中, 选一个最小的, 加到 max_pq 中
			min_pq.push(num);
			max_pq.push(min_pq.top());
			min_pq.pop();
		}
		else {
			max_pq.push(num);
			min_pq.push(max_pq.top());
			max_pq.pop();
		}
	}

	double findMedian() {
		if (max_pq.size() > min_pq.size())
			return max_pq.top();
		return (max_pq.top() + min_pq.top()) / 2.0;
	}
};

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */