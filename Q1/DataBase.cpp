#include <DataBase.h>
#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

using namespace std;

void show_error(unsigned int handletype, const SQLHANDLE &handle)
{
    SQLCHAR sqlstate[1024];
    SQLCHAR message[1024];
    if (SQL_SUCCESS == SQLGetDiagRec(handletype, handle, 1, sqlstate, NULL, message, 1024, NULL))
        cout << "Message: " << message << "\nSQLSTATE: " << sqlstate << endl;
}
void Connect_DB()
{
    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &sqlenvhandle))
        return;

    if (SQL_SUCCESS != SQLSetEnvAttr(sqlenvhandle, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
        return;

    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, sqlenvhandle, &sqlconnectionhandle))
        return;

    SQLCHAR retconstring[1024];
    switch (SQLDriverConnect(sqlconnectionhandle, NULL, //___________ IP ______ Port ______ DBname ___ User ___ Password
                             (SQLCHAR *)"DRIVER={SQL Server};SERVER=localhost, 1433;DATABASE=Test;UID=Zyad;PWD=password;",
                             SQL_NTS, retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT))
    {
    case SQL_SUCCESS_WITH_INFO:
        show_error(SQL_HANDLE_DBC, sqlconnectionhandle);
        break;
    case SQL_INVALID_HANDLE:
    case SQL_ERROR:
        show_error(SQL_HANDLE_DBC, sqlconnectionhandle);
        retcode = -1;
        break;
    default:
        break;
    }

    if (retcode == -1)
        return;

    if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, sqlconnectionhandle, &sqlstatementhandle))
        return;
}

void Disconnect_DB()
{
    SQLFreeHandle(SQL_HANDLE_STMT, sqlstatementhandle);
    SQLDisconnect(sqlconnectionhandle);
    SQLFreeHandle(SQL_HANDLE_DBC, sqlconnectionhandle);
    SQLFreeHandle(SQL_HANDLE_ENV, sqlenvhandle);
}