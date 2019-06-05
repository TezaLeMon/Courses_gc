// 1752762 计1班 魏鹳达
#include "11-b1-date.h"
#include "11-b1-time.h"
#include <iostream>
using namespace std;

class DateTime :public Date, public Time {
public:
	DateTime();
	DateTime(const int _year, const int _month, const int _day, const int _hour, const int _minute, const int _second);
	DateTime(const long long seconds_total);
	void set(const int _year, const int _month, const int _day, const int _hour, const int _minute, const int _second);
	void set(const long long seconds_total);
	operator long long();
	friend istream& operator>>(istream& is, DateTime& dt);
	friend ostream& operator<<(ostream& os, const DateTime& dt);
	friend DateTime operator+(DateTime& dt1, const long long dt2);	//考虑到可能会加一个大数的情况 但书写时需要如 x + 5LL 的形式
	friend DateTime operator+(const long long dt1, DateTime& dt2);
	friend long long operator-(DateTime& dt1, DateTime& dt2);
	friend DateTime operator-(DateTime& dt1, const long long dt2);
	DateTime& operator++();
	DateTime operator++(int);
	DateTime& operator--();
	DateTime operator--(int);
	friend bool operator>(DateTime& t1, DateTime& t2);
	friend bool operator>=(DateTime& t1, DateTime& t2);
	friend bool operator<(DateTime& t1, DateTime& t2);
	friend bool operator<=(DateTime& t1, DateTime& t2);
	friend bool operator==(DateTime& t1, DateTime& t2);
	friend bool operator!=(DateTime& t1, DateTime& t2);
};