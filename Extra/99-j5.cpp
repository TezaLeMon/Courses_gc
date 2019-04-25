// 1752762 计1班 魏鹳达
#include <iostream>
using namespace std;

void f_sub(int x)
{
	cout << "x = " << x << endl;
}

void* fun1(const char *p)
{
	cout << "str = " << p << endl;
	return f_sub;
}

int main()
{
	void(*(*f[3])(const char *p))(int x);
	//void (*(*f[])())()
	//优先级 () = [] > *
	//1. f[3] f为数组
	//2. *f[3] f为指针数组
	//3. (*f[3])(char *p) 函数指针 函数参数为char *p  之后用P替代(*f[3])(char *p)来看 即将P看作整体
	//void (*P)(int x)
	//4. (*P) 指针
	//5. void (*P)(int x) 函数指针 返回类型为void 参数为int x
	//头昏...fun1函数的返回类型似乎是不对的...但是写成void系统就忽略掉了这一点（大概吧

	f[0] = (void(*(*)(const char *p))(int x))fun1;

	f[0]("Hello")(2);
	f[0]("Tongji")(7);

	return 0;
}
