#include "DecimalString.hpp"
#include <iostream>
#include <regex>
#include <climits>
#include <cmath>

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
