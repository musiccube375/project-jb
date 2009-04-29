#include "stdAfx.h"
#include "CMD_Handler.h"

CCMDHandlerMgr::CCMDHandlerMgr()
{

}

CCMDHandlerMgr::~CCMDHandlerMgr()
{

}

PMSG_DATA CCMDHandlerMgr::CMD_Main_Handle(MSG_DATA msgData, CClientSock* pSock)
{
	switch(msgData.msgHeader.nCommandType)
	{
	case MIDDLE_CMD:
		{
			return CMD_MS_Handle(msgData, pSock);
		}
		break;
	}
}


