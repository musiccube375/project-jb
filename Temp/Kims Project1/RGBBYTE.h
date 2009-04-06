#pragma once

class RGBBYTE
{
public:
	RGBBYTE(const BYTE& pixel = 0);
	RGBBYTE(const BYTE& _r, const BYTE& _g, const BYTE& _b);
	RGBBYTE(const RGBBYTE& pixel);
	~RGBBYTE(void);

public:
	BYTE b;
	BYTE g;
	BYTE r;

public:
	//치환 연산자 오버로딩
	RGBBYTE&	operator= (const RGBBYTE& pixel);
	RGBBYTE&	operator= (const COLORREF& pixel);
	RGBBYTE&	operator= (const BYTE& pixel);


	int			operator== (const RGBBYTE& pixel);
	int			operator!= (const RGBBYTE& pixel);
};
