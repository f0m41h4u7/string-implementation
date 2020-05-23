#include <gtest/gtest.h>
#include "String.hpp"
#include "Identifier.hpp"
#include "DecimalString.hpp"

TEST(StringTest, CharPtrConstructor) { 
	String str("Hello world!");
	ASSERT_STREQ ("Hello world!", str.getString());
	ASSERT_EQ (12, str.getLength());
}

TEST(StringTest, EmptyConstructor) {
        String str;
        ASSERT_STREQ ("", str.getString());
	ASSERT_EQ (0, str.getLength());
}

TEST(StringTest, SingleCharConstructor) {
        String str('@');
        ASSERT_STREQ ("@", str.getString());
	ASSERT_EQ (1, str.getLength());
}

TEST(StringTest, CopyConstructor) {
        String str1("Hello world!");
	String str2(str1);
        ASSERT_STREQ ("Hello world!", str2.getString());
	ASSERT_TRUE (str1 == str2);
}

TEST(StringTest, CleanString) {
        String str("Hello world!");
	ASSERT_STREQ ("Hello world!", str.getString());
	str.clean();
        ASSERT_STREQ ("", str.getString());
	ASSERT_EQ (0, str.getLength());
}

TEST(StringTest, NullString) {
        String* str = nullptr;
	try {
		str = new String(nullptr);
	} catch(std::bad_alloc const&){}

        ASSERT_EQ (nullptr, str);
}

TEST(StringTest, OperatorCompare) {
        String str1("abcd");
	String str2("abcdqwqw");
        ASSERT_TRUE (str1 != str2);
}

//************************************************

TEST(IdentifierTest, EmptyConstructor) {
        Identifier id;
        ASSERT_STREQ ("", id.getString());
        ASSERT_EQ (0, id.getLength());
}

TEST(IdentifierTest, CharPtrConstructor) { 
	Identifier id("abcd");
        ASSERT_STREQ ("abcd", id.getString());
        ASSERT_EQ (4, id.getLength());
}

TEST(IdentifierTest, WrongString) {
        Identifier id("123abcd");
        ASSERT_STREQ ("", id.getString());
        ASSERT_EQ (0, id.getLength());
}

TEST(IdentifierTest, SingleCharConstructor) {
        Identifier id('a');
        ASSERT_STREQ ("a", id.getString());
        ASSERT_EQ (1, id.getLength());
}

TEST(IdentifierTest, WrongChar) {
        Identifier id('#');
        ASSERT_STREQ ("", id.getString());
        ASSERT_EQ (0, id.getLength());
}

TEST(IdentifierTest, CopyConstructor) {
        Identifier id1("_ab_cd12");
	Identifier id2(id1);
        ASSERT_STREQ ("_ab_cd12", id2.getString());
        ASSERT_EQ (8, id1.getLength());
	ASSERT_TRUE (id1 == id2);
}

TEST(IdentifierTest, NullString) {
        Identifier* str = nullptr;
        try {
                str = new Identifier(nullptr);
        } catch(std::bad_alloc const&){}

        ASSERT_EQ (nullptr, str);
}

TEST(IdentifierTest, FindFirstExists) {
        Identifier id("a12vcv");
        ASSERT_EQ (3, id.findFirst('v'));
}

TEST(IdentifierTest, FindFirstDoesntExists) {
        Identifier id("a12vcv");
        ASSERT_EQ (-1, id.findFirst('b'));
}

TEST(IdentifierTest, OperatorAssign) {
        Identifier id1("abc");
	Identifier id2("cdefgh");
	id1 = id2;
        ASSERT_STREQ ("cdefgh", id1.getString());
	ASSERT_EQ (6, id1.getLength());
	ASSERT_FALSE (id1 != id2);
}

TEST(IdentifierTest, OperatorMoreEqualLength) {
        Identifier id1("qwerty");
	Identifier id2("asdfgg");
        ASSERT_TRUE (id1 > id2);
}

TEST(IdentifierTest, OperatorMoreNotEqualLength) {
        Identifier id1("asd");
        Identifier id2("asdfgg");
        ASSERT_TRUE (id2 > id1);
}

TEST(IdentifierTest, OperatorMoreEqualValues) {
        Identifier id1("qwerty");
        Identifier id2("qwerty");
        ASSERT_FALSE (id1 > id2);
}

TEST(IdentifierTest, OperatorLess) {
        Identifier id1("qwe");
        Identifier id2("asdfgg");
        ASSERT_TRUE (id2 < id1);
}

//************************************************

TEST(DecimalTest, EmptyConstructor) {
        DecimalString dec;
        ASSERT_STREQ ("", dec.getString());
        ASSERT_EQ (0, dec.getLength());
}

TEST(DecimalTest, CharPtrConstructor) {
        DecimalString dec("1337");
        ASSERT_STREQ ("1337", dec.getString());
        ASSERT_EQ (4, dec.getLength());
	ASSERT_EQ (1337, std::stoi(dec.getString()));
}

TEST(DecimalTest, PlusSign) {
        DecimalString dec("+1337");
        ASSERT_STREQ ("+1337", dec.getString());
        ASSERT_EQ (5, dec.getLength());
        ASSERT_EQ (1337, std::stoi(dec.getString()));
}

TEST(DecimalTest, WrongString) {
        DecimalString dec("123abcd");
        ASSERT_STREQ ("", dec.getString());
        ASSERT_EQ (0, dec.getLength());
}

TEST(DecimalTest, WrongStringSigns) {
        DecimalString dec("--123");
        ASSERT_STREQ ("", dec.getString());
        ASSERT_EQ (0, dec.getLength());
}

TEST(DecimalTest, SingleCharConstructor) {
        DecimalString dec('9');
        ASSERT_STREQ ("9", dec.getString());
        ASSERT_EQ (1, dec.getLength());
}

TEST(DecimalTest, WrongChar) {
        DecimalString dec('#');
        ASSERT_STREQ ("", dec.getString());
        ASSERT_EQ (0, dec.getLength());
}

TEST(DecimalTest, WrongCharSign) {
        DecimalString dec('-');
        ASSERT_STREQ ("", dec.getString());
        ASSERT_EQ (0, dec.getLength());
}

TEST(DecimalTest, CopyConstructor) {
        DecimalString dec1("1337");
        DecimalString dec2(dec1);
        ASSERT_STREQ ("1337", dec2.getString());
        ASSERT_EQ (4, dec1.getLength());
        ASSERT_TRUE (dec1 == dec2);
}

TEST(DecimalTest, NullString) {
        DecimalString* str = nullptr;
        try {
                str = new DecimalString(nullptr);
        } catch(std::bad_alloc const&){}

        ASSERT_EQ (nullptr, str);
}

TEST(DecimalTest, LimitsMax) {
        DecimalString dec("2147483650000000");
	ASSERT_FALSE(dec.isInteger());
}

TEST(DecimalTest, IsInteger) {
        DecimalString dec("2147");
        ASSERT_FALSE(dec.isInteger());
}

TEST(DecimalTest, LimitsMin) {
        DecimalString dec("-2147483650000000");
        ASSERT_FALSE(dec.isInteger());
}

TEST(DecimalTest, OperatorMoreNotEqualLength) {
        DecimalString dec1("1337");
        DecimalString dec2("31337");
        ASSERT_TRUE (dec2 > dec1);
}

TEST(DecimalTest, OperatorMoreEqualLength) {
        DecimalString dec1("1337");
        DecimalString dec2("1338");
        ASSERT_TRUE (dec2 > dec1);
}

TEST(DecimalTest, OperatorMoreEqualValues) {
        DecimalString dec1("1337");
        DecimalString dec2("1337");
        ASSERT_FALSE (dec1 > dec2);
	ASSERT_TRUE (dec2 == dec1);
}

TEST(DecimalTest, OperatorLess) {
        DecimalString dec1("31337");
        DecimalString dec2("1337");
        ASSERT_TRUE (dec2 < dec1);
}

TEST(DecimalTest, CompareNegativeAndPositive) {
        DecimalString dec1("-31337");
        DecimalString dec2("1337");
        ASSERT_TRUE (dec1 < dec2);
}

TEST(DecimalTest, CompareNegatives) {
        DecimalString dec1("-31337");
        DecimalString dec2("-1337");
        ASSERT_TRUE (dec2 > dec1);
}

TEST(DecimalTest, SubtractionPositive) {
        DecimalString dec1("31337");
        DecimalString dec2("1337");
	DecimalString res = dec1 - dec2;
        ASSERT_STREQ ("30000", res.getString());
}

TEST(DecimalTest, SubtractionNegative) {
        DecimalString dec1("-31337");
        DecimalString dec2("1337");
        DecimalString res = dec1 - dec2;
        ASSERT_STREQ ("-32674", res.getString());
}

TEST(DecimalTest, Addition) {
        DecimalString dec1("-31337");
        DecimalString dec2("-1337");
        DecimalString res = dec1 + dec2;
        ASSERT_STREQ ("-32674", res.getString());
}

TEST(DecimalTest, Multiplication) {
        DecimalString dec1("31337");
        DecimalString dec2("1337");
        DecimalString res = dec1 * dec2;
        ASSERT_STREQ ("41897569", res.getString());
}

//************************************************

TEST(TypecastTest, StrToDecRight) {
        String dec1("31337");
	String dec2("31337");
	bool failed = false;
	int res = 0;
	try {
		auto x = static_cast<DecimalString&> (dec1);
		auto y = static_cast<DecimalString&> (dec2);
        	res = std::stoi((x+y).getString());
	} catch (std::exception const&) {failed = true;}
        ASSERT_EQ (62674, res);
	ASSERT_FALSE (failed);
}

TEST(TypecastTest, StrToDecWrong) {
	String dec1("31337");
        String dec2("qwrqer");
        bool failed = false;
        int res = 0;
        try {
                auto x = static_cast<DecimalString&> (dec1);
                auto y = static_cast<DecimalString&> (dec2);
                res = std::stoi((x+y).getString());
        } catch (std::exception const&) {failed = true;}
        ASSERT_EQ (0, res);
        ASSERT_TRUE (failed);
}

TEST(TypecastTest, OperatorMoreIdentifierRight) {
        String str1("qqqq");
        String str2("abc");
        bool failed = false, res = false;
        try {
		res = (static_cast<Identifier&> (str1) > static_cast<Identifier&> (str2)) ? true : false; 
        } catch (std::exception const&) {failed = true;}
        ASSERT_TRUE (res);
        ASSERT_FALSE (failed);
}

TEST(TypecastTest, OperatorMoreIdentifierWrong) {
        String str1("qqqq");
        String str2("ab&c");
        bool failed = false, res = false;
        try {
                res = (static_cast<Identifier&> (str1) > static_cast<Identifier&> (str2)) ? true : false;
        } catch (std::exception const&) {failed = true;}
        ASSERT_TRUE (failed);
        ASSERT_FALSE (res);
}

TEST(TypecastTest, DecToStr) {
        String str1("31337");
        DecimalString str2("31337");
        bool failed = false, res = false;
        try {
                res = (str1 == str2) ? true : false;
        } catch (std::exception const&) {failed = true;}
	ASSERT_TRUE (res);
        ASSERT_FALSE (failed);
}

TEST(TypecastTest, IdentToStr) {
        String str1("qqq");
        Identifier str2("qqq");
        bool failed = false, res = false;
        try {
                res = (str1 == str2) ? true : false;
        } catch (std::exception const&) {failed = true;}
        ASSERT_TRUE (res);
        ASSERT_FALSE (failed);
}

int main(int argc, char** argv) {
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
