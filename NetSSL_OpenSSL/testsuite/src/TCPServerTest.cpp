//
// TCPServerTest.cpp
//
// $Id: //poco/1.3/NetSSL_OpenSSL/testsuite/src/TCPServerTest.cpp#3 $
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


#include "TCPServerTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Net/TCPServer.h"
#include "Poco/Net/TCPServerConnection.h"
#include "Poco/Net/TCPServerConnectionFactory.h"
#include "Poco/Net/TCPServerParams.h"
#include "Poco/Net/SecureStreamSocket.h"
#include "Poco/Net/SecureServerSocket.h"
#include "Poco/Thread.h"
#include <iostream>


using Poco::Net::TCPServer;
using Poco::Net::TCPServerConnection;
using Poco::Net::TCPServerConnectionFactory;
using Poco::Net::TCPServerConnectionFactoryImpl;
using Poco::Net::TCPServerParams;
using Poco::Net::StreamSocket;
using Poco::Net::SecureStreamSocket;
using Poco::Net::SecureServerSocket;
using Poco::Net::SocketAddress;
using Poco::Thread;


namespace
{
	class EchoConnection: public TCPServerConnection
	{
	public:
		EchoConnection(const StreamSocket& s): TCPServerConnection(s)
		{
		}
		
		void run()
		{
			StreamSocket& ss = socket();
			try
			{
				char buffer[256];
				int n = ss.receiveBytes(buffer, sizeof(buffer));
				while (n > 0)
				{
					ss.sendBytes(buffer, n);
					n = ss.receiveBytes(buffer, sizeof(buffer));
				}
			}
			catch (Poco::Exception& exc)
			{
				std::cerr << "EchoConnection: " << exc.displayText() << std::endl;
			}
		}
	};
}


TCPServerTest::TCPServerTest(const std::string& name): CppUnit::TestCase(name)
{
}


TCPServerTest::~TCPServerTest()
{
}


void TCPServerTest::testOneConnection()
{
	SecureServerSocket svs(0);
	TCPServer srv(new TCPServerConnectionFactoryImpl<EchoConnection>(), svs);
	srv.start();
	assert (srv.currentConnections() == 0);
	assert (srv.currentThreads() == 0);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 0);
	
	SocketAddress sa("localhost", svs.address().port());
	SecureStreamSocket ss1(sa);
	std::string data("hello, world");
	ss1.sendBytes(data.data(), (int) data.size());
	char buffer[256];
	int n = ss1.receiveBytes(buffer, sizeof(buffer));
	assert (n > 0);
	assert (std::string(buffer, n) == data);
	assert (srv.currentConnections() == 1);
	assert (srv.currentThreads() == 1);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 1);
	ss1.close();
	Thread::sleep(300);
	assert (srv.currentConnections() == 0);
}


void TCPServerTest::testTwoConnections()
{
	SecureServerSocket svs(0);
	TCPServer srv(new TCPServerConnectionFactoryImpl<EchoConnection>(), svs);
	srv.start();
	assert (srv.currentConnections() == 0);
	assert (srv.currentThreads() == 0);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 0);
	
	SocketAddress sa("localhost", svs.address().port());
	SecureStreamSocket ss1(sa);
	SecureStreamSocket ss2(sa);
	std::string data("hello, world");
	ss1.sendBytes(data.data(), (int) data.size());
	ss2.sendBytes(data.data(), (int) data.size());

	char buffer[256];
	int n = ss1.receiveBytes(buffer, sizeof(buffer));
	assert (n > 0);
	assert (std::string(buffer, n) == data);

	n = ss2.receiveBytes(buffer, sizeof(buffer));
	assert (n > 0);
	assert (std::string(buffer, n) == data);
	
	assert (srv.currentConnections() == 2);
	assert (srv.currentThreads() == 2);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 2);
	ss1.close();
	Thread::sleep(300);
	assert (srv.currentConnections() == 1);
	assert (srv.currentThreads() == 1);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 2);
	ss2.close();

	Thread::sleep(300);
	assert (srv.currentConnections() == 0);
}


void TCPServerTest::testMultiConnections()
{
	SecureServerSocket svs(0);
	TCPServerParams* pParams = new TCPServerParams;
	pParams->setMaxThreads(4);
	pParams->setMaxQueued(4);
	pParams->setThreadIdleTime(100);
	TCPServer srv(new TCPServerConnectionFactoryImpl<EchoConnection>(), svs, pParams);
	srv.start();
	assert (srv.currentConnections() == 0);
	assert (srv.currentThreads() == 0);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 0);
	
	SocketAddress sa("localhost", svs.address().port());
	SecureStreamSocket ss1(sa);
	SecureStreamSocket ss2(sa);
	SecureStreamSocket ss3(sa);
	SecureStreamSocket ss4(sa);
	std::string data("hello, world");
	ss1.sendBytes(data.data(), (int) data.size());
	ss2.sendBytes(data.data(), (int) data.size());
	ss3.sendBytes(data.data(), (int) data.size());
	ss4.sendBytes(data.data(), (int) data.size());

	char buffer[256];
	int n = ss1.receiveBytes(buffer, sizeof(buffer));
	assert (n > 0);
	assert (std::string(buffer, n) == data);

	n = ss2.receiveBytes(buffer, sizeof(buffer));
	assert (n > 0);
	assert (std::string(buffer, n) == data);

	n = ss3.receiveBytes(buffer, sizeof(buffer));
	assert (n > 0);
	assert (std::string(buffer, n) == data);

	n = ss4.receiveBytes(buffer, sizeof(buffer));
	assert (n > 0);
	assert (std::string(buffer, n) == data);
	
	assert (srv.currentConnections() == 4);
	assert (srv.currentThreads() == 4);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 4);
	
	SecureStreamSocket ss5;
	ss5.setLazyHandshake();
	ss5.connect(sa);
	Thread::sleep(200);
	assert (srv.queuedConnections() == 1);
	SecureStreamSocket ss6;
	ss6.setLazyHandshake();
	ss6.connect(sa);
	Thread::sleep(200);
	assert (srv.queuedConnections() == 2);
	
	ss1.close();
	Thread::sleep(300);
	assert (srv.currentConnections() == 4);
	assert (srv.currentThreads() == 4);
	assert (srv.queuedConnections() == 1);
	assert (srv.totalConnections() == 5);

	ss2.close();
	Thread::sleep(300);
	assert (srv.currentConnections() == 4);
	assert (srv.currentThreads() == 4);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 6);
	
	ss3.close();
	Thread::sleep(300);
	assert (srv.currentConnections() == 3);
	assert (srv.currentThreads() == 3);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 6);

	ss4.close();
	Thread::sleep(300);
	assert (srv.currentConnections() == 2);
	assert (srv.currentThreads() == 2);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 6);

	ss5.close();
	ss6.close();
	Thread::sleep(300);
	assert (srv.currentConnections() == 0);
}


void TCPServerTest::testReuseSocket()
{
	SecureServerSocket svs(0);
	TCPServer srv(new TCPServerConnectionFactoryImpl<EchoConnection>(), svs);
	srv.start();
	assert (srv.currentConnections() == 0);
	assert (srv.currentThreads() == 0);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 0);
	
	SocketAddress sa("localhost", svs.address().port());
	SecureStreamSocket ss1(sa);
	std::string data("hello, world");
	ss1.sendBytes(data.data(), (int) data.size());
	char buffer[256];
	int n = ss1.receiveBytes(buffer, sizeof(buffer));
	assert (n > 0);
	assert (std::string(buffer, n) == data);
	assert (srv.currentConnections() == 1);
	assert (srv.currentThreads() == 1);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 1);
	ss1.close();
	Thread::sleep(300);
	assert (srv.currentConnections() == 0);

	ss1.connect(sa);
	ss1.sendBytes(data.data(), (int) data.size());
	n = ss1.receiveBytes(buffer, sizeof(buffer));
	assert (n > 0);
	assert (std::string(buffer, n) == data);
	assert (srv.currentConnections() == 1);
	assert (srv.queuedConnections() == 0);
	assert (srv.totalConnections() == 2);
	ss1.close();
	Thread::sleep(300);
	assert (srv.currentConnections() == 0);
}


void TCPServerTest::setUp()
{
}


void TCPServerTest::tearDown()
{
}


CppUnit::Test* TCPServerTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TCPServerTest");

	CppUnit_addTest(pSuite, TCPServerTest, testOneConnection);
	CppUnit_addTest(pSuite, TCPServerTest, testTwoConnections);
	CppUnit_addTest(pSuite, TCPServerTest, testMultiConnections);
	CppUnit_addTest(pSuite, TCPServerTest, testReuseSocket);

	return pSuite;
}