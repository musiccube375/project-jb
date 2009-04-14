#pragma once

//#include "ChatSDlg.h"
//#define UM_DATARECEIVE (WM_USER+11)


// CDataSocket 명령 대상입니다.

class CChatSDlg;
class CData;
class CDataSocket : public CSocket
{
public:
	CDataSocket();
	CDataSocket(CChatSDlg * dlg);
	virtual ~CDataSocket();

	void Init(CChatSDlg * dlg);
	void Send(CData * pData);
	void Receive(CData * pData);
	void operator <<(CData & data);
	void operator >>(CData & data);
	void Flush();
	CArchive *m_pArIn;
	CArchive *m_pArOut;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	CString m_id;
	
private:
	CSocketFile *m_pFile;
	CChatSDlg *m_pDlg;
};