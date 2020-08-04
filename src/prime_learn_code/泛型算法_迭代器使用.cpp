//#include <iostream>
//#include <algorithm>
//#include <vector>
//#include <list>
//#include <forward_list>
//#include <iterator>
//#include <set>
//using namespace std;
//
//// STL 分为 序列式容器（Sequence Containers）和关联式容器（Associative Containers）两大类
//template <typename Sequence> void print(Sequence const& seq)
//{
//	for (const auto& i : seq) std::cout << i << " ";
//	std::cout << std::endl;
//}
//
//int main()
//{
//	std::vector<float> vec_0{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//	auto inserter_it = inserter(vec_0, vec_0.begin() + 3); // 创建一个指向 4 的插入迭代器
//	*inserter_it = 3.3;
//	*inserter_it = 3.4;
//	print(vec_0);
//	// 0, 1, 2, 3, 3.3, 3.4, 4, ...
//
//	std::vector<int> vec{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };
//
//	// uses inserter
//	list<int> lst1;
//	copy(vec.cbegin(), vec.cend(), inserter(lst1, lst1.begin()));
//	print(lst1);
//
//	// uses back_inserter
//	list<int> lit2;
//	copy(vec.cbegin(), vec.cend(), back_inserter(lit2));
//	print(lit2);
//
//	// uses front_inserter
//	list<int> lst3;
//	copy(vec.cbegin(), vec.cend(), front_inserter(lst3));
//	print(lst3);
//	// 这个是倒序，其他是正序
//
//	//// stream iterator
//	//// 直接用输入构造一个 vec，显得非常的方便，非常的实用，在做题的时候，可以这样直接构建一个 vector
//	//istream_iterator<int> in_iter(cin), eof;
//	//vector<int> vec_for_in_iter(in_iter, eof);
//
//	std::list<int> l = { 3, 7, 0, -3, -4, 0, 5 };
//	auto found = std::find(l.crbegin(), l.crend(), 0); // 反向迭代器，实用 base() 后，指向的是下一个
//	std::cout << *found << " in front of " << *found.base() << std::endl;
//
//	//forward_list<int> l = { 1,2,3,4,5,6 };
//	//reverse(l.cbegin(), l.cend()); // 这样写不会报错，但是编译不能通过
//
//	vector<int> v_out;
//	v_out.resize(l.size());
//	transform(l.begin(), l.begin(), v_out.begin(), [](int i) {if (i < 0) return  i < 0 ? -i : i; });
//
//	std::multiset<int, bool(*)(const int& lhs, const int& rhs)>;
//
//	std::list<int> l1 = { 3, 7, 0, -3, -4, 0, 5 };
//	std::list<int> l2 = { 1, -2, -1, 2, 8};
//
//	l1.merge(l2);
//}