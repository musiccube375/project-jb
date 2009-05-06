#include "stdAfx.h"
#include "Client_MSG.h"
#include "Common_MSG_Generator.h"

void MSG_SendToServer(const char* pszSend)
{
	g_sToolMgr.GetWinSockMgr()->GetServerSock()->Send(pszSend, 512);
}

void MSG_Exit_Server_Req(const char* pszID)
{
	if(!g_sToolMgr.m_bConnected) return;

	char send[512];

	char szServerIP[16];
	
	strcpy(szServerIP, g_sToolMgr.m_ServerList[g_sToolMgr.GetWinSockMgr()->GetServerCount()].szServerIP);

	MSG_Generator(send, (char *) pszID, szServerIP, MSG_CLIENT_TO_MIDDLE, CLIENT_CMD, CC_EXIT_SERVER_REQ_TO_MIDDLE);

	MSG_SendToServer(send);	
}

void MSG_ID_Check_Req(const char* pszID)
{
	if(!g_sToolMgr.m_bConnected) return;

	char send[512];

	MSG_Generator(send, UNKNOWNED_USER, (char *) pszID, MSG_CLIENT_TO_MIDDLE, CLIENT_CMD, CC_ID_CHECK_REQ_TO_MIDDLE);

	MSG_SendToServer(send);	
}

MSG_RET MSG_ID_Check_Ack(MSG_DATA msgData)
{
	if(!msgData.IsValidHeader()) return MSG_RET_ERROR;

	if(msgData.msgMessage[0] == MSG_PARSING_ID_CHECK_OK)
		return MSG_PARSING_ID_CHECK_OK;
	else if(msgData.msgMessage[0] == MSG_PARSING_ID_CHECK_FAIL)
		return MSG_PARSING_ID_CHECK_FAIL;

	return MSG_RET_NONE;
}

void MSG_Add_ID_Req(const char* pszID, const char* pszPasswords)
{
	if(!g_sToolMgr.m_bConnected) return;

	char send[512];
	char msg[MSG_MAX_SIZE];

	int nIDSize = 0, nPWSize = 0;

	nIDSize = strlen(pszID);
	nPWSize = strlen(pszPasswords);

	memset(msg, 0, MSG_MAX_SIZE);
	sprintf(msg, "%d%s%d%s\0", nIDSize, pszID, nPWSize, pszPasswords);

	MSG_Generator(send, UNKNOWNED_USER, UNKNOWNED_USER, MSG_CLIENT_TO_MIDDLE, 
		          CLIENT_CMD, CC_ADD_ID_REQ_TO_MIDDLE, msg);

	MSG_SendToServer(send);	
}

MSG_RET MSG_Add_ID_Ack(MSG_DATA msgData)
{
	if(!msgData.IsValidHeader()) return MSG_RET_ERROR;

	if(msgData.msgMessage[0] == MSG_PARSING_ADD_ID_OK)
		return MSG_PARSING_ADD_ID_OK;
	else if(msgData.msgMessage[0] == MSG_PARSING_ADD_ID_FAIL)
		return MSG_PARSING_ADD_ID_FAIL;

	return MSG_RET_NONE;
}

void MSG_Login_Req(const char* pszID, const char* pszPasswords, const char* pszServer)
{
	if(!g_sToolMgr.m_bConnected) return;

	char send[512];
	char msg[MSG_MAX_SIZE];

	int nIDSize = 0, nPWSize = 0, nServerSize = 0;

	nIDSize = strlen(pszID);
	nPWSize = strlen(pszPasswords);
	nServerSize = strlen(pszServer);

	memset(msg, 0, MSG_MAX_SIZE);
	sprintf(msg, "%d%s%d%s%d%s\0", nIDSize, pszID, nPWSize, pszPasswords, nServerSize, pszServer);

	MSG_Generator(send, UNKNOWNED_USER, UNKNOWNED_USER, MSG_CLIENT_TO_MIDDLE, 
		          CLIENT_CMD, CC_LOGIN_REQ_TO_MIDDLE, msg);

	MSG_SendToServer(send);	
}

MSG_RET MSG_Login_Ack(MSG_DATA msgData)
{
	if(!msgData.IsValidHeader()) return MSG_RET_ERROR;

	if(msgData.msgMessage[0] == MSG_PARSING_LOGIN_OK)
		return MSG_PARSING_LOGIN_OK;
	else if(msgData.msgMessage[0] == MSG_PARSING_LOGIN_FAIL)
		return MSG_PARSING_LOGIN_FAIL;

	return MSG_RET_NONE;
}

void MSG_Add_Friend_Req(const char* pszID, const char* pszFriendID, const char* pszMessage)
{
	if(!g_sToolMgr.m_bConnected) return;

	char send[512];
	char msg[MSG_MAX_SIZE];

	int nFriendIDSize = 0, nMsgSize = 0;

	nFriendIDSize = strlen(pszFriendID);

	memset(msg, 0, MSG_MAX_SIZE);
	sprintf(msg, "%d%s%d%s\0", nFriendIDSize, pszFriendID, nMsgSize, pszMessage);

	MSG_Generator(send, (char *) pszID, (char *) pszFriendID, MSG_CLIENT_TO_MIDDLE, CLIENT_CMD, CC_ADD_FRIENT_REQ_TO_MIDDLE);

	MSG_SendToServer(send);	
}

MSG_RET MSG_Add_Friend_Ack(MSG_DATA msgData)
{
	if(!msgData.IsValidHeader()) return MSG_RET_ERROR;

	if(msgData.msgMessage[0] == MSG_PARSING_ADD_FRIEND_OK)
		return MSG_PARSING_ADD_FRIEND_OK;
	else if(msgData.msgMessage[0] == MSG_PARSING_ADD_FRIEND_FAIL)
		return MSG_PARSING_ADD_FRIEND_FAIL;

	return MSG_RET_NONE;
}