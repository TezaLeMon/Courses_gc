// 1752762 ��1�� κ�ٴ�
#include <iostream>
using namespace std;
class Time
{
public:		//ԭ��û��
	void set_time(void);
	void show_time(void);
	int hour;
	int minute;
	int sec;
};

Time t;

int main()
{

	int set_time(void);	//ԭ��û��
	int show_time(void);	//ԭ��û��
	set_time();
	show_time();
	return 0;
}

int set_time(void)
{
	cin >> t.hour;
	cin >> t.minute;
	cin >> t.sec;
	return 0;
}

int show_time(void)
{
	cout << t.hour << ":" << t.minute << ":" << t.sec << endl;
	return 0;
}