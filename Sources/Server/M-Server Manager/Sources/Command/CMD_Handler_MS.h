/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 27.
	Project	Name		: Message Handler(Main Server)
	Version				: 1.00.01

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Message Handler(Main Server) Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

/*
	Class : CMD Handler MS Class

	Release Date		: 2008. 04. 27.
	Version				: 1.00.00
*/

class CCMDHandlerMS
{
protected:
	PMSG_DATA CMD_MS_Handle(MSG_DATA msgData, CClientSock* pSock);

public:
	CCMDHandlerMS();
	~CCMDHandlerMS();
};