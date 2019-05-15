// 1752762 ��1�� κ�ٴ�

#include <iostream>
using namespace std;

class Date {
public:
	Date(int = 1, int = 1, int = 2005);
	//Date(int, int);
	//Date(int);
	//Date();
	void display();
private:
	int month;
	int day;
	int year;
};

Date::Date(int m, int d, int y) :month(m), day(d), year(y) {
}

//Date::Date(int m, int d) : month(m), day(d) {
//	year = 2005;
//}
//
//Date::Date(int m) : month(m) {
//	year = 2005;
//	day = 1;
//}
//
//Date::Date() {
//	year = 2005;
//	day = 1;
//	month = 1;
//}

void Date::display() {
	cout << month << "/" << day << "/" << year << endl;
}

int main()
{
	Date d1(10, 13, 2005);
	Date d2(12, 30);
	Date d3(10);
	Date d4;
	d1.display();
	d2.display();
	d3.display();
	d4.display();
	return 0;
}

/*	��д�������ڶ�����
	d2 d3 d4���õĹ��캯������ ����
	�޸ĺ�ĳ�����d1 d2 d3 d4����ͳһ���캯��
	�����������Ϊ:
	10/13/2005
	12/30/2005
	10/1/2005
	1/1/2005	*/