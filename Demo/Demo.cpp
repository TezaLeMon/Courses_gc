#include <iostream>
using namespace std;

class Time {
private:
	int hour;
public:
	Time() {
		hour = 0;
	}
	void display(){
		cout << hour << endl;
	}
	~Time() {
		cout << "End" << endl;
	}
};

int main()
{
	Time *t = new Time[10];
	delete[] t;
	return 0;
}
