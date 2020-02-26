//#include <iostream>
//#include <memory>
//#include <string>
//using namespace std;
//
//// 假设有这么一个继承链
//class Investment {};
//class Stock :public Investment{};
//class Bond :public Investment{};
//class RealEstate :public Investment{};
//
//template<typename... Ts>
//unique_ptr<Investment> makeInvestment()
//{
//	// some logic
//	return unique_ptr<Investment>(new Investment());
//}
//
//int main()
//{
//	{
//		// 右值形势的 unique_ptr 可以对 shared_ptr 直接赋值
//		shared_ptr<Investment> p2 = makeInvestment();
//
//		// 这是移动, 不会改变引用
//		auto p3 = move(p2);
//		cout << p3.use_count() << endl;
//
//		// 这是拷贝, 会增加引用
//		auto p4 = p3;
//		cout << p4.use_count() << endl;
//	}
//	{
//		auto pw = new Investment;
//		shared_ptr<Investment> spw1(pw);
//		shared_ptr<Investment> spw2(pw);
//
//		// 正确的写法
//		/*shared_ptr<Investment> spw1(new Investment);
//		shared_ptr<Investment> spw2(spw1);*/
//
//		// 这段代码运行会直接报错, 具体原因是 基于 shared_ptr 的 control-block 机制
//	}
//	{
//		
//	}
//}
//
//
