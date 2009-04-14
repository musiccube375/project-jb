#pragma once

// CDataSocket 명령 대상입니다.

class CChatCDlg;
class CData;
class CDataSocket : public CSocket
{
public:
	CDataSocket();
	CDataSocket(CChatCDlg * dlg);
	virtual ~CDataSocket();

	void Init(CChatCDlg * dlg);
	void Send(CData * pData);
	void Receive(CData * pData);
	void operator <<(CData & data);
	void operator >>(CData & data);
	void Flush();
	CArchive *m_pArIn;
	CArchive *m_pArOut;
	virtual void OnReceive(int nErrorCode);
	virtual void OnClose(int nErrorCode);
private:
	CSocketFile *m_pFile;
	CChatCDlg *m_pDlg;
};


