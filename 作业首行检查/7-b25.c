// 1752762 计1班 魏鹳达
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

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
	printf("Usage: %s [-checktitle] [课号] [源程序文件名]\n", procname);
	return 0;
}

void print_stu_inf(const char *stu_num, const char *stu_inf, const char *file_name) {
	char temp[32] = { '\0' };
	int i;
	for (i = 0; stu_inf[i] != '\t'&&stu_inf[i] != '\0'; i++)
		temp[i] = stu_inf[i];
	printf("%s-%s : %s : ", stu_num, temp, file_name);
}

int check_first_line(FILE *first_line, const char *stu_num, const char *stu_inf)
{
	int n_inf = 0;
	char line[100], t;
	do {
		t = fgetc(first_line);
		if (t == EOF) {
			printf("未取到首行信息\n");
			return 0;
		}
		if (t == ' ' || t == '\t' || t == '\n')
			continue;
		break;
	} while (1);	//读到第一个不是空格/tab/换行的字符
	ungetc(t, first_line);
	fgets(line, 99, first_line);		//获得作业中首行
	if (!((strstr(line, "//") || (strstr(line, "/*") && strstr(line, "*/"))))) {
		printf("未取到首行信息\n");
		return 0;
	}
	if (strstr(line, "//"))
		strcpy(line, strstr(line, "//") + 2);
	else {
		int i = strstr(line, "*/") - strstr(line, "/*") - 2;
		strncpy(line, strstr(line, "/*") + 2, i);	//处理后首行不含注释符
		line[i] = '\0';
	}
	int i, flag;
	for (i = 0, flag = 1; line[i] != '\0'; i++) {
		if (line[i] == ' ' || line[i] == '\t')
			flag = 1;
		else {
			if (flag)
				n_inf++;
			flag = 0;
		}
	}
	if (n_inf < 3) {
		printf("首行信息不全\n");
		return 0;
	}
	else if (n_inf > 3) {
		printf("首行信息过多\n");
		return 0;
	}

	int flag_correct = 1;
	if (!strstr(line, stu_num)) {
		printf("学号不匹配");
		flag_correct = 0;
	}

	char temp[32];
	for (i = 0; stu_inf[i] != '\t'&&stu_inf[i] != '\0'; i++)
		temp[i] = stu_inf[i];
	temp[i] = stu_inf[i];
	i++;
	if (strstr(line, temp) == NULL) {
		if (!flag_correct)
			printf("，");
		printf("姓名不匹配");
		flag_correct = 0;
	}

	for (i = 0; stu_inf[i] != '\t'&&stu_inf[i] != '\0'; i++)
		temp[i] = stu_inf[i];
	temp[i] = stu_inf[i];

	if (!strstr(line, temp)) {
		i++;
		for (i = 0; stu_inf[i] != '\t'&&stu_inf[i] != '\0'; i++)
			temp[i] = stu_inf[i];
		temp[i] = stu_inf[i];

		if (!strstr(line, temp)) {
			if (!flag_correct)
				printf("，");
			printf("班级不匹配");
			flag_correct = 0;
		}
	}
	if (flag_correct)
		printf("通过");
	printf("\n");
	return flag_correct;
}

int main(int argc, char** argv)
{
	if (argc < 4) {
		usage(argv[0]);
		return -1;
	}

	if (strcmp(argv[1], "-checktitle") != 0) {
		printf("参数错误%s\n", argv[1]);
		return -1;
	}

	if (strlen(argv[2]) > 15) {
		printf("课号%s过长\n", argv[2]);
		return -1;
	}

	if (strlen(argv[3]) > 63) {
		printf("源文件名%s过长\n", argv[3]);
		return -1;
	}
	else if (!(strcmp(argv[3], "all") == 0 || !strcmp(argv[3] + strlen(argv[3]) - 2, ".c")
		|| !strcmp(argv[3] + strlen(argv[3]) - 4, ".cpp") || !strcmp(argv[3] + strlen(argv[3]) - 2, ".h"))) {
		printf("不是源程序文件\n");
		return -1;
	}

	FILE *fin_class_inf;
	char t_name[32] = "./source/";
	strcat(t_name, argv[2]);
	strcat(t_name, ".dat");
	fin_class_inf = fopen(t_name, "r");
	if (fin_class_inf == NULL) {
		printf("学生名单打开失败\n");
		return -1;
	}

	while (1) {
		char stu_num[16];	//默认学号最长15
		char stu_inf[100];	//除学号外的信息 默认一行不超过99
		fscanf(fin_class_inf, "%s", stu_num);
		fgetc(fin_class_inf);
		fgets(stu_inf, 99, fin_class_inf);
		if (feof(fin_class_inf))
			break;

		char stu_file[64] = "./source/";
		strcat(stu_file, argv[2]);
		strcat(stu_file, "-");
		strcat(stu_file, stu_num);
		strcat(stu_file, "/");
		FILE *fin_stu_file;

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
					fin_stu_file = fopen(strcat(t_stu_file, file.name), "r");
					if (fin_stu_file == NULL) {
						printf("文件%s打开失败\n", t_stu_file);
						continue;
					}
					print_stu_inf(stu_num, stu_inf, file.name);
					check_first_line(fin_stu_file, stu_num, stu_inf);
					fclose(fin_stu_file);
				}
			}
			_findclose(HANDLE);
			printf("\n");

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
					fin_stu_file = fopen(strcat(t_stu_file, node->d_name), "r");
					if (fin_stu_file == NULL) {
						printf("文件%s打开失败\n", t_stu_file);
						continue;
					}
					print_stu_inf(stu_num, stu_inf, node->d_name);
					check_first_line(fin_stu_file, stu_num, stu_inf);
					fclose(fin_stu_file);
				}
			}
			printf("\n");
			closedir(dir);
#endif			

		}
		else {
			fin_stu_file = fopen(strcat(stu_file, argv[3]), "r");
			if (fin_stu_file == NULL) {
				printf("%s %s 未提交\n", stu_num, argv[3]);
			}
			else {
				printf("%s %s ", stu_num, argv[3]);
				check_first_line(fin_stu_file, stu_num, stu_inf);
				fclose(fin_stu_file);
			}
		}
	}

	fclose(fin_class_inf);
	return 0;
}