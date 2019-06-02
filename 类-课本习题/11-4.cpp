// 1752762 计1班 魏鹳达
#include <iostream>
#include <string>
using namespace std;

class Student {
public:
protected:
	int num;
	string name;
	char sex;
};

class Student1 :public Student {
public:
	void get_value_1();
	void display_1();
private:
	int age;
	string addr;
};

void Student1::get_value_1() {
	cin >> num >> name >> sex >> age >> addr;
}

void Student1::display_1() {
	cout << "num:" << num << endl;
	cout << "name:" << name << endl;
	cout << "sex:" << sex << endl;
	cout << "age:" << age << endl;
	cout << "address:" << addr << endl;
}

int main()
{
	Student1 stud;
	stud.get_value_1();
	stud.display_1();
	return 0;
}

/*
	在继承3代或以上时不可互相替代
	或者在需要体外访问public段时也不能替代
	主要区别在于：
	public段被保护继承后视为protected段（改变了属性）
			被公有继承后视为public段（为改变属性）
*/