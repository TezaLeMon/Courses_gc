// 1752762 ��1�� κ�ٴ�
#include <iostream>
using namespace std;

class Days {
private:
	int year;
	int month;
	int day;
	//�����������private���ݳ�Ա�⣬������������κ����͵����ݳ�Ա

	int is_leap_year();  //�ж��Ƿ����꣬�ǣ�����1  /   �񣺷���0
public:
	int calc_days();     //�����ǵ���ĵڼ���
	/* ������Բ���������Ҫ�����Ա�����Ķ���(����ʵ��)���������� */
	Days(int y, int m, int d);
};

/* �˴��������Ա����������ʵ�� */
Days::Days(int y, int m, int d) {
	year = y;
	month = m;
	day = d;
}

int Days::is_leap_year() {
	if ((year % 4 == 0) && (year % 100 != 0) || (year % 400 == 0))
		return 1;
	return 0;
}

int Days::calc_days() {
	int day_total[12] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
	if (is_leap_year())
		day_total[1] = 29;
	int counts, i;
	for (counts = 0, i = 0; i < month - 1; i++)
		counts += day_total[i];
	if (day > day_total[i] || day <= 0)
		return -1;
	counts += day;
	return counts;
}

/* main������׼�� */
int main()
{
	if (1) {
		Days d1(2012, 3, 18);
		cout << "Ӧ�����78�� ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 12, 31);
		cout << "Ӧ�����365��ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2012, 12, 31);
		cout << "Ӧ�����366��ʵ���ǣ�" << d1.calc_days() << endl;
	}

	if (1) {
		Days d1(2011, 2, 29);
		cout << "Ӧ�����-1�� ʵ���ǣ�" << d1.calc_days() << endl;
	}

	return 0;
}
