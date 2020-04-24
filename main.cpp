#include "str.hpp"
#include <iostream>
#include <cstring>
#include <chrono> 
#include <regex>
#include <string>

using namespace std::chrono;

const std::regex exprRegex("arr\[[0-9]+\][+\*\-]arr\[[0-9]+\]");
const std::regex cleanRegex("arr\[[0-9]+\]clean");
const std::regex lengthRegex("arr\[[0-9]+\]len");
const std::regex equalityRegex("arr\[[0-9]+\]==arr\[[0-9]+\]");

inline bool isInteger(const std::string & s) {
	if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
	char * p;
	std::strtol(s.c_str(), &p, 10);
	return (*p == 0);
}

void printHelp() {
	std::cout << "./interactiveTest [-h] -l <number> --  simple interactive test program for testing String class.\n\nwhere:\n\t-h  show this help text\n\t-l  number of elements in String[] to test\n\nExample: ./interactiveTest -l 42\n\n";
	exit(0);
}

int main (int argc, char** argv) {
	if ((argc == 2) && (!strcmp(argv[1], "-h"))) printHelp();

	if (argc != 3) {
		std::cout << "Wrong argument amount.\nType -h to get help.\n";
		return 1;
	} 
	
	if ((strcmp(argv[1], "-l")) || (!isInteger(argv[2]))) {
		std::cout << "Wrong arguments.\nType -h to get help.\n";
		return 1;
	}

	char* end;
        size_t len = std::strtol(argv[2], &end, 10);

	std::cout << "Allocating memory for String[" << len <<"]...\n";
	auto start = high_resolution_clock::now();
	//auto arr = std::make_unique<String*[]>(len);
	String* arr[len];
	auto stop = high_resolution_clock::now(); 
	std::cout << "Done (" << duration_cast<microseconds>(stop - start).count() << " μs)\n\n";

	std::cout << "Enter initial values for String[] elements:\n";
	for(int i = 0; i < len; ++i) {
		std::cout << "[" << i << "]: ";
		char* str = new char[256];
		scanf("%s", str);
		arr[i] = new String(str);
	}

	std::cout << "Done\n\nCurrent values:\n";
	for(int i = 0; i < len; ++i) std::cout << "arr[" << i << "] = " << arr[i]->getString() << "\n";
	
	std::cout << "\nNow you can start testing!\nUsage:\n\t- Operands: arr[0], ..., arr[n-1]\n\t- Common operators: ==, length, clean\n\t- Decimal operators: +, -, *\n\t- View current values: values\n\t- Add value: add\n\t- Set value: set\n\t- Exit: exit\nExamples:\n\t> arr[0]+arr[1]\n\t> arr[3]len\n\t> arr[0]clean\n\t> arr[2]==arr[4]\n\t> add qwerty\n\t> set arr[1] qwerty\nHave fun!\n\n";

	while(true) {
		std::cout << "> ";
		std::string command;
		std::cin >> command;

		if (!command.compare("exit")) return 0;
		if (!command.compare("values")) {
			std::cout << "Current values:\n";
			for(int i = 0; i < len; ++i) std::cout << "arr[" << i << "] = " << arr[i]->getString() << "\n";
		} 
		else if (std::regex_match(command, exprRegex)) {
			int order1 = std::stoi(command.substr((command.find("[")+1), (command.find("]")-command.find("["))-1));
                        command = command.substr(command.find("[")+1, command.size());
                        int order2 = std::stoi(command.substr((command.find("[")+1), (command.find("]")-command.find("["))-1));
			char op = *std::find_if(command.begin(), command.end(), [](char c) {std::string symbols = "+-*/"; if (symbols.find(c) != std::string::npos) return 1; return 0; });	

			try {
				DecimalString res;
				auto x = static_cast<DecimalString&> (*arr[order1]);
				auto y = static_cast<DecimalString&> (*arr[order2]);
				switch (op) {
					case '+':
						res = x + y;
					case '-':
						res = x - y ;
					case '*':
						res = x * y ;
				}
				std::cout << res.getString() << "\n";
			} catch (std::exception const&) {std::cout << "Wrong types!";}
		} 
		else if (std::regex_match(command, cleanRegex)) {
			int order = std::stoi(command.substr((command.find("[")+1), (command.find("]")-command.find("["))-1));
                        if (order < len) arr[order]->clean();
                        else std::cout << "Order out of range!\n";
		} 
		else if (std::regex_match(command, lengthRegex)) {
			int order = std::stoi(command.substr((command.find("[")+1), (command.find("]")-command.find("["))-1));
			if (order < len) std::cout << arr[order]->getLength() << "\n";
			else std::cout << "Order out of range!\n";
		} 
		else if (std::regex_match(command, equalityRegex)) {
			int order1 = std::stoi(command.substr((command.find("[")+1), (command.find("]")-command.find("["))-1));
			command = command.substr(command.find("[")+1, command.size());
			int order2 = std::stoi(command.substr((command.find("[")+1), (command.find("]")-command.find("["))-1));
				
			bool res = (*arr[order1] == *arr[order2]) ? true : false;
			std::cout << std::boolalpha << res << "\n";
		} 
		else {
			std::cout << "Unknown command!\n";
		}
	}

	return 0;
}
