// 1752762 ��1�� κ�ٴ�
#include <iostream>
using namespace std;

/* ��ȫTString��Ķ��壬���г�Ա����������ʵ�֣���Ҫ�ڴ˴�����ʵ�� */
class TString {
	private:
		char *content;
		int   len;
		/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */
	public:
		/* ������Ҫ������������ݳ�Ա����Ա��������Ԫ������ */
		TString();
		TString(const char* s);
		TString(TString& Ts);
		friend istream& operator>>(istream& is, TString& Ts);
		friend ostream& operator<<(ostream& os, TString& Ts);
		char* c_str();
		TString operator+(const TString& Ts);
		TString& operator+=(const TString& Ts);
		TString operator-(const TString& Ts);
		TString& operator-=(const TString& Ts);
		TString& operator=(const TString& Ts);
		TString& operator*=(const TString& Ts);
		TString& operator!();
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

/* ���������ȫ�ֺ�����Ҫ������д�ڴ˴� */
int TStringLen(const TString& Ts);
/* �������Ҫ�ĺ궨�塢ֻ��ȫ�ֱ����ȣ�д�ڴ˴� */
