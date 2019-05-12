// 1752762 计1班 魏鹳达
#include <iostream>
using namespace std;
class Time
{
public:		//原：没有
	void set_time(void);
	void show_time(void);
	int hour;
	int minute;
	int sec;
};

Time t;

int main()
{

	int set_time(void);	//原：没有
	int show_time(void);	//原：没有
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