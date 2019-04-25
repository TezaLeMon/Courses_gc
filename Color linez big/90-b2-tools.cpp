#include <iostream>
#include <conio.h>
#include <string.h>
#include <iomanip>
#include "90-b2.h"
#include "cmd_console_tools.h"
using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ���ʾ��ʾ��Ϣ
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
void to_be_continued(const char *prompt)
{
	setcolor(); //�ָ�ȱʡ��ɫ
	
	cout << endl;
	if (prompt)
		cout << prompt << "�����س�������...";
	else
		cout << "���س�������...";

	/* ���Գ��س�������������루ע�⣺_getch�Ļس���\r����getchar��\n��*/
	while (_getch() != '\r')
		;
}

//��������
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
		showstr(x, y + 1, "���벻�Ϸ�������������");
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
		showstr(0, y + 1, "���벻�Ϸ�������������");
	}
	gotoxy(0, y + 1);
}

void ball_creat_print(int ball[3], const int again_flag)
{
	cout << endl << "��3���������ɫ�ֱ��ǣ�";
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
	showstr(4 * 9 + 4, 5, "�X�T�j�T�j�T�[", COLOR_HWHITE, COLOR_HBLACK);
	for (int i = 0; i < 3; i++)
	{
		showstr(4 * 9 + 4 + 4 * i, 6, "�U", COLOR_HWHITE, COLOR_HBLACK);
		showstr(4 * 9 + 6 + 4 * i, 6, "��", 7 + ball[i], COLOR_HWHITE);
	}
	showstr(4 * 9 + 4 + 4 * 3, 6, "�U", COLOR_HWHITE, COLOR_HBLACK);
	showstr(4 * 9 + 4, 7, "�^�T�m�T�m�T�a", COLOR_HWHITE, COLOR_HBLACK);
}

void score_print(const int ball_conut[8])
{
	showstr(4 * 9 + 4, 1, "�X�T�T�T�T�T�[", COLOR_HWHITE, COLOR_HBLACK);
	showstr(4 * 9 + 4, 2, "�U�÷֣�    �U", COLOR_HWHITE, COLOR_HBLACK);
	showstr(4 * 9 + 4, 3, "�^�T�T�T�T�T�a", COLOR_HWHITE, COLOR_HBLACK);
	int score = 0;
	for (int i = 1; i < 8; i++)
		score += ball_conut[i] * 2;
	showint(4 * 9 + 4 + 8, 2, score, COLOR_HWHITE, COLOR_BLACK);
}

void ball_count_print(const int arr[MAX_ROW + 2][MAX_COL + 2], const int removeball_conut[8], const int row, const int col)
{
	showstr(4 * 9 + 4, 10, "�X�T�T�T�T�T�T�T�T�T�T�T�[", COLOR_HWHITE, COLOR_HBLACK);
	for (int i = 0; i < 8; i++)
		showstr(4 * 9 + 4, 11 + i, "�U                      �U", COLOR_HWHITE, COLOR_HBLACK);
	showstr(4 * 9 + 4, 19, "�^�T�T�T�T�T�T�T�T�T�T�T�a", COLOR_HWHITE, COLOR_HBLACK);
	int ball[8] = { 0 };
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col; j++)
			ball[arr[i][j]]++;
	showstr(4 * 9 + 6, 11, "��", COLOR_HWHITE, COLOR_HWHITE);
	setcolor(COLOR_HWHITE, COLOR_BLACK);
	cout << ":" << ball[0] << "/(" << setiosflags(ios::fixed) << setprecision(2) << (double)ball[0] / (row*col) * 100 << "%) del-" << removeball_conut[0];
	for (int i = 1; i < 8; i++)
	{
		showstr(4 * 9 + 6, 11 + i, "��", COLOR_WHITE + i, COLOR_HWHITE);
		setcolor(COLOR_HWHITE, COLOR_BLACK);
		cout << ":" << ball[i] << "/(" << setiosflags(ios::fixed) << setprecision(2) << (double)ball[i] / (row*col) * 100 << "%) del-" << removeball_conut[i];
	}
}