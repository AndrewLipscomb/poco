#
# Makefile
#
# The global Makefile for POCO [generated by mkrelease]
#

sinclude config.make

ifndef POCO_BASE
$(warning WARNING: POCO_BASE is not defined. Assuming current directory.)
export POCO_BASE=$(shell pwd)
endif

ifndef POCO_PREFIX
export POCO_PREFIX=/usr/local
endif

ifndef POCO_BUILD
export POCO_BUILD=$(POCO_BASE)
endif

.PHONY: all libexecs cppunit tests samples clean distclean install

all: libexecs tests samples

INSTALLDIR = $(DESTDIR)$(POCO_PREFIX)
COMPONENTS = Foundation XML Util Net Crypto NetSSL_OpenSSL Data Data/SQLite Data/ODBC Data/MySQL Zip

cppunit:
	$(MAKE) -C $(POCO_BASE)/CppUnit 

install: libexecs
	mkdir -p $(INSTALLDIR)/include/Poco
	mkdir -p $(INSTALLDIR)/lib
	mkdir -p $(INSTALLDIR)/bin
	for comp in $(COMPONENTS) ; do \
		if [ -d "$(POCO_BASE)/$$comp/include" ] ; then \
			cp -Rf $(POCO_BASE)/$$comp/include/* $(INSTALLDIR)/include/ ; \
		fi ; \
		if [ -d "$(POCO_BUILD)/$$comp/bin" ] ; then \
			find $(POCO_BUILD)/$$comp/bin -perm -700 -type f -exec cp -f {} $(INSTALLDIR)/bin \; ; \
		fi ; \
	done
	find $(POCO_BUILD)/lib -name "libPoco*" -type f -exec cp -f {} $(INSTALLDIR)/lib \;
	find $(POCO_BUILD)/lib -name "libPoco*" -type l -exec cp -Rf {} $(INSTALLDIR)/lib \;

libexecs =  Foundation-libexec XML-libexec Util-libexec Net-libexec Crypto-libexec NetSSL_OpenSSL-libexec Data-libexec Data/SQLite-libexec Data/ODBC-libexec Data/MySQL-libexec Zip-libexec
tests    =  Foundation-tests XML-tests Util-tests Net-tests Crypto-tests NetSSL_OpenSSL-tests Data-tests Data/SQLite-tests Data/ODBC-tests Data/MySQL-tests Zip-tests
samples  =  Foundation-samples XML-samples Util-samples Net-samples Crypto-samples NetSSL_OpenSSL-samples Data-samples Zip-samples

.PHONY: $(libexecs)
.PHONY: $(tests)
.PHONY: $(samples)

libexecs: $(filter-out $(foreach f,$(OMIT),$f%),$(libexecs))
tests: $(filter-out $(foreach f,$(OMIT),$f%),$(tests))
samples: $(filter-out $(foreach f,$(OMIT),$f%),$(samples))

Foundation-libexec: 
	$(MAKE) -C $(POCO_BASE)/Foundation

Foundation-tests: Foundation-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Foundation/testsuite
	
Foundation-samples: Foundation-libexec 
	$(MAKE) -C $(POCO_BASE)/Foundation/samples

XML-libexec:  Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/XML

XML-tests: XML-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/XML/testsuite
	
XML-samples: XML-libexec 
	$(MAKE) -C $(POCO_BASE)/XML/samples

Util-libexec:  Foundation-libexec XML-libexec
	$(MAKE) -C $(POCO_BASE)/Util

Util-tests: Util-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Util/testsuite
	
Util-samples: Util-libexec 
	$(MAKE) -C $(POCO_BASE)/Util/samples

Net-libexec:  Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/Net

Net-tests: Net-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Net/testsuite
	
Net-samples: Net-libexec  Foundation-libexec XML-libexec Util-libexec
	$(MAKE) -C $(POCO_BASE)/Net/samples

Crypto-libexec:  Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/Crypto

Crypto-tests: Crypto-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Crypto/testsuite
	
Crypto-samples: Crypto-libexec  Foundation-libexec Util-libexec
	$(MAKE) -C $(POCO_BASE)/Crypto/samples

NetSSL_OpenSSL-libexec:  Foundation-libexec Net-libexec Util-libexec Crypto-libexec
	$(MAKE) -C $(POCO_BASE)/NetSSL_OpenSSL

NetSSL_OpenSSL-tests: NetSSL_OpenSSL-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/NetSSL_OpenSSL/testsuite
	
NetSSL_OpenSSL-samples: NetSSL_OpenSSL-libexec 
	$(MAKE) -C $(POCO_BASE)/NetSSL_OpenSSL/samples

Data-libexec:  Foundation-libexec
	$(MAKE) -C $(POCO_BASE)/Data

Data-tests: Data-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Data/testsuite
	
Data-samples: Data-libexec  Data-libexec Data/SQLite-libexec
	$(MAKE) -C $(POCO_BASE)/Data/samples

Data/SQLite-libexec:  Foundation-libexec Data-libexec
	$(MAKE) -C $(POCO_BASE)/Data/SQLite

Data/SQLite-tests: Data/SQLite-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Data/SQLite/testsuite

Data/ODBC-libexec:  Foundation-libexec Data-libexec
	$(MAKE) -C $(POCO_BASE)/Data/ODBC

Data/ODBC-tests: Data/ODBC-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Data/ODBC/testsuite

Data/MySQL-libexec:  Foundation-libexec Data-libexec
	$(MAKE) -C $(POCO_BASE)/Data/MySQL

Data/MySQL-tests: Data/MySQL-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Data/MySQL/testsuite

Zip-libexec:  Foundation-libexec Net-libexec Util-libexec XML-libexec
	$(MAKE) -C $(POCO_BASE)/Zip

Zip-tests: Zip-libexec cppunit
	$(MAKE) -C $(POCO_BASE)/Zip/testsuite
	
Zip-samples: Zip-libexec 
	$(MAKE) -C $(POCO_BASE)/Zip/samples

clean:
	$(MAKE) -C $(POCO_BASE)/Foundation clean
	$(MAKE) -C $(POCO_BASE)/Foundation/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Foundation/samples clean
	$(MAKE) -C $(POCO_BASE)/XML clean
	$(MAKE) -C $(POCO_BASE)/XML/testsuite clean
	$(MAKE) -C $(POCO_BASE)/XML/samples clean
	$(MAKE) -C $(POCO_BASE)/Util clean
	$(MAKE) -C $(POCO_BASE)/Util/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Util/samples clean
	$(MAKE) -C $(POCO_BASE)/Net clean
	$(MAKE) -C $(POCO_BASE)/Net/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Net/samples clean
	$(MAKE) -C $(POCO_BASE)/Crypto clean
	$(MAKE) -C $(POCO_BASE)/Crypto/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Crypto/samples clean
	$(MAKE) -C $(POCO_BASE)/NetSSL_OpenSSL clean
	$(MAKE) -C $(POCO_BASE)/NetSSL_OpenSSL/testsuite clean
	$(MAKE) -C $(POCO_BASE)/NetSSL_OpenSSL/samples clean
	$(MAKE) -C $(POCO_BASE)/Data clean
	$(MAKE) -C $(POCO_BASE)/Data/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Data/samples clean
	$(MAKE) -C $(POCO_BASE)/Data/SQLite clean
	$(MAKE) -C $(POCO_BASE)/Data/SQLite/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Data/ODBC clean
	$(MAKE) -C $(POCO_BASE)/Data/ODBC/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Data/MySQL clean
	$(MAKE) -C $(POCO_BASE)/Data/MySQL/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Zip clean
	$(MAKE) -C $(POCO_BASE)/Zip/testsuite clean
	$(MAKE) -C $(POCO_BASE)/Zip/samples clean

distclean:
	rm -rf $(POCO_BUILD)/lib
	find $(POCO_BUILD) -name obj -type d -print0 | xargs -0 rm -rf
	find $(POCO_BUILD) -name .dep -type d -print0 | xargs -0 rm -rf
	find $(POCO_BUILD) -name bin -type d -print0 | xargs -0 rm -rf
