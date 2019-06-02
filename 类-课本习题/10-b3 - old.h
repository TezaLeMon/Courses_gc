// 1752762 计1班 魏鹳达
#include <iostream>
using namespace std;

/* 补全TString类的定义，所有成员函数均体外实现，不要在此处体内实现 */
class TString {
	private:
		char *content;
		int   len;
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

/* 如果有其它全局函数需要声明，写于此处 */
int TStringLen(const TString& Ts);
/* 如果有需要的宏定义、只读全局变量等，写于此处 */
//#define LEN_STR_PER 16