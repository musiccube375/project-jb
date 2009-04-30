#include "stdAfx.h"
#include "Server_MSG.h"

void MSG_SendToServerMgr(const char* pszSend)
{
	g_sToolMgr.GetWinSockMgr()->GetServerMgrSock()->Send(pszSend, 512);
}

void MSG_SendToClient(const char* pszSend, char* pszID)
{
	g_sToolMgr.GetWinSockMgr()->GetUser(pszID)->pSock->Send(pszSend, 512);
}

void MSG_Exit_Server_Req(MSG_DATA msgData)
{
	char send[512];
	char szID[512];

	//strcpy(szID, msgData.msgHeader.szFromID);
	//szID[MAX_ID_SIZE-2] = NULL;

	int nIndex = msgData.msgMessage[MSG_MAX_SIZE-1];
	g_sToolMgr.GetWinSockMgr()->DelUser(nIndex);

	/*if(strcmp(szID, "Unknowned User") == 0)
	{
		int nIndex = msgData.msgMessage[MSG_MAX_SIZE-1];
		g_sToolMgr.GetWinSockMgr()->DelUser(nIndex);
	}
	else
		MSG_SendToServerMgr(send); */
}

void MSG_SendToQueryClient(const char* pszSend, int nIndex)
{
	if(nIndex < 0 || nIndex >= g_sToolMgr.GetWinSockMgr()->GetUserSize()) return;

	g_sToolMgr.GetWinSockMgr()->GetUser(nIndex)->pSock->Send(pszSend, 512);
}

void MSG_ID_Check_Req(MSG_DATA msgData)
{
	char send[512];

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MIDDLE_CMD, CD_ID_CHECK_REQ_TO_CLIENT, msgData.msgMessage);

	MSG_SendToServerMgr(send); 
}

void MSG_ID_Check_Ack(MSG_DATA msgData)
{
	char send[512];

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_CLIENT, MIDDLE_CMD, CD_ID_CHECK_RET_TO_CLIENT, msgData.msgMessage);

	MSG_SendToQueryClient(send, atoi(&msgData.msgMessage[MSG_MAX_SIZE-1]));
}

void MSG_Add_ID_Req(MSG_DATA msgData)
{
	char send[512];

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MIDDLE_CMD, CD_ADD_ID_REQ_TO_MAIN, msgData.msgMessage);

	MSG_SendToServerMgr(send); 
}

void MSG_Add_ID_Ack(MSG_DATA msgData)
{
	char send[512];

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_CLIENT, MIDDLE_CMD, CD_ADD_ID_RET_TO_CLIENT, msgData.msgMessage);

	MSG_SendToQueryClient(send, atoi(&msgData.msgMessage[MSG_MAX_SIZE-1]));
}

void MSG_Login_Req(MSG_DATA msgData)
{
	char send[512];

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MIDDLE_CMD, CD_LOGIN_REQ_TO_CLIENT, msgData.msgMessage);

	MSG_SendToServerMgr(send); 
}

void MSG_Login_Ack(MSG_DATA msgData)
{
	char send[512];

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_CLIENT, MIDDLE_CMD, CD_LOGIN_RET_TO_CLIENT, msgData.msgMessage);

	MSG_SendToQueryClient(send, atoi(&msgData.msgMessage[MSG_MAX_SIZE-1]));
}