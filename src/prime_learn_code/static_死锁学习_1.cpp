class TestA
{
public:
	TestA() {
		hello();
	}

	void hello() {
	}
};

TestA TestThread2();

TestA TestThread1()
{
	// 并不会堆栈溢出，反而会导致死锁
	// 会尝试初始化 2 次 static a 导致死锁
	static TestA a = TestThread2();
	return a;
}

TestA TestThread2()
{
	static TestA b = TestThread1();
	return b;
}

void TestRun()
{
	TestThread1();
}
//int main()
//{
//	// TestRun();
//
//
//
//
//	int bk = 1;
//}