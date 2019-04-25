#include <iostream>
#include <conio.h>
#include <string.h>
#include <iomanip>
#include "90-b2.h"
#include "cmd_console_tools.h"
using namespace std;

/***************************************************************************
  函数名称：
  功    能：显示提示信息
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
void to_be_continued(const char *prompt)
{
	setcolor(); //恢复缺省颜色
	
	cout << endl;
	if (prompt)
		cout << prompt << "，按回车键继续...";
	else
		cout << "按回车键继续...";

	/* 忽略除回车键外的所有输入（注意：_getch的回车是\r，而getchar是\n）*/
	while (_getch() != '\r')
		;
}

//输入数据
void input_int(const char *s, int *target, const int low, const int high, const int x, const int y)
{
	while (1) {
		showstr(x, y, s);
		cin >> *target;
		showstr(x, y + 1, "                      ");
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(1024, '\n');
		}
		else if (*target >= low && *target <= high)
			break;
		showstr(x + strlen(s), y, "                      ");
		showstr(x, y + 1, "输入不合法，请重新输入");
	}
}

void input_str2(const char *s, char *target, const int row_low, const int row_high, const int col_low, const int col_high)
{
	int x, y;
	getxy(x, y);
	cout << s;
	while (1) {
		showstr(strlen(s), y, "                      ");
		gotoxy(strlen(s), y);
		cin >> target[0];
		cin >> target[1];
		showstr(0, y + 1, "                      ");
		target[2] = '\0';
		cin.ignore(1024, '\n');
		if (target[0] >= 'A' && target[0] <= 'Z')
			target[0] = target[0] - 'A' + 'a';
		if (target[0] >= row_low && target[0] <= row_high && target[1] >= col_low && target[1] <= col_high)
			break;
		showstr(0, y + 1, "输入不合法，请重新输入");
	}
	gotoxy(0, y + 1);
}

void ball_creat_print(int ball[3], const int again_flag)
{
	cout << endl << "下3个彩球的颜色分别是：";
	if (!again_flag)
		for (int i = 0; i < 3; i++)
			cout << (ball[i] = 1 + rand() % 7) << " ";
	else
		for (int i = 0; i < 3; i++)
			cout << ball[i] << " ";
	cout << endl;
}

void ball_creat_print_img(int ball[3], const int again_flag)
{
	if (!again_flag)
		for (int i = 0; i < 3; i++)
			ball[i] = 1 + rand() % 7;
	showstr(4 * 9 + 4, 5, "╔═╦═╦═╗", COLOR_HWHITE, COLOR_HBLACK);
	for (int i = 0; i < 3; i++)
	{
		showstr(4 * 9 + 4 + 4 * i, 6, "║", COLOR_HWHITE, COLOR_HBLACK);
		showstr(4 * 9 + 6 + 4 * i, 6, "〇", 7 + ball[i], COLOR_HWHITE);
	}
	showstr(4 * 9 + 4 + 4 * 3, 6, "║", COLOR_HWHITE, COLOR_HBLACK);
	showstr(4 * 9 + 4, 7, "╚═╩═╩═╝", COLOR_HWHITE, COLOR_HBLACK);
}

void score_print(const int ball_conut[8])
{
	showstr(4 * 9 + 4, 1, "╔═════╗", COLOR_HWHITE, COLOR_HBLACK);
	showstr(4 * 9 + 4, 2, "║得分：    ║", COLOR_HWHITE, COLOR_HBLACK);
	showstr(4 * 9 + 4, 3, "╚═════╝", COLOR_HWHITE, COLOR_HBLACK);
	int score = 0;
	for (int i = 1; i < 8; i++)
		score += ball_conut[i] * 2;
	showint(4 * 9 + 4 + 8, 2, score, COLOR_HWHITE, COLOR_BLACK);
}

void ball_count_print(const int arr[MAX_ROW + 2][MAX_COL + 2], const int removeball_conut[8], const int row, const int col)
{
	showstr(4 * 9 + 4, 10, "╔═══════════╗", COLOR_HWHITE, COLOR_HBLACK);
	for (int i = 0; i < 8; i++)
		showstr(4 * 9 + 4, 11 + i, "║                      ║", COLOR_HWHITE, COLOR_HBLACK);
	showstr(4 * 9 + 4, 19, "╚═══════════╝", COLOR_HWHITE, COLOR_HBLACK);
	int ball[8] = { 0 };
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col; j++)
			ball[arr[i][j]]++;
	showstr(4 * 9 + 6, 11, "〇", COLOR_HWHITE, COLOR_HWHITE);
	setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << ":" << ball[0] << "/(" << setiosflags(ios::fixed) << setprecision(2) << (double)ball[0] / (row*col) * 100 << "%) del-" << removeball_conut[0];
	for (int i = 1; i < 8; i++)
	{
		showstr(4 * 9 + 6, 11 + i, "〇", COLOR_WHITE + i, COLOR_HWHITE);
		setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << ":" << ball[i] << "/(" << setiosflags(ios::fixed) << setprecision(2) << (double)ball[i] / (row*col) * 100 << "%) del-" << removeball_conut[i];
	}
}