// 1752762 计1班 魏鹳达
#include <iostream>
using namespace std;

class Days {
private:
	int year;
	int month;
	int day;
	//除上面的三个private数据成员外，不再允许添加任何类型的数据成员

	int is_leap_year();  //判断是否闰年，是：返回1  /   否：返回0
public:
	int calc_days();     //计算是当年的第几天
	/* 下面可以补充其它需要的类成员函数的定义(体外实现)，数量不限 */
	Days(int y, int m, int d);
};

/* 此处给出类成员函数的体外实现 */
Days::Days(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}

int Days::is_leap_year() {
	if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
		return 1;
	return 0;
}

int Days::calc_days() {
	int day_total[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (is_leap_year())
		day_total[1] = 29;
	int counts, i;
	for (counts = 0, i = 0; i < month - 1; i++)
		counts += day_total[i];
	if (day > day_total[i] || day <= 0)
		return -1;
	counts += day;
	return counts;
}

/* main函数不准动 */
int main()
{
	if (1) {
		Days d1(2012, 3, 18);
		cout << "应该输出78， 实际是：" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 12, 31);
		cout << "应该输出365，实际是：" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2012, 12, 31);
		cout << "应该输出366，实际是：" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 2, 29);
		cout << "应该输出-1， 实际是：" << d1.calc_days() << endl;
	}

	return 0;
}
