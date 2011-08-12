//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	CTimer.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	high frequency timer
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Windows.h>
#include <stdio.h>
#include "Helpers.h"

class CTimer  
{
private:

	LARGE_INTEGER	m_liCounter;			//general counter used for everything
	LARGE_INTEGER	m_liFPSCounter;			//fps only counter
	double			m_fFractionOfSeconds;	//stores the amount of time between each cycle
	int				m_nFrameCount;			//frame count used for frame rate
	int				m_nFrameRate;			//int of the current frame rate
	char			m_szFrameRate[128];		//string of the current frame rate

	static LONGLONG	m_llFrequency;			//frequency (never will change once system is on)
	static	CTimer *m_pInstance;			//instance to the singleton	

	CTimer(){};
	CTimer(const CTimer &a){};
	CTimer &operator=(const CTimer &a){};

public:

	//	~CTimer: Destructor
	~CTimer(){};

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DeleteInstance
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		Delete the instance of the class, and set the pointer to NULL
	//
	//////////////////////////////////////////////////////////////////////////
	static void DeleteInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetInstance
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		Creates the first instance of this class and returns it's address.
	//
	//////////////////////////////////////////////////////////////////////////
	static CTimer *GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitTimer
	//
	//	Last Modified: 	2006/01/15
	//
	//	Purpose:		Initializes the frequency and counter
	//
	//////////////////////////////////////////////////////////////////////////
	void InitTimer();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		RefreshFPS
	//
	//	Last Modified: 	2006/01/15
	//
	//	Purpose:		Updates the fps
	//
	//////////////////////////////////////////////////////////////////////////
	void UpdateFPS();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		RefreshCounter
	//
	//	Last Modified: 	2006/01/15
	//
	//	Purpose:		Updates the general counter
	//
	//////////////////////////////////////////////////////////////////////////
	void Update();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Inline Functions
	//
	//	Last Modified: 	2006/01/15
	//
	//	Purpose:		Inline functions to get Timer information. 
	//
	//////////////////////////////////////////////////////////////////////////
	inline	char *	GetFrameRateChar()				{return m_szFrameRate;}
	inline	int		GetFrameRateInt()				{return m_nFrameRate;}
	inline	double	GetFractionOfSecondsPassed()	{return m_fFractionOfSeconds;}
};