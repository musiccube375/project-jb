#include "stdafx.h"
#include "BasicConfig.h"

HRESULT DeleteConfigFile(const char* pszFileName)
{
	CStringA strPath;

	strPath.Format(".\\%s.ini", pszFileName);

	DeleteFile(strPath);

	return S_OK;
}

HRESULT SetStringToConfig(const char* pszFileName, const char* pszAppName, 
						  const char* pszKeyName, const char* pszString)
{
	CStringA strPath;

	strPath.Format(".\\%s.ini", pszFileName);

	WritePrivateProfileString(pszAppName, pszKeyName, pszString, strPath);

	return S_OK;
}

HRESULT GetStringFromConfig(const char* pszFileName, const char* pszAppName, 
						    const char* pszKeyName, char* pszOutString)
{
	CFileFind FileFind;

	if(!FileFind.FindFile(pszFileName)) return E_FAIL;

	CStringA strPath;

	strPath.Format(".\\%s.ini", pszFileName);

	GetPrivateProfileString(pszAppName, pszKeyName, "", pszOutString, MAX_STRING_SIZE, strPath);

	return E_FAIL;
}