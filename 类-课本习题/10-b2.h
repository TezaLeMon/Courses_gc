// 1752762 ��1�� κ�ٴ�
#include <iostream>
using namespace std;

/* ��ȫDate��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class Date {
	private:
		int year;
		int month;
		int day;
		/* ������������ݳ�Ա */
	public:
	/* ������Ҫ��������ĳ�Ա��������Ԫ������(������������ݳ�Ա) */
		Date();
		Date(int y, int m, int d);
		void set(int y = 2000, int m = 1, int d = 1);
		void get(int& y, int& m, int& d);
		void show();
		Date(int days_total);
		operator int();
		//friend Date& operator+(Date& a, int& b);
		//friend Date& operator+(int& a, Date& b);
		//friend Date& operator-(Date& a, int& b);
		//friend Date& operator-(int& a, Date& b);
		Date& operator+(int b);
		Date& operator-(int b);
		int operator-(Date& b);

		Date operator++(int);
		Date& operator++();
		Date operator--(int);
		Date& operator--();
		friend istream& operator>>(istream& is, Date& a);
		friend ostream& operator<<(ostream& os, Date& a);
		friend bool operator<(Date& a, Date& b);
		friend bool operator<=(Date& a, Date& b);
		friend bool operator>(Date& a, Date& b);
		friend bool operator>=(Date& a, Date& b);
		friend bool operator==(Date& a, Date& b);
		friend bool operator!=(Date& a, Date& b);
};

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
int is_leap(int year);

/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */
