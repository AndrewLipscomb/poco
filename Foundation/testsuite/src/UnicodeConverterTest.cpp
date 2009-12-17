//
// UnicodeConverterTest.cpp
//
// $Id: //poco/1.3/Foundation/testsuite/src/UnicodeConverterTest.cpp#2 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#include "UnicodeConverterTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/UnicodeConverter.h"


using Poco::UnicodeConverter;


UnicodeConverterTest::UnicodeConverterTest(const std::string& name): CppUnit::TestCase(name)
{
}


UnicodeConverterTest::~UnicodeConverterTest()
{
}

void UnicodeConverterTest::testString()
{
	const unsigned char supp[] = {0x41, 0x42, 0xf0, 0x90, 0x82, 0xa4, 0xf0, 0xaf, 0xa6, 0xa0, 0xf0, 0xaf, 0xa8, 0x9d, 0x00};
	std::string text((const char*) supp);

	std::wstring wtext;

	UnicodeConverter::toUTF16 (text, wtext);

	std::string text2;

	UnicodeConverter::toUTF8 (wtext, text2);

	assert (text == text2);
}

void UnicodeConverterTest::testCharPtrLength()
{
	const unsigned char supp[] = {0x41, 0x42, 0xf0, 0x90, 0x82, 0xa4, 0xf0, 0xaf, 0xa6, 0xa0, 0xf0, 0xaf, 0xa8, 0x9d, 0x00};
	std::string text((const char*) supp);

	std::wstring wtext;
	std::string text2;

	UnicodeConverter::toUTF16 ((const char*)supp, 14, wtext);
	UnicodeConverter::toUTF8 (wtext.c_str (), (int) wtext.size (), text2);

	assert (text == text2);
}

void UnicodeConverterTest::testCharPtr()
{
	const unsigned char supp[] = {0x41, 0x42, 0xf0, 0x90, 0x82, 0xa4, 0xf0, 0xaf, 0xa6, 0xa0, 0xf0, 0xaf, 0xa8, 0x9d, 0x00};
	std::string text((const char*) supp);

	std::wstring wtext;
	std::string text2;

	UnicodeConverter::toUTF16 ((const char*)supp, wtext);
	UnicodeConverter::toUTF8 (wtext.c_str (), text2);

	assert (text == text2);
}


void UnicodeConverterTest::setUp()
{
}


void UnicodeConverterTest::tearDown()
{
}


CppUnit::Test* UnicodeConverterTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("UnicodeConverterTest");

	CppUnit_addTest(pSuite, UnicodeConverterTest, testString);
	CppUnit_addTest(pSuite, UnicodeConverterTest, testCharPtrLength);
	CppUnit_addTest(pSuite, UnicodeConverterTest, testCharPtr);

	return pSuite;
}
