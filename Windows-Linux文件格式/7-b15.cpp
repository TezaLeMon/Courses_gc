// 1752762 计1班 魏鹳达
#include <iostream>
#include <string.h>
#include <fstream>
using namespace std;

int usage(const char *procname)
{
	cout << "Usage: " << procname << endl;
	cout << "[-check 文件名]" << endl;
	cout << "[-convert wtol/ltow 源文件 目标文件]" << endl;
	return 0;
}

/*	windows格式返回1 linux格式返回2 非法返回-1*/
int check(const char* file_name, const int is_prompt = 1)
{
	ifstream fin;
	fin.open(file_name, ios::in | ios::binary);
	if (!fin.is_open()) {
		cout << "文件打开失败" << endl;
		return -1;
	}
	char ch;
	while (1) {
		if ((ch = fin.get()) == '\r') {
			if (is_prompt)
				cout << "Windows格式" << endl;
			fin.close();
			return 1;
		}
		else if (fin.eof())
			break;
	}
	fin.close();
	if(is_prompt)
		cout << "Linux格式" << endl;
	return 2;
}

int xtox(char *source, ios_base::openmode smode, char *target, ios_base::openmode tmode)  
{
	ifstream fin;
	ofstream fout;
	fin.open(source, smode);
	if (!fin.is_open()) {
		cout << "源文件打开失败" << endl;
		return -1;
	}
	fout.open(target, tmode);
	if(!fout.is_open()){
		cout << "目标文件打开失败" << endl;
		fin.close();
		return -1;
	}
	char ch;
	while (1) {
		ch = fin.get();
		if (fin.eof())
			break;
		fout.put(ch);
	}
	fin.close();
	fout.close();
	return 0;
}

int convert(char** argv)
{
	if (strcmp(*argv, "wtol") == 0) {
		int t = check(argv[1], 0);
		if (t == -1)
			return -1;
		else if (t != 1) {
			cout << "文件格式错误" << endl;
			return -1;
		}
		xtox(*(argv + 1), ios::in, *(argv + 2), ios::out | ios::binary);
		return 1;
	}
	else if (strcmp(*argv, "ltow") == 0) {
		int t = check(argv[1], 0);
		if (t == -1)
			return -1;
		else if (t != 2) {
			cout << "文件格式错误" << endl;
			return -1;
		}
		xtox(*(argv + 1), ios::in | ios::binary, *(argv + 2), ios::out);
		return 2;
	}
	else {
		cout << "参数有误" << endl;
		return -1;
	}
	return 0;
}

int main(int argc, char** argv)
{
	if (argc <= 2) {
		usage(argv[0]);
		return -1;
	}
	if (strcmp(argv[1], "-check") == 0)
		check(*(argv + 2));
	else if (strcmp(argv[1], "-convert") == 0) {
		if (argc < 5) {
			cout << "参数有误" << endl;
			return -1;
		}
		convert(argv + 2);
	}
	else {
		cout << "参数有误" << endl;
		return -1;
	}
	return 0;
}
