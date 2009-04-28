#include "stdAfx.h"
#include "ServerMgr_MSG.h"

void MSG_SendToServer(const char* pszSend)
{
	g_sToolMgr.GetWinSockMgr()->GetServerSock()->Send(pszSend, 512);
}

void MSG_ID_Check_Ack(MSG_DATA msgData)
{
	char send[512];

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MAIN_CMD, CM_ID_CHECK_REQ_TO_MIDDLE, msgData.msgMessage);

	MSG_SendToServer(send); 
}