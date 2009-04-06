#include "StdAfx.h"
#include "Dib.h"
#include "RGBBYTE.h"

CDib::CDib(void)
{
	m_nWidth		= 0;
	m_nHeight		= 0;
	m_nBitCount		= 0;
	m_nDibSize		= 0;
	
	m_pDib			= NULL;
	m_pPtr			= NULL;
	m_pRgbPtr		= NULL;
}
CDib::CDib(const CDib& dib)
{
	m_nWidth		= 0;
	m_nHeight		= 0;
	m_nBitCount		= 0;
	m_nDibSize		= 0;

	m_pDib			= NULL;
	m_pPtr			= NULL;
	m_pRgbPtr		= NULL;

	if( dib.m_pDib != NULL )
	{
		//인자로부터 DIB 내용을 복사한다.
		m_pDib = new BYTE[dib.m_nDibSize];
		memcpy(m_pDib, dib.m_pDib, dib.m_nDibSize);

		//멤버 변수 값 설정
		InitDib();
	}

}
//인자로 넘어온 dib와 동일한 CDib 객체를 생성한다.
CDib& CDib::operator=(const CDib& dib)
{
	//재귀 검사
	if( this == &dib )
		return *this;

	//dib가 비어있는 CDib 객체라면 자신도 비운다
	if( dib.m_pDib == NULL )
	{
		Destroy();
		return *this;
	}

	//현재 설정된 CDib 객체가 있다면 삭제.
	if( m_pDib ) Destroy();

	//(BITMAPINFOHEADER + 픽셀데이터)를 담을 메모리 공간 할당
	m_pDib = new BYTE[dib.m_nDibSize];

	//Dib내용 복사
	memcpy( m_pDib, dib.m_pDib, dib.m_nDibSize );

	//멤버 변수 값 설정
	InitDib();

	return *this;
}


CDib::~CDib(void)
{
	Destroy();
}

BOOL CDib::CreateGrayImage(int nWidth, int nHeight, BYTE value)
{
	if( m_pDib ) Destroy();

	int nBitCount = 8;
	DWORD dwSizeImage = nHeight * (DWORD)((nWidth*nBitCount/8+3) & ~3);

	m_pDib = new BYTE[sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*(1<<nBitCount) + dwSizeImage];
	if( m_pDib == NULL ) return FALSE;

	////BITMAPINFOHEADER 구조체 필드 값을 설정.
	LPBITMAPINFOHEADER lpbmi		= (LPBITMAPINFOHEADER)m_pDib;
	lpbmi->biSize					= sizeof(BITMAPINFOHEADER);
	lpbmi->biWidth					= nWidth;
	lpbmi->biHeight					= nHeight;
	lpbmi->biPlanes					= 1;
	lpbmi->biBitCount				= nBitCount;
	lpbmi->biCompression			= BI_RGB;
	lpbmi->biSizeImage				= dwSizeImage;
	lpbmi->biXPelsPerMeter			= 0;
	lpbmi->biYPelsPerMeter			= 0;
	lpbmi->biClrUsed				= 0;
	lpbmi->biClrImportant			= 0;

	////색상테이블을 설정.
	RGBQUAD* pPal = (RGBQUAD*)((BYTE*)m_pDib + sizeof(BITMAPINFOHEADER));
	for( int i = 0; i < 256; i++ )
	{
		pPal->rgbBlue		= (BYTE)i;
		pPal->rgbGreen		= (BYTE)i;
		pPal->rgbRed		= (BYTE)i;
		pPal->rgbReserved	= 0;
		pPal++;
	}	

	InitDib();

	BYTE* pData = (BYTE*)GetDibBitsAddr();
	memset(pData, value, dwSizeImage);
	
	return TRUE;
}

bool CDib::CreateRGBImage(int nWidth, int nHeight, COLORREF value)
{
	if( m_pDib ) Destroy();

	int nBitCount = 24;

	//실제 영상 데이터의 크기//
	DWORD dwSizeImage = nHeight * (DWORD)((nWidth * nBitCount/ 8+3)&~3);

	//////메모리 공간 할당/////
	m_pDib = new BYTE[sizeof(BITMAPINFOHEADER) + dwSizeImage];
	if( m_pDib == NULL ) return false;

	//BITMAPINFOHEADER부분 초기화//
	LPBITMAPINFOHEADER lpbmi		= (LPBITMAPINFOHEADER)m_pDib;
	
	lpbmi->biSize					= sizeof(BITMAPINFOHEADER);
	lpbmi->biWidth					= nWidth;
	lpbmi->biHeight					= nHeight;
	lpbmi->biPlanes					= 1;
	lpbmi->biBitCount				= nBitCount;
	lpbmi->biCompression			= BI_RGB;
	lpbmi->biSizeImage				= dwSizeImage;
	lpbmi->biXPelsPerMeter			= 0;
	lpbmi->biYPelsPerMeter			= 0;
	lpbmi->biClrUsed				= 0;
	lpbmi->biClrImportant			= 0;

	InitDib();

	////TrueColor영상의 픽셀값을 초기화 시키는 부분
	register int i, j;
	for( j = 0; j < m_nHeight; j++ )
	{
		for( i = 0; i < m_nWidth; i++ )
		{
			m_pRgbPtr[j][i] = value;
		}
	}
	
	return TRUE;
}

void CDib::Destroy(void)
{
	if( m_pDib )
	{
		delete [] m_pDib;
		m_pDib = NULL;
	}

	FreePtr();

	m_nWidth	= 0;
	m_nHeight	= 0;
	m_nBitCount = 0;
	m_nDibSize	= 0;
}

BOOL CDib::InitDib(void)
{
	LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;

	//Image의 가로 크기, 세로 크기, 픽셀당 비트수, DIB 크기에 대한 멤버 변수를 설정
	m_nWidth	= lpbmi->biWidth;
	m_nHeight	= lpbmi->biHeight;
	m_nBitCount	= lpbmi->biBitCount;

	DWORD dwSizeImage = m_nHeight * 
		(DWORD)((m_nWidth * m_nBitCount/8 +3)& ~3);
	m_nDibSize = sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD) * GetPaletteNums() + dwSizeImage;

	if( !AllocPtr() )
		return FALSE;

	return TRUE;
}

BOOL CDib::Load(LPCTSTR lpszFileName)
{
	////////////////////////파일이 BMP 파일인지 확인하는 함수입니다.///////////////////

	CString filetype;
	filetype = lpszFileName;
	filetype.MakeUpper();				//MakeUpper() -> 문자를 죄다 대문자로 바꿔놓는 함수//

	if( filetype.Right(4) == ".BMP" )
		return LoadBMP(lpszFileName);	//BMP파일이라면 LoadBMP함수로 넘어가라..lpszFileName을 가지고

	return 0;
}

BOOL CDib::Save(LPCTSTR lpszFileName)
{
	////////////////////////파일이 BMP 파일인지 확인하는 함수입니다.///////////////////

	CString filetype;
	filetype = lpszFileName;
	filetype.MakeUpper();				//MakeUpper() -> 문자를 죄다 대문자로 바꿔놓는 함수//

	if( filetype.Right(4) == ".BMP" )
		return SaveBMP(lpszFileName);	//BMP파일이라면 LoadBMP함수로 넘어가라..lpszFileName을 가지고

	return 0;
}
int CDib::GetPaletteNums(void)
{
	switch( m_nBitCount )
	{
	case 1:		return 2;
	case 4:		return 16;
	case 8:		return 256;
	default:	return 0;
	}
}
LPVOID CDib::GetDibBitsAddr(void)
{
	LPBITMAPINFOHEADER lpbmi;
	LPVOID lpDibBits;
	lpbmi = (LPBITMAPINFOHEADER)m_pDib;

	lpDibBits = (LPVOID)((BYTE*)m_pDib + lpbmi->biSize + sizeof(RGBQUAD)*GetPaletteNums());

	return lpDibBits;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////
void CDib::Draw(HDC hDC)
{
	Draw(hDC, 0, 0);
}


void CDib::Draw(HDC hDC, int dx, int dy)
{
	LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
	void* lpBits = (void*)GetDibBitsAddr();

	::SetDIBitsToDevice(hDC,	//hDC
		dx,						//DestX
		dy,						//DestY
		m_nWidth,				//nSrcWidth
		m_nHeight,				//nSrcHeight
		0,						//SrcX
		0,						//SrcY
		0,						//nStartScan
		m_nHeight,				//nNumScans
		lpBits,					//lpBits
		lpbi,					//lpBitsInfo
		DIB_RGB_COLORS			//wUsage
		);
}
void CDib::Draw(HDC hDC, int dx, int dy, int dw, int dh, DWORD dwRop)
{
	LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
	void* lpDibBits = (void *)GetDibBitsAddr();

	::StretchDIBits(hDC,
		dx,
		dy,
		dw,
		dh,
		0,
		0,
		m_nWidth,
		m_nHeight,
		lpDibBits,
		lpbi,
		DIB_RGB_COLORS,
		SRCCOPY
		);
}
void CDib::Draw(HDC hDC, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, DWORD dwRop)
{
	LPBITMAPINFO lpbi = (LPBITMAPINFO)m_pDib;
	void* lpBits = (void *)GetDibBitsAddr();

	::StretchDIBits(hDC,
		dx,
		dy,
		dw,
		dh,
		sx,
		sy,
		sw,
		sh,
		lpBits,
		lpbi,
		DIB_RGB_COLORS,
		SRCCOPY
		);
}

BOOL CDib::Copy(CDib* pDib)
{
	if( !pDib->IsValid() )
	{
		Destroy();
		return TRUE;
	}

	if( m_pDib ) Destroy();

	//(BITMAPINFOHEADER + 픽셀데이터)를 담을 메모리 공간 할당
	DWORD dwDibSize = pDib->GetDibSize();
	m_pDib = new BYTE[dwDibSize];
	if( m_pDib == NULL )
		return FALSE;

	//Dib내용 복사
	BYTE* pbi = (BYTE*)pDib->GetBitmapInfoAddr();

	memcpy(m_pDib, pbi, dwDibSize);

	//멤버 변수 값 설정
	InitDib();
	
	return TRUE;
}

BOOL CDib::AllocPtr(void)
{
	if( m_nBitCount == 8 )
	{
		if( m_pPtr ) FreePtr();
		m_pPtr = new BYTE* [m_nHeight];
		if( !m_pPtr ) return FALSE;
	
		int nRWidth = ((m_nWidth*m_nBitCount/8 +3)& ~3);
		BYTE* pDib = (BYTE*)GetDibBitsAddr();
		
		for( int i = 0; i < m_nHeight; i++ )
			m_pPtr[i] = (BYTE*)(pDib + (m_nHeight -i -1)*nRWidth);
	}
	else if( m_nBitCount == 24 ) //트루컬러 이미지
	{
		if( m_pRgbPtr ) FreePtr();
		m_pRgbPtr = new RGBBYTE* [m_nHeight];
		if( !m_pRgbPtr ) return FALSE;

		int nRWidth = ((m_nWidth*m_nBitCount/8 +3)& ~3);
		BYTE* pDib = (BYTE*)GetDibBitsAddr();
		
		for( int i = 0; i < m_nHeight; i++ )
			m_pRgbPtr[i] = (RGBBYTE*)(pDib + (m_nHeight -i -1)*nRWidth);
	}
	else
		return FALSE;

	return TRUE;
}

//DIB 객체를 저장하기 위해 할당한 메모리 공간을 삭제하는 함수.
void CDib::FreePtr(void)
{
	if( m_pPtr != NULL )
	{
		delete [] m_pPtr;
		m_pPtr = NULL;
	}

	if( m_pRgbPtr != NULL )
	{
		delete [] m_pRgbPtr;
		m_pRgbPtr = NULL;
	}
}

