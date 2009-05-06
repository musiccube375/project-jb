/* 
	Author				: 김정훈(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: Common Define
	Version				: 1.00.10

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Common Define Header

	2009 ⓒ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "Common_Util.h"
#include "Common_MSG.h"
#include "Common_Command.h"
#include "Common_MSG_Type.h"
#include "Common_MSG_Generator.h"

#include "DialogSkin.h"

#include <map>
#include <queue>

using namespace std;

#include "ServerSock.h"
#include "ClientSock.h"

#define MAIN_SERVER_PORT		9988
#define MIDDLE_SERVER_PORT		9989
#define CLIENT_USER_PORT		9990

#define LOCAL_HOST_IP			"127.0.0.1"

#define MAX_SERVER_COUNT		16
#define MAX_CLIENT_COUNT		5000

#define INDEX_SYNTAX			0
#define INDEX_FROMID			3
#define INDEX_TOID				19
#define INDEX_TYPE				35
#define INDEX_CMDTYPE			36
#define INDEX_CMDDATA			37
#define INDEX_MSGLEN			38
#define INDEX_MSG				39

#define MSG_MAX_SIZE			256

#define TAG_MAIN_SERVER			0x01
#define TAG_MIDDLE_SERVER		0x02
#define TAG_CLIENT				0x03

#define MAX_INT_SIZE			214783600

enum MSG_RET
{
	MSG_RET_ERROR = 0,
	MSG_RET_NONE,

	MSG_CONNECT_SUCCESS,
	MSG_CONNECT_FAIL,

	MSG_PARSING_ID_CHECK_OK,
	MSG_PARSING_ID_CHECK_FAIL,

	MSG_PARSING_ADD_ID_OK,
	MSG_PARSING_ADD_ID_FAIL,

	MSG_PARSING_LOGIN_OK,
	MSG_PARSING_LOGIN_FAIL,

	MSG_PARSING_ADD_FRIEND_OK,
	MSG_PARSING_ADD_FRIEND_FAIL,
};

enum USER_STATE
{
	USER_STATE_ONLINE = 0,		// 온라인
	USER_STATE_OFFLINE,			// 오프라인
	USER_STATE_BUSY,			// 다른 용무중
	USER_STATE_NOT_MY_DESK,		// 자리 비움
	USER_STATE_ON_THE_PHONE,	// 통화중
	USER_STATE_BE_RIGHT_BACK,	// 곧 돌아오겠음
};

typedef map<int, CClientSock*>					CLIENTSOCK_MAP;
typedef map<int, CClientSock*>::iterator		CLIENTSOCK_MAP_IT;
typedef map<int, CClientSock*>::value_type		CLIENTSOCK_MAP_VALUE;

/*
	Structure : USER BASEINFO Structure

	Release Date		: 2009. 04. 15.
	Version				: 1.00.00
*/

typedef struct _USERBASEINFO
{
	char	szID[32];
	char	szNick[128];
}USERBASEINFO, *PUSERBASEINFO;

/*
	Structure : USER INFO Structure

	Release Date		: 2009. 04. 15.
	Version				: 1.00.00
*/

typedef struct _USERINFO
{
	CClientSock*	pSock;
	USERBASEINFO	UserBase;
}USERINFO, *PUSERINFO;

typedef map<int, USERINFO>					USERINFO_MAP;
typedef map<int, USERINFO>::iterator		USERINFO_MAP_IT;
typedef map<int, USERINFO>::value_type		USERINFO_MAP_VALUE;

/*
	Structure : MSG HEADER Structure

	Release Date		: 2009. 04. 27.
	Version				: 1.00.00
*/

typedef struct _MSG_HEADER
{
	char szHead[3];
	char szFromID[MAX_ID_SIZE];
	char szToID[MAX_ID_SIZE];
	int nType;
	int nCommandType;
	int nCommandData;
	int nMsgLen;
}MSG_HEADER, *PMSG_HEADER;

/*
	Structure : MSG DATA Structure

	Release Date		: 2009. 04. 27.
	Version				: 1.00.01
*/

typedef struct _MSG_DATA
{
	MSG_HEADER msgHeader;
	char msgMessage[MSG_MAX_SIZE];
	char msgTail[3];

	bool IsValidHeader()
	{
		if(msgHeader.szHead[0] == 'S' &&
		   msgHeader.szHead[1] == 'O' &&
		   msgHeader.szHead[2] == 'M')
			return true;

		return false;
	}
}MSG_DATA, *PMSG_DATA;

/*
	Structure : MSERVER Structure

	Release Date		: 2009. 04. 28.
	Version				: 1.00.00
*/

typedef struct _MSERVERINFO
{
	char szIP[32];
	CClientSock*	pSock;
}MSERVERINFO, *PMSERVERINFO;

typedef map<int, MSERVERINFO>				MSERVERINFO_MAP;
typedef map<int, MSERVERINFO>::iterator		MSERVERINFO_MAP_IT;
typedef map<int, MSERVERINFO>::value_type	MSERVERINFO_MAP_VALUE;

/*
	Structure : MAIN SERVER USER INFO Structure

	Release Date		: 2009. 05. 04.
	Version				: 1.00.01
*/

typedef struct _MSUSERINFO
{
	USERBASEINFO UserBase;
	char szServer[16];

	// 서버
	// 아이디
	// 친구 리스트
}MSUSERINFO, *PMSUSERINFO;

typedef map<int, MSUSERINFO>				MSUSERINFO_MAP;
typedef map<int, MSUSERINFO>::iterator		MSUSERINFO_MAP_IT;
typedef map<int, MSUSERINFO>::value_type	MSUSERINFO_MAP_VALUE;