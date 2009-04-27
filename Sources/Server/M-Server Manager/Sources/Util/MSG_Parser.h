/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 27.
	Project	Name		: MSG Parser
	Version				: 1.00.00

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	MSG Parser Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include <queue>

using namespace std;

/*
	Structure : MSGInfo Structure

	Release Date		: 2008. 04. 27.
	Version				: 1.00.00
*/

typedef struct _MSGINFO
{
	char szMsg[256];

	_MSGINFO(const char* pszMsg)
	{
		strcpy(szMsg, pszMsg);
	}

	_MSGINFO() { }
}MSGINFO, *PMSGINFO;

/*
	Class : MSG Queue Class

	Release Date		: 2008. 04. 27.
	Version				: 1.00.00
*/

class CMSGQueue
{
private:
	queue<MSGINFO> m_queueMSG;

public:
	void PushMSG(const char* pszMsg);
	PMSGINFO PopMSG();
	void ClearMSG();

	void ProcessMSG();

public:
	CMSGQueue();
	~CMSGQueue();
};

/*
	Class : MSG Parser Class

	Release Date		: 2008. 04. 27.
	Version				: 1.00.00
*/

class CMSGParser 
{
public:
	char* ParseMSG(const char* pszMsg);

public:
	CMSGParser();
	~CMSGParser();
};