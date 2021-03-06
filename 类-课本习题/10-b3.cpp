// 1752762 计1班 魏鹳达

/* 允许添加需要的头文件、宏定义等 */
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string.h>
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
		content = new char[(len / LEN_STR_PER + 1)*LEN_STR_PER];
		//if (content == NULL)
		//	return;
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
		content = new char[(len / LEN_STR_PER + 1)*LEN_STR_PER];
		//if (content == NULL)
		//	return;
		strcpy(content, Ts.content);
	}
	else {
		len = 0;
		content = NULL;
	}
}

istream& operator>>(istream& is, TString& Ts)
{
	char temp[LEN_STR_PER + 1] = "\0";

	if (Ts.content)
		delete[] Ts.content;

	int n = 1;
	streamsize ssize = is.width(LEN_STR_PER);
	is >> temp;
	
	Ts.content = new char[LEN_STR_PER];
	//if (Ts.content == NULL)
	//	return is;
	strcpy(Ts.content, temp);
	Ts.len = strlen(Ts.content);
	is.width(LEN_STR_PER + 1);
	while (is.fail() && Ts.len%LEN_STR_PER == LEN_STR_PER - 1) {	//读满缓冲区/遇到空格会置错误标记 需要继续读
		is.clear();
		is >> temp;

		char *t = new char[(n - 1)*LEN_STR_PER];
		strcpy(t, Ts.content);
		delete[] Ts.content;
		Ts.content = new char[n*LEN_STR_PER];
		n++;
		strcpy(Ts.content, t);
		strcat(Ts.content, temp);
		Ts.len = strlen(Ts.content);
		delete[] t;
	}
	is.width(ssize);
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

	newString.content = new char[(newString.len / LEN_STR_PER + 1)*LEN_STR_PER];
	//if (newString.content = NULL)
	//	exit(-1);

	strcpy(newString.content, Ts1.content);
	strcat(newString.content, Ts2.content);

	return newString;
}

TString operator+(const TString& Ts1, const char c)
{
	TString newString;

	newString.len = Ts1.len + 1;

	newString.content = new char[(newString.len / LEN_STR_PER + 1)*LEN_STR_PER];
	//if (newString.content = NULL)
	//	exit(-1);

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

	newString.content = new char[(newString.len / LEN_STR_PER + 1)*LEN_STR_PER];
	//if (newString.content = NULL)
	//	exit(-1);

	newString.content[0] = c;
	newString.content[1] = '\0';

	if (Ts2.content)
		strcpy(newString.content + 1, Ts2.content);

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

	char *temp = NULL;

	temp = new char[(len / LEN_STR_PER + 1)*LEN_STR_PER];
	//if (temp = NULL)
	//	exit(-1);
	strcpy(temp, content);
	delete[] content;

	len = l;
	content = new char[(len / LEN_STR_PER + 1)*LEN_STR_PER];
	//if (content = NULL)
	//	exit(-1);

	strcpy(content, temp);
	strcat(content, Ts.content);

	delete[] temp;
	return *this;
}

TString& TString::operator+=(const char c)
{
	int l;
	if ((l = len + 1) == 0)		//两个串都为空
		return *this;
	else if (len == 0) {
		content = new char[LEN_STR_PER];
		content[0] = c;
		content[1] = '\0';
		return *this;
	}

	char *temp = new char[(len / LEN_STR_PER + 1)*LEN_STR_PER];
	//if (temp = NULL)
	//	exit(-1);
	strcpy(temp, content);
	delete[] content;

	len = l;
	content = new char[(len / LEN_STR_PER + 1)*LEN_STR_PER];
	//if (content = NULL)
	//	exit(-1);

	strcpy(content, temp);
	content[len - 1] = c;
	content[len] = '\0';

	delete[] temp;
	return *this;
}

TString operator-(const TString& Ts1, const TString& Ts2)
{
	TString newString(Ts1);
	if (Ts1.content == NULL || Ts2.content == NULL)
		return newString;

	int l = 0, lc = Ts2.len;
	char *t;
	if (t = strstr(newString.content, Ts2.content)){	//在内存管理上有些问题例如 长度从 LEN_STR_PER+2 减到 LEN_STR_PER-2 之后再增长时实际不用再次申请了 但自己的实现会再申请一次 有时间的浪费
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

	int lc = Ts.len;
	char *t;
	if (t = strstr(content, Ts.content))
	{
		strcpy(t, t + lc);
		len = strlen(content);
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
		strcpy(content + l, content + l + 1);
	}

	len = strlen(content);

	return *this;
}

TString& TString::operator=(const TString& Ts)
{
	if (this == &Ts)	//考虑自己=自己的情况
		return *this;

	if (Ts.content) {
		len = Ts.len;
		if (content)
			delete[] content;
		content = new char[(len / LEN_STR_PER + 1)*LEN_STR_PER];
		//if (content = NULL)
		//	exit(-1);
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
	if (n == 0) {
		*this = "";
		return *this;
	}
	if (content == NULL || n < 0)
		return *this;
	char *temp = new char[(len / LEN_STR_PER + 1)*LEN_STR_PER];
	//if (temp = NULL)
	//	exit(-1);
	strcpy(temp, content);
	delete[] content;
	content = new char[(n*len / LEN_STR_PER + 1)*LEN_STR_PER];
	content[0] = '\0';
	//if (content = NULL)
	//	exit(-1);
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
	if (n == 0) {
		newTString = "";
		return newTString;
	}

	newTString = *this;
	if (content == NULL || n < 0)
		return newTString;

	delete[] newTString.content;

	newTString.content = new char[(n*len / LEN_STR_PER + 1)*LEN_STR_PER];
	newTString.content[0] = '\0';
	//if (newTString.content = NULL)
	//	exit(-1);
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
