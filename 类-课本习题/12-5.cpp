// 1752762 ��1�� κ�ٴ�

#include <iostream>
#include <math.h>
using namespace std;

class Shape {
protected:
	
public:
	virtual double area() = 0;
};

//Բ
class Circle :public Shape {
private:
	double radius;
public:
	Circle();
	virtual double area();
};

Circle::Circle() {
	radius = 1;	//Ĭ�ϰ뾶Ϊ1
}

double Circle::area() {
	return 3.14*radius*radius;
}

//������
class Square :public Shape {
private:
	double len;
public:
	Square();
	virtual double area();
};

Square::Square() {
	len = 1;	//������Ĭ�ϱ߳�Ϊ1
}

double Square::area() {
	return len * len;
}

//������
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
	len2 = 2;	//Ĭ��Ϊ 1*2�ĳ�����
}

double Rectangle::area() {
	return len1 * len2;
}

//����
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
	len_down = 10;	//Ĭ��Ϊ�µ�10 �ϵ�4�ĵ�������
	len_up = 4;
	len_left = 5;
	len_right = 5;
	h = 4;
}

double Trapezoid::area() {
	return (len_up + len_down)*h / 2;
}

//������
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
	len3 = 5;	//Ĭ��Ϊ3*4*5��ֱ��������
}

double Triangle::area() {
	double p = (len1 + len2 + len3) / 2;
	return sqrt(p*(p - len1)*(p - len2)*(p - len3));
}

int main()
{
	Circle c1;	//û�����вεĹ��캯�� ��ͬ
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