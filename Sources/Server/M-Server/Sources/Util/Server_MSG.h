/* 
	Author				: 김정훈(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 28.
	Project	Name		: Server Message
	Version				: 1.00.02

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Server Message Header

	2009 ⓒ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#include "Common_Define.h"

// 서버 매니저로 메시지 전송
void MSG_SendToServerMgr(const char* pszSend);

// 클라이언트 유저로 메시지 전송
void MSG_SendToClient(const char* pszSend, char* pszID);

// 클라이언트 유저 서버 나가기
void MSG_Exit_Server_Req(MSG_DATA msgData);

// 아이디 체크(가입시에)
void MSG_ID_Check_Req(MSG_DATA msgData);
void MSG_ID_Check_Ack(MSG_DATA msgData);

// 계정 추가
void MSG_Add_ID_Req(MSG_DATA msgData);
void MSG_Add_ID_Ack(MSG_DATA msgData);

// 로그인
void MSG_Login_Req(MSG_DATA msgData);
void MSG_Login_Ack(MSG_DATA msgData);

// 친구 추가
void MSG_Add_Friend_Req(MSG_DATA msgData);
void MSG_Add_Friend_Ack(MSG_DATA msgData);

