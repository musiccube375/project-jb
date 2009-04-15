#include "stdafx.h"
#include "WinSockMgr.h"
#include "ELConfigDll.h"

CWinSockMgr::CWinSockMgr()
{
	
}	

CWinSockMgr::~CWinSockMgr()
{
	Clear();
	SAFE_DELETE(m_pELSocket);
}

void CWinSockMgr::InitEL()
{
	CELConfigDll ELConfigDll;

	GetELConfigDll(&ELConfigDll);

	for(int i = 0; i < ELConfigDll.GetSize(); i++)
	{
		BYTE* pbyAptIndex = ELConfigDll.GetAptIndex(i);
		BYTE* pbyELIndex = ELConfigDll.GetELIndex(i);
		int nLowestFloor = ELConfigDll.GetLFloor(i);

		// 엘리베이터를 등록(동, 라인, 최하층)
		g_sToolMgr.GetWinSock()->AddELInfo(pbyAptIndex, pbyELIndex, nLowestFloor);
	}
}

void CWinSockMgr::SetServerID(CString strServerID)
{
	char* pszText = strServerID.GetBuffer(0);

	for(int i = 0; i < 17; i++)
	{
		m_byServerID[i] = pszText[i];
	}
}

ELINFO* CWinSockMgr::GetELInfo(ELID ID)
{
	ELINFO_MAP_IT it = m_mapELInfo.begin();

	for( ; it != m_mapELInfo.end(); it++)
	{
		if(it->second._ID == ID)
		{
			return &it->second;
		}
	}

	return NULL;
}

ELINFO* CWinSockMgr::GetELInfo(BYTE* pbyELIndex)
{
	ELINFO_MAP_IT it = m_mapELInfo.begin();

	for( ; it != m_mapELInfo.end(); it++)
	{
		if(it->second._Info._byELIndex[0] == pbyELIndex[0] &&
		   it->second._Info._byELIndex[1] == pbyELIndex[1])
		{
			return &it->second;
		}
	}

	return NULL;
}
 
void CWinSockMgr::AddServerSock(int nIndex, int nPort)
{
	/*if(nIndex > MAX_INT_COUNT) nIndex = 0;

	CServerSock* pServerSock = new CServerSock;

	//pServerSock->Close();
	//pServerSock->Create(nPort);
	//pServerSock->Listen();

	m_mapServerSock.insert(SERVERSOCK_MAP_VALUE(nIndex, pServerSock));

	//m_mapServerSock[0]->Close();
	m_mapServerSock[0]->Create(nPort);
	m_mapServerSock[0]->Listen();*/

	m_ServerSock.Create(nPort);
	m_ServerSock.Listen();
}

void CWinSockMgr::AddWPInfo(WPINFO WPInfo)
{
	//if(!g_sToolMgr.GetToolFrameMgr()->GetRun()) return;

	if(m_nWPInfoCnt > MAX_INT_COUNT) m_nWPInfoCnt = 0;

	m_mapWPInfo.insert(WPINFO_MAP_VALUE(m_nWPInfoCnt++, WPInfo));
}

void CWinSockMgr::AddELInfo(BYTE* pbyAptIndex, BYTE* pbyELIndex, int nLowestFloor)
{
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "EL 정보 초기화 작업 시작...");

	// EL ID 구성
	ELID ID(pbyAptIndex, pbyELIndex);
	
	int n10Num = (pbyELIndex[0] - '0') * 10;
	int nNum = pbyELIndex[1] - '0';

	BYTE byIndex = n10Num + nNum + 0x30;

	ELSENDINFO ELSendInfo;
	ELSendInfo.SetDefault(byIndex);

	// EL 정보 구성
	ELINFO ELInfo(ID, nLowestFloor, ELSendInfo);

	ELInfo._bConnect = false;

	if(m_nELInfoCnt > MAX_INT_COUNT) m_nELInfoCnt = 0;

	// EL 정보 맵 추가
	m_mapELInfo.insert(ELINFO_MAP_VALUE(m_nELInfoCnt++, ELInfo));
}

void CWinSockMgr::DelServerSock(int nIndex)
{
	/*SERVERSOCK_MAP_IT it = m_mapServerSock.find(nIndex);

	if(it == m_mapServerSock.end()) return;

	it->second->Close();
	SAFE_DELETE(it->second);
	m_mapServerSock.erase(it);*/
}

void CWinSockMgr::DelWPInfo(WPID ID)
{
	WPINFO_MAP_IT it = m_mapWPInfo.begin();

	for( ; it != m_mapWPInfo.end(); it++)
	{
		if(it->second._ID == ID)
		{
			it->second._pSock->Close();
			SAFE_DELETE(it->second._pSock);
			m_mapWPInfo.erase(it);

			return;
		}
	}
}

void CWinSockMgr::DelELInfo(ELID ID)
{
	ELINFO_MAP_IT it = m_mapELInfo.begin();

	for( ; it != m_mapELInfo.end(); it++)
	{
		if(it->second._ID == ID)
		{
			m_mapELInfo.erase(it);

			return;
		}
	}
}

void CWinSockMgr::DelELInfo(int nCnt)
{
	ELINFO_MAP_IT it = m_mapELInfo.begin();

	if(it == m_mapELInfo.end()) return;

	for(int i = 0; i < nCnt; i++, it++) { }

	m_mapELInfo.erase(it);
}

void CWinSockMgr::Init(int nHomeCnt, int nELCnt, int nServerCnt)
{
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_ALL, "프로그램 초기화 작업 시작...");

	//m_nServerSockCnt = 0;
	m_nWPInfoCnt = 0;
	m_nWPSockCnt = 0;
	m_nELInfoCnt = 0;

	m_nWPAcceptCnt = 0;
	m_nWPDiscCnt = 0;
	m_nELCallCnt = 0;
	m_nELArriveCnt = 0;
	m_nIOCnt = 0;

	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_ALL, "프로그램 초기화 작업 성공...");

	ClearWPInfo();
	ClearELInfo();

	g_sToolMgr.GetToolFrameMgr()->SetRun(true);

	m_bELConnect = false;

	// CFG 파일 로드(Tool, ELConfig, IOConfig)
	g_sToolMgr.GetCFGFile()->LoadCFGFile("Config.cfg");

	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "서버 소켓 초기화 작업 시작...");

	// 서버 소켓 초기화
	ClearServerSock();
	InitServerSock();

	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "서버 소켓 초기화 작업 성공...");
	
	char name[255];
	CString strIP;
	PHOSTENT hostinfo;

	// 자신의 IP 알기
	if(gethostname(name, sizeof(name)) == 0) 
	{ 
		if((hostinfo = gethostbyname(name)) != NULL) 
		{ 
			strIP = inet_ntoa (*(struct in_addr *) *hostinfo->h_addr_list); 
		} 
	}

	//g_sToolMgr.GetToolConfig()->_strWPIP.SetString(strIP);

	InitEL();

	g_sToolMgr.GetCFGFile()->LoadELConfigFile("ELConfig.cfg");
	g_sToolMgr.GetCFGFile()->LoadIOConfigFile("IOConfig.cfg");

	SetServerID(g_sToolMgr.GetToolConfig()->_strServerID);

	m_nSelectIndex = -1;
}

void CWinSockMgr::InitServerSock(int nServerCnt)
{
	for(int i = 0; i < nServerCnt; i++)
	{
		AddServerSock(i, atoi(g_sToolMgr.GetToolConfig()->_strWPPort));
		//m_nServerSockCnt++;
	}
}

bool CWinSockMgr::ExtractELInfoFromData(BYTE* pTemp, BYTE* pbyData, int nIndex)
{
	//if(pbyData[0] != 'S' || pbyData[1] != 'T' || pbyData[2] != 'X')
	//	return false;

	int nCnt = 3;

	pTemp[0] = 'S';
	pTemp[1] = 'T';
	pTemp[2] = 'X';

	// 인덱스로부터 하나의 EL 정보만을 빼낸다.
	for(int i = 0; i < EL_INFO_SIZE; i++)
	{
		pTemp[nCnt++] = pbyData[i + (nIndex * EL_INFO_SIZE) + 3];
	}

	pTemp[EL_INFO_SIZE+3] = 'E';
	pTemp[EL_INFO_SIZE+4] = 'T';
	pTemp[EL_INFO_SIZE+5] = 'X';

	return true;
}

bool CWinSockMgr::SendToHome(BYTE* pbyData, BYTE* pbyAptIndex, int nLowestFloor, char* pszRealFloor, BYTE byELDir)
{
	//if(!g_sToolMgr.GetToolFrameMgr()->GetRun()) return false;

	char buff[MAX_STRING_SIZE];
	WPINFO_MAP_IT it = m_mapWPInfo.begin();

	if(m_mapWPInfo.size() <= 0 || g_pMainDlg->m_listctrlWP.GetItemCount() <= 0)
	{
		m_nWPSockCnt = 0;
		sprintf(buff, "%d", m_nWPSockCnt);

		g_pMainDlg->m_editWPCount.SetWindowText(buff);

		g_pMainDlg->m_listctrlWP.DeleteAllItems();
	}

	for(int i = 0; it != m_mapWPInfo.end(); i++, it++)
	{
		BYTE byELIndex[2];//, byELFloor[2];

		byELIndex[0] = pbyData[7];
		byELIndex[1] = pbyData[8];

		// 현재 선택된 호기와 같지 않으면 다음 월패드로 넘어감
		// 월패드내에서 여러 개의 호기가 번갈아 가면서 출력되는 문제때문에
		// 단 하나의 엘리베이터 호기만 선택된다
		if(it->second._Info._bySelectELIndex[0] != byELIndex[0] ||
           it->second._Info._bySelectELIndex[1] != byELIndex[1])
		   continue;

		// 출통기일 경우
		if(it->second._Info._byClass == 1 ||
		   it->second._Info._byClass == 0x31)
		{
			// 맞는 호기로만 정보 전송
			if(!g_sToolMgr.GetIOConfig()->CheckIndex(byELIndex, it->second._ID._byAptIndex, it->second._ID._byELLine)) continue;
		}
		// 홈콜일 경우
		else
		{
			// 맞는 호기로만 정보 전송
			if(!g_sToolMgr.GetELConfig()->CheckIndex(byELIndex, it->second._ID._byAptIndex, it->second._ID._byELLine)) continue;
		}

		//if(it->second._Info._dwCommand == 0xA000)
		{
			// 원하는 층에 도착했었다면 파싱도 필요없고 그냥 다음 WP 로 넘어간다
			//if(it->second._bArrived) break;
			
			// 원하는 층에 도착하였을 때
			if(atoi(pszRealFloor) == it->second._Info._nFloor)
			{
				// 엘리베이터가 정지하였을 때나 세대 층의 호출 방향과 같으면 현재 층을 비교하여 도착 여부를 확인

				BYTE byWPDir = 0x30;

				if(it->second._Info._byNewUp == '1' || it->second._Info._byNewUp == 1 ||
				   it->second._Info._byNewUp == 0x31) 
				{
					byWPDir = 0x31;
				}
				else if(it->second._Info._byNewDown == '1' || it->second._Info._byNewDown == 1 ||
				        it->second._Info._byNewDown == 0x31)
				{
					byWPDir = 0x32;
				}

				if(byELDir == 0x30 || byELDir == 0 || byELDir == byWPDir)
				{
					//if(!it->second._bArrived)
					{
						sprintf(buff, "SOCKET : [%d] - EL [%c%c]호기 [%s]층 - WP (%c%c%c%c동 %c%c층 %c%c호 라인) 도착 완료", 
																					it->second._pSock->m_hSocket,
																					byELIndex[0], byELIndex[1], pszRealFloor,
																					it->second._ID._byAptIndex[0], 
																					it->second._ID._byAptIndex[1], 
																					it->second._ID._byAptIndex[2], 
																					it->second._ID._byAptIndex[3],
																					it->second._Info._byFloor[0],
																					it->second._Info._byFloor[1],
																					it->second._ID._byELLine[0],
																					it->second._ID._byELLine[1]);

						g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, buff);
						g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "");

						it->second._bArrived = true;

						m_nELArriveCnt++;
					}
				}
			}
		}

		BYTE* pbyTemp = g_sToolMgr.GetETWMgr()->ELToWP(pbyData, nLowestFloor, it->second._Info._byFloor, &it->second._Info, it->second._bArrived);

		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_WP, "EL 정보 파싱 완료...");
		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_WP, "");

		int nRet;
		
		// 연결되고 5분 후 자동으로 연결 종료
		if(g_sToolMgr.CheckTime(it->second._nTime, 60 * 5)) 
		{
			it->second._bConnected = false;

			sprintf(buff, "SOCKET : [%d] - 5분 경과 - EL [%c%c]호기 [%s]층 - WP (%c%c%c%c동 %c%c층 %c%c호 라인) 접속 종료... ", 
																		it->second._pSock->m_hSocket,
																		byELIndex[0], byELIndex[1], pszRealFloor,
																		it->second._ID._byAptIndex[0], 
																		it->second._ID._byAptIndex[1], 
																		it->second._ID._byAptIndex[2], 
																		it->second._ID._byAptIndex[3],
																		it->second._Info._byFloor[0],
																		it->second._Info._byFloor[1],
																		it->second._ID._byELLine[0],
																		it->second._ID._byELLine[1]);

			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, buff);
			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "");

			it->second._pSock->Close();
			SAFE_DELETE(it->second._pSock);
			m_mapWPInfo.erase(it);

			g_pMainDlg->DelWPListData(i);

			m_nWPSockCnt--;
			if(m_nWPSockCnt < 0) m_nWPSockCnt = 0;
			sprintf(buff, "%d", m_nWPSockCnt);

			g_pMainDlg->m_editWPCount.SetWindowText(buff);

			m_nWPDiscCnt++;

			return false;
		}

		if(it->second._Info._dwCommand == 0xA000)
		{
			nRet = it->second._pSock->Send(pbyTemp, g_sToolMgr.GetETWMgr()->m_nCnt);
		}
		else if(it->second._Info._dwCommand == 0xA001)
		{
			char szDir[16];

			if(it->second._Info._byCall == 0x31)
			{
				sprintf(szDir, "%s", "UP");
			}
			else if(it->second._Info._byCall == 0x32)
			{
				sprintf(szDir, "%s", "DOWN");
			}
			else sprintf(szDir, "%s", "NONE");

			// Command 가 0xA001 일 경우 엘리베이터 콜 호출이므로 
			// 데이터 분석 후 해당 WP 로 데이터 전송 후 바로 접속 종료
			sprintf(buff, "SOCKET : [%d] - WP (%s 콜 등록 소켓 - %c%c%c%c동 %c%c층) 접속 해제", it->second._pSock->m_hSocket,
																		szDir, it->second._Info._byAptIndex[0], 
																		it->second._Info._byAptIndex[1], 
																		it->second._Info._byAptIndex[2], 
																		it->second._Info._byAptIndex[3],
																		it->second._Info._byFloor[0],
																		it->second._Info._byFloor[1]);

			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, buff);
			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "");

			it->second._pSock->Close();
			SAFE_DELETE(it->second._pSock);
			m_mapWPInfo.erase(it);

			return false;
		}
		else if(it->second._Info._dwCommand == 0xA002)
		{
			sprintf(buff, "SOCKET : [%d] - WP (월패드 화면 창 닫음 - %c%c%c%c동 %c%c층) 접속 해제", it->second._pSock->m_hSocket,
																		it->second._Info._byAptIndex[0], 
																		it->second._Info._byAptIndex[1], 
																		it->second._Info._byAptIndex[2], 
																		it->second._Info._byAptIndex[3],
																		it->second._Info._byFloor[0],
																		it->second._Info._byFloor[1]);

			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, buff);
			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "");

			it->second._pSock->Close();
			SAFE_DELETE(it->second._pSock);
			m_mapWPInfo.erase(it);

			return false;
		}

		if(it->second._Info._dwCommand == 0xA000)
		//if(pbyTemp[53] == 0x00)
		{
			// 원하는 층에 도착했었다면 파싱도 필요없고 그냥 다음 WP 로 넘어간다
			//if(it->second._bArrived) break;
			
			// 엘리베이터가 정지하였을 때나 세대 층의 호출 방향과 같으면 현재 층을 비교하여 도착 여부를 확인
			/*if(byELDir == 0x30 || byELDir == it->second._Info._byCall)
			{
				// 원하는 층에 도착하였을 때
				if(atoi(pszRealFloor) == it->second._Info._nFloor)
				{
					if(!it->second._bArrived)
					{
						sprintf(buff, "SOCKET : [%d] - EL [%c%c]호기 [%s]층 - WP (%c%c%c%c동 %c%c층 %c%c호 라인) 도착 완료", 
																					it->second._pSock->m_hSocket,
																					byELIndex[0], byELIndex[1], pszRealFloor,
																					it->second._ID._byAptIndex[0], 
																					it->second._ID._byAptIndex[1], 
																					it->second._ID._byAptIndex[2], 
																					it->second._ID._byAptIndex[3],
																					it->second._Info._byFloor[0],
																					it->second._Info._byFloor[1],
																					it->second._ID._byELLine[0],
																					it->second._ID._byELLine[1]);

						g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, buff);
						g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "");

						it->second._bArrived = true;

						m_nELArriveCnt++;
					}
				}
			}*/

			int nIndex = g_pMainDlg->GetWPListIndex(it->second._szAptIndex, 
													it->second._Info._byWPIndex,
													it->second._Info._byFloor);

			// 도착했다면
			if(it->second._bArrived)
			{
				sprintf(buff, "SOCKET : [%d] - EL [%c%c]호기 [%s]층 - WP (%c%c%c%c동 %c%c층 %c%c호 라인) 도착 완료로 소켓 삭제...", 
																			it->second._pSock->m_hSocket,
																			byELIndex[0], byELIndex[1], pszRealFloor,
																			it->second._ID._byAptIndex[0], 
																			it->second._ID._byAptIndex[1], 
																			it->second._ID._byAptIndex[2], 
																			it->second._ID._byAptIndex[3],
																			it->second._Info._byFloor[0],
																			it->second._Info._byFloor[1],
																			it->second._ID._byELLine[0],
																			it->second._ID._byELLine[1]);

				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, buff);

				it->second._pSock->Close();
				SAFE_DELETE(it->second._pSock);
				m_mapWPInfo.erase(it);

				g_pMainDlg->DelWPListData(nIndex);

				m_nWPSockCnt--;
				if(m_nWPSockCnt < 0) m_nWPSockCnt = 0;
				sprintf(buff, "%d", m_nWPSockCnt);
				g_pMainDlg->m_editWPCount.SetWindowText(buff);

				return false;
			}

			// WP 접속이 끊어 졌을 경우
			if(nRet <= SOCKET_ERROR)
			{
				if(nRet == WSAENETDOWN)
				{
					sprintf(buff, "SOCKET : [%d] - 서버 소켓과 연결 실패(SEND)", it->second._pSock->m_hSocket);
					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, buff);
					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "");
				}

				it->second._nSendFailCnt++;

				sprintf(buff, "SOCKET : [%d] - WP (%c%c%c%c동 %c%c층 %c%c호 라인) Send %d 번째 실패...", 
																			it->second._pSock->m_hSocket,
																			it->second._ID._byAptIndex[0], 
																			it->second._ID._byAptIndex[1], 
																			it->second._ID._byAptIndex[2], 
																			it->second._ID._byAptIndex[3],
																			it->second._Info._byFloor[0],
																			it->second._Info._byFloor[1],
																			it->second._ID._byELLine[0],
																			it->second._ID._byELLine[1],
																			it->second._nSendFailCnt);

				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, buff);
				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "");

				if(it->second._nSendFailCnt > 9) 
				{
					//if(it->second._bArrived) continue;

					m_nWPDiscCnt++;

					sprintf(buff, "SOCKET : [%d] - EL [%c%c]호기 [%s]층 - WP (%c%c%c%c동 %c%c층 %c%c호 라인) 접속 종료...", 
																				it->second._pSock->m_hSocket,
																				byELIndex[0], byELIndex[1], pszRealFloor,
																				it->second._ID._byAptIndex[0], 
																				it->second._ID._byAptIndex[1], 
																				it->second._ID._byAptIndex[2], 
																				it->second._ID._byAptIndex[3],
																				it->second._Info._byFloor[0],
																				it->second._Info._byFloor[1],
																				it->second._ID._byELLine[0],
																				it->second._ID._byELLine[1]);

					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, buff);

					it->second._pSock->Close();
					SAFE_DELETE(it->second._pSock);
					m_mapWPInfo.erase(it);

					g_pMainDlg->DelWPListData(nIndex);

					m_nWPSockCnt--;
					if(m_nWPSockCnt < 0) m_nWPSockCnt = 0;
					sprintf(buff, "%d", m_nWPSockCnt);
					g_pMainDlg->m_editWPCount.SetWindowText(buff);

					return false;
				}
			}
			else if(!it->second._bArrived)
			{
				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_WP, "파싱된 EL 정보 송신...");

				sprintf(buff, "SOCKET : [%d] - EL [%c%c]호기 [%s]층 - WP (%c%c%c%c동 %c%c층 %c%c호 라인) 로 데이터 송신 :", it->second._pSock->m_hSocket,
																				byELIndex[0], byELIndex[1], pszRealFloor,
																				it->second._Info._byAptIndex[0], 
																				it->second._Info._byAptIndex[1], 
																				it->second._Info._byAptIndex[2], 
																				it->second._Info._byAptIndex[3],
																				it->second._Info._byFloor[0],
																				it->second._Info._byFloor[1],
																				it->second._ID._byELLine[0],
																				it->second._ID._byELLine[1]);

				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_WP, buff);

				sprintf(buff, "%s", ByteToText(pbyTemp, SEND_WP_SIZE));
				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_WP, buff);

				sprintf(buff, "UP CALL : %s", ByteToText(&pbyData[EW_UPCALL_PTR], 16));
				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_WP, buff);

				sprintf(buff, "DOWN CALL : %s", ByteToText(&pbyData[EW_DOWNCALL_PTR], 16));
				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_WP, buff);

				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_WP, "");
			}
		}
	}

	return true;
}

void CWinSockMgr::SendToEL(BYTE* pbyData, BYTE* pbyELIndex, PWPRECVINFO pWPRecvInfo, bool bHome)
{
	//if(!g_sToolMgr.GetToolFrameMgr()->GetRun()) return;

	char buff[16];
	ELINFO_MAP_IT it = m_mapELInfo.begin();

	for(int i = 0; it != m_mapELInfo.end(); i++, it++)
	{
		// 같은 호기인지 체크
		sprintf(buff, "%c%c", pbyELIndex[0], pbyELIndex[1]);
		if(atoi(buff) != i + 1) continue;

		/*if(it->second._ID._byELIndex[0] != pbyELIndex[0] ||
		   it->second._ID._byELIndex[1] != pbyELIndex[1])
		{
			char buff[128];
			sprintf(buff, "%d호기 EL을 찾을 수 없음.........", i);
			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, buff);
			continue;
		}*/

		//ELID ID(pbyData);
		//if(it->second._ID != ID) continue;

		BYTE* pData;

		if(bHome)
			pData = g_sToolMgr.GetWTEMgr()->WPToEL(pbyData, it->second._nLowestFloor, &it->second._ELSendInfo, pWPRecvInfo);
		else
			pData = g_sToolMgr.GetWTEMgr()->WPToEL(pbyData, it->second._nLowestFloor, &it->second._ELSendInfo, pWPRecvInfo, false);

		//if(pData == NULL) continue;

		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_EL, "WP 정보 파싱 완료...");

		//DelELInfo(ID);

		char buff[MAX_STRING_SIZE];

		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_EL, "파싱된 WP 정보 송신...");

		sprintf(buff, "EL [%s]층 - EL (%c%c%c%c동 %c%c호기) 로 데이터 송신 \r\n :", it->second._Info._szRealFloor, 
																it->second._Info._byAptIndex[0],
																it->second._Info._byAptIndex[1],
																it->second._Info._byAptIndex[2],
																it->second._Info._byAptIndex[3],
																it->second._Info._byELIndex[0],
																it->second._Info._byELIndex[1]);

		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_EL, buff);

		sprintf(buff, "%s", ByteToText(pData, ETS_DATA_SIZE));
		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_EL, buff);

		char szCall[64];

		strcpy(szCall, "");
		if(CheckFrame(it->second._ELSendInfo._byUpCall)) strcpy(szCall, "[---------- UP 콜 최초 등록 ----------]");

		sprintf(buff, "UP CALL : %s %s", ByteToText(it->second._ELSendInfo._byUpCall, 16), szCall);
		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_EL, buff);

		strcpy(szCall, "");
		if(CheckFrame(it->second._ELSendInfo._byDownCall)) strcpy(szCall, "[---------- DOWN 콜 최초 등록 ----------]");

		sprintf(buff, "DOWN CALL : %s %s", ByteToText(it->second._ELSendInfo._byDownCall, 16), szCall);
		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_EL, buff);

		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_EL, "");

		//return;
	}
}

void CWinSockMgr::SendDefaultELInfo()
{
	//if(!g_sToolMgr.GetToolFrameMgr()->GetRun()) return;

	int nCnt = 0;
	int nTempCnt = 0;
	BYTE bySend[ETS_DATA_SIZE];

	memset(bySend, 0, sizeof(bySend));

	ELINFO_MAP_IT it = m_mapELInfo.begin();

	bySend[nCnt++] = 'S';
	bySend[nCnt++] = 'T';
	bySend[nCnt++] = 'X';

	for(int i = 0; it != m_mapELInfo.end(); i++, it++)
	{
		// EL 소켓이 끊어 졌을 경우 통신 이상으로 설정
		if(!m_bELConnect)
		{
			memcpy(it->second._Info._byELState, "", 2);
			it->second.SetText();

			m_nSelectIndex = -1;
			g_sToolMgr.UpdateELList(i, &it->second, m_nSelectIndex);

			continue;
		}

		// 여러 호기가 가능하도록 수정 테스트 요망

		/*nTempCnt = 0;
		BYTE Temp[ETS_DATA_SIZE];
		memset(Temp, 0, sizeof(Temp));

		PELSENDINFO pELSendInfo = &it->second._ELSendInfo;

		BYTE by10Num = (it->second._ID._byELIndex[0] - '0') * 10;
		BYTE byNum = it->second._ID._byELIndex[1] - '0';

		BYTE byELIndex = by10Num + byNum;

		bySend[nCnt++] = byELIndex + 0x30; 
		Temp[nTempCnt++] = bySend[nCnt-1];*/

		nTempCnt = 0;
		BYTE Temp[ETS_DATA_SIZE];
		memset(Temp, 0, sizeof(Temp));

		PELSENDINFO pELSendInfo = &it->second._ELSendInfo;

		bySend[nCnt++] = i + 0x31; 
		Temp[nTempCnt++] = bySend[nCnt-1];

		for(int i = 0; i < 16; i++)
		{
			bySend[nCnt++] = pELSendInfo->_byUpCall[i];
			Temp[nTempCnt++] = bySend[nCnt-1];
		}

		for(int i = 0; i < 16; i++)
		{
			bySend[nCnt++] = pELSendInfo->_byDownCall[i];
			Temp[nTempCnt++] = bySend[nCnt-1];
		}

		for(int i = 0; i < 6; i++)
		{
			bySend[nCnt++] = 0x30;
			Temp[nTempCnt++] = bySend[nCnt-1];
		}

		char buff[MAX_STRING_SIZE];

		sprintf(buff, "현재 [%s]층 - %s", it->second._Info._szRealFloor, ByteToText(Temp, nTempCnt));
		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_EL, buff);

		sprintf(buff, "UP CALL : %s", ByteToText(it->second._ELSendInfo._byUpCall, 16));
		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_EL, buff);

		sprintf(buff, "DOWN CALL : %s", ByteToText(it->second._ELSendInfo._byDownCall, 16));
		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_EL, buff);

		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_EL, "");

		memset(pELSendInfo->_byUpCall, 0x30, sizeof(pELSendInfo->_byUpCall));
		memset(pELSendInfo->_byDownCall, 0x30, sizeof(pELSendInfo->_byDownCall));

		sprintf(buff, "EL (%c%c%c%c동 %c%c호기) 기본 EL SEND 정보 데이터 생성 완료...", it->second._ID._byAptIndex[0],
																						it->second._ID._byAptIndex[1],
																						it->second._ID._byAptIndex[2],
																						it->second._ID._byAptIndex[3],
																						it->second._ID._byELIndex[0],
																						it->second._ID._byELIndex[1]);

		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_SEND_EL, buff);

		/*sprintf(buff, "EL (%d%d%d%d동 %d%d호기) 로 데이터 송신 : %s", it->second._ID._byAptIndex[0] - '0',
																it->second._ID._byAptIndex[1] - '0',
																it->second._ID._byAptIndex[2] - '0',
																it->second._ID._byAptIndex[3] - '0',
																it->second._ID._byELIndex[0] - '0',
																it->second._ID._byELIndex[1] - '0',
																ByteToText(Temp, nTempCnt));*/
	}

	bySend[nCnt++] = 'E';
	bySend[nCnt++] = 'T'; 
	bySend[nCnt++] = 'X';

	bySend[nCnt] = NULL;

	//if(nCnt < 7) return;

	// 모든 EL에 대한 Send 정보를 송신
	if(m_pELSocket->Send(bySend, nCnt) <= SOCKET_ERROR)
	{
		if(m_bELConnect)
		{
			CString str;
			str.Format("HomeLink - EL 서버(%s : %s) 연결 끊어짐...", g_sToolMgr.GetToolConfig()->_strELIP, g_sToolMgr.GetToolConfig()->_strELPort);
			AfxGetApp()->m_pMainWnd->SetWindowText(str);

			m_bELConnect = false;	
			m_pELSocket->Close();
		}
	}
}

void CWinSockMgr::SendELCallReq(PWPINFO pWPInfo)
{
	//BYTE bySend[1024];
	memset(pWPInfo->_bySend, 0, sizeof(pWPInfo->_bySend));

	int nCnt = 0;

	// Tag
	pWPInfo->_bySend[nCnt++] = 'S';
	pWPInfo->_bySend[nCnt++] = 'H';
	pWPInfo->_bySend[nCnt++] = 'V';
	pWPInfo->_bySend[nCnt++] = 0x00;

	// Ver
	pWPInfo->_bySend[nCnt++] = '3';
	pWPInfo->_bySend[nCnt++] = '.';
	pWPInfo->_bySend[nCnt++] = '0';
	pWPInfo->_bySend[nCnt++] = 0x00;

	for(int i = 0 ; i < 17; i++)
	{
		// Source addr
		pWPInfo->_bySend[nCnt++] = pWPInfo->_Info._byServerID[i];//m_byServerID[i];
	}

	for(int i = 0 ; i < 17; i++)
	{
		// Destination addr
		pWPInfo->_bySend[nCnt++] = pWPInfo->_Info._byClientID[i];
	}

	// Time stamp
	time_t t = time(NULL);
	struct tm *p = localtime(&t);

	LONGLONG d = (LONGLONG) t;
	d *= 1000;

	pWPInfo->_bySend[nCnt++] = (BYTE) (d >> 56);
	pWPInfo->_bySend[nCnt++] = (BYTE) (d >> 48);
	pWPInfo->_bySend[nCnt++] = (BYTE) (d >> 40);
	pWPInfo->_bySend[nCnt++] = (BYTE) (d >> 32);
	pWPInfo->_bySend[nCnt++] = (BYTE) (d >> 24);
	pWPInfo->_bySend[nCnt++] = (BYTE) (d >> 16);
	pWPInfo->_bySend[nCnt++] = (BYTE) (d >> 8);
	pWPInfo->_bySend[nCnt++] = (BYTE) d;

	// Command
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0xA0;
	pWPInfo->_bySend[nCnt++] = 0x01;

	// Data length
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x17;

	// Status - Field name
	pWPInfo->_bySend[nCnt++] = 'R';
	pWPInfo->_bySend[nCnt++] = 'E';
	pWPInfo->_bySend[nCnt++] = 'T';
	pWPInfo->_bySend[nCnt++] = 'U';
	pWPInfo->_bySend[nCnt++] = 'R';
	pWPInfo->_bySend[nCnt++] = 'N';
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;

	// Status - Field type
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x00;
	pWPInfo->_bySend[nCnt++] = 0x06;

	// Status - Field value
	if((pWPInfo->_Info._byELState[0] == '0') && (pWPInfo->_Info._byELState[1] == '0'))
	{
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x03;
	}
	else if((pWPInfo->_Info._byELState[0] == '0') && (pWPInfo->_Info._byELState[1] == '1'))
	{
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
	}
	else if((pWPInfo->_Info._byELState[0] == '0') && (pWPInfo->_Info._byELState[1] == '2'))
	{
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x01;
	}
	else if((pWPInfo->_Info._byELState[0] == '0') && (pWPInfo->_Info._byELState[1] == '3'))
	{
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x02;
	}
	else if((pWPInfo->_Info._byELState[0] == '0') && (pWPInfo->_Info._byELState[1] == '4'))
	{
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x02;
	}
	else if((pWPInfo->_Info._byELState[0] == '0') && (pWPInfo->_Info._byELState[1] == '5'))
	{
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x01;
	}
	else if((pWPInfo->_Info._byELState[0] == '0') && (pWPInfo->_Info._byELState[1] == '6'))
	{
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x02;
	}
	else if((pWPInfo->_Info._byELState[0] == '0') && (pWPInfo->_Info._byELState[1] == '7'))
	{
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
	}
	else
	{
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
		pWPInfo->_bySend[nCnt++] = 0x00;
	}

	pWPInfo->_pSock->Send(pWPInfo->_bySend, nCnt);
}

void CWinSockMgr::WPRecvLog(BYTE* pbyAptIndex, BYTE* pbyFloor, BYTE* pbyELLine, BYTE* pbyData)
{
	char buff[1024];
	BYTE byTemp[1024];

	memset(buff, 0, 1024);
	sprintf(buff, "[RECV 데이터] - %c%c%c%c동 %c%c층 %c%c호", 
															pbyAptIndex[0], pbyAptIndex[1], pbyAptIndex[2], pbyAptIndex[3],
															pbyFloor[0], pbyFloor[1], pbyELLine[0], pbyELLine[1]);
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	// Tag + Ver
	memset(byTemp, 0, sizeof(byTemp));

	for(int i = 0; i < 7; i++)
	{
		byTemp[i] = pbyData[i];
	}

	memset(buff, 0, 1024);
	sprintf(buff, "Tag + Ver : %s", ByteToHex(byTemp, 7));
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	// Source Addr
	memset(byTemp, 0, sizeof(byTemp));

	for(int i = 0; i < 17; i++)
	{
		byTemp[i] = pbyData[i+8];
	}

	memset(buff, 0, 1024);
	sprintf(buff, "Source Address : %s", ByteToHex(byTemp, 17));
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	// Destination Addr
	memset(byTemp, 0, sizeof(byTemp));

	for(int i = 0; i < 17; i++)
	{
		byTemp[i] = pbyData[i+25];
	}

	memset(buff, 0, 1024);
	sprintf(buff, "Destination Address : %s", ByteToHex(byTemp, 17));
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	// Time Stamp
	memset(byTemp, 0, sizeof(byTemp));

	for(int i = 0; i < 8; i++)
	{
		byTemp[i] = pbyData[i+42];
	}

	memset(buff, 0, 1024);
	sprintf(buff, "Time Stamp : %s", ByteToHex(byTemp, 8));
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	// Command
	memset(byTemp, 0, sizeof(byTemp));

	for(int i = 0; i < 4; i++)
	{
		byTemp[i] = pbyData[i+50];
	}

	memset(buff, 0, 1024);
	sprintf(buff, "Command : %s", ByteToHex(byTemp, 4));
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	// Data Length
	memset(byTemp, 0, sizeof(byTemp));

	for(int i = 0; i < 4; i++)
	{
		byTemp[i] = pbyData[i+54];
	}

	memset(buff, 0, 1024);
	sprintf(buff, "Data Length : %s", ByteToHex(byTemp, 4));
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	// Direction - Field Name
	memset(byTemp, 0, sizeof(byTemp));

	for(int i = 0; i < 15; i++)
	{
		byTemp[i] = pbyData[i+58];
	}

	memset(buff, 0, 1024);
	sprintf(buff, "Direction Field Name : %s", ByteToHex(byTemp, 15));
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	// Direction - Field Type
	memset(byTemp, 0, sizeof(byTemp));

	for(int i = 0; i < 4; i++)
	{
		byTemp[i] = pbyData[i+73];
	}

	memset(buff, 0, 1024);
	sprintf(buff, "Direction Field Type : %s", ByteToHex(byTemp, 4));
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	// Direction - Field Value
	memset(byTemp, 0, sizeof(byTemp));

	for(int i = 0; i < 1; i++)
	{
		byTemp[i] = pbyData[i+77];
	}

	memset(buff, 0, 1024);
	sprintf(buff, "Direction Field Value : %s", ByteToHex(byTemp, 1));
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	// Floor - Field Name
	memset(byTemp, 0, sizeof(byTemp));

	for(int i = 0; i < 15; i++)
	{
		byTemp[i] = pbyData[i+78];
	}

	memset(buff, 0, 1024);
	sprintf(buff, "Floor Field Name : %s", ByteToHex(byTemp, 15));
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	// Floor - Field Type
	memset(byTemp, 0, sizeof(byTemp));

	for(int i = 0; i < 4; i++)
	{
		byTemp[i] = pbyData[i+93];
	}

	memset(buff, 0, 1024);
	sprintf(buff, "Floor Field Type : %s", ByteToHex(byTemp, 4));
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	// Floor - Field Value
	memset(byTemp, 0, sizeof(byTemp));

	for(int i = 0; i < 1; i++)
	{
		byTemp[i] = pbyData[i+97];
	}

	memset(buff, 0, 1024);
	sprintf(buff, "Floor Field Value : %s", ByteToHex(byTemp, 1));
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, buff);

	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP_DATA, "");
}

bool CWinSockMgr::HasSameWP(BYTE* pbyAptIndex, BYTE* pbyFloor, BYTE* pbyELLine)
{
	WPINFO_MAP_IT it = m_mapWPInfo.begin();

	for( ; it != m_mapWPInfo.end(); it++)
	{
		if(it->second._Info._byAptIndex[0] == pbyAptIndex[0] &&
		   it->second._Info._byAptIndex[1] == pbyAptIndex[1] &&
		   it->second._Info._byAptIndex[2] == pbyAptIndex[2] &&
		   it->second._Info._byAptIndex[3] == pbyAptIndex[3])
		{
			if(it->second._Info._byFloor[0] == pbyFloor[0] &&
			   it->second._Info._byFloor[1] == pbyFloor[1])
			{
				if(it->second._Info._byAptIndex[0] == pbyELLine[0] &&
				   it->second._Info._byAptIndex[1] == pbyELLine[1])
				{
					return true;
				}
			}
		}
	}

	return false;
}

bool CWinSockMgr::HasSameIP(CClientSock* pClient)
{
	CString strIP, strIP2;
	int nPort, nPort2;

	WPINFO_MAP_IT it = m_mapWPInfo.begin();

	for( ; it != m_mapWPInfo.end(); it++)
	{
		it->second._pSock->GetPeerName(strIP, (UINT &) nPort);
		pClient->GetPeerName(strIP2, (UINT &) nPort2);

		if(strIP == strIP2) return true;
	}

	return false;
}

void CWinSockMgr::OnReceive(SOCKET Socket, int nTag)
{
	char buff[256];

	// EL로부터 받았을 경우
	if(nTag == SOKECK_TYPE_EL)
	{
		OnReceiveFromEL(Socket);
	}
	else if(nTag == -1)
	{
		sprintf(buff, "SOCKET : [%d] - 서버 소켓과 연결 실패(ACCEPT)", Socket);
		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, buff);
		g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "");
	}
	// 월패드로부터 받았을 경우
	else //if(nTag == SOKECK_TYPE_WP)
	{
		OnReceiveFromHome(Socket);
	}

	m_nWPSockCnt = (int) m_mapWPInfo.size();
	sprintf(buff, "%d", m_nWPSockCnt);
	g_pMainDlg->m_editWPCount.SetWindowText(buff);
}

bool CWinSockMgr::OnReceiveFromHome(SOCKET Socket)
{
	//if(!g_sToolMgr.GetToolFrameMgr()->GetRun()) return false;

	int nCnt = 0;
	BYTE byData[WTS_DATA_SIZE];

	WPINFO_MAP_IT it = m_mapWPInfo.begin();
  
	for(int i = 0; it != m_mapWPInfo.end(); i++, it++)
	{
		if(it->second._pSock->m_hSocket != Socket) continue;

		//memset(byData, 0, sizeof(byData));

		// 원하는 층에 도착했었다면 그냥 함수를 빠져나간다
		//if(it->second._bArrived) return false;

		// 월패드로부터 데이터 수신
		int nRet = it->second._pSock->Receive(byData, WTS_DATA_SIZE);

		if(nRet <= SOCKET_ERROR) 
		{
			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, "소켓 에러 발생!!!");
			return false;
		}

		if(byData[0] == 'S' && byData[1] == 'H' && byData[2] == 'V') 
		{
			char buff[MAX_STRING_SIZE];
			static char szDir[16];
			int nELCnt = 0;
			int nMinFloorDiff = 100;

			BYTE* pbyELIndex = NULL;

			// 최대 64개까지 군관리 가능
			ELINDEX ELIndex[64];

			// ID(동, 호기) 정보 설정
			it->second._ID.SetID(byData);

			char* pszIOIDSyn = g_sToolMgr.GetIOConfig()->GetIOIDSynChar();
			BYTE* pbyELFloor = g_sToolMgr.GetIOConfig()->GetFloor(it->second._ID._byAptIndex, it->second._ID._byELLine);

			// 기본 RECV 정보 설정
			it->second._Info.SetInfo(byData, pszIOIDSyn, pbyELFloor, it->second._ID._byAptIndex, it->second._ID._byELLine);

			// 리스트에 설정될 텍스트 설정
			it->second.SetText(byData, it->second._Info._byClass, pbyELFloor);

			// 받은 WP RECV 원래의 데이터를 그대로 출력
			WPRecvLog(it->second._Info._byAptIndex, it->second._Info._byFloor, it->second._Info._byWPIndex, byData);

			// 출통기일 경우
			if(it->second._Info._byClass == 1 ||
			   it->second._Info._byClass == 0x31)
			{
				sprintf(buff, "SOCKET : [%d] - 출통기 (%c%c%c%c동 [%c%c %c%c]) 로부터 데이터 수신 :", 
																				it->second._pSock->m_hSocket,
																				it->second._Info._byAptIndex[0], 
																				it->second._Info._byAptIndex[1], 
																				it->second._Info._byAptIndex[2], 
																				it->second._Info._byAptIndex[3],
																				it->second._Info._byFloor[0],
																				it->second._Info._byFloor[1],
																				it->second._Info._byWPIndex[0],
																				it->second._Info._byWPIndex[1]);
				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

				if(pbyELFloor == NULL) 
				{
					sprintf(buff, "SOCKET : [%d] - 출통기 (%c%c%c%c동 [%c%c %c%c]) 설정 층 이상으로 자동 삭제...", 
																					it->second._pSock->m_hSocket,
																					it->second._Info._byAptIndex[0], 
																					it->second._Info._byAptIndex[1], 
																					it->second._Info._byAptIndex[2], 
																					it->second._Info._byAptIndex[3],
																					it->second._Info._byFloor[0],
																					it->second._Info._byFloor[1],
																					it->second._Info._byWPIndex[0],
																					it->second._Info._byWPIndex[1]);
					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

					it->second._pSock->Close();
					SAFE_DELETE(it->second._pSock);
					m_mapWPInfo.erase(it);

					return false;
				}
			}

 			// 출통기일 경우
			if(it->second._Info._byClass == 1 ||
			   it->second._Info._byClass == 0x31)
			{
				// 해당하는 EL 이 존재하는지 체크(군관리 적용)
				IOCONFIG_VEC_IT it2 = g_sToolMgr.GetIOConfig()->GetIOConfig()->begin();

				// 일반 군관리
				if(g_sToolMgr.GetIOGroup())
				{
					for( ; it2 != g_sToolMgr.GetIOConfig()->GetIOConfig()->end(); it2++)
					{
						if(it2->_byAptIndex[0] == it->second._ID._byAptIndex[0] &&
							it2->_byAptIndex[1] == it->second._ID._byAptIndex[1] &&
							it2->_byAptIndex[2] == it->second._ID._byAptIndex[2] &&
							it2->_byAptIndex[3] == it->second._ID._byAptIndex[3])
						{
							if(it2->_byIOID[0] == it->second._ID._byELLine[0] &&
							it2->_byIOID[1] == it->second._ID._byELLine[1])
							{
								pbyELIndex = it2->_byELIndex;
								ELIndex[nELCnt++]._pbyELIndex = it2->_byELIndex;
							}
						}
					}
				}
				// 지능형 군관리(한 개의 가까운 엘리베이터만 선택됨)
				else
				{
					for( ; it2 != g_sToolMgr.GetIOConfig()->GetIOConfig()->end(); it2++)
					{
						// 엘리베이터의 상태가 정상 운행이 아닐 경우는 그냥 넘어간다.
						if(GetELInfo(it2->_byELIndex) == NULL) continue;
						if(strcmp(GetELInfo(it2->_byELIndex)->_szELState, "NORMAL") != 0) continue;

						if(it2->_byAptIndex[0] == it->second._ID._byAptIndex[0] &&
							it2->_byAptIndex[1] == it->second._ID._byAptIndex[1] &&
							it2->_byAptIndex[2] == it->second._ID._byAptIndex[2] &&
							it2->_byAptIndex[3] == it->second._ID._byAptIndex[3])
						{
							if(it2->_byIOID[0] == it->second._ID._byELLine[0] &&
							it2->_byIOID[1] == it->second._ID._byELLine[1])
							{
								char szFloor[4];
								sprintf(szFloor, "%c%c", pbyELFloor[0], pbyELFloor[1]);

								if(GetELInfo(it2->_byELIndex) == NULL) continue;

								int nFloorDiff = abs((atoi(szFloor) - GetELInfo(it2->_byELIndex)->_nLowestFloor) - 
													 atoi(GetELInfo(it2->_byELIndex)->_szELFloor));

								if(nMinFloorDiff > nFloorDiff)
								{
									nMinFloorDiff = nFloorDiff;
									pbyELIndex = it2->_byELIndex;
								}
							}
						}
					}
				}

				// 출통기일 경우 층 정보가 맞지 않게 오므로 미리 설정된 층으로 변경(IO Config)
				char szFloor[4];
				sprintf(szFloor, "%c%c", pbyELFloor[0], pbyELFloor[1]);

				int nFloor = atoi(szFloor);

				byData[100] = nFloor;

				if(nFloor < 0)
				{
					byData[21] = 'B';
					byData[22] = abs(nFloor) + '0';
				}
				else 
				{
					byData[21] = szFloor[0];
					byData[22] = szFloor[1];
				}
			}
			// 홈콜일 경우
			else
			{
				// 해당하는 EL 이 존재하는지 체크
				//pbyELIndex = g_sToolMgr.GetELConfig()->GetIndex(it->second._ID._byAptIndex, it->second._ID._byELLine);
				//if(pbyELIndex == NULL) continue;

				// 해당하는 EL 이 존재하는지 체크
				// 홈콜의 경우에는 출통기와 달리 무조건 한개의 가까운 엘리베이터만 선택됨
				// 때문에 지능형 군관리만 적용 가능(월패드 내에서 보이는 엘리베이터 층이 하나이므로)
				ELCONFIG_VEC_IT it2 = g_sToolMgr.GetELConfig()->GetELConfig()->begin();

				for( ; it2 != g_sToolMgr.GetELConfig()->GetELConfig()->end(); it2++)
				{
					// 엘리베이터의 상태가 정상 운행이 아닐 경우는 그냥 넘어간다.
					if(GetELInfo(it2->_byELIndex) == NULL) continue;
					if(strcmp(GetELInfo(it2->_byELIndex)->_szELState, "NORMAL") != 0) continue;

					if(it2->_byAptIndex[0] == it->second._ID._byAptIndex[0] &&
						it2->_byAptIndex[1] == it->second._ID._byAptIndex[1] &&
						it2->_byAptIndex[2] == it->second._ID._byAptIndex[2] &&
						it2->_byAptIndex[3] == it->second._ID._byAptIndex[3])
					{
						if(it2->_byELLine[0] == it->second._ID._byELLine[0] &&
							it2->_byELLine[1] == it->second._ID._byELLine[1])
						{
							if(GetELInfo(it2->_byELIndex) == NULL) continue;

							int nFloorDiff = abs((it->second._Info._nFloor - GetELInfo(it2->_byELIndex)->_nLowestFloor) - 
											atoi(GetELInfo(it2->_byELIndex)->_szELFloor));

							if(nMinFloorDiff > nFloorDiff)
							{
								nMinFloorDiff = nFloorDiff;

								pbyELIndex = it2->_byELIndex;

								it->second._Info._bySelectELIndex[0] = it2->_byELIndex[0];
								it->second._Info._bySelectELIndex[1] = it2->_byELIndex[1];
							}
						}
					}
				}
			}

			if(pbyELIndex == NULL) 
			{
				sprintf(buff, "SOCKET : [%d] - (%c%c%c%c동 [%c%c %c%c]) 'pbyELIndex = NULL'...", 
																it->second._pSock->m_hSocket,
																it->second._Info._byAptIndex[0], 
																it->second._Info._byAptIndex[1], 
																it->second._Info._byAptIndex[2], 
																it->second._Info._byAptIndex[3],
																it->second._Info._byFloor[0],
																it->second._Info._byFloor[1],
																it->second._Info._byWPIndex[0],
																it->second._Info._byWPIndex[1]);
				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

				it->second._pSock->Close();
				SAFE_DELETE(it->second._pSock);
				m_mapWPInfo.erase(it);

				//continue;

				return false;
			}

			char szELIndex[4];
			sprintf(szELIndex, "%c%c", pbyELIndex[0], pbyELIndex[1]);
			m_nSelectIndex = atoi(szELIndex) - 1;

			// 홈콜일 경우
			if(it->second._Info._byClass == 0x30)
			{
				// 맞는 EL 인덱스가 존재시 데이터 파싱 후 정보 전달
				SendToEL(byData, pbyELIndex, &it->second._Info);
			}
			// 출통기일 경우(군관리 적용)
			else
			{
				// 무조건 군관리 적용되는 EL 모두 이동
				if(g_sToolMgr.GetIOGroup())
				{
					// 맞는 EL 인덱스가 존재시 데이터 파싱 후 정보 전달
					for(int i = 0; i < nELCnt; i++)
					{
						SendToEL(byData, ELIndex[i]._pbyELIndex, &it->second._Info, false);
					}
				}
				// 가까운 층의 EL만 이동
				else
				{
					// 맞는 EL 인덱스가 존재시 데이터 파싱 후 정보 전달
					SendToEL(byData, pbyELIndex, &it->second._Info, false);
				}
			}

			if(it->second._Info._dwCommand) 
			{			
				sprintf(buff, "SOCKET : [%d] - EL [%c%c]호기 - WP (%c%c%c%c동 %c%c층 %c%c호) 로부터 데이터 수신 :", it->second._pSock->m_hSocket,
																				pbyELIndex[0], pbyELIndex[1],
																				it->second._Info._byAptIndex[0], 
																				it->second._Info._byAptIndex[1], 
																				it->second._Info._byAptIndex[2], 
																				it->second._Info._byAptIndex[3],
																				it->second._Info._byFloor[0],
																				it->second._Info._byFloor[1],
																				it->second._Info._byWPIndex[0],
																				it->second._Info._byWPIndex[1]);
				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

				sprintf(buff, "%s", ByteToText(byData, WTS_DATA_SIZE));
				g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

				// EL 상태 요청 커맨드일 경우
				if(it->second._Info._dwCommand == 0xA000)
				//if(byData[53] == 0x00)
				{
					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, "RECV TYPE : 상태정보 요청 커맨드");

					sprintf(buff, "RECV COMMAND : 0x%02X%02X - PARSING COMMAND : 0x%02X", byData[52], byData[53], it->second._Info._dwCommand);
					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

					sprintf(buff, "콜 : DEC - [%3d] HEX - [0x%02X] -------------------- %s -------------------- ", it->second._Info._byCall, it->second._Info._byCall, "NONE");
					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

					sprintf(buff, "DIRECTION : %02X - [%s]", byData[77], "NONE");
					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

					sprintf(buff, "FLOOR : %02d", byData[100]);
					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, "");

					/*char buff[16];

					m_nWPSockCnt++;
					sprintf(buff, "%d", m_nWPSockCnt);
					g_pMainDlg->m_editWPCount.SetWindowText(buff);*/
				}				
				// EL 콜 요청 커맨드일 경우
				else if(it->second._Info._dwCommand == 0xA001)
				//else if(byData[53] == 0x01)
				{
					if(it->second._Info._byClass == 0x30)
					{
						if(it->second._Info._byCall != 0x30)
							m_nELCallCnt++;
					}

					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, "RECV TYPE : 엘리베이터 콜 요청 커맨드");

					if(it->second._Info._byCall == 0x31)
					{
						sprintf(szDir, "%s", "UP");
					}
					else if(it->second._Info._byCall == 0x32)
					{
						sprintf(szDir, "%s", "DOWN");
					}
					else sprintf(szDir, "%s", "NONE");

					//if(strcmp(szDir, "NONE") != 0) i--;

					int nIndex;

					if(it->second._Info._byClass == 0x30)
					{
						nIndex = g_pMainDlg->GetWPListIndex(it->second._szAptIndex, 
															it->second._Info._byWPIndex,
															it->second._Info._byFloor);

						// 리스트의 크기가 일정수를 넘어서면 리스트 컨트롤에 데이터를 추가하지 않음
						//if(i < MAX_WP_LIST)
						//if(g_pMainDlg->m_listctrlWP.GetItemCount() < MAX_WP_LIST)
						{
							g_pMainDlg->SetWPListData(nIndex, pbyELIndex, it->second._szClass,
														it->second._szAptIndex,
														it->second._Info._byWPIndex,
														it->second._Info._byFloor,
														szDir);
						}
					}
					else
					{
						nIndex = g_pMainDlg->GetWPListIndex(it->second._szAptIndex, 
															it->second._Info._byWPIndex,
															pbyELFloor);
															//it->second._Info._byFloor);

						// 리스트의 크기가 일정수를 넘어서면 리스트 컨트롤에 데이터를 추가하지 않음
						//if(i < MAX_WP_LIST)
						//if(g_pMainDlg->m_listctrlWP.GetItemCount() < MAX_WP_LIST)
						{
							g_pMainDlg->SetWPListData(nIndex, pbyELIndex, it->second._szClass,
														it->second._szAptIndex,
														it->second._Info._byWPIndex,
														pbyELFloor,
														//it->second._Info._byFloor,
														szDir);
						}
					}

					//if(strcmp(szDir, "NONE") != 0) i++;

					sprintf(buff, "RECV COMMAND : 0x%02X%02X - PARSING COMMAND : 0x%02X", byData[52], byData[53], it->second._Info._dwCommand);
					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

					sprintf(buff, "콜 : DEC - [%3d] HEX - [0x%02X] -------------------- %s -------------------- ", it->second._Info._byCall, it->second._Info._byCall, szDir);
					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

					sprintf(buff, "DIRECTION : %02X - [%s]", byData[77], szDir);
					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

					sprintf(buff, "FLOOR : %02d", byData[100]);
					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, buff);

					g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_WP, "");

					// WP 로 EL 상태 정보 패킷 전송
					SendELCallReq(&it->second);
				}

				// 출통기일 경우는 EL 로 데이터를 전송 후 바로 삭제 함
				if(it->second._Info._byClass == 1 ||
				it->second._Info._byClass == 0x31)
				{
					if(it->second._Info._byCall != 0x30)
					{
						m_nIOCnt++;

						char buff[1024];

						sprintf(buff, "WP (출통기 - %c%c%c%c동 %c%c층) 접속 해제", it->second._Info._byAptIndex[0], 
																					it->second._Info._byAptIndex[1], 
																					it->second._Info._byAptIndex[2], 
																					it->second._Info._byAptIndex[3],
																					it->second._Info._byFloor[0],
																					it->second._Info._byFloor[1]);

						g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, buff);
						g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "");

						it->second._pSock->Close();
						SAFE_DELETE(it->second._pSock);
						m_mapWPInfo.erase(it);

						g_pMainDlg->DelWPListData(i);
					}

					return false;
				}

				return true;
			}
		}
	}

	return true;
}

bool CWinSockMgr::OnReceiveFromEL(SOCKET Socket)
{
	//if(!g_sToolMgr.GetToolFrameMgr()->GetRun()) return false;

	bool bCheck = false;
	BYTE byData[ETS_DATA_SIZE];

	int nSize = (int) m_mapELInfo.size();
	ELINFO_MAP_IT it = m_mapELInfo.begin();

	// EL로부터 정보 수신
	memset(byData, 0, sizeof(byData));
	m_pELSocket->Receive(byData, ETS_DATA_SIZE);

	for(int i = 0; it != m_mapELInfo.end(); i++, it++)
	{
		it->second.SetText();
		g_sToolMgr.UpdateELList(i, &it->second, m_nSelectIndex);

		//if(it->second.SetText()) g_sToolMgr.UpdateELList(i, &it->second);

		ELID ID;

		// EL ID로부터 인덱스 추출
		int nIndex = ID.GetIDIndex(byData, it->second._ID, nSize);		
		if(nIndex == -1) 
		{
			continue;
		}

		//it->second._Info.SetInfo(byData, it->second._nLowestFloor, nIndex);
		it->second._Info.SetInfo(byData, it->second._nLowestFloor, i);

		for(int j = 0; j < 4; j++)
		{
			it->second._Info._byAptIndex[j] = it->second._ID._byAptIndex[j];
		}

		for(int j = 0; j < 2; j++)
		{
			it->second._Info._byELIndex[j] = it->second._ID._byELIndex[j];
		}

		//if(it->second.SetText()) g_sToolMgr.UpdateELList(i, &it->second);

		BYTE byTemp[EL_INFO_SIZE+7];

		// 하나의 EL 데이터 추출
		//if(ExtractELInfoFromData(byTemp, byData, nIndex))
		if(ExtractELInfoFromData(byTemp, byData, i))
		{
			char buff[MAX_STRING_SIZE];

			sprintf(buff, "EL [%s]층 [%s] - (%c%c%c%c동 %c%c호기) 로부터 데이터 수신", 
																	it->second._Info._szRealFloor,
																	it->second._szELDir,
																	it->second._Info._byAptIndex[0],
																	it->second._Info._byAptIndex[1],
																	it->second._Info._byAptIndex[2],
																	it->second._Info._byAptIndex[3],
																	it->second._Info._byELIndex[0],
																	it->second._Info._byELIndex[1]);

			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_EL, buff);
			
			memset(buff, 0, MAX_STRING_SIZE);
			sprintf(buff, "%s", ByteToText(byTemp, EL_INFO_SIZE+7));//ByteToChar(byData, ETS_DATA_SIZE));

			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_EL, buff);

			sprintf(buff, "UP CALL : %s", ByteToText(&byTemp[EW_UPCALL_PTR], 16));
			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_EL, buff);

			sprintf(buff, "DOWN CALL : %s", ByteToText(&byTemp[EW_DOWNCALL_PTR], 16));
			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_EL, buff);

			g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_RECV_EL, "");

			// EL 정보를 파싱 후 맞는 세대로 전송
			bCheck = SendToHome(byTemp, it->second._ID._byAptIndex, it->second._nLowestFloor, it->second._Info._szRealFloor, it->second._Info._byDirection);
		}
	}

	return bCheck;

	return 1;
}

void CWinSockMgr::UpdateEL()
{
	/*ELINFO_MAP_IT it = m_mapELInfo.begin();

	for(int i = 0; it != m_mapELInfo.end(); i++, it++)
	{
		g_sToolMgr.UpdateELList(i, &it->second);
	}*/
}

void CWinSockMgr::OnAccept()
{
	//if(!g_sToolMgr.GetToolFrameMgr()->GetRun()) return;

	// 월패드 ID 구성
	WPID ID((BYTE *) "0101", 1);

	// 서버소켓으로부터 하나의 소켓 Accept
	CClientSock* pClientSock = new CClientSock;
	//m_mapServerSock[0]->Accept(*pClientSock);
	m_ServerSock.Accept(*pClientSock);

	//pClientSock->m_bConnect = true;

	// 태그를 월패드로 설정
	pClientSock->m_Tag = SOKECK_TYPE_WP;

	// 월패드 정보 설정
	WPINFO WPInfo(ID, pClientSock);
	WPInfo._bArrived = false;

	char* pszServerID = g_sToolMgr.GetToolConfig()->_strServerID.GetBuffer(0);
	
	for(int i = 0; i < 17; i++)
	{
		WPInfo._Info._byServerID[i] = pszServerID[i];
	}

	CString strIP;	
	int nPort;

	pClientSock->GetPeerName(strIP, (UINT &) nPort);

	CString str;
	str.Format("SOCKET : [%d] - WP (%s : %d) 연결", pClientSock->m_hSocket, strIP, nPort);

	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, str.GetBuffer(0));

	AddWPInfo(WPInfo);

	str.Format("SOCKET : [%d] - WP (%s : %d) 정보 생성 완료", pClientSock->m_hSocket, strIP, nPort);
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, str.GetBuffer(0));

	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "");

	m_nWPAcceptCnt++;
}

bool CWinSockMgr::OnConnect()
{
	//if(!g_sToolMgr.GetToolFrameMgr()->GetRun()) return false;

	if(m_bELConnect) return true;

	// EL 소켓 접속 시도
	m_pELSocket->Close();
	m_pELSocket->Create();
	m_pELSocket->Connect(g_sToolMgr.GetToolConfig()->_strELIP, atoi(g_sToolMgr.GetToolConfig()->_strELPort));

	CString str;
	str.Format("HomeLink - EL 서버(%s : %s) 연결 중...", g_sToolMgr.GetToolConfig()->_strELIP, g_sToolMgr.GetToolConfig()->_strELPort);
	AfxGetApp()->m_pMainWnd->SetWindowText(str);

	return false;
}

bool CWinSockMgr::OnConnect(SOCKET Socket)
{
	// EL 소켓 접속 성공시 
	m_bELConnect = true;

	CString str;
	str.Format("EL 서버(%s : %s) 연결 성공", g_sToolMgr.GetToolConfig()->_strELIP, g_sToolMgr.GetToolConfig()->_strELPort);
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, str.GetBuffer(0));

	str.Format("HomeLink - EL 서버(%s : %s) 연결 성공", g_sToolMgr.GetToolConfig()->_strELIP, g_sToolMgr.GetToolConfig()->_strELPort);
	AfxGetApp()->m_pMainWnd->SetWindowText(str);

	return false;
}

void CWinSockMgr::ClearServerSock()
{
	/*int nCnt = m_mapServerSock.size();

	if(nCnt > 0)
	{
		SERVERSOCK_MAP_IT it = m_mapServerSock.begin();

		for(int i = 0; i <  nCnt; i++, it++)
		{
			it->second->Close();
			SAFE_DELETE(it->second);
			//m_mapServerSock.erase(it);
		}

		m_mapServerSock.clear();
	}

	m_nServerSockCnt = 0;*/

	m_ServerSock.Close();

	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "서버 소켓 정보 초기화 성공...");
}

void CWinSockMgr::ClearWPInfo()
{
	int nCnt = (int) m_mapWPInfo.size();

	if(nCnt > 0)
	{
		WPINFO_MAP_IT it = m_mapWPInfo.begin();

		for(int i = 0; i <  nCnt; i++, it++)
		{
			it->second._pSock->Close();
			SAFE_DELETE(it->second._pSock);
			//m_mapWPInfo.erase(it);
		}

		m_mapWPInfo.clear();
	}

	m_nWPInfoCnt = 0;
	m_nWPSockCnt = 0;

	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "WP 정보 초기화 성공...");
}

void CWinSockMgr::ClearELInfo()
{
	int nCnt = (int) m_mapELInfo.size();

	if(nCnt > 0)
	{
		m_mapELInfo.clear();
	}

	m_nELInfoCnt = 0;

	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "EL 정보 초기화 성공...");

	m_pELSocket = new CClientSock;
	m_pELSocket->Close();
	m_pELSocket->Create();
	m_pELSocket->m_Tag = SOKECK_TYPE_EL;

	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "EL 접속 소켓 초기화 작업 성공...");
}

void CWinSockMgr::Clear()
{
	SAFE_DELETE(m_pELSocket);
	ClearServerSock();
	ClearWPInfo();
	ClearELInfo();

	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, "모든 정보 초기화 성공...");
}

void CWinSockMgr::OnCloseEL(SOCKET Socket)
{
	//m_bELConnect = false;

	CString str;
	str.Format("EL 서버(%s : %s) 로부터 연결 종료", g_sToolMgr.GetToolConfig()->_strELIP, g_sToolMgr.GetToolConfig()->_strELPort);
	g_sToolMgr.GetLogMgr()->AddLog(E_LOG_TYPE_CONN, str.GetBuffer(0));
}

bool CWinSockMgr::CheckFrame(BYTE* pbyFrame)
{
	//int nSize = sizeof(pbyFrame);
	
	for(int i = 0; i < 16; i++)
	{
		if(pbyFrame[i] != 48 || pbyFrame[i] != '0' || pbyFrame[i] != 0x30)
			return true;
	}

	return false;
}

void CWinSockMgr::OnCloseWP(SOCKET Socket)
{
	/*WPINFO_MAP_IT it = m_mapWPInfo.begin();

	for(int i = 0; it != m_mapWPInfo.end(); i++, it++)
	{
		if(it->second._Info._dwCommand == 0xA001)
		{
			if(Socket == it->second._pSock->m_hSocket)
			{
				it->second._pSock->Close();
				SAFE_DELETE(it->second._pSock);
				m_mapWPInfo.erase(it);

				return;
			}
		}
	}*/
}