// 1752762 ��x�� κ�ٴ�
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main()
{
	int x;

	while (1) {
		printf("������x��ֵ(0-100)��");
		if (scanf("%d", &x) == 0)	//����x�ķ�ʽ������ˣ���׼�÷�scanf
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