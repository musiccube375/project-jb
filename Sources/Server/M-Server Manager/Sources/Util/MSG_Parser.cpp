#include "stdAfx.h"
#include "SQL.h"

CSQL::CSQL()
{
	m_pConn = NULL;
}

CSQL::~CSQL()
{
	//ReleaseSQL();
}

HRESULT CSQL::InitSQL(const char* pszUser, const char* pszPasswords, const char* pszDB, const char* pszHost)
{
	m_pConn = NULL;

	strcpy(m_szUser, "");
	strcpy(m_szPasswords, "");
	strcpy(m_szDB, "");

	// Initialization
	m_pConn = mysql_init(NULL);

	// Connect
	mysql_real_connect(m_pConn, pszHost, pszUser, pszPasswords, pszDB, 0, NULL, 0);

	if(m_pConn == NULL)
		return E_FAIL;

	strcpy(m_szUser, pszUser);
	strcpy(m_szPasswords, pszPasswords);
	strcpy(m_szDB, pszDB);

	return S_OK;
}

HRESULT CSQL::ReleaseSQL()
{	
	if(m_pConn == NULL) return E_FAIL;

	mysql_close(m_pConn);

	return S_OK;
}

HRESULT CSQL::Query(const char* pszQuery)
{
	int query_stat = mysql_query(m_pConn, pszQuery);

	if(query_stat != 0)
		return E_FAIL;

	return S_OK;
}

char* CSQL::GetRow(const char* pszQuery)
{
	HRESULT hr = Query(pszQuery);

	if(hr == E_FAIL)
		return NULL;

	RES* result = mysql_store_result(m_pConn);

	int num_fields = mysql_num_fields(result);

	ROW row = mysql_fetch_row(result);

	if(row == NULL)
		return NULL;

	char buff[512], temp[256];

	buff[0] = NULL;

	for(int i = 0; i < num_fields; i++)
	{
		temp[0] = NULL;

		sprintf(temp, "%s ", row[i] ? row[i] : NULL);
		strcat(buff, temp);
	}

	return buff;
}

void CSQL::Backup(const char* pszPath)
{
	char query[256];

	sprintf(query, "mysqldump -u%s -p%s %s > %s%s.sql", m_szUser, m_szPasswords, m_szDB, pszPath, m_szDB);
	system(query); 
}

void CSQL::Restore(const char* pszPath)
{
	char query[256];

	sprintf(query, "mysql -u%s -p%s %s < %s%s.sql", m_szUser, m_szPasswords, m_szDB, pszPath, m_szDB);
	system(query); 
}