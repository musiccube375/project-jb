// sql_01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#include <mysql++.h>

#include <iomanip>
#include <iostream>

using namespace std;
using namespace mysqlpp;

#pragma comment(lib,"libmysql")
#pragma comment(lib,"mysqlpp")


int _tmain(int argc, _TCHAR* argv[])
{
	Connection con("gamedata","127.0.0.1","root","6957");
	return 0;
}

