// 1752762 计1班 魏鹳达
#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

#define N_PARA 4
const char para_1[] = "ln ";	//存放有一值参数
const char para_0[] = "  t";	//存放无值参数
const int para_min[] = { 64,1 };	//相应参数最小值
const int para_max[] = { 64000,10000 };	//相应参数最大值

/***************************************************************************
  函数名称：
  功    能：
  输入参数：
  返 回 值：
  说    明：
***************************************************************************/
int usage(const char *procname)
{
	cout << "Usage: " << procname << " [-l 大小] [-n 数量] [-t] IP地址" << endl;
	return 0;
}

//非法返回0 合法返回ip所在argv下标
int check_ip(char **argv) {
	int i = 0, n_dot = 0, sum = 0;
	while (argv[i + 1] != NULL)
		i++;
	char *p;
	for (p = argv[i]; *p; p++) {
		if (*p == '.') {
			if (p == argv[i] || *(p + 1) == '.' || *(p + 1) == '\0')	//字符串为.开头 或连续两个. 或.结尾
				return 0;
			if (sum < 0 || sum>255)	//非法ip
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
	if (n_dot != 3 || sum < 0 || sum>255)		//.个数应为3 （对应4个数字）
		return 0;
	return i;
}

//非法返回-1	合法：0参参数返回1 1参参数返回2
int check(char **argv, int* para_inf)
{
	if (**argv == '-') {
		int i;
		for (i = 0; *(*argv + 1) && para_0[i] && *(*argv + 1) != para_0[i]; i++)	//是否是0参参数
			;
		if (*(*argv + 1) == para_0[i]) {
			para_inf[i] = 1;	//有0参参数
			return 1;
		}

		for (i = 0; *(*argv + 1) && para_1[i] && *(*argv + 1) != para_1[i]; i++)	//是否是1参参数
			;
		if (*(*argv + 1) == para_1[i]) {
			if (**(argv + 1) == '-' || *(argv + 2) == NULL) {
				cout << "参数" << *argv << "没有后续参数" << endl;
				return -1;
			}
			int n = atoi(*(argv + 1));
			if (n >= para_min[i] && n <= para_max[i])
				para_inf[i] = n;
			return 2;
		}
		cout << "参数" << *argv << "不存在" << endl;
		return -1;
	}
	else {
		cout << *argv << "不是以-开头的合法参数" << endl;
		return -1;
	}
}

int main(int argc, char **argv)
{
	if (argc == 1) {
		usage(argv[0]);
		return -1;
	}
	int para_inf[N_PARA] = { 128,100,0,0 };		//顺序记录参数 l n t 大小 ip地址位置 初始值为默认值
	char **t_argv = argv;
	para_inf[3] = check_ip(t_argv);
	if (para_inf[3] == 0) {
		cout << "IP地址错误" << endl;
		return -1;
	}

	for (t_argv++; *(t_argv + 1) != NULL;) {
		int flag = check(t_argv, para_inf);
		if (flag == -1)
			return -1;
		t_argv += flag;
	}

	cout << "参数检查通过" << endl;
	cout << "-n参数：" << para_inf[1] << endl;
	cout << "-l参数：" << para_inf[0] << endl;
	cout << "-t参数：" << para_inf[2] << endl;
	cout << "IP地址：" << argv[para_inf[3]] << endl;
	return 0;
}
