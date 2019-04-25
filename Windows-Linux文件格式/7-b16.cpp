// 1752762 ��1�� κ�ٴ�
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
using namespace std;
#define MAX_LEN_FILENAME 32	//����ļ�������
#define LEN_CH_DISPLAY 16	//ÿ�������ʾ�ַ���

int usage()
{
	cout << "�ļ���������ʽ�����ԣ�" << endl;
	cout << "a.txt������·����ʽ" << endl;
	cout << "..\\data\\b.dat�����·����ʽ" << endl;
	cout << "C:\\Windows\\System32\\c.dat���������·����ʽ" << endl;
	cout << "�������ļ���: ";
	return 0;
}

int main(int argc, char** argv)
{
	char file_name[MAX_LEN_FILENAME + 1];
	if (argc == 1) {
		usage();
		cin >> file_name;
	}
	else
		strcpy(file_name, argv[1]);

	ifstream fin;
	fin.open(file_name, ios::in | ios::binary);
	if (!fin.is_open()) {
		cout << "�ļ�" << file_name << "��ʧ��!" << endl;
		return -1;
	}

	int i = 0, j, flag1 = 1, flag2 = 1;
	char ch[LEN_CH_DISPLAY + 1] = { '\0' };
	while (flag2) {
		if (flag1)
			ch[i%LEN_CH_DISPLAY] = fin.get();
		if (fin.eof()) {
			flag1 = 0;
			ch[i%LEN_CH_DISPLAY] = '\0';
		}

		if (!(i%LEN_CH_DISPLAY))
			cout << setw(8) << setfill('0') << hex << i << "  ";	//ÿ�����ַ���ַ
		else if (i%LEN_CH_DISPLAY % 8 == 0) {
			if(flag1)
				cout << "- ";
			else
				cout << "  ";
		}
		if (flag1)
			cout << setw(2) << setfill('0') << hex << (int)(ch[i%LEN_CH_DISPLAY] & 0xff) << ' ';
		else
			cout << "   ";

		if (flag1 && (ch[i%LEN_CH_DISPLAY] < 33 || ch[i%LEN_CH_DISPLAY] > 126))
			ch[i%LEN_CH_DISPLAY] = '.';

		if (i%LEN_CH_DISPLAY == LEN_CH_DISPLAY - 1) {
			cout << "    ";
			for (j = 0; j < LEN_CH_DISPLAY; j++) {
				if (ch[j] != '\0')
					cout << ch[j];
				ch[j] = '\0';
			}
			cout << endl;
			if (!flag1)
				flag2 = 0;
		}
		i++;
	}
	fin.close();
	return 0;
}