// 1752762 ��1�� κ�ٴ�
#include <iostream>
using namespace std;

class matrix {
    private:
        int value[2][3];
	//����֮�ⲻ������������ݳ�Ա
    public:
        matrix operator+(const matrix &b);

        /* ----������Ҫ��ӳ����ݳ�Ա����Ķ��壬��������---- */
		friend istream& operator>>(istream& ifs, matrix& m);
		friend ostream& operator<<(ostream& ofs, matrix& m);
};

/* ----�������Ա����������ʵ��---- */
matrix matrix::operator+(const matrix &b)
{
	matrix c;
	int i, j;
	for (i = 0; i < 2; i++)
		for (j = 0; j < 3; j++)
			c.value[i][j] = value[i][j] + b.value[i][j];
	return c;
}

istream& operator>>(istream& ifs, matrix& m)
{
	int i, j;
	for (i = 0; i < 2; i++)
		for (j = 0; j < 3; j++)
			ifs >> m.value[i][j];
	return ifs;
}

ostream& operator<<(ostream& ofs, matrix& m)
{
	int i, j;
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 3; j++)
			ofs << m.value[i][j] << " ";
		cout << endl;
	}
	return ofs;
}

/* ----main������׼��---- */
int main()
{
    matrix m1, m2, m3;

    cout << "���������m1��ֵ(��2��3�У������к��е�˳������)" << endl;
    cin >> m1;
    cout << "���������m2��ֵ(��2��3�У������к��е�˳������)" << endl;
    cin >> m2;
	
    cout << "��ʼ����m1��ֵ��" << endl;
    cout << m1 << endl;
    cout << "��ʼ����m2��ֵ��" << endl;
    cout << m2 << endl;
    cout << "��Ӻ����m3��ֵ��" << endl;
    cout << (m3=m1+m2) << endl;

    return 0;
}
