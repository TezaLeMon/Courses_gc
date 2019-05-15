// 1752762 计1班 魏鹳达
#include <iostream>
using namespace std;

class Student
{
public:
	Student(int n,float s):num(n),score(s){	}
	void change(int n, float s) {
		num = n;
		score = s;
	}
	void display() {
		cout << num << " " << score << endl;
	}
private:
	int num;
	float score;
};

int main()
{
	Student stud(101, 78.5);
	stud.display();
	stud.change(101, 80.5);
	stud.display();
	return 0;
}

/*	stud先调用构造函数 赋初始值
	随后调用change函数 改变stud.num stud.score值
	程序的输出结果为:
	101 78.5
	101 80.5	*/