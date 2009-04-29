/* 
	Author				: Bill Kim (kjh_900@hanmail.net, kjh_900@hotmail.com, BillKim@joyon.com)	
	Release Date		: 2008. 01. 14.
	File Name			: Singleton Pattern
	Version				: 1.00.00

	Test PC				: CPU - Sonoma 1.86, RAM - 1 GB Graphic - GMA 900
	Test OS				: Windows XP Home Edition + SP2
	Test Application	: Visual Studio 2003, 2005 + DirectX SDK 9.0c(Nov, 2007)
	
	Contents

	Singleton Pattern Header

	2008 ¨Ï Copyright MIS Corporation. All Rights Reserved.
*/

#pragma once

template <class T>
class /*__DLL*/ CSingleton
{
private:
	static T* m_Instance; 

public:
	T* operator->() { return m_Instance; }

	static T* GetpInstance()
	{
		if(m_Instance == NULL) m_Instance = new T;
		return m_Instance;
	}

	static T& GetInstance()
	{
		if(m_Instance == NULL) m_Instance = new T;
		return *m_Instance;
	}

	static void DestroyInstance()
	{
		//delete m_Instance;
		//m_Instance = NULL;

		SAFE_DELETE(m_Instance);
	}
};

template<class T> T* CSingleton<T>::m_Instance = NULL;