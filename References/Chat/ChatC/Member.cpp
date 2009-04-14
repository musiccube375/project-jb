#include "StdAfx.h"
#include ".\member.h"

CMember::CMember(void)
: m_name(_T(""))
, m_id(_T(""))
, m_online(false)
, m_dlg(NULL)
{
}

CMember::~CMember(void)
{
}

void CMember::ModifyName(CString name)
{
	m_name = name;
}

void CMember::SetOnline(bool online)
{
	m_online = online;
}

void CMember::SetDlgPtr(CChatCDlg * dlg)
{
	m_dlg = dlg;
}

CString CMember::GetID(void)
{
	return m_id;
}

CString CMember::GetName(void)
{
	return m_name;
}

bool CMember::GetOnline(void)
{
	return m_online;
}

CChatCDlg * CMember::GetDlgPtr(void)
{
	return m_dlg;
}
