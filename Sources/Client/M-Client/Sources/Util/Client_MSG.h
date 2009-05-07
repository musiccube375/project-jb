/* 
	Author				: 김정훈(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 28.
	Project	Name		: Client Message
	Version				: 1.00.03

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Client Message Header

	2009 ⓒ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "Common_Define.h"

void MSG_Seperator(int nIndex, const char* msg, char* pOut);

// 서버로 메시지 전송
void MSG_SendToServer(const char* pszSend);

// 서버 나가기
void MSG_Exit_Server_Req(const char* pszID);

// 아이디 체크(가입시에)
void MSG_ID_Check_Req(const char* pszID);
MSG_RET MSG_ID_Check_Ack(MSG_DATA msgData);

// 계정 생성
void MSG_Add_ID_Req(const char* pszID, const char* pszPasswords);
MSG_RET MSG_Add_ID_Ack(MSG_DATA msgData);

// 로그인
void MSG_Login_Req(const char* pszID, const char* pszPasswords, const char* pszServer);
MSG_RET MSG_Login_Ack(MSG_DATA msgData);

// 친구 추가
void MSG_Add_Friend_Req(const char* pszID, const char* pszFriendID, const char* pszMessage);
MSG_RET MSG_Add_Friend_Ack(MSG_DATA msgData);