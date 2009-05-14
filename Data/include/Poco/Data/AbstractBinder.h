//
// AbstractBinder.h
//
// $Id: //poco/1.3/Data/include/Poco/Data/AbstractBinder.h#2 $
//
// Library: Data
// Package: DataCore
// Module:  AbstractBinder
//
// Definition of the AbstractBinder class.
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


#ifndef Data_AbstractBinder_INCLUDED
#define Data_AbstractBinder_INCLUDED


#include "Poco/Data/Data.h"
#include <cstddef>


namespace Poco {
namespace Data {


class BLOB;


class Data_API AbstractBinder
	/// Interface for Binding data types to placeholders. The default placeholder format 
	/// in the SQL query is ":name".
{
public:
	AbstractBinder();
		/// Creates the AbstractBinder.

	virtual ~AbstractBinder();
		/// Destroys the AbstractBinder.

	virtual void bind(std::size_t pos, const Poco::Int8& val) = 0;
		/// Binds an Int8.

	virtual void bind(std::size_t pos, const Poco::UInt8& val) = 0;
		/// Binds an UInt8.

	virtual void bind(std::size_t pos, const Poco::Int16& val) = 0;
		/// Binds an Int16.

	virtual void bind(std::size_t pos, const Poco::UInt16& val) = 0;
		/// Binds an UInt16.

	virtual void bind(std::size_t pos, const Poco::Int32& val) = 0;
		/// Binds an Int32.

	virtual void bind(std::size_t pos, const Poco::UInt32& val) = 0;
		/// Binds an UInt32.
		
	virtual void bind(std::size_t pos, const Poco::Int64& val) = 0;
		/// Binds an Int64.

	virtual void bind(std::size_t pos, const Poco::UInt64& val) = 0;
		/// Binds an UInt64.

	virtual void bind(std::size_t pos, const bool& val) = 0;
		/// Binds a boolean.

	virtual void bind(std::size_t pos, const float& val) = 0;
		/// Binds a float.

	virtual void bind(std::size_t pos, const double& val) = 0;
		/// Binds a double.

	virtual void bind(std::size_t pos, const char& val) = 0;
		/// Binds a single character.

	virtual void bind(std::size_t pos, const char* const &pVal) = 0;
		/// Binds a const char ptr.

	virtual void bind(std::size_t pos, const std::string& val) = 0;
		/// Binds a string.

	virtual void bind(std::size_t pos, const BLOB& val) = 0;
		/// Binds a BLOB.
};


} } // namespace Poco::Data


#endif // Data_AbstractBinder_INCLUDED
