// 1752762 计1班 魏鹳达
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
using namespace std;

/* 此处允许添加必须的定义或声明（不允许全局变量） */
class Teacher;

/* Student 类的定义与实现 */
class Student {
private:
	int num;		//学号
	char name[16];	//姓名
	char sex;		//性别，只能是 F/M 两种，大小写不敏感
	char addr[64];	//家庭住址
	//私有部分不允许添加任何内容
public:
	Student();
	Student(const int num1, const char *name1, const char sex1, const char *addr1);
	friend ostream &operator<<(ostream &out, const Student &stu);
	friend Teacher;
	//公有部分不允许添加任何内容
};

/* ----给出Student类成员函数及友元函数的体外实现---- */
Student::Student()
{
	num = 1750000;
	strcpy(name, "<学生S>");
	sex = 'M';
	strcpy(addr, "四平路1239号");
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

/* Teacher 类的定义与实现 */
class Teacher {
private:
	int num;		//工号
	char name[16];	//姓名
	char sex;		//性别，只能是 F/M 两种，大小写不敏感
	char addr[64];	//家庭住址
	//私有部分不允许添加任何内容
public:
	Teacher();
	Teacher(const int num1, const char *name1, const char sex1, const char *addr1);
	friend ostream &operator<<(ostream &out, const Teacher &te);
	//公有部分允许添加成员函数（体外实现），不允许添加数据成员、友元声明
	Teacher(Student stu);
	operator Student();
};

/* ----给出Teacher类成员函数及友元函数的体外实现---- */
Teacher::Teacher()
{
	num = 18000;
	strcpy(name, "<教师T>");
	sex = 'M';
	strcpy(addr, "四平路1239号衷和楼");
}

Teacher::Teacher(Student stu)
{
	num = stu.num % 1000 + 18000;
	strcpy(name, stu.name);
	sex = stu.sex;
	strcpy(addr, stu.addr);
	strcat(addr, "**学院");
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

Teacher::operator Student()
{
	Student stu;
	stu.num = num % 1000 + 1750000;
	strcpy(stu.name, name);
	stu.sex = sex;
	strcpy(stu.addr, addr);
	strcat(stu.addr, "**室");
	return stu;
}

/* ----main函数不准动---- */
int main()
{
	Student s1;	//缺省值 - 学号：1750000 姓名：<学生S> 性别：M 地址：四平路1239号
	Student s2 = Student( 1751234, "学生甲", 'M', "曹安公路4800号" );
	Teacher t1;	//缺省值 - 工号：18000 姓名：<教师T> 性别：M 地址：四平路1239号衷和楼
	Teacher t2 = Teacher( 18123, "教师乙", 'F', "曹安公路4800号智信馆" );

	/* 打印原始学生信息 */
	cout << "学生信息：" << s1 << endl;				//期望输出："学生信息：1750000 <学生S> M 四平路1239号"
	cout << "学生信息：" << s2 << endl;				//期望输出："学生信息：1751234 学生甲 M 曹安公路4800号"
	cout << endl;

	/* 打印原始教师信息 */
	cout << "教师信息：" << t1 << endl;				//期望输出："教师信息：18000 <教师T> M 四平路1239号衷和楼"
	cout << "教师信息：" << t2 << endl;				//期望输出："教师信息：18123 教师乙 F 曹安公路4800号智信馆"
	cout << endl;

	/* 学生转教师测试：
	学号转工号规则：工号 = 18 + 学号后三位
	姓名转换规则：原样转换
	性别转换规则：原样转换
	地址转换规则：原地址后加"**学院"(不考虑字符串越界)    */
	t1 = s2;
	cout << "学生信息：" << s2 << endl;				//期望输出："学生信息：1751234 学生甲 M 曹安公路4800号"
	cout << "转换为教师的信息：" << t1 << endl;		//期望输出："转换为教师的信息：18234 学生甲 M 曹安公路4800号**学院"
	cout << endl;

	/* 教师转学生测试：
	工号转学号规则：学号 = 1750 + 工号后三位
	姓名转换规则：原样转换
	性别转换规则：原样转换
	地址转换规则：原地址后加"**室"(不考虑字符串越界)    */
	s1 = t2;
	cout << "教师信息：" << t2 << endl;				//期望输出："教师信息：18123 教师乙 F 曹安公路4800号智信馆"
	cout << "转换为学生的信息：" << s1 << endl;		//期望输出："转换为学生的信息：1750123 教师乙 F 曹安公路4800号智信馆**室"
	cout << endl;

	return 0;
}
