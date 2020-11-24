// 力扣
// https://leetcode-cn.com/problems/implement-strstr/

// 学习
// https://labuladong.gitbook.io/algo/dong-tai-gui-hua-xi-lie/1.5-qi-ta-jing-dian-wen-ti/dong-tai-gui-hua-zhi-kmp-zi-fu-pi-pei-suan-fa

// 解法, KMP算法
// 参考资料
// https://blog.csdn.net/dark_cy/article/details/88698736

// 说一下我理解的 KMP
// KMP 的 核心, 是构建 next 数组
// 这个数组代表, 
// s, 和 p 在匹配时, p 做一次回溯, 而不是全部重新来
// p 的回溯跟 p 本身有关, 跟 s 是无关的
// 记住 next[0] = -1 用于表示 只有第一个数时的状态(或者说, 直接回溯到 -1 的位置开始匹配)
// 而 next[x]+1 就是我们需要匹配的下一个字符

#include<string>
using std::string;

#include<vector>
using std::vector;

class Solution {
public:
	int strStr(string haystack, string needle) {
		if (needle.empty()) return 0;
		// 第一步, 构建 next 数组
		vector<int> next(needle.size());
		next[0] = -1;
		int k = -1, j = 0;
		while (j < needle.size())
		{
			// 我们在无法匹配的时候, 我们会回滚到 -1 的位置, 这个时候, 相当于开始重新记录
			if (k == -1 || needle[k] == needle[j])
			{
				++j;
				++k;
				if (j < needle.size()) // 注意这里超出界限的情况
					next[j] = k; // 记录这个回溯的位置
			}
			else {
				// 如果我们做内部匹配, 不行了, 我们回到我们上一次的匹配结果
				k = next[k];
			}
		}

		// next 数组
		// lll   -1 0 1 (两个开头, 都是 -1 0)
		// llo   -1 0 1 (o 如果不匹配, 但是我们的父串有 ll, 所以从 第二个 l 开始即可)
		// lob   -1 0 0 (b 如果不匹配, 就回到 l 开始)

		// 第二步, 使用 next 数组做匹配
		// 这个匹配, 不能用 for, 需要用 while 因为 haystack 的部分可能不需要递增(比如匹配到不符合的, i 是不递增的)
		int i = 0; // haystack 的 index
		j = 0; // needle 的 index
		// 注意 size 要先 int(), 不然 j = -1 时, 会视为一个很大的整数
		while (i < haystack.size() && j < int(needle.size()))
		{
			if (j == -1 || haystack[i] == needle[j])
			{
				++i;
				++j;
				continue;
			}
			j = next[j];
		}
		if (j < int(needle.size())) return -1;
		return i - j;
	}
};