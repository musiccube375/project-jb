/* 
	Author				: ±èÁ¤ÈÆ(Bill) (kjh_900@hanmail.net)	
	Release Date		: 2009. 04. 15.
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
