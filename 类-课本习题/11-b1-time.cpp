// 1752762 ¼Æ1°à ÎºðÙ´ï
#include "11-b1-time.h"

Time::Time() {
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(const int _hour, const int _minute, const int _second) {
	if (_hour < 0 || _hour > 23 || _minute < 0 || _minute > 59 || _second < 0 || _second > 59) {
		hour = 0;
		minute = 0;
		second = 0;
		return;
	}
	hour = _hour;
	minute = _minute;
	second = _second;
}

Time::Time(const int seconds_total) {
	if (seconds_total <= 0 || seconds_total >= 86400) {
		second = 0;
		minute = 0;
		hour = 0;
		return;
	}

	second = seconds_total % 60;
	minute = seconds_total % 3600 / 60;
	hour = seconds_total / 3600 % 24;
}

void Time::set(const int _hour, const int _minute, const int _second) {
	if (_hour < 0 || _hour > 23 || _minute < 0 || _minute > 59 || _second < 0 || _second > 59) {
		hour = 0;
		minute = 0;
		second = 0;
		return;
	}
	hour = _hour;
	minute = _minute;
	second = _second;
}

void Time::set(const int seconds_total) {
	if (seconds_total <= 0 || seconds_total >= 86400) {
		second = 0;
		minute = 0;
		hour = 0;
		return;
	}

	second = seconds_total % 60;
	minute = seconds_total % 3600 / 60;
	hour = seconds_total / 3600 % 24;
}

Time::operator int() {
	return second + minute * 60 + hour * 3600;
}

istream& operator>>(istream& is, Time& ti) {
	int h, m, s;
	is >> h >> m >> s;
	ti.set(h, m, s);
	return is;
}

ostream& operator<<(ostream& os, const Time& ti) {
	os << ti.hour << ":" << ti.minute << ":" << ti.second;
	return os;
}

Time operator+(Time& ti1, const int ti2) {
	return int(ti1) + ti2;
}

Time operator+(const int ti1, Time& ti2) {
	return ti1 + int(ti2);
}

int operator-(Time& ti1, Time& ti2) {
	return (ti1.second + ti1.minute * 60 + ti1.hour * 3600) - (ti2.second + ti2.minute * 60 + ti2.hour * 3600);
}

Time operator-(Time& ti1, const int ti2) {
	return (ti1.second + ti1.minute * 60 + ti1.hour * 3600) - ti2;
}

Time& Time::operator++() {
	second++;
	if (second == 60) {
		second = 0;
		minute++;
		if (minute == 60) {
			minute = 0;
			hour++;
			if (hour == 24) {
				hour = 0;
			}
		}
	}
	return *this;
}

Time Time::operator++(int) {
	Time t(*this);

	second++;
	if (second == 60) {
		second = 0;
		minute++;
		if (minute == 60) {
			minute = 0;
			hour++;
			if (hour == 24) {
				hour = 0;
			}
		}
	}

	return t;
}

Time& Time::operator--() {
	second--;
	if (second == -1) {
		second = 59;
		minute--;
		if (minute == -1) {
			minute = 59;
			hour--;
			if (hour == -1) {
				hour = 23;
			}
		}
	}
	return *this;
}

Time Time::operator--(int) {
	Time t(*this);

	second--;
	if (second == -1) {
		second = 59;
		minute--;
		if (minute == -1) {
			minute = 59;
			hour--;
			if (hour == -1) {
				hour = 23;
			}
		}
	}

	return t;
}

bool operator<(Time& a, Time& b)
{
	if (a.hour > b.hour)
		return 0;
	if (a.hour < b.hour)
		return 1;
	if (a.minute > b.minute)
		return 0;
	if (a.minute < b.minute)
		return 1;
	return a.second < b.second;
}

bool operator<=(Time& a, Time& b)
{
	if (a.hour > b.hour)
		return 0;
	if (a.hour < b.hour)
		return 1;
	if (a.minute > b.minute)
		return 0;
	if (a.minute < b.minute)
		return 1;
	return a.second <= b.second;
}

bool operator>(Time& a, Time& b)
{
	if (a.hour > b.hour)
		return 1;
	if (a.hour < b.hour)
		return 0;
	if (a.minute > b.minute)
		return 1;
	if (a.minute < b.minute)
		return 0;
	return a.second > b.second;
}

bool operator>=(Time& a, Time& b)
{
	if (a.hour > b.hour)
		return 1;
	if (a.hour < b.hour)
		return 0;
	if (a.minute > b.minute)
		return 1;
	if (a.minute < b.minute)
		return 0;
	return a.second >= b.second;
}

bool operator==(Time& a, Time& b)
{
	return a.hour == b.hour&&a.minute == b.minute&&a.second == b.second;
}

bool operator!=(Time& a, Time& b)
{
	return !(a.hour == b.hour&&a.minute == b.minute&&a.second == b.second);
}