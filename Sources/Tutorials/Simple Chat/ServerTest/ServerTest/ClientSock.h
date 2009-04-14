#pragma once

class CClientSock : public CAsyncSocket
{
// Attributes
public:
	int		m_Tag;			// 소켓 정보를 위한 태그
	bool	m_bConnect;		// 접속 여부 확인

// Operations
public:
	CClientSock();
	virtual ~CClientSock();

// Overrides
public:
	// ClassWizard generated virtual function overrides
	//{{AFX_VIRTUAL(CClientSock)
	public:
	virtual void OnReceive(int nErrorCode);
	virtual void OnSend(int nErrorCode);
	virtual void OnConnect(int nErrorCode);
	virtual void OnClose(int nErrorCode);
	//}}AFX_VIRTUAL

	// Generated message map functions
	//{{AFX_MSG(CClientSock)
		// NOTE - the ClassWizard will add and remove member functions here.
	//}}AFX_MSG

// Implementation
protected:
};