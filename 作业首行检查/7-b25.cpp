// 1752762 计1班 魏鹳达
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
using namespace std;

#if defined _MSC_VER
#include <io.h>
#elif defined __linux || defined __linux__
#include <sys/types.h>
#include <dirent.h>
#endif

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int usage(const char *procname)
{
	cout << "Usage: " << procname << " [-checktitle] [课号] [源程序文件名]" << endl;
	return 0;
}

void print_stu_inf(const char *stu_num, const char *stu_inf, const char *file_name) {
	istringstream iss_stu_inf(stu_inf);
	cout << stu_num << '-';
	char temp[32];
	iss_stu_inf >> temp;
	cout << temp << " : " << file_name << " : ";
}

int check_first_line(ifstream *first_line, const char *stu_num, const char *stu_inf)
{
	int n_inf = 0;
	char line[100], t;

	do {
		t = first_line->peek();
		if (t == EOF) {
			cout << "未取到首行信息" << endl;
			return 0;
		}
		if (t == ' ' || t == '\t' || t == '\n')
			first_line->get();
		else
			break;
	} while (1);	//读到第一个不是空格/tab/换行的字符
	first_line->get(line, 99, '\n');		//获得作业中首行
	if (!((strstr(line, "//") || (strstr(line, "/*") && strstr(line, "*/"))))) {
		cout << "未取到首行信息" << endl;
		return 0;
	}
	if (strstr(line, "//"))
		strcpy(line, strstr(line, "//") + 2);
	else {
		int i = strstr(line, "*/") - strstr(line, "/*") - 2;
		strncpy(line, strstr(line, "/*") + 2, i);	//处理后首行不含注释符
		line[i] = '\0';
	}
	for (int i = 0, flag = 1; line[i] != '\0'; i++) {
		if (line[i] == ' ' || line[i] == '\t')
			flag = 1;
		else {
			if (flag)
				n_inf++;
			flag = 0;
		}
	}
	if (n_inf < 3) {
		cout << "首行信息不全" << endl;
		return 0;
	}
	else if (n_inf > 3) {
		cout << "首行信息过多" << endl;
		return 0;
	}

	int flag_correct = 1;
	if (!strstr(line, stu_num)) {
		cout << "学号不匹配";
		flag_correct = 0;
	}

	istringstream iss_stu_inf(stu_inf);
	char temp[32];
	iss_stu_inf >> temp;
	if (strstr(line, temp) == NULL) {
		if (!flag_correct)
			cout << "，";
		cout << "姓名不匹配";
		flag_correct = 0;
	}

	iss_stu_inf >> temp;
	if (!strstr(line, temp)) {
		iss_stu_inf >> temp;
		if (!strstr(line, temp)) {
			if (!flag_correct)
				cout << "，";
			cout << "班级不匹配";
			flag_correct = 0;
		}
	}
	if (flag_correct)
		cout << "通过";
	cout << endl;
	return flag_correct;
}

int main(int argc, char** argv)
{
	if (argc < 4) {
		usage(argv[0]);
		return -1;
	}

	if (strcmp(argv[1], "-checktitle") != 0) {
		cout << "参数错误" << argv[1] << endl;
		return -1;
	}

	if (strlen(argv[2]) > 15) {
		cout << "课号" << argv[2] << "过长" << endl;
		return -1;
	}

	if (strlen(argv[3]) > 63) {
		cout << "源文件名" << argv[3] << "过长" << endl;
		return -1;
	}
	else if (!(strcmp(argv[3], "all") == 0 || !strcmp(argv[3] + strlen(argv[3]) - 2, ".c") 
		|| !strcmp(argv[3] + strlen(argv[3]) - 4, ".cpp") || !strcmp(argv[3] + strlen(argv[3]) - 2, ".h"))) {
		cout << "不是源程序文件" << endl;
		return -1;
	}

	ifstream fin_class_inf;
	char t_name[32] = "./source/";
	strcat(t_name, argv[2]);
	strcat(t_name, ".dat");
	fin_class_inf.open(t_name, ios::in);
	if (!fin_class_inf.is_open()) {
		cout << "学生名单打开失败" << endl;
		return -1;
	}

	while (1) {
		char stu_num[16];	//默认学号最长15
		char stu_inf[100];	//除学号外的信息 默认一行不超过99
		fin_class_inf.getline(stu_num, 15, '\t');
		fin_class_inf.getline(stu_inf, 99, '\n');
		if (fin_class_inf.eof())
			break;


		char stu_file[64] = "./source/";
		strcat(stu_file, argv[2]);
		strcat(stu_file, "-");
		strcat(stu_file, stu_num);
		strcat(stu_file, "/");
		ifstream fin_stu_file;
		
		if (strcmp(argv[3], "all") == 0) {

#if defined _MSC_VER
			struct _finddata_t file;
			int k;
			long HANDLE; //记录第一次打开的文件句柄，关闭时需用此值
			char t[64];
			strcpy(t, stu_file);
			k = HANDLE = _findfirst(strcat(t, "*.*"), &file);
			for (; k != -1; k = _findnext(HANDLE, &file))
			{
				if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
					continue;
				if (file.attrib&_A_SUBDIR)	//是文件夹
					continue;
				char t_stu_file[64];
				strcpy(t_stu_file, stu_file);
				//if (strstr(file.name, ".c") || strstr(file.name, ".cpp") || strstr(file.name, ".h")) {
				//	fin_stu_file.open(strcat(t_stu_file, file.name), ios::in);
				if (!strcmp(file.name + strlen(file.name) - 2, ".c")
					|| !strcmp(file.name + strlen(file.name) - 4, ".cpp")
					|| !strcmp(file.name + strlen(file.name) - 2, ".h")) {
					fin_stu_file.open(strcat(t_stu_file, file.name), ios::in);
					if (!fin_stu_file.is_open()) {
						cout << "文件" << t_stu_file << "打开失败" << endl;
						continue;
					}
					print_stu_inf(stu_num, stu_inf, file.name);
					check_first_line(&fin_stu_file, stu_num, stu_inf);
					fin_stu_file.close();
				}
			}
			_findclose(HANDLE);
			cout << endl;

#elif defined __linux || defined __linux__
			DIR            *dir;
			struct dirent  *node;
			if ((dir = opendir(stu_file)) == NULL)
				return -1;
			for (node = readdir(dir); node != NULL; node = readdir(dir))
			{
				if (strcmp(node->d_name, ".") == 0 || strcmp(node->d_name, "..") == 0)
					continue;
				if (node->d_type != DT_REG)	//不是常规文件
					continue;
				char t_stu_file[64];
				strcpy(t_stu_file, stu_file);
				if (!strcmp(node->d_name + strlen(node->d_name) - 2, ".c")
					|| !strcmp(node->d_name + strlen(node->d_name) - 4, ".cpp")
					|| !strcmp(node->d_name + strlen(node->d_name) - 2, ".h")) {
					fin_stu_file.open(strcat(t_stu_file, node->d_name), ios::in);
					if (!fin_stu_file.is_open()) {
						cout << "文件" << t_stu_file << "打开失败" << endl;
						continue;
					}
					print_stu_inf(stu_num, stu_inf, node->d_name);
					check_first_line(&fin_stu_file, stu_num, stu_inf);
					fin_stu_file.close();
				}
			}
			cout << endl;
			closedir(dir);
#endif			

		}
		else {
			fin_stu_file.open(strcat(stu_file, argv[3]), ios::in);
			if (!fin_stu_file.is_open()) {
				cout << stu_num << ' ' << argv[3] << " 未提交" << endl;
			}
			else {
				cout << stu_num << ' ' << argv[3] << ' ';
				check_first_line(&fin_stu_file, stu_num, stu_inf);
				fin_stu_file.close();
			}
		}
	}


	fin_class_inf.close();
	return 0;
}