#pragma once

class RGBBYTE;
class CDib
{
public:
	CDib(void);
	CDib(const CDib& dib);
	~CDib(void);
protected:
	LONG			m_nWidth; //이미지 가로크기
	LONG			m_nHeight;//이미지 세로크기
	WORD			m_nBitCount;//픽셀당 비트수
	DWORD		m_nDibSize;	//Dib사이즈
	BYTE*			m_pDib;		//Dib 버퍼의 시작 주소
	BYTE**		m_pPtr;		//그레이 스케일 이미지에서 2D 픽셀 접근용 포인터
	RGBBYTE**	m_pRgbPtr;	//트루컬러 이미지에서 2D픽셀 접근용 포인터	

public:
	BOOL CreateGrayImage(int nWidth, int nHeight, BYTE value = 255);
	bool CreateRGBImage(int nWidth, int nHeight, COLORREF value = 0x00ffffff);
	void Destroy(void);

	//치환 연산자 오버로딩과 이미지 복사.
	CDib& operator = (const CDib& dib);

protected:
	BOOL InitDib(void);
public:
	BOOL			Load(LPCTSTR lpszFileName);
	BOOL			Save(LPCTSTR lpszFileName);
	
	BOOL			LoadBMP(LPCTSTR lpszFileName);
	BOOL			SaveBMP(LPCTSTR lpszFileName);
	//BITMAP정보 제공 함수///////////////////////////////////////////////////
	LONG			GetHeight(void)			{ return m_nHeight;			}
	LONG			GetWidth(void)			{ return m_nWidth;			}
	WORD			GetBitCount(void)		{ return m_nBitCount;		}
	DWORD			GetDibSize(void)		{ return m_nDibSize;		}
	BOOL			IsValid(void)			{ return (m_pDib != NULL);	}
	
	//m_pDib 포인터를 BITMAPINFO* 타입으로 형변환해서 반환한다.
	LPBITMAPINFO	GetBitmapInfoAddr()	{ return (LPBITMAPINFO)m_pDib;}
	
	//팔레트에서 RGBQUAD 배열의 개수를 반환.
	int				GetPaletteNums(void);	
	
	// 픽셀 데이터 시작 포인터 반환.
	LPVOID			GetDibBitsAddr(void);

	void Draw(HDC hDC);
	void Draw(HDC hDC, int dx, int dy);
	void Draw(HDC hDC, int dx, int dy, int dw, int dh, DWORD dwRop = SRCCOPY);
	void Draw(HDC hDC, int dx, int dy, int dw, int dh, int sx, int sy, int sw, int sh, DWORD dwRop = SRCCOPY);

	BOOL Copy(CDib* pDib);
	BOOL AllocPtr(void);
	void FreePtr(void);
	
	
	BYTE**		GetPtr(void);
	RGBBYTE**	CDib::GetRGBPtr(void);
};

inline BYTE**	CDib::GetPtr()
{
	ASSERT(m_nBitCount == 8);
	ASSERT(m_pPtr != NULL);

	return m_pPtr;
}
inline RGBBYTE** CDib::GetRGBPtr()
{
	ASSERT(m_nBitCount == 24);
	ASSERT(m_pRgbPtr != NULL);

	return m_pRgbPtr;
}

template<typename T>
inline T limit(const T& value)
{
	return ( (value > 255) ? 255 : ((value < 0) ? 0 : value));
}
template<typename T>
inline T limit(const T& value, const T& lower, const T& upper)
{
	return ((value > upper) ? upper : ((value < lower) ? lower : value));
}
template<typename T>
inline void swap( T& left, T& right )
{
	T tmp = left;
	left = right;
	right = tmp;
}