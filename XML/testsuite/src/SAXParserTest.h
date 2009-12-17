//
// SAXParserTest.h
//
// $Id: //poco/1.3/XML/testsuite/src/SAXParserTest.h#3 $
//
// Definition of the SAXParserTest class.
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


#ifndef SAXParserTest_INCLUDED
#define SAXParserTest_INCLUDED


#include "Poco/XML/XML.h"
#include "CppUnit/TestCase.h"
#include "Poco/SAX/XMLReader.h"


class SAXParserTest: public CppUnit::TestCase
{
public:
	SAXParserTest(const std::string& name);
	~SAXParserTest();

	void testSimple1();
	void testSimple2();
	void testAttributes();
	void testCDATA();
	void testComment();
	void testPI();
	void testDTD();
	void testInternalEntity();
	void testNotation();
	void testExternalUnparsed();
	void testExternalParsed();
	void testDefaultNamespace();
	void testNamespaces();
	void testNamespacesNoPrefixes();
	void testNoNamespaces();
	void testUndeclaredNamespace();
	void testUndeclaredNamespaceNoPrefixes();
	void testUndeclaredNoNamespace();
	void testRSS();
	void testEncoding();
	void testParseMemory();
	void testCharacters();
	void testParsePartialReads();

	void setUp();
	void tearDown();

	std::string parse(Poco::XML::XMLReader& reader, int options, const std::string& data);
	std::string parseMemory(Poco::XML::XMLReader& reader, int options, const std::string& data);

	static CppUnit::Test* suite();

	static const std::string SIMPLE1;
	static const std::string SIMPLE2;
	static const std::string ATTRIBUTES;
	static const std::string CDATA;
	static const std::string COMMENT;
	static const std::string PROCESSING_INSTRUCTION;
	static const std::string DTD;
	static const std::string INTERNAL_ENTITY;
	static const std::string NOTATION;
	static const std::string EXTERNAL_UNPARSED;
	static const std::string EXTERNAL_PARSED;
	static const std::string INCLUDE;
	static const std::string DEFAULT_NAMESPACE;
	static const std::string NAMESPACES;
	static const std::string UNDECLARED_NAMESPACE;
	static const std::string XHTML_LATIN1_ENTITIES;
	static const std::string RSS;
	static const std::string ENCODING;
	static const std::string WSDL;
};


#endif // SAXParserTest_INCLUDED
