// 1752762 ��1�� κ�ٴ�
#include <iostream>
using namespace std;
class Time
{
public:		//ԭ��û��
	void set_time(void);
	void show_time(void);
private:
	int hour;
	int minute;
	int sec;
};

Time t;

int main()
{
	t.set_time();	//ԭ��set_time();
	t.show_time();	//ԭ��show_time();
	return 0;
}

void Time::set_time(void)	//ԭ��int set_time(void)
{
	cin >> hour;	//ԭ��cin >> t.hour;
	cin >> minute;	//ԭ��cin >> t.minute;
	cin >> sec;	//ԭ��cin >> t.sec;
}

void Time::show_time(void)	//ԭ��int show_time(void)
{
	cout << hour << ":" << minute << ":" << sec << endl;	//ԭ��cout << t.hour << ":" << t.minute << ":" << t.sec << endl;
}