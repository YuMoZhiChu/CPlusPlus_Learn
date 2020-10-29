#include<vector>
using std::vector;

class Solution {
public:

	int lengthOfLIS(vector<int>& nums) {
		if (nums.empty()) return 0;
		// dp[i] �� nums[i] ��β, �������������� �� ����
		// stack_table �� �������� ���ƶѱ�, �����, �ƶ��������һ��
		int *stack_table = new int[nums.size()]();
		int stack_size = 0;// �ƶ������Ĵ�С
		// n ^ 2 ���ĵı���
		for (int i = 0; i < nums.size(); ++i)
		{
			// �����ö��ֲ���, ����, �ҵ�������Ӧ�÷ŵ�λ��
			// ��Ϊ, ������ά��, �ƶ��������һ����, һ����һ��������˳��
			// ����һ����, �����½�һ���ƶ�
			int left = 0;
			int right = stack_size; // ����ҿ�
			while (left < right)
			{
				int mid = (left + right) / 2;
				// ����м���, ���ڵ�ǰ��, ��ô����Ӧ���� ����
				if (stack_table[mid] > nums[i])
					right = mid;
				// ����м���, С�ڵ�ǰ��, �����������, ���Ұ��, ��Ϊ����Ǳ�����, ����+1
				else if (stack_table[mid] < nums[i])
					left = mid + 1;
				// ������ȵ����, ��Ϊrihgt�Ǳ�����, ����ͨ��ֱ���ų�right, ���� left �� right ���
				else
					right = mid;
			}
			// ����һ���µ��ƶ�
			if (left == stack_size) stack_size++;
			// �����Ʒ����ƶѵ�������
			stack_table[left] = nums[i];
		}
		delete[] stack_table;
		// �ƶѵĸ���, ���������������
		return stack_size;
	}
};