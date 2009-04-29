#include "stdAfx.h"
#include "CMD_Handler.h"

CCMDHandlerMgr::CCMDHandlerMgr()
{

}

CCMDHandlerMgr::~CCMDHandlerMgr()
{

}

MSG_RET CCMDHandlerMgr::CMD_Main_Handle(MSG_DATA msgData)
{
	switch(msgData.msgHeader.nCommandType)
	{
	case MIDDLE_CMD:
		{
			return CMD_MDS_Handle(msgData);
		}
		break;
	}
}


