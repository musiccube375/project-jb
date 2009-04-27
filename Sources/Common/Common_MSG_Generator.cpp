#include "stdafx.h"
#include "Common_MSG_Generator.h"

HRESULT MSG_Generator(char* pszOutMessage, char* pszFrom, char* pszTo, 
				      int nType, int nCmdType, int nCmdData, char* pszMessage)
{
	int nCount = 0;
	BYTE nMsgLenght = 0;
	
	if(pszMessage != NULL)
		nMsgLenght = strlen(pszMessage);

	pszOutMessage[nCount++] = 'S';
	pszOutMessage[nCount++] = 'O';
	pszOutMessage[nCount++] = 'M';

	for(int i = 0; i < MAX_ID_SIZE; i++)
	{
		pszOutMessage[nCount++] = pszFrom[i] ? pszFrom[i] : 0x30;
	}

	for(int i = 0; i < MAX_ID_SIZE; i++)
	{
		pszOutMessage[nCount++] = pszTo[i] ? pszTo[i] : 0x30;
	}

	pszOutMessage[nCount++] = nType;
	pszOutMessage[nCount++] = nCmdType;
	pszOutMessage[nCount++] = nCmdData;

	pszOutMessage[nCount++] = nMsgLenght ? nMsgLenght : 0x30;

	for(int i = 0; i < nMsgLenght; i++)
	{
		pszOutMessage[nCount++] = pszMessage[i];
	}

	pszOutMessage[nCount++] = 'E';
	pszOutMessage[nCount++] = 'O';
	pszOutMessage[nCount++] = 'M';

	return S_OK;
}
