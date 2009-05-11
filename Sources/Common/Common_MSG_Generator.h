/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 27.
	Project	Name		: Common Message Generator
	Version				: 1.00.01

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Common Message Generator Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

HRESULT MSG_Generator(char* pszOutMessage, char* pszFrom, char* pszTo, 
				      int nType, int nCmdType, int nCmdData, char* pszMessage = NULL);
