#pragma once


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

#define DEF_CAP 2048

class MySQL_DAO_v3  {
private:
  class StringBuilder {
  private:
    TString main;
    TString scratch;

    const TString::size_type ScratchSize = 1024;  // 다른 임의의 숫자 넣어도 됨.

  public:
    StringBuilder& append(const TString& str) {
      scratch.append(str);
      if (scratch.size() > ScratchSize) {
        main.append(scratch);
        scratch.resize(0);
      }
      return *this;
    }

    StringBuilder& append_endl(const TString& str) {
      append(str);
      append(_T("\n"));
      return *this;
    }

    const TString& str() {
      if (scratch.size() > 0) {
        main.append(scratch);
        scratch.resize(0);
      }
      return main;
    }

    void clear() {
      main.resize(0);
      scratch.resize(0);
    }
  };
public:
  MySQL_DAO_v3()
    : host(DB_HOST)
    , port(DB_PORT)
    , user(DB_USER)
    , pass(DB_PASS)
    , name(DB_NAME)
  { }
  MySQL_DAO_v3(TString _name)
    : host(DB_HOST)
    , port(DB_PORT)
    , user(DB_USER)
    , pass(DB_PASS)
    , name(_name)
  { }

  MySQL_DAO_v3(TString _host, TString _port, TString _user, TString _pass, TString _name)
  {
    host = _host;
    port = _port;
    user = _user;
    pass = _pass;
    name = _name;
    StringBuilder str_buil;
    str_buil.append(_T("DATA SOURCE=") + host + _T(";"));
    str_buil.append(_T("PORT =") + port + _T(";"));
    str_buil.append(_T("DATABASE =") + name + _T(";"));
    str_buil.append(_T("UID =") + user + _T(";"));
    str_buil.append(_T("PASSWORD =") + pass + _T(";"));
    str_buil.append(_T("CharSet =") + CHAR_SET + _T(";"));
    str_buil.append(_T("Allow User Variables = TRUE;"));
    url = str_buil.str();
    //url = _T("DATA SOURCE=" + host + "; PORT = {port}; DATABASE = {name}; UID = {user}; PASSWORD = {pass}; CharSet = {CHAR_SET}; Allow User Variables = TRUE; ");
  }
private:
  const TString DB_HOST = _T("localhost");
  const TString DB_PORT = _T("3306");
  const TString DB_USER = _T("root");
  const TString DB_PASS = _T("root");
  const TString DB_NAME = _T("TwoMites");
  const TString CHAR_SET = _T("UTF8");

  TString host;
  TString port;
  TString user;
  TString pass;
  TString name;

  TString url;
  TString query;

public:
	std::unique_ptr<sql::ResultSet> GetResultSet(const TString& _query);
	std::vector<std::vector<TString>> GetDataContainer(const TString& _query, int _column_cnt);
	void Execute(const TString& _query);
	bool ExecuteTransaction(std::vector<TString> _vec_query);

};