#include "stdAfx.h"
#include "Server_MSG.h"

void MSG_SendToServerMgr(const char* pszSend)
{
	g_sToolMgr.GetWinSockMgr()->GetServerMgrSock()->Send(pszSend, 512);
}

void MSG_SendToClient(const char* pszSend, char* pszID)
{
	char id[MAX_ID_SIZE];

	int i;
	int nSize = strlen(pszID);

	for(i = 0; i < nSize; i++)
	{
		if(pszID[i] == '0')
			break;

		id[i] = pszID[i]; 
	}

	id[i] = NULL;

	nSize = g_sToolMgr.GetWinSockMgr()->GetUserSize();
	PUSERINFO pUserInfo = g_sToolMgr.GetWinSockMgr()->GetUser(id);

	if(pUserInfo == NULL) return;

	pUserInfo->pSock->Send(pszSend, 512);
}

void MSG_Exit_Server_Req(MSG_DATA msgData)
{
	char send[512];
	char szID[256];

	strcpy(szID, msgData.msgHeader.szFromID);
	szID[MAX_ID_SIZE-2] = NULL;

	if(strcmp(szID, "Unknowned User") == 0)
	{
		int nIndex = msgData.msgMessage[MSG_MAX_SIZE-1] - 48;
		g_sToolMgr.GetWinSockMgr()->DelUser(nIndex);
	}
	else g_sToolMgr.GetWinSockMgr()->DelUser(szID);

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MIDDLE_CMD, CD_EXIT_SERVER_REQ_TO_MAIN, msgData.msgMessage);

	MSG_SendToServerMgr(send); 
}

void MSG_SendToQueryClient(const char* pszSend, int nIndex, char* pszID)
{
	if(nIndex < 0 || nIndex >= g_sToolMgr.GetWinSockMgr()->GetUserSize()) return;

	CClientSock* pSock = g_sToolMgr.GetWinSockMgr()->GetUser(nIndex)->pSock;

	pSock->Send(pszSend, 512);

	g_sToolMgr.GetWinSockMgr()->GetUser(nIndex)->pSock = pSock;

	for(int i = 0; i < MAX_ID_SIZE; i++)
	{
		g_sToolMgr.GetWinSockMgr()->GetUser(nIndex)->UserBase.szID[i] = pszID[i];
	}
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

	int i;
	char id[MAX_ID_SIZE];

	for(i = 0; i < MAX_ID_SIZE; i++)
	{
		if(msgData.msgMessage[i+1] == '_')
			break;

		id[i] = msgData.msgMessage[i+1];
	}

	id[i] = NULL;

	MSG_SendToQueryClient(send, atoi(&msgData.msgMessage[MSG_MAX_SIZE-1]), id);
}

void MSG_Add_Friend_Req(MSG_DATA msgData)
{
	char send[512];

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MIDDLE_CMD, CD_ADD_FRIEND_REQ_TO_MAIN, msgData.msgMessage);

	MSG_SendToServerMgr(send); 
}

void MSG_Add_Friend_Ack(MSG_DATA msgData)
{
	char send[512];

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_CLIENT, MIDDLE_CMD, CD_ADD_FRIEND_RET_TO_CLIENT, msgData.msgMessage);

	MSG_SendToClient(send, msgData.msgHeader.szFromID);
}