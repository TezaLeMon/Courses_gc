// 1752762 ��1�� κ�ٴ�
#include <iostream>
using namespace std;

class Date {
protected:
	int year;
	int month;
	int day;
public:
	Date();
	Date(const int _year, const int _month, const int _day);
	Date(const int days_total);
	void set(const int _year, const int _month, const int _day);
	void set(const int days_total);
	operator int();
	friend istream& operator>>(istream& is, Date& da);
	friend ostream& operator<<(ostream& os, const Date& da);
	friend Date operator+(Date& da1, const int da2);
	friend Date operator+(const int da1, Date& da2);
	friend int operator-(Date& da1, Date& da2);
	friend Date operator-(Date& da1, const int da2);
	Date& operator++();
	Date operator++(int);
	Date& operator--();
	Date operator--(int);
	friend bool operator>(Date& t1, Date& t2);
	friend bool operator>=(Date& t1, Date& t2);
	friend bool operator<(Date& t1, Date& t2);
	friend bool operator<=(Date& t1, Date& t2);
	friend bool operator==(Date& t1, Date& t2);
	friend bool operator!=(Date& t1, Date& t2);
};

//д����ȫ�ֺ���	��Ϊ��date.cpp datetime.cpp�ﶼ��Ҫʹ��
int is_leap(const int year);