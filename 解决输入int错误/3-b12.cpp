// 1752762 计x班 魏鹳达
#include <iostream>
#include <limits>
using namespace std;
int main()
{
	int x;

	while (1) {
		cout << "请输入x的值(0-100)：";
		cin >> x;   //读入x的方式必须如此，不准用非cin
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
