#include <iostream>
#define CATCH_CONFIG_MAIN
#include "../../../../catch.hpp"
#include "../MyString/CMyString.h"

TEST_CASE("Creating MyString")
{
	WHEN("Create without args")
	{
		CMyString myStr = CMyString();
		THEN("Len = 0, str is empty")
		{
			CHECK(myStr.GetLength() == 0);
			CHECK(std::string(myStr.GetStringData()).empty());
		}
	}

	WHEN("Create with char* str")
	{
		const char* str = "Some text";
		CMyString myStr = CMyString(str);
		THEN("Str will has end symbol and length == text.length")
		{
			CHECK(strcmp(myStr.GetStringData(), str) == 0);
			CHECK(myStr.GetLength() == strlen(str));
		}
	}

	WHEN("Creating char* str contains nulling string code")
	{
		const char* str = "Some \0 text";
		CMyString myStr = CMyString(str);
		THEN("Str will has end symbol and length == text.length")
		{
			CHECK(strcmp(myStr.GetStringData(), str) == 0);
			CHECK(myStr.GetLength() == strlen(str));
		}
	}

	WHEN("Create with char* str with length")
	{
		const char* str = "Some text";
		CMyString myStr = CMyString(str, strlen(str));
		THEN("Str will has end symbol and length == text.length")
		{
			CHECK(strcmp(myStr.GetStringData(), str) == 0);
			CHECK(myStr.GetLength() == strlen(str));
		}
	}

	WHEN("Use copy constructor")
	{
		const char* str = "Some text";
		CMyString myStr1 = CMyString(str);
		CMyString myStr2 = CMyString(myStr1);
		THEN("myStr2 will contains same symbols as mystr1")
		{
			CHECK(myStr1.GetLength() == myStr2.GetLength());
			CHECK(strcmp(myStr1.GetStringData(), myStr2.GetStringData()) == 0);
		}
	}

	WHEN("Use move constructor")
	{
		const char* str = "Some text";
		CMyString myStr1 = CMyString(str);
		CMyString myStr2 = CMyString(std::move(myStr1));
		THEN("myStr2 will contains same symbols as mystr1, mystr1 is empty")
		{
			CHECK(myStr1.GetLength() == 0);
			CHECK(strcmp(myStr1.GetStringData(), "") == 0);
			CHECK(strcmp(myStr2.GetStringData(), "Some text") == 0);
		}
	}

	WHEN("Create with STL string")
	{
		std::string text = "Some text";
		CMyString myStr(text);
		THEN("myStr will contains same symbols as STL text")
		{
			CHECK(myStr.GetLength() == text.size());
			CHECK(strcmp(myStr.GetStringData(), text.c_str()) == 0);
		}
	}

	WHEN("Creating STL string contain nulling string code")
	{
		std::string text = "Some\0 text";
		CMyString myStr(text);
		THEN("myStr will contains same symbols as STL text")
		{
			CHECK(myStr.GetLength() == text.size());
			CHECK(strcmp(myStr.GetStringData(), text.c_str()) == 0);
		}
	}
}

TEST_CASE("Getting substr")
{
	WHEN("Getting substr success")
	{
		const char* str = "Some text";
		CMyString myStr = CMyString(str);
		CMyString substr = myStr.SubString(2, 5);
		THEN("Sub string is correct")
		{
			CHECK(strcmp(substr.GetStringData(), "me te") == 0);
		}
	}

	WHEN("Start > length of str")
	{
		const char* str = "Some text";
		CMyString myStr = CMyString(str);
		THEN("Will throw exception")
		{
			CHECK_THROWS_WITH(myStr.SubString(15, 5), "Start of sub string bigger length of string");
		}
	}

	WHEN("Count to get > strlen - start")
	{
		const char* str = "Some text";
		CMyString myStr = CMyString(str);
		CMyString substr = myStr.SubString(5, 10);
		THEN("Sub string will contain symbols after start")
		{
			CHECK(strcmp(substr.GetStringData(), "text") == 0);
		}
	}
}

TEST_CASE("Clear MyString")
{
	WHEN("MyString is empty")
	{
		CMyString myStr = CMyString();
		myStr.Clear();
		THEN("MyString is empty")
		{
			CHECK(strcmp(myStr.GetStringData(), "") == 0);
			CHECK(myStr.GetLength() == 0);
		}
	}

	WHEN("MyString contain some symbols")
	{
		const char* str = "Some text";
		CMyString myStr = CMyString(str);
		myStr.Clear();
		THEN("MyString will empty")
		{
			CHECK(strcmp(myStr.GetStringData(), "") == 0);
			CHECK(myStr.GetLength() == 0);
		}
	}
}

TEST_CASE("Operator =")
{
	WHEN("MyString = with copy another MyString")
	{
		const char* str = "Some text";
		CMyString myStr1 = CMyString();
		CMyString myStr2 = CMyString(str);
		myStr1 = myStr2;
		THEN("Second will contains symbols from first")
		{
			CHECK(strcmp(myStr1.GetStringData(), "Some text") == 0);
			CHECK(strcmp(myStr2.GetStringData(), "Some text") == 0);
		}
	}

	WHEN("MyString = self")
	{
		CMyString myStr = CMyString("Some text");
		myStr = myStr;
		THEN("Without change")
		{
			CHECK(strcmp(myStr.GetStringData(), "Some text") == 0);
		}
	}

	WHEN("MyString move with =")
	{
		const char* str = "Some text";
		CMyString myStr1 = CMyString(str);
		CMyString myStr2 = std::move(myStr1);
		THEN("Second will contains symbols from first, first will empty")
		{
			CHECK(myStr1.GetLength() == 0);
			CHECK(strcmp(myStr1.GetStringData(), "") == 0);
			CHECK(strcmp(myStr2.GetStringData(), "Some text") == 0);
		}
	}

	WHEN("MyString move self")
	{
		CMyString myStr = CMyString("Some text");
		myStr = std::move(myStr);
		THEN("Without change")
		{
			CHECK(strcmp(myStr.GetStringData(), "Some text") == 0);
		}
	}
}

TEST_CASE("Operator +")
{
	WHEN("MyString + MyString")
	{
		CMyString myStr1("Some ");
		CMyString myStr2("text");
		CMyString result = myStr1 + myStr2;
		THEN("Resut contain concatenation of strs")
		{
			CHECK(strcmp(result.GetStringData(), "Some text") == 0);
		}
	}

	WHEN("String + MyString")
	{
		std::string str = "Some ";
		CMyString myStr("text");
		CMyString result = str + myStr;
		THEN("Resut contain concatenation of strs")
		{
			CHECK(strcmp(result.GetStringData(), "Some text") == 0);
		}
	}

	WHEN("Char * + MyString")
	{
		const char* str = "Some ";
		CMyString myStr("text");
		CMyString result = str + myStr;
		THEN("Resut contain concatenation of strs")
		{
			CHECK(strcmp(result.GetStringData(), "Some text") == 0);
		}
	}
}

TEST_CASE("OOperator +=")
{
	WHEN("Success concatination")
	{
		CMyString myStr1("Some ");
		CMyString myStr2("text");
		myStr1 += myStr2;
		THEN("MyStr will contain concatination")
		{
			CHECK(strcmp(myStr1.GetStringData(), "Some text") == 0);
		}
	}

	WHEN("myStr += empty")
	{
		CMyString myStr1("Some ");
		CMyString myStr2;
		myStr1 += myStr2;
		THEN("MyStr not change")
		{
			CHECK(strcmp(myStr1.GetStringData(), "Some ") == 0);
		}
	}

	WHEN("empty += myStr")
	{
		CMyString myStr1;
		CMyString myStr2("text");
		myStr1 += myStr2;
		THEN("MyStr contain symbols from myStr2")
		{
			CHECK(strcmp(myStr1.GetStringData(), "text") == 0);
		}
	}
}

TEST_CASE("Operator ==")
{
	WHEN("MyStr is equal")
	{
		CMyString myStr1("Some");
		CMyString myStr2("Some");
		THEN("Will true")
		{
			CHECK(myStr1 == myStr2);
		}
	}

	WHEN("MyStr are different in len")
	{
		CMyString myStr1("Some");
		CMyString myStr2("Some ddd");
		THEN("Will false")
		{
			CHECK(!(myStr1 == myStr2));
		}
	}

	WHEN("MyStr are different in symbols")
	{
		CMyString myStr1("Some");
		CMyString myStr2("Ssss");
		THEN("Will false")
		{
			CHECK(!(myStr1 == myStr2));
		}
	}
}

TEST_CASE("Operator !=")
{
	WHEN("MyStr is equal")
	{
		CMyString myStr1("Some");
		CMyString myStr2("Some");
		THEN("Will false")
		{
			CHECK(!(myStr1 != myStr2));
		}
	}

	WHEN("MyStr are different in len")
	{
		CMyString myStr1("Some");
		CMyString myStr2("Some ddd");
		THEN("Will true")
		{
			CHECK(myStr1 != myStr2);
		}
	}

	WHEN("MyStr are different in symbols")
	{
		CMyString myStr1("Some");
		CMyString myStr2("Ssss");
		THEN("Will true")
		{
			CHECK(myStr1 != myStr2);
		}
	}
}

TEST_CASE("Operator <")
{
	WHEN("First < second")
	{
		CMyString myStr1("abcd");
		CMyString myStr2("zxyq");
		THEN("Will true")
		{
			CHECK(myStr1 < myStr2);
		}
	}

	WHEN("First > second")
	{
		CMyString myStr1("zxyq");
		CMyString myStr2("abcd");
		THEN("Will false")
		{
			CHECK(!(myStr1 < myStr2));
		}
	}

	WHEN("First = second")
	{
		CMyString myStr1("Some");
		CMyString myStr2("Some");
		THEN("Will false")
		{
			CHECK(!(myStr1 < myStr2));
		}
	}
}

TEST_CASE("Operator >")
{
	WHEN("First < second")
	{
		CMyString myStr1("abcd");
		CMyString myStr2("zxyq");
		THEN("Will false")
		{
			CHECK(!(myStr1 > myStr2));
		}
	}

	WHEN("First > second")
	{
		CMyString myStr1("zxyq");
		CMyString myStr2("abcd");
		THEN("Will true")
		{
			CHECK(myStr1 > myStr2);
		}
	}

	WHEN("First = second")
	{
		CMyString myStr1("Some");
		CMyString myStr2("Some");
		THEN("Will false")
		{
			CHECK(!(myStr1 > myStr2));
		}
	}
}

TEST_CASE("Operator <=")
{
	WHEN("First < second")
	{
		CMyString myStr1("abcd");
		CMyString myStr2("zxyq");
		THEN("Will true")
		{
			CHECK(myStr1 <= myStr2);
		}
	}

	WHEN("First > second")
	{
		CMyString myStr1("zxyq");
		CMyString myStr2("abcd");
		THEN("Will false")
		{
			CHECK(!(myStr1 <= myStr2));
		}
	}

	WHEN("First = second")
	{
		CMyString myStr1("Some");
		CMyString myStr2("Some");
		THEN("Will true")
		{
			CHECK(myStr1 <= myStr2);
		}
	}
}

TEST_CASE("Operator >=")
{
	WHEN("First < second")
	{
		CMyString myStr1("abcd");
		CMyString myStr2("zxyq");
		THEN("Will false")
		{
			CHECK(!(myStr1 >= myStr2));
		}
	}

	WHEN("First > second")
	{
		CMyString myStr1("zxyq");
		CMyString myStr2("abcd");
		THEN("Will true")
		{
			CHECK(myStr1 >= myStr2);
		}
	}

	WHEN("First = second")
	{
		CMyString myStr1("Some");
		CMyString myStr2("Some");
		THEN("Will true")
		{
			CHECK(myStr1 >= myStr2);
		}
	}
}

TEST_CASE("Operator []")
{
	WHEN("Read value")
	{
		CMyString myStr("Some text");
		THEN("Get char in index")
		{
			CHECK(myStr[3] == 'e');
		}
	}

	WHEN("Index not in range")
	{
		CMyString myStr("Some text");
		THEN("Will be exception")
		{
			CHECK_THROWS_WITH(myStr[20], "Index out of range");
			CHECK_THROWS_WITH(myStr[-8], "Index out of range");
		}
	}

	WHEN("Set new value")
	{
		CMyString myStr("Some text");
		myStr[3] = 'm';
		THEN("Get char in index")
		{
			CHECK(strcmp(myStr.GetStringData(), "Somm text") == 0);
		}
	}

	WHEN("Set index not in range")
	{
		CMyString myStr("Some text");
		THEN("Get char in index")
		{
			CHECK_THROWS_WITH((myStr[20] = '2'), "Index out of range");
			CHECK_THROWS_WITH((myStr[-8] = '2'), "Index out of range");
		}
	}
}

TEST_CASE("Operator >>")
{
	WHEN("Read till space")
	{
		std::istringstream in("Some text");
		CMyString myStr;
		in >> myStr;
		THEN("Will read symbols before space")
		{
			CHECK(strcmp(myStr.GetStringData(), "Some") == 0);
		}
	}

	WHEN("Read till eoln")
	{
		std::istringstream in("Sometext\nanothertext");
		CMyString myStr;
		in >> myStr;
		THEN("Will read symbols before eoln")
		{
			CHECK(strcmp(myStr.GetStringData(), "Sometext") == 0);
		}
	}

	WHEN("Read till eof")
	{
		std::istringstream in("Sometext");
		CMyString myStr;
		in >> myStr;
		THEN("Will read symbols before eof")
		{
			CHECK(strcmp(myStr.GetStringData(), "Sometext") == 0);
		}
	}
}

TEST_CASE("Operator <<")
{
	WHEN("Succes writting")
	{
		std::ostringstream out;
		CMyString myStr("Some text");
		out << myStr;
		THEN("Will write symbols from MyString")
		{
			CHECK(out.str() == myStr.GetStringData());
		}
	}

	WHEN("MyString is empty")
	{
		std::ostringstream out;
		CMyString myStr;
		out << myStr;
		THEN("Stream not change")
		{
			CHECK(out.str().empty());
		}
	}

	WHEN("MyString has null symbol inside")
	{
		std::ostringstream out;
		CMyString myStr("Some\0 text");
		out << myStr;
		THEN("Will write symbols from MyString")
		{
			CHECK(out.str() == myStr.GetStringData());
		}
	}
}
