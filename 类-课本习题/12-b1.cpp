// 1752762 ��1�� κ�ٴ�

#include <math.h>
#include <iostream>
using namespace std;

#define dx 0.1	//���־���

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
	friend istream& operator>>(istream& is, integral_sin& it_s);	//δ�������Ϸ���
};

double integral_sin::value() {	//���Ժ�������һ�� ��һ��������ʵ�֣�ʹ�ú���ָ�룩
	double i, s = 0;
	for (i = low; high - i > 1e-6; i += dx)
		s += dx * sin(i);
	return s;
}

istream& operator>>(istream& is, integral_sin& it_s) {
	cout << "����sin����������" << endl;
	is >> it_s.high >> it_s.low;
	return is;
}

class integral_cos :public integral {
private:
	double low;
	double high;
public:
	virtual double value();
	friend istream& operator>>(istream& is, integral_cos& it_c);	//δ�������Ϸ���
};

double integral_cos::value() {
	double i, s = 0;
	for (i = low; high - i > 1e-6; i += dx)
		s += dx * cos(i);
	return s;
}

istream& operator>>(istream& is, integral_cos& it_c) {	//δ�������Ϸ���
	cout << "����cos����������" << endl;
	is >> it_c.high >> it_c.low;
	return is;
}

class integral_exp :public integral {
private:
	double low;
	double high;
public:
	virtual double value();
	friend istream& operator>>(istream& is, integral_exp& it_e);	//δ�������Ϸ���
};

double integral_exp::value() {
	double i, s = 0;
	for (i = low; high - i > 1e-6; i += dx)
		s += dx * exp(i);
	return s;
}

istream& operator>>(istream& is, integral_exp& it_e) {	//δ�������Ϸ���
	cout << "����exp����������" << endl;
	is >> it_e.high >> it_e.low;
	return is;
}

int main()
{
	integral_sin s1;
	integral_cos s2;
	integral_exp s3;
	integral *p;

	cin >> s1;	//����������
	p = &s1;
	cout << p->value() << endl;
	cin >> s2;	//����������
	p = &s2;
	cout << p->value() << endl;
	cin >> s3;	//����������
	p = &s3;
	cout << p->value() << endl;

	return 0;
}