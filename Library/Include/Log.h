/* 
	Author				: 김정훈(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2008. 11. 02.
	Project	Name		: Log
	Version				: 1.00.08

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP2
	Test Application	: Visual Studio 2003 + D3D 9.0c(Dec 2006)
	
	Contents

	Log Header

	2008 ⓒ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include <assert.h>

#include <deque>

using namespace std;

#define MAX_LOG_COUNT	90000
#define LOG_ALL_TYPE	0x424C4C

/*
	Structure : LOGINFO structure

	Release Date		: 2008. 11. 02.
	Version				: 1.00.06
*/

typedef struct _LOGINFO
{
	int			_nType;			// 로그 타입
	CString		_strText;		// 로그 텍스트
	CString		_strTime;		// 로그 시간

	char*		GetText() { return _strText.GetBuffer(0); }
	char*		GetTime() { return _strTime.GetBuffer(0); }
	int			GetTextSize() { return strlen(_strText); }

	_LOGINFO() { }
	_LOGINFO(int nType, CString strText, CString strTime)
	{
		_nType = nType;
		_strText = strText;
		_strTime = strTime;
	}
}LOGINFO, PLOGINFO;

typedef deque<LOGINFO>					LOGINFO_DEQUE;
typedef deque<LOGINFO>::iterator		LOGINFO_DEQUE_IT;

/*
	Class : Log Manager Class

	Release Date		: 2008. 11. 02.
	Version				: 1.00.02
*/

class CLogInfo
{
private:
	LOGINFO_DEQUE		m_deqLogInfo;	// 로그 정보 데크 

public:
	LOGINFO_DEQUE*		GetLogInfo() { return &m_deqLogInfo; }
	LOGINFO				GetLogInfo(int nIndex) { return m_deqLogInfo[nIndex]; }

public:
	int					GetSize() { return m_deqLogInfo.size(); }

	// 로그 정보를 추가한다.
	void				AddLogInfo(int nType, CString str, CString strTime);
	// 로그 정보를 Pop(Front) 한다.
	void				PopLogInfo();
	// 모든 로그 정보를 클리어한다.
	void				ClearLogInfo();

public:
	// The basic constructor
	CLogInfo();

	// The basic destructor
	~CLogInfo();
};

/*
	Class : Log Class

	Release Date		: 2008. 11. 02.
	Version				: 1.00.06
*/

class CLog
{
protected:
	CLogInfo	m_LogInfo;			// Log Info
	int			m_nLogCnt;			// Log Info Count

public:
	CLogInfo	GetLogInfo() { return m_LogInfo; }
	int			GetLogSize();

	void		GetLog(int nType, CLogInfo* pLogInfo);

public:
	// 로그 추가(fmt)
	void		AddLog(const char* fmt, ...);
	// 로그 추가(nType, fmt)
	void		AddLog(int nType, const char* fmt, ...);

	// 로그 클리어
	void		ClearLog();

	void		SaveTxtFile(const char* pszFileName, bool bTime = false, int nType = LOG_ALL_TYPE);
	// For Excel 
	void		SaveCSVFile(const char* pszFileName, int nType = LOG_ALL_TYPE);

public:
	// The basic constructor
	CLog();  

	// The basic destructor
	~CLog();
};
