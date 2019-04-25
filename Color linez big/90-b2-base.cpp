// 1752762 计1班 魏鹳达
#include <time.h>
#include <stdlib.h>
#include "90-b2.h"
void array_create(int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col, int n_balls)
{
	int i, j;
	//初始化 边界为-1 内部全为0
	for (i = 0; i <= col + 1; i++)
	{
		arr[0][i] = -1;
		arr[row + 1][i] = -1;
	}
	for (i = 1; i <= row; i++)
	{
		arr[i][0] = -1;
		arr[i][col + 1] = -1;
		for (j = 1; j <= col; j++)
			arr[i][j] = 0;
	}
	while (n_balls--)
	{
		int t_row = 0;
		int t_col = 0;
		while (arr[t_row][t_col] != 0)
		{
			t_row = 1 + rand() % row;
			t_col = 1 + rand() % col;
		}
		arr[t_row][t_col] = 1 + rand() % 7;
	}
}

void array_add(int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col, const int ball)
{
	int t_row = 0;
	int t_col = 0;
	while (arr[t_row][t_col] != 0)
	{
		t_row = 1 + rand() % row;
		t_col = 1 + rand() % col;
	}
	arr[t_row][t_col] = ball;
}

void array_move(int arr[MAX_ROW + 2][MAX_COL + 2], const int row_from, const int col_from, const int row_to, const int col_to)
{
	arr[row_to][col_to] = arr[row_from][col_from];
	arr[row_from][col_from] = 0;
}

//ps 调用时&flag_find手动置0 先假设未找到
int path_find(const int arr[MAX_ROW + 2][MAX_COL + 2], int path[MAX_ROW + 2][MAX_COL + 2], const int row_from, const int col_from, const int row_to, const int col_to, int &flag_find)
{
	path[row_from][col_from] = 1;		//先假设走此地
	if (row_from == row_to && col_from == col_to)		//到达目的地
		flag_find = 1;

	//未到达目的地则继续查找
	if (!flag_find&&arr[row_from][col_from + 1] == 0 && path[row_from][col_from + 1] == 0)	//右
		path_find(arr, path, row_from, col_from + 1, row_to, col_to, flag_find);
	if (!flag_find&&arr[row_from + 1][col_from] == 0 && path[row_from + 1][col_from] == 0)	//下
		path_find(arr, path, row_from + 1, col_from, row_to, col_to, flag_find);
	if (!flag_find&&arr[row_from][col_from - 1] == 0 && path[row_from][col_from - 1] == 0)	//左
		path_find(arr, path, row_from, col_from - 1, row_to, col_to, flag_find);
	if (!flag_find&&arr[row_from - 1][col_from] == 0 && path[row_from - 1][col_from] == 0)	//上
		path_find(arr, path, row_from - 1, col_from, row_to, col_to, flag_find);

	if (!flag_find)		//此路不通
		path[row_from][col_from] = 2;

	return flag_find;
}

int is_over(int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col)
{
	for (int i = 1; i <= row; i++)
		for (int j = 1; j <= col; j++)
			if (arr[i][j] == 0)
				return 0;
	return 1;
}

int remove(int arr[MAX_ROW + 2][MAX_COL + 2], const int row_target, const int col_target, const int row, const int col, int *ball_count)
{
	int i, from, to, count = 1, flag = 0;
	//纵向
	for (from = row_target - 1; from >= 1 && arr[from][col_target] == arr[row_target][col_target]; from--)
		count++;
	for (to = row_target + 1; to <= row && arr[to][col_target] == arr[row_target][col_target]; to++)
		count++;
	if (count >= 5)
	{
		flag = 1;
		for (i = from + 1; i < to; i++)
		{
			if (i == row_target)
				continue;
			arr[i][col_target] = 0;
		}
		if (ball_count)
			ball_count[arr[row_target][col_target]] += count - 1;
	}
	//横向
	count = 1;
	for (from = col_target - 1; from >= 1 && arr[row_target][from] == arr[row_target][col_target]; from--)
		count++;
	for (to = col_target + 1; to <= col && arr[row_target][to] == arr[row_target][col_target]; to++)
		count++;
	if (count >= 5)
	{
		flag = 1;
		for (i = from + 1; i < to; i++)
		{
			if (i == col_target)
				continue;
			arr[row_target][i] = 0;
		}
		if (ball_count)
			ball_count[arr[row_target][col_target]] += count - 1;
	}
	//斜向-左上到右下
	count = 1;
	for (from = -1; col_target + from >= 1 && row_target + from >= 1 
		&& arr[row_target + from][col_target + from] == arr[row_target][col_target]; from--)
		count++;
	for (to = 1; col_target + to <= col && row_target + to <= row
		&& arr[row_target + to][col_target + to] == arr[row_target][col_target]; to++)
		count++;
	if (count >= 5)
	{
		flag = 1;
		for (i = from + 1; i < to; i++)
		{
			if (i == 0)
				continue;
			arr[row_target + i][col_target + i] = 0;
		}
		if (ball_count)
			ball_count[arr[row_target][col_target]] += count - 1;
	}
	//斜向-左下到右上
	count = 1;
	for (from = -1; col_target + from >= 1 && row_target + from <= row
		&& arr[row_target - from][col_target + from] == arr[row_target][col_target]; from--)
		count++;
	for (to = 1; col_target + to <= col && row_target + to >= 1
		&& arr[row_target - to][col_target + to] == arr[row_target][col_target]; to++)
		count++;
	if (count >= 5)
	{
		flag = 1;
		for (i = from + 1; i < to; i++)
			arr[row_target - i][col_target + i] = 0;
		if (ball_count)
			ball_count[arr[row_target][col_target]] += count - 1;
	}

	if (flag)
	{
		ball_count[arr[row_target][col_target]]++;
		arr[row_target][col_target] = 0;
		return 1;
	}
	return 0;
}