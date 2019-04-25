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

const char *PARA[] = {
	"-checktitle",
	"-linecount",
	"-lineanalyse",
	NULL
};


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

int rank_arr(char num[13][16], char inf[13][100])
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
	char temp[3][32] = { '\0' };
	sscanf(stu_inf, "%s %s %s", temp[0], temp[1], temp[2]);
	printf("%s-%s-%s : %s : ", stu_num, temp[0], temp[1], file_name);
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
	int i;
	char s[4][32] = { '\0' };
	sscanf(line, "%s%s%s%s", s[0], s[1], s[2], s[3]);
	if (s[1][0] == '\0') {
		printf("������Ϣ��ȫ\n");
		return 0;
	}
	else if (s[3][0] != '\0') {
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

int line_count(FILE *fp) {
	int count = 1;
	char ch;
	while ((ch = fgetc(fp)) != EOF) {
		if (ch == '\n')
			count++;
	}
	fseek(fp, 0, SEEK_SET);
	printf("������-%d", count);
	return count;
}

int line_analyse(FILE *fp) {
	line_count(fp);
	int i, flag = 0;
	int count[3] = { 0 };
	char line[100] = { '\0' };
	while (1) {
		fgets(line, 99, fp);

		int flag_nr = 0;
		//����������
		for (i = 0; line[i] != '\0'; i++)
			if (line[i] != ' ' && line[i] != '\t'&& line[i] != '\n') {
				count[0]++;
				flag_nr = 1;
				break;
			}

		//ע���������
		int flag_zs = 0;
		if (!flag) {	//	flag:ǰ��"/*"
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


		//��Ч�������
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

		if (feof(fp))
			break;
	}
	printf(" ������-%d ��Ч���-%d ע��-%d ����-%.2lf%%\n", count[0], count[1], count[2], (double)count[2] / (count[1] + count[2]) * 100);
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

	char num[13][16] = { '\0' };	//Ĭ��ѧ���15
	char num_inf[13][100] = { '\0' };	//��ѧ�������Ϣ Ĭ��һ�в�����99
	int n_stu = 0, i;
	while (1) {
		fscanf(fin_class_inf, "%s", num[n_stu]);
		fgetc(fin_class_inf);
		fgets(num_inf[n_stu], 99, fin_class_inf);
		if (feof(fin_class_inf))
			break;
		n_stu++;
	}
	fclose(fin_class_inf);

	rank_arr(num, num_inf);
	for (i = 0; i < n_stu; i++) {
		char stu_file[64] = "./source/";
		strcat(stu_file, argv[2]);
		strcat(stu_file, "-");
		strcat(stu_file, num[i]);
		strcat(stu_file, "/");
		FILE* fin_stu_file;
		if (strcmp(argv[3], "all") == 0) {

#if defined _MSC_VER
			struct _finddata_t file;
			int k;
			long HANDLE; //��¼��һ�δ򿪵��ļ�������ر�ʱ���ô�ֵ
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
					print_stu_inf(num[i], num_inf[i], file.name);
					if (i_PARA == 0)	//���м��
						check_first_line(fin_stu_file, num[i], num_inf[i]);
					else if (i_PARA == 1) {	//ͳ������
						line_count(fin_stu_file);
						printf("\n");
					}
					else if (i_PARA == 2)
						line_analyse(fin_stu_file);
					fclose(fin_stu_file);
				}
			}
			_findclose(HANDLE);
			printf("\n");

#elif defined __linux || defined __linux__
			DIR            *dir;
			struct dirent  *node;
			if ((dir = opendir(stu_file)) == NULL)
				continue;
			for (node = readdir(dir); node != NULL; node = readdir(dir))
			{
				if (strcmp(node->d_name, ".") == 0 || strcmp(node->d_name, "..") == 0)
					continue;
				if (node->d_type == DT_DIR)	//���ļ���
					continue;
				char t_stu_file[64];
				if (!strcmp(node->d_name + strlen(node->d_name) - 2, ".c")
					|| !strcmp(node->d_name + strlen(node->d_name) - 4, ".cpp")
					|| !strcmp(node->d_name + strlen(node->d_name) - 2, ".h")) {
					strcpy(t_stu_file, stu_file);
					fin_stu_file = fopen(strcat(t_stu_file, node->d_name), "r");
					if (fin_stu_file == NULL) {
						printf("�ļ�%s��ʧ��\n", t_stu_file);
						continue;
					}
					print_stu_inf(num[i], num_inf[i], node->d_name);
					if (i_PARA == 0)	//���м��
						check_first_line(fin_stu_file, num[i], num_inf[i]);
					else if (i_PARA == 1) {	//ͳ������
						line_count(fin_stu_file);
						printf("\n");
					}
					else if (i_PARA == 2)
						line_analyse(fin_stu_file);
					fclose(fin_stu_file);
				}
			}
			printf("\n");
			closedir(dir);
#endif			

		}
		else {
			fin_stu_file=fopen(strcat(stu_file, argv[3]), "r");
			if (fin_stu_file == NULL) {
				print_stu_inf(num[i], num_inf[i], argv[3]);
				printf(" δ�ύ\n");
			}
			else {
				print_stu_inf(num[i], num_inf[i], argv[3]);
				if (i_PARA == 0)	//���м��
					check_first_line(fin_stu_file, num[i], num_inf[i]);
				else if (i_PARA == 1) {	//ͳ������
					line_count(fin_stu_file);
					printf("\n");
				}
				else if (i_PARA == 2)
					line_analyse(fin_stu_file);
				fclose(fin_stu_file);
			}
		}
	}
	return 0;
}