// 1752762 计1班 魏鹳达
#include "12-b2-student.h"
using namespace std;

student::student() {
	num = 1850000;
	name = "张三";
	sex = 'M';
	score = 100;
	addr = "电信学院";
}

student::student(int _num, const string& _name, char _sex, float _score, const string& _addr) {
	num = _num;
	name = _name;
	sex = _sex;
	score = _score;
	addr = _addr;
}

student& student::operator=(const student& s) {
	num = s.num;
	name = s.name;
	sex = s.sex;
	score = s.score;
	addr = s.addr;
	return *this;
}

bool student::operator==(const student& s2) {
	return num == s2.num;
}

bool student::operator!=(const student& s2) {
	return num != s2.num;
}

ostream& operator<<(ostream& os, const student& s) {
	os << s.num << '-' << s.name << '-' << s.sex << '-' << s.score << '-' << s.addr << "->";
	return os;
}

istream& operator>>(istream& is, student& s) {
	is >> s.num >> s.name >> s.sex >> s.score >> s.addr;
	return is;
}