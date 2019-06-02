// 1752762 计1班 魏鹳达
#include <iostream>
#include <string>
using namespace std;

class Teacher {
private:
	int num;
	string name;
	char sex;
public:
	Teacher();
	Teacher(const int& _num, const string& _name, const char& _sex);
	void display();
};

class BirthDate {
private:
	int year;
	int month;
	int day;
public:
	BirthDate();
	BirthDate(const int& _year, const int& _month, const int& _day);
	void display();
	void change(const int& _year, const int& _month, const int& _day);
};

class Professor :public Teacher {
private:
	BirthDate birthday;
public:
	Professor();
	Professor(const int& _num, const string& _name, const char& _sex, const int& _year, const int& _month, const int& _day);
	void show();
	void change_bir(const int& _year, const int& _month, const int& _day);
};


Teacher::Teacher() {
	num = 0;
	name = "";
	sex = 'M';
}

Teacher::Teacher(const int& _num, const string& _name, const char& _sex){
	num = _num;
	name = _name;
	sex = _sex;
}

void Teacher::display() {
	cout << "num: " << num << endl;
	cout << "name: " << name << endl;
	cout << "sex:" << sex << endl;
}


BirthDate::BirthDate() {
	year = 1900;
	month = 1;
	day = 1;
}

BirthDate::BirthDate(const int& _year, const int& _month, const int& _day) {
	year = _year;
	month = _month;
	day = _day;
}

void BirthDate::display() {
	cout << "birthdate: " << year << '.' << month << '.' << day << endl;
}

void BirthDate::change(const int& _year, const int& _month, const int& _day) {
	year = _year;
	month = _month;
	day = _day;
}


Professor::Professor() {

}

Professor::Professor(const int& _num, const string& _name, const char& _sex, const int& _year, const int& _month, const int& _day) :
	Teacher(_num, _name, _sex) {
	birthday = BirthDate(_year, _month, _day);
}

void Professor::show() {
	display();
	birthday.display();
}

void Professor::change_bir(const int& _year, const int& _month, const int& _day)
{
	birthday.change(_year, _month, _day);
}



int main()
{
	Professor prof1(18123, "张三", 'F', 1988, 1, 23);

	cout << "初始信息：" << endl;
	prof1.show();
	cout << endl;

	cout << "修改生日后：" << endl;
	prof1.change_bir(1913, 4, 25);
	prof1.show();

	return 0;
}