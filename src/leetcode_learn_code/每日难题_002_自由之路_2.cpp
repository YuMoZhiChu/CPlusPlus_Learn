//// 这个标准答案十分的优美
//// 1. 映射关系，用 vector 来做，O1
//// 2. dp中，利用 pos 特性，做到动归的解，是常数项的，非常的nice
//
//#include<string>
//using std::string;
//
//#include<vector>
//using std::vector;
//
//#include<algorithm>
//using std::min;
//using std::min_element;
//
//class Solution {
//public:
//	int findRotateSteps(string ring, string key) {
//		int n = ring.size(), m = key.size();
//		vector<int> pos[26];
//		for (int i = 0; i < n; ++i) {
//			pos[ring[i] - 'a'].push_back(i);
//		}
//		int dp[m][n]; // 力扣做了优化？这个可行？
//		memset(dp, 0x3f3f3f3f, sizeof(dp));
//		for (auto& i : pos[key[0] - 'a']) {
//			dp[0][i] = min(i, n - i) + 1;
//		}
//		for (int i = 1; i < m; ++i) {
//			for (auto& j : pos[key[i] - 'a']) {
//				for (auto& k : pos[key[i - 1] - 'a']) {
//					dp[i][j] = min(dp[i][j], dp[i - 1][k] + min(abs(j - k), n - abs(j - k)) + 1);
//				}
//			}
//		}
//		return *min_element(dp[m - 1], dp[m - 1] + n);
//	}
//};
