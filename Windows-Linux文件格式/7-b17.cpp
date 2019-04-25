// 1752762 计1班 魏鹳达
/* 已验证 1853849 范正源 / 1852101 曹乾 / 1851977 李家麟 / 1851909 聂尧 / 1752919 祁好雨 / 1851981 杨逸佳 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <fstream>
#include <iomanip>
using namespace std;
#define LEN_CH_DISPLAY 16	//每行最大显示字符数

int usage(const char* procname)
{
	cout << "Usage: " << procname << " 16进制debug格式文件名 原始文件名" << endl;
	return 0;
}

/*	地址所对应字符串每次增16	*/
void address_change(char* address)
{
	//未考虑超出范围的情况
	int i;	//等待加1
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

//返回对应值 非法返回-1
char hex_to_dec(char ch) {
	if (ch >= '0'&&ch <= '9')
		return ch - '0';
	else if (ch >= 'a'&&ch <= 'f')
		return ch - 'a' + 10;
	return -1;
}

//返回对应值 未检查是否为16进制
char str_to_char(char *ch) {
	char t, sum = 0;
	int i;
	for (i = 0; i < 2; i++) {		//写死 长度两位
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
		cout << "文件" << argv[1] << "打开失败!" << endl;
		return -1;
	}
	ofstream fout;
	fout.open(argv[2], ios::out | ios::binary);
	if (!fout.is_open()) {
		cout << "文件" << argv[2] << "打开失败!" << endl;
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
			cout << "最左侧的偏移量0x" << address_file << "不是期望值" << address << endl;
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
				if (fin.eof())	//文件末尾/EOF
					break;
				if (i != 2)	//行末字符串
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