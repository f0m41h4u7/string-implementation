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
