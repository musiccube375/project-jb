/* 
	Author				: ������(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: Dialog Manager
	Version				: 1.00.01

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Dialog Manager Header

	2009 �� Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "LogDlg.h"
#include "UserDlg.h"

/*
	Class : Dialog Manager Class

	Release Date		: 2009. 04. 15.
	Version				: 1.00.01
*/

class CDialogMgr
{
public:
	CLogDlg m_LogDlg;
	CUserDlg m_UserDlg;

	HRESULT InitDialogMgr(CMFCTabCtrl* pTab);

public:
	// The basic constructor
	CDialogMgr();

	// The basic destructor
	~CDialogMgr();
};