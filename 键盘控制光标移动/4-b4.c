// 1752762 计x班 魏鹳达
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

const int MAX_X = 69;	//定义*组成的边框的宽度
const int MAX_Y = 17;	//定义*组成的边框的高度

/* -- 按需增加的若干函数可以放在此处 --*/
char menu()
{
	char chioce;
	while (1)
	{
		system("cls");
		printf("1.用I、J、K、L键控制上下左右(大小写均可，边界停止)\n");
		printf("2.用I、J、K、L键控制上下左右(大小写均可，边界回绕)\n");
		printf("3.用箭头键控制上下左右，边界停止\n");
		printf("4.用箭头键控制上下左右，边界回绕\n");
		printf("0.退出\n");
		printf("[请选择0 - 4] ");

		chioce = _getche();
		if (chioce >= '0' && chioce <= '4')
			break;
	}
	return chioce;
}

/***************************************************************************
  函数名称：gotoxy
  功    能：将光标移动到指定位置
  输入参数：HANDLE hout：输出文件句柄
			int X      ：指定位置的x坐标
			int Y      ：指定位置的y坐标
  返 回 值：无
  说    明：此函数不准修改
***************************************************************************/
void gotoxy(const HANDLE hout, const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/***************************************************************************
  函数名称：showch
  功    能：在指定位置处打印一个指定的字符
  输入参数：HANDLE hout：输出文件句柄
			int X      ：指定位置的x坐标
			int Y      ：指定位置的y坐标
			char ch    ：要打印的字符
  返 回 值：无
  说    明：此函数不准修改
***************************************************************************/
void showch(const HANDLE hout, const int X, const int Y, const char ch)
{
	gotoxy(hout, X, Y);
	putchar(ch);
}

/***************************************************************************
  函数名称：init_border
  功    能：显示初始的边框及随机字符
  输入参数：HANDLE hout：输出文件句柄
  返 回 值：无
  说    明：此函数不准修改
***************************************************************************/
void init_border(const HANDLE hout)
{
	gotoxy(hout, 0, 0);	//光标移回左上角(0,0)
	printf("***********************************************************************\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("*                                                                     *\n");
	printf("***********************************************************************\n");

	/* 随机显示20个大写字母，字母的值、XY坐标都随机显示
	   rand()函数的功能：随机生成一个在 0-32767 之间的整数
	   思考：在什么情况下，下面这个循环执行生成后，你看到的实际字母个数不足20个？ */
	int i;
	for (i = 0; i < 20; i++)
		showch(hout, rand() % MAX_X + 1, rand() % MAX_Y + 1, 'A' + rand() % 26);

	return;
}

/* -- 按需增加的若干函数可以放在此处 --*/
void move_ijkl(const HANDLE hout, int chioce)
{
	int x = MAX_X / 2 + 1, y = MAX_Y / 2 + 1;
	int run = 1;
	gotoxy(hout, x, y);
	while (run)
	{
		switch (_getch())
		{
			case 224:
				_getch();
				break;
			case 'i':
			case 'I':
				y--;
				if (chioce == 0 && y == 0)
					y = 1;
				else if (chioce == 1 && y == 0)
					y = MAX_Y - 1;
				gotoxy(hout, x, y);
				break;
			case 'j':
			case 'J':
				x--;
				if (chioce == 0 && x == 0)
					x = 1;
				else if (chioce == 1 && x == 0)
					x = MAX_X - 1;
				gotoxy(hout, x, y);
				break;
			case 'k':
			case 'K':
				y++;
				if (chioce == 0 && y == MAX_Y + 1)
					y = MAX_Y;
				else if (chioce == 1 && y == MAX_Y + 1)
					y = 1;
				gotoxy(hout, x, y);
				break;
			case 'l':
			case 'L':
				x++;
				if (chioce == 0 && x == MAX_X + 1)
					x = MAX_X;
				else if (chioce == 1 && x == MAX_X + 1)
					x = 1;
				gotoxy(hout, x, y);
				break;
			case ' ':
				printf(" ");
				gotoxy(hout, x, y);
				break;
			case 'q':
			case 'Q':
				run = 0;
				gotoxy(hout, 0, MAX_Y + 6);
				printf("游戏结束，按回车键返回菜单.\n");
				while (_getch() != '\r')
					;
				break;
			default:
				continue;
		}
	}
}

void move_sxzy(const HANDLE hout, int chioce)
{
	int x = MAX_X / 2 + 1, y = MAX_Y / 2 + 1;
	int run = 1;
	gotoxy(hout, x, y);
	while (run)
	{
		switch (_getch())
		{
			case 224:
				switch (_getch())
				{
					case 72:
						y--;
						if (chioce == 0 && y == 0)
							y = 1;
						else if (chioce == 1 && y == 0)
							y = MAX_Y - 1;
						gotoxy(hout, x, y);
						break;
					case 75:
						x--;
						if (chioce == 0 && x == 0)
							x = 1;
						else if (chioce == 1 && x == 0)
							x = MAX_X - 1;
						gotoxy(hout, x, y);
						break;
					case 80:
						y++;
						if (chioce == 0 && y == MAX_Y + 1)
							y = MAX_Y;
						else if (chioce == 1 && y == MAX_Y + 1)
							y = 1;
						gotoxy(hout, x, y);
						break;
					case 77:
						x++;
						if (chioce == 0 && x == MAX_X + 1)
							x = MAX_X;
						else if (chioce == 1 && x == MAX_X + 1)
							x = 1;
						gotoxy(hout, x, y);
						break;
					default:
						break;
				}
				break;
			case ' ':
				printf(" ");
				gotoxy(hout, x, y);
				break;
			case 'q':
			case 'Q':
				run = 0;
				gotoxy(hout, 0, MAX_Y + 6);
				printf("游戏结束，按回车键返回菜单.\n");
				while (_getch() != '\r')
					;
				break;
			default:
				continue;
		}
	}
}

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：main函数仅用于初始演示，可以按题目要求全部推翻重写
***************************************************************************/
int main()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //取标准输出设备对应的句柄

	/* 生成伪随机数的种子，只需在程序开始时执行一次即可 */
	srand((unsigned int)(time(0)));

	int is_run = 1;
	char chioce;
	while (is_run)
	{
		chioce = menu();

		switch (chioce)
		{
			case '1':
			case '2':
				init_border(hout);
				move_ijkl(hout, chioce - '1');
				break;
			case '3':
			case '4':
				init_border(hout);
				move_sxzy(hout, chioce - '3');
				break;
			case '0':
				is_run = 0;
				break;
			default:
				break;
		}
	}

	return 0;
}

/* -- 按需增加的若干函数可以放在此处 --*/