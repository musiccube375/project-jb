// SQL Test.cpp : 콘솔 응용 프로그램에 대한 진입점을 정의합니다.
//

#include "stdafx.h"
#include <conio.h>

#include "afxsock.h"
#include "mysql.h"

#pragma comment(lib, "libmysql")

int main(int argc, char **argv)
{
	char query[256];

	//sprintf(query, "mysqldump -uroot -p1124 mmuser > mmuser.sql");
	//system(query); 
	//sprintf(query, "mysqldump -uroot -p1124 mmuser > ..\\..\\..\\..\\DB(MY-SQL)\\mmuser.sql");
	//system(query); 

	//sprintf(query, "mysqldump -uroot -p1124 friendinfo > friendinfo.sql");
	//system(query); 
	sprintf(query, "mysql -uroot -p1124 friendinfo < friendinfo.sql");
	system(query); 

	// Restore
	//sprintf(query, "mysql -uroot -p1124 mmuser < mmuser.sql");
	//system(query); 

	/*MYSQL *conn = NULL;
	int query_stat;
	char query[256];
	MYSQL_RES *result;
	MYSQL_ROW row;

	// Initialization
	conn = mysql_init(NULL);

	// Connect
	mysql_real_connect(conn, "localhost", "root", "1124", "mmuser", 0, NULL, 0);

	if(conn == NULL)
	{
		printf("Failed to access DB");
		return 0;
	}*/

	// Main Server Admin Info Tables
	/*query_stat = mysql_query(conn, "CREATE TABLE mainsadmin( \
					idx INT AUTO_INCREMENT PRIMARY KEY, \
					id VARCHAR(32), \
					passwords VARCHAR(16), \
					level INT)");

	sprintf(query, "INSERT INTO mainsadmin VALUES('%d', '%s', '%s', '%d')", 0, "Admin", "admin", 1);
	query_stat = mysql_query(conn, query);

	// Middle Server Admin Info Tables
	query_stat = mysql_query(conn, "CREATE TABLE middlesadmin( \
					idx INT AUTO_INCREMENT PRIMARY KEY, \
					id VARCHAR(32), \
					passwords VARCHAR(16), \
					level INT)");

	sprintf(query, "INSERT INTO middlesadmin VALUES('%d', '%s', '%s', '%d')", 0, "Admin", "admin", 1);
	query_stat = mysql_query(conn, query);

	sprintf(query, "INSERT INTO middlesadmin VALUES('%d', '%s', '%s', '%d')", 0, "guest", "guest", 3);
	query_stat = mysql_query(conn, query);

	sprintf(query, "INSERT INTO middlesadmin VALUES('%d', '%s', '%s', '%d')", 0, "Bill", "1111", 2);
	query_stat = mysql_query(conn, query);

	sprintf(query, "INSERT INTO middlesadmin VALUES('%d', '%s', '%s', '%d')", 0, "Jack", "1111", 2);
	query_stat = mysql_query(conn, query);*/

	// Create Table
	/*query_stat = mysql_query(conn, "CREATE TABLE userinfo( \
					idx INT AUTO_INCREMENT PRIMARY KEY, \
					id VARCHAR(32), \
					nickname VARCHAR(128), \
					passwords VARCHAR(16))");*/

	//sprintf(query, "CREATE TABLE userinfo(index INT)");
	//query_stat = mysql_query(conn, query);

	/*if(query_stat != 0)
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
	//sprintf(query, "mysqldump -uroot -p1124 mmuser > c:\\mmuser.sql");
	//system(query); 
	//sprintf(query, "mysqldump -uroot -p1124 mmuser > ..\\..\\..\\..\\DB(MY-SQL)\\mmuser.sql");
	//system(query); 

	// Restore
	//sprintf(query, "mysql -uroot -p1124 mmuser < c:\\mmuser.sql");
	//system(query); 

	//sprintf(query, "SELECT userinfo INTO OUTFILE 'C:\\Documents and Settings\\Bill\\바탕 화면\\backup.sql'");
	//mysql_query(conn, query);

	// Insert value to the table
	/*sprintf(query, "INSERT INTO userinfo VALUES('%d', '%s', '%s', '%s')", 0, "Joyce", "Joy", "1124");
	query_stat = mysql_query(conn, query);

	sprintf(query, "INSERT INTO userinfo VALUES('%d', '%s', '%s', '%s')", 0, "Bill", "Billy", "6957");
	query_stat = mysql_query(conn, query);

	sprintf(query, "INSERT INTO userinfo VALUES('%d', '%s', '%s', '%s')", 0, "Jill", "Jilly", "1111");
	query_stat = mysql_query(conn, query);

	sprintf(query, "INSERT INTO userinfo VALUES('%d', '%s', '%s', '%s')", 0, "Jack", "JJ", "0000");
	query_stat = mysql_query(conn, query);*/

	//sprintf(query, "INSERT INTO userinfo VALUES('Joyce')");
	//query_stat = mysql_query(conn, query);

	//mysql_close(conn);

	getch();
}
