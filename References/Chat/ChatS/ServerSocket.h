#pragma once

//#define UM_ACCEPT (WM_USER+10)

// CServerSocket 명령 대상입니다.

class CChatSDlg;
class CServerSocket : public CSocket
{
public:
	CServerSocket();
	CServerSocket(CChatSDlg * dlg);
	virtual ~CServerSocket();
	virtual void OnAccept(int nErrorCode);
	void Init(CChatSDlg *dlg, int nPortNum);
private:
	CChatSDlg *m_pDlg;
};


