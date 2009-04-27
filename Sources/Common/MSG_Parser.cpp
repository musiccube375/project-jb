#include "stdAfx.h"
#include "MSG_Parser.h"

CMSGParser::CMSGParser()
{
	
}

CMSGParser::~CMSGParser()
{
	
}

PMSG_DATA CMSGParser::ParseMSG(const char* pszMsg)
{
	if(ParseMSGHeader(pszMsg) != S_OK)
		return NULL;

	ParseMSGMessage(pszMsg);
	
	if(ParseMSGTail(pszMsg) != S_OK)
		return NULL;

	CMD_Main_Handle(m_msgData);

	return &m_msgData;
}

HRESULT CMSGParser::ParseMSGHeader(const char* pszMsg)
{
	if(pszMsg[INDEX_SYNTAX] != 'S' ||
	   pszMsg[INDEX_SYNTAX+1] != 'O' ||
	   pszMsg[INDEX_SYNTAX+2] != 'M')
	   return E_FAIL;

	for(int i = 0; i < 3; i++)
	{
		m_msgData.msgHeader.szHead[i] = pszMsg[INDEX_SYNTAX+i];
	}

	for(int i = 0; i < MAX_ID_SIZE; i++)
	{
		m_msgData.msgHeader.szFromID[i] = pszMsg[INDEX_FROMID+i];
	}

	for(int i = 0; i < MAX_ID_SIZE; i++)
	{
		m_msgData.msgHeader.szToID[i] = pszMsg[INDEX_TOID+i];
	}

	m_msgData.msgHeader.nType = pszMsg[INDEX_TYPE];
	m_msgData.msgHeader.nCommandType = pszMsg[INDEX_CMDTYPE];
	m_msgData.msgHeader.nCommandData = pszMsg[INDEX_CMDDATA];
	m_msgData.msgHeader.nMsgLen = pszMsg[INDEX_MSGLEN];

	return S_OK;
}

HRESULT CMSGParser::ParseMSGMessage(const char* pszMsg)
{
	if(m_msgData.msgHeader.nMsgLen == 0) 
		return E_FAIL;

	for(int i = 0; i < m_msgData.msgHeader.nMsgLen; i++)
	{
		m_msgData.msgMessage[i] = pszMsg[INDEX_MSG+i];
	}

	return S_OK;
}

HRESULT CMSGParser::ParseMSGTail(const char* pszMsg)
{
	for(int i = 0; i < 3; i++)
	{
		m_msgData.msgTail[i] = pszMsg[INDEX_MSG+m_msgData.msgHeader.nMsgLen+i];
	}

	if(m_msgData.msgTail[0] != 'E' ||
	   m_msgData.msgTail[1] != 'O' ||
	   m_msgData.msgTail[2] != 'M')
	   return E_FAIL;

	return S_OK;
}

