/* 
	Author				: ±èÁ¤ÈÆ(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2008. 12. 12.
	Project	Name		: UI Manager
	Version				: 1.00.00

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP2
	Test Application	: Visual Studio 2003 + D3D 9.0c(Dec 2006)
	
	Contents

	UI Manager Header

	2008 ¨Ï Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "UIEL.h"

#define MAX_EL_COUNT		99

#define STANDARD_UI_EL_X	12
#define STANDARD_UI_EL_Y	74

#define STANDARD_UI_EL_W	600
#define STANDARD_UI_EL_H	600

#define GAP_WIDTH			108
#define GAP_HEIGHT			32

#define GAP_COL				6
#define GAP_ROW				6

/*
	Class : UI Manager Class

	Release Date		: 2008. 12. 12.
	Version				: 1.00.00
*/

class CUIMgr
{
private:
	int			m_nCurPage;
	int			m_nMaxPage;

	CUIEL		m_UIEL[MAX_EL_COUNT];

	CVPage		m_VPage;

public:
	int			GetCurPage() { return m_nCurPage; } 
	int			GetMaxPage() { return m_nMaxPage; } 

public:
	void		SetMaxPage(int nCount) { m_nMaxPage = nCount / (GAP_COL * GAP_ROW) + 1; }

public:
	bool		IncCurPage() { m_nCurPage++; if(m_nCurPage > m_nMaxPage) { m_nCurPage = m_nMaxPage; return false; } return true; }
	bool		DecCurPage() { m_nCurPage--; if(m_nCurPage < 1) { m_nCurPage = 1; return false; } return true; }

public:
	void		Init();
	void		Update(int nIndex,
					   CDC* pDC,
		               char* pszELState, 
					   char* pszAptIndex, 
					   char* pszELIndex, 
					   char* pszFloor, 
					   int	 nLowestFloor,
					   BYTE byDir,
					   int nSelect);

public:
	// The basic constructor
	CUIMgr();

	// The basic destructor
	~CUIMgr();
};