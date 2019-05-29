// 1752762 ��1�� κ�ٴ�
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

/* �˴�������ӱ���Ķ����������������ȫ�ֱ����� */
class Teacher;

/* Student ��Ķ�����ʵ�� */
class Student {
private:
	int num;		//ѧ��
	char name[16];	//����
	char sex;		//�Ա�ֻ���� F/M ���֣���Сд������
	char addr[64];	//��ͥסַ
	//˽�в��ֲ���������κ�����
public:
	Student();
	Student(const int num1, const char *name1, const char sex1, const char *addr1);
	friend ostream &operator<<(ostream &out, const Student &stu);
	//���в���������ӳ�Ա����������ʵ�֣���������������ݳ�Ա����Ԫ����
	Student(Teacher Tea);
	operator Teacher();
};

/* Teacher ��Ķ�����ʵ��(Teacher���в�����������κ����ݳ�Ա����Ա��������Ԫ) */
class Teacher {
private:
	int num;		//����
	char name[16];	//����
	char sex;		//�Ա�ֻ���� F/M ���֣���Сд������
	char addr[64];	//��ͥסַ
	//˽�в��ֲ���������κ�����
public:
	Teacher();
	Teacher(const int num1, const char *name1, const char sex1, const char *addr1);
	friend ostream &operator<<(ostream &out, const Teacher &te);
	friend Student;
	//���в��ֲ���������κ�����
};

/* ----����Student���Ա��������Ԫ����������ʵ��---- */
Student::Student()
{
	num = 1750000;
	strcpy(name, "<ѧ��S>");
	sex = 'M';
	strcpy(addr, "��ƽ·1239��");
}

Student::Student(const int num1, const char *name1, const char sex1, const char *addr1)
{
	num = num1;
	strcpy(name, name1);
	sex = sex1;
	strcpy(addr, addr1);
}

ostream &operator<<(ostream &out, const Student &stu)
{
	out << stu.num << " " << stu.name << " " << stu.sex << " " << stu.addr;
	return out;
}

/* ----����Teacher���Ա��������Ԫ����������ʵ��---- */
Teacher::Teacher()
{
	num = 18000;
	strcpy(name, "<��ʦT>");
	sex = 'M';
	strcpy(addr, "��ƽ·1239���Ժ�¥");
}

Student::Student(Teacher Tea)
{
	num = Tea.num % 1000 + 1750000;
	strcpy(name, Tea.name);
	sex = Tea.sex;
	strcpy(addr, Tea.addr);
	strcat(addr, "**��");
}

Teacher::Teacher(const int num1, const char *name1, const char sex1, const char *addr1)
{
	num = num1;
	strcpy(name, name1);
	sex = sex1;
	strcpy(addr, addr1);
}

ostream &operator<<(ostream &out, const Teacher &te)
{
	out << te.num << " " << te.name << " " << te.sex << " " << te.addr;
	return out;
}

Student::operator Teacher()
{
	Teacher Tea;
	Tea.num = num % 1000 + 18000;
	strcpy(Tea.name, name);
	Tea.sex = sex;
	strcpy(Tea.addr, addr);
	strcat(Tea.addr, "**ѧԺ");
	return Tea;
}

/* ----main������׼��---- */
int main()
{
	Student s1;	//ȱʡֵ - ѧ�ţ�1750000 ������<ѧ��S> �Ա�M ��ַ����ƽ·1239��
	Student s2 = Student( 1751234, "ѧ����", 'M', "�ܰ���·4800��" );
	Teacher t1;	//ȱʡֵ - ���ţ�18000 ������<��ʦT> �Ա�M ��ַ����ƽ·1239���Ժ�¥
	Teacher t2 = Teacher( 18123, "��ʦ��", 'F', "�ܰ���·4800�����Ź�" );

	/* ��ӡԭʼѧ����Ϣ */
	cout << "ѧ����Ϣ��" << s1 << endl;				//���������"ѧ����Ϣ��1750000 <ѧ��S> M ��ƽ·1239��"
	cout << "ѧ����Ϣ��" << s2 << endl;				//���������"ѧ����Ϣ��1751234 ѧ���� M �ܰ���·4800��"
	cout << endl;

	/* ��ӡԭʼ��ʦ��Ϣ */
	cout << "��ʦ��Ϣ��" << t1 << endl;				//���������"��ʦ��Ϣ��18000 <��ʦT> M ��ƽ·1239���Ժ�¥"
	cout << "��ʦ��Ϣ��" << t2 << endl;				//���������"��ʦ��Ϣ��18123 ��ʦ�� F �ܰ���·4800�����Ź�"
	cout << endl;

	/* ѧ��ת��ʦ���ԣ�
	   ѧ��ת���Ź��򣺹��� = 18 + ѧ�ź���λ
	   ����ת������ԭ��ת��
	   �Ա�ת������ԭ��ת��
	   ��ַת������ԭ��ַ���"**ѧԺ"(�������ַ���Խ��)    */
	t1 = s2;
	cout << "ѧ����Ϣ��" << s2 << endl;				//���������"ѧ����Ϣ��1751234 ѧ���� M �ܰ���·4800��"
	cout << "ת��Ϊ��ʦ����Ϣ��" << t1 << endl;		//���������"ת��Ϊ��ʦ����Ϣ��18234 ѧ���� M �ܰ���·4800��**ѧԺ"
	cout << endl;

	/* ��ʦתѧ�����ԣ�
	   ����תѧ�Ź���ѧ�� = 1750 + ���ź���λ
	   ����ת������ԭ��ת��
	   �Ա�ת������ԭ��ת��
	   ��ַת������ԭ��ַ���"**��"(�������ַ���Խ��)    */
	s1 = t2;
	cout << "��ʦ��Ϣ��" << t2 << endl;				//���������"��ʦ��Ϣ��18123 ��ʦ�� F �ܰ���·4800�����Ź�"
	cout << "ת��Ϊѧ������Ϣ��" << s1 << endl;		//���������"ת��Ϊѧ������Ϣ��1750123 ��ʦ�� F �ܰ���·4800�����Ź�**��"
	cout << endl;

	return 0;
}
