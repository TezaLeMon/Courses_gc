// 1752762 ��1�� κ�ٴ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define MAX_LEN_FILENAME 32	//����ļ�������
#define LEN_CH_DISPLAY 16	//ÿ�������ʾ�ַ���

int usage()
{
	printf("�ļ���������ʽ�����ԣ�\n");
	printf("a.txt������·����ʽ\n");
	printf("..\\data\\b.dat�����·����ʽ\n");
	printf("C:\\Windows\\System32\\c.dat���������·����ʽ\n");
	printf("�������ļ���: ");
	return 0;
}

int main(int argc, char** argv)
{
	char file_name[MAX_LEN_FILENAME + 1];
	if (argc == 1) {
		usage();
		scanf("%s", file_name);
	}
	else
		strcpy(file_name, argv[1]);
	
	FILE *fpin;
	fpin = fopen(file_name, "rb");
	if (fpin == NULL) {
		printf("�ļ�%s��ʧ��!\n", file_name);
		return -1;
	}

	int i = 0, j, flag1 = 1, flag2 = 1;
	char ch[LEN_CH_DISPLAY + 1] = { '\0' };
	while (flag2) {
		if (flag1)
			ch[i%LEN_CH_DISPLAY] = fgetc(fpin);
		if (feof(fpin)) {
			flag1 = 0;
			ch[i%LEN_CH_DISPLAY] = '\0';
		}

		if (!(i%LEN_CH_DISPLAY))
			printf("%08x  ", i);	//ÿ�����ַ���ַ
		else if (i%LEN_CH_DISPLAY % 8 == 0) {
			if (flag1)
				printf("- ");
			else
				printf("  ");
		}
		if (flag1)
			printf("%02x ", ch[i%LEN_CH_DISPLAY] & 0xff);	//ÿ�����ַ���ַ
		else
			printf("   ");

		if (flag1 && (ch[i%LEN_CH_DISPLAY] < 33 || ch[i%LEN_CH_DISPLAY] > 126))
			ch[i%LEN_CH_DISPLAY] = '.';

		if (i%LEN_CH_DISPLAY == LEN_CH_DISPLAY - 1) {
			printf("    ");
			for (j = 0; j < LEN_CH_DISPLAY; j++) {
				if (ch[j] != '\0')
					printf("%c", ch[j]);
				ch[j] = '\0';
			}
			printf("\n");
			if (!flag1)
				flag2 = 0;
		}
		i++;
	}
	fclose(fpin);
	return 0;
}