/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 27.
	Project	Name		: MSG Parser
	Version				: 1.00.01

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	MSG Parser Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

/*
	Class : MSG Parser Class

	Release Date		: 2008. 04. 27.
	Version				: 1.00.01
*/

class CMSGParser 
{
	friend class CWinSockMgr;

private:
	MSG_DATA m_msgData;
	bool m_bParseOK;

public:
	PMSG_DATA ParseMSG(const char* pszMsg);

protected:
	HRESULT ParseMSGHeader(const char* pszMsg);
	HRESULT ParseMSGMessage(const char* pszMsg);
	HRESULT ParseMSGTail(const char* pszMsg);

public:
	char* GetMessage();

public:
	CMSGParser();
	~CMSGParser();
};
