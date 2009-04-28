#include "stdAfx.h"
#include "CMD_Handler_MS.h"
#include "ServerMgr_MSG.h"

CCMDHandlerMS::CCMDHandlerMS()
{

}

CCMDHandlerMS::~CCMDHandlerMS()
{

}

PMSG_DATA CCMDHandlerMS::CMD_MS_Handle(MSG_DATA msgData)
{
	switch(msgData.msgHeader.nCommandData)
	{
	case CD_CONNECT_RET_TO_CLIENT:
		{
	
		}
		break;

	case CD_ADD_ID_REQ_TO_MAIN:
		{

		}
		break;		

	case CD_ADD_FRIEND_REQ_TO_MAIN:
		{

		}
		break;

	case CD_ADD_ID_RET_TO_CLIENT:
		{
			
		}
		break;

	case CD_ADD_FRIEND_RET_TO_CLIENT:
		{

		}
		break;

	case CD_ID_CHECK_RET_TO_CLIENT:
		{
			MSG_ID_Check_Ack(msgData);
		}
		break;
	}

	return 0;
}