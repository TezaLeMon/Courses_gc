// 1752762 ��1�� κ�ٴ�
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
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int usage(const char *procname)
{
	printf("Usage: %s [-checktitle] [�κ�] [Դ�����ļ���]\n", procname);
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
			printf("δȡ��������Ϣ\n");
			return 0;
		}
		if (t == ' ' || t == '\t' || t == '\n')
			continue;
		break;
	} while (1);	//������һ�����ǿո�/tab/���е��ַ�
	ungetc(t, first_line);
	fgets(line, 99, first_line);		//�����ҵ������
	if (!((strstr(line, "//") || (strstr(line, "/*") && strstr(line, "*/"))))) {
		printf("δȡ��������Ϣ\n");
		return 0;
	}
	if (strstr(line, "//"))
		strcpy(line, strstr(line, "//") + 2);
	else {
		int i = strstr(line, "*/") - strstr(line, "/*") - 2;
		strncpy(line, strstr(line, "/*") + 2, i);	//��������в���ע�ͷ�
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
		printf("������Ϣ��ȫ\n");
		return 0;
	}
	else if (n_inf > 3) {
		printf("������Ϣ����\n");
		return 0;
	}

	int flag_correct = 1;
	if (!strstr(line, stu_num)) {
		printf("ѧ�Ų�ƥ��");
		flag_correct = 0;
	}

	char temp[32];
	for (i = 0; stu_inf[i] != '\t'&&stu_inf[i] != '\0'; i++)
		temp[i] = stu_inf[i];
	temp[i] = stu_inf[i];
	i++;
	if (strstr(line, temp) == NULL) {
		if (!flag_correct)
			printf("��");
		printf("������ƥ��");
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
				printf("��");
			printf("�༶��ƥ��");
			flag_correct = 0;
		}
	}
	if (flag_correct)
		printf("ͨ��");
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
		printf("��������%s\n", argv[1]);
		return -1;
	}

	if (strlen(argv[2]) > 15) {
		printf("�κ�%s����\n", argv[2]);
		return -1;
	}

	if (strlen(argv[3]) > 63) {
		printf("Դ�ļ���%s����\n", argv[3]);
		return -1;
	}
	else if (!(strcmp(argv[3], "all") == 0 || !strcmp(argv[3] + strlen(argv[3]) - 2, ".c")
		|| !strcmp(argv[3] + strlen(argv[3]) - 4, ".cpp") || !strcmp(argv[3] + strlen(argv[3]) - 2, ".h"))) {
		printf("����Դ�����ļ�\n");
		return -1;
	}

	FILE *fin_class_inf;
	char t_name[32] = "./source/";
	strcat(t_name, argv[2]);
	strcat(t_name, ".dat");
	fin_class_inf = fopen(t_name, "r");
	if (fin_class_inf == NULL) {
		printf("ѧ��������ʧ��\n");
		return -1;
	}

	while (1) {
		char stu_num[16];	//Ĭ��ѧ���15
		char stu_inf[100];	//��ѧ�������Ϣ Ĭ��һ�в�����99
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
			long HANDLE; //��¼��һ�δ򿪵��ļ�������ر�ʱ���ô�ֵ
			char t[64];
			strcpy(t, stu_file);
			k = HANDLE = _findfirst(strcat(t, "*.*"), &file);
			for (; k != -1; k = _findnext(HANDLE, &file))
			{
				if (strcmp(file.name, ".") == 0 || strcmp(file.name, "..") == 0)
					continue;
				if (file.attrib&_A_SUBDIR)	//���ļ���
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
						printf("�ļ�%s��ʧ��\n", t_stu_file);
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
				if (node->d_type != DT_REG)	//���ǳ����ļ�
					continue;
				char t_stu_file[64];
				strcpy(t_stu_file, stu_file);
				if (!strcmp(node->d_name + strlen(node->d_name) - 2, ".c")
					|| !strcmp(node->d_name + strlen(node->d_name) - 4, ".cpp")
					|| !strcmp(node->d_name + strlen(node->d_name) - 2, ".h")) {
					fin_stu_file = fopen(strcat(t_stu_file, node->d_name), "r");
					if (fin_stu_file == NULL) {
						printf("�ļ�%s��ʧ��\n", t_stu_file);
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
				printf("%s %s δ�ύ\n", stu_num, argv[3]);
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