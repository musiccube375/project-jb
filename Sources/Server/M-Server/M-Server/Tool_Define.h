/* 
	Author				: ±èÁ¤ÈÆ(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 22.
	Project	Name		: Tool Define 
	Version				: 1.00.00

	Test PC				: CPU - Pentium(R) 4 2.40Ghz, RAM - 1 GB Graphic - Radeon 9600
	Test OS				: Windows XP Professional + SP3
	Test Application	: Visual Studio 2008 + SP1
	
	Contents

	Tool Define Header

	2009 ¨Ï Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

#ifndef SAFE_DELETE
#define SAFE_DELETE(p)          if(p) { delete (p); (p) = NULL; }
#endif 

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p)    if(p) { delete[] (p); (p) = NULL; }
#endif 

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p)         if(p) { (p)->Release(); (p) = NULL; }
#endif 

#include "T_Singleton.h"
#include "ToolMgr.h"	

CSingleton<CToolMgr>	sToolMgr;
#define g_sToolMgr		sToolMgr.GetInstance()

#define LOG_TYPE				0x004C4F47
#define LOG_TYPE_TOOLWORK		LOG_TYPE + 1
#define LOG_TYPE_CONFIG			LOG_TYPE + 2
#define LOG_TYPE_CONN			LOG_TYPE + 3
#define LOG_TYPE_ERROR			LOG_TYPE + 4
#define LOG_TYPE_RECV			LOG_TYPE + 5
#define LOG_TYPE_SEND			LOG_TYPE + 6

#define WM_SERVER_ACCEPT		WM_USER + 1
#define WM_CLIENT_RECEIVE		WM_USER + 2
#define WM_CLIENT_CONNECT		WM_USER + 3
#define WM_CLIENT_CLOSE			WM_USER + 4
#define WM_CLIENT_NETDOWN		WM_USER + 5	
#define WM_CLIENT_SEND			WM_USER + 6
#define WM_CLIENT_SEND_ERROR	WM_USER + 7
