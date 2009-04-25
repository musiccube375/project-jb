/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 25.
	Project	Name		: SQL Manager
	Version				: 1.00.00

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	SQL Manager Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "SQL.h"

/*
	Class : SQL Manager Class

	Release Date		: 2009. 04. 25.
	Version				: 1.00.00
*/

class CSQLMgr
{
private:
	CSQL m_SQLDB;

public:
	inline CSQL* GetSQLDB() { return &m_SQLDB; }

public:
	HRESULT InitSQLMgr();
	void ReleaseSQLMgr();

public:
	bool IsValidIDFromDB(const char* pszID);
	bool IsValidPWFromDB(const char* pszID, const char* passwords);

public:
	// The basic constructor
	CSQLMgr();

	// The basic destructor
	~CSQLMgr();
};