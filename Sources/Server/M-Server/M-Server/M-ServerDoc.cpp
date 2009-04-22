
// M-ServerDoc.cpp : CMServerDoc 클래스의 구현
//

#include "stdafx.h"
#include "M-Server.h"

#include "M-ServerDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMServerDoc

IMPLEMENT_DYNCREATE(CMServerDoc, CDocument)

BEGIN_MESSAGE_MAP(CMServerDoc, CDocument)
END_MESSAGE_MAP()


// CMServerDoc 생성/소멸

CMServerDoc::CMServerDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMServerDoc::~CMServerDoc()
{
}

BOOL CMServerDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMServerDoc serialization

void CMServerDoc::Serialize(CArchive& ar)
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


// CMServerDoc 진단

#ifdef _DEBUG
void CMServerDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMServerDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMServerDoc 명령
