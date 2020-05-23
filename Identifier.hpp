#pragma once
#include "String.hpp"
#include <cstdlib>
#include <memory>

class Identifier : public String
{
public:
        Identifier();
        Identifier(char const *);
        Identifier(char);
        Identifier(const Identifier&);
        ~Identifier();

        void set(char const*);
        int findFirst(char) const;
        static bool isIdentifier(char const*);

        Identifier& operator = (Identifier const&);
        bool operator > (Identifier const&) const;
        bool operator < (Identifier const&) const;
        bool operator == (Identifier const&) const;
        bool operator != (Identifier const&) const;

        char const* getString() const {return String::getString();};
        size_t getLength() const {return String::getLength();};
};
