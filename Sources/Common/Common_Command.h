/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 22.
	Project	Name		: Common Command
	Version				: 1.00.01

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Common Command Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once
 
// Main Server Command
#define MAIN_CMD							0xCM
#define CM_ADD_ID_REQ_TO_MIDDLE				0x01
#define CM_ADD_FRIEND_REQ_TO_MIDDLE			0x02
#define CM_ID_CHECK_REQ_TO_MIDDLE			0x03

// Middle Server Command
#define MIDDLE_CMD							0xCD
#define CD_CONNECT_RET_TO_CLIENT			0x01
#define CD_ADD_ID_REQ_TO_MAIN				0x02
#define CD_ADD_FRIEND_REQ_TO_MAIN			0x03
#define CD_ADD_ID_RET_TO_CLIENT				0x04
#define CD_ADD_FRIEND_RET_TO_CLIENT			0x05
#define CD_ID_CHECK_RET_TO_CLIENT			0x06

// Client Command
#define CLIENT_CMD							0xCC
#define CC_CONNECT_REQ_TO_MIDDLE			0x01
#define CC_ADD_ID_REQ_TO_MIDDLE				0x02
#define CC_ADD_FRIENT_REQ_TO_MIDDLE			0x03
#define CC_ID_CHECK_REQ_TO_MIDDLE			0x04
