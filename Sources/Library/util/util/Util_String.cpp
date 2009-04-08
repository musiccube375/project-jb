#include "stdafx.h"
#include "Util_String.h"

// String Copy function(Multibyte & Unicode)
#ifdef _UNICODE
int StringCopy(wchar_t* pDest, const wchar_t* pSrc)
#else
int StringCopy(char* pDest, const char* pSrc)
#endif
{
	int nRet;

#ifdef _UNICODE
	nRet = StringCchCopyW(pDest, pSrc);
#else 
	nRet = StringCopyM(pDest, pSrc);
#endif

	return nRet;
}

// String Copy function(Multibyte)
int StringCopyM(char* pDest, const char* pSrc)
{
	if(pSrc == NULL) return 0;

	StringCchCopy(pDest, MAX_STRING_SIZE, pSrc);
	pDest[strlen(pSrc)] = NULL;

	return 1;
}

// String Copy function(Unicode)
int StringCopyW(wchar_t* pDest, const wchar_t* pSrc)
{
	if(pSrc == NULL) return 0;

	StringCchCopyW(pDest, MAX_STRING_SIZE, pSrc);
	pDest[wcslen(pSrc)] = NULL;

	return 1;
}

// Compare two strings(Multibyte & Unicode)
#ifdef _UNICODE
bool IsSameString(const wchar_t* pSrc1, const wchar_t* pSrc2)
#else
bool IsSameString(const char* pSrc1, const char* pSrc2)
#endif
{
	bool bRet;

#ifdef _UNICODE
	bRet = IsSameStringW(pSrc1, pSrc2);
#else 
	bRet = IsSameStringM(pSrc1, pSrc2);
#endif

	return bRet;
}

// Compare two strings(Multibyte)
bool IsSameStringM(const char* pSrc1, const char* pSrc2)
{
	if(pSrc1 == NULL) return false;
	if(pSrc2 == NULL) return false;

	if(strcmp(pSrc1, pSrc2) == 0) return true;

	return false;
}

// Compare two strings(Unicode)
bool IsSameStringW(const wchar_t* pSrc1, const wchar_t* pSrc2)
{
	if(pSrc1 == NULL) return false;
	if(pSrc2 == NULL) return false;

	if(wcscmp(pSrc1, pSrc2) == 0) return true;

	return false;
}

// Change the number(interger) to the string type(Multibyte & Unicode)
#ifdef _UNICODE
wchar_t* IToS(const int nIn)
#else
char* IToS(const int nIn)
#endif
{
#ifdef _UNICODE
	return IToSW(nIn);
#else
	return IToSM(nIn);
#endif
}

// Change the number(interger) to the string type(Multibyte)
char* IToSM(const int nIn)
{
	char buff[MAX_STRING_SIZE];

	sprintf(buff, "%d", nIn);
	
	return buff;
}

// Change the number(interger) to the string type(Unicode)
wchar_t* IToSW(const int nIn)
{
	wchar_t buff[MAX_STRING_SIZE];

	swprintf(buff, L"%d", nIn);
	
	return buff;
}

// Change the number(interger) to the string type(Multibyte & Unicode)
#ifdef _UNICODE
wchar_t* FToS(const float nIn)
#else
char* FToS(const float nIn)
#endif
{
#ifdef _UNICODE
	return FToSW(nIn);
#else
	return FToSM(nIn);
#endif
}

// Change the number(float) to the string type(Multibyte)
char* FToSM(const float fIn)
{
	char buff[MAX_STRING_SIZE];

	sprintf(buff, "%f", fIn);
	buff[strlen(buff)] = NULL;
	
	return buff;
}

// Change the number(float) to the string type(Unicode)
wchar_t* FToSW(const float fIn)
{
	wchar_t buff[MAX_STRING_SIZE];

	swprintf(buff, L"%f", fIn);
	buff[wcslen(buff)] = NULL;

	return buff;
}

// Change the string to the interger number(Multibyte & Unicode)
#ifdef _UNICODE
int SToI(const wchar_t* pwszString)
#else
int SToI(const char* pszString)
#endif
{
#ifdef _UNICODE
	return SToIW(pwszString);
#else
	return SToIM(pszString);
#endif
}

// Change the string to the interger number(Multibyte)
int SToIM(const char* pszString)
{
	return atoi(pszString);
}

// Change the string to the interger number(Unicode)
int SToIW(const wchar_t* pszString)
{
	return _wtoi(pszString);
}

// Change the string to the float number(Multibyte & Unicode)
#ifdef _UNICODE
int SToF(const wchar_t* pszString)
#else
int SToF(const char* pszString)
#endif
{
#ifdef _UNICODE
	return SToFW(pszString);
#else
	return SToFM(pszString);
#endif
}

// Change the string to the float number(Multibyte)
int SToFM(const char* pszString)
{
	return atof(pszString);
}

// Change the string to the float number(Unicode)
int SToFW(const wchar_t* pszString)
{
	return _wtof(pszString);
}

// Multyibyte to Wide Character String
int MultibyteToWide(wchar_t* pszDest, const char* pszSrc)
{
	return MultiByteToWideChar(CP_ACP, 0, pszSrc, strlen(pszSrc)+1, pszDest, NULL);
}

// Multyibyte to Wide Character String
wchar_t* MultibyteToWide(const char* pszSrc)
{
	wchar_t szDest[MAX_STRING_SIZE];

	MultiByteToWideChar(CP_ACP, 0, pszSrc, strlen(pszSrc)+1, szDest, NULL);

	return szDest;
}

// Wide Character String to Multyibyte
int WideToMultibyte(char* pszDest, const wchar_t* pszSrc)
{
	/*int nLen = wcstombs(pszDes, pszSrc, 100);

	nLen = WideCharToMultiByte(CP_ACP, 0, pszSrc, -1, NULL, 0, NULL, NULL);
	
	if(nLen)
	{
		return WideCharToMultiByte(CP_ACP, 0, pszSrc, -1, pszDes, nLen, NULL, NULL);
	}*/

	return WideCharToMultiByte(CP_ACP, 0, pszSrc, -1, pszDest, 0, NULL, NULL);
}

// Wide Character String to Multyibyte
char* WideToMultibyte(const wchar_t* pszSrc)
{
	char szDest[MAX_STRING_SIZE];

	WideCharToMultiByte(CP_ACP, 0, pszSrc, -1, szDest, 0, NULL, NULL);

	return szDest;
}

// CString -> char
int CStringToChar(char* pszDest, const CString str)
{
	if(str.IsEmpty()) return 0;

	pszDest = (LPSTR) (LPCSTR) str;

	return 1;
}

// CString -> char
char* CStringToChar(const CString str)
{
	if(str.IsEmpty()) return 0;

	char pszDest[MAX_STRING_SIZE];
	wsprintf(pszDest, "%s", str);

	//char* pszDest = str.GetBuffer(str.GetLength());

	//char* pszDest = (LPSTR) (LPCSTR) str;

	return pszDest;
}

// CString -> wchar_t
int CStirngToWChar(wchar_t* pszDest, const CString str)
{
	if(str.IsEmpty()) return 0;

	char* pszBuff = NULL;
	pszBuff = (LPSTR) (LPCSTR) str;

	mbstowcs(pszDest, pszBuff, MAX_STRING_SIZE);

	return 1;
}

// Byte -> char
char* ByteToChar(BYTE* pbyData, int nSize)
{
	/*char buff[1024];

	for(int i = 0; i < nSize; i++)
	{
		buff[i] = pbyData[i];
	}

	buff[nSize-1] = NULL;

	return buff;*/

	CString str;
	char buff[MAX_STRING_SIZE];

	if(nSize >= MAX_STRING_SIZE) return NULL;

	for(int i = 0; i < nSize; i++)
	{
		sprintf(buff, "%d", pbyData[i]);
		str += buff;
	}

	return CStringToChar(str);
}

// Byte -> text
char* ByteToText(BYTE* pbyData, int nSize)
{
	CString str;
	char buff[MAX_STRING_SIZE];

	if(nSize >= MAX_STRING_SIZE) return NULL;

	for(int i = 0; i < nSize; i++)
	{
		sprintf(buff, "%c", pbyData[i]);
		str += buff;
	}

	return CStringToChar(str);
}

// Byte -> text
char* ByteToHex(BYTE* pbyData, int nSize)
{
	CString str;
	char buff[MAX_STRING_SIZE];

	if(nSize >= MAX_STRING_SIZE) return NULL;

	for(int i = 0; i < nSize; i++)
	{
		sprintf(buff, "%02X ", pbyData[i]);
		str += buff;
	}

	return CStringToChar(str);
}