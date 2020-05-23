#pragma once
#include <cstdlib>
#include <memory>

class String
{
protected:
        std::unique_ptr<char[]>  m_address;
        size_t m_length{0};

public:
        String();
        String(char const*);
        String(char);
        String(const String&);
        ~String();

        void clean();
        void set(char const*);

        bool operator == (String const&) const;
        bool operator != (String const&) const;

        char const* getString() const {return m_address.get();};
        size_t getLength() const {return m_length;};
};
