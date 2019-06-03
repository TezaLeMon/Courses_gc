// 1752762 ¼Æ1°à ÎºðÙ´ï
#include "11-b1-time.h"

Time::Time() {
	hour = 0;
	minute = 0;
	second = 0;
}

Time::Time(const int _hour, const int _minute, const int _second) {
	if (_hour < 0 || _hour > 23 || _minute < 0 || _minute > 59 || _second < 0 || _second > 59) {
		Time();
		return;
	}
	hour = _hour;
	minute = _minute;
	second = _second;
}

Time::Time(const int seconds) {
	second = seconds % 60;
	minute = seconds % 3600 / 60;
	hour = seconds / 3600;
}

void Time::set(const int _hour, const int _minute, const int _second) {
	Time(_hour, _minute, _second);
}

Time::operator int() {
	return second + minute * 60 + hour * 3600;
}

istream& operator>>(istream& is, Time& ti) {
	int h, m, s;
	is >> h >> m >> s;
	Time(h, m, s);
	return is;
}

ostream& operator<<(ostream& os, const Time& ti) {
	os << ti.hour << ":" << ti.minute << ":" << ti.second;
	return os;
}

Time operator+(Time& ti1, const int ti2) {

}

Time operator+(const int ti1, Time& ti2) {

}

int operator-(Time& ti1, Time& ti2) {

}

Time operator-(Time& ti1, const int ti2) {

}

Time& Time::operator++() {

}

Time& Time::operator++(int) {

}

Time& Time::operator--() {

}

Time& Time::operator--(int) {

}