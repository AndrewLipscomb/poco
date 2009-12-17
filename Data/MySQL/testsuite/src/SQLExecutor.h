//
// SQLExecutor.h
//
// $Id: //poco/1.3/Data/MySQL/testsuite/src/SQLExecutor.h#2 $
//
// Definition of the SQLExecutor class.
//
// Copyright (c) 2008, Applied Informatics Software Engineering GmbH.
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


#ifndef SQLExecutor_INCLUDED
#define SQLExecutor_INCLUDED


#include "Poco/Data/MySQL/MySQL.h"
#include "Poco/Data/Session.h"


class SQLExecutor: public CppUnit::TestCase
{
public:
	enum DataBinding
	{
		PB_IMMEDIATE,
		PB_AT_EXEC
	};
	
	enum DataExtraction
	{
		DE_MANUAL,
		DE_BOUND
	};

	SQLExecutor(const std::string& name, Poco::Data::Session* _pSession);
	~SQLExecutor();

	void bareboneMySQLTest(const char* host, const char* user, const char* pwd, const char* db, int port, const char* tableCreateString);
		/// This function uses "bare bone" MySQL API calls (i.e. calls are not 
		/// "wrapped" in PocoData framework structures).
		/// The purpose of the function is to verify that driver behaves
		/// correctly. If this test passes, subsequent tests failures are likely ours.

	void simpleAccess();
	void complexType();
	void simpleAccessVector();
	void complexTypeVector();
	void insertVector();
	void insertEmptyVector();

	void insertSingleBulk();
	void insertSingleBulkVec();

	void limits();
	void limitOnce();
	void limitPrepare();
	void limitZero();
	void prepare();

	void setSimple();
	void setComplex();
	void setComplexUnique();
	void multiSetSimple();
	void multiSetComplex();
	void mapComplex();
	void mapComplexUnique();
	void multiMapComplex();
	void selectIntoSingle();
	void selectIntoSingleStep();
	void selectIntoSingleFail();
	void lowerLimitOk();
	void lowerLimitFail();
	void combinedLimits();
	void combinedIllegalLimits();
	void ranges();
	void illegalRange();
	void singleSelect();
	void emptyDB();

	void blob(int bigSize = 1024);
	void blobStmt();

	void floats();
	void doubles();
	void tuples();
	void tupleVector();

	void internalExtraction();
	void doNull();

private:
	Poco::Data::Session* _pSession;
};


#endif // SQLExecutor_INCLUDED