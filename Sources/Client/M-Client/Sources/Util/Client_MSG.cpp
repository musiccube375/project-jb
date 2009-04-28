#include "stdAfx.h"
#include "Client_MSG.h"
#include "Common_MSG_Generator.h"

void MSG_SendToServer(const char* pszSend)
{
	g_sToolMgr.GetWinSockMgr()->GetServerSock()->Send(pszSend, 512);
}

void MSG_ID_Check_Req()
{
	char send[512];
	char szIP[32];

	strcpy(szIP, g_sToolMgr.m_ServerList[g_sToolMgr.GetWinSockMgr()->GetServerCount()].szServerIP);

	MSG_Generator(send, UNKNOWNED_USER, szIP, MSG_CLIENT_TO_MIDDLE, CLIENT_CMD, CC_ID_CHECK_REQ_TO_MIDDLE);

	MSG_SendToServer(send);	
}