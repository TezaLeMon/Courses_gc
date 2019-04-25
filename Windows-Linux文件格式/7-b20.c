// 1752762 ��1�� κ�ٴ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int usage(const char *procname)
{
	printf("Usage: %s\n", procname);
	printf("[-check �ļ���]\n");
	printf("[-convert wtol/ltow Դ�ļ� Ŀ���ļ�]\n");
	return 0;
}

/*	windows��ʽ����1 linux��ʽ����2 �Ƿ�����-1*/
int check(const char* file_name, const int is_prompt)
{
	FILE *fp;
	fp = fopen(file_name, "rb");
	if (fp == NULL) {
		printf("�ļ���ʧ��\n");
		return -1;
	}
	char ch;
	while (1) {
		if ((ch = fgetc(fp)) == '\r') {
			if (is_prompt)
				printf("Windows��ʽ\n");
			fclose(fp);
			return 1;
		}
		else if (feof(fp))
			break;
	}
	fclose(fp);
	if (is_prompt)
		printf("Linux��ʽ\n");
	return 2;
}

int xtox(char *source, const char *smode, char *target, const char *tmode)
{
	FILE *fpin, *fpout;
	fpin = fopen(source, smode);
	if (fpin == NULL) {
		printf("Դ�ļ���ʧ��\n");
		return -1;
	}
	fpout = fopen(target, tmode);
	if (fpout == NULL) {
		printf("Ŀ���ļ���ʧ��\n");
		fclose(fpin);
		return -1;
	}
	char ch;
	while (1) {
		fscanf(fpin, "%c", &ch);
		if (feof(fpin))
			break;
		fprintf(fpout, "%c", ch);
	}
	fclose(fpin);
	fclose(fpout);
	return 0;
}

int convert(char** argv)
{
	if (strcmp(*argv, "wtol") == 0) {
		int t = check(argv[1], 0);
		if (t == -1)
			return -1;
		else if (t != 1) {
			printf("�ļ���ʽ����\n");
			return -1;
		}
		xtox(*(argv + 1), "r", *(argv + 2), "wb");
		return 1;
	}
	else if (strcmp(*argv, "ltow") == 0) {
		int t = check(argv[1], 0);
		if (t == -1)
			return -1;
		else if (t != 2) {
			printf("�ļ���ʽ����\n");
			return -1;
		}
		xtox(*(argv + 1), "rb", *(argv + 2), "w");
		return 2;
	}
	else {
		printf("��������\n");
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
		check(*(argv + 2), 1);
	else if (strcmp(argv[1], "-convert") == 0) {
		if (argc < 5) {
			printf("��������\n");
			return -1;
		}
		convert(argv + 2);
	}
	else {
		printf("��������\n");
		return -1;
	}
	return 0;
}