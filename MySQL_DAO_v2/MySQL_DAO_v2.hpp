#pragma once
#include <stdlib.h>
#include <string>
#include <tchar.h>
#include <vector>

#include <boost/noncopyable.hpp>

#include <C:\Program Files\MySQL\Connector C++ 8.0\include\jdbc\cppconn/connection.h>
#include <C:\Program Files\MySQL\Connector C++ 8.0\include\jdbc\cppconn/exception.h>
#include <C:\Program Files\MySQL\Connector C++ 8.0\include\jdbc\cppconn/driver.h>
#include <C:\Program Files\MySQL\Connector C++ 8.0\include\jdbc\cppconn/resultset.h>
#include <C:\Program Files\MySQL\Connector C++ 8.0\include\jdbc\cppconn/statement.h>
//#include <../include/jdbc/cppconn/connection.h>

//#include <jdbc/cppconn/connection.h>
//#include <jdbc/cppconn/driver.h>
//#include <jdbc/cppconn/exception.h>
//#include <jdbc/cppconn/resultset.h>
//#include <jdbc/cppconn/statement.h>

#include <exception>
#include "pch.h"
#if UNICODE 
//typedef std::wstring& sqlstring;
using TString = std::wstring;
using tifstream = std::wifstream;
using tofstream = std::wofstream;
#define tcout  wcout
#define tcin  wcin
#else
using TString = std::string;
using tifstream = std::ifstream;
using tofstream = std::ofstream;
#define tcout  cout
#define tcin  wcin
#endif;

class MySQL_DAO_v2 : public boost::noncopyable {
private:
	MySQL_DAO_v2() = default;
	MySQL_DAO_v2(const MySQL_DAO_v2&) = delete;

public:
	static MySQL_DAO_v2& GetInstance() {
		static MySQL_DAO_v2 s_instance;
		return s_instance;
	}

public:
	std::unique_ptr<sql::ResultSet> GetResultSet(const TString& _query);
	std::vector<std::vector<TString>> GetDataContainer(const TString& _query, int _column_cnt);
	void Execute(const TString& _query);
	bool ExecuteTransaction(std::vector<TString> _vec_query);

};