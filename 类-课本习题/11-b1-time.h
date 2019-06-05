// 1752762 ¼Æ1°à ÎºðÙ´ï
#include <iostream>
using namespace std;

class Time {
protected:
	int hour;
	int minute;
	int second;
public:
	Time();
	Time(const int _hour, const int _minute, const int _second);
	Time(const int seconds_total);
	void set(const int _hour, const int _minute, const int _second);
	void set(const int seconds_total);
	operator int();
	friend istream& operator>>(istream& is, Time& ti);
	friend ostream& operator<<(ostream& os, const Time& ti);
	friend Time operator+(Time& ti1, const int ti2);
	friend Time operator+(const int ti1, Time& ti2);
	friend int operator-(Time& ti1, Time& ti2);
	friend Time operator-(Time& ti1, const int ti2);
	Time& operator++();
	Time operator++(int);
	Time& operator--();
	Time operator--(int);
	friend bool operator>(Time& t1, Time& t2);
	friend bool operator>=(Time& t1, Time& t2);
	friend bool operator<(Time& t1, Time& t2);
	friend bool operator<=(Time& t1, Time& t2);
	friend bool operator==(Time& t1, Time& t2);
	friend bool operator!=(Time& t1, Time& t2);
};