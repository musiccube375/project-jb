/* 
	Author				: ������(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 29.
	Project	Name		: Message Handler(Client)
	Version				: 1.00.00

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Message Handler(Client) Header

	2009 �� Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

/*
	Class : CMD Handler CLT Class

	Release Date		: 2009. 04. 29.
	Version				: 1.00.00
*/

class CCMDHandlerCLT
{
protected:
	MSG_RET CMD_MDS_Handle(MSG_DATA msgData);

public:
	CCMDHandlerCLT();
	~CCMDHandlerCLT();
};