#pragma once
#include "member.h"

using namespace std;

class CMember;
class CChatSDlg;
class CMgr : public CObject
{
public:
	CMgr(void);
	~CMgr(void);
	//static CMgr* GetInstance();
private:
	CMember m_Memberlist[200];
	virtual void Serialize(CArchive& ar);
public:	int m_Membernum;
public:
	int ExistMember(CString id);
	bool Addmember(CString id, CString pass, CString name);
	bool Delmember(CString id);
	bool Init(CChatSDlg *p);
	bool CheckPass(CString id, CString pass);
	void SetMemberOnline(CString id, bool online, CDataSocket * pDataSocket=NULL);
	void ModMemberName(int nSel, CString name);

	bool GetMemberOnline(CString id);
	bool GetMemberOnline(int nSel);
	CString GetMemberName(CString id);
	CString GetMemberName(int nSel);
	CString GetMemberID(int nSel);
	CDataSocket * GetMemberSocket(CString id);
	CDataSocket * GetMemberSocket(int nSel);
	void AddMemberMylist(int nSel, CString destId);
	void DelMemberMylist(int nSel, CString destId);
	int GetMemberMylistnum(int nSel);
	CString GetMemberMylist(int nSel, int nSel2);
	int GetMemberMylistExist(int nSel, CString id);
};
