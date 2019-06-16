// 1752762 ¼Æ1°à ÎºðÙ´ï
#include "12-b2-double1.h"
#include <math.h> 
#include <iostream>
using namespace std;

double1::double1() {
	value = 0;
}

double1::double1(const double i) {
	value = double(i);
}

bool double1::operator==(const double1& s2) {
	return fabs(value - s2.value) < 1e-6;
}

bool double1::operator!=(const double1& s2) {
	return fabs(value - s2.value) > 1e-6;
}

ostream& operator<<(ostream& os, const double1& s) {
	os << s.value;
	return os;
}

istream& operator>>(istream& is, double1& s){
	is >> s.value;
	return is;
}