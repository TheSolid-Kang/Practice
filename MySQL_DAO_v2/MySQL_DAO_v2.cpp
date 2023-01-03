﻿#include "pch.h"
#include "MySQL_DAO_v2.hpp"

std::unique_ptr<sql::ResultSet> MySQL_DAO_v2::GetResultSet(const std::string& _query) {
	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::Statement* stmt = nullptr;
	std::unique_ptr<sql::ResultSet> _uniq_res;
	driver = get_driver_instance();
	try {

		con = (*driver).connect("tcp://127.0.0.1:3306", "root", "root");
		stmt = (*con).createStatement();
		(*con).setSchema("test");
		std::unique_ptr<sql::ResultSet> uniq_res((*stmt).executeQuery(_query));
		_uniq_res = std::move(uniq_res);
	}
	catch (sql::SQLException _e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << _e.what();
		std::cout << " (MySQL error code: " << _e.getErrorCode();
		std::cout << ", SQLState: " << _e.getSQLState() << " )" << std::endl;
		std::cout << "실패" << std::endl;
	}
	catch (std::exception _e) {
		std::cout << _e.what() << std::endl;
		std::cout << "실패" << std::endl;
	}



#if NDEBUG
	if (false == (*con).isClosed())
	{
		(*con).close();

		(*stmt).close();
		delete stmt;
		delete con;
	}
#endif
	return std::move(_uniq_res);
}


std::vector<std::vector<std::string>> MySQL_DAO_v2::GetDataContainer(const std::string& _query, int _column_cnt) {
	auto uniq_res = GetResultSet("SELECT id, label FROM test ORDER BY id ASC");
	std::vector<std::vector<std::string>> vec_result((*uniq_res).rowsCount());
	int i = 0;
	while ((*uniq_res).next()) {
		for (int column_cnt = 1; column_cnt <= _column_cnt; ++column_cnt)
			vec_result[i].push_back((*uniq_res).getString(column_cnt));
		i++;
	}
	return vec_result;
}

void MySQL_DAO_v2::Execute(const std::string& _query)
{
	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::Statement* stmt = nullptr;
	driver = get_driver_instance();
	try {
		con = (*driver).connect("tcp://127.0.0.1:3306", "root", "root");
		stmt = (*con).createStatement();
		(*con).setSchema("test");
		(*stmt).execute(_query);
	}
	catch (sql::SQLException _e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << _e.what();
		std::cout << " (MySQL error code: " << _e.getErrorCode();
		std::cout << ", SQLState: " << _e.getSQLState() << " )" << std::endl;
		std::cout << "실패" << std::endl;
	}
	catch (std::exception _e) {
		std::cout << _e.what() << std::endl;
		std::cout << "실패" << std::endl;
	}
#if NDEBUG
	if (false == (*con).isClosed())
	{
		(*stmt).close();
		(*con).close();

		delete stmt;
		delete con;
	}
#endif
}

bool MySQL_DAO_v2::ExecuteTransaction(std::vector<std::string> _vec_query)
{
	bool is_commit = false;
	sql::Driver* driver = nullptr;
	sql::Connection* con = nullptr;
	sql::Statement* stmt = nullptr;
	driver = get_driver_instance();
	try {
		con = (*driver).connect("tcp://127.0.0.1:3306", "root", "root");
		stmt = (*con).createStatement();
		(*con).setSchema("test");
		stmt->execute("START TRANSACTION;");
		for (auto _query : _vec_query)
			(*stmt).execute(_query);

		is_commit = true;
	}
	catch (sql::SQLException _e) {
		std::cout << "# ERR: SQLException in " << __FILE__;
		std::cout << "(" << __FUNCTION__ << ") on line " << __LINE__ << std::endl;
		std::cout << "# ERR: " << _e.what();
		std::cout << " (MySQL error code: " << _e.getErrorCode();
		std::cout << ", SQLState: " << _e.getSQLState() << " )" << std::endl;
		std::cout << "실패" << std::endl;

		stmt->execute("ROLLBACK;");
	}
	catch (std::exception _e) {
		std::cout << _e.what() << std::endl;
		std::cout << "실패" << std::endl;
		stmt->execute("ROLLBACK;");
	}
	stmt->execute("COMMIT;");
#if NDEBUG
	if (false == (*con).isClosed())
	{
		(*stmt).close();
		(*con).close();

		delete stmt;
		delete con;
	}
#endif

	return is_commit;
}