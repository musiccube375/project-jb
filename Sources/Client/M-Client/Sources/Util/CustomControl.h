/* 
	Author				: ±Ë¡§»∆(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
	Project	Name		: Custom Control For MFC contorls
	Version				: 1.00.00

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Custom Control Header

	2009 ®œ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#define globalData afxGlobalData

/*
	Class : ColorListCtrl Class

	Release Date		: 2008. 04. 15.
	Version				: 1.00.00
*/

class CColorListCtrl : public CMFCListCtrl
{
	virtual COLORREF OnGetCellTextColor(int nRow, int nColum);
	virtual COLORREF OnGetCellBkColor(int nRow, int nColum);
	virtual HFONT OnGetCellFont(int nRow, int nColum, DWORD dwData = 0);

public:
	BOOL m_bColor;
	BOOL m_bModifyFont;
};