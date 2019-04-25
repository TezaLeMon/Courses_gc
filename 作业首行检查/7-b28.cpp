// 1752762 计1班 魏鹳达
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <sstream>
#include <fstream>
#include <iomanip>
using namespace std;

#if defined _MSC_VER
#include <io.h>
#elif defined __linux || defined __linux__
#include <sys/types.h>
#include <dirent.h>
#endif

const char *PARA[] = {
	"-checktitle",
	"-linecount",
	"-lineanalyse",
	NULL
};


int usage(const char *procname)
{
	cout << "Usage: " << procname << " [-checktitle] [课号] [源程序文件名]" << endl;
	return 0;
}

int rank_arr(char num[13][16],char inf[13][100])
{
	int i, j;
	for (i = 0; *num[i + 1] != '\0'; i++)
		for (j = 0; *num[j + i + 1] != '\0'; j++)
			if (strcmp(num[j], num[j + 1]) > 0) {
				char t1[16];
				char t2[100];
				strcpy(t1, num[j]);
				strcpy(num[j], num[j + 1]);
				strcpy(num[j + 1], t1);

				strcpy(t2, inf[j]);
				strcpy(inf[j], inf[j + 1]);
				strcpy(inf[j + 1], t2);
			}
	return 0;
}

void print_stu_inf(const char *stu_num, const char *stu_inf, const char *file_name) {
	istringstream iss_stu_inf(stu_inf);
	cout << stu_num << '-';
	char temp[32];
	iss_stu_inf >> temp;
	cout << temp << '-';
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
	char s[4][32] = { '\0' };
	sscanf(line, "%s%s%s%s", s[0], s[1], s[2], s[3]);
	if (s[1][0] == '\0') {
		cout << "首行信息不全" << endl;
		return 0;
	}
	else if (s[3][0] != '\0') {
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

int line_count(ifstream *fin) {
	int count = 1;
	char ch;
	while ((ch = fin->get()) != EOF) {
		if (ch == '\n') {
			if (char(fin->peek() != EOF))
				count++;
		}
	}
	fin->clear();
	fin->seekg(ios::beg);
	cout << "总行数-" << count;
	return count;
}

int line_analyse(ifstream *fin) {
	int line_total = line_count(fin);
	int i, flag = 0;
	int count[3] = { 0 };
	char line[256] = { '\0' };
	while (line_total--) {
		fin->getline(line, 255, '\n');

		int flag_nr = 0;
		//有内容行数
		for (i = 0; line[i] != '\0'; i++)
			if (line[i] != ' ' && line[i] != '\t'&& line[i] != '\n') {
				count[0]++;
				flag_nr = 1;
				break;
			}

		//注释语句行数
		int flag_zs = 0;
		if (!flag) {	//	flag:前有"/*"
			for (i = 0; line[i] != '\0'; i++)
				if (line[i] == '/') {
					if (line[i + 1] == '/') {
						count[2]++;
						flag_zs = 1;
						break;
					}
					else if (line[i + 1] == '*') {
						flag_zs = 1;
						flag = 1;
					}
					else if (i&&line[i - 1] == '*') {
						flag_zs = 1;
						flag = 0;
						count[2]++;
						break;
					}
				}
		}
		if (flag) {
			flag_zs = 1;
			count[2]++;
			if (strstr(line, "*/"))
				flag = 0;
		}


		//有效语句行数
		int flag_yx = 0;
		if (flag_zs) {
			if (strstr(line, "//") || strstr(line, "/*")) {
				int to = 100;
				if (strstr(line, "//"))
					to = strstr(line, "//") - line;
				if (strstr(line, "/*"))
					to = to < (strstr(line, "/*") - line) ? to : (strstr(line, "/*") - line);
				for (i = 0; i < to; i++)
					if (line[i] != '\0'&&line[i] != '\t'&&line[i] != ' ') {
						count[1]++;
						flag_yx = 1;
						break;
					}
			}
			if (!flag_yx&&strstr(line, "*/")) {
				char *ch;
				for (ch = strstr(line, "*/") + 2; *ch != '\0'; ch++)
					if (*ch != '\0'&&*ch != '\t'&&*ch != ' ') {
						count[1]++;
						break;
					}
			}
		}
		else
			count[1]++;

		if (fin->eof())
			break;
	}
	cout << " 有内容-" << count[0] << " 有效语句-" << count[1] << " 注释-" << count[2] << " 比例-"
		<< setiosflags(ios::fixed) << setprecision(2) << (double)count[2] / (count[1] + count[2]) * 100 << "%" << endl;
	return 0;
}

int main(int argc, char** argv)
{
	if (argc < 4) {
		usage(argv[0]);
		return -1;
	}

	int i_PARA;
	for (i_PARA = 0; PARA[i_PARA] != NULL; i_PARA++)
		if (strcmp(argv[1], PARA[i_PARA]) == 0)
			break;
	if (PARA[i_PARA] == NULL) {
		usage(argv[0]);
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

	char num[13][16] = { '\0' };	//默认学号最长15
	char num_inf[13][100] = { '\0' };	//除学号外的信息 默认一行不超过99
	int n_stu = 0, i;
	while (1) {
		fin_class_inf.getline(num[n_stu], 15, '\t');
		fin_class_inf.getline(num_inf[n_stu], 99, '\n');
		if (fin_class_inf.eof())
			break;
		n_stu++;
	}
	fin_class_inf.close();
	rank_arr(num, num_inf);
	for (i = 0; i < n_stu; i++) {
		char stu_file[64] = "./source/";
		strcat(stu_file, argv[2]);
		strcat(stu_file, "-");
		strcat(stu_file, num[i]);
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
			if (k == -1) {
				_findclose(HANDLE);
				continue;
			}
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
					print_stu_inf(num[i], num_inf[i], file.name);
					if (i_PARA == 0)	//首行检查
						check_first_line(&fin_stu_file, num[i], num_inf[i]);
					else if (i_PARA == 1) {	//统计行数
						line_count(&fin_stu_file);
						cout << endl;
					}
					else if (i_PARA == 2)
						line_analyse(&fin_stu_file);
				}
				fin_stu_file.close();
			}
			_findclose(HANDLE);
			cout << endl;

#elif defined __linux || defined __linux__
			DIR            *dir;
			struct dirent  *node;
			if ((dir = opendir(stu_file)) == NULL) {
				closedir(dir);
				continue;
			}
			for (node = readdir(dir); node != NULL; node = readdir(dir))
			{
				if (strcmp(node->d_name, ".") == 0 || strcmp(node->d_name, "..") == 0)
					continue;
				if (node->d_type == DT_DIR)	//是文件夹
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
					print_stu_inf(num[i], num_inf[i], node->d_name);
					if (i_PARA == 0)	//首行检查
						check_first_line(&fin_stu_file, num[i], num_inf[i]);
					else if (i_PARA == 1) {	//统计行数
						line_count(&fin_stu_file);
						cout << endl;
					}
					else if (i_PARA == 2)
						line_analyse(&fin_stu_file);
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
				print_stu_inf(num[i], num_inf[i], argv[3]);
				cout << " 未提交" << endl;
			}
			else {
				print_stu_inf(num[i], num_inf[i], argv[3]);
				if (i_PARA == 0)	//首行检查
					check_first_line(&fin_stu_file, num[i], num_inf[i]);
				else if (i_PARA == 1) {	//统计行数
					line_count(&fin_stu_file);
					cout << endl;
				}
				else if (i_PARA == 2)
					line_analyse(&fin_stu_file);
				fin_stu_file.close();
			}
		}
	}
	return 0;
}