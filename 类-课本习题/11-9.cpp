// 1752762 计1班 魏鹳达
#include <iostream>
#include <string>
using namespace std;

class Teacher {
protected:
	string name;
	int age;
	char sex;
	string addr;
	string phone;

	string title;
public:
	Teacher();
	Teacher(const string& _name, const int& _age, const char& _sex, const string& _addr, const string& _phone, const string& _title);
	void display();
};

class Cadre {
protected:
	string name;
	int age;
	char sex;
	string addr;
	string phone;

	string post;
public:
	Cadre();
	Cadre(const string& _name, const int& _age, const char& _sex, const string& _addr, const string& _phone, const string& _post);
};

class Teacher_Cadre :public Teacher, public Cadre {
protected:
	int wages;
public:
	Teacher_Cadre();
	Teacher_Cadre(const string& _name, const int& _age, const char& _sex, const string& _addr, const string& _phone, const string& _title, const string& _post, const int& _wages);
	void show();
};

Teacher::Teacher() {
	name = "";
	age = 0;
	sex = 'M';
	addr = "";
	phone = "";
	title = "";
}

Teacher::Teacher(const string& _name, const int& _age, const char& _sex, const string& _addr, const string& _phone, const string& _title){
	name = _name;
	age = _age;
	sex = _sex;
	addr = _addr;
	phone = _phone;
	title = _title;
}

void Teacher::display() {
	cout << "name: " << name << endl;
	cout << "age: " << age << endl;
	cout << "sex: " << sex << endl;
	cout << "title: " << title << endl;
	cout << "address: " << addr << endl;
	cout << "phone: " << phone << endl;
}

Cadre::Cadre() {
	name = "";
	age = 0;
	sex = 'F';
	addr = "";
	phone = "";
	post = "";
}

Cadre::Cadre(const string& _name, const int& _age, const char& _sex, const string& _addr, const string& _phone, const string& _post) {
	name = _name;
	age = _age;
	sex = _sex;
	addr = _addr;
	phone = _phone;
	post = _post;
}

Teacher_Cadre::Teacher_Cadre() :Teacher(), Cadre() {
	wages = 0;
}

Teacher_Cadre::Teacher_Cadre(const string& _name, const int& _age, const char& _sex, const string& _addr, const string& _phone, const string& _title, const string& _post, const int& _wages):
	Teacher(_name, _age, _sex, _addr, _phone, _title), Cadre(_name, _age, _sex, _addr, _phone, _post) {
	wages = _wages;
}

void Teacher_Cadre::show() {
	display();
	cout << "post: " << post << endl;
	cout << "wages: " << wages << endl;
}

int main()
{
	Teacher_Cadre test("张三", 28, 'F', "同济大学电信学院", "12345678910", "教授", "教务处主任", 10000);
	test.show();
	return 0;
}