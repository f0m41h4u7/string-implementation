#include "str.hpp"
#include <iostream>
#include <memory>
#include <cstdlib>

int main()
{
	DecimalString dec1("1337");
	DecimalString dec2("31337");

	std::cout << std::stoi(dec1.getString()) << " " << std::stoi(dec2.getString()) << std::endl;
	if (dec2 > dec1) std::cout << "yes" << std::endl;
	else std::cout << "no" << std::endl;
	return 0;	
}
