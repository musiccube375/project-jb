/* 
	Author				: 김정훈(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 28.
	Project	Name		: Server Manager Message
	Version				: 1.00.01

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Server Manager Message Header

	2009 ⓒ Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

// 서버로 메시지 전송
void MSG_SendToServer(CClientSock* pSock, const char* pszSend);

// 메시지를 인덱스에 맞춰 파싱한다
void MSG_Seperator(int nIndex, const char* msg, char* pOut);

// 아이디 체크(가입시에)
void MSG_ID_Check_Ack(MSG_DATA msgData, CClientSock* pSock);

// 계정 추가
void MSG_Add_ID_Ack(MSG_DATA msgData, CClientSock* pSock);

// 로그인
void MSG_Login_Ack(MSG_DATA msgData, CClientSock* pSock);