#pragma once

class CMember
{
public:
	CMember();
	~CMember();

	void Setmember(CString id, CString pass, CString name);

	void Addmylist(CString dest_id);
	void Delmylist(CString dest_id);

	CString GetID();
	CString GetName();
	
	friend class CMgr;

private:
	CString m_id;
	CString m_pass;
	CString m_name;
	CString m_mylist[100];
	int m_mylistnum;
	bool m_online;
	CDataSocket *m_pDataSocket;

};
