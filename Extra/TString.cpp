// 1752762 计1班 魏鹳达

/* 允许添加需要的头文件、宏定义等 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
#include <iostream>
using namespace std;

/* 补全TString类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class TString {
private:
	char *content;
	int   len;
	int   capacity;
	/* 根据需要定义所需的数据成员、成员函数、友元函数等 */
public:
	/* 根据需要定义所需的数据成员、成员函数、友元函数等 */
	~TString();
	TString();
	TString(const char* s);
	TString(const TString& Ts);
	friend istream& operator>>(istream& is, TString& Ts);
	friend ostream& operator<<(ostream& os, const TString& Ts);
	const char* c_str() const;
	//TString operator+(const TString& Ts);
	//TString& operator+=(const TString& Ts);
	//TString operator-(const TString& Ts);
	//TString& operator-=(const TString& Ts);

	friend TString operator+(const TString& Ts1, const TString& Ts2);
	friend TString operator+(const TString& Ts1, const char c);
	friend TString operator+(const char c, const TString& Ts2);

	TString& operator+=(const TString& Ts);
	TString& operator+=(const char c);

	friend TString operator-(const TString& Ts1, const TString& Ts2);
	friend TString operator-(const TString& Ts1, const char c);

	TString& operator-=(const TString& Ts);
	TString& operator-=(const char c);

	TString& operator=(const TString& Ts);
	TString& operator*=(const int n);
	TString operator*(const int n);
	TString operator!();
	friend bool operator<(const TString& a, const TString& b);
	friend bool operator<=(const TString& a, const TString& b);
	friend bool operator>(const TString& a, const TString& b);
	friend bool operator>=(const TString& a, const TString& b);
	friend bool operator==(const TString& a, const TString& b);
	friend bool operator!=(const TString& a, const TString& b);
	int length();
	friend int TStringLen(const TString& Ts);
	char& operator[](int n);
};

/* 如果有其它全局函数需要声明，写于此处 */
int TStringLen(const TString& Ts);

/* 如果有需要的宏定义、只读全局变量等，写于此处 */
#define LEN_STR_PER 65536		//每次申请空间的单位 调节此大小会影响空间和时间的平衡

/* 给出 TString 类的所有成员函数的体外实现 */
TString::~TString()
{
	if(content)
		delete[] content;
	len = 0;
	capacity = 0;
}

TString::TString()
{
	content = NULL;
	len = 0;
	capacity = 0;
}

TString::TString(const char* s)
{
	if (s&&s[0] != 0) {
		len = strlen(s);
		capacity = (len / LEN_STR_PER + 1)*LEN_STR_PER;
		content = new char[capacity];
		if (content)
			memcpy(content, s, len + 1);
	}
	else {
		len = 0;
		capacity = 0;
		content = NULL;
	}
}

TString::TString(const TString& Ts)
{
	if (Ts.content) {
		len = Ts.len;
		capacity = Ts.capacity;
		content = new char[capacity];
		if (content)
			memcpy(content, Ts.content, len + 1);
	}
	else {
		len = 0;
		capacity = 0;
		content = NULL;
	}
}

istream& operator>>(istream& is, TString& Ts)
{
	//可以无限读缓冲区 但是效率较慢 已注释
	//char temp[LEN_STR_PER + 1] = "\0";

	//if (Ts.content)
	//	delete[] Ts.content;

	//int n = 1;
	//streamsize ssize = is.width(LEN_STR_PER);
	//is >> temp;

	//Ts.content = new char[LEN_STR_PER];
	////if (Ts.content == NULL)
	////	return is;
	//strcpy(Ts.content, temp);
	//Ts.len = strlen(Ts.content);
	//is.width(LEN_STR_PER + 1);
	//while (is.fail() && Ts.len%LEN_STR_PER == LEN_STR_PER - 1) {	//读满缓冲区/遇到空格会置错误标记 需要继续读
	//	is.clear();
	//	is >> temp;

	//	char *t = new char[(n - 1)*LEN_STR_PER];
	//	strcpy(t, Ts.content);
	//	delete[] Ts.content;
	//	Ts.content = new char[n*LEN_STR_PER];
	//	n++;
	//	strcpy(Ts.content, t);
	//	strcat(Ts.content, temp);
	//	Ts.len = strlen(Ts.content);
	//	delete[] t;
	//}
	//is.width(ssize);

	static char temp[1025] = "\0";	//假设最多1024

	is >> temp;
	Ts.len = strlen(temp);
	int newcapacity = (Ts.len / LEN_STR_PER + 1)*LEN_STR_PER;
	if (Ts.capacity < newcapacity) {
		delete[] Ts.content;
		Ts.content = new char[newcapacity];
		if (Ts.content == NULL) {
			Ts.len = 0;
			Ts.capacity = 0;
			return is;
		}
		Ts.capacity = newcapacity;
	}

	memcpy(Ts.content, temp, Ts.len + 1);

	return is;
}

ostream& operator<<(ostream& os, const TString& Ts)
{
	if (Ts.content)
		cout << Ts.content;
	else
		cout << "<NULL>";
	return os;
}

const char* TString::c_str() const
{
	//if (content == NULL)
	//	return NULL;
	//char* t = new char[len];
	//strcpy(t, content);
	return content;
}

TString operator+(const TString& Ts1, const TString& Ts2)
{
	TString newString;

	if ((newString.len = Ts1.len + Ts2.len) == 0) {	//两个串都为空
		newString.content = NULL;
		return newString;
	}
	else if (Ts1.len == 0) {
		newString = Ts2;
		return newString;
	}
	else if (Ts2.len == 0) {
		newString = Ts1;
		return newString;
	}

	newString.capacity = (newString.len / LEN_STR_PER + 1)*LEN_STR_PER;
	newString.content = new char[newString.capacity];
	if (newString.content) {
		//strcpy(newString.content, Ts1.content);
		//strcat(newString.content, Ts2.content);
		memcpy(newString.content, Ts1.content, Ts1.len);
		memcpy(newString.content + Ts1.len, Ts2.content, Ts2.len + 1);
	}
	else {
		newString.capacity = 0;
		newString.len = 0;
	}

	return newString;
}

TString operator+(const TString& Ts1, const char c)
{
	TString newString;

	newString.len = Ts1.len + 1;
	newString.capacity = (newString.len / LEN_STR_PER + 1)*LEN_STR_PER;
	newString.content = new char[newString.capacity];

	if (newString.content) {
		memcpy(newString.content, Ts1.content, Ts1.len);
		newString.content[newString.len - 1] = c;
		newString.content[newString.len] = '\0';
	}
	else {
		newString.capacity = 0;
		newString.len = 0;
	}

	return newString;
}

TString operator+(const char c, const TString& Ts2)
{
	TString newString;

	newString.len = Ts2.len + 1;
	newString.capacity = (newString.len / LEN_STR_PER + 1)*LEN_STR_PER;
	newString.content = new char[(newString.len / LEN_STR_PER + 1)*LEN_STR_PER];
	//if (newString.content = NULL)
	//	exit(-1);
	if (newString.content) {
		newString.content[0] = c;
		if (Ts2.content)
			memcpy(newString.content + 1, Ts2.content, Ts2.len);
		newString.content[newString.len] = c;
	}
	else {
		newString.capacity = 0;
		newString.len = 0;
	}

	return newString;
}

TString& TString::operator+=(const TString& Ts)
{
	int l;
	if ((l = len + Ts.len) == 0)		//两个串都为空
		return *this;
	else if (len == 0) {
		*this = Ts;
		return *this;
	}
	else if (Ts.len == 0) {
		return *this;
	}

	if (l / LEN_STR_PER > len / LEN_STR_PER) {	//已有空间不足
		char *temp = NULL;

		temp = new char[capacity];
		if (temp) {
			memcpy(temp, content, len + 1);

			delete[] content;

			capacity = (l / LEN_STR_PER + 1)*LEN_STR_PER;
			content = new char[capacity];
			if (content) {
				memcpy(content, temp, len);
				memcpy(content + len, Ts.content, Ts.len + 1);
			}
			len = l;
			delete[] temp;
		}
	}
	else {
		memcpy(content + len, Ts.content, Ts.len + 1);
		len = l;
	}

	return *this;
}

TString& TString::operator+=(const char c)
{
	if (len == 0) {
		content = new char[LEN_STR_PER];
		if (content) {
			content[0] = c;
			content[1] = '\0';
			len = 1;
			capacity = LEN_STR_PER;
		}
		return *this;
	}

	int l = len + 1;

	if (l / LEN_STR_PER > len / LEN_STR_PER) {	//已有空间不足
		char *temp = NULL;

		temp = new char[capacity];
		if (temp) {
			memcpy(temp, content, len + 1);
			delete[] content;

			capacity = (l / LEN_STR_PER + 1)*LEN_STR_PER;
			content = new char[capacity];
			if (content) {
				memcpy(content, temp, len);
				content[len] = c;
				content[len + 1] = '\0';
			}
			len = l;
			delete[] temp;
		}
	}
	else {
		content[len] = c;
		content[len + 1] = '\0';
		len = l;
	}

	return *this;
}

TString operator-(const TString& Ts1, const TString& Ts2)
{
	TString newString(Ts1);
	if (Ts1.content == NULL || Ts2.content == NULL)
		return newString;

	int l = 0, lc = Ts2.len;
	char *t;
	if (t = strstr(newString.content, Ts2.content)) {
		l = t - newString.content;
		memcpy(t, t + lc, newString.len - l - lc + 1);
		newString.len = strlen(newString.content);
	}

	return newString;
}

TString operator-(const TString& Ts1, const char c)
{
	TString newString(Ts1);
	if (Ts1.content == NULL)
		return newString;

	int l = 0;
	char *t;
	if (t = strchr(newString.content, c))
	{
		l = t - newString.content;
		memcpy(t, t + 1, newString.len - l);
		newString.len = strlen(newString.content);
	}

	return newString;
}

TString& TString::operator-=(const TString& Ts)
{
	if (&Ts == this) {
		*this = "";
		return *this;
	}

	if (content == NULL || Ts.content == NULL)
		return *this;

	int lc = Ts.len;
	char *t;
	if (t = strstr(content, Ts.content))
	{
		memcpy(t, t + lc, len - (t - content));
		len = len - lc;
	}

	return *this;
}

TString& TString::operator-=(const char c)
{
	if (content == NULL)
		return *this;

	int l = 0;
	char *t;
	if (t = strchr(content, c))
	{
		l = t - content;
		memcpy(t, t + 1, len - (t - content));
		len -= 1;
	}

	return *this;
}

TString& TString::operator=(const TString& Ts)
{
	if (this == &Ts)	//考虑自己=自己的情况
		return *this;

	if (Ts.content) {
		//len = Ts.len;
		if (content) {
			if (len / LEN_STR_PER < Ts.len / LEN_STR_PER) {
				delete[] content;
				capacity = (Ts.len / LEN_STR_PER + 1)*LEN_STR_PER;
				content = new char[capacity];
				if (content == NULL) {
					len = 0;
					capacity = 0;
					return *this;
				}
			}
		}
		else {
			capacity = (Ts.len / LEN_STR_PER + 1)*LEN_STR_PER;
			content = new char[capacity];
			if (content == NULL) {
				len = 0;
				capacity = 0;
				return *this;
			}
		}
		len = Ts.len;
		memcpy(content, Ts.content, len + 1);
	}
	else {
		len = 0;
		capacity = 0;
		if (content)
			delete[] content;
		content = NULL;
	}
	return *this;
}

TString& TString::operator*=(const int n)
{
	if (n == 0) {
		*this = "";
		return *this;
	}
	if (content == NULL || n < 0)
		return *this;

	if (len / LEN_STR_PER < n*len / LEN_STR_PER) {
		char *temp = new char[capacity];
		if (temp) {
			memcpy(temp, content, len + 1);
			delete[] content;
			capacity = (n * len / LEN_STR_PER + 1)*LEN_STR_PER;
			content = new char[capacity];
			int i;
			for (i = 0; i < n; i++)
				memcpy(content + i * len, temp, len + 1);
			len *= n;
			delete[] temp;
		}
	}
	else {
		int i;
		for (i = 1; i < n; i++)
			memcpy(content + i * len, content, len);
		len *= n;
		content[len] = '\0';
	}

	return *this;
}

TString TString::operator*(const int n)
{
	TString newTString;
	if (content == NULL || n <= 0)
		return newTString;

	newTString.len = n * len;
	newTString.capacity = (n * len / LEN_STR_PER + 1)*LEN_STR_PER;
	newTString.content = new char[capacity];
	if (newTString.content) {
		int i;
		for (i = 0; i < n; i++)
			memcpy(newTString.content + i * len, content, len + 1);
	}
	else {
		newTString.len = 0;
		newTString.capacity = 0;
	}

	return newTString;
}

TString TString::operator!()
{
	TString newString = *this;

	int i;
	char t;
	for (i = 0; i < len / 2; i++) {
		t = newString.content[i];
		newString.content[i] = newString.content[len - i - 1];
		newString.content[len - i - 1] = t;
	}
	return newString;
}

bool operator<(const TString& a, const TString& b)
{
	if (a.content == NULL) {
		if (b.content == NULL)
			return false;
		return true;
	}
	if (b.content == NULL)
		return true;
	return strcmp(a.content, b.content) < 0;
}

bool operator<=(const TString& a, const TString& b)
{
	if (a.content == NULL)
		return true;
	if (b.content == NULL)
		return false;
	return strcmp(a.content, b.content) <= 0;
}

bool operator>(const TString& a, const TString& b)
{
	if (a.content == NULL)
		return false;
	if (b.content == NULL)
		return true;
	return strcmp(a.content, b.content) > 0;
}

bool operator>=(const TString& a, const TString& b)
{
	if (a.content == NULL) {
		if (b.content == NULL)
			return true;
		return false;
	}
	if (b.content == NULL)
		return true;
	return strcmp(a.content, b.content) >= 0;
}

bool operator==(const TString& a, const TString& b)
{
	if (a.content == NULL && b.content == NULL)
		return true;
	if (a.content == NULL || b.content == NULL)
		return false;
	return strcmp(a.content, b.content) == 0;
}

bool operator!=(const TString& a, const TString& b)
{
	if (a.content == NULL && b.content == NULL)
		return false;
	if (a.content == NULL || b.content == NULL)
		return true;
	return strcmp(a.content, b.content) != 0;
}

int TString::length()
{
	return len;
}

char& TString::operator[](int n)
{
	return content[n];
}

/* 如果有需要的其它全局函数的实现，可以写于此处 */
int TStringLen(const TString& Ts)
{
	return Ts.len;
}
