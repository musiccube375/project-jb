#include "stdAfx.h"
#include "CMD_Handler_MS.h"
#include "ServerMgr_MSG.h"

CCMDHandlerMS::CCMDHandlerMS()
{

}

CCMDHandlerMS::~CCMDHandlerMS()
{

}

PMSG_DATA CCMDHandlerMS::CMD_MS_Handle(MSG_DATA msgData, CClientSock* pSock)
{
	switch(msgData.msgHeader.nCommandData)
	{
	case CD_ADD_ID_REQ_TO_MAIN:
		{
			MSG_Add_ID_Ack(msgData, pSock);
		}
		break;		

	case CD_ADD_FRIEND_REQ_TO_MAIN:
		{
			MSG_Add_Friend_Ack(msgData, pSock);
		}
		break;

	case CD_ID_CHECK_REQ_TO_MAIN:
		{	
			MSG_ID_Check_Ack(msgData, pSock);
		}
		break;

	case CD_LOGIN_REQ_TO_MAIN:
		{	
			MSG_Login_Ack(msgData, pSock);
		}
		break;

	case CD_EXIT_SERVER_REQ_TO_MAIN:
		{
			MSG_LogOut_Ack(msgData);
		}
		break;



	case CD_UPDATE_FRIEND_REQ_TO_CLIENT:
		{	
			MSG_Update_Friend_Ack(msgData, pSock);
		}
		break;

	case CD_DELETE_FRIEND_REQ_TO_CLIENT:
		{	
			MSG_Delete_Friend_Ack(msgData, pSock);
		}
		break;
	}

	return 0;
}