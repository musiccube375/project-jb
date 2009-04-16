// SQL Test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>

#include "afxsock.h"
#include "mysql.h"

#pragma comment(lib, "libmysql")

int main(int argc, char **argv)
{
	MYSQL *conn;
	int query_stat;
	char query[256];
	MYSQL_RES *result;
	MYSQL_ROW row;

	// Initialization
	conn = mysql_init(NULL);

	// Connect
	mysql_real_connect(conn, "localhost", "root", "1124", "mmuser", 0, NULL, 0);

	// Create Table
	/*query_stat = mysql_query(conn, "CREATE TABLE userinfo( \
					index INT NOT NULL AUTO_INCREMENT PRIMARY KEY, \
					id VARCHAR(32), \
					nickname VARCHAR(128), \
					passwords VARCHAR(16))");

	if(query_stat != 0)
		printf("Query Failed!!!\n");

	// Insert value to the table
	sprintf(query, "INSERT INTO userinfo VALUES('%d', '%s', '%s', '%s')", 0, "Joyce", "Joy", "1124");
	//query_stat = mysql_query(conn, query);

	if(query_stat != 0)
		printf("Query Failed!!!\n");

	// Select
	mysql_query(conn, "SELECT * FROM userinfo");
	result = mysql_store_result(conn);

	// Get all values from the table
	int num_fields = mysql_num_fields(result);

	while((row = mysql_fetch_row(result)))
	{
		for(int i = 0; i < num_fields; i++)
		{
			printf("%s ", row[i] ? row[i] : "NULL");
		}

		printf("\n");
	}

	// Update
	sprintf(query, "UPDATE userinfo SET nickname = 'Love Joyce' WHERE id = 'Bill'");
	query_stat = mysql_query(conn, query);

	if(query_stat != 0)
		printf("Query Failed!!!\n");

	// Select
	mysql_query(conn, "SELECT * FROM userinfo");
	result = mysql_store_result(conn);

	// Get all values from the table
	num_fields = mysql_num_fields(result);

	while((row = mysql_fetch_row(result)))
	{
		for(int i = 0; i < num_fields; i++)
		{
			printf("%s ", row[i] ? row[i] : "NULL");
		}

		printf("\n");
	}

	// Delete 
	sprintf(query, "DELETE FROM userinfo WHERE id = 'Bill'");
	query_stat = mysql_query(conn, query);

	if(query_stat != 0)
		printf("Query Failed!!!\n");

	// Select
	mysql_query(conn, "SELECT * FROM userinfo");
	result = mysql_store_result(conn);

	// Get all values from the table
	num_fields = mysql_num_fields(result);

	while((row = mysql_fetch_row(result)))
	{
		for(int i = 0; i < num_fields; i++)
		{
			printf("%s ", row[i] ? row[i] : "NULL");
		}

		printf("\n");
	}*/

	// Backup
	sprintf(query, "/usr/local/bin/mysqldump userinfo > C:\Documents and Settings\Bill\바탕 화면\backup.sql");
	//sprintf(query, "C:\\Program Files\\MySQL\\MySQL Server 5.1\\bin\\mysqldump %s > backup.sql", "C:\\Documents and Settings\Bill\\바탕 화면\\");
	system(query); 

	//sprintf(query, "SELECT userinfo INTO OUTFILE 'C:\\Documents and Settings\\Bill\\바탕 화면\\backup.sql'");
	//mysql_query(conn, query);

	mysql_close(conn);

	getch();
}
