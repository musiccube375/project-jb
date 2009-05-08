/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: Dialog Manager
	Version				: 1.00.04

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Dialog Manager Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "RegisterNewUserDlg.h"
#include "AddFriendDlg.h"
#include "ReqAddFriendDlg.h"

#define REQADDFRINED_DIALOG_WIDTH		300
#define REQADDFRINED_DIALOG_HEIGHT		210

/*
	Class : Dialog Manager Class

	Release Date		: 2009. 04. 15.
	Version				: 1.00.04
*/

class CDialogMgr
{
public:
	CRegisterNewUserDlg		m_RegisterNewUserDlg;
	CAddFriendDlg			m_AddFriendDlg;

	// Add ReqAddFriendDialog
public:
	bool m_bShowReqAddFriendDlg;
	CReqAddFriendDlg* m_pReqAddFriendDlg;

	void CreatReqAddFriendDlg(char* pszMessage);
	void DestroyReqAddFriendDlg();
	// Add ReqAddFriendDialog

public:
	HRESULT InitDialogMgr();

public:
	// The basic constructor
	CDialogMgr();

	// The basic destructor
	~CDialogMgr();
};