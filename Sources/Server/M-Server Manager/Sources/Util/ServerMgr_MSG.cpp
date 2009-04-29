#include "stdAfx.h"
#include "ServerMgr_MSG.h"

void MSG_SendToServer(CClientSock* pSock, const char* pszSend)
{
	if(pSock == NULL) return;

	pSock->Send(pszSend, 512);
}

void MSG_ParseFromIndex(int nIndex, char* pszOutMsg, const char* pszMsg)
{
	int nMsgStartIndex = -1, nMsgEndIndex = -1;
	int nMsgIndexCount = 0;

	memset(pszOutMsg, 0, MSG_MAX_SIZE);

	if(nIndex == 0)
	{
		nMsgStartIndex = nIndex;

		for(int i = 0; i < MSG_MAX_SIZE; i++)
		{
			if(pszMsg[i] == 95) // '_'
			{
				nMsgEndIndex = i;
				break;
			}
		}
	}
	else
	{
		for(int i = 0; i < MSG_MAX_SIZE; i++)
		{
			if(pszMsg[i] == 95) // '_'
			{
				if(nMsgStartIndex == -1)
				{
					if(nIndex == nMsgIndexCount++)
					{
						nMsgStartIndex = i+1;
					}
				}
				else
				{
					nMsgEndIndex = i;
					break;
				}
			}
		}
	}

	for(int i = nMsgStartIndex; i < nMsgEndIndex; i++)
	{
		pszOutMsg[i] = pszMsg[i];
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

	int i;
	char szSize[1];

	szSize[0] = msg[0];

	int nIDSize = atoi(szSize);

	for(i = 0; i < nIDSize; i++)
	{
		id[i] = msg[i+1];
	}

	id[i] = NULL;

	szSize[0] = msg[i+1];

	int nPWSize = atoi(szSize);

	for(i = 0; i < nPWSize; i++)
	{
		pw[i] = msg[i+nIDSize+2];
	}

	pw[i] = NULL;

	// DB 에 유저 추가
	bool bSuccess = g_sToolMgr.GetSQLMgr()->AddClientUser(id, pw);

	if(bSuccess)
		msg[0] = MSG_PARSING_ADD_ID_OK;
	else msg[0] = MSG_PARSING_ADD_ID_FAIL;

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MAIN_CMD, CM_ADD_ID_RET_TO_MIDDLE, msg);

	MSG_SendToServer(pSock, send); 
}