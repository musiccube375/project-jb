// GaussianDoc.cpp : CGaussianDoc 클래스의 구현
//

#include "stdafx.h"
#include "Gaussian.h"

#include "GaussianDoc.h"
#include "GaussianView.h"
#include "FileNewDlg.h"
#include "MainFrm.h"
#include "ChildFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CGaussianDoc

IMPLEMENT_DYNCREATE(CGaussianDoc, CDocument)

BEGIN_MESSAGE_MAP(CGaussianDoc, CDocument)
	ON_COMMAND(ID_WINDOW_DUPLICATE, &CGaussianDoc::OnWindowDuplicate)
END_MESSAGE_MAP()


// CGaussianDoc 생성/소멸

CGaussianDoc::CGaussianDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.
}

CGaussianDoc::~CGaussianDoc()
{
}

BOOL CGaussianDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	BOOL bSuccess = TRUE;

	if( theApp.m_pNewDib != NULL )
	{
		m_Dib.Copy(theApp.m_pNewDib);
		theApp.m_pNewDib = NULL;
	}
	else
	{
		CFileNewDlg dlg;
		if( dlg.DoModal() == IDOK )
		{
			if( dlg.m_nType == 0 ) // 그레이스케일 이미지
				bSuccess = m_Dib.CreateGrayImage(dlg.m_nWidth, dlg.m_nHeight);
			else // 트루칼라 이미지
				bSuccess = m_Dib.CreateRGBImage(dlg.m_nWidth, dlg.m_nHeight);
		}
		else
		{
			bSuccess = FALSE;
		}
	}

	return bSuccess;

}

// CGaussianDoc serialization

void CGaussianDoc::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{
		// TODO: 여기에 저장 코드를 추가합니다.
	}
	else
	{
		// TODO: 여기에 로딩 코드를 추가합니다.
	}
}


// CGaussianDoc 진단

#ifdef _DEBUG
void CGaussianDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CGaussianDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CGaussianDoc 명령

BOOL CGaussianDoc::OnOpenDocument(LPCTSTR lpszPathName)
{
	if(!CDocument::OnOpenDocument(lpszPathName))
		return FALSE;
	
	return m_Dib.Load(lpszPathName);
}

BOOL CGaussianDoc::OnSaveDocument(LPCTSTR lpszPathName)
{
	return m_Dib.Save(lpszPathName);
}

void CGaussianDoc::OnWindowDuplicate()
{
	// TODO: 여기에 명령 처리기 코드를 추가합니다.
	AfxNewImage(m_Dib);
}
