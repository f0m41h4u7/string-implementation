#include "str.hpp"
#include <iostream>

int main()
{
//	char* s = "abcd";
	String* str = new String("abcd");
	std::cout << str->getString();
	delete str;

	return 0;	
}
