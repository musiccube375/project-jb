#include "stdAfx.h"
#include "CMD_Handler_MDS.h"

CCMDHandlerMDS::CCMDHandlerMDS()
{

}

CCMDHandlerMDS::~CCMDHandlerMDS()
{

}

MSG_RET CCMDHandlerMDS::CMD_MS_Handle(MSG_DATA msgData)
{
	switch(msgData.msgHeader.nCommandData)
	{
	case CM_ADD_ID_RET_TO_MIDDLE:
		{
			MSG_Add_ID_Ack(msgData);
		}
		break;

	case CM_ADD_FRIEND_RET_TO_MIDDLE:
		{
			
		}
		break;		

	case CM_ID_CHECK_RET_TO_MIDDLE:
		{
			MSG_ID_Check_Ack(msgData);
		}
		break;

	case CM_LOGIN_RET_TO_MIDDLE:
		{
			MSG_Login_Ack(msgData);
		}
		break;	
	}

	return MSG_RET_NONE;
}

MSG_RET CCMDHandlerMDS::CMD_CLT_Handle(MSG_DATA msgData)
{
	switch(msgData.msgHeader.nCommandData)
	{
	case CC_CONNECT_REQ_TO_MIDDLE:
		{
	
		}
		break;

	case CC_ADD_ID_REQ_TO_MIDDLE:
		{
			MSG_Add_ID_Req(msgData);
		}
		break;		

	case CC_ADD_FRIENT_REQ_TO_MIDDLE:
		{
			MSG_Add_Friend_Req(msgData);
		}
		break;

	case CC_ID_CHECK_REQ_TO_MIDDLE:
		{
			MSG_ID_Check_Req(msgData);
		}
		break;

	case CC_EXIT_SERVER_REQ_TO_MIDDLE:
		{	
			MSG_Exit_Server_Req(msgData);	
		}
		break;

	case CC_LOGIN_REQ_TO_MIDDLE:
		{
			MSG_Login_Req(msgData);
		}
		break;
	}

	return MSG_RET_NONE;
}