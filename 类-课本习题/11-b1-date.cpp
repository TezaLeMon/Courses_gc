// 1752762 ��1�� κ�ٴ�
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
		year = 1900;
		month = 1;
		day = 1;
		return;
	}

	int day_all[13] = { 0,31,28 + is_leap(_year),31,30,31,30,31,31,30,31,30,31 };

	if (_day<1 || _day>day_all[_month]) {
		year = 1900;
		month = 1;
		day = 1;
		return;
	}

	year = _year;
	month = _month;
	day = _day;
}

Date::Date(const int days_total) {
	int days = days_total;
	if (days <= 1 || days > 73049) {
		year = 1900;
		month = 1;
		day = 1;
	}
	else {
		year = 1900;
		month = 1;
		day = 1;
		int t;	//t������¼�Ƿ�������
		while (days > 365 + (t = is_leap(year))) {	//�������
			days -= 365 + t;
			year++;
		}
		int day_all[13] = { 0,31,28 + t,31,30,31,30,31,31,30,31,30,31 };
		t = 1;	//���治��Ҫ�Ƿ������������Ϣ t��Ϊ������ʹ��
		while (days > day_all[t]) {	//�����·�
			month++;
			days -= day_all[t];
			t++;
		}
		day = days;	//ʣ��Ϊ����
	}
}

void Date::set(const int _year, const int _month, const int _day) {
	if (_year < 1900 || _year > 2099 || _month < 1 || _month>12) {
		year = 1900;
		month = 1;
		day = 1;
		return;
	}

	int day_all[13] = { 0,31,28 + is_leap(_year),31,30,31,30,31,31,30,31,30,31 };

	if (_day<1 || _day>day_all[_month]) {
		year = 1900;
		month = 1;
		day = 1;
		return;
	}

	year = _year;
	month = _month;
	day = _day;
}

void Date::set(const int days_total) {
	int days = days_total;
	if (days <= 1 || days > 73049) {
		year = 1900;
		month = 1;
		day = 1;
	}
	else {
		year = 1900;
		month = 1;
		day = 1;
		int t;	//t������¼�Ƿ�������
		while (days > 365 + (t = is_leap(year))) {	//�������
			days -= 365 + t;
			year++;
		}
		int day_all[13] = { 0,31,28 + t,31,30,31,30,31,31,30,31,30,31 };
		t = 1;	//���治��Ҫ�Ƿ������������Ϣ t��Ϊ������ʹ��
		while (days > day_all[t]) {	//�����·�
			month++;
			days -= day_all[t];
			t++;
		}
		day = days;	//ʣ��Ϊ����
	}
}

Date::operator int() {
	int y = year, m = month;
	int result = day;	//������ת��������
	int day_all[13] = { 0,31,28 + is_leap(year),31,30,31,30,31,31,30,31,30,31 };

	while (m > 1) {
		m--;
		result += day_all[m];	//������ת��������
	}

	while (y > 1900) {	//������ת��������
		y--;
		result += 365 + is_leap(y);
	}
	return result;
}

istream& operator>>(istream& is, Date& da) {
	int y, m, d;
	is >> y >> m >> d;	//�����ǷǷ�����
	da.set(y, m, d);
	return is;
}

ostream& operator<<(ostream& os, const Date& da) {
	os << da.year << '-' << da.month << '-' << da.day;
	return os;
}

Date operator+(Date& da1, const int da2) {
	return int(da1) + da2;
}

Date operator+(const int da1, Date& da2) {
	return da1 + int(da2);
}

int operator-(Date& da1, Date& da2) {
	return int(da1) - int(da2);
}

Date operator-(Date& da1, const int da2) {
	return int(da1) - da2;
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
			if (year > 2099) {	//�����������ֻص�1900
				year = 1900;
				month = 1;
				day = 1;
				return *this;
			}
		}
	}
	return *this;
}

Date Date::operator++(int) {
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

Date& Date::operator--() {
	int day_all[13] = { 0,31,28 + is_leap(year),31,30,31,30,31,31,30,31,30,31 };

	day--;
	if (day < 1) {
		month--;
		if (month < 1) {
			month = 12;
			year--;
			if (year < 1900) {	//С��1900-1-1 �ֻص�2099-12-31
				year = 2099;
				month = 12;
				day = 31;
				return *this;
			}
		}
		day = day_all[month];
	}

	return *this;
}

Date Date::operator--(int) {
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