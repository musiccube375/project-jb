#include "stdAfx.h"
#include "CMD_Handler_MDS.h"

CCMDHandlerMDS::CCMDHandlerMDS()
{

}

CCMDHandlerMDS::~CCMDHandlerMDS()
{

}

PMSG_DATA CCMDHandlerMDS::CMD_MS_Handle(MSG_DATA msgData)
{
	switch(msgData.msgHeader.nCommandData)
	{
	case CM_ADD_ID_REQ_TO_MIDDLE:
		{
	
		}
		break;

	case CM_ADD_FRIEND_REQ_TO_MIDDLE:
		{

		}
		break;		

	case CM_ID_CHECK_REQ_TO_MIDDLE:
		{

		}
		break;
	}

	return 0;
}

PMSG_DATA CCMDHandlerMDS::CMD_MDS_Handle(MSG_DATA msgData)
{
	switch(msgData.msgHeader.nCommandData)
	{
	case CC_CONNECT_REQ_TO_MIDDLE:
		{
	
		}
		break;

	case CC_ADD_ID_REQ_TO_MIDDLE:
		{

		}
		break;		

	case CC_ADD_FRIENT_REQ_TO_MIDDLE:
		{

		}
		break;

	case CC_ID_CHECK_REQ_TO_MIDDLE:
		{
			MSG_ID_Check_Req(msgData);
		}
		break;
	}

	return 0;
}