// 1752762 计1班 魏鹳达
#define _CRT_SECURE_NO_WARNINGS		//使用了VS2017认为unsafe的函数
#include <iostream>
#include <ctime>
#include <conio.h>
#include <cstring>
using namespace std;

struct tj_time {
	int tj_year;	//表示年份
	int tj_month;	//表示月(1-12)
	int tj_day;		//表示日(1-28/29/30/31)
	int tj_hour;	//表示小时(0-23)
	int tj_minute;	//表示分(0-59)
	int tj_second;	//表示秒(0-59)
};

/* 可以在此定义其它需要的函数 */



/***************************************************************************
  函数名称：
  功    能：给出提示并等待回车键
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void wait_for_enter(const char *prompt = "")
{
	if (strlen(prompt) == 0)
		cout << endl << "按回车键继续";
	else
		cout << endl << prompt << "，按回车键继续";

	while (_getch() != '\r')
		;
	cout << endl << endl;
}

/***************************************************************************
  函数名称：
  功    能：调用系统的转换函数将整型秒值转换为与本题相似的结构体并输出
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void system_time_output(const time_t input_time)  //time_t的本质是64位无符号整数
{
	struct tm *tt;	//struct tm 为系统定义的结构体
	
	tt = localtime(&input_time);	//localtime为系统函数
	
	/* tm_*** 为struct tm中的成员，和本题的struct tj_time具体的内容不完全符合，具体含义自己查找相关资料 */
	cout << tt->tm_year + 1900 << '-' << tt->tm_mon + 1 << '-' << tt->tm_mday << ' ' << tt->tm_hour << ':' << tt->tm_min << ':' << tt->tm_sec << endl;

	return;
}

/***************************************************************************
  函数名称：
  功    能：自定义转换结果输出函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void tj_time_output(struct tj_time *tp)
{
	/* 实现自定义结构的输出，输出形式与system_time_output相同 */
	cout << tp->tj_year << '-' << tp->tj_month << '-' << tp->tj_day << ' ' << tp->tj_hour << ':' << tp->tj_minute << ':' << tp->tj_second << endl;
}

/***************************************************************************
  函数名称：
  功    能：自定义转换函数
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
struct tj_time *tj_time_convert(int input_time)
{
	static struct tj_time result;	//定义静态局部变量，不准动

	/* 实现过程开始，在下面添加相应的定义及执行语句即可 */
	struct tm *t;
	time_t now;
	time(&now);
	t = localtime(&now);
	input_time += t->tm_isdst;

	int day_total[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	result.tj_second = input_time % 60;
	input_time /= 60;	//剩下的分
	result.tj_minute = input_time % 60;
	input_time /= 60;	//剩下的时

	result.tj_hour = input_time % 24;
	const int pass_year_per4 = input_time / ((365 * 3 + 366) * 24);	//以4年为单位
	result.tj_year = 1970 + 4 * pass_year_per4;	//有缺年 之后补齐不到4年的
	input_time %= ((365 * 3 + 366) * 24);	//余下的时

	int hour_single_year;
	while (1)	//补齐年数
	{
		hour_single_year = 365 * 24;
		if ((result.tj_year % 4 == 0) && (result.tj_year % 100 != 0) || (result.tj_year % 400 == 0))
			hour_single_year += 24;
		if (input_time < hour_single_year)
			break;
		result.tj_year++;
		input_time -= hour_single_year;
	}

	input_time /= 24;	//剩下的天数
	input_time++;
	if ((result.tj_year % 4 == 0) && (result.tj_year % 100 != 0) || (result.tj_year % 400 == 0))
		day_total[1] = 29;
	else
		day_total[1] = 28;
	/* 实现过程结束 */
	for (result.tj_month = 0; day_total[result.tj_month] < input_time; result.tj_month++)
		input_time -= day_total[result.tj_month];
	result.tj_day = input_time;
	result.tj_month++;
	return &result;	//注意，返回的是静态局部变量的地址，本语句不准动
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int main()
{
	int test_time[] = { 1, 123456789, 349823021, 987654321, 1202990407, 1216468807, 1250312143, 1272636353, 1326193524, 1336549496, 1392837128, 1625675376, 2052743737 };
	int i;
	struct tj_time *tp;

	for (i = 0; i < sizeof(test_time) / sizeof(int); i++) {
		cout << "秒数            ：" << test_time[i] << endl;
		cout << "系统转换的结果  ：";
		system_time_output(test_time[i]);

		cout << "自定义转换的结果：";
		tp = tj_time_convert(test_time[i]);
		tj_time_output(tp);

		wait_for_enter();
	}

	if (1) {
		struct tj_time *tp;
		int t = (int)time(0);		//系统函数，取当前系统时间（从1970-01-01 00:00:00开始的秒数）

		cout << "当前系统时间    ：" << t << endl;
		cout << "系统转换的结果  ：";
		system_time_output(t);

		cout << "自定义转换的结果：";
		tp = tj_time_convert(t);
		tj_time_output(tp);

		wait_for_enter();
	}

	return 0;
}
