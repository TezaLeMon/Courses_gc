// 1752762 ��x�� κ�ٴ�
#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <windows.h>

const int MAX_X = 69;	//����*��ɵı߿�Ŀ��
const int MAX_Y = 17;	//����*��ɵı߿�ĸ߶�

/* -- �������ӵ����ɺ������Է��ڴ˴� --*/
char menu()
{
	char chioce;
	while (1)
	{
		system("cls");
		printf("1.��I��J��K��L��������������(��Сд���ɣ��߽�ֹͣ)\n");
		printf("2.��I��J��K��L��������������(��Сд���ɣ��߽����)\n");
		printf("3.�ü�ͷ�������������ң��߽�ֹͣ\n");
		printf("4.�ü�ͷ�������������ң��߽����\n");
		printf("0.�˳�\n");
		printf("[��ѡ��0 - 4] ");

		chioce = _getche();
		if (chioce >= '0' && chioce <= '4')
			break;
	}
	return chioce;
}

/***************************************************************************
  �������ƣ�gotoxy
  ��    �ܣ�������ƶ���ָ��λ��
  ���������HANDLE hout������ļ����
			int X      ��ָ��λ�õ�x����
			int Y      ��ָ��λ�õ�y����
  �� �� ֵ����
  ˵    �����˺�����׼�޸�
***************************************************************************/
void gotoxy(const HANDLE hout, const int X, const int Y)
{
	COORD coord;
	coord.X = X;
	coord.Y = Y;
	SetConsoleCursorPosition(hout, coord);
}

/***************************************************************************
  �������ƣ�showch
  ��    �ܣ���ָ��λ�ô���ӡһ��ָ�����ַ�
  ���������HANDLE hout������ļ����
			int X      ��ָ��λ�õ�x����
			int Y      ��ָ��λ�õ�y����
			char ch    ��Ҫ��ӡ���ַ�
  �� �� ֵ����
  ˵    �����˺�����׼�޸�
***************************************************************************/
void showch(const HANDLE hout, const int X, const int Y, const char ch)
{
	gotoxy(hout, X, Y);
	putchar(ch);
}

/***************************************************************************
  �������ƣ�init_border
  ��    �ܣ���ʾ��ʼ�ı߿�����ַ�
  ���������HANDLE hout������ļ����
  �� �� ֵ����
  ˵    �����˺�����׼�޸�
***************************************************************************/
void init_border(const HANDLE hout)
{
	gotoxy(hout, 0, 0);	//����ƻ����Ͻ�(0,0)
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

	/* �����ʾ20����д��ĸ����ĸ��ֵ��XY���궼�����ʾ
	   rand()�����Ĺ��ܣ��������һ���� 0-32767 ֮�������
	   ˼������ʲô����£��������ѭ��ִ�����ɺ��㿴����ʵ����ĸ��������20���� */
	int i;
	for (i = 0; i < 20; i++)
		showch(hout, rand() % MAX_X + 1, rand() % MAX_Y + 1, 'A' + rand() % 26);

	return;
}

/* -- �������ӵ����ɺ������Է��ڴ˴� --*/
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
				printf("��Ϸ���������س������ز˵�.\n");
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
				printf("��Ϸ���������س������ز˵�.\n");
				while (_getch() != '\r')
					;
				break;
			default:
				continue;
		}
	}
}

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����main���������ڳ�ʼ��ʾ�����԰���ĿҪ��ȫ���Ʒ���д
***************************************************************************/
int main()
{
	const HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE); //ȡ��׼����豸��Ӧ�ľ��

	/* ����α����������ӣ�ֻ���ڳ���ʼʱִ��һ�μ��� */
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

/* -- �������ӵ����ɺ������Է��ڴ˴� --*/