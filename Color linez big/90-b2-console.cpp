// 1752762 计1班 魏鹳达
#include <iomanip>
#include <iostream>
#include <Windows.h>
#include "90-b2.h"
#include "cmd_console_tools.h"
using namespace std;
void array_print_text(const char* s, const int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col, const int color)
{
	int i, j;
	if (s)
		cout << endl << s << endl;
	cout << "  |";
	for (i = 1; i <= col; i++)
		cout << setw(3) << i;
	cout << endl << "--+-";
	for (i = 1; i <= col; i++)
		cout << "---";
	for (i = 1; i <= row; i++)
	{
		cout << endl;
		cout << char('A' + i - 1) << " |";
		for (j = 1; j <= col; j++)
		{
			cout << "  ";
			if (color&&arr[i][j] > 0)
				setcolor(COLOR_HYELLOW, arr[i][j]);
			cout << arr[i][j];
			setcolor();
		}
	}
	cout << endl;
}

int array_print_move_text(int arr[MAX_ROW + 2][MAX_COL + 2], int path[MAX_ROW + 2][MAX_COL + 2], const int row, const int col, const int move_flag)
{
	char from[3], to[3];
	int x, y;
	while (1)
	{
		input_str2("请以字母+数字形式[例：c2]输入要移动球的矩阵坐标：", from, 'a', 'a' + row - 1, '1', '1' + col - 1);
		if (arr[from[0] - 'a' + 1][from[1] - '1' + 1] > 0)
			break;
		cout << "起始位置为空，请重新输入";
		getxy(x, y);
		gotoxy(50, y - 1);
	}
	cout << "输入为" << char(from[0] - 'a' + 'A') << "行" << from[1] << "列" << endl;
	while (1)
	{
		input_str2("请以字母+数字形式[例：c2]输入要移动球的目的坐标：", to, 'a', 'a' + row - 1, '1', '1' + col - 1);
		if (arr[to[0] - 'a' + 1][to[1] - '1' + 1] == 0)
			break;
		cout << "移动位置非空，请重新输入";
		getxy(x, y);
		gotoxy(50, y - 1);
	}
	cout << "输入为" << char(to[0] - 'a' + 'A') << "行" << to[1] << "列" << endl;
	int flag = 0;
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col; j++)
			path[i][j] = 0;
	if (!path_find(arr, path, from[0] - 'a' + 1, from[1] - '1' + 1, to[0] - 'a' + 1, to[1] - '1' + 1, flag))
	{
		cout << "无法找到移动路径" << endl;
		return 0;
	}
	else if (move_flag)
	{
		array_move(arr, from[0] - 'a' + 1, from[1] - '1' + 1, to[0] - 'a' + 1, to[1] - '1' + 1);
		if (remove(arr, to[0] - 'a' + 1, to[1] - '1' + 1, row, col))
			return 2;
	}
	return 1;
}

void path_print_result_text(const int path[MAX_ROW + 2][MAX_COL + 2], const int row, const int col)
{
	int i, j;
	cout << endl << "查找结果数组：" << endl << endl;
	cout << "  |";
	for (i = 1; i <= col; i++)
		cout << setw(3) << i;
	cout << endl << "--+-";
	for (i = 1; i <= col; i++)
		cout << "---";
	for (i = 1; i <= row; i++)
	{
		cout << endl;
		cout << char('A' + i - 1) << " |";
		for (j = 1; j <= col; j++)
		{
			cout << "  ";
			if (path[i][j] == 1)
				cout << "*";
			else
				cout << "0";
		}
	}
	cout << endl;
}
void path_print_move_text(const int arr[MAX_ROW + 2][MAX_COL + 2], const int path[MAX_ROW + 2][MAX_COL + 2], const int row, const int col)
{
	int i, j;
	cout << endl << "移动路径（不同色标识）：" << endl << endl;
	cout << "  |";
	for (i = 1; i <= col; i++)
		cout << setw(3) << i;
	cout << endl << "--+-";
	for (i = 1; i <= col; i++)
		cout << "---";
	for (i = 1; i <= row; i++)
	{
		cout << endl;
		cout << char('A' + i - 1) << " |";
		for (j = 1; j <= col; j++)
		{
			cout << "  ";
			if (path[i][j] == 1)
				setcolor(COLOR_HYELLOW, COLOR_HBLUE);
			cout << arr[i][j];                                                                                                                               
			setcolor();
		}
	}
	cout << endl;
}


void disp_border_img_no(const int row, const int col)
{
	setcolor(COLOR_HWHITE, COLOR_HBLACK);
	cout << "╔";
	showstr(2, 1, "═", COLOR_HWHITE, COLOR_HBLACK, col);
	cout << "╗" << endl;
	for (int i = 0; i < row; i++)
	{
		cout << "║";
		gotoxy(2 * (col + 1), 2 + i);
		cout << "║" << endl;
	}
	cout << "╚";
	for (int i = 0; i < col; i++)
		cout << "═";
	cout << "╝" << endl;
}
void disp_arr_img_no(const int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col)
{
	setcolor(COLOR_HWHITE, COLOR_HWHITE);
	for (int i = 1; i <= row; i++)
	{
		gotoxy(2, 1 + i);
		for (int j = 1; j <= col; j++)
		{
			if (arr[i][j])
				setcolor(7 + arr[i][j], COLOR_HWHITE);
			cout << "〇";
			setcolor(COLOR_HWHITE, COLOR_HWHITE);
		}
	}
	gotoxy(0, 3 + row);
}
void array_print_img_no(const int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col)
{
	disp_border_img_no(row, col);
	disp_arr_img_no(arr, row, col);
}

void disp_border_img_yes(const int row, const int col)
{
	setcolor(COLOR_HWHITE, COLOR_HBLACK);
	cout << "╔";
	for (int i = 1; i < col; i++)
		cout << "═╦";
	cout << "═╗" << endl;
	for (int i = 0; i < 2 * row - 1; i++)
	{
		if (i % 2)
			cout << "╠═";
		else
			cout << "║  ";
		for (int j = 1; j < col; j++)
		{
			if (i % 2)
				cout << "╬═";
			else
				cout << "║  ";
		}
		if (i % 2)
			cout << "╣";
		else
			cout << "║";
		cout << endl;
	}
	cout << "╚";
	for (int i = 1; i < col; i++)
		cout << "═╩";
	cout << "═╝" << endl;
}
void disp_arr_img_yes(const int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col)
{
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col; j++)
			if (arr[i][j])
				showstr(4 * j - 2, 2 * i, "〇", 7 + arr[i][j], COLOR_HWHITE);
			else
				showstr(4 * j - 2, 2 * i, "〇", COLOR_HWHITE, COLOR_HWHITE);
	gotoxy(0, 2 * row + 2);
	setcolor();
}
void array_print_img_yes(const int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col)
{
	disp_border_img_yes(row, col);
	disp_arr_img_yes(arr, row, col);
}

//读入鼠标动作 按下左键返回1 按下右键返回0
int read_position_mouse_img(int &t_row, int &t_col, const int row, const int col, const int can_keyboard = 0)
{
	int X = 2, Y = 3;
	int ret, maction;
	int keycode1, keycode2;
	t_row = 1;
	t_col = 1;
	enable_mouse();
	setcolor();
	while (1) {
		/* 读鼠标/键盘，返回值为下述操作中的某一种, 当前鼠标位置在<X,Y>处 */
		ret = read_keyboard_and_mouse(X, Y, maction, keycode1, keycode2);
		if (ret == CCT_MOUSE_EVENT) {
			if (Y > 1 && Y < 2 * row + 1 && Y % 2 == 0)
				t_row = Y / 2;
			if (X < 4 * col&&X % 4>1)
				t_col = X / 4 + 1;
			gotoxy(0, 2 + 2 * row);
			cout << "[当前光标] " << setw(2) << char(t_row + 'A' - 1) << "行" << setw(2) << t_col << "列";
			switch (maction) {
				case MOUSE_LEFT_BUTTON_CLICK:			//按下左键
					return 1;
				case MOUSE_RIGHT_BUTTON_CLICK:			//按下右键
					return 0;
				default:
					break;
			}
		}
		else if (can_keyboard&&ret == CCT_KEYBOARD_EVENT) {
			switch (keycode1) {
				case 27: //ESC
					setcursor(CURSOR_INVISIBLE);
					return 0;
				case '\r':	//回车
					setcursor(CURSOR_INVISIBLE);
					return 1;
				case 224:
					switch (keycode2)
					{
						case KB_ARROW_UP:
							if (t_row > 1)
								t_row--;
							break;
						case KB_ARROW_DOWN:
							if (t_row < row)
								t_row++;
							break;
						case KB_ARROW_RIGHT:
							if (t_col < col)
								t_col++;
							break;
						case KB_ARROW_LEFT:
							if (t_col > 1)
								t_col--;
							break;
						default:
							break;
					}
				default:
					break;
			}
			gotoxy(0, 2 + 2 * row);
			cout << "[当前光标] " << setw(2) << char(t_row + 'A' - 1) << "行" << setw(2) << t_col << "列";
			setcursor(CURSOR_VISIBLE_FULL);
			gotoxy(4 * t_col - 2, 2 * t_row);
		}
	}
	disable_mouse();	//禁用鼠标
}

//type: 1右 2下 3左 4上
void disp_move_single(const int arr[MAX_ROW + 2][MAX_COL + 2], const int row_from, const int col_from, const int row_ori, const int col_ori, const int type)
{
	if (type % 2)	//水平
	{
		int t = 2 - type;
		showstr(4 * col_from - 2, 2 * row_from, "〇", COLOR_HWHITE, COLOR_HWHITE);
		Sleep(50);
		showstr(4 * col_from - 2 + 2 * t, 2 * row_from, "〇", 7 + arr[row_ori][col_ori], COLOR_HWHITE);
		Sleep(50);
		showstr(4 * col_from - 2 + 2 * t, 2 * row_from, "║", COLOR_HWHITE, COLOR_HBLACK);
		Sleep(50);
		showstr(4 * col_from - 2 + 4 * t, 2 * row_from, "〇", 7 + arr[row_ori][col_ori], COLOR_HWHITE);
		Sleep(50);
	}
	else
	{
		int t = 3 - type;
		showstr(4 * col_from - 2, 2 * row_from, "〇", COLOR_HWHITE, COLOR_HWHITE);
		Sleep(50);
		showstr(4 * col_from - 2, 2 * row_from + t, "〇", 7 + arr[row_ori][col_ori], COLOR_HWHITE);
		Sleep(50);
		showstr(4 * col_from - 2, 2 * row_from + t, "═", COLOR_HWHITE, COLOR_HBLACK);
		Sleep(50);
		showstr(4 * col_from - 2, 2 * row_from + 2 * t, "〇", 7 + arr[row_ori][col_ori], COLOR_HWHITE);
		Sleep(50);
	}
	setcolor();
}
void disp_move_img(const int arr[MAX_ROW + 2][MAX_COL + 2], int path[MAX_ROW + 2][MAX_COL + 2], const int row_from, const int col_from, const int row_to, const int col_to, const int row_ori, const int col_ori)
{
	if (row_from == row_to && col_from == col_to)
		return;

	path[row_from][col_from] = 2;
	if (path[row_from][col_from + 1] == 1)
	{
		disp_move_single(arr, row_from, col_from, row_ori, col_ori, 1);
		disp_move_img(arr, path, row_from, col_from + 1, row_to, col_to, row_ori, col_ori);
	}
	else if (path[row_from + 1][col_from] == 1)
	{
		disp_move_single(arr, row_from, col_from, row_ori, col_ori, 2);
		disp_move_img(arr, path, row_from + 1, col_from, row_to, col_to, row_ori, col_ori);
	}
	else if (path[row_from][col_from - 1] == 1)
	{
		disp_move_single(arr, row_from, col_from, row_ori, col_ori, 3);
		disp_move_img(arr, path, row_from, col_from - 1, row_to, col_to, row_ori, col_ori);
	}
	else if (path[row_from - 1][col_from] == 1)
	{
		disp_move_single(arr, row_from, col_from, row_ori, col_ori, 4);
		disp_move_img(arr, path, row_from - 1, col_from, row_to, col_to, row_ori, col_ori);
	}
}

int array_print_move_img(int arr[MAX_ROW + 2][MAX_COL + 2], int path[MAX_ROW + 2][MAX_COL + 2], const int row, const int col, int *ball_count, const int can_keyboard)
{
	int row_from, row_to, col_from, col_to;
	int flag = 0;
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col; j++)
			path[i][j] = 0;
	do
	{
		if (!read_position_mouse_img(row_from, col_from, row, col, can_keyboard))
			return -1;
	} while (arr[row_from][col_from] <= 0);
	showstr(4 * col_from - 2, 2 * row_from, "◎", 7 + arr[row_from][col_from], COLOR_HWHITE);
	do
	{
		while (1)
		{
			if (!read_position_mouse_img(row_to, col_to, row, col, can_keyboard))
				return -1;
			if (arr[row_to][col_to] > 0)
			{
				showstr(4 * col_from - 2, 2 * row_from, "〇", 7 + arr[row_from][col_from], COLOR_HWHITE);
				row_from = row_to;
				col_from = col_to;
				showstr(4 * col_from - 2, 2 * row_from, "◎", 7 + arr[row_from][col_from], COLOR_HWHITE);
				continue;
			}
			break;
		}
	} while (!path_find(arr, path, row_from, col_from, row_to, col_to, flag));
	disp_move_img(arr, path, row_from, col_from, row_to, col_to, row_from, col_from);
	gotoxy(0, 2 + 2 * row);
	array_move(arr, row_from, col_from, row_to, col_to);
	if (remove(arr, row_to, col_to, row, col, ball_count))
		return 2;
	return 1;
}