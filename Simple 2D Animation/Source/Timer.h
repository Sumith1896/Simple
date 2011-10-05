//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	Timer.h
//
//	Purpose:	high frequency timer
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Windows.h>
#include <stdio.h>
#include "Helpers.h"

#define MAXTIMERS 8

struct CACHE_ALIGN tTimer
{
	LARGE_INTEGER	liCounter;			//general counter used for everything
	LARGE_INTEGER	liFPSCounter;		//fps only counter
	double			fFractionOfSeconds;	//stores the amount of time between each cycle
	int				nFrameCount;		//frame count used for frame rate
	int				nFrameRate;			//int of the current frame rate
	char			szFrameRate[32];	//string of the current frame rate
};

class CACHE_ALIGN Timer  
{
private:

	tTimer	m_Timers[MAXTIMERS];	//all the different timers, 8 max for now
	unsigned short	m_nCurrentTimer; //index of the current timer for creating them
	LARGE_INTEGER m_liNow;
	bool	m_bInit;	//true = init

	LONGLONG	m_llFrequency;			//frequency (never will change once system is on)
	static	Timer *m_pInstance;			//instance to the singleton	

	Timer(){};
	Timer(const Timer &a){};
	Timer &operator=(const Timer &a){};

public:

	//	~Timer: Destructor
	~Timer(){};

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DeleteInstance
	//
	//	Purpose:		Delete the instance of the class, and set the pointer to NULL
	//
	//////////////////////////////////////////////////////////////////////////
	static void DeleteInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetInstance
	//
	//	Purpose:		Creates the first instance of this class and returns it's address.
	//
	//////////////////////////////////////////////////////////////////////////
	static Timer *GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Init
	//
	//	Purpose:		Initializes the frequency and counter
	//
	//////////////////////////////////////////////////////////////////////////
	void Init();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		CreateTimer
	//
	//	Purpose:		creates a new timer to use and returns the index of 
	//					that timer, -1 will be returned if it fails
	//
	//////////////////////////////////////////////////////////////////////////
	int CreateTimer();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		RefreshFPS
	//
	//	Purpose:		Updates the fps
	//
	//////////////////////////////////////////////////////////////////////////
	void UpdateFPS(unsigned int nTimer);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Update
	//
	//	Purpose:		Updates the general counter
	//
	//////////////////////////////////////////////////////////////////////////
	void Update(unsigned int nTimer);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Inline Functions
	//
	//	Purpose:		Inline functions to get Timer information. 
	//
	//////////////////////////////////////////////////////////////////////////
	char *GetFrameRateChar(unsigned int nTimer)				
	{
#ifdef _DEBUG
		if(nTimer > MAXTIMERS)
		{
			COUT << "Timer::GetFrameRateChar() - FAIL(nTimer id out of array bounds)" << endl; 
			assert(false);
			return NULL;
		}
#endif
		int tom  = 0;
		return m_Timers[nTimer].szFrameRate;
	}

	int GetFrameRateInt(unsigned int nTimer)					
	{
#ifdef _DEBUG
		if(nTimer > MAXTIMERS)
		{
			COUT << "Timer::GetFrameRateInt() - FAIL(nTimer id out of array bounds)" << endl;
			assert(false);
			return 0;
		}
#endif
		return m_Timers[nTimer].nFrameRate;
	}

	double GetFractionOfSecondsPassed(unsigned int nTimer)	
	{
#ifdef _DEBUG
		if(nTimer > MAXTIMERS)
		{
			COUT << "Timer::GetFractionOfSecondsPassed() - FAIL(nTimer id out of array bounds)" << endl;
			assert(false);
			return 0.0f;
		}
#endif
		return m_Timers[nTimer].fFractionOfSeconds;
	}
};