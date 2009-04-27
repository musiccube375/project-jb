/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 25.
	Project	Name		: SQL 
	Version				: 1.00.00

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	SQL Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "mysql.h"

typedef MYSQL_RES RES;
typedef MYSQL_ROW ROW;

/*
	Class : SQL Class

	Release Date		: 2008. 04. 25.
	Version				: 1.00.00
*/

class CSQL 
{
private:
	MYSQL *m_pConn;

	char m_szUser[256];
	char m_szPasswords[64];
	char m_szDB[256];

public:
	char* GetUser() { return m_szUser; }

public:
	HRESULT InitSQL(const char* pszUser, const char* pszPasswords, const char* pszDB, const char* pszHost = "localhost");
	HRESULT ReleaseSQL();

	HRESULT Query(const char* pszQuery);
	char* GetRow(const char* pszQuery); // Use Select Query

	void Backup(const char* pszPath = "c:\\");
	void Restore(const char* pszPath = "c:\\");

public:
	CSQL();
	~CSQL();
};