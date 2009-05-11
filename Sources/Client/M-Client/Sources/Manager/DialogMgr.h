/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: Dialog Manager
	Version				: 1.00.05

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
	Structure : ML_DIALOG Structure

	Release Date		: 2009. 05. 11.
	Version				: 1.00.00
*/

template <typename T>
struct ML_DIALOG
{
	T* pDialog;

	bool bShow;

	int nWidth;
	int nHeight;

	void SetSize(int w, int h)
	{
		nWidth = w;
		nHeight = h;
	}

	void CreateMLDialog(UINT nDialogID, RECT rt, char* pszMessage = NULL)
	{
		if(bShow) return;

		pDialog = new T;
		pDialog->Create(nDialogID);

		int w = rt.right - rt.left;
		int h = rt.bottom - rt.top;

		pDialog->MoveWindow(rt.left + w / 2 - (nWidth / 2), 
							rt.top + h / 2 - (nHeight / 2), 
							nWidth, nHeight);

		pDialog->ShowWindow(SW_SHOW); 
		pDialog->Init(pszMessage);

		bShow = true;
	}

	void DestroyMLDialog()
	{
		if(pDialog != NULL)   
		{
			pDialog->DestroyWindow();
			SAFE_DELETE(pDialog);
		}

		bShow = false;
	}

	ML_DIALOG()
	{
		bShow = false;
	}
};

typedef map<int, ML_DIALOG<CReqAddFriendDlg>>					ML_REQ_ADD_FRINED_MAP;
typedef map<int, ML_DIALOG<CReqAddFriendDlg>>::iterator			ML_REQ_ADD_FRINED_MAP_IT;
typedef map<int, ML_DIALOG<CReqAddFriendDlg>>::value_type		ML_REQ_ADD_FRINED_MAP_VALUE;

/*
	Class : Dialog Manager Class

	Release Date		: 2009. 04. 15.
	Version				: 1.00.05
*/

class CDialogMgr
{
public:
	CRegisterNewUserDlg		m_RegisterNewUserDlg;
	CAddFriendDlg			m_AddFriendDlg;

	// Add ReqAddFriendDialog
private:
	int m_nReqAddFriendDlgCount;
	ML_REQ_ADD_FRINED_MAP m_mapReqAddFriendDlg;

public:
	void AddReqAddFriendDlg(UINT nDialogID, RECT rt, char* pszMessage = NULL);
	void DelReqAddFriendDlg(int nIndex);
	void ClearReqAddFriendDlg();
	// Add ReqAddFriendDialog

public:
	HRESULT InitDialogMgr();
	void ClearDialogMgr();

public:
	// The basic constructor
	CDialogMgr();

	// The basic destructor
	~CDialogMgr();
};