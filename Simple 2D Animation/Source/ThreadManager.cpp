//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	CThreadManager.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	manages the creation, updating and destroying of threads
//
//////////////////////////////////////////////////////////////////////////
#include "ThreadManager.h"
#include <process.h>

//initialize the static variable member(s)
CThreadManager *CThreadManager::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
//
//	Last Modified: 	03/06/2008
//
//	Purpose:		Delete the instance of the class, and set the pointer to NULL
//
//////////////////////////////////////////////////////////////////////////
void CThreadManager::DeleteInstance()
{
	SAFE_DELETE(m_pInstance);

	COUT << "CThreadManager::DeleteInstance() - SUCCESS" << endl; 
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetInstance
//
//	Last Modified: 	03/06/2008
//
//	Purpose:		Creates the first instance of this class and returns it's address.
//
//////////////////////////////////////////////////////////////////////////
CThreadManager *CThreadManager::GetInstance()
{
	if(!m_pInstance)
		m_pInstance = new CThreadManager;

	COUT << "CThreadManager::DeleteInstance() - SUCCESS" << endl; 

	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		CreateThread
//
//	Last Modified: 	03/06/2008
//
//	Purpose:		Creates a thread and returns an index to it 
//
//////////////////////////////////////////////////////////////////////////
int CThreadManager::CreateThread(unsigned ( *start_address )( void * ))
{
	HANDLE hNewThread = NULL;

	//hNewThread = (HANDLE)_beginthreadex(NULL, 0, start_address, 0, CREATE_SUSPENDED,  (unsigned int *)&hNewThread);

	m_vThreadHandles.push_back(hNewThread);

	m_nThreadCount++;

	return ((int)m_vThreadHandles.size() - 1);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		ThreadComplete
//
//	Last Modified: 	03/06/2008
//
//	Purpose:		A thread will call this when it has completed the work
//					for the current frame and needs to sleep until the next
//
//////////////////////////////////////////////////////////////////////////
void CThreadManager::ThreadComplete(int nThreadIndex)
{
	SuspendThread(m_vThreadHandles[nThreadIndex]);
}

//DWORD WINAPI ResumeThread( __in  HANDLE hThread  );
//DWORD WINAPI SuspendThread(__in  HANDLE hThread  );

