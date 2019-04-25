// 1752762 计1班 魏鹳达
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>

#define N_para_total 3
#define PATH_LEN_MAX 128
const char para[N_para_total] = "ad";	//存放合法参数

int usage(const char* procname)
{
	printf("Usage: %s [-a] [-d] [<directory>]\n", procname);
	return 0;
}

//合法 返回para数组中对应参数下标+1/默认为0 非法则返回-1
int read_para(int argc, char **argv)
{
	int i, j;
	for (i = argc - 1; i > 0; i--) {	//直接寻找最末尾参数  若有多个参数 因为本例中参数互斥 取最后一个参数 
		if (*argv[i] != '-')
			continue;
		for (j = 0; j < N_para_total; j++)
			if (*(argv[i] + 1) == para[j])
				return j + 1;
		return -1;	//不在合法参数中
	}
	return 0;
}

void print_inf(const int layer, char *d_name) {
	int i;
	for (i = 0; i < layer; i++)
		printf("    ");
	printf("|-- %s", d_name);
}

//mode:0：默认		1：-a模式		2：-d模式
int read_file(char *dir_name, int layers, const int mode, int *n_dir, int *n_reg)
{
	DIR            *dir;
	struct dirent  *node;

	if ((dir = opendir(dir_name)) == NULL)
		return -1;
	while ((node = readdir(dir)) != NULL) {
		if (!strcmp(node->d_name, ".") || !strcmp(node->d_name, ".."))
			continue;
		if (mode != 1 && *(node->d_name) == '.')	//隐藏文件
			continue;

		char t[PATH_LEN_MAX + 1];
		strcpy(t, dir_name);

		if (node->d_type == DT_DIR) {	//是目录
			print_inf(layers, node->d_name);
			printf("\n");
			strcat(t, "/");
			strcat(t, node->d_name);
			(*n_dir)++;
			read_file(t, layers + 1, mode, n_dir, n_reg);
		}
		else if (node->d_type == DT_LNK) {	//快捷方式
			char path[PATH_LEN_MAX + 1];
			strcat(t, "/");
			strcat(t, node->d_name);
			int res = readlink(t, path, PATH_LEN_MAX);
			if (res < 0 || res > PATH_LEN_MAX) {
				printf("\n");
				continue;
			}
			path[res] = '\0';
			if (path[0] != '/') {	//在同一目录
				strcpy(t, dir_name);
				strcat(t, "/");
				strcat(t, path);
			}
			else
				strcpy(t, path);
			struct stat link;
			stat(t, &link);
			while (S_ISLNK(link.st_mode)) {	//可能是多重快捷方式
				res = readlink(t, path, PATH_LEN_MAX);
				if (res < 0 || res > PATH_LEN_MAX)
					break;
				path[res] = '\0';
				if (path[0] != '/') {	//在同一目录
					strcpy(t, dir_name);
					strcat(t, "/");
					strcat(t, path);
				}
				else
					strcpy(t, path);
				stat(path, &link);
			}

			if (mode != 2) {
				print_inf(layers, node->d_name);
				if (S_ISDIR(link.st_mode))
					(*n_dir)++;
				else
					(*n_reg)++;
				printf(" -> %s\n", path);
			}
			else {
				if (S_ISDIR(link.st_mode)) {	//是文件夹则显示
					print_inf(layers, node->d_name);
					printf(" -> %s\n", path);
					(*n_dir)++;
				}
			}
		}
		else if (node->d_type == DT_UNKNOWN) {
			strcat(t, "/");
			strcat(t, node->d_name);
			print_inf(layers, node->d_name);
			printf("\n");
			if (read_file(t, layers + 1, mode, n_dir, n_reg) == -1)
				(*n_reg)++;
			else
				(*n_dir)++;
		}
		else if (mode != 2) {	//是文件(除文件夹和快捷方式之外)
			print_inf(layers, node->d_name);
			printf("\n");
			(*n_reg)++;
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
			printf("%s\n", *(argv + i));
			read_file(*(argv + i), 0, t, &n_dir, &n_reg);
			flag = 0;
		}

	if (flag) {
		char path[PATH_LEN_MAX] = "./";
		printf("%s\n", path);
		read_file(path, 0, t, &n_dir, &n_reg);
	}

	if(t!=2)
		printf("\n%d directories, %d files\n", n_dir, n_reg);
	else
		printf("\n%d directories\n", n_dir);
	return 0;
}