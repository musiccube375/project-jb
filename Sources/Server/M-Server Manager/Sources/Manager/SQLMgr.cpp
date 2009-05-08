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
	m_SQLFriendDB.InitSQL("root", "1124", "friendinfo");

	return S_OK;
}

void CSQLMgr::ReleaseSQLMgr()
{
	m_SQLDB.ReleaseSQL();	
	m_SQLFriendDB.ReleaseSQL();
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

bool CSQLMgr::CheckUser(const char* pszID, const char* passwords)
{
	char query[256];

	sprintf(query, "SELECT passwords FROM userinfo WHERE id = '%s'", pszID);

	char* res = m_SQLDB.GetRow(query);

	if(res == NULL) return false;

	res[strlen(res)-1] = NULL;

	if(strcmp(passwords, res) == 0)
		return true;

	return false;
}

bool CSQLMgr::CreateTableFriendDB(const char* pszID)
{
	char query[256];
	char table[256];

	memset(table, 0, 256);

	sprintf(table, "%s_friend_list", pszID);
	sprintf(query, "CREATE TABLE %s(id VARCHAR(32) PRIMARY KEY, msg VARCHAR(128), verify INT, deny INT)", table);

	int query_stat = m_SQLFriendDB.Query(query);

	if(query_stat != 0) return false;

	return true;
}

bool CSQLMgr::AddFriendUser(const char* pszID, const char* pszFriendID, char* pszMessage, 
							bool bVerify, bool bDeny)
{
	char query[256];
	char table[256];

	memset(table, 0, 256);
	sprintf(table, "%s_friend_list", pszID);
	
	sprintf(query, "INSERT INTO %s VALUES('%s', '%s', '%d', '%d')", table, pszFriendID, pszMessage, bVerify, bDeny);
	int query_stat = m_SQLFriendDB.Query(query);

	if(query_stat != 0) return false;

	return true;
}

bool CSQLMgr::UpdateFriendUser(const char* pszID, const char* pszFriendID, bool bVerify, bool bDeny)
{
	char query[256];
	char table[256];

	memset(table, 0, 256);
	sprintf(table, "%s_friend_list", pszID);
	
	sprintf(query, "UPDATE %s SET verify = %d deny = %d WHERE id = '%s', table, pszFriendID, bVerify, bDeny");
	int query_stat = m_SQLFriendDB.Query(query);

	if(query_stat != 0) return false;

	return true;
}

bool CSQLMgr::DeleteFriendUser(const char* pszID, const char* pszFriendID)
{
	char query[256];
	char table[256];

	memset(table, 0, 256);
	sprintf(table, "%s_friend_list", pszID);
	
	sprintf(query, "DELETE FROM %s WHERE id = '%s'", table, pszFriendID, pszFriendID);
	int query_stat = m_SQLFriendDB.Query(query);

	if(query_stat != 0) return false;

	return true;
}