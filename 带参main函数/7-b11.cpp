// 1752762 ��1�� κ�ٴ�
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdlib.h>
#include <string.h>
using namespace std;

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int usage(const char *procname)
{
	cout << "Usage: " << procname << " Ҫ����ѧ��/all ƥ��ѧ��/all Դ������/all ���ƶȷ�ֵ(60-100) ���(filename/screen)" << endl;
	cout << "               1859999          1859998      all          80                screen" << endl;
	cout << "               1859999          all          7-b2.cpp     75                result.txt" << endl;
	cout << "               all              all          7-b2.cpp     80                check.dat" << endl;
	cout << "               all              all          all          85                screen" << endl;

	return 0;
}

//���Ϲ淶����numֵ �Ƿ��򷵻�-1 all����0
int check_num(const char *num, const char *prompt)
{
	if (strcmp(num, "all") == 0)
		return 0;
	if (strlen(num) != 7) {		//д����7λ
		cout << prompt << "����7λ";
		return -1;
	}
	int n = atoi(num);
	if (n >= 1000000 && n <= 9999999)	//0��ͷҲ���ų� ʵ������Ҫ����ʵ������ж�
		return n;
	else {
		cout << prompt << "����7λ����";
		return -1;
	}
}

//�������ȷ���-1 ���Ϲ淶����0
int check_str(const char *str, const char *prompt)
{
	if (strlen(str) > 32) {
		cout << prompt << "�ļ���������32�ֽ�" << endl;
		return -1;
	}
	return 0;
}

//60-80�� ����ֵ ���ڷ�Χ�� ����ȱʡֵ80
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

	if ((num_jc = check_num(argv[1], "Ҫ����ѧ��")) == -1)
		return -1;
	if ((num_pp = check_num(argv[2], "Ҫƥ���ѧ��")) == -1)
		return -1;
	else if (num_jc == 0 && num_pp != 0) {
		cout << "���ѧ����all,ƥ��ѧ�ű�����all" << endl;
		return -1;
	}
	if (check_str(argv[3], "Դ����") == -1)
		return -1;
	yz = check_int(argv[4], 60, 80);
	if (check_str(argv[5], "������") == -1)
		return -1;

	cout << "�������ͨ��" << endl;
	cout << "���ѧ�ţ�";
	if (num_jc)
		cout << num_jc << endl;
	else
		cout << "all" << endl;

	cout << "ƥ��ѧ�ţ�";
	if (num_pp)
		cout << num_pp << endl;
	else
		cout << "all" << endl;

	cout << "Դ�ļ�����" << argv[3] << endl;
	cout << "ƥ����ֵ��" << yz << endl;
	cout << "���Ŀ�꣺" << argv[5] << endl;
	return 0;
}
