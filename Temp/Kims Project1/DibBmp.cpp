#include "stdafx.h"
#include "Dib.h"
#define DIB_HEADER_MARKER ((WORD)'M' << 8 | 'B')

BOOL CDib::LoadBMP(LPCTSTR lpszFileName)
{
	//file변수 선언 후, lpszFileName의 이름을 가진 파일을 열고 오류 검사하는 문.
	CFile	file;

	if( !file.Open(lpszFileName,
		CFile::modeRead | CFile::shareDenyWrite ))
		return FALSE;

	//정상적으로 파일이 열렸을 시 수행. BITMAPINFOHEADER만큼의 길이를 읽어 들이고, 처음 2바이트가 'BM'인지 확인하는 문
	//'BM'이 아니라면 정상적인 BMP파일이라도 열리지 않는다.
	BITMAPFILEHEADER	bmfh;
	if( file.Read((LPSTR)&bmfh, sizeof(BITMAPFILEHEADER)) != sizeof(BITMAPFILEHEADER)) //파일에서 sizeof(BITMAPFILEHEADER)만큼의 크기를 
	{																				   //읽어 &bmfh에 할당
		file.Close();
		return FALSE;
	}
	
	if( bmfh.bfType != DIB_HEADER_MARKER )
	{
		file.Close();
		return FALSE;
	}

	//DIB구조의 크기를 계산.
	UINT nFileSize, nDibSize;
	nFileSize	= (UINT)file.GetLength();  //BITMAPFILEHEADER + BITMAPINFOHEADER + 색상테이블 + 픽셀데이터
	nDibSize	= nFileSize - sizeof(bmfh);//BITMAPINFOHEADER + 색상테이블 + 픽셀데이터

	//m_pDib에 메모리를 할당하고 Dib파일의 헤더에 추가
	if( m_pDib ) Destroy();
	m_pDib = new BYTE[nDibSize];
	if( m_pDib == NULL )
	{
		file.Close();
		return FALSE;
	}

	if( file.Read(m_pDib, nDibSize) != nDibSize)//파일에서 nDibSize만큼의 크기를 읽은 후 m_pDib에 할당.
	{
		delete [] m_pDib;
		m_pDib	= NULL;
		file.Close();
		return FALSE;
	}

	//BITMAPINFOHEADER의 biSize 필드를 확인하여 이것이 일반적인 윈도우즈 비트맵이 맞는지를 확인.
	LPBITMAPINFOHEADER lpbmi = (LPBITMAPINFOHEADER)m_pDib;
	if( lpbmi->biSize != sizeof(BITMAPINFOHEADER) )
	{
		delete [] m_pDib;
		m_pDib	= NULL;
		file.Close();
		return FALSE;
	}

	////////////////////////////////////////////////////////////////////////////////////////////
	//지금까지는 DIB의 내용을 CDib 객체 내부로 읽어 들이고 정상적인 포맷인지를 확인하였다./////
	////////////////////////////////////////////////////////////////////////////////////////////

	//멤버변수의 값을 설정//
	InitDib();

	//모든 과정 완료.
	file.Close();

	return TRUE;
}

BOOL CDib::SaveBMP(LPCTSTR lpszFileName)
{
	CFile	file;
	BITMAPFILEHEADER    bmfh;

	// DIB 객체를 포함하고 있지 않으면 FALSE를 반환.
	if( m_pDib == NULL )
		return FALSE;

	// 쓰기 모드로 파일 열기
	if( !file.Open(lpszFileName, CFile::modeCreate | CFile::modeWrite | 
		CFile::shareDenyWrite) )
		return FALSE;

	// BITMAPFILEHEADER 멤버 변수 설정
	bmfh.bfType      = DIB_HEADER_MARKER;	// 항상 "BM"
	bmfh.bfSize		 = (DWORD)sizeof(BITMAPFILEHEADER) + m_nDibSize;
	bmfh.bfReserved1 = 0;		// 항상 0
	bmfh.bfReserved2 = 0;		// 항상 0
	bmfh.bfOffBits	 = (DWORD)(sizeof(BITMAPFILEHEADER) 
		+ sizeof(BITMAPINFOHEADER) + sizeof(RGBQUAD)*GetPaletteNums());

	// BITMAPFILEHEADER 쓰기 
	file.Write((LPSTR)&bmfh, sizeof(bmfh));

	// DIB 구조(BITMAPINFOHEADER + 색상 테이블 + 픽셀 데이터) 쓰기
	file.Write(m_pDib, m_nDibSize);

	// 파일 닫기
	file.Close();

	return TRUE;
}