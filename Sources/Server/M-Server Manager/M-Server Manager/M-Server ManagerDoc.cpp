
// M-Server ManagerDoc.cpp : CMServerManagerDoc 클래스의 구현
//

#include "stdafx.h"
#include "M-Server Manager.h"

#include "M-Server ManagerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMServerManagerDoc

IMPLEMENT_DYNCREATE(CMServerManagerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMServerManagerDoc, CDocument)
END_MESSAGE_MAP()


// CMServerManagerDoc 생성/소멸

CMServerManagerDoc::CMServerManagerDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMServerManagerDoc::~CMServerManagerDoc()
{
}

BOOL CMServerManagerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMServerManagerDoc serialization

void CMServerManagerDoc::Serialize(CArchive& ar)
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


// CMServerManagerDoc 진단

#ifdef _DEBUG
void CMServerManagerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMServerManagerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMServerManagerDoc 명령
