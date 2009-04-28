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

void MSG_SendToQueryClient(const char* pszSend, int nIndex)
{
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
		          MSG_MIDDLE_TO_MAIN, MIDDLE_CMD, CD_ID_CHECK_RET_TO_CLIENT, msgData.msgMessage);

	// 인덱스 수정 필요
	MSG_SendToQueryClient(send, atoi(msgData.msgMessage));
}