#include<vector>
using std::vector;

class Solution {
public:
	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty()) return 0;
		// dp[i] �� nums[i] ��β, �������������� �� ����
		const int nums_size = nums.size();
		int *dp = new int[nums_size]();
		// һ������β, ������ 1 - 1, ���г���Ӧ�ó�ʼ��Ϊ 1, ����Ϊ�˷���
		dp[0] = 0;
		// n ^ 2 ���ĵı���
		for (int i = 1; i < nums_size; ++i)
		{
			for (int j = 0; j < i; ++j)
			{
				if (nums[j] < nums[i])
				{
					dp[i] = dp[j] + 1 > dp[i] ? dp[j] + 1 : dp[i];
				}
			}
		}

		// ����dp ȡ���ֵ
		int max = 0;
		for (int i = 0; i < nums_size; ++i)
		{
			max = dp[i] > max ? dp[i] : max;
		}
		delete[] dp;
		// ���϶�ʧ�� 1
		return max + 1;
	}
};