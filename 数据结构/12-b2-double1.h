// 1752762 ¼Æ1°à ÎºðÙ´ï

#include <string>
#include <iostream> 
using namespace std;

class double1 {
private:
	double value;
public:
	double1();
	double1(const double i);
	bool operator==(const double1& s2);
	bool operator!=(const double1& s2);
	friend ostream& operator<<(ostream& os, const double1& s);
	friend istream& operator>>(istream& is, double1& s);
};