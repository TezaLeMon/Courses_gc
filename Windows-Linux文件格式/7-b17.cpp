// 1752762 ��1�� κ�ٴ�
/* ����֤ 1853849 ����Դ / 1852101 ��Ǭ / 1851977 ����� / 1851909 ��Ң / 1752919 ����� / 1851981 ���ݼ� */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
using namespace std;
#define LEN_CH_DISPLAY 16	//ÿ�������ʾ�ַ���

int usage(const char* procname)
{
	cout << "Usage: " << procname << " 16����debug��ʽ�ļ��� ԭʼ�ļ���" << endl;
	return 0;
}

/*	��ַ����Ӧ�ַ���ÿ����16	*/
void address_change(char* address)
{
	//δ���ǳ�����Χ�����
	int i;	//�ȴ���1
	for (i = 6; i >= 0; i--) {
		if (address[i] == '9') {
			address[i] = 'a';
			break;
		}
		else if (address[i] == 'f') {
			address[i] = '0';
			continue;
		}
		else
			address[i]++;
		break;
	}
}

//���ض�Ӧֵ �Ƿ�����-1
char hex_to_dec(char ch) {
	if (ch >= '0'&&ch <= '9')
		return ch - '0';
	else if (ch >= 'a'&&ch <= 'f')
		return ch - 'a' + 10;
	return -1;
}

//���ض�Ӧֵ δ����Ƿ�Ϊ16����
char str_to_char(char *ch) {
	char t, sum = 0;
	int i;
	for (i = 0; i < 2; i++) {		//д�� ������λ
		t = hex_to_dec(ch[i]);
		if (t == -1)
			break;
		sum = sum * 16 + t;
	}
	return sum;
}

int main(int argc, char** argv)
{
	if (argc < 3)
		usage(argv[0]);

	ifstream fin;
	fin.open(argv[1], ios::in);
	if (!fin.is_open()) {
		cout << "�ļ�" << argv[1] << "��ʧ��!" << endl;
		return -1;
	}
	ofstream fout;
	fout.open(argv[2], ios::out | ios::binary);
	if (!fout.is_open()) {
		cout << "�ļ�" << argv[2] << "��ʧ��!" << endl;
		fin.close();
		return -1;
	}

	char address[9] = { "00000000" };
	char address_file[9];
	char ch[LEN_CH_DISPLAY + 1] = { '\0' };
	int i;
	while (!fin.eof()) {
		fin >> address_file;
		if (fin.eof())
			break;
		if (strcmp(address, address_file) != 0) {
			cout << "������ƫ����0x" << address_file << "��������ֵ" << address << endl;
			fin.close();
			fout.close();
			return -1;
		}
		address_change(address);
		i = 0;
		while(1) {
			fin >> ch;
			if (strcmp(ch, "-") == 0)
				continue;
			else if (strlen(ch) == i) {
				if (fin.eof())	//�ļ�ĩβ/EOF
					break;
				if (i != 2)	//��ĩ�ַ���
					break;
			}
			fout.put(str_to_char(ch));
			i++;
			if (i > 16)
				break;
		}
	}
	fin.close();
	fout.close();
	return 0;
}