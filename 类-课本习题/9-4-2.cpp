// 1752762 ��1�� κ�ٴ�
#include <iostream>
using namespace std;

class student {
private:
	int num;
	float score;
public:
	void display();  //���ѧ�źͳɼ�
	void get(void);  //��������ѧ�źͳɼ�
//���в�����������κ����ݳ�Ա�ͳ�Ա����
};

/* �ڴ˸������Ա����������ʵ�� */
void student::display() {
	cout << num << '\t' << score << endl;
}

void student::get(void) {
	cin >> num >> score;		//δ���������봦��
}

int main()
{
	/* ��ע�⣺�������в������ٶ����κ����͵ı���(����ȫ�ֱ���) */
	student *p, s[5];

	/* ��������5���˵�ѧ�ż��ɼ�
	  ��Ҫ�󣺡����������ȷ��������ʾ�����硰�������**����ѧ�źͳɼ��� */
	int i;
	p = s;
	for (i = 0; i < 5; i++) {
		cout << "�������" << i + 1 << "���˵�ѧ�źͳɼ�" << endl;
		(*(p + i)).get();		//δ���������봦��
	}

	  /* �����1��3��5���˵���Ϣ */
	for (i = 0; i < 5; i += 2) {
		cout << "��" << i + 1 << "���˵�ѧ�źͳɼ�Ϊ" << endl;
		(*(p + i)).display();
	}

	return 0;
}