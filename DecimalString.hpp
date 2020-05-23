#pragma once
#include "String.hpp"
#include <cstdlib>
#include <memory>

class DecimalString : public String
{
public:
        DecimalString();
        DecimalString(char const *);
        DecimalString(char);
        DecimalString(const DecimalString&);
        ~DecimalString();

        bool isInteger() const;
        void set(char const*);
        static bool isDecimal(char const*);

        DecimalString& numToStr(int);

        DecimalString& operator = (DecimalString const&);
        DecimalString& operator - (DecimalString const&);
        DecimalString& operator * (DecimalString const&);
        DecimalString& operator + (DecimalString const&);

        bool operator > (DecimalString const&) const;
        bool operator < (DecimalString const&) const;
        bool operator == (DecimalString const&) const;
        bool operator != (DecimalString const&) const;

        char const* getString() const {return String::getString();};
        size_t getLength() const {return String::getLength();};
};
