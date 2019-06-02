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
		TString& operator*(const int n);
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
//#define LEN_STR_PER 16