#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <windows.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>
using namespace std;

SQLHANDLE sqlenvhandle;
SQLHANDLE sqlconnectionhandle;
SQLHANDLE sqlstatementhandle;
SQLRETURN retcode;
// check for the error handle and display the error
void show_error(unsigned int handletype, const SQLHANDLE &handle);
//init connection with the database
//user and pass is hardcoded!
void Connect_DB();
// disconnect from database
void Disconnect_DB()

#endif
