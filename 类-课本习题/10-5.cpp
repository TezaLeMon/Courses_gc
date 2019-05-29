// 1752762 计1班 魏鹳达
#include <iostream>
using namespace std;

class matrix {
    private:
        int value[2][3];
	//除此之外不允许再添加数据成员
    public:
        matrix operator+(const matrix &b);

        /* ----根据需要添加除数据成员以外的定义，数量不限---- */
		friend istream& operator>>(istream& ifs, matrix& m);
		friend ostream& operator<<(ostream& ofs, matrix& m);
};

/* ----给出类成员函数的体外实现---- */
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

/* ----main函数不准动---- */
int main()
{
    matrix m1, m2, m3;

    cout << "请输入矩阵m1的值(共2行3列，按先行后列的顺序输入)" << endl;
    cin >> m1;
    cout << "请输入矩阵m2的值(共2行3列，按先行后列的顺序输入)" << endl;
    cin >> m2;
	
    cout << "初始矩阵m1的值：" << endl;
    cout << m1 << endl;
    cout << "初始矩阵m2的值：" << endl;
    cout << m2 << endl;
    cout << "相加后矩阵m3的值：" << endl;
    cout << (m3=m1+m2) << endl;

    return 0;
}
