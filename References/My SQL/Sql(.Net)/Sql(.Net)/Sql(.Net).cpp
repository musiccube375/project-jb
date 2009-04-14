// Sql(.Net).cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <mysql++.h>
#include <iomanip>
#include <iostream>
#include <conio.h>

#pragma comment(lib,"libmysql")
#pragma comment(lib,"mysqlpp")

using namespace std;
using namespace mysqlpp;

int _tmain(int argc, _TCHAR* argv[])
{
	Connection con("gamedata","127.0.0.1","root","6957");

	getch();
	
	return 0;
}

