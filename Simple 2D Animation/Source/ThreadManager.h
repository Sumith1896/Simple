//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	ThreadManager.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	manages the creation, updating and destroying of threads
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Windows.h>
#include <vector>
#include "Helpers.h"
using std::vector;

class CACHE_ALIGN CThreadManager  
{
private:

	int	m_nThreadsRunning;					//number of total threads still running
	int	m_nThreadCount;						//number of total threads
	vector<HANDLE> m_vThreadHandles;		//handles to all the threads
	static	CThreadManager *m_pInstance;	//instance to the singleton	

	CThreadManager(){};
	CThreadManager(const CThreadManager &a){};
	CThreadManager &operator=(const CThreadManager &a){};

public:

	//	~CTimer: Destructor
	~CThreadManager(){};

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DeleteInstance
	//
	//	Last Modified: 	03/06/2008
	//
	//	Purpose:		Delete the instance of the class, and set the pointer to NULL
	//
	//////////////////////////////////////////////////////////////////////////
	static void DeleteInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetInstance
	//
	//	Last Modified: 	03/06/2008
	//
	//	Purpose:		Creates the first instance of this class and returns it's address.
	//
	//////////////////////////////////////////////////////////////////////////
	static CThreadManager *GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		CreateThread
	//
	//	Last Modified: 	03/06/2008
	//
	//	Purpose:		Creates a thread and returns a handle 
	//
	//////////////////////////////////////////////////////////////////////////
	int CreateThread(unsigned ( *start_address )( void * ));

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
	void ThreadComplete(int nThreadIndex);
};