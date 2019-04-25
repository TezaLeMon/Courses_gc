// 1752762 计1班 魏鹳达
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>

int usage(const char *procname)
{
	printf("Usage: %s\n", procname);
	printf("[-check 文件名]\n");
	printf("[-convert wtol/ltow 源文件 目标文件]\n");
	return 0;
}

/*	windows格式返回1 linux格式返回2 非法返回-1*/
int check(const char* file_name, const int is_prompt)
{
	FILE *fp;
	fp = fopen(file_name, "rb");
	if (fp == NULL) {
		printf("文件打开失败\n");
		return -1;
	}
	char ch;
	while (1) {
		if ((ch = fgetc(fp)) == '\r') {
			if (is_prompt)
				printf("Windows格式\n");
			fclose(fp);
			return 1;
		}
		else if (feof(fp))
			break;
	}
	fclose(fp);
	if (is_prompt)
		printf("Linux格式\n");
	return 2;
}

int xtox(char *source, const char *smode, char *target, const char *tmode)
{
	FILE *fpin, *fpout;
	fpin = fopen(source, smode);
	if (fpin == NULL) {
		printf("源文件打开失败\n");
		return -1;
	}
	fpout = fopen(target, tmode);
	if (fpout == NULL) {
		printf("目标文件打开失败\n");
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
			printf("文件格式错误\n");
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
			printf("文件格式错误\n");
			return -1;
		}
		xtox(*(argv + 1), "rb", *(argv + 2), "w");
		return 2;
	}
	else {
		printf("参数有误\n");
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
			printf("参数有误\n");
			return -1;
		}
		convert(argv + 2);
	}
	else {
		printf("参数有误\n");
		return -1;
	}
	return 0;
}