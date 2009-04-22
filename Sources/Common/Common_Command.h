/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 22.
	Project	Name		: Common Command
	Version				: 1.00.00

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Common Command Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once
 
// Main Server Command
#define MAIN_CMD_ADD_ID_REQ_TO_MIDDLE				0xCM01
#define MAIN_CMD_ADD_FRIEND_REQ_TO_MIDDLE			0xCM02

// Middle Server Command
#define MIDDLE_CMD_ADD_ID_REQ_TO_MAIN				0xCD01
#define MIDDLE_CMD_ADD_FRIEND_REQ_TO_MAIN			0xCD02
#define MIDDLE_CMD_ADD_ID_RET_TO_CLIENT				0xCD03
#define MIDDLE_CMD_ADD_FRIEND_RET_TO_CLIENT			0xCD04

// Client Command
#define CLIENT_CMD_ADD_ID_REQ_TO_MIDDLE				0xCC01
#define CLIENT_CMD_ADD_FRIENT_REQ_TO_MIDDLE			0xCC02
