#include "pch.h"
#include <iostream>
#include "limits.h"
#include <typeinfo>
using namespace std;
void Dash(int n) {
	for (int i = 0; i < n; i++) {
		printf("-");
	}
	cout << endl;
}
int main()
{
	char c;
	signed char sc;
	unsigned char uc;

	short s;
	unsigned short us;
	int i;
	unsigned int ui;
	long l;
	unsigned long ul;
	long long ll;
	unsigned long long ull;

	float f;
	double d;
	long double ld;
	cout << "Data types:\n\n";

	cout << "Name: " << typeid(c).name() << endl;
	cout << "Size (b): " << CHAR_BIT << endl;
	cout << "Minimum value: " << CHAR_MIN << endl;
	cout << "Maximum value: " << CHAR_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(sc).name() << endl;
	cout << "Size (b): " << CHAR_BIT << endl;
	cout << "Minimum value: " << SCHAR_MIN << endl;
	cout << "Maximum value: " << SCHAR_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(uc).name() << endl;
	cout << "Size (b): " << CHAR_BIT << endl;
	cout << "Minimum value: " << "0" << endl;
	cout << "Maximum value: " << UCHAR_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(s).name() << endl;
	cout << "Size (b): " << sizeof(short) << endl;
	cout << "Minimum value: " << SHRT_MIN << endl;
	cout << "Maximum value: " << SHRT_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(us).name() << endl;
	cout << "Size (b): " << sizeof(unsigned short) << endl;
	cout << "Minimum value: " << "0" << endl;
	cout << "Maximum value: " << USHRT_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(i).name() << endl;
	cout << "Size (b): " << sizeof(int)<< endl;
	cout << "Minimum value: " << INT_MIN << endl;
	cout << "Maximum value: " << INT_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(ui).name() << endl;
	cout << "Size (b): " << sizeof(unsigned int)<< endl;
	cout << "Minimum value: " << "0" << endl;
	cout << "Maximum value: " << UINT_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(l).name() << endl;
	cout << "Size (b): " << sizeof(long)<< endl;
	cout << "Minimum value: " << LONG_MIN << endl;
	cout << "Maximum value: " << LONG_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(ul).name() << endl;
	cout << "Size (b): " << sizeof(unsigned long)<< endl;
	cout << "Minimum value: " << "0" << endl;
	cout << "Maximum value: " << ULONG_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(ll).name() << endl;
	cout << "Size (b): " << sizeof(long long)<< endl;
	cout << "Minimum value: " << LLONG_MIN << endl;
	cout << "Maximum value: " << LLONG_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(ull).name() << endl;
	cout << "Size (b): " << sizeof(unsigned long long) << endl;
	cout << "Minimum value: " << "0" << endl;
	cout << "Maximum value: " << ULLONG_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(f).name() << endl;
	cout << "Size (b): " << sizeof(float)<< endl;
	cout << "Minimum value: " << FLT_MIN << endl;
	cout << "Maximum value: " << FLT_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(d).name() << endl;
	cout << "Size (b): " << sizeof(double)<< endl;
	cout << "Minimum value: " << DBL_MIN << endl;
	cout << "Maximum value: " << DBL_MAX << endl;
	Dash(30);
	cout << "Name: " << typeid(ld).name() << endl;
	cout << "Size (b): " << sizeof(long double) << endl;
	cout << "Minimum value: " << LDBL_MIN << endl;
	cout << "Maximum value: " << LDBL_MAX << endl;
	Dash(30);
}

