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

bool CSQLMgr::IsValidAdminIDFromDB(const char* pszID)
{
	char query[256];

	sprintf(query, "SELECT id FROM mainsadmin WHERE id = '%s'", pszID);

	char * res = m_SQLDB.GetRow(query);

	if(res == NULL)
	{
		return false;
	}

	return true;
}

bool CSQLMgr::IsValidAdminPWFromDB(const char* pszID, const char* passwords)
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

bool CSQLMgr::IsValidUserIDFromDB(char* pszID)
{
	char query[256];

	for(int i = 0; i < MAX_ID_SIZE; i++)
	{
		if(pszID[i] == '0')
			pszID[i] = NULL;
	}

	sprintf(query, "SELECT id FROM userinfo WHERE id = '%s'", pszID);

	char* res = m_SQLDB.GetRow(query);

	if(res == NULL)
	{
		return true;
	}

	return false;
}

bool CSQLMgr::AddClientUser(const char* pszID, const char* passwords)
{
	char query[256];

	sprintf(query, "INSERT INTO userinfo VALUES('%d', '%s', '%s', '%d')", 0, pszID, "NONE", atoi(passwords));
	int query_stat = m_SQLDB.Query(query);

	if(query_stat != 0) return false;

	return true;
}