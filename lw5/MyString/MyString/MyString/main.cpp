#include <iostream>
#include "CMyString.h"

int main()
{
	const char* stri = "Some";
	CMyString str(stri);
	CMyString str1("Hello1 Hello World!!!!!!!");
	str += str1;
}
