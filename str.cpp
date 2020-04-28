#include "str.hpp"
#include <iostream>
#include <regex>
#include <climits>
#include <cmath>

/*********************************************************************
 *
 * Class String
 * 
 * *******************************************************************/

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

/*********************************************************************
 *
 * Class Identifier
 * 
 * *******************************************************************/

Identifier::Identifier() {}

Identifier::~Identifier() {}

void Identifier::set(char const* cString) 
{
    if(cString != nullptr) 
    {
        if(isIdentifier(cString)) 
        {
            m_length = strlen(cString);
            m_address = std::make_unique<char[]>(m_length + 1);
            memcpy(m_address.get(), cString, m_length);
            m_address.get()[m_length] = '\0';
        }
        else clean();
    }
    else throw std::bad_alloc();
}

bool Identifier::isIdentifier(char const* str) 
{
    const std::regex identifierRegex("^[_a-zA-Z][_a-zA-Z0-9]{0,30}$");
    if(std::regex_match(str, identifierRegex)) return true;
    return false;
}

Identifier::Identifier(char const * cString) 
{
    set(cString);
}

Identifier::Identifier(char c) 
{
    if( ((c>='a') && (c<='z')) || ((c>='A') && (c<='Z')) || (c=='_'))
    {
        m_address = std::make_unique<char[]>(2);
        m_length = 1;
        m_address[0] = c;
        m_address[1] = '\0';
    }
    else clean();
}

Identifier::Identifier(const Identifier& orig) 
{
    set(orig.m_address.get());
}

int Identifier::findFirst(char c) const 
{
    for(size_t i = 0; i < m_length; ++i)
        if(m_address[i] == c) return i;
    return -1;
}

Identifier& Identifier::operator = (Identifier const& str) 
{
    set(str.m_address.get());
    return *this;
}

bool Identifier::operator > (Identifier const& str) const 
{
    if(!isIdentifier(m_address.get()) || !isIdentifier(str.m_address.get())) 
        throw std::bad_cast();
    if (*this == str) return false;
    return *(unsigned char *)m_address.get() < *(unsigned char *)str.m_address.get() ?
        false : true;
}

bool Identifier::operator < (Identifier const& str) const 
{
    return !(*this > str);
}

bool Identifier::operator == (Identifier const& str) const 
{
    return (String)*this == (String)str;
}

bool Identifier::operator != (Identifier const& str) const 
{
    return !(*this == str);
}


/*********************************************************************
 *
 * Class DecimalString
 * 
 * *******************************************************************/

DecimalString::DecimalString() {}

DecimalString::~DecimalString() {}

void DecimalString::set(char const* cString) 
{
    if(cString != nullptr) 
    {
        if(isDecimal(cString)) 
        {
            m_length = strlen(cString);
            m_address = std::make_unique<char[]>(m_length + 1);
            memcpy(m_address.get(), cString, m_length);
            m_address.get()[m_length] = '\0';
        } else clean();
    }
    else throw std::bad_alloc();
}

bool DecimalString::isDecimal(char const* str) 
{
    const std::regex identifierRegex("^[-+]?[0-9]+$");
    if(std::regex_match(str, identifierRegex))
    {
        return true;
    }
    return false;
}

DecimalString::DecimalString(char const * cString) 
{
    set(cString);
}

DecimalString::DecimalString(char c) 
{
    if((c>='0')&&(c<='9')) 
    {
        m_address = std::make_unique<char[]>(2);
        m_length = 1;
        m_address[0] = c;
        m_address[1] = '\0';
    } 
    else clean();
}

DecimalString::DecimalString(const DecimalString& orig) 
{
    set(orig.m_address.get());
}

DecimalString& DecimalString::operator = (DecimalString const& str) 
{
    set(str.m_address.get());
    return *this;
}

bool DecimalString::operator == (DecimalString const& str) const 
{
    return (String)*this == (String)str;
}

bool DecimalString::operator != (DecimalString const& str) const 
{
    return !(*this == str);
}

bool DecimalString::isInteger() const 
{
    if(!isDecimal(m_address.get())) throw std::bad_cast();
    return m_length <= sizeof(INT_MAX)/sizeof(int) ? true : false;
}

bool DecimalString::operator > (DecimalString const& str) const 
{
    if(!isDecimal(m_address.get()) || !isDecimal(str.m_address.get()))
        throw std::bad_cast();
    if (*this == str) return false;
    
    int t1 = std::stoi(m_address.get());
    int t2 = std::stoi(str.m_address.get());
    return t1 > t2 ? true : false;
}

bool DecimalString::operator < (DecimalString const& str) const 
{
    if (*this == str) return false;
    return !(*this > str);
}

DecimalString& DecimalString::numToStr (int num) 
{
    if (num == 0) 
    {
        clean();
        return *this;
    }
    
    int i = 0;
    m_address = std::make_unique<char[]>(sizeof(num)/sizeof(int));
    
    bool isNegative = false;
    if (num < 0)
    {
        isNegative = true;
        num = -num;
    }
    
    while (num != 0)
    {
        int rem = num % 10;
        m_address[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/10;
    }
    
    if (isNegative) m_address[i++] = '-';
    m_length = i;
    
    [](DecimalString& str){
        int start = 0;
        int end = str.m_length -1;
        while (start < end)
        {
            std::swap(*(str.m_address.get()+start), *(str.m_address.get()+end));
            start++;
            end--;
        }
    }(*this);

    return *this;
}

DecimalString& DecimalString::operator - (DecimalString const& dec) 
{
    if(!isDecimal(m_address.get()) || !isDecimal(dec.m_address.get()))
        throw std::bad_cast();
    int num = std::stoi(m_address.get()) - std::stoi(dec.m_address.get());
    return numToStr(num);
}

DecimalString& DecimalString::operator + (DecimalString const& dec) 
{
    if(!isDecimal(m_address.get()) || !isDecimal(dec.m_address.get()))
        throw std::bad_cast();
    int num = std::stoi(m_address.get()) + std::stoi(dec.m_address.get());
    return numToStr(num);
}

DecimalString& DecimalString::operator * (DecimalString const& dec) 
{
    if(!isDecimal(m_address.get()) || !isDecimal(dec.m_address.get()))
        throw std::bad_cast();
    int num = std::stoi(m_address.get()) * std::stoi(dec.m_address.get());
    return numToStr(num);
}
