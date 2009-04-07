// log.cpp : Defines the entry point for the DLL application.
//

#include "stdafx.h"
#include "Log.h"

CLogInfo::CLogInfo()
{

}

CLogInfo::~CLogInfo()
{
	ClearLogInfo();
} 
 
void CLogInfo::AddLogInfo(int nType, CString str, CString strTime)
{
	LOGINFO LogInfo(nType, str, strTime);
	m_deqLogInfo.push_back(LogInfo);
}

void CLogInfo::PopLogInfo()
{
	m_deqLogInfo.pop_front();
}

void CLogInfo::ClearLogInfo()
{
	if(m_deqLogInfo.size() > 0)
		m_deqLogInfo.clear();
}

CLog::CLog()
{

}

CLog::~CLog()
{
	ClearLog();
}

int	CLog::GetLogSize()
{
	return m_LogInfo.GetSize();
}

void CLog::GetLog(int nType, CLogInfo* pLogInfo)
{
	for(int i = 0; i < m_LogInfo.GetSize(); i++)
	{
		if(m_LogInfo.GetLogInfo(i)._nType == nType)
		{
			pLogInfo->AddLogInfo(nType, 
				                 m_LogInfo.GetLogInfo(i)._strText, 
								 m_LogInfo.GetLogInfo(i)._strTime);
		}
	}
}

void CLog::AddLog(const char* fmt, ...)
{
	char buff[1024];
	va_list ap;

	va_start(ap, fmt);
	vsprintf(buff, fmt, ap);
	va_end(ap);

	CTime Time = CTime::GetCurrentTime();   
	CString strTime = Time.Format("[%Y년%m월%d일 : %H시%M분%S초] ");   

	m_LogInfo.AddLogInfo(-1, buff, strTime);
}

void CLog::AddLog(int nType, const char* fmt, ...)
{
	char buff[1024];
	va_list ap;

	va_start(ap, fmt);
	vsprintf(buff, fmt, ap);
	va_end(ap);

	CTime Time = CTime::GetCurrentTime();   
	CString strTime = Time.Format("[%Y년%m월%d일 : %H시%M분%S초] ");   

	m_LogInfo.AddLogInfo(nType, buff, strTime);
}

void CLog::ClearLog()
{
	m_LogInfo.ClearLogInfo();
}

void CLog::SaveTxtFile(const char* pszFileName, bool bTime, int nType)
{
	if(pszFileName == NULL)
	{
		assert(!"pszFileName = NULL (CLog - SaveTxtFile())");
	}

	CFile File;
	CString strTemp;

	strTemp.Format("%s.txt", pszFileName);

	File.Open(strTemp, CFile::modeCreate | CFile::modeWrite);

	for(int i = 0; i < m_LogInfo.GetSize(); i++)
	{
		if(nType == LOG_ALL_TYPE || m_LogInfo.GetLogInfo(i)._nType == nType)
		{
			if(bTime) 
			{
				File.Write(m_LogInfo.GetLogInfo(i)._strTime, 
					       m_LogInfo.GetLogInfo(i)._strTime.GetLength());
			}
			
			if(bTime)
			{
				strTemp.Format(" [%d] ", m_LogInfo.GetLogInfo(i)._nType);
				File.Write(strTemp, strTemp.GetLength());
			}
			else
			{
				strTemp.Format("[%d] ", m_LogInfo.GetLogInfo(i)._nType);
				File.Write(strTemp, strTemp.GetLength());
			}

			File.Write(m_LogInfo.GetLogInfo(i)._strText,
				       m_LogInfo.GetLogInfo(i)._strText.GetLength());

			File.Write("\r\n", 2);
		}
	}

	File.Close();
}

void CLog::SaveCSVFile(const char* pszFileName, int nType)
{
	if(pszFileName == NULL)
	{
		assert(!"pszFileName = NULL (CLog - SaveCSVFile())");
	}

	CFile File;
	CString strTemp;

	strTemp.Format("%s.csv", pszFileName);

	File.Open(strTemp, CFile::modeCreate | CFile::modeWrite);

	strTemp.Format("\"Time\",\"Type\",\"Context\",\n"); 
	File.Write(strTemp, strTemp.GetLength());

	for(int i = 0; i < m_LogInfo.GetSize(); i++)
	{
		if(nType == LOG_ALL_TYPE || m_LogInfo.GetLogInfo(i)._nType == nType)
		{
			strTemp.Format("\"%s\",\"%d\",\"%s\"\n",
						   m_LogInfo.GetLogInfo(i)._strTime,
						   m_LogInfo.GetLogInfo(i)._nType,
						   m_LogInfo.GetLogInfo(i)._strText);

			File.Write(strTemp, strTemp.GetLength());
		}
	}

	File.Close();
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
    return TRUE;
}

