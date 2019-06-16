// 1752762 计1班 魏鹳达

#include <math.h>
#include <iostream>
using namespace std;

#define dx 0.1	//积分精度

class integral {
public:
	virtual double value() = 0;
};

class integral_sin :public integral {
private:
	double low;
	double high;
public:
	virtual double value();
	friend istream& operator>>(istream& is, integral_sin& it_s);	//未检查输入合法性
};

double integral_sin::value() {	//可以和其他类一起 用一个函数来实现（使用函数指针）
	double i, s = 0;
	for (i = low; high - i > 1e-6; i += dx)
		s += dx * sin(i);
	return s;
}

istream& operator>>(istream& is, integral_sin& it_s) {
	cout << "输入sin积分上下限" << endl;
	is >> it_s.high >> it_s.low;
	return is;
}

class integral_cos :public integral {
private:
	double low;
	double high;
public:
	virtual double value();
	friend istream& operator>>(istream& is, integral_cos& it_c);	//未检查输入合法性
};

double integral_cos::value() {
	double i, s = 0;
	for (i = low; high - i > 1e-6; i += dx)
		s += dx * cos(i);
	return s;
}

istream& operator>>(istream& is, integral_cos& it_c) {	//未检查输入合法性
	cout << "输入cos积分上下限" << endl;
	is >> it_c.high >> it_c.low;
	return is;
}

class integral_exp :public integral {
private:
	double low;
	double high;
public:
	virtual double value();
	friend istream& operator>>(istream& is, integral_exp& it_e);	//未检查输入合法性
};

double integral_exp::value() {
	double i, s = 0;
	for (i = low; high - i > 1e-6; i += dx)
		s += dx * exp(i);
	return s;
}

istream& operator>>(istream& is, integral_exp& it_e) {	//未检查输入合法性
	cout << "输入exp积分上下限" << endl;
	is >> it_e.high >> it_e.low;
	return is;
}

int main()
{
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;
	integral *p;

	cin >> s1;	//输入上下限
	p = &s1;
	cout << p->value() << endl;
	cin >> s2;	//输入上下限
	p = &s2;
	cout << p->value() << endl;
	cin >> s3;	//输入上下限
	p = &s3;
	cout << p->value() << endl;

	return 0;
}