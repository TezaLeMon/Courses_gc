// 1752762 计x班 魏鹳达
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int x;

	while (1) {
		printf("请输入x的值(0-100)：");
		if (scanf("%d", &x) == 0)	//读入x的方式必须如此，不准用非scanf
		{
			int ch;
			while (((ch = getchar()) != EOF) && ch != '\n');
		}
		else if (x >= 0 && x <= 100)
			break;
	}

	printf("x=%d\n", x);

	return 0;
}