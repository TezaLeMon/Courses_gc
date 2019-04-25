// 1752762 ��1�� κ�ٴ�
/* ����֤  1851293 Ҧ� / 1853849 ����Դ / 1852101 ��Ǭ / 1852839 ����Ȼ / 1752066 ���Ӻ� */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define LEN_CH_DISPLAY 16	//ÿ�������ʾ�ַ���

int usage(const char* procname)
{
	printf("Usage: %s 16����debug��ʽ�ļ��� ԭʼ�ļ���\n", procname);
	return 0;
}

//���ض�Ӧֵ �Ƿ�����-1     #! %x���뼴��(δ�޸�) !#
char hex_to_dec(char ch) {
	if (ch >= '0'&&ch <= '9')
		return ch - '0';
	else if (ch >= 'a'&&ch <= 'f')
		return ch - 'a' + 10;
	else if (ch >= 'A'&&ch <= 'F')
		return ch - 'A' + 10;
	return -1;
}

//���ض�Ӧֵ δ����Ƿ�Ϊ16����
char str_to_char(char *ch) {
	char t, sum = 0;
	int i;
	for (i = 0; i < 2; i++) {		//д�� ������λ
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

	FILE *fpin;
	fpin=fopen(argv[1], "r");
	if (fpin == NULL) {
		printf("�ļ�%s��ʧ��!\n", argv[1]);
		return -1;
	}
	FILE *fpout;
	fpout = fopen(argv[2], "wb");
	if (fpout==NULL) {
		printf("�ļ�%s��ʧ��!\n", argv[2]);
		fclose(fpin);
		return -1;
	}

	int address = 0;
	int address_file;
	char ch[LEN_CH_DISPLAY + 1] = { '\0' };
	int i;
	while (!feof(fpin)) {
		fscanf(fpin, "%x", &address_file);
		if (feof(fpin))
			break;
		if (address != address_file) {
			printf("������ƫ����0x%08x��������ֵ%08x\n", address_file, address);
			fclose(fpin);
			fclose(fpout);
			return -1;
		}
		address += 16;
		i = 0;
		while (1) {
			fscanf(fpin, "%s", ch);
			if (strcmp(ch, "-") == 0)
				continue;
			else if (strlen(ch) == i) {
				if (feof(fpin))	//�ļ�ĩβ/EOF
					break;
				if (i != 2)	//��ĩ�ַ���         #! ����ͨ����ȡ�ո���������ж� !#
					break;
			}
			fputc(str_to_char(ch),fpout);
			i++;
			if (i > 16)
				break;
		}
	}
	fclose(fpin);
	fclose(fpout);
	return 0;
}