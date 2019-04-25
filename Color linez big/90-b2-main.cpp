// 1752762 计1班 魏鹳达
#include <iostream>
#include <conio.h>
#include <time.h>
#include <stdlib.h>
#include "cmd_console_tools.h"
#include "90-b2.h"
using namespace std;
int menu()
{
	cout << "---------------------------------------------" << endl;
	cout << "1.内部数组，随机生成初始5个球" << endl;
	cout << "2.内部数组，随机生成60%的球，寻找移动路径" << endl;
	cout << "3.内部数组，完整版" << endl;
	cout << "4.画出n*n的框架（无分隔线），随机显示5个球" << endl;
	cout << "5.画出n*n的框架（有分隔线），随机显示5个球" << endl;
	cout << "6.n*n的框架，60%的球，支持鼠标，完成一次移动" << endl;
	cout << "7.cmd图形界面完整版" << endl;
	cout << "8.cmd图形界面完整版 - 支持同时读键（额外加分）" << endl;
	cout << "0.退出" << endl;
	cout << "---------------------------------------------" << endl;
	cout << "[请选择0 - 8] ";
	int ch;
	while (1)
	{
		ch = _getch();
		if (ch >= '0' && ch <= '8')
		{
			cout << ch - '0' << endl;
			to_be_continued(NULL);
			break;
		}
	}
	return ch;
}
int main()
{
	srand((unsigned)time(0));
	int arr[MAX_ROW + 2][MAX_COL + 2], row, col, ball[3];
	int path[MAX_ROW + 2][MAX_COL + 2] = { 0 };
	int ball_conut[8] = { 0 };
	setcursor(CURSOR_INVISIBLE);
	while (1)
	{
		setconsoleborder(80, 25, 80, 1000);
		setfontsize("Terminal", 16, 8);
		for (int i = 1; i < 8; i++)
			ball_conut[i] = 0;
		int choice = menu();
		if (choice == '0')
			return 0;
		cls();
		input_int("请输入行数(7-9)： ", &row, 7, 9, 0, 0);
		input_int("请输入列数(7-9)： ", &col, 7, 9, 0, 1);
		switch (choice)
		{
			case '1':
				array_create(arr, row, col, 5);
				array_print_text("初始数组：", arr, row, col);
				break;
			case '2':
				array_create(arr, row, col, int(row*col*0.6));
				array_print_text("当前数组：", arr, row, col);
				ball_creat_print(ball, 0);
				if (array_print_move_text(arr, path, row, col))
				{
					path_print_result_text(path, row, col);
					path_print_move_text(arr, path, row, col);
				}
				break; 
			case '3':
				array_create(arr, row, col, 5);
				while (!is_over(arr, row, col))
				{
					static int ball_flag = 0;
					array_print_text("当前数组：", arr, row, col);
					ball_creat_print(ball, ball_flag);
					int t = array_print_move_text(arr, path, row, col, 1);
					if (t == 1)
					{
						for (int i = 0; i < 3; i++)
						{
							array_add(arr, row, col, ball[i]);
							if (is_over)
								i = 3;
						}
						ball_flag = 0;
					}
					else
						ball_flag = 1;
					if (t)
						array_print_text("移动后数组：", arr, row, col);
				}
				break;
			case '4':
				array_create(arr, row, col, 5);
				array_print_text("初始数组：", arr, row, col);
				to_be_continued(NULL);
				setconsoleborder(26 + col, 15, 26 + col, 15);
				setfontsize("新宋体", 28);
				cout << "屏幕：15行" << 26 + col << "列" << endl;
				array_print_img_no(arr, row, col);
				break;
			case '5':
				array_create(arr, row, col, 5);
				array_print_text("初始数组：", arr, row, col);
				to_be_continued(NULL);
				setconsoleborder(4 * col + 3, 2 * row + 5, 4 * col + 2, 2 * row + 5);
				setfontsize("新宋体", 28); 
				cout << "屏幕：" << 2 * row + 5 << "行" << 4 * col + 2 << "列" << endl;
				array_print_img_yes(arr, row, col);
				break;
			case '6':
				array_create(arr, row, col, int(row*col*0.6));
				setconsoleborder(4 * col + 3, 2 * row + 5, 4 * col + 2, 2 * row + 5);
				setfontsize("新宋体", 28);
				cout << "屏幕：" << 2 * row + 5 << "行" << 4 * col + 2 << "列（右键退出）" << endl;
				array_print_img_yes(arr, row, col);
				array_print_move_img(arr, path, row, col);
				break;
			case '7':
			case '8':
				array_create(arr, row, col, 5);
				setconsoleborder(4 * 9 + 32, 2 * row + 5, 4 * 9 + 2, 2 * row + 5);
				setfontsize("新宋体", 28);
				while (!is_over(arr, row, col))
				{
					static int ball_flag = 0;
					cls();
					cout << "屏幕：" << 2 * row + 5 << "行" << 4 * col + 2 << "列（右键退出）" << endl;
					array_print_img_yes(arr, row, col);
					ball_creat_print_img(ball, ball_flag);
					score_print(ball_conut);
					ball_count_print(arr, ball_conut, row, col);
					int t = array_print_move_img(arr, path, row, col, ball_conut, choice - '7');
					if (t == 1)
					{
						for (int i = 0; i < 3; i++)
						{
							array_add(arr, row, col, ball[i]);
							if (is_over)
								i = 3;
						}
						ball_flag = 0;
					}
					else if (t == -1)
						break;
					else
						ball_flag = 1;
				}
				break;
			default:
				cout << "error" << endl;
				break;
		}
		to_be_continued("本小题结束");
	}
	return 0;
}