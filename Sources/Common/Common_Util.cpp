#include "stdafx.h"
#include "Common_Util.h"

void GetMyIP(CString& strIP)
{
	char name[255];
	PHOSTENT hostinfo;

	if(gethostname(name, sizeof(name)) == 0) 
	{ 
		if((hostinfo = gethostbyname(name)) != NULL) 
		{ 
			strIP = inet_ntoa(*(struct in_addr *) *hostinfo->h_addr_list); 
		} 
	}
}