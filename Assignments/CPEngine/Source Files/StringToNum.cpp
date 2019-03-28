#include<string.h>
#include<ctype.h>
#include<math.h>
#include<iostream>
using namespace std;
namespace Conversion {

	/**
	Converts the digit of string to a number

	@param s: a character Pointer
	@return the number from string
	*/
	int StoN(char* s) {
		int len = int (strlen(s));
		int num = 0;
		for (int i = 0; i < len; i++) {
			if (isdigit(s[i])) {
				num = (num * 10) + (s[i] - '0');
			}
		}
		return num;
	}

	/**
	Converts the digit to string

	@param n: a number to convert into string
	@return the string
	*/
	char* NtoS(int n) {
		int len = n > 0 ? int(log10(double(n)) + 1) : 1;
		char* s = new char[len + 1];
		for (int i = len - 1; i > -1; i--) {
			s[i] = char(n % 10 + 0x30);
			n = n / 10;
		}
		s[len] = '\0';
		return s;
	}
}