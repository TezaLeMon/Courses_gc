// 1752762 ��x�� κ�ٴ�
#include <iostream>
#include <limits>
using namespace std;
int main()
{
	int x;

	while (1) {
		cout << "������x��ֵ(0-100)��";
		cin >> x;   //����x�ķ�ʽ������ˣ���׼�÷�cin
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			continue;
		}
		if (x >= 0 && x <= 100)
			break;
	}

	cout << "x=" << x << endl;

	return 0;
}
