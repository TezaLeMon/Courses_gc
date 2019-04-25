// 1752762 计1班 魏鹳达
#define MAX_ROW 9
#define MAX_COL 9

//内部数组生成
void array_create(int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col, int n_balls);
//添加球
void array_add(int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col, const int ball);
//移动球
void array_move(int arr[MAX_ROW + 2][MAX_COL + 2], const int row_from, const int col_from, const int row_to, const int col_to);
//寻路 有路返回1 无路返回0  数组path中经过的路径为1，其余为0
int path_find(const int arr[MAX_ROW + 2][MAX_COL + 2], int path[MAX_ROW + 2][MAX_COL + 2], const int row_from, const int col_from, const int row_to, const int col_to, int &flag_find);
//判断游戏是否结束
int is_over(int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col);
//判断是否消除球并进行相应操作 消除返回1 否则返回0
int remove(int arr[MAX_ROW + 2][MAX_COL + 2], const int row_target, const int col_target, const int row, const int col, int *ball_count = NULL);



//文本形式打印内部数组
void array_print_text(const char* s, const int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col, const int color = 1);
//文本形式移动内部数组 未移动返回0 移动但未消除返回1 移动且有消除返回2
int array_print_move_text(int arr[MAX_ROW + 2][MAX_COL + 2], int path[MAX_ROW + 2][MAX_COL + 2], const int row, const int col, const int move_flag = 0);
//文本打印路径查找结果
void path_print_result_text(const int path[MAX_ROW + 2][MAX_COL + 2], const int row, const int col);
void path_print_move_text(const int arr[MAX_ROW + 2][MAX_COL + 2], const int path[MAX_ROW + 2][MAX_COL + 2], const int row, const int col);

//图形打印内部数组（无分隔线）
void array_print_img_no(const int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col);
//图形打印内部数组（有分隔线）
void array_print_img_yes(const int arr[MAX_ROW + 2][MAX_COL + 2], const int row, const int col);
//图形移动内部数组 移动但未消除返回1 移动且有消除返回2
int array_print_move_img(int arr[MAX_ROW + 2][MAX_COL + 2], int path[MAX_ROW + 2][MAX_COL + 2], const int row, const int col, int *ball_count = NULL, const int can_keyboard = 0);



//暂停继续 显示信息
void to_be_continued(const char *prompt);
//输入数据
void input_int(const char *s, int *target, const int low, const int high, const int x, const int y);
void input_str2(const char *s, char *target, const int row_low, const int row_high, const int col_low, const int col_high);
//生成球并打印信息
void ball_creat_print(int ball[3], const int again_flag);
void ball_creat_print_img(int ball[3], const int again_flag);
//图形界面 打印得分
void score_print(const int ball_conut[8]);
//图形界面 打印彩球情况
void ball_count_print(const int arr[MAX_ROW + 2][MAX_COL + 2], const int removeball_conut[8], const int row, const int col);