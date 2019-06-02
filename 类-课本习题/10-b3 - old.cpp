// 1752762 计1班 魏鹳达

/* 允许添加需要的头文件、宏定义等 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include "10-b3.h"
using namespace std;

/* 给出 TString 类的所有成员函数的体外实现 */
TString::~TString()
{
	delete[] content;
	len = 0;
}

TString::TString()
{
	content = NULL;
	len = 0;
}

TString::TString(const char* s)
{
	if (s) {
		if ((len = strlen(s)) == 0) {
			content = NULL;
			return;
		}
		content = new char[len + 1];
		if (content = NULL)
			exit(-1);
		strcpy(content, s);
	}
	else {
		len = 0;
		content = NULL;
	}
}

TString::TString(const TString& Ts)
{
	if (Ts.content) {
		len = Ts.len;
		content = new char[len + 1];
		if (content = NULL)
			exit(-1);
		strcpy(content, Ts.content);
	}
	else {
		len = 0;
		content = NULL;
	}
}

istream& operator>>(istream& is, TString& Ts)
{
	char temp[128];	//默认输入长度不超过127
	is >> temp;
	if (is.fail()) {
		temp[128] = '\0';
	}
	if (Ts.content)
		delete[] Ts.content;
	Ts.len = strlen(temp);
	Ts.content = new char[Ts.len + 1];
	if (Ts.content = NULL)
		exit(-1);
	strcpy(Ts.content, temp);
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

	newString.len = Ts1.len + Ts2.len;

	if (newString.len == 0) {	//两个串都为空
		newString.content = NULL;
		return newString;
	}

	newString.content = new char[newString.len + 1]{ '\0' };
	if (newString.content = NULL)
		exit(-1);

	if (Ts1.content)
		strcpy(newString.content, Ts1.content);
	if (Ts2.content)
		strcat(newString.content, Ts2.content);

	return newString;
}

TString operator+(const TString& Ts1, const char c)
{
	TString newString;

	newString.len = Ts1.len + 1;

	newString.content = new char[newString.len + 1];
	if (newString.content = NULL)
		exit(-1);

	if (Ts1.content)
		strcpy(newString.content, Ts1.content);

	newString.content[newString.len - 1] = c;
	newString.content[newString.len] = '\0';

	return newString;
}

TString operator+(const char c, const TString& Ts2)
{
	TString newString;

	newString.len = Ts2.len + 1;

	newString.content = new char[newString.len + 1];
	if (newString.content = NULL)
		exit(-1);

	newString.content[0] = c;
	newString.content[1] = '\0';

	if (Ts2.content)
		strcpy(newString.content + 1, Ts2.content);


	return newString;
}

TString& TString::operator+=(const TString& Ts)
{
	int l = len + Ts.len;

	if (l == 0)		//两个串都为空
		return *this;

	char *temp = NULL;

	if (content) {
		temp = new char[len + 1];
		if (temp = NULL)
			exit(-1);
		strcpy(temp, content);
		delete[] content;
	}
	else {
		len = l;
		*this = Ts;
		return *this;
	}

	len = l;

	content = new char[len + 1];
	if (content = NULL)
		exit(-1);

	strcpy(content, temp);
	if (Ts.content)
		strcat(content, Ts.content);

	delete[] temp;
	return *this;
}

TString& TString::operator+=(const char c)
{
	int l = len + 1;

	char *temp = NULL;

	if (content) {
		temp = new char[len + 1];
		if (temp = NULL)
			exit(-1);
		strcpy(temp, content);
		delete[] content;
	}
	else {
		content = new char[2]{ '\0' };
		if (content = NULL)
			exit(-1);
		content[0] = c;
		len = 1;
		return *this;
	}
	len = l;

	content = new char[len + 1]{ '\0' };
	if (content = NULL)
		exit(-1);

	strcpy(content, temp);
	content[len - 1] = c;

	delete[] temp;
	return *this;
}

TString operator-(const TString& Ts1, const TString& Ts2)
{
	TString newString(Ts1);
	if (Ts1.content == NULL || Ts2.content == NULL)
		return newString;

	int l = 0, lc = strlen(Ts2.content);
	char *t;
	if (t = strstr(newString.content, Ts2.content)){
		l = t - newString.content;
		strcpy(newString.content + l, newString.content + l + lc);
	}

	newString.len = strlen(newString.content);
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
		strcpy(newString.content + l, newString.content + l + 1);
	}

	newString.len = strlen(newString.content);
	return newString;
}

TString& TString::operator-=(const TString& Ts)
{
	if (content == NULL || Ts.content == NULL)
		return *this;

	int l = 0, lc = strlen(Ts.content);
	char *t;
	if (t = strstr(content, Ts.content))
	{
		l = t - content;
		strcpy(content + l, content + l + lc);
	}

	len = strlen(content);

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
		strcpy(content + l, content + l + 1);
	}

	len = strlen(content);

	return *this;
}







TString& TString::operator=(const TString& Ts)
{
	if (this == &Ts)
		return *this;

	if (Ts.content) {
		len = Ts.len;
		if (content)
			delete[] content;
		content = new char[len + 1];
		if (content = NULL)
			exit(-1);
		strcpy(content, Ts.content);
	}
	else {
		len = 0;
		if (content)
			delete[] content;
		content = NULL;
	}
	return *this;
}

TString& TString::operator*=(const int n)
{
	if (content == NULL || n < 0)
		return *this;
	char *temp = new char[len + 1];
	if (temp = NULL)
		exit(-1);
	strcpy(temp, content);
	delete[] content;
	content = new char[n*len + 1]{ '\0' };
	if (content = NULL)
		exit(-1);
	int i;
	for (i = 0; i < n; i++)
		strcat(content, temp);
	len *= n;
	delete[] temp;
	return *this;
}

TString& TString::operator*(const int n)
{
	static TString newTString;
	newTString = *this;
	if (content == NULL || n < 0)
		return newTString;

	delete[] newTString.content;
	newTString.content = new char[n*len + 1]{ '\0' };
	if (newTString.content = NULL)
		exit(-1);
	int i;
	for (i = 0; i < n; i++)
		strcat(newTString.content, content);
	newTString.len *= n;
	return newTString;
}

TString& TString::operator!()
{
	static TString newString;
	newString = *this;
	if (content == NULL)
		return newString;
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
