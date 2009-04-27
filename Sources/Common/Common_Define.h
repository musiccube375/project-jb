/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: Common Define
	Version				: 1.00.02

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Common Define Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "Common_Util.h"
#include "Common_MSG.h"
#include "Common_Command.h"
#include "Common_MSG_Type.h"
#include "Common_MSG_Generator.h"

#include "DialogSkin.h"

#include <map>

using namespace std;

#include "ServerSock.h"
#include "ClientSock.h"

#define MAIN_SERVER_PORT		9988
#define MIDDLE_SERVER_PORT		9989
#define CLIENT_USER_PORT		9990

#define LOCAL_HOST_IP			"127.0.0.1"

#define MAX_CLIENT_COUNT		5000

typedef map<int, CClientSock*>					CLIENTSOCK_MAP;
typedef map<int, CClientSock*>::iterator		CLIENTSOCK_MAP_IT;
typedef map<int, CClientSock*>::value_type		CLIENTSOCK_MAP_VALUE;

typedef struct _USERBASEINFO
{
	char	szID[32];
	char	szNick[128];
}USERBASEINFO, *PUSERBASEINFO;

typedef struct _USERINFO
{
	CClientSock*	pSock;
	USERBASEINFO	UserBase;
}USERINFO, *PUSERINFO;

typedef map<int, USERINFO>					USERINFO_MAP;
typedef map<int, USERINFO>::iterator		USERINFO_MAP_IT;
typedef map<int, USERINFO>::value_type		USERINFO_MAP_VALUE;