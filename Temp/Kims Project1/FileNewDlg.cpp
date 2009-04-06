// FileNewDlg.cpp : ���� �����Դϴ�.
//

#include "stdafx.h"
#include "Gaussian.h"
#include "FileNewDlg.h"


// CFileNewDlg ��ȭ �����Դϴ�.

IMPLEMENT_DYNAMIC(CFileNewDlg, CDialog)

CFileNewDlg::CFileNewDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CFileNewDlg::IDD, pParent)
	, m_nWidth(256)
	, m_nHeight(256)
	, m_nType(0)
{

}

CFileNewDlg::~CFileNewDlg()
{
}

void CFileNewDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_nWidth);
	DDV_MinMaxInt(pDX, m_nWidth, 0, 2048);
	DDX_Text(pDX, IDC_EDIT2, m_nHeight);
	DDV_MinMaxInt(pDX, m_nHeight, 0,2048);
	DDX_CBIndex(pDX, IDC_COMBO1, m_nType);
}


BEGIN_MESSAGE_MAP(CFileNewDlg, CDialog)
END_MESSAGE_MAP()


// CFileNewDlg �޽��� ó�����Դϴ�.