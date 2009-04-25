#include "stdafx.h"
#include "SQLMgr.h"

CSQLMgr::CSQLMgr()
{
	
}

CSQLMgr::~CSQLMgr()
{
	
}

HRESULT CSQLMgr::InitSQLMgr()
{
	m_SQLDB.InitSQL("root", "1124", "mmuser");

	return S_OK;
}

void CSQLMgr::ReleaseSQLMgr()
{
	m_SQLDB.ReleaseSQL();	
}

bool CSQLMgr::IsValidIDFromDB(const char* pszID)
{
	char query[256];
	char* res;
	char buff[256];

	sprintf(query, "SELECT id FROM mainsadmin WHERE id = '%s'", pszID);

	res = m_SQLDB.GetRow(query);

	if(res == NULL)
	{
		return false;
	}

	return true;
}

bool CSQLMgr::IsValidPWFromDB(const char* pszID, const char* passwords)
{
	char query[256];

	sprintf(query, "SELECT passwords FROM mainsadmin WHERE id = '%s'", pszID);

	char* res = m_SQLDB.GetRow(query);

	res[strlen(res)-1] = NULL;

	if(strcmp(res, passwords) == 0)
	{
		return true;
	}

	return false;
}