#include "stdAfx.h"
#include "CustomControl.h"

COLORREF CColorListCtrl::OnGetCellTextColor(int nRow, int nColum)
{
	if (!m_bColor)
	{
		return CMFCListCtrl::OnGetCellTextColor(nRow, nColum);
	}

	return(nRow % 2) == 0 ? RGB(128, 37, 0) : RGB(0, 0, 0);
}

COLORREF CColorListCtrl::OnGetCellBkColor(int nRow, int nColum)
{
	if (!m_bColor)
	{
		return CMFCListCtrl::OnGetCellBkColor(nRow, nColum);
	}

	if (m_bMarkSortedColumn && nColum == m_iSortedColumn)
	{
		return(nRow % 2) == 0 ? RGB(233, 221, 229) : RGB(176, 218, 234);
	}

	return(nRow % 2) == 0 ? RGB(253, 241, 249) : RGB(196, 238, 254);
}

HFONT CColorListCtrl::OnGetCellFont(int nRow, int nColum, DWORD dwData)
{
	if (!m_bModifyFont)
	{
		return NULL;
	}

	if (nColum == 2 &&(nRow >= 4 && nRow <= 8))
	{
		return globalData.fontDefaultGUIBold;
	}

	return NULL;
}
