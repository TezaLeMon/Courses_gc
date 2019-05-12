// 1752762 计1班 魏鹳达
#include <iostream>
using namespace std;
class Time
{
public:		//原：没有
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
	t.set_time();	//原：set_time();
	t.show_time();	//原：show_time();
	return 0;
}

void Time::set_time(void)	//原：int set_time(void)
{
	cin >> hour;	//原：cin >> t.hour;
	cin >> minute;	//原：cin >> t.minute;
	cin >> sec;	//原：cin >> t.sec;
}

void Time::show_time(void)	//原：int show_time(void)
{
	cout << hour << ":" << minute << ":" << sec << endl;	//原：cout << t.hour << ":" << t.minute << ":" << t.sec << endl;
}