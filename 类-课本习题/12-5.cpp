// 1752762 计1班 魏鹳达

#include <iostream>
#include <math.h>
using namespace std;

class Shape {
protected:
	
public:
	virtual double area() = 0;
};

//圆
class Circle :public Shape {
private:
	double radius;
public:
	Circle();
	virtual double area();
};

Circle::Circle() {
	radius = 1;	//默认半径为1
}

double Circle::area() {
	return 3.14*radius*radius;
}

//正方形
class Square :public Shape {
private:
	double len;
public:
	Square();
	virtual double area();
};

Square::Square() {
	len = 1;	//正方形默认边长为1
}

double Square::area() {
	return len * len;
}

//长方形
class Rectangle :public Shape {
private:
	double len1;
	double len2;
public:
	Rectangle();
	virtual double area();
};

Rectangle::Rectangle() {
	len1 = 1;
	len2 = 2;	//默认为 1*2的长方形
}

double Rectangle::area() {
	return len1 * len2;
}

//梯形
class Trapezoid :public Shape {
private:
	double len_down;
	double len_up;
	double len_left;
	double len_right;
	double h;
public:
	Trapezoid();
	virtual double area();
};

Trapezoid::Trapezoid() {
	len_down = 10;	//默认为下底10 上底4的等腰梯形
	len_up = 4;
	len_left = 5;
	len_right = 5;
	h = 4;
}

double Trapezoid::area() {
	return (len_up + len_down)*h / 2;
}

//三角形
class Triangle :public Shape {
private:
	double len1;
	double len2;
	double len3;
public:
	Triangle();
	virtual double area();
};

Triangle::Triangle() {
	len1 = 3;
	len2 = 4;
	len3 = 5;	//默认为3*4*5的直角三角形
}

double Triangle::area() {
	double p = (len1 + len2 + len3) / 2;
	return sqrt(p*(p - len1)*(p - len2)*(p - len3));
}

int main()
{
	Circle c1;	//没有设有参的构造函数 下同
	Square s1;
	Rectangle r1;
	Trapezoid t1;
	Triangle t2;
	Shape *s[5] = { &c1,&s1,&r1,&t1,&t2 };

	int i;
	for (i = 0; i < 5; i++)
		cout << s[i]->area() << endl;

	return 0;
}