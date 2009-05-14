//
// ZipArchiveInfo.cpp
//
// $Id: //poco/1.3/Zip/src/ZipArchiveInfo.cpp#3 $
//
// Library: Zip
// Package: Zip
// Module:  ZipArchiveInfo
//
// Copyright (c) 2007, Applied Informatics Software Engineering GmbH.
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


#include "Poco/Zip/ZipArchiveInfo.h"
#include "Poco/Buffer.h"
#include <istream>
#include <cstring>


namespace Poco {
namespace Zip {


const char ZipArchiveInfo::HEADER[ZipCommon::HEADER_SIZE] = {'\x50', '\x4b', '\x05', '\x06'};


ZipArchiveInfo::ZipArchiveInfo(std::istream& in, bool assumeHeaderRead):
	_rawInfo(),
	_startPos(in.tellg()),
	_comment()
{
	if (assumeHeaderRead)
		_startPos -= ZipCommon::HEADER_SIZE;
	parse(in, assumeHeaderRead);
}

ZipArchiveInfo::ZipArchiveInfo():
	_rawInfo(),
	_startPos(0),
	_comment()
{
	std::memset(_rawInfo, 0, FULLHEADER_SIZE);
	std::memcpy(_rawInfo, HEADER, ZipCommon::HEADER_SIZE);
}


ZipArchiveInfo::~ZipArchiveInfo()
{
}


void ZipArchiveInfo::parse(std::istream& inp, bool assumeHeaderRead)
{
	if (!assumeHeaderRead)
	{
		inp.read(_rawInfo, ZipCommon::HEADER_SIZE);
	}
	else
	{
		std::memcpy(_rawInfo, HEADER, ZipCommon::HEADER_SIZE);
	}
	poco_assert (std::memcmp(_rawInfo, HEADER, ZipCommon::HEADER_SIZE) == 0);
	// read the rest of the header
	inp.read(_rawInfo + ZipCommon::HEADER_SIZE, FULLHEADER_SIZE - ZipCommon::HEADER_SIZE);
	Poco::UInt16 len = getZipCommentSize();
	if (len > 0)
	{
		Poco::Buffer<char> buf(len);
		inp.read(buf.begin(), len);
		_comment = std::string(buf.begin(), len);
	}
}


std::string ZipArchiveInfo::createHeader() const
{
	std::string result(_rawInfo, FULLHEADER_SIZE);
	result.append(_comment);
	return result;
}


} } // namespace Poco::Zip
