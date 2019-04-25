// 1752762 计1班 魏鹳达
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int usage(const char *procname)
{
	cout << "Usage: " << procname << " 要检查的学号/all 匹配学号/all 源程序名/all 相似度阀值(60-100) 输出(filename/screen)" << endl;
	cout << "               1859999          1859998      all          80                screen" << endl;
	cout << "               1859999          all          7-b2.cpp     75                result.txt" << endl;
	cout << "               all              all          7-b2.cpp     80                check.dat" << endl;
	cout << "               all              all          all          85                screen" << endl;

	return 0;
}

//符合规范返回num值 非法则返回-1 all返回0
int check_num(const char *num, const char *prompt)
{
	if (strcmp(num, "all") == 0)
		return 0;
	if (strlen(num) != 7) {		//写死了7位
		cout << prompt << "不是7位";
		return -1;
	}
	int n = atoi(num);
	if (n >= 1000000 && n <= 9999999)	//0开头也被排除 实际上需要根据实际情况判定
		return n;
	else {
		cout << prompt << "不是7位数字";
		return -1;
	}
}

//超出长度返回-1 符合规范返回0
int check_str(const char *str, const char *prompt)
{
	if (strlen(str) > 32) {
		cout << prompt << "文件名超过了32字节" << endl;
		return -1;
	}
	return 0;
}

//60-80内 返回值 不在范围内 返回缺省值80
int check_int(const char *num, int low, int high)
{
	int n = atoi(num);
	if (n >= low && n <= high)
		return n;
	return 80;
}

int main(int argc, char** argv)
{
	int num_jc, num_pp, yz;
	if (argc < 6) {
		usage(argv[0]);
		return -1;
	}

	if ((num_jc = check_num(argv[1], "要检查的学号")) == -1)
		return -1;
	if ((num_pp = check_num(argv[2], "要匹配的学号")) == -1)
		return -1;
	else if (num_jc == 0 && num_pp != 0) {
		cout << "检查学号是all,匹配学号必须是all" << endl;
		return -1;
	}
	if (check_str(argv[3], "源程序") == -1)
		return -1;
	yz = check_int(argv[4], 60, 80);
	if (check_str(argv[5], "输出结果") == -1)
		return -1;

	cout << "参数检查通过" << endl;
	cout << "检查学号：";
	if (num_jc)
		cout << num_jc << endl;
	else
		cout << "all" << endl;

	cout << "匹配学号：";
	if (num_pp)
		cout << num_pp << endl;
	else
		cout << "all" << endl;

	cout << "源文件名：" << argv[3] << endl;
	cout << "匹配阈值：" << yz << endl;
	cout << "输出目标：" << argv[5] << endl;
	return 0;
}
