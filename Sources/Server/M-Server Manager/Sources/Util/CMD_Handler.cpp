#include "stdAfx.h"
#include "CMD_Handler.h"

CCMDHandlerMgr::CCMDHandlerMgr()
{

}

CCMDHandlerMgr::~CCMDHandlerMgr()
{

}

void CCMDHandlerMgr::CMD_Main_Handle(MSG_DATA msgData)
{
	switch(msgData.msgHeader.nCommandType)
	{
	case MAIN_CMD:
		{
			CMD_MS_Handle(msgData.msgHeader.nCommandData);
		}
		break;
	case MIDDLE_CMD:
		{
			CMD_MDS_Handle(msgData.msgHeader.nCommandData);
		}
		break;
	case CLIENT_CMD:
		{
			CMD_CLT_Handle(msgData.msgHeader.nCommandData);
		}
		break;
	}
}


