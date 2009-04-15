/* 
	Author				: 김정훈(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2008. 10. 17.
	Project	Name		: WinSock Manager
	Version				: 1.02.10

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP2
	Test Application	: Visual Studio 2003 + D3D 9.0c(Dec 2006)
	
	Contents

	WinSock Manager Header

	2008 ⓒ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "ServerSock.h"
#include "ClientSock.h"
#include "Convertor.h"

/*
	Structure : ELINFO structure

	Release Date		: 2008. 10. 28.
	Version				: 1.00.07
*/

typedef struct _ELINFO
{
	ELID			_ID;				// EL ID
	int				_nLowestFloor;		// 최하층
	ELRECVINFO		_Info;				// EL Recv Info
	ELSENDINFO		_ELSendInfo;		// EL Send Info
	bool			_bConnect;			// 연결 여부

	char			_szELState[32];		// EL 상태 텍스트
	char			_szAptIndex[16];	// 동 텍스트
	char			_szELIndex[16];		// 호기 텍스트
	char			_szELFloor[16];		// EL 층 텍스트
	char			_szELDir[16];		// EL 방향 텍스트

	// EL 정보 텍스트 설정
	bool			SetText()
	{
		bool bChange = false;
		char szTemp[64], szTemp2[64];

		strcpy(szTemp, _szELState);

		sprintf(_szELState, "%c%c", _Info._byELState[0],
									_Info._byELState[1]);

		// 통신 이상
		if(strcmp(_szELState, "00") == 0) 
		{
			strcpy(szTemp2, _szELState);
			sprintf(_szELState, "NET ERROR");
		}
		// 자동 운전(정상 운행)
		else if(strcmp(_szELState, "01") == 0) 
		{
			strcpy(szTemp2, _szELState);
			sprintf(_szELState, "NORMAL");
		}
		// 수동 운전(보수중)
		else if(strcmp(_szELState, "02") == 0) 
		{
			strcpy(szTemp2, _szELState);
			sprintf(_szELState, "REPARING");
		}
		// 독립 운전(이사중)
		else if(strcmp(_szELState, "03") == 0) 
		{
			strcpy(szTemp2, _szELState);
			sprintf(_szELState, "MOVING");
		}
		// 소방 운전
		else if(strcmp(_szELState, "04") == 0) 
		{
			strcpy(szTemp2, _szELState);
			sprintf(_szELState, "FIRE");
		}
		// 승강기 고장
		else if(strcmp(_szELState, "05") == 0) 
		{
			strcpy(szTemp2, _szELState);
			sprintf(_szELState, "ERROR");
		}
		// 파킹 상태
		else if(strcmp(_szELState, "06") == 0) 
		{
			strcpy(szTemp2, _szELState);
			sprintf(_szELState, "PARKING");
		}
		// 만원
		else if(strcmp(_szELState, "07") == 0) 
		{
			strcpy(szTemp2, _szELState);
			sprintf(_szELState, "FULL");
		}
		else 
		{
			strcpy(szTemp2, _szELState);
			sprintf(_szELState, "NET ERROR");
		}

		if(strcmp(szTemp2, szTemp) != 0) bChange = true;

		sprintf(_szAptIndex, "%c%c%c%c", _ID._byAptIndex[0],
										_ID._byAptIndex[1],
										_ID._byAptIndex[2],
										_ID._byAptIndex[3]);

		sprintf(_szELIndex, "%c%c", _ID._byELIndex[0],
									_ID._byELIndex[1]);

		strcpy(szTemp, _szELFloor);

		sprintf(_szELFloor, "%c%c", _Info._byFloor[0],
									_Info._byFloor[1]);

		if(strcmp(_szELFloor, szTemp) != 0) bChange = true;

		strcpy(szTemp, _szELDir);

		// None
		if(_Info._byDirection == 0x30) sprintf(_szELDir, "STOP");
		// Up
		else if(_Info._byDirection == 0x31) sprintf(_szELDir, "UP");
		// Down
		else if(_Info._byDirection == 0x32) sprintf(_szELDir, "DOWN");

		if(strcmp(_szELDir, szTemp) != 0) bChange = true;

		return bChange;
	}

	_ELINFO() 
	{
		_bConnect = false;

		strcpy(_szELState, "통신 이상");
		strcpy(_szAptIndex, "-");
		strcpy(_szELIndex, "-");
		strcpy(_szELFloor, "-");
		strcpy(_szELDir, "-");
	}

	_ELINFO(ELID ID, int nLowestFloor, ELSENDINFO ELSendInfo)
	{
		_bConnect = false;

		_ID = ID;
		_nLowestFloor = nLowestFloor;
		_ELSendInfo = ELSendInfo;

		strcpy(_szELState, "통신 이상");
		strcpy(_szAptIndex, "-");
		strcpy(_szELIndex, "-");
		strcpy(_szELFloor, "-");
		strcpy(_szELDir, "-");
	}
}ELINFO, *PELINFO;

/*
	Structure : WPINFO structure

	Release Date		: 2008. 10. 28.
	Version				: 1.00.07
*/

typedef struct _WPINFO
{
	WPID			_ID;				// WP ID
	CClientSock*	_pSock;				// WP Socket
	WPRECVINFO		_Info;				// WP Recv Info

	char			_szClass[32];		// 월패드 종류(홈콜, 출통기) 텍스트
	char			_szAptIndex[16];	// 동 텍스트
	char			_szELIndex[16];		// 호기 텍스트
	char			_szFloor[16];		// 층 텍스트
	char			_szCallDir[16];		// 콜 방향 텍스트

	bool			_bConnected;		// 연결 된 상태인지 아닌지 체크
	int				_nTime;				// 생성된 시간
	bool			_bArrived;			// 엘리베이터가 원하는 층으로 도착했눈지 체크
	bool			_bInList;			// 리스트 컨트롤에 있는지 없는지 체크
	int				_nSendFailCnt;		// Send Fail 카운터
	BYTE			_bySend[1024];		// 엘리베이터 콜 요청 반응 데이터

	// WP 정보 텍스트 설정
	bool			SetText(BYTE* pbyData, BYTE byClass, BYTE* pbyFloor)
	{
		/*if(pbyData[0] != 'S' || pbyData[1] != 'H' || pbyData[2] != 'V')
		{
			return false;
		}*/

		/*if(pbyData[13] != 'E' || pbyData[14] != 'T' || pbyData[15] != 'X')
		{
			return false;
		}*/

		char szClass[16], szDir[16];

		bool bChange = false;
		char szTemp[64];

		if(byClass == 0x30)
			strcpy(szClass, "HOMECALL");
		else if(byClass == 0x31)
			strcpy(szClass, "NOT HOME");
		else
			strcpy(szClass, "HOMECALL");

		strcpy(_szClass, szClass);

		strcpy(szTemp, _szCallDir);

		BYTE byData = pbyData[WE_CALL_PTR];

		if(pbyData[WE_CALL_PTR] == 1)
			strcpy(_szCallDir, "UP");
		else if(pbyData[WE_CALL_PTR] == -1 || pbyData[WE_CALL_PTR] == 255)
			strcpy(_szCallDir, "DOWN");
		else	
			strcpy(_szCallDir, "-");
		
		if(strcmp(_szCallDir, szTemp) != 0) bChange = true;

		strcpy(_szClass, szClass);

		/*sprintf(_szText, "[구분] %s [동] %c%c%c%c [호기] %c%c [층] %c%c [콜 방향] %s", szClass,
																						pbyData[WE_APTINDEX_PTR],
																						pbyData[WE_APTINDEX_PTR+1],
																						pbyData[WE_APTINDEX_PTR+2],
																						pbyData[WE_APTINDEX_PTR+3],
																						pbyData[WE_INDEX_PTR],
																						pbyData[WE_INDEX_PTR+1],
																						pbyData[WE_FLOOR_PTR],
																						pbyData[WE_FLOOR_PTR+1],
																						szDir);*/

		char Temp[64];

		sprintf(Temp, "%c%c%c%c", pbyData[WE_APTINDEX_PTR],
								  pbyData[WE_APTINDEX_PTR+1],
								  pbyData[WE_APTINDEX_PTR+2],
								  pbyData[WE_APTINDEX_PTR+3]);
		strcpy(_szAptIndex, Temp);

		sprintf(Temp, "%c%c", pbyData[WE_INDEX_PTR],
								  pbyData[WE_INDEX_PTR+1]);
		strcpy(_szELIndex, Temp);

		if(pbyFloor == NULL) return bChange;

		sprintf(Temp, "%c%c", pbyFloor[0], pbyFloor[1]);
		strcpy(_szFloor, Temp);

		return bChange;
	}

	// 현재 시간을 설정
	void			SetCurTime()
	{
		CTime Time = CTime::GetCurrentTime();   

		int nHour = Time.GetHour();
		int nMin = Time.GetMinute();
		int nSec = Time.GetSecond();

		int nCurTime = (nHour * 3600) + (nMin * 60) + nSec;

		_nTime = nCurTime;
	}

	_WPINFO() 
	{
		_bConnected = true;
		_bArrived = false;
		_bInList = true;

		_nSendFailCnt = 0;
	}

	_WPINFO(WPID ID, CClientSock* pSock)
	{
		_ID = ID;
		_pSock = pSock;
		_bConnected = true;
		_bArrived = false;
		_bInList = true;

		SetCurTime();

		_nSendFailCnt = 0;
	}
}WPINFO, *PWPINFO;

typedef map<int, CServerSock*>					SERVERSOCK_MAP;
typedef map<int, CServerSock*>::iterator		SERVERSOCK_MAP_IT;
typedef map<int, CServerSock*>::value_type		SERVERSOCK_MAP_VALUE;

typedef map<int, WPINFO>						WPINFO_MAP;
typedef map<int, WPINFO>::iterator				WPINFO_MAP_IT;
typedef map<int, WPINFO>::value_type			WPINFO_MAP_VALUE;

typedef map<int, ELINFO>						ELINFO_MAP;
typedef map<int, ELINFO>::iterator				ELINFO_MAP_IT;
typedef map<int, ELINFO>::value_type			ELINFO_MAP_VALUE;

#define SERVER_PORT		4332
#define EL_PORT			2999

/*
	Class : WinSock Manager Class

	Release Date		: 2008. 10. 17.
	Version				: 1.03.03
*/

class CWinSockMgr
{
private:
	// Server Socket
	//SERVERSOCK_MAP		m_mapServerSock;		// 서버 소켓 맵
	//int					m_nServerSockCnt;		// 서버 소켓 맵 카운터
	CServerSock				m_ServerSock;		// 서버 소켓	
	
	// Wallpad Info(Homecall)
	WPINFO_MAP			m_mapWPInfo;			// 월패드 정보 맵
	int					m_nWPInfoCnt;			// 월패드 정보 맵 카운터
	int					m_nWPSockCnt;			// 월패드 소켓 카운터(상태 소켓만)

	// Elevator Info
	ELINFO_MAP			m_mapELInfo;			// EL 정보 맵
	int					m_nELInfoCnt;			// EL 정보 맵 카운터

	bool				m_bELConnect;			// Check the connection status whether it is connected or not.
	CClientSock*		m_pELSocket;			// EL 서버로부터 접속 및 데이터 송수신을 위한 소켓

	int					m_nSelectIndex;			// 선택된 EL 인덱스

public:
	int					m_nWPAcceptCnt;			// WP 접속 카운터
	int					m_nWPDiscCnt;			// WP 접속 종료 카운터
	int					m_nELCallCnt;			// EL 콜 요청 카운터
	int					m_nELArriveCnt;			// EL 도착 완료 카운터
	int					m_nIOCnt;				// 총 출통기 호출 카운터

public:
	BYTE				m_byServerID[17];		// 서버 아이디(17 Byte)

public:
	ELINFO_MAP*			GetELInfo() { return &m_mapELInfo; }
	ELINFO*				GetELInfo(ELID ID);
	ELINFO*				GetELInfo(BYTE* pbyELIndex);

	WPINFO_MAP*			GetWPInfo() { return &m_mapWPInfo; }

	int					GetELSize() { return m_mapELInfo.size(); }
	int					GetWPSize() { return m_mapWPInfo.size(); }

	bool				GetELConnect() { return m_bELConnect; }

	int					GetSelectIndex() { return m_nSelectIndex; }

public:
	void				SetELConnect(bool bConnect) { m_bELConnect = bConnect; }
	
	void				SetServerID(CString strServerID);

public:
	// 서버 소켓 추가
	void				AddServerSock(int nIndex, int nPort);
	// 월패드 정보 추가
	void				AddWPInfo(WPINFO WPInfo);
	// EL 정보 추가
	void				AddELInfo(BYTE* pbyAptIndex, BYTE* pbyELIndex, int nLowestFloor);

	// 서버 소켓 삭제(Wp 카운터 필요)
	void				DelServerSock(int nIndex);
	// 월패드 정보 삭제(WP ID 필요)
	void				DelWPInfo(WPID ID);
	// EL 정보 삭제(EL ID 필요)
	void				DelELInfo(ELID ID);
	// EL 정보 삭제(EL 카운터 필요)
	void				DelELInfo(int nCnt);

	// 서버 소켓 클리어
	void				ClearServerSock();
	// 월패드 정보 클리어
	void				ClearWPInfo();
	// EL 정보 클리어
	void				ClearELInfo();

public:
	// 윈속 매니저 초기화
	void				Init(int nHomeCnt = 0, int nELCnt = 0, int nServerCnt = 1);
	// 서버 소켓 초기화
	void				InitServerSock(int nServerCnt = 1);
	// EL 초기화
	void				InitEL();

	// 받은 데이터로부터 하나의 EL 정보만을 추출
	bool				ExtractELInfoFromData(BYTE* pTemp, BYTE* pbyData, int nIndex);
	// 모든 월패드로 정보 전송
	bool				SendToHome(BYTE* pbyData, BYTE* pbyAptIndex, int nLowestFloor, char* pszRealFloor, BYTE byELDir);
	// 모든 EL로 정보 전송
	void				SendToEL(BYTE* pbyData, BYTE* pbyELIndex, PWPRECVINFO pWPRecvInfo, bool bHome = true);
	// 기본 EL 정보 EL로 Send
	void				SendDefaultELInfo();
	// EL 상태 정보를 요청(2.5)
	void				SendELCallReq(PWPINFO pWPInfo);

	// 윈속 매니저 클리어
	void				Clear();

	// 프레임 체크(업콜, 다운콜에 대한 분석을 위하여 추가)
	bool				CheckFrame(BYTE* pbyFrame);

	// WP 데이터 수신 로그
	void				WPRecvLog(BYTE* pbyAptIndex, BYTE* pbyFloor, BYTE* pbyELLine, BYTE* pbyData);

	// 이미 같은 WP 가 있는지 체크(임시 버전에서 사용)
	bool				HasSameWP(BYTE* pbyAptIndex, BYTE* pbyFloor, BYTE* pbyELLine);

	// 이미 같은 WP IP 가 있는지 체크(임시 버전에서 사용)
	bool				HasSameIP(CClientSock* pClient);

public:
	// 정보 수신
	void				OnReceive(SOCKET Socket, int nTag);
	// 정보 수신(월패드)
	bool				OnReceiveFromHome(SOCKET Socket);
	// 정보 수신(EL)
	bool				OnReceiveFromEL(SOCKET Socket);
	// EL 출력 갱신
	void				UpdateEL();

	// 접속 승인
	void				OnAccept();
	// 접속
	bool				OnConnect();
	// 접속(소켓 필요)
	bool				OnConnect(SOCKET Socket);
	// EL 접속 종료
	void				OnCloseEL(SOCKET Socket);
	// WP 접속 종료
	void				OnCloseWP(SOCKET Socket);


public:
	// The basic constructor
	CWinSockMgr();

	// The basic destructor
	~CWinSockMgr();
};