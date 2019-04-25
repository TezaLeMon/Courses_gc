// 1752762 ��1�� κ�ٴ�
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <iomanip>
#include <string.h>
using namespace std;

#define N_para_total 3
#define PATH_LEN_MAX 128
const char para[N_para_total] = "ad";	//��źϷ�����

int usage(const char* procname)
{
	cout << "Usage: " << procname << " [-a] [-d] [<directory>]" << endl;
	return 0;
}

//�Ϸ� ����para�����ж�Ӧ�����±�+1/Ĭ��Ϊ0 �Ƿ��򷵻�-1
int read_para(int argc, char **argv)
{
	int i, j;
	for (i = argc - 1; i > 0; i--) {	//ֱ��Ѱ����ĩβ����  ���ж������ ��Ϊ�����в������� ȡ���һ������ 
		if (*argv[i] != '-')
			continue;
		for (j = 0; j < N_para_total; j++)
			if (*(argv[i] + 1) == para[j])
				return j + 1;
		return -1;	//���ںϷ�������
	}
	return 0;
}

void print_inf(const int layer, char *d_name) {
	int i;
	cout << setw(layer * 4) << ' ';
	cout << "|-- " << d_name;
}

int read_file(char *dir_name, int layers, const int mode, int *n_dir, int *n_reg)
{
	DIR            *dir;
	struct dirent  *node;

	if ((dir = opendir(dir_name)) == NULL)
		return -1;

	while ((node = readdir(dir)) != NULL) {
		char t[PATH_LEN_MAX + 1];
		strcpy(t, dir_name);
		if (!strcmp(node->d_name, ".") || !strcmp(node->d_name, ".."))
			continue;
		if (mode != 1 && *(node->d_name) == '.')	//�����ļ�
			continue;
		if (node->d_type == DT_DIR) {	//��Ŀ¼
			print_inf(layers, node->d_name);
			cout << endl;
			strcat(t, "/");
			strcat(t, node->d_name);
			(*n_dir)++;
			read_file(t, layers + 1, mode, n_dir, n_reg);
		}
		else if (mode != 2 && node->d_type == DT_REG) {	//���ļ�
			print_inf(layers, node->d_name);
			cout << endl;
			(*n_reg)++;
		}
		else if (node->d_type == DT_LNK) {	//��ݷ�ʽ
			if (mode != 2) {
				char path[PATH_LEN_MAX + 1];
				strcat(t, node->d_name);
				print_inf(layers, node->d_name);
				int res = readlink(t, path, PATH_LEN_MAX);
				if (res < 0 || res >= PATH_LEN_MAX) {
					cout << endl;
					continue;
				}
				path[res] = '\0';
				cout << " -> " << path << endl;
				(*n_reg)++;
			}
			else {
				char path[PATH_LEN_MAX + 1];
				strcat(t, node->d_name);
				int res = readlink(t, path, PATH_LEN_MAX);
				if (res < 0 || res >= PATH_LEN_MAX)
					continue;
				path[res] = '\0';
				struct stat link;
				stat(path, &link);

				if (link.st_mode & S_IFDIR) {
					print_inf(layers, node->d_name);
					cout << " -> " << path << endl;
					(*n_dir)++;
				}
			}
		}
	}

	closedir(dir);
	return 0;
}

int main(int argc, char **argv)
{
	int t = read_para(argc, argv);
	if (t == -1) {
		usage(argv[0]);
		return -1;
	}

	int i, flag = 1;
	int n_reg = 0, n_dir = 0;
	for (i = 1; i < argc; i++)
		if (**(argv + i) != '-') {
			cout << *(argv + i) << endl;
			read_file(*(argv + i), 0, t, &n_dir, &n_reg);
			flag = 0;
		}

	if (flag) {
		char path[PATH_LEN_MAX] = "./";
		cout << path << endl;
		read_file(path, 0, t, &n_dir, &n_reg);
	}

	cout << endl << n_dir << " directories, " << n_reg << " files" << endl;
	return 0;
}