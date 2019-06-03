// 1752762 计1班 魏鹳达
#include "11-b1-datetime.h"

DateTime::DateTime() :Date(), Time() {

}

DateTime::DateTime(const int _year, const int _month, const int _day, const int _hour, const int _minute, const int _second){
	if (_year < 1900 || _year > 2099 || _month < 1 || _month>12|| _hour < 0 || _hour > 23 || _minute < 0 || _minute > 59 || _second < 0 || _second > 59) {
		Date::set(1900, 1, 1);
		Time::set(0, 0, 0);
		return;
	}

	int day_all[13] = { 0,31,28 + is_leap(_year),31,30,31,30,31,31,30,31,30,31 };

	if (_day < 1 || _day > day_all[_month]) {
		Date::set(1900, 1, 1);
		Time::set(0, 0, 0);
		return;
	}

	Date::set(_year, _month, _day);
	Time::set(_hour, _minute, _second);
}

DateTime::DateTime(const long long seconds_total) {
	if (seconds_total <= 0|| seconds_total >= 6311433600) {	//	24 * 60 * 60 * 73049
		Date::set(1900, 1, 1);
		Time::set(0, 0, 0);
		return;
	}
	Date::set(int(seconds_total / 86400 + 1));	//24 * 60 * 60 = 86400
	Time::set(seconds_total % 86400);
}

void DateTime::set(const int _year, const int _month, const int _day, const int _hour, const int _minute, const int _second) {
	if (_year < 1900 || _year > 2099 || _month < 1 || _month>12 || _hour < 0 || _hour > 23 || _minute < 0 || _minute > 59 || _second < 0 || _second > 59) {
		Date::set(1900, 1, 1);
		Time::set(0, 0, 0);
		return;
	}

	int day_all[13] = { 0,31,28 + is_leap(_year),31,30,31,30,31,31,30,31,30,31 };

	if (_day < 1 || _day > day_all[_month]) {
		Date::set(1900, 1, 1);
		Time::set(0, 0, 0);
		return;
	}

	Date::set(_year, _month, _day);
	Time::set(_hour, _minute, _second);
}

void DateTime::set(const long long seconds_total) {
	if (seconds_total <= 0 || seconds_total >= 6311433600) {	//	24 * 60 * 60 * 73049
		Date::set(1900, 1, 1);
		Time::set(0, 0, 0);
		return;
	}

	Date::set(int(seconds_total / 86400 + 1));	//24 * 60 * 60 = 86400
	Time::set(seconds_total % 86400);
}

DateTime::operator long long() {
	return Time::operator int() + 86400LL * (Date::operator int() - 1);
}

istream& operator>>(istream& is, DateTime& dt) {
	int y, mo, d, h, mi, s;
	is >> y >> mo >> d >> h >> mi >> s;
	dt.Date::set(y, mo, d);
	dt.Time::set(h, mi, s);
	return is;
}

ostream& operator<<(ostream& os, const DateTime& dt) {
	os << dt.year << '-' << dt.month << '-' << dt.day << ' ' << dt.hour << ':' << dt.minute << ':' << dt.second;
	return os;
}

DateTime operator+(DateTime& dt1, const long long dt2) {
	return long long(dt1) + dt2;
}

DateTime operator+(const long long dt1, DateTime& dt2) {
	return dt1 + long long(dt2);
}

long long operator-(DateTime& dt1, DateTime& dt2) {
	return long long(dt1) - long long(dt2);
}

DateTime operator-(DateTime& dt1, const long long dt2) {
	return long long(dt1) - dt2;
}

DateTime& DateTime::operator++() {
	Time::operator++();
	if (hour == 0 && minute == 0 && second == 0)
		Date::operator++();

	return *this;
}

DateTime DateTime::operator++(int) {
	DateTime dt(*this);

	Time::operator++();
	if (hour == 0 && minute == 0 && second == 0)
		Date::operator++();

	return dt;
}

DateTime& DateTime::operator--() {
	Time::operator--();
	if (hour == 23 && minute == 59 && second == 59)
		Date::operator--();

	return *this;
}

DateTime DateTime::operator--(int) {
	DateTime dt(*this);

	Time::operator--();
	if (hour == 23 && minute == 59 && second == 59)
		Date::operator--();

	return dt;
}
