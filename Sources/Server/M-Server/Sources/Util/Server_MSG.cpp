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

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MIDDLE_CMD, CD_EXIT_SERVER_REQ_TO_CLIENT, msgData.msgMessage);

	// 익명 유저라면 그냥 유저 정보 데이터만 삭제
	if(strcmp(msgData.msgHeader.szFromID, "Unknowned User\0") == 0)
	{

	}
	else
		MSG_SendToServerMgr(send); 
}

void MSG_SendToQueryClient(const char* pszSend, int nIndex)
{
	int nSize = g_sToolMgr.GetWinSockMgr()->GetUserQuerySize();

	if(nIndex < 0 || nIndex >= g_sToolMgr.GetWinSockMgr()->GetUserQuerySize()) return;

	g_sToolMgr.GetWinSockMgr()->GetUserQuery(nIndex)->pSock->Send(pszSend, 512);
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