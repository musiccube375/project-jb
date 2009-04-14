#pragma once

class CMember
{
public:
	CMember(void);
	~CMember(void);

	void ModifyName(CString name);
	void SetOnline(bool online);
	void SetDlgPtr(CChatCDlg * dlg);

	CString GetID(void);
	CString GetName(void);
	bool GetOnline(void);
	CChatCDlg * GetDlgPtr(void);

private:
	CString m_name;
	CString m_id;
	bool m_online;
	CChatCDlg *m_dlg;
};
