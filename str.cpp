#include "str.hpp"
#include <iostream>
#include <regex>

/*********************************************************************
 *
 * Class String
 * 
 * *******************************************************************/

String::String() {
	clean();
}

String::~String(){}

void String::set(char const* cString) {
	if(cString != nullptr) {
		set(std::string_view(cString, strlen(cString)));
        }
	else {
		throw std::bad_alloc();
	}
}

void String::set(std::string_view sv) {
	m_length = sv.size();
	m_address = std::make_unique<char[]>(m_length + 1);
	memcpy(m_address.get(), sv.data(), m_length);
	m_address.get()[m_length] = '\0';
}

String::String(char const* cString) {
	set(cString);
}

String::String(char c) {
	m_address = std::make_unique<char[]>(2);
	m_length = 1;
	m_address[0] = c;
	m_address[1] = '\0';
}

String::String(const String& orig) {
	set(orig);
}

void String::clean() {
	m_address = std::make_unique<char[]>(1);
        m_address.get()[0] = 0;
        m_length = 0;
}

bool String::operator == (String const& str) const {
	if(m_length != str.m_length) return false;

        for(size_t i = 0; i < m_length; ++i) {
                if(m_address[i] != str.m_address[i]) return false;

        }
        return true;

}

/*********************************************************************
 *
 * Class Identifier
 * 
 * *******************************************************************/

Identifier::Identifier() {}

Identifier::~Identifier() {}

bool Identifier::isIdentifier(char const* str) {
        const std::regex identifierRegex("^[_a-zA-Z][_a-zA-Z0-9]{0,30}$");
        if(std::regex_match(str, identifierRegex)) {
                return true;
        }
        return false;
}

Identifier::Identifier(char const * cString) {
	if(cString != nullptr) {
		if(isIdentifier(cString))
			set(cString);
		else
			clean();
	} else {
		throw std::bad_alloc();
	}
}

Identifier::Identifier(char c) {
	if( ((c>='a') && (c<='z')) || ((c>='A') && (c<='Z')) || (c=='_')) {
		m_address = std::make_unique<char[]>(2);
        	m_length = 1;
	        m_address[0] = c;
        	m_address[1] = '\0';
	} else {
		clean();
	}
}

Identifier::Identifier(const Identifier& orig) {
	set(orig.m_address.get());
}

int Identifier::findFirst(char c) const {
	for(size_t i = 0; i < m_length; ++i){
		if(m_address[i] == c) return i;
	}
	return -1;
}

Identifier& Identifier::operator = (Identifier const& str) {
	set(str);
	return *this;
}

bool Identifier::operator > (Identifier const& str) const {
	size_t len = m_length < str.m_length ? m_length : str.m_length;
	for(size_t i = 0; i < len; ++i) {
		if(m_address[i] > str.m_address[i]) return true;
		if(str.m_address[i] > m_address[i]) return false;

		if(i + 1 == m_length || i + 1 == str.m_length) return false;
	}
	return false;
}

bool Identifier::operator == (Identifier const& str) const {
        return (String)*this == (String)str;
}

/*********************************************************************
 *
 * Class DecimalString
 * 
 * *******************************************************************/

DecimalString::DecimalString() {}

DecimalString::~DecimalString() {}

bool DecimalString::isDecimal(char const* str) {
	const std::regex identifierRegex("^[-+]?[0-9]+$");
        if(std::regex_match(str, identifierRegex)) {
                return true;
        }
        return false;
}

DecimalString::DecimalString(char const * cString) {
        if(cString != nullptr) {
                if(isDecimal(cString))
                        set(cString);
                else
                        clean();
        } else {
                throw std::bad_alloc();
        }
}

DecimalString::DecimalString(char c) {
	if((c>='0')&&(c<='9')) {
                m_address = std::make_unique<char[]>(2);
                m_length = 1;
                m_address[0] = c;
                m_address[1] = '\0';
        } else {
                clean();
        }
}

DecimalString::DecimalString(const DecimalString& orig) {
        set(orig.m_address.get());
}

bool DecimalString::operator == (DecimalString const& str) const {
        return (String)*this == (String)str;
}
