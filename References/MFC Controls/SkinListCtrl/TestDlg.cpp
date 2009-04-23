// TestDlg.cpp : implementation file
//

#include "stdafx.h"
#include "Test.h"
#include "TestDlg.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTestDlg dialog

#define TAB_HEADER_HEIGHT		24

const TCHAR *lpszHeader[] = {	_T("Type"),			// 0
								_T("Icon"),			// 1
								_T("Value"),		// 2
								_T("Description"),	// 3
								NULL};	

const int colWidthList[] = {	15,					// 0
								10,					// 1
								50,					// 2
								0};					// 3

CTestDlg::CTestDlg(CWnd* pParent /*=NULL*/)
	: CSkinDialog(CTestDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	m_bInitialized = FALSE;

	m_pImageList = NULL;
}

void CTestDlg::DoDataExchange(CDataExchange* pDX)
{
	CSkinDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDOK, m_btnOk);
	DDX_Control(pDX, IDCANCEL, m_btnCancel);
	DDX_Control(pDX, IDC_LIST, m_list);
}

BEGIN_MESSAGE_MAP(CTestDlg, CSkinDialog)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_SIZE()
	ON_WM_DESTROY()
	//}}AFX_MSG_MAP	
END_MESSAGE_MAP()


// CTestDlg message handlers

BOOL CTestDlg::OnInitDialog()
{
	CSkinDialog::OnInitDialog();

#if 0
	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here
#else
	if( !m_bInitialized )
	{
		m_bInitialized = TRUE;

		// Ok Button
		m_btnOk.SetBitmaps(Global.GetBitmap(IDX_BMP_BTN_BASE), Global.GetRGB(IDX_RGB_MASK));
		m_btnOk.SetIcon(Global.GetIcon(IDX_ICON_OK, ICON16), NULL, 5);

		// Cancel Button
		m_btnCancel.SetBitmaps(Global.GetBitmap(IDX_BMP_BTN_BASE), Global.GetRGB(IDX_RGB_MASK));
		m_btnCancel.SetIcon(Global.GetIcon(IDX_ICON_CANCEL, ICON16), NULL, 5);

		// Image List
		m_pImageList = new CImageList();		
		if(!m_pImageList->Create( 16, 16, ILC_COLOR32, 0, 1))
		{
			delete m_pImageList;
			m_pImageList = NULL;
		}
		else 
		{
			m_pImageList->Add(Global.GetIcon(IDX_ICON_HOME,ICON16));
			m_pImageList->Add(Global.GetIcon(IDX_ICON_FAVORITES,ICON16));
			m_pImageList->Add(Global.GetIcon(IDX_ICON_INTERNET,ICON16));
			m_pImageList->Add(Global.GetIcon(IDX_ICON_SETTING,ICON16));
		}

		// List 초기화
		CString str(_T(""));
		m_list.SetImageList(m_pImageList, LVSIL_NORMAL);	
		InitList(m_list, lpszHeader);

		// 아이템 추가: Normal
		int nItem=0;
		m_list.InsertItem(nItem, _T("Normal"));
		m_list.SetItemImage(nItem, 1, 0, TRUE);
		m_list.SetItemText(nItem, 2, _T("Are you ready?"), RGB(242,149,48), RGB(255,255,255));

		// 아이템 추가: EditBox
		nItem++;
		m_list.InsertItem(nItem, _T("EditBox"));
		m_list.SetItemImage(nItem, 1, 1, TRUE);
		m_list.SetEditBox(nItem, 2, TRUE);
		m_list.SetItemText(nItem, 2, _T("How am I supposed to live without you?"), RGB(242,149,48), RGB(255,255,255));

		// 아이템 추가: SpinBox
		nItem++;
		m_list.InsertItem(nItem, _T("SpinBox"));
		m_list.SetItemImage(nItem, 1, 2, TRUE);
		m_list.SetEditBox(nItem, 2, TRUE, 100, 1000);
		m_list.SetItemText(nItem, 2, _T("100"), RGB(0,200,0), RGB(255,255,255));
		m_list.SetItemText(nItem, 3, _T("Limit( 100~1000 )"), RGB(124,124,200), RGB(255,255,255));

		// 아이템 추가: ComboBox
		nItem++;
		m_list.InsertItem(nItem, _T("ComboBox"));
		m_list.SetItemImage(nItem, 1, 3, TRUE);
		CStringArray sa;
		sa.Add(_T("사진"));
		sa.Add(_T("여행"));
		sa.Add(_T("연극"));
		sa.Add(_T("영화"));
		m_list.SetComboBox(nItem, 2, TRUE, &sa );
		m_list.SetItemText(nItem, 2, _T("사진"), RGB(242,149,48), RGB(255,255,255));

		// 아이템 추가: DateBox
		nItem++;
		m_list.InsertItem(nItem, _T("DateBox"));
		m_list.SetItemImage(nItem, 1, 0, TRUE);
		m_list.SetDateBox(nItem, 2, TRUE, _T("yyyy'년 'MM'월 'dd'일 'HH'시 'mm'분 'ss'초 '"));
		m_list.UpdateDate(nItem, 2, CTime::GetCurrentTime(), RGB(242,149,48), RGB(255,255,255));

		// 아이템 추가: CheckBox
		nItem++;
		m_list.InsertItem(nItem, _T("CheckBox"));
		m_list.SetItemImage(nItem, 1, 1, TRUE);
		m_list.SetCheckbox(nItem, 2, 1);
		m_list.SetItemText(nItem, 2, _T("male"), RGB(242,149,48), RGB(255,255,255));

		// 아이템 추가: Progress
		nItem++;
		m_list.InsertItem(nItem, _T("Progress"));
		m_list.SetItemImage(nItem, 1, 2, TRUE);
		m_list.SetProgress(nItem, 2);
		m_list.UpdateProgress(nItem, 2, 70, RGB(120,120,120), RGB(148,250,148));

		// 리스트 컬럼 재조정
		ResizeListColumn(m_list, colWidthList);		

		// 컨트롤들을 재배치
		RelocationControls();
	}
#endif

	return TRUE;  // return TRUE  unless you set the focus to a control
}

void CTestDlg::InitList(CXListCtrl &list, const TCHAR**pszTitle)
{
	LV_COLUMN lvcolumn;
	memset(&lvcolumn, 0, sizeof(lvcolumn));
	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT /*| LVCF_WIDTH | LVCF_IMAGE*/;
	for( int i=0; ; i++ )
	{
		if( pszTitle[i] == NULL )
			break;

		lvcolumn.fmt = LVCFMT_LEFT;
		lvcolumn.pszText = (TCHAR *)pszTitle[i];
		lvcolumn.iSubItem = i;
		list.InsertColumn(i, &lvcolumn);
	}	

	lvcolumn.pszText = (TCHAR *)pszTitle[0];
	lvcolumn.iSubItem = 0;
	list.SetColumn(0, &lvcolumn);
	list.SetExtendedStyle(LVS_EX_FULLROWSELECT/*| LVS_EX_GRIDLINES | LVS_EX_FLATSB | LVS_EX_SUBITEMIMAGES*/);
	list.EnableToolTips(TRUE);

	// 리스트 아이템 높이 설정
	list.SetRowHeight(20);
	// 리스트 폰트 설정
	list.SetTextFont( Global.GetFont(IDX_FONT_MEDIUM) );
	// 언더라인 컬러 설정
	list.SetColorUnderLine( RGB(240,240,240) );

	// 헤더 높이 설정
	list.m_HeaderCtrl.SetHeight(30);
	// 헤더 폰트 설정
	list.m_HeaderCtrl.SetTextFont( Global.GetFont(IDX_FONT_SMALL) );
}

void CTestDlg::ResizeListColumn(CXListCtrl &list, const int *arrWidth)
{
	SCROLLINFO si;
	CRect rc;
	list.GetWindowRect(&rc);
	int nMargin=0;

	// 스크롤 유무에 따른 마진 추가
	list.GetScrollInfo(SB_VERT, &si);	
	if( si.nPage && si.nPage <= (UINT)si.nMax ) 
	{
		nMargin = ::GetSystemMetrics(SM_CXVSCROLL);
	}

	// 보더 유무에 따른 마진 추가
	DWORD dwExStyle = list.GetExStyle();
	if( dwExStyle&WS_EX_STATICEDGE || 
		dwExStyle&WS_EX_CLIENTEDGE )
	{
		nMargin += ::GetSystemMetrics(SM_CXEDGE)*2;
	}

	int nWidth = 0;
	int nLastWidth = rc.Width()-nMargin;
	for( int i=0; ; i++ )
	{
		// 마지막 컬럼일 경우
		if( arrWidth[i] == 0 )
		{
			list.SetColumnWidth(i, nLastWidth);
			break;
		}

		nWidth = (rc.Width()*arrWidth[i])/100;
		list.SetColumnWidth(i, nWidth);
		nLastWidth -= nWidth;
	}
	list.RedrawWindow();
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTestDlg::OnPaint()
{
#if 0
	if( IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CSkinDialog::OnPaint();
	}
#else
	CSkinDialog::OnPaint();
#endif
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTestDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CTestDlg::OnSize(UINT nType, int cx, int cy)
{
	CSkinDialog::OnSize(nType, cx, cy);

	// TODO: Add your message handler code here

	if( m_bInitialized )
		RelocationControls();
}

void CTestDlg::RelocationControls()
{
	CRect rc;
	GetClientRect(&rc);

	SIZE size = Global.GetBitmapSize(IDX_BMP_BTN_BASE);

	int x=0, y=0, cx=0, cy=0;

	x = 20;
	y = 20;
	cx = rc.Width() - 20*2;
	cy = rc.Height() - 20 - 10*2 - size.cy;
	m_list.MoveWindow(x, y, cx, cy);
	ResizeListColumn(m_list, colWidthList);

	x = rc.Width() - 20 - size.cx;
	y = rc.Height() - 10 - size.cy;
	m_btnCancel.MoveWindow(x, y, size.cx, size.cy, TRUE);
	m_btnCancel.Invalidate();
	
	x -= size.cx + 10;
	m_btnOk.MoveWindow(x, y, size.cx, size.cy, TRUE);
	m_btnOk.Invalidate();
}

void CTestDlg::OnDestroy()
{
	CSkinDialog::OnDestroy();

	// TODO: Add your message handler code here

	if( m_pImageList != NULL ) 
	{
		if( m_pImageList->GetImageCount() )
			m_pImageList->DeleteImageList();
		delete m_pImageList;
		m_pImageList = NULL;
	}
}