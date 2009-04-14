#include "StdAfx.h"
#include "mgr.h"
#include "member.h"
#include "ChatSDlg.h"
#include ".\mgr.h"

CMgr::CMgr(void)
{
}

CMgr::~CMgr(void)
{
}

int CMgr::ExistMember(CString id)
{
	// 아이디가 존재하는지 검사..
	int nSel=-1;
	for(int i=0;i<m_Membernum;i++){
		if(strcmp(m_Memberlist[i].GetID(), id)==0){
			nSel=i;
			break;
		}
	}
	return nSel;
}

bool CMgr::Addmember(CString id, CString pass, CString name) // 멤버 추가.
{
	// 기존 아이디가 존재하는지 검사
	if(m_Membernum==0 || ExistMember(id) == -1)
	{
		// 파일에 추가
		CFile file;
		if(file.Open(_T("Memberdata.dat"), CFile::modeWrite))
		{
			//리스트에 저장
			m_Memberlist[m_Membernum].Setmember(id, pass, name);
			m_Memberlist[m_Membernum].m_mylistnum = 0;
			m_Membernum++;
			

			//파일에 저장
			CArchive ar(&file, CArchive::store);
			Serialize(ar);
			ar.Close();
		}
		else {
			AfxMessageBox(_T("파일에 저장 실패"));
		}
	}
	else
	{
		// 아이디가 이미 존재하는 경우 멤버추가 실패
		return false;
	}
	return true;
}

bool CMgr::Delmember(CString id)
{
	// 번호 찾기
	int nSel=ExistMember(id);

	CFile file;
	if(file.Open(_T("Memberdata.dat"), CFile::modeWrite))
	{
		//리스트에서 삭제
		for(int i=nSel;i<m_Membernum-1;i++){
			m_Memberlist[i].Setmember (m_Memberlist[i+1].m_id, m_Memberlist[i+1].m_pass, m_Memberlist[i+1].m_name);
		}

		m_Membernum --;

		//파일에 저장
		CArchive ar(&file, CArchive::store);
		Serialize(ar);
		ar.Close();
		return true;
	}
	return false;
}

void CMgr::Serialize(CArchive& ar)
{
	if (ar.IsStoring())
	{	// storing code
		ar << m_Membernum;
		for(int i=0;i<m_Membernum;i++){
			ar << m_Memberlist[i].m_id;
			ar << m_Memberlist[i].m_pass;
			ar << m_Memberlist[i].m_name;
			ar << m_Memberlist[i].m_mylistnum;
			for(int j=0;j<m_Memberlist[i].m_mylistnum;j++)
			{
				ar << m_Memberlist[i].m_mylist[j];
			}
		}
	}
	else
	{	// loading code
		ar >> m_Membernum;
		for(int i=0;i<m_Membernum;i++){
			ar >> m_Memberlist[i].m_id;
			ar >> m_Memberlist[i].m_pass;
			ar >> m_Memberlist[i].m_name;
			ar >> m_Memberlist[i].m_mylistnum;
			for(int j=0;j<m_Memberlist[i].m_mylistnum;j++)
			{
				ar >> m_Memberlist[i].m_mylist[j];
			}
		}
	}
}

bool CMgr::Init(CChatSDlg *p)
{
	CFile file;
	if(file.Open(_T("Memberdata.dat"), CFile::modeRead))
	{
		// 파일이 이미 존재할 경우 읽기모드
		CArchive ar(&file, CArchive::load);
		Serialize(ar);
		for(int i=0;i<m_Membernum;i++){
			// 다이얼로그에 표시
			p->ShowMember(i,m_Memberlist[i].GetID(), m_Memberlist[i].GetName());
		}
		ar.Close();
	}
	else {
		// 파일이 없을 경우 파일 생성
		file.Open(_T("Memberdata.dat"), CFile::modeCreate | CFile::modeWrite);
		CArchive ar(&file, CArchive::store);

		m_Membernum = 0;
		Serialize(ar); 
		ar.Close();
	}
	return true;
}

bool CMgr::CheckPass(CString id, CString pass)
{
	int nSel=ExistMember(id);

	if(strcmp(m_Memberlist[nSel].m_pass , pass) == 0) return true;

	return false;
}

void CMgr::ModMemberName(int nSel, CString name)
{
	// 데이터 변경
	m_Memberlist[nSel].m_name = name;

	// 파일에 저장
	CFile file;
	if(file.Open(_T("Memberdata.dat"), CFile::modeWrite))
	{
		CArchive ar(&file, CArchive::store);
		Serialize(ar);
		ar.Close();
	}
}

void CMgr::SetMemberOnline(CString id, bool online, CDataSocket * pDataSocket)
{
	// 번호 찾기
	int nSel=ExistMember(id);
	if(nSel==-1) return;

	m_Memberlist[nSel].m_online = online;
	m_Memberlist[nSel].m_pDataSocket = pDataSocket;
}

CString CMgr::GetMemberName(CString id)
{
	int nSel=ExistMember(id);
	return m_Memberlist[nSel].GetName();
}

bool CMgr::GetMemberOnline(CString id)
{
	// 번호 찾기
	int nSel=ExistMember(id);
	if(nSel==-1) return false;

	return m_Memberlist[nSel].m_online;
}

CDataSocket * CMgr::GetMemberSocket(CString id)
{
	// 번호 찾기
	int nSel=ExistMember(id);
	if(nSel==-1) return NULL;

	return m_Memberlist[nSel].m_pDataSocket;
}

void CMgr::AddMemberMylist(int nSel, CString destId) // 대화상대 추가해서 저장.
{
	// 이미 있는 사람인지.. 확인
	// 데이터 변경
	m_Memberlist[nSel].Addmylist(destId);

	// 파일에 저장
	CFile file;
	if(file.Open(_T("Memberdata.dat"), CFile::modeWrite))
	{
		CArchive ar(&file, CArchive::store);
		Serialize(ar);
		ar.Close();
	}
}

void CMgr::DelMemberMylist(int nSel, CString destId) // 대화상대 삭제해서 저장.
{
	// 데이터 변경
	m_Memberlist[nSel].Delmylist(destId);

	// 파일에 저장
	CFile file;
	if(file.Open(_T("Memberdata.dat"), CFile::modeWrite))
	{
		CArchive ar(&file, CArchive::store);
		Serialize(ar);
		ar.Close();
	}
}
CDataSocket * CMgr::GetMemberSocket(int nSel)
{
	return m_Memberlist[nSel].m_pDataSocket;
}

CString CMgr::GetMemberID(int nSel)
{
	return m_Memberlist[nSel].m_id;
}

CString CMgr::GetMemberName(int nSel)
{
	return m_Memberlist[nSel].m_name;
}

bool CMgr::GetMemberOnline(int nSel)
{
	return m_Memberlist[nSel].m_online;
}


int CMgr::GetMemberMylistnum(int nSel)
{
	return m_Memberlist[nSel].m_mylistnum;
}

CString CMgr::GetMemberMylist(int nSel, int nSel2)
{
	return m_Memberlist[nSel].m_mylist[nSel2];
}

int CMgr::GetMemberMylistExist(int nSel, CString id)
{
	int n = m_Memberlist[nSel].m_mylistnum;
	// 리스트에 아이디가 존재하는지 검사..
	int nSel2=-1;
	for(int i=0;i<n;i++){
		if(strcmp(m_Memberlist[nSel].m_mylist[i], id)==0){
			nSel2=i;
			break;
		}
	}
	return nSel2;
}
