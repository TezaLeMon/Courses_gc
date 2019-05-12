// 1752762 ¼Æ1°à ÎºðÙ´ï
#include <iostream>
using namespace std;
#define N 3

class cfz {
private:
	double length, width, height;
public:
	void input() {
		cout << "input length, width, height" << endl;
		cin >> length >> width >> height;
	}
	double volume() {
		return length * width * height;
	}
	void output() {
		cout << "volume:" << volume() << endl;
	}
};

int main()
{
	cfz t;
	int i;
	for (i = 0; i < N; i++) {
		t.input();
		t.volume();
		t.output();
	}
	return 0;
}