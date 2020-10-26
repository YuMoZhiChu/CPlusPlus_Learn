#include<iostream>
using std::cin;
using std::cout;
using std::endl;

#include<vector>
using std::vector;

#include<climits>

#include<algorithm>
using std::min;

class Solution {
public:
	int coinChange(vector<int>& coins, int amount) {
		vector<int> memo(amount+1, INT_MAX);
		// 记录本
		memo[0] = 0;
		for (int i = 1; i < memo.size(); ++i)
		{
			for (int coin : coins)
			{
				// 子方案不成立
				if (i < coin) continue;
				// 子方案不成立，父方案也不成立
				if (memo[i - coin] == INT_MAX) continue;
				memo[i] = min(memo[i], memo[i-coin]+1);
			}
		}
		return memo[amount] == INT_MAX ? -1 : memo[amount];
	}
};

int main()
{
	vector<int> test;
	int result;

	test = { 1, 2, 5 };
	result = Solution().coinChange(test, 11);
	cout << result << endl;

	test = { 2 };
	result = Solution().coinChange(test, 3);
	cout << result << endl;

	test = { 1 };
	result = Solution().coinChange(test, 1);
	cout << result << endl;
}

