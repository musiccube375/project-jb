
// M-ClientDoc.cpp : CMClientDoc 클래스의 구현
//

#include "stdafx.h"
#include "M-Client.h"

#include "M-ClientDoc.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CMClientDoc

IMPLEMENT_DYNCREATE(CMClientDoc, CDocument)

BEGIN_MESSAGE_MAP(CMClientDoc, CDocument)
END_MESSAGE_MAP()


// CMClientDoc 생성/소멸

CMClientDoc::CMClientDoc()
{
	// TODO: 여기에 일회성 생성 코드를 추가합니다.

}

CMClientDoc::~CMClientDoc()
{
}

BOOL CMClientDoc::OnNewDocument()
{
	if (!CDocument::OnNewDocument())
		return FALSE;

	// TODO: 여기에 재초기화 코드를 추가합니다.
	// SDI 문서는 이 문서를 다시 사용합니다.

	return TRUE;
}




// CMClientDoc serialization

void CMClientDoc::Serialize(CArchive& ar)
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


// CMClientDoc 진단

#ifdef _DEBUG
void CMClientDoc::AssertValid() const
{
	CDocument::AssertValid();
}

void CMClientDoc::Dump(CDumpContext& dc) const
{
	CDocument::Dump(dc);
}
#endif //_DEBUG


// CMClientDoc 명령
