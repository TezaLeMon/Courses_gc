// 1752762 计1班 魏鹳达
/* 已验证  1851293 姚瑗 / 1853849 范正源 / 1852101 曹乾 / 1852839 李培然 / 1752066 吴子豪 */
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#define LEN_CH_DISPLAY 16	//每行最大显示字符数

int usage(const char* procname)
{
	printf("Usage: %s 16进制debug格式文件名 原始文件名\n", procname);
	return 0;
}

//返回对应值 非法返回-1     #! %x读入即可(未修改) !#
char hex_to_dec(char ch) {
	if (ch >= '0'&&ch <= '9')
		return ch - '0';
	else if (ch >= 'a'&&ch <= 'f')
		return ch - 'a' + 10;
	else if (ch >= 'A'&&ch <= 'F')
		return ch - 'A' + 10;
	return -1;
}

//返回对应值 未检查是否为16进制
char str_to_char(char *ch) {
	char t, sum = 0;
	int i;
	for (i = 0; i < 2; i++) {		//写死 长度两位
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
		printf("文件%s打开失败!\n", argv[1]);
		return -1;
	}
	FILE *fpout;
	fpout = fopen(argv[2], "wb");
	if (fpout==NULL) {
		printf("文件%s打开失败!\n", argv[2]);
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
			printf("最左侧的偏移量0x%08x不是期望值%08x\n", address_file, address);
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
				if (feof(fpin))	//文件末尾/EOF
					break;
				if (i != 2)	//行末字符串         #! 可以通过读取空格的数量来判断 !#
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