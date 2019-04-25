// 1752762 ��1�� κ�ٴ�
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

#define N_PARA 4
const char para_1[] = "ln ";	//�����һֵ����
const char para_0[] = "  t";	//�����ֵ����
const int para_min[] = { 64,1 };	//��Ӧ������Сֵ
const int para_max[] = { 64000,10000 };	//��Ӧ�������ֵ

/***************************************************************************
  �������ƣ�
  ��    �ܣ�
  ���������
  �� �� ֵ��
  ˵    ����
***************************************************************************/
int usage(const char *procname)
{
	cout << "Usage: " << procname << " [-l ��С] [-n ����] [-t] IP��ַ" << endl;
	return 0;
}

//�Ƿ�����0 �Ϸ�����ip����argv�±�
int check_ip(char **argv) {
	int i = 0, n_dot = 0, sum = 0;
	while (argv[i + 1] != NULL)
		i++;
	char *p;
	for (p = argv[i]; *p; p++) {
		if (*p == '.') {
			if (p == argv[i] || *(p + 1) == '.' || *(p + 1) == '\0')	//�ַ���Ϊ.��ͷ ����������. ��.��β
				return 0;
			if (sum < 0 || sum>255)	//�Ƿ�ip
				return 0;
			n_dot++;
			sum = 0;
			continue;
		}
		else if (*p >= '0'&&*p <= '9') {
			sum = sum * 10 + *p - '0';
		}
		else
			return 0;
	}
	if (n_dot != 3 || sum < 0 || sum>255)		//.����ӦΪ3 ����Ӧ4�����֣�
		return 0;
	return i;
}

//�Ƿ�����-1	�Ϸ���0�β�������1 1�β�������2
int check(char **argv, int* para_inf)
{
	if (**argv == '-') {
		int i;
		for (i = 0; *(*argv + 1) && para_0[i] && *(*argv + 1) != para_0[i]; i++)	//�Ƿ���0�β���
			;
		if (*(*argv + 1) == para_0[i]) {
			para_inf[i] = 1;	//��0�β���
			return 1;
		}

		for (i = 0; *(*argv + 1) && para_1[i] && *(*argv + 1) != para_1[i]; i++)	//�Ƿ���1�β���
			;
		if (*(*argv + 1) == para_1[i]) {
			if (**(argv + 1) == '-' || *(argv + 2) == NULL) {
				cout << "����" << *argv << "û�к�������" << endl;
				return -1;
			}
			int n = atoi(*(argv + 1));
			if (n >= para_min[i] && n <= para_max[i])
				para_inf[i] = n;
			return 2;
		}
		cout << "����" << *argv << "������" << endl;
		return -1;
	}
	else {
		cout << *argv << "������-��ͷ�ĺϷ�����" << endl;
		return -1;
	}
}

int main(int argc, char **argv)
{
	if (argc == 1) {
		usage(argv[0]);
		return -1;
	}
	int para_inf[N_PARA] = { 128,100,0,0 };		//˳���¼���� l n t ��С ip��ַλ�� ��ʼֵΪĬ��ֵ
	char **t_argv = argv;
	para_inf[3] = check_ip(t_argv);
	if (para_inf[3] == 0) {
		cout << "IP��ַ����" << endl;
		return -1;
	}

	for (t_argv++; *(t_argv + 1) != NULL;) {
		int flag = check(t_argv, para_inf);
		if (flag == -1)
			return -1;
		t_argv += flag;
	}

	cout << "�������ͨ��" << endl;
	cout << "-n������" << para_inf[1] << endl;
	cout << "-l������" << para_inf[0] << endl;
	cout << "-t������" << para_inf[2] << endl;
	cout << "IP��ַ��" << argv[para_inf[3]] << endl;
	return 0;
}
