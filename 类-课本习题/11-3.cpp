// 1752762 ¼Æ1°à ÎºğÙ´ï
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

class Student1 :protected Student {
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