#pragma once
#include <stdlib.h>
#include <string>
#include <vector>

#include <boost/noncopyable.hpp>

#include <C:\Program Files\MySQL\Connector C++ 8.0\include\jdbc\cppconn/connection.h>
#include <C:\Program Files\MySQL\Connector C++ 8.0\include\jdbc\cppconn/exception.h>
#include <C:\Program Files\MySQL\Connector C++ 8.0\include\jdbc\cppconn/driver.h>
#include <C:\Program Files\MySQL\Connector C++ 8.0\include\jdbc\cppconn/resultset.h>
#include <C:\Program Files\MySQL\Connector C++ 8.0\include\jdbc\cppconn/statement.h>

#include <exception>

#include "pch.h"
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

public:
	std::unique_ptr<sql::ResultSet> GetResultSet(const std::string& _query);
	std::vector<std::vector<std::string>> GetDataContainer(const std::string& _query, int _column_cnt);
	void Execute(const std::string& _query);
	bool ExecuteTransaction(std::vector<std::string> _vec_query);

};