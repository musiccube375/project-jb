#include "StdAfx.h"
#include "member.h"
#include ".\member.h"

CMember::CMember(void)
: m_online(false)
, m_pDataSocket(NULL)
{
	m_mylistnum=0;
}

CMember::~CMember(void)
{
}

CString CMember::GetID()
{
	return m_id;
}
CString CMember::GetName()
{
	return m_name;
}

void CMember::Setmember(CString id, CString pass, CString name)
{
	m_id = id;
	m_pass = pass;
	m_name = name;
	m_mylistnum = 0;
	m_mylist->Empty();
}

void CMember::Addmylist(CString dest_id)
{
	m_mylist[m_mylistnum] = dest_id;
	m_mylistnum++;
}

void CMember::Delmylist(CString dest_id)
{
	int n;
	for(int i=0;i<m_mylistnum;i++)
	{
		if(m_mylist[i]==dest_id)
		{
			n=i;
			break;
		}
	}
	for(int i=n;i<m_mylistnum-1;i++)
	{
		m_mylist[i] = m_mylist[i+1];
	}
	m_mylistnum--;
}