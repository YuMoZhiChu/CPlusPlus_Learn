// 力扣
// https://leetcode-cn.com/problems/design-twitter/
// 学习
// https://labuladong.gitbook.io/algo/shu-ju-jie-gou-xi-lie/2.4-shou-ba-shou-she-ji-shu-ju-jie-gou/she-ji-twitter

#include<unordered_map>
using std::unordered_map;

#include<unordered_set>
using std::unordered_set;
using std::pair;

#include<forward_list>
using std::forward_list;

#include<vector>
using std::vector;

class Twitter {
	int time; // 定义时间
	// name ID - friendSet 查询在 O(logn)
	unordered_map<int, unordered_set<int>> name2friend_table;
	struct TweetMsg
	{
		TweetMsg(int _time, int _tweetId) :time(_time), tweetId(_tweetId) {}
		int time; // 发推的时间
		int tweetId; // 这一条推的ID
	};
	// name ID - 这个人发的 TweetList
	unordered_map<int, forward_list<TweetMsg>> name2tweets_table;

	inline void new_a_user(int userId)
	{
		name2friend_table.emplace(userId, unordered_set<int>());
		name2tweets_table.emplace(userId, forward_list<TweetMsg>({}));
	}

public:
	/** Initialize your data structure here. */
	Twitter() {
		time = 0;
		name2friend_table.clear();
		name2tweets_table.clear();
	}

	/** Compose a new tweet. */
	void postTweet(int userId, int tweetId) {
		if (name2friend_table.find(userId) == name2friend_table.end())
		{
			new_a_user(userId);
		}
		name2tweets_table[userId].emplace_front(time, tweetId);
		++time;
	}

	/** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
	vector<int> getNewsFeed(int userId) {
		if (name2friend_table.find(userId) == name2friend_table.end())
		{
			new_a_user(userId);
			return {}; // 新用户, 自然啥也没有
		}
		vector< forward_list<TweetMsg>* > find_vec({
			&name2tweets_table[userId]
			}); // 初始化有自己
		auto friends = name2friend_table[userId];
		for (int friendId : friends)
		{
			// 加入内容
			find_vec.push_back(
				&name2tweets_table[friendId]
			);
		}
		vector<forward_list<TweetMsg>::iterator> it_vec(find_vec.size());
		for (int i = 0; i < find_vec.size(); ++i)
		{
			it_vec[i] = find_vec[i]->begin(); // 一开始全部指向开头
		}

		vector<int> result;
		while (result.size() != 10)
		{
			int max_time = -1; // 选取最大时间
			int record_i = -1;
			for (int i = 0; i < find_vec.size(); ++i)
			{
				if (it_vec[i] == find_vec[i]->end()) continue;
				if (it_vec[i]->time > max_time)
				{
					max_time = it_vec[i]->time;
					record_i = i;
				}
			}
			// 没有了, 找不到了
			if (max_time == -1) break;
			result.push_back(it_vec[record_i]->tweetId);
			++it_vec[record_i]; // 记录也要往前走一走
		}
		return result;
	}

	/** Follower follows a followee. If the operation is invalid, it should be a no-op. */
	void follow(int followerId, int followeeId) {
		if (followerId == followeeId) return;
		if (name2friend_table.find(followerId) == name2friend_table.end())
		{
			new_a_user(followerId);
		}
		if (name2friend_table.find(followeeId) == name2friend_table.end())
		{
			new_a_user(followeeId);
		}
		name2friend_table[followerId].insert(followeeId); // 加入关注
	}

	/** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
	void unfollow(int followerId, int followeeId) {
		if (followerId == followeeId) return;
		name2friend_table[followerId].erase(followeeId);
	}
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter* obj = new Twitter();
 * obj->postTweet(userId,tweetId);
 * vector<int> param_2 = obj->getNewsFeed(userId);
 * obj->follow(followerId,followeeId);
 * obj->unfollow(followerId,followeeId);
 */