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
	{
		// Friend table 도 같이 생성
		g_sToolMgr.GetSQLMgr()->CreateTableFriendDB(id);

		msg[0] = MSG_PARSING_ADD_ID_OK;
	}
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
	char server[256];

	MSG_Seperator(0, msg, id);
	MSG_Seperator(1, msg, pw);
	MSG_Seperator(2, msg, server);

	// DB 에서 유저 체크
	bool bSuccess = g_sToolMgr.GetSQLMgr()->CheckUser(id, pw);

	if(bSuccess)
	{
		msg[0] = MSG_PARSING_LOGIN_OK;
	
		MSUSERINFO MSUserInfo;

		strcpy(MSUserInfo.UserBase.szID, id);
		strcpy(MSUserInfo.szServer, server);

		g_sToolMgr.GetWinSockMgr()->AddMSUserInfo(MSUserInfo);
		g_sToolMgr.GetDialogMgr()->m_UserDlg.AddList(id, id, "온라인");
		g_sToolMgr.GetDialogMgr()->m_UserDlg.SetUserCount(g_sToolMgr.GetWinSockMgr()->GetMSUserInfoCount());
	}
	else msg[0] = MSG_PARSING_LOGIN_FAIL;

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MAIN_CMD, CM_LOGIN_RET_TO_MIDDLE, msg);

	MSG_SendToServer(pSock, send); 
}

void MSG_LogOut_Ack(MSG_DATA msgData)
{
	char id[256];

	memset(id, 0, 256);

	for(int i = 0; i < 256; i++)
	{
		if(msgData.msgHeader.szFromID[i] == '0')
			break;

		id[i] = msgData.msgHeader.szFromID[i];
	}

	g_sToolMgr.GetWinSockMgr()->DelMSUserInfo(id);
	g_sToolMgr.GetDialogMgr()->m_UserDlg.DelList(id);
	g_sToolMgr.GetDialogMgr()->m_UserDlg.SetUserCount(g_sToolMgr.GetWinSockMgr()->GetMSUserInfoCount());
}

void MSG_Add_Friend_Ack(MSG_DATA msgData, CClientSock* pSock)
{
	char send[512];
	char msg[512];

	strcpy(msg, msgData.msgMessage);

	char friendid[MAX_ID_SIZE];

	MSG_Seperator(0, msg, friendid);

	// DB 에서 친구 ID 체크
	bool bSuccess = g_sToolMgr.GetSQLMgr()->IsValidUserIDFromDB(friendid);

	char id[256];

	memset(id, 0, 256);

	for(int i = 0; i < 256; i++)
	{
		if(msgData.msgHeader.szFromID[i] == '0')
			break;

		id[i] = msgData.msgHeader.szFromID[i];
	}

	// 친구 ID 를 찾았다면 친구 리스트 DB 에 추가한다.
	if(bSuccess)
	{
		g_sToolMgr.GetSQLMgr()->AddFriendUser(id, friendid); 

		msg[0] = MSG_PARSING_ADD_FRIEND_OK;
	}
	else
	{
		msg[0] = MSG_PARSING_ADD_FRIEND_FAIL;
	}

	MSG_Generator(send, msgData.msgHeader.szFromID, msgData.msgHeader.szToID, 
		          MSG_MIDDLE_TO_MAIN, MAIN_CMD, CM_ADD_FRIEND_RET_TO_MIDDLE, msg);

	MSG_SendToServer(pSock, send); 
}