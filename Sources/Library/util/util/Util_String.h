/* 
	Author				: Bill Kim (kjh_900@hanmail.net, kjh_900@hotmail.com, BillKim@joyon.com)	
	Release Date		: 2008. 05. 26.
	File Name			: Utility String
	Version				: 1.00.08

	Test PC				: CPU - Pentium(R) 4 3.4 Ghz, RAM - 2 GB Graphic - NVIDIA Geforce 7800 GT
	Test OS				: Windows XP Home Professional + SP2
	Test Application	: Visual Studio 2003 + DirectX SDK 9.0c(Dec, 2006)
	
	Contents

	Utility String Header

	2008 ¨Ï Copyright MIS Corporation. All Rights Reserved.
*/ 

#pragma once

#include <strsafe.h>

#define MAX_STRING_SIZE		16384

// TCHAR -> ANSI
#define TCHAR_TO_ANSI(str) winUnicodeToAnsi((char*)appAlloca(winGetSizeAnsiByUnicode(str)),str,winGetSizeAnsiByUnicode(str))

// ANSI -> TCHAR
#define ANSI_TO_TCHAR(str) winAnsiToUnicode((S_TCHAR*) appAlloca(sizeof(S_TCHAR)*winGetSizeUnicodeByAnsi(str)),str,winGetSizeUnicodeByAnsi(str))

// TCHAR -> UTF8
#define TCHAR_TO_UTF8(str) winUnicodeToUtf8((char*)appAlloca(winGetSizeUtf8ByUnicode(str)),str,winGetSizeUtf8ByUnicode(str))

// UTF8 -> TCHAR
#define UTF8_TO_TCHAR(str) winUtf8ToUnicode((S_TCHAR*) appAlloca(sizeof(S_TCHAR)*winGetSizeUnicodeByUtf8(str)),str,winGetSizeUnicodeByUtf8(str))

// String Copy function(Multibyte & Unicode)
_DLL int StringCopy(char* pDest, const char* pSrc);

// String Copy function(Multibyte)
_DLL int StringCopyM(char* pDest, const char* pSrc);

// String Copy function(Unicode)
_DLL int StringCopyW(wchar_t* pDest, const wchar_t* pSrc);

// Compare two string(Multibyte & Unicode)
_DLL bool IsSameString(const char* pSrc1, const char* pSrc2);

// Compare two string(Multibyte)
_DLL bool IsSameStringM(const char* pSrc1, const char* pSrc2);

// Compare two string(Unicode)
_DLL bool IsSameStringW(const wchar_t* pSrc1, const wchar_t* pSrc2);

// Change the number(interger) to the string type(Multibyte & Unicode)
_DLL char* IToS(const int nIn);

// Change the number(interger) to the string type(Multibyte)
_DLL char* IToSM(const int nIn);

// Change the number(interger) to the string type(Unicode)
_DLL wchar_t* IToSW(const int nIn);

// Change the number(float) to the string type(Multibyte & Unicode)
_DLL char* FToS(const float fIn);

// Change the number(float) to the string type(Multibyte)
_DLL char* FToSM(const float fIn);

// Change the number(float) to the string type(Unicode)
_DLL wchar_t* FToSW(const float fIn);

// Change the string to the interger number(Multibyte & Unicode)
_DLL int SToI(const char* pszString);

// Change the string to the interger number(Multibyte)
_DLL int SToIM(const char* pszString);

// Change the string to the interger number(Unicode)
_DLL int SToIW(const char* pszString);

// Change the string to the float number(Multibyte & Unicode)
_DLL int SToF(const char* pszString);

// Change the string to the float number(Multibyte)
_DLL int SToFM(const char* pszString);

// Change the string to the float number(Unicode)
_DLL int SToFW(const char* pszString);

// Multyibyte to Wide Character String
_DLL int MultibyteToWide(wchar_t* pszDest, const char* pszSrc);

// Multyibyte to Wide Character String
_DLL wchar_t* MultibyteToWide(const char* pszSrc);

// Wide Character String to Multyibyte
_DLL int WideToMultibyte(char* pszDest, const wchar_t* pszSrc);

// Wide Character String to Multyibyte
_DLL char* WideToMultibyte(const wchar_t* pszSrc);

// CString -> char
_DLL int CStringToChar(char* pszDest, const CString str);

// CString -> char
_DLL char* CStringToChar(const CString str);

// CString -> wchar_t
_DLL int CStirngToWChar(wchar_t* pszDest, const CString str);

// Byte -> char
_DLL char* ByteToChar(BYTE* pbyData, int nSize);

// Byte -> text
_DLL char* ByteToText(BYTE* pbyData, int nSize);

// Byte -> text
_DLL char* ByteToHex(BYTE* pbyData, int nSize);