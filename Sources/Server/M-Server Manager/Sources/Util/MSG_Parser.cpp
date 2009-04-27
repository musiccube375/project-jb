#include "stdAfx.h"
#include "MSG_Parser.h"

CMSGQueue::CMSGQueue()
{
	
}

CMSGQueue::~CMSGQueue()
{
	ClearMSG();	
}

void CMSGQueue::PushMSG(const char* pszMsg)
{
	MSGINFO MSG(pszMsg);
	m_queueMSG.push(MSG);
}

PMSGINFO CMSGQueue::PopMSG()
{
	MSGINFO MSG = m_queueMSG.front();

	m_queueMSG.pop();

	return &MSG;
}

void CMSGQueue::ClearMSG()
{
	m_queueMSG.empty();
}

void CMSGQueue::ProcessMSG()
{
	MSGINFO MSG = m_queueMSG.front();
}

char* CMSGParser::ParseMSG(const char* pszMsg)
{

	return 0;
}

CMSGParser::CMSGParser()
{
	
}

CMSGParser::~CMSGParser()
{
	
}
