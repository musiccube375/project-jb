// sql_01.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <conio.h>

#include "mysql++.h"

//#include <iomanip>
//#include <iostream>

using namespace std;
//using namespace mysqlpp;

#pragma comment(lib, "libmysql")
//#pragma comment(lib, "mysqlpp")

/*#define SQL_CREATE_USERINFO_TABLE "CREATE TABLE `userinfo` ( \
	`index` INT NOT NULL AUTO_INCREMENT PRIMARY KEY, \
	`id` VARCHAR(32), \
	`nickname` VARCHAR(128), \
	`passwords` VARCHAR(16))" */

#define SQL_CREATE_USERINFO_TABLE "CREATE TABLE `userinfo` ( \
	`id` VARCHAR(32)"

//#define SQL_INSERT_USERINFO_TABLE "INSERT INTO `userinfo` ( `index` , `id` , `nickname` , `passwords` ) VALUES ( '', '%s', '%s', '%s' )"

/*#define SQL_INSERT_USERINFO_TABLE "INSERT INTO `userinfo` \
    ( `index`, `id`, `nickname`, `passwords` ) \
    VALUES ('', '%s', '%s', '%s')" */

int _tmain(int argc, _TCHAR* argv[])
{
	//Connection con("mmuser", "127.0.0.1", "root", "1124");

	//Query query = con.query();

	//MYSQL Con;
	MYSQL* pConn = NULL;

	pConn = mysql_init(NULL);

	mysql_real_connect(pConn, "localhost", "root", "1124", "mmuser", 3306, (char*) NULL, 0);

	if(pConn == (MYSQL*) NULL)
	{
		printf("Failed to access DB\n");

		return 0;
	}

	int query_stat; 
	char query[256];

	/*query_stat = mysql_query(pConn, SQL_CREATE_USERINFO_TABLE);

	if(query_stat != 0)
	{
		printf("Query error!!!\n");
	}*/

	//sprintf(query, SQL_INSERT_USERINFO_TABLE, "", "aaa", "aaa", "aaa");
	sprintf(query, "INSERT INTO userinfo VALUES('aaa')");
	query_stat = mysql_query(pConn, query);

	/*char buff[64];

	for(int i = 0; i < 10; i++)
	{
		sprintf(buff, "user%d\0", i);
		//sprintf(query, SQL_INSERT_USERINFO_TABLE, buff, buff, buff);
		sprintf(query, SQL_INSERT_USERINFO_TABLE, "aaa", "aaa", "aaa");

		query_stat = mysql_query(pConn, query);
		
		if(query_stat != 0)
		{
			printf("Query error!!!\n");
		}
	}*/

	mysql_close(pConn);

	getch();
	return 0;
}

