// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once


#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
//#include <windows.h>
#include <afx.h>

// TODO: reference additional headers your program requires here

#ifdef _DLL
#define _DLL __declspec(dllexport)
#else
#define _DLL __declspec(dllimport)
#endif