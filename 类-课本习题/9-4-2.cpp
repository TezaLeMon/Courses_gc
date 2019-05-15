// 1752762 计1班 魏鹳达
#include <iostream>
using namespace std;

class student {
private:
	int num;
	float score;
public:
	void display();  //输出学号和成绩
	void get(void);  //键盘输入学号和成绩
//类中不允许再添加任何数据成员和成员函数
};

/* 在此给出类成员函数的体外实现 */
void student::display() {
	cout << num << '\t' << score << endl;
}

void student::get(void) {
	cin >> num >> score;		//未作错误输入处理
}

int main()
{
	/* 【注意：】函数中不允许再定义任何类型的变量(包括全局变量) */
	student *p, s[5];

	/* 键盘输入5个人的学号及成绩
	  【要求：】必须给出明确的输入提示，例如“请输入第**个人学号和成绩” */
	int i;
	p = s;
	for (i = 0; i < 5; i++) {
		cout << "请输入第" << i + 1 << "个人的学号和成绩" << endl;
		(*(p + i)).get();		//未作错误输入处理
	}

	  /* 输出第1、3、5个人的信息 */
	for (i = 0; i < 5; i += 2) {
		cout << "第" << i + 1 << "个人的学号和成绩为" << endl;
		(*(p + i)).display();
	}

	return 0;
}