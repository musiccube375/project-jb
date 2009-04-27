#include "stdAfx.h"
#include "CMD_Handler.h"

CCMDHandlerMgr::CCMDHandlerMgr()
{

}

CCMDHandlerMgr::~CCMDHandlerMgr()
{

}

PMSG_DATA CCMDHandlerMgr::CMD_Main_Handle(MSG_DATA msgData)
{
	switch(msgData.msgHeader.nCommandType)
	{
	case MAIN_CMD:
		{
			return CMD_MS_Handle(msgData.msgHeader.nCommandData);
		}
		break;
	case MIDDLE_CMD:
		{
			return CMD_MDS_Handle(msgData.msgHeader.nCommandData);
		}
		break;
	case CLIENT_CMD:
		{
			return CMD_CLT_Handle(msgData.msgHeader.nCommandData);
		}
		break;
	}
}


