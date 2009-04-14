#pragma once



// CData 명령 대상입니다.

class CData : public CObject
{
public:
	CData();
	virtual ~CData();
	virtual void Serialize(CArchive& ar);

	int m_flag;
	CString m_strId;
	CString m_strPass;
	CString m_strName;
	CString m_strData;
	CString m_strDestId;
	CString m_mylist[100];
	int m_mylistnum;
	bool m_result;

	void Setdata(int flag, bool result=true, CString id="", CString name="", CString data="", CString dest_id="", CString pass="");
	void SetLogindata(int flag, CString id, CString pass);
};


