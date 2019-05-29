// 1752762 计1班 魏鹳达
#include <iostream>
using namespace std;

/* 补全Date类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class Date {
	private:
		int year;
		int month;
		int day;
		/* 不允许添加数据成员 */
	public:
	/* 根据需要定义所需的成员函数、友元函数等(不允许添加数据成员) */
		Date();
		Date(int y, int m, int d);
		void set(int y = 2000, int m = 1, int d = 1);
		void get(int& y, int& m, int& d);
		void show();
		Date(int days_total);
		operator int();
		//friend Date& operator+(Date& a, int& b);
		//friend Date& operator+(int& a, Date& b);
		//friend Date& operator-(Date& a, int& b);
		//friend Date& operator-(int& a, Date& b);
		Date& operator+(int b);
		Date& operator-(int b);
		int operator-(Date& b);

		Date operator++(int);
		Date& operator++();
		Date operator--(int);
		Date& operator--();
		friend istream& operator>>(istream& is, Date& a);
		friend ostream& operator<<(ostream& os, Date& a);
		friend bool operator<(Date& a, Date& b);
		friend bool operator<=(Date& a, Date& b);
		friend bool operator>(Date& a, Date& b);
		friend bool operator>=(Date& a, Date& b);
		friend bool operator==(Date& a, Date& b);
		friend bool operator!=(Date& a, Date& b);
};

/* 如果有其它全局函数需要声明，写于此处 */
int is_leap(int year);

/* 如果有需要的宏定义、只读全局变量等，写于此处 */
