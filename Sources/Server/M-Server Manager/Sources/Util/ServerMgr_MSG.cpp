#include "stdAfx.h"
#include "ServerMgr_MSG.h"

void MSG_SendToServer(CClientSock* pSock, const char* pszSend)
{
	if(pSock == NULL) return;

	pSock->Send(pszSend, 512);
}

void MSG_Seperator(int nIndex, const char* msg, char* pOut)
{
	int nMsgCount = -1;
	int nMsgIndex = 0;
	int nMsgSize = strlen(msg);

	while(nMsgCount < nMsgSize)
	{
		char buff[512];
		char szNum[2];

		szNum[0] = msg[nMsgIndex++];
		szNum[1] = NULL;

		int nSize = atoi(szNum);

		memset(buff, 0, 512);

		int i;

		for(i = 0; i < nSize; i++)
		{
			buff[i] = msg[nMsgIndex++];
		}

		buff[i] = NULL;

		nMsgCount++;

		if(nIndex <= nMsgCount)
		{
			int nBuffSize = strlen(buff);

			for(i = 0; i < nBuffSize; i++)
			{
				pOut[i] = buff[i];
			}

			pOut[i] = NULL;

			return;
		}
	}
}

void MSG_ID_Check_Ack(MSG_DATA msgData, CClientSock* pSock)
{
	char send[512];
	
	// 메시지 첫 부분에 결과값을 입력
	if(g_sToolMgr.GetSQLMgr()->IsValidUserIDFromDB(msgData.msgHeader.szToID))
		msgData.msgMessage[0] = MSG_PARSING_ID_CHECK_OK;
	else msgData.msgMessage[0] = MSG_PARSING_ID_CHECK_FAIL;

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MAIN_CMD, CM_ID_CHECK_RET_TO_MIDDLE, msgData.msgMessage);

	MSG_SendToServer(pSock, send); 
}

void MSG_Add_ID_Ack(MSG_DATA msgData, CClientSock* pSock)
{
	char send[512];
	char msg[512];

	strcpy(msg, msgData.msgMessage);

	char id[MAX_ID_SIZE];
	char pw[MAX_PASSWORD_SIZE];

	MSG_Seperator(0, msg, id);
	MSG_Seperator(1, msg, pw);

	// DB 에 유저 추가
	bool bSuccess = g_sToolMgr.GetSQLMgr()->AddClientUser(id, pw);

	if(bSuccess)
		msg[0] = MSG_PARSING_ADD_ID_OK;
	else msg[0] = MSG_PARSING_ADD_ID_FAIL;

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MAIN_CMD, CM_ADD_ID_RET_TO_MIDDLE, msg);

	MSG_SendToServer(pSock, send); 
}

void MSG_Login_Ack(MSG_DATA msgData, CClientSock* pSock)
{
	char send[512];
	char msg[512];

	strcpy(msg, msgData.msgMessage);

	char id[MAX_ID_SIZE];
	char pw[MAX_PASSWORD_SIZE];

	MSG_Seperator(0, msg, id);
	MSG_Seperator(1, msg, pw);

	// DB 에서 유저 체크
	bool bSuccess = g_sToolMgr.GetSQLMgr()->CheckUser(id, pw);

	if(bSuccess)
		msg[0] = MSG_PARSING_LOGIN_OK;
	else msg[0] = MSG_PARSING_LOGIN_FAIL;

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MAIN_CMD, CM_LOGIN_RET_TO_MIDDLE, msg);

	MSG_SendToServer(pSock, send); 
}