//
// Parameter.h
//
// $Id: //poco/1.3/Data/ODBC/include/Poco/Data/ODBC/Parameter.h#3 $
//
// Library: Data/ODBC
// Package: ODBC
// Module:  Parameter
//
// Definition of Parameter.
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
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


#ifndef ODBC_Parameter_INCLUDED
#define ODBC_Parameter_INCLUDED


#include "Poco/Data/ODBC/ODBC.h"
#include "Poco/Data/ODBC/Handle.h"
#ifdef POCO_OS_FAMILY_WINDOWS
#include <windows.h>
#endif
#include <sqlext.h>


namespace Poco {
namespace Data {
namespace ODBC {


class ODBC_API Parameter
{
public:
	explicit Parameter(const StatementHandle& rStmt, std::size_t colNum);
		/// Creates the Parameter.
		
	~Parameter();
		/// Destroys the Parameter.

	std::size_t number() const;
		/// Returns the column number.

	std::size_t dataType() const;
		/// Returns the SQL data type.

	std::size_t columnSize() const;
		/// Returns the the size of the column or expression of the corresponding 
		/// parameter marker as defined by the data source.

	std::size_t decimalDigits() const;
		/// Returns the number of decimal digits of the column or expression 
		/// of the corresponding parameter as defined by the data source.

	bool isNullable() const;
		/// Returns true if column allows null values, false otherwise.

private:
	Parameter();

	static const int BUFFER_LENGTH = 2048;

	void init();

	SQLSMALLINT _dataType;
    SQLULEN     _columnSize;
    SQLSMALLINT _decimalDigits;
    SQLSMALLINT _isNullable;

	const StatementHandle& _rStmt;
	std::size_t _number;
};


///
/// inlines
///
inline std::size_t Parameter::number() const
{
	return _number;
}


inline std::size_t Parameter::dataType() const
{
	return _dataType;
}


inline std::size_t Parameter::columnSize() const
{
	return _columnSize;
}


inline std::size_t Parameter::decimalDigits() const
{
	return _decimalDigits;
}


inline bool Parameter::isNullable() const
{
	return SQL_NULLABLE == _isNullable;
}


} } } // namespace Poco::Data::ODBC


#endif
