// 1752762 计1班 魏鹳达
#include "11-b1-date.h"

int is_leap(const int year) 
{
	return (year % 4 == 0 && year % 100) || year % 400 == 0;
}

Date::Date() {
	year = 1900;
	month = 1;
	day = 1;
}

Date::Date(const int _year, const int _month, const int _day) {
	if (_year < 1900 || _year > 2099 || _month < 1 || _month>12) {
		Date();
		return;
	}

	int day_all[13] = { 0,31,28 + is_leap(_year),31,30,31,30,31,31,30,31,30,31 };

	if (_day<1 || _day>day_all[_month]) {
		Date();
		return;
	}

	year = _year;
	month = _month;
	day = _day;
}

Date::Date(const int days) {

}

void Date::set(const int _year, const int _month, const int _day) {
	Date(_year, _month, _day);
}

Date::operator int() {

}

istream& operator>>(istream& is, Date& da) {
	int y, m, d;
	is >> y >> m >> d;	//不考虑非法输入
	da.set(y, m, d);
	return is;
}

ostream& operator<<(ostream& os, const Date& da) {
	os << da.year << '-' << da.month << '-' << da.day;
	return os;
}

Date operator+(Date& da1, const int da2) {
	return Date(int(da1) + da2);
}

Date operator+(const int da1, Date& da2) {
	return Date(da1 + int(da2));
}

int operator-(Date& da1, Date& da2) {
	return int(da1) - int(da2);
}

Date operator-(Date& da1, const int da2) {
	return Date(int(da1) - da2);
}

Date& Date::operator++() {
	int day_all[13] = { 0,31,28 + is_leap(year),31,30,31,30,31,31,30,31,30,31 };

	day++;
	if (day > day_all[month]) {
		month++;
		day = 1;
		if (month > 12) {
			month = 1;
			year++;
			if (year > 2099) {
				year = 2099;
				month = 12;
				day = 31;
				return *this;
			}
		}
	}
	return *this;
}

Date& Date::operator++(int) {
	int day_all[13] = { 0,31,28 + is_leap(year),31,30,31,30,31,31,30,31,30,31 };

	day++;
	if (day > day_all[month]) {
		month++;
		day = 1;
		if (month > 12) {
			month = 1;
			year++;
			if (year > 2099) {
				year = 2099;
				month = 12;
				day = 31;
				return *this;
			}
		}
	}
	return *this;
}

Date& Date::operator--() {
	int day_all[13] = { 0,31,28 + is_leap(year),31,30,31,30,31,31,30,31,30,31 };

	day--;
	if (day < 1) {
		month--;
		if (month < 1) {
			month = 12;
			year--;
			if (year < 1900) {
				year = 1900;
				month = 1;
				day = 1;
				return *this;
			}
		}
		day = day_all[month];
	}

	return *this;
}

Date& Date::operator--(int) {
	Date d(*this);
	int day_all[13] = { 0,31,28 + is_leap(year),31,30,31,30,31,31,30,31,30,31 };

	day--;
	if (day < 1) {
		month--;
		if (month < 1) {
			month = 12;
			year--;
			if (year < 1900) {
				year = 1900;
				month = 1;
				day = 1;
				return d;
			}
		}
		day = day_all[month];
	}

	return d;
}