// 1752762 计1班 魏鹳达
#include <iostream>
#include "10-b2.h"
using namespace std;

/* 给出 Date 类的所有成员函数的体外实现 */
Date::Date()
{
	year = 2000;
	month = 1;
	day = 1;
}

Date::Date(int y, int m, int d)
{
	year = y;
	if (year < 1900 || year>2099)
		year = 2000;

	month = m % 12;
	if (!month)
		month = 12;

	int day_all[13] = { 0,31,28 + is_leap(year),31,30,31,30,31,31,30,31,30,31 };

	day = d % day_all[month];
	if (!day)
		day = day_all[month];

	//while (day > day_all[month]) {
	//	month++;
	//	if (month > 12) {
	//		month = 1;
	//		day = day - day_all[12];
	//		year++;
	//	}
	//	else {
	//		day -= day_all[month - 1];
	//	}
	//}

}

void Date::set(int y, int m, int d)
{
	if (y != 0)
		year = y;
	if (m != 0)
		month = m;
	if (d != 0)
		day = d;

	if (year < 1900 || year>2099)
		year = 2000;

	month = month % 12;
	if (!month)
		month = 12;

	int day_all[13] = { 0,31,28 + is_leap(year),31,30,31,30,31,31,30,31,30,31 };

	day = day % day_all[month];
	if (!day)
		day = day_all[month];
}

void Date::get(int& y, int& m, int& d)
{
	y = year;
	m = month;
	d = day;
}

void Date::show()
{
	cout << year << "年" << month << "月" << day << "日" << endl;
}

Date::Date(int days_total)
{
	if (days_total <= 1) {
		year = 1900;
		month = 1;
		day = 1;
	}
	else if (days_total >= 73049) {
		year = 2099;
		month = 12;
		day = 31;
	}
	else {
		year = 1900;
		month = 1;
		day = 1;
		int year_single = 365;
		while (days_total > year_single) {	//计算年份
			year++;
			days_total -= year_single;
			if (is_leap(year))
				year_single = 366;
			else
				year_single = 365;
		}
		int day_all[13] = { 0,31,28 + is_leap(year),31,30,31,30,31,31,30,31,30,31 };
		int i = 1;
		while (days_total > day_all[i]) {	//计算月份
			month++;
			days_total -= day_all[i];
			i++;
		}
		day = days_total;	//剩下为天数
	}
}

Date::operator int()
{
	int y = year, m = month;
	int year_single;
	int result = day;	//加入日转换的天数
	int day_all[13] = { 0,31,28 + is_leap(year),31,30,31,30,31,31,30,31,30,31 };
	
	while (m > 1) {
		m--;
		result += day_all[m];	//加入月转换的天数
	}

	while (y > 1900) {	//加入年转换的天数
		y--;
		year_single = 365 + is_leap(y);
		result += year_single;
	}
	return result;
}

//Date& operator+(Date& a, int& b)
//{
//	int t = int(a) + b;
//	static Date c;
//	c = t;
//	return c;
//}
//
//Date& operator+(int& a, Date& b)
//{
//	int t = a + int(b);
//	static Date c;
//	c = t;
//	return c;
//}
//
//Date& operator-(Date& a, int& b)
//{
//	int t = int(a) + b;
//	static Date c;
//	c = t;
//	return c;
//}
//
//Date& operator-(int& a, Date& b)
//{
//	int t = a + int(b);
//	static Date c;
//	c = t;
//	return c;
//}


Date& Date::operator+(int b)
{
	static Date c;
	c = Date(int(*this) + b);
	return c;
}
Date& Date::operator-(int b)
{
	static Date c;
	c = Date(int(*this) - b);
	return c;
}
int Date::operator-(Date& b)
{
	return int(*this) - b;
}

Date Date::operator++(int)
{
	Date d(*this);
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
				return d;
			}
		}
	}

	return d;
}

Date& Date::operator++()
{
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

Date Date::operator--(int)
{
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

Date& Date::operator--()
{
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

istream& operator>>(istream& is, Date& a)
{
	is >> a.year >> a.month >> a.day;

	if ((a.year < 1900 || a.year>2099) && (a.month < 1 || a.month>12)) {
		a.year = 2000;
		a.month = 1;
		a.day = 1;
	}

	if (a.year < 1900 || a.year>2099) {
		a.year = 2000;
	}

	a.month = a.month % 12;
	if (!a.month)
		a.month = 12;

	int day_all[13] = { 0,31,28 + is_leap(a.year),31,30,31,30,31,31,30,31,30,31 };

	a.day = a.day % day_all[a.month];
	if (!a.day)
		a.day = day_all[a.month];
	return is;
}

ostream& operator<<(ostream& os, Date& a)
{
	os << a.year << "年" << a.month << "月" << a.day << "日";
	return os;
}

bool operator<(Date& a, Date& b)
{
	if (a.year > b.year)
		return 0;
	if (a.year < b.year)
		return 1;
	if (a.month > b.month)
		return 0;
	if (a.month < b.month)
		return 1;
	return a.day < b.day;
}

bool operator<=(Date& a, Date& b)
{
	if (a.year > b.year)
		return 0;
	if (a.year < b.year)
		return 1;
	if (a.month > b.month)
		return 0;
	if (a.month < b.month)
		return 1;
	return a.day <= b.day;
}

bool operator>(Date& a, Date& b)
{
	if (a.year > b.year)
		return 1;
	if (a.year < b.year)
		return 0;
	if (a.month > b.month)
		return 1;
	if (a.month < b.month)
		return 0;
	return a.day > b.day;
}

bool operator>=(Date& a, Date& b)
{
	if (a.year > b.year)
		return 1;
	if (a.year < b.year)
		return 0;
	if (a.month > b.month)
		return 1;
	if (a.month < b.month)
		return 0;
	return a.day >= b.day;
}

bool operator==(Date& a, Date& b)
{
	return a.year == b.year&&a.month == b.month&&a.day == b.day;
}

bool operator!=(Date& a, Date& b)
{
	return !(a.year == b.year&&a.month == b.month&&a.day == b.day);
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */

int is_leap(int year)
{
	return (year % 4 == 0 && year % 100) || year % 400 == 0;
}
