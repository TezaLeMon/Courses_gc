// 1752762 ¼Æ1°à ÎºğÙ´ï
#include <iostream>
using namespace std;

class Date {
private:
	int year;
	int month;
	int day;
public:
	Date();
	Date(const int _year, const int _month, const int _day);
	Date(const int days);
	void set(const int _year, const int _month, const int _day);
	operator int();
	friend istream& operator>>(istream& is, Date& da);
	friend ostream& operator<<(ostream& os, const Date& da);
	friend Date operator+(Date& da1, const int da2);
	friend Date operator+(const int da1, Date& da2);
	friend int operator-(Date& da1, Date& da2);
	friend Date operator-(Date& da1, const int da2);
	Date& operator++();
	Date& operator++(int);
	Date& operator--();
	Date& operator--(int);
};