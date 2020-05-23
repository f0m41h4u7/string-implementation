#include "Identifier.hpp"
#include <iostream>
#include <regex>
#include <climits>
#include <cmath>

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
