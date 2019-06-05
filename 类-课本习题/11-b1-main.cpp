// 1752762 计1班 魏鹳达
#include <iostream>
#include "11-b1-datetime.h"
#include <cstdlib>
#include <cstdio>
using namespace std;

#if defined(__linux) || defined(__linux__)
#include <sys/time.h>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (getchar() != '\n')
		;
	cout << endl << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
long get_cur_msec(void)
{
	struct timespec ts;
	clock_gettime(CLOCK_PROCESS_CPUTIME_ID, &ts);

	return (ts.tv_sec * 1000 + ts.tv_nsec / 1000000);
}

#else
#include <Windows.h>
#include <conio.h>
/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void wait_for_enter()
{
	cout << endl << "按回车键继续";
	while (_getch() != '\r')
		;
	cout << endl << endl;
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
long get_cur_msec(void)
{
	return GetTickCount(); //取当前系统时间，单位毫秒
}

#endif

void test_Date()
{
	if (1) {
		Date d1;
		Date d2(2019, 5, 23);

		cout << "测试初始化及cout，完全正确的赋值" << endl;

		cout << "d1应该是1900-1-1， 实际为：";
		cout << d1 << endl;
		cout << "d2应该是2019-5-23，实际为：";
		cout << d2 << endl;

		wait_for_enter();
	}

	if (1) {
		Date d1(1870, 3, 15);  //2000.3.15
		Date d2(2112, 3, 4);   //2000.3.4
		Date d3(2005, 13, 15); //2005.1.15
		Date d4(2019, 5, 32);  //2019.5.1

		cout << "测试初始化，年、月、日非法" << endl;

		cout << "d1应该是1900-1-1，实际为：";
		cout << d1 << endl;
		cout << "d2应该是1900-1-1， 实际为：";
		cout << d2 << endl;
		cout << "d3应该是1900-1-1，实际为：";
		cout << d3 << endl;
		cout << "d4应该是1900-1-1， 实际为：";
		cout << d4 << endl;

		wait_for_enter();
	}

	if (1) {
		Date d1(2019, 2, 29);   //2019.2.1
		Date d2(2016, 2, 29);   //2016.2.29

		cout << "测试初始化，闰年" << endl;

		cout << "d1应该是1900-1-1， 实际为：";
		cout << d1 << endl;
		cout << "d2应该是2016-2-29，实际为：";
		cout << d2 << endl;

		wait_for_enter();
	}

	if (1) {
		Date d1(2016, 4, 28);
		Date d2(2007, 5, 20);
		Date d3(2016, 4, 28);
		Date d4(2019, 5, 23);

		cout << "测试set，年、月、日非法及合法" << endl;

		d1.set(2112, 1, 1);
		d2.set(2019, 2, 29);
		d3.set(2016, 5, 32);
		d4.set(2019, 12, 12);

		cout << "d1应该是1900-1-1，实际为：";
		cout << d1 << endl;
		cout << "d2应该是1900-1-1， 实际为：";
		cout << d2 << endl;
		cout << "d3应该是1900-1-1， 实际为：";
		cout << d3 << endl;
		cout << "d4应该是2019-12-12，实际为：";
		cout << d4 << endl;

		wait_for_enter();
	}

	if (1) {
		Date d1;

		cout << "测试cin" << endl;

		cout << "请输入2019 5 23" << endl;
		cin >> d1;
		cout << "d1应该是2019-5-23，实际为：" << d1 << endl;

		cout << "请输入2016 2 29" << endl;
		cin >> d1;
		cout << "d1应该是2016-2-29，实际为：" << d1 << endl;

		cout << "请输入2019 2 29" << endl;
		cin >> d1;
		cout << "d1应该是1900-1-1，实际为：" << d1 << endl;

		cout << "请输入1899 4 10" << endl;
		cin >> d1;
		cout << "d1应该是1900-1-1，实际为：" << d1 << endl;

		cout << "请输入2019 13 10" << endl;
		cin >> d1;
		cout << "d1应该是1900-1-1，实际为：" << d1 << endl;

		cout << "请输入2112 15 34" << endl;
		cin >> d1;
		cout << "d1应该是1900-1-1，实际为：" << d1 << endl;

		wait_for_enter();
	}

	if (1) {
		Date d1(1);          //1900.1.1
		Date d2(73049);      //2099.12.31
		Date d3(-100);       //1900.1.1
		Date d4(80000);      //2099.12.31

		cout << "转换构造函数测试，包括合法及非法值" << endl;

		cout << "d1应该是1900-1-1，  实际为：";
		cout << d1 << endl;
		cout << "d2应该是2099-12-31，实际为：";
		cout << d2 << endl;
		cout << "d3应该是1900-1-1，  实际为：";
		cout << d3 << endl;
		cout << "d4应该是1900-1-1，  实际为：";
		cout << d4 << endl;

		d1 = 30000;
		cout << "d1应该是1982-2-19， 实际为：";
		cout << d1 << endl;

		d2 = 43607;
		cout << "d2应该是2019-5-23， 实际为：";
		cout << d2 << endl;

		wait_for_enter();
	}

	if (1) {
		Date d1(1900, 1, 1);
		Date d2(2099, 12, 31);
		Date d3(1982, 2, 19);
		Date d4(2019, 5, 23);

		cout << "类型转换函数测试，包括合法及非法值" << endl;

		cout << "d1应该是1，     实际为：" << int(d1) << endl;
		cout << "d2应该是73049， 实际为：" << int(d2) << endl;
		cout << "d3应该是30000， 实际为：" << int(d3) << endl;
		cout << "d4应该是43607， 实际为：" << int(d4) << endl;

		wait_for_enter();
	}

	if (1) {
		Date d1(2019, 5, 23);
		Date d2;

		cout << "测试+/- n" << endl;

		d2 = d1 + 39;
		cout << "d2应该是2019-7-1，    实际为：" << d2 << endl;

		d2 = 39 + d1;
		cout << "d2应该是2019-7-1，    实际为：" << d2 << endl;

		d2 = d1 - 7;
		cout << "d2应该是2019-5-16，   实际为：" << d2 << endl;

		d1.set(2016, 2, 28);
		d2 = d1 + 3;
		cout << "d2应该是2016-3-2，    实际为：" << d2 << endl;

		d1.set(2019, 2, 28);
		d2 = d1 + 3;
		cout << "d2应该是2019-3-3，    实际为：" << d2 << endl;

		d1.set(2010, 12, 28);
		d2 = d1 + 5;
		cout << "d2应该是2011-1-2，    实际为：" << d2 << endl;

		d1.set(2011, 1, 1);
		d2 = d1 - 5;
		cout << "d2应该是2010-12-27，  实际为：" << d2 << endl;

		d1.set(2009, 12, 31);
		d2 = d1 + 366;
		cout << "d2应该是2011-1-1，    实际为：" << d2 << endl;

		d1.set(2009, 1, 1);
		d2 = d1 - 367;
		cout << "d2应该是2007-2-31，  实际为：" << d2 << endl;

		d1.set(1900, 1, 2);
		d2 = d1 - 10;
		cout << "d2应该是1900-1-1，    实际为：" << d2 << endl;

		d1.set(2099, 12, 30);
		d2 = d1 + 5;
		cout << "d2应该是1900-1-1，  实际为：" << d2 << endl;

		d1.set(2019, 5, 23);
		d2.set(2019, 4, 21);
		cout << "d1-d2应该是32，实际为：" << d1 - d2 << endl;

		d1.set(2016, 4, 28);
		d2.set(2015, 4, 28);
		cout << "d1-d2应该是366，实际为：" << d1 - d2 << endl;

		d1.set(2019, 5, 23);
		d2.set(2018, 5, 23);
		cout << "d1-d2应该是365，实际为：" << d1 - d2 << endl;

		d1.set(2019, 5, 23);
		cout << "d1+9应该是2019-6-1， 实际为：" << d1 + 9 << endl;
		cout << "9+d1应该是2019-6-1， 实际为：" << 9 + d1 << endl;
		cout << "d1-3应该是2019-5-20，实际为：" << d1 - 3 << endl;

		wait_for_enter();
	}

	if (1) {
		Date d1(2019, 5, 1);
		Date d2(2019, 3, 11);

		cout << "测试-date" << endl;
		cout << "日期差值应为51， 实际为：" << d1 - d2 << endl;

		d2.set(2019, 5, 23);
		cout << "日期差值应为-22，实际为：" << d1 - d2 << endl;

		d1.set(2016, 3, 2);
		d2.set(2016, 2, 27);
		cout << "日期差值应为4，  实际为：" << d1 - d2 << endl;

		d1.set(2019, 3, 2);
		d2.set(2019, 2, 27);
		cout << "日期差值应为3，  实际为：" << d1 - d2 << endl;

		d1.set(2019, 1, 2);
		d2.set(2018, 12, 27);
		cout << "日期差值应为6，  实际为：" << d1 - d2 << endl;

		d1.set(2019, 1, 1);
		d2.set(2017, 12, 31);
		cout << "日期差值应为366，实际为：" << d1 - d2 << endl;

		d1.set(2017, 1, 1);
		d2.set(2015, 12, 31);
		cout << "日期差值应为367，实际为：" << d1 - d2 << endl;

		wait_for_enter();
	}

	if (1) {
		Date d1, d2;

		cout << "测试++/--" << endl;

		d1.set(2019, 5, 23);
		d2 = d1++;
		cout << "d1应该是2019-5-24，  实际为：" << d1 << endl;
		cout << "d2应该是2019-5-23，  实际为：" << d2 << endl;

		d1.set(2019, 5, 23);
		d2 = ++d1;
		cout << "d1应该是2019-5-24，  实际为：" << d1 << endl;
		cout << "d2应该是2019-5-24，  实际为：" << d2 << endl;

		d1.set(2019, 5, 1);
		d2 = d1--;
		cout << "d1应该是2019-4-30， 实际为：" << d1 << endl;
		cout << "d2应该是2019-5-1，  实际为：" << d2 << endl;

		d1.set(2019, 5, 1);
		d2 = --d1;
		cout << "d1应该是2019-4-30， 实际为：" << d1 << endl;
		cout << "d2应该是2019-4-30， 实际为：" << d2 << endl;

		d1.set(2018, 12, 31);
		d2 = d1++;
		cout << "d1应该是2019-1-1，  实际为：" << d1 << endl;
		cout << "d2应该是2018-12-31，实际为：" << d2 << endl;

		d1.set(2019, 1, 1);
		d2 = d1--;
		cout << "d1应该是2018-12-31，实际为：" << d1 << endl;
		cout << "d2应该是2019-1-1，  实际为：" << d2 << endl;

		d1.set(2016, 2, 28);
		d2 = d1++;
		cout << "d1应该是2016-2-29， 实际为：" << d1 << endl;
		cout << "d2应该是2016-2-28， 实际为：" << d2 << endl;

		d1.set(2019, 2, 28);
		d2 = d1++;
		cout << "d1应该是2019-3-1，  实际为：" << d1 << endl;
		cout << "d2应该是2019-2-28， 实际为：" << d2 << endl;

		d1.set(2016, 3, 1);
		d2 = d1--;
		cout << "d1应该是2016-2-29， 实际为：" << d1 << endl;
		cout << "d2应该是2016-3-1，  实际为：" << d2 << endl;

		d1.set(2019, 3, 1);
		d2 = d1--;
		cout << "d1应该是2019-2-28， 实际为：" << d1 << endl;
		cout << "d2应该是2019-3-1，  实际为：" << d2 << endl;

		d1.set(2099, 12, 31);
		d2 = d1++;
		cout << "d1应该是1900-1-1，实际为：" << d1 << endl;
		cout << "d2应该是2099-12-31，实际为：" << d2 << endl;

		d1.set(1900, 1, 1);
		d2 = d1--;
		cout << "d1应该是1900-1-1，  实际为：" << d1 << endl;
		cout << "d2应该是1900-1-1，  实际为：" << d2 << endl;

		wait_for_enter();
	}


	if (1) {
		/* 测试比较运算符 */
		Date d1(2019, 5, 23);
		Date d2(2019, 5, 23);
		Date d3(2019, 4, 27);

		cout << "测试比较运算符" << endl;

		cout << "比较结果应为0，实际为：" << (d1 > d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 >= d2) << endl;
		cout << "比较结果应为0，实际为：" << (d1 < d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 <= d2) << endl;
		cout << "比较结果应为1，实际为：" << (d1 == d2) << endl;
		cout << "比较结果应为0，实际为：" << (d1 != d2) << endl;

		cout << "比较结果应为1，实际为：" << (d1 > d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 >= d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 < d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 <= d3) << endl;
		cout << "比较结果应为0，实际为：" << (d1 == d3) << endl;
		cout << "比较结果应为1，实际为：" << (d1 != d3) << endl;

		wait_for_enter();
	}
}


void test_Time()
{
	if (1) {
		Time t1;
		Time t2(15, 5, 43);

		cout << "测试初始化及cout，完全正确的赋值" << endl;

		cout << "t1应该是0:0:0，  实际为：";
		cout << t1 << endl;
		cout << "t2应该是15:5:43，实际为：";
		cout << t2 << endl;

		wait_for_enter();
	}

	if (1) {
		Time t1(-1, 3, 15);
		Time t2(27, 3, 66);
		Time t3(20, 13, 15);
		Time t4(7, 5, 32);

		cout << "测试初始化，包含非法及合法" << endl;

		cout << "t1应该是0:0:0，   实际为：";
		cout << t1 << endl;
		cout << "t2应该是0:0:0，   实际为：";
		cout << t2 << endl;
		cout << "t3应该是20:13:15，实际为：";
		cout << t3 << endl;
		cout << "t4应该是7:5:32，  实际为：";
		cout << t4 << endl;

		wait_for_enter();
	}

	if (1) {
		Time t1;
		Time t2;
		Time t3;
		Time t4;

		cout << "测试set，非法及合法" << endl;

		t1.set(-1, 5, 8);
		t2.set(24, 0, 0);
		t3.set(16, 5, 99);
		t4.set(23, 59, 59);

		cout << "t1应该是0:0:0，   实际为：";
		cout << t1 << endl;
		cout << "t2应该是0:0:0，   实际为：";
		cout << t2 << endl;
		cout << "t3应该是0:0:0，   实际为：";
		cout << t3 << endl;
		cout << "t4应该是23:59:69，实际为：";
		cout << t4 << endl;

		wait_for_enter();
	}

	if (1) {
		Time t1;

		cout << "测试cin" << endl;

		cout << "请输入12 34 56" << endl;
		cin >> t1;
		cout << "t1应该是12:34:56，实际为：" << t1 << endl;

		cout << "请输入-1 3 7" << endl;
		cin >> t1;
		cout << "t1应该是0:0:0，   实际为：" << t1 << endl;

		cout << "请输入24 0 0" << endl;
		cin >> t1;
		cout << "t1应该是0:0:0，   实际为：" << t1 << endl;

		cout << "请输入30 66 40" << endl;
		cin >> t1;
		cout << "t1应该是0:0:0，   实际为：" << t1 << endl;

		wait_for_enter();
	}

	if (1) {
		Time t1(1);
		Time t2(86400);
		Time t3(-100);
		Time t4(86399);

		cout << "转换构造函数测试，包括合法及非法值" << endl;

		cout << "t1应该是0:0:1，     实际为：";
		cout << t1 << endl;
		cout << "t2应该是0:0:0，     实际为：";
		cout << t2 << endl;
		cout << "t3应该是0:0:0，     实际为：";
		cout << t3 << endl;
		cout << "t4应该是23:59:59，  实际为：";
		cout << t4 << endl;

		t1 = 30000;
		cout << "t1应该是8:20:0，    实际为：";
		cout << t1 << endl;

		t2 = 43607;
		cout << "t2应该是12:6:47，   实际为：";
		cout << t2 << endl;

		wait_for_enter();
	}

	if (1) {
		Time t1(0, 0, 0);
		Time t2(5, 45, 8);
		Time t3(23, 59, 59);

		cout << "类型转换函数测试，包括合法及非法值" << endl;

		cout << "t1应该是1，     实际为：" << int(t1) << endl;
		cout << "t2应该是20708， 实际为：" << int(t2) << endl;
		cout << "t3应该是86399， 实际为：" << int(t3) << endl;

		wait_for_enter();
	}

	if (1) {
		Time t1(10, 23, 44);
		Time t2;

		cout << "测试+/- n" << endl;

		t2 = t1 + 39;
		cout << "t2应该是10:24:23，    实际为：" << t2 << endl;

		t2 = 39 + t1;
		cout << "t2应该是10:24:23，    实际为：" << t2 << endl;

		t2 = t1 - 7;
		cout << "t2应该是10:23:37，    实际为：" << t2 << endl;

		t2 = t1 + 3;
		cout << "t2应该是10:23:47，    实际为：" << t2 << endl;

		t1.set(10, 59, 50);
		t2 = t1 + 15;
		cout << "t2应该是11:0:5，      实际为：" << t2 << endl;

		t1.set(10, 0, 10);
		t2 = t1 - 15;
		cout << "t2应该是9:59:55，     实际为：" << t2 << endl;

		t1.set(10, 55, 30);
		t2 = t1 + 600;
		cout << "t2应该是11:5:30，     实际为：" << t2 << endl;

		t1.set(10, 5, 30);
		t2 = t1 - 666;
		cout << "t2应该是9:54:24，     实际为：" << t2 << endl;

		t1.set(23, 59, 55);
		t2 = t1 + 15;
		cout << "t2应该是0:0:0，       实际为：" << t2 << endl;

		t1.set(10, 5, 23);
		cout << "t1+9应该是10:5:32，   实际为：" << t1 + 9 << endl;
		cout << "9+t1应该是10:5:32，   实际为：" << 9 + t1 << endl;
		cout << "t1-3应该是10:5:20，   实际为：" << t1 - 3 << endl;

		wait_for_enter();
	}

	if (1) {
		Time t1(20, 5, 1);
		Time t2(20, 3, 11);

		cout << "测试-Time" << endl;
		cout << "差值应为110，   实际为：" << t1 - t2 << endl;

		t2.set(20, 5, 23);
		cout << "差值应为-22，   实际为：" << t1 - t2 << endl;

		t1.set(19, 1, 2);
		t2.set(20, 12, 27);
		cout << "差值应为-4285， 实际为：" << t1 - t2 << endl;

		wait_for_enter();
	}

	if (1) {
		Time t1, t2;

		cout << "测试++/--" << endl;

		t1.set(19, 5, 23);
		t2 = t1++;
		cout << "t1应该是19:5:24，  实际为：" << t1 << endl;
		cout << "t2应该是19:5:23，  实际为：" << t2 << endl;

		t1.set(19, 5, 23);
		t2 = ++t1;
		cout << "t1应该是19:5:24，  实际为：" << t1 << endl;
		cout << "t2应该是19:5:24，  实际为：" << t2 << endl;

		t1.set(19, 5, 0);
		t2 = t1--;
		cout << "t1应该是19:4:59，   实际为：" << t1 << endl;
		cout << "t2应该是19:5:0，    实际为：" << t2 << endl;

		t1.set(19, 5, 0);
		t2 = --t1;
		cout << "t1应该是2019:4:59， 实际为：" << t1 << endl;
		cout << "t2应该是2019:4:59， 实际为：" << t2 << endl;

		t1.set(18, 59, 59);
		t2 = t1++;
		cout << "t1应该是19:0:0，    实际为：" << t1 << endl;
		cout << "t2应该是18:59:59，  实际为：" << t2 << endl;

		t1.set(19, 0, 0);
		t2 = t1--;
		cout << "t1应该是18:59:59，  实际为：" << t1 << endl;
		cout << "t2应该是19:0:0，    实际为：" << t2 << endl;

		t1.set(23, 59, 59);
		t2 = t1++;
		cout << "t1应该是0:0:0，实际为：" << t1 << endl;
		cout << "t2应该是23:59:59，实际为：" << t2 << endl;

		t1.set(0, 0, 0);
		t2 = t1--;
		cout << "t1应该是23:59:59，  实际为：" << t1 << endl;
		cout << "t2应该是0:0:0，  实际为：" << t2 << endl;

		wait_for_enter();
	}

	if (1) {
		/* 测试比较运算符 */
		Time t1(19, 5, 23);
		Time t2(19, 5, 23);
		Time t3(19, 4, 27);

		cout << "测试比较运算符" << endl;

		cout << "比较结果应为0，实际为：" << (t1 > t2) << endl;
		cout << "比较结果应为1，实际为：" << (t1 >= t2) << endl;
		cout << "比较结果应为0，实际为：" << (t1 < t2) << endl;
		cout << "比较结果应为1，实际为：" << (t1 <= t2) << endl;
		cout << "比较结果应为1，实际为：" << (t1 == t2) << endl;
		cout << "比较结果应为0，实际为：" << (t1 != t2) << endl;

		cout << "比较结果应为1，实际为：" << (t1 > t3) << endl;
		cout << "比较结果应为1，实际为：" << (t1 >= t3) << endl;
		cout << "比较结果应为0，实际为：" << (t1 < t3) << endl;
		cout << "比较结果应为0，实际为：" << (t1 <= t3) << endl;
		cout << "比较结果应为0，实际为：" << (t1 == t3) << endl;
		cout << "比较结果应为1，实际为：" << (t1 != t3) << endl;

		wait_for_enter();
	}
}


void test_DateTime()
{
	if (1) {
		DateTime dt1;
		DateTime dt2(2019, 5, 23, 12, 34, 56);

		cout << "测试初始化及cout，完全正确的赋值" << endl;

		cout << "dt1应该是1900-1-1 0:0:0，    实际为：";
		cout << dt1 << endl;
		cout << "dt2应该是2019-5-23 12:34:56，实际为：";
		cout << dt2 << endl;

		wait_for_enter();
	}

	if (1) {
		DateTime dt1(1870, 3, 15, 12, 34, 56);
		DateTime dt2(2000, 3, 4, 26, 34, 70);
		DateTime dt3(2005, 13, 15, 12, 99, 56);
		DateTime dt4(2019, 5, 32, 40, 34, 56);

		cout << "测试初始化，非法" << endl;

		cout << "dt1应该是1900-1-1 0:0:0， 实际为：";
		cout << dt1 << endl;
		cout << "dt2应该是1900-1-1 0:0:0， 实际为：";
		cout << dt2 << endl;
		cout << "dt3应该是1900-1-1 0:0:0， 实际为：";
		cout << dt3 << endl;
		cout << "dt4应该是1900-1-1 0:0:0， 实际为：";
		cout << dt4 << endl;

		wait_for_enter();
	}

	if (1) {
		DateTime dt1(2019, 2, 29, 12, 34, 56);   //2019.2.1
		DateTime dt2(2016, 2, 29, 12, 34, 56);   //2016.2.29

		cout << "测试初始化，闰年" << endl;

		cout << "dt1应该是1900-1-1 0:0:0，    实际为：";
		cout << dt1 << endl;
		cout << "dt2应该是2016-2-29 12:34:56，实际为：";
		cout << dt2 << endl;

		wait_for_enter();
	}

	if (1) {
		DateTime dt1(2016, 4, 28, 12, 34, 56);
		DateTime dt2(2007, 5, 20, 12, 34, 56);
		DateTime dt3(2016, 4, 28, 12, 34, 56);
		DateTime dt4(2019, 5, 23, 12, 34, 56);

		cout << "测试set，年、月、日非法及合法" << endl;

		dt1.set(2112, 1, 1, 12, 34, 56);
		dt2.set(2019, 2, 29, 12, 34, 56);
		dt3.set(2016, 5, 32, 12, 34, 56);
		dt4.set(2019, 12, 12, 12, 34, 56);

		cout << "dt1应该是1900-1-1 0:0:0，     实际为：";
		cout << dt1 << endl;
		cout << "dt2应该是1900-1-1 0:0:0，     实际为：";
		cout << dt2 << endl;
		cout << "dt3应该是1900-1-1 0:0:0，     实际为：";
		cout << dt3 << endl;
		cout << "dt4应该是2019-12-12 12:34:56，实际为：";
		cout << dt4 << endl;

		wait_for_enter();
	}

	if (1) {
		DateTime dt1;

		cout << "测试cin" << endl;

		cout << "请输入2019 5 23 12 34 56" << endl;
		cin >> dt1;
		cout << "dt1应该是2019-5-23 12:34:56，实际为：" << dt1 << endl;

		cout << "请输入2016 2 29 12 34 56" << endl;
		cin >> dt1;
		cout << "dt1应该是2016-2-29 12:34:56，实际为：" << dt1 << endl;

		cout << "请输入2019 2 28 30 22 55" << endl;
		cin >> dt1;
		cout << "dt1应该是1900-1-1 0:0:0，    实际为：" << dt1 << endl;

		cout << "请输入1899 4 10 23 45 33" << endl;
		cin >> dt1;
		cout << "dt1应该是1900-1-1 0:0:0，    实际为：" << dt1 << endl;

		cout << "请输入2019 10 10 12 45 99" << endl;
		cin >> dt1;
		cout << "dt1应该是1900-1-1 0:0:0，    实际为：" << dt1 << endl;

		cout << "请输入2112 15 34 12 34 55" << endl;
		cin >> dt1;
		cout << "dt1应该是1900-1-1 0:0:0，    实际为：" << dt1 << endl;

		wait_for_enter();
	}

	if (1) {
		DateTime dt1(1);
		DateTime dt2(6311433599);
		DateTime dt3(-100);
		DateTime dt4(6311433600);

		cout << "转换构造函数测试，包括合法及非法值" << endl;

		cout << "dt1应该是1900-1-1 0:0:1，     实际为：";
		cout << dt1 << endl;
		cout << "dt2应该是2099-12-31 23:59:59，实际为：";
		cout << dt2 << endl;
		cout << "dt3应该是1900-1-1 0:0:0，     实际为：";
		cout << dt3 << endl;
		cout << "dt4应该是1900-1-1 0:0:0，     实际为：";
		cout << dt4 << endl;

		dt1 = 30000;
		cout << "dt1应该是1900-1-1 8:20:0，    实际为：";
		cout << dt1 << endl;

		dt2 = 4346443607;
		cout << "dt2应该是2037-9-25 1:26:47，  实际为：";
		cout << dt2 << endl;

		wait_for_enter();
	}

	if (1) {
		DateTime dt1(1900, 1, 1, 12, 34, 56);
		DateTime dt2(2099, 12, 31, 12, 34, 56);
		DateTime dt3(1982, 2, 19, 12, 34, 56);
		DateTime dt4(2019, 5, 23, 24, 0, 0);

		cout << "类型转换函数测试，包括合法及非法值" << endl;

		cout << "dt1应该是45296，      实际为：" << (long long)(dt1) << endl;
		cout << "dt2应该是6311392496， 实际为：" << (long long)(dt2) << endl;
		cout << "dt3应该是2591958896， 实际为：" << (long long)(dt3) << endl;
		cout << "dt4应该是0，          实际为：" << (long long)(dt4) << endl;

		wait_for_enter();
	}

	if (1) {
		DateTime dt1(2019, 5, 23, 12, 34, 56);
		DateTime dt2;

		cout << "测试+/- n" << endl;

		dt2 = dt1 + 39LL;
		cout << "dt2应该是2019-5-23 12:35:35，    实际为：" << dt2 << endl;

		dt2 = 39LL + dt1;
		cout << "dt2应该是2019-5-23 12:35:35，    实际为：" << dt2 << endl;

		dt2 = dt1 - 7LL;
		cout << "dt2应该是2019-5-23 12:34:49，    实际为：" << dt2 << endl;

		dt1.set(2016, 2, 28, 23, 59, 55);
		dt2 = dt1 + 13LL;
		cout << "dt2应该是2016-2-29 0:0:8，       实际为：" << dt2 << endl;

		dt1.set(2010, 12, 31, 23, 59, 30);
		dt2 = dt1 + 75LL;
		cout << "dt2应该是2011-1-1 0:0:45，       实际为：" << dt2 << endl;

		dt1.set(2011, 1, 1, 0, 5, 2);
		dt2 = dt1 - 445LL;
		cout << "dt2应该是2010-12-31 23:57:37，   实际为：" << dt2 << endl;

		dt1.set(2009, 12, 31, 23, 58, 22);
		dt2 = dt1 + 366LL;
		cout << "dt2应该是2010-1-1 0:4:28，       实际为：" << dt2 << endl;

		dt1.set(2009, 1, 1, 0, 2, 3);
		dt2 = dt1 - 367LL;
		cout << "dt2应该是2008-12-31 23:55:56，   实际为：" << dt2 << endl;

		dt1.set(1900, 1, 2, 0, 2, 4);
		dt2 = dt1 - 210LL;
		cout << "dt2应该是1900-1-1 23:58:34，     实际为：" << dt2 << endl;

		dt1.set(2099, 12, 30, 23, 56, 7);
		dt2 = dt1 + 555LL;
		cout << "dt2应该是2099-12-31 0:5:22，     实际为：" << dt2 << endl;

		dt1.set(2019, 5, 23, 21, 23, 6);
		dt2.set(2019, 4, 21, 11, 43, 44);
		cout << "dt1-dt2应该是2799562， 实际为：" << dt1 - dt2 << endl;

		cout << "dt2-dt1应该是-2799562，实际为：" << dt2 - dt1 << endl;

		dt1.set(2019, 5, 23, 23, 58, 44);
		cout << "dt1+9应该是2019-5-24 0:0:53，  实际为：" << dt1 + 129LL << endl;
		cout << "9+dt1应该是2019-5-24 0:0:53，  实际为：" << 129LL + dt1 << endl;
		cout << "dt1-3应该是2019-5-23 23:56:51，实际为：" << dt1 - 113LL << endl;

		wait_for_enter();
	}

	if (1) {
		DateTime dt1(2019, 5, 1, 12, 6, 23);
		DateTime dt2(2019, 3, 11, 20, 12, 5);

		cout << "测试-DateTime" << endl;
		cout << "差值应为4377258， 实际为：" << dt1 - dt2 << endl;

		dt2.set(2019, 5, 23, 20, 12, 5);
		cout << "差值应为-1929942，实际为：" << dt1 - dt2 << endl;

		dt1.set(2019, 1, 1, 12, 6, 23);
		dt2.set(2017, 12, 31, 10, 12, 5);
		cout << "差值应为31629258，实际为：" << dt1 - dt2 << endl;

		dt1.set(2017, 1, 1, 12, 6, 23);
		dt2.set(2015, 12, 31, 10, 12, 5);
		cout << "差值应为31715658，实际为：" << dt1 - dt2 << endl;

		wait_for_enter();
	}

	if (1) {
		DateTime dt1, dt2;

		cout << "测试++/--" << endl;

		dt1.set(2019, 5, 23, 23, 59, 59);
		dt2 = dt1++;
		cout << "dt1应该是2019-5-24 0:0:0，     实际为：" << dt1 << endl;
		cout << "dt2应该是2019-5-23 23:59:59，  实际为：" << dt2 << endl;

		dt1.set(2019, 5, 23, 23, 59, 59);
		dt2 = ++dt1;
		cout << "dt1应该是2019-5-24 0:0:0，     实际为：" << dt1 << endl;
		cout << "dt2应该是2019-5-24 0:0:0，     实际为：" << dt2 << endl;

		dt1.set(2019, 5, 1, 0, 0, 0);
		dt2 = dt1--;
		cout << "dt1应该是2019-4-30 23:59:59，  实际为：" << dt1 << endl;
		cout << "dt2应该是2019-5-1 0:0:0，      实际为：" << dt2 << endl;

		dt1.set(2019, 5, 1, 0, 0, 0);
		dt2 = --dt1;
		cout << "dt1应该是2019-4-30 23:59:59，  实际为：" << dt1 << endl;
		cout << "dt2应该是2019-4-30 23:59:59，  实际为：" << dt2 << endl;

		dt1.set(2018, 12, 31, 23, 59, 59);
		dt2 = dt1++;
		cout << "dt1应该是2019-1-1 0:0:0，      实际为：" << dt1 << endl;
		cout << "dt2应该是2018-12-31 23:59:59， 实际为：" << dt2 << endl;

		dt1.set(2019, 1, 1, 0, 0, 0);
		dt2 = dt1--;
		cout << "dt1应该是2018-12-31 23:59:59， 实际为：" << dt1 << endl;
		cout << "dt2应该是2019-1-1 0:0:0，      实际为：" << dt2 << endl;

		dt1.set(2016, 2, 28, 23, 59, 59);
		dt2 = dt1++;
		cout << "dt1应该是2016-2-29 0:0:0，     实际为：" << dt1 << endl;
		cout << "dt2应该是2016-2-28 23:59:59，  实际为：" << dt2 << endl;

		dt1.set(2019, 2, 28, 23, 59, 59);
		dt2 = dt1++;
		cout << "dt1应该是2019-3-1 0:0:0，      实际为：" << dt1 << endl;
		cout << "dt2应该是2019-2-28 23:59:59，  实际为：" << dt2 << endl;

		dt1.set(2016, 3, 1, 0, 0, 0);
		dt2 = dt1--;
		cout << "dt1应该是2016-2-29 23:59:59，  实际为：" << dt1 << endl;
		cout << "dt2应该是2016-3-1 0:0:0，      实际为：" << dt2 << endl;

		dt1.set(2019, 3, 1, 0, 0, 0);
		dt2 = dt1--;
		cout << "dt1应该是2019-2-28 23:59:59，  实际为：" << dt1 << endl;
		cout << "dt2应该是2019-3-1 0:0:0，      实际为：" << dt2 << endl;

		dt1.set(2099, 12, 31, 23, 59, 59);
		dt2 = dt1++;
		cout << "dt1应该是1900-1-1 0:0:0，      实际为：" << dt1 << endl;
		cout << "dt2应该是2099-12-31 23:59:59， 实际为：" << dt2 << endl;

		dt1.set(1900, 1, 1, 0, 0, 0);
		dt2 = dt1--;
		cout << "dt1应该是2099-12-31 23:59:59， 实际为：" << dt1 << endl;
		cout << "dt2应该是1900-1-1 0:0:0，      实际为：" << dt2 << endl;

		wait_for_enter();
	}

	if (1) {
		/* 测试比较运算符 */
		DateTime t1(2019, 5, 23, 12, 34, 7);
		DateTime t2(2019, 5, 23, 12, 34, 7);
		DateTime t3(2019, 4, 27, 12, 34, 7);

		cout << "测试比较运算符" << endl;

		cout << "比较结果应为0，实际为：" << (t1 > t2) << endl;
		cout << "比较结果应为1，实际为：" << (t1 >= t2) << endl;
		cout << "比较结果应为0，实际为：" << (t1 < t2) << endl;
		cout << "比较结果应为1，实际为：" << (t1 <= t2) << endl;
		cout << "比较结果应为1，实际为：" << (t1 == t2) << endl;
		cout << "比较结果应为0，实际为：" << (t1 != t2) << endl;

		cout << "比较结果应为1，实际为：" << (t1 > t3) << endl;
		cout << "比较结果应为1，实际为：" << (t1 >= t3) << endl;
		cout << "比较结果应为0，实际为：" << (t1 < t3) << endl;
		cout << "比较结果应为0，实际为：" << (t1 <= t3) << endl;
		cout << "比较结果应为0，实际为：" << (t1 == t3) << endl;
		cout << "比较结果应为1，实际为：" << (t1 != t3) << endl;

		wait_for_enter();
	}

}


int main()
{
	cout << "测试Date类" << endl;
	test_Date();

	cout << "测试Time类" << endl;
	test_Time();

	cout << "测试DateTime类" << endl;
	test_DateTime();

	return 0;
}
