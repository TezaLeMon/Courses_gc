// 1752762 ¼Æ1°à ÎºğÙ´ï
#include <string>
#include <iostream>
using namespace std;

class student {
private:
	int num;
	string name;
	char sex;
	float score;
	string addr;
public:
	student();
	student(int _num, const string& _name, char _sex, float _score, const string& addr);
	student& operator=(const student& s);
	bool operator==(const student& s2);
	bool operator!=(const student& s2);
	friend ostream& operator<<(ostream& os, const student& s);
	friend istream& operator>>(istream& is, student& s);
};