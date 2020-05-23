#include "String.hpp"
#include <iostream>
#include <regex>
#include <climits>
#include <cmath>

String::String() 
{
    clean();
}

String::~String(){}

void String::set(char const* cString) 
{
    if(cString != nullptr)
    {
        m_length = strlen(cString);
        m_address = std::make_unique<char[]>(m_length + 1);
        memcpy(m_address.get(), cString, m_length);
        m_address.get()[m_length] = '\0';
    }
    else throw std::bad_alloc();
}

String::String(char const* cString) 
{
    set(cString);
}

String::String(char c) 
{
    m_address = std::make_unique<char[]>(2);
    m_length = 1;
    m_address[0] = c;
    m_address[1] = '\0';
}

String::String(const String& orig) 
{
    set(orig.m_address.get());
}

void String::clean() 
{
    m_address = std::make_unique<char[]>(1);
    m_address.get()[0] = 0;
    m_length = 0;
}

bool String::operator == (String const& str) const 
{
    if(m_length != str.m_length) return false;
    char const* s1 = m_address.get();
    char const* s2 = str.m_address.get();
    for ( ; *s1 == *s2; s1++, s2++)
    if (*s1 == '\0') return true;
    return false;
}

bool String::operator != (String const& str) const 
{
    return !(*this == str);
}
