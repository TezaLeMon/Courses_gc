// 1752762 ��1�� κ�ٴ�
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

/*	stud�ȵ��ù��캯�� ����ʼֵ
	������change���� �ı�stud.num stud.scoreֵ
	�����������Ϊ:
	101 78.5
	101 80.5	*/