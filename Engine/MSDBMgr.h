#pragma once
#include <windows.h>
#include <sql.h>
#include <sqlext.h>

class MSDBMgr
{
    SQLHENV henv;
    SQLHDBC hdbc;
    SQLHSTMT hstmt;
};

