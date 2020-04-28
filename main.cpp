#include "str.hpp"
#include <iostream>
#include <cstring>
#include <regex>
#include <string>
#include <vector>

const std::regex exprRegex("arr\[[0-9]+\][ ]*[+\*\-][ ]*arr\[[0-9]+\]");
const std::regex equalityRegex("arr\[[0-9]+\][ ]==[ ]*arr\[[0-9]+\]");
const std::regex addRegex("add .+");
const std::regex setRegex("set arr\[[0-9]+\] .+");
const std::regex findRegex("find arr\[[0-9]+\] .+");
const std::regex cleanRegex("clean arr\[[0-9]+\]");
const std::regex lenRegex("len arr\[[0-9]+\]");

bool isInteger(const std::string & s) 
{
    if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
    char * p;
    std::strtol(s.c_str(), &p, 10);
    return (*p == 0);
}

void printHelp() 
{
    std::cout << "./interactiveTest [-h] -l <number> --  simple interactive test program ";
    std::cout << "for testing String class.\n\nwhere:\n\t-h  show this help text";
    std::cout << "\n\t-l  number of elements in String[] to test\n\nExample: ";
    std::cout << " ./interactiveTest -l 42\n\n";
    exit(0);
}

int main (int argc, char** argv) 
{
    if ((argc == 2) && (!strcmp(argv[1], "-h"))) printHelp();
    
    if (argc != 3)
    {
        std::cout << "Wrong argument amount.\nType -h to get help.\n";
        return 1;
    }
    
    if ((strcmp(argv[1], "-l")) || (!isInteger(argv[2])))
    {
        std::cout << "Wrong arguments.\nType -h to get help.\n";
        return 1;
    }
    
    char* end;
    size_t len = std::strtol(argv[2], &end, 10);
    
    std::cout << "Allocating memory for String[" << len <<"]...\n";
    std::vector<String*> arr(len);
    std::cout << "Done\n\n";
    
    std::cout << "Enter initial values for String[] elements:\n";
    for(int i = 0; i < len; ++i) 
    {
        std::cout << "[" << i << "]: ";
        char* str = new char[256];
        scanf("%s", str);
        arr[i] = new String(str);
    }
    
    std::cout << "Done\n\nCurrent values:\n";
    for(int i = 0; i < len; ++i) 
        std::cout << "arr[" << i << "] = " << arr[i]->getString() << "\n";
    
    std::cout << "\nNow you can start testing!\nUsage:\n\t- Operands: arr[0], ..., arr[n-1]";
    std::cout << "\n\t- Common operators: ==, length, clean\n\t- Decimal operators:";
    std::cout << "+, -, *\n\t- View current values: values\n\t- Add value: add";
    std::cout << "\n\t- Set value: set\n\t- Find first (Identifiers only): find- Exit:";
    std::cout << "exit\nExamples:\n\t> arr[0]+arr[1]\n\t> arr[3]len\n\t> ";
    std::cout << "arr[0]clean\n\t> arr[2]==arr[4]\n\t> add qwerty\n\t> set arr[1] qwerty";
    std::cout << "\n\t> find arr[66] qwqw\nHave fun!\n\n";
    
    while(true)
    {
        char com[100];
        std::cin.getline(com, sizeof(com));
        std::string command(com);
        
        if (!command.compare("exit")) return 0;
        if (!command.compare("values")) 
        {
            std::cout << "Current values:\n";
            for(int i = 0; i < arr.size(); ++i)
                std::cout << "arr[" << i << "] = " << arr[i]->getString() << "\n";
        }
        
        else if (std::regex_match(command, exprRegex))
        {
            int order1 = std::stoi(command.substr(
                (command.find("[")+1),
                (command.find("]")-command.find("["))-1
            ));
            command = command.substr(
                command.find("[")+1,
                command.size()
            );
            int order2 = std::stoi(command.substr(
                (command.find("[")+1),
                (command.find("]")-command.find("["))-1
            ));
            char op = *std::find_if(
                command.begin(),
                command.end(), 
                [](char c) {
                    std::string symbols = "+-*/"; 
                    if (symbols.find(c) != std::string::npos) return 1; 
                    return 0; 
                }
            );
            
            if((order1 >= len) || (order1 < 0) || (order2 >= len) || (order2 < 0))
            {
                std::cout << "Order out of range!\n";
                continue;
            }
            
            try
            {
                int res = 0;
                auto x = static_cast<DecimalString&> (*arr[order1]);
                auto y = static_cast<DecimalString&> (*arr[order2]);
                switch (op)
                {
                    case '+':
                        res = std::stoi((x + y).getString());
                        break;
                    case '-':
                        res = std::stoi((x - y).getString());
                        break;
                    case '*':
                        res = std::stoi((x * y).getString());
                        break;
                }
                std::cout << res << "\n";
            }
            catch (std::exception const&) {std::cout << "Wrong type!\n";}
        }
        
        else if (std::regex_match(command, cleanRegex))
        {
            int order = std::stoi(command.substr(
                (command.find("[")+1),
                (command.find("]")-command.find("["))-1
            ));
            if ((order < len) && (order >= 0)) arr[order]->clean();
            else std::cout << "Order out of range!\n";
        }
        
        else if (std::regex_match(command, lenRegex))
        {
            int order = std::stoi(command.substr(
                (command.find("[")+1),
                (command.find("]")-command.find("["))-1
            ));
            if ((order < len) && (order >= 0)) 
                std::cout << arr[order]->getLength() << "\n";
            else std::cout << "Order out of range!\n";
        }
        
        else if (std::regex_match(command, equalityRegex))
        {
            int order1 = std::stoi(command.substr(
                (command.find("[")+1),
                (command.find("]")-command.find("["))-1
            ));
            command = command.substr(command.find("[")+1, command.size());
            int order2 = std::stoi(command.substr(
                (command.find("[")+1),
                (command.find("]")-command.find("["))-1
            ));
            if ((order1 < len) && (order1 >= 0) || (order2 < len) || (order2 >= 0))
            {
                bool res = (*arr[order1] == *arr[order2]) ? true : false;
                std::cout << std::boolalpha << res << "\n";
            }
            else std::cout << "Order out of range!\n";
        }
        
        else if (std::regex_match(command, addRegex))
        {
            std::string str = command.substr(4, command.size());
            arr.push_back(new String(str.c_str()));
            len++;
        }
        
        else if(std::regex_match(command, setRegex))
        {
            int order = std::stoi(command.substr(
                (command.find("[")+1),
                (command.find("]")-command.find("["))-1
            ));
            if ((order < len) && (order >= 0))
            {
                std::string str = command.substr(command.find("]")+2, command.size());
                arr[order]->set(str.c_str());
            }
            else std::cout << "Order out of range!\n";
        }
        
        else if(std::regex_match(command, findRegex))
        {
            int order = std::stoi(command.substr(
                (command.find("[")+1),
                (command.find("]")-command.find("["))-1
            ));
            if ((order >= len) || (order < 0)) std::cout << "Order out of range!\n";
            
            std::string target = command.substr(command.find("]")+2, 1);
            try
            {
                auto x = static_cast<Identifier&> (*arr[order]);
                int res = x.findFirst(target[0]);
                if (res == -1) std::cout << "Not found.\n";
                else std::cout << res << "\n";
            }
            catch (std::bad_cast const&) {std::cout << "Not an Identifier string!\n";}
        }
        else if (!command.compare("\n")) std::cout << "Unknown command!\n";
        std::cout << "> ";
    }
    return 0;
}
