/* 
	Author				: Bill Kim (kjh_900@hanmail.net, kjh_900@hotmail.com, BillKim@joyon.com)	
	Release Date		: 2009. 04. 08.
	File Name			: Basic Config
	Version				: 1.00.00

	Test PC				: CPU - Pentium(R) 4 3.4 Ghz, RAM - 2 GB Graphic - NVIDIA Geforce 7800 GT
	Test OS				: Windows XP Home Professional + SP2
	Test Application	: Visual Studio 2003 + DirectX SDK 9.0c(Dec, 2006)
	
	Contents

	Basic Config Header

	2008 ¨Ï Copyright MIS Corporation. All Rights Reserved.
*/ 

#pragma once

#define MAX_STRING_SIZE		1024

HRESULT DeleteConfigFile(const char* pszFileName);

HRESULT SetStringToConfig(const char* pszFileName, const char* pszAppName, 
						  const char* pszKeyName, const char* pszString);

HRESULT GetStringFromConfig(const char* pszFileName, const char* pszAppName, 
						    const char* pszKeyName, char* pszOutString);