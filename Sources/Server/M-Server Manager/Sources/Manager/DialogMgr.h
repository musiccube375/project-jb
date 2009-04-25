/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: Dialog Manager
	Version				: 1.00.02

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Dialog Manager Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "LogDlg.h"
#include "UserDlg.h"
#include "AccountDlg.h"
#include "StatusDlg.h"

/*
	Class : Dialog Manager Class

	Release Date		: 2009. 04. 15.
	Version				: 1.00.02
*/

class CDialogMgr
{
public:
	CLogDlg m_LogDlg;
	CUserDlg m_UserDlg;
	CStatusDlg m_StatusDlg;

public:
	CAccountDlg m_AccountDlg;

public:
	HRESULT InitDialogMgr(CMFCTabCtrl* pTab);

public:
	// The basic constructor
	CDialogMgr();

	// The basic destructor
	~CDialogMgr();
};