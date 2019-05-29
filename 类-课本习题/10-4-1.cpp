// 1752762 ��1�� κ�ٴ�
#include <iostream>
using namespace std;

class matrix {
    private:
        int value[2][3];
	//����֮�ⲻ������������ݳ�Ա
    public:
	matrix(const int(*p)[3]);	//���캯�����������ʼ������
	void display() const;		//����þ���
	matrix operator+(const matrix &b);

	/* ----������Ҫ���������Ա�����Ķ��壬��������---- */
	matrix();
};

/* ----������Ա����������ʵ��---- */
matrix::matrix(const int(*p)[3])	//���캯�����������ʼ������
{
	int i, j;
	for (i = 0; i < 2; i++)
		for (j = 0; j < 3; j++)
			value[i][j] = p[i][j];
}

matrix::matrix()
{
	int i, j;
	for (i = 0; i < 2; i++)
		for (j = 0; j < 3; j++)
			value[i][j] = 0;
}

void matrix::display() const		//����þ���
{
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++)
			cout << value[i][j] << " ";
		cout << endl;
	}
}

matrix matrix::operator+(const matrix &b)
{
	matrix c;
	int i, j;
	for (i = 0; i < 2; i++)
		for (j = 0; j < 3; j++)
			c.value[i][j] = value[i][j] + b.value[i][j];
	return c;
}

/* ----main������׼��---- */
int main()
{
	int a[2][3] = { { 1,2,3 },{ 4,5,6 } };
	int b[2][3] = { { 2,4,6 },{ 3,6,9 } };
	matrix m1(a), m2(b), m3;

	cout << "��ʼ����m1��ֵ��" << endl;
	m1.display();
	cout << "��ʼ����m2��ֵ��" << endl;
	m2.display();
	m3 = m1 + m2;
	cout << "��Ӻ����m3��ֵ��" << endl;
	m3.display();

	return 0;
}
