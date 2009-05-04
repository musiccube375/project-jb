/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 29.
	Project	Name		: Message Handler
	Version				: 1.00.00

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Message Handler Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "CMD_Handler_CLT.h"

/*
	Class : MSG Handler Manager Class

	Release Date		: 2009. 04. 29.
	Version				: 1.00.00
*/

class CCMDHandlerMgr : public CCMDHandlerCLT
{
public:
	MSG_RET CMD_Main_Handle(MSG_DATA msgData);

public:
	CCMDHandlerMgr();
	~CCMDHandlerMgr();
};