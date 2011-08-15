//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	Timer.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	high frequency timer
//
//////////////////////////////////////////////////////////////////////////
#include "Timer.h"

//initialize the static variable member(s)
Timer *Timer::m_pInstance = NULL;
LONGLONG Timer::m_llFrequency = 0;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Delete the instance of the class, and set the pointer to NULL
//
//////////////////////////////////////////////////////////////////////////
void Timer::DeleteInstance()
{
	SAFE_DELETE(m_pInstance);

	COUT << "Timer::DeleteInstance() - SUCCESS" << endl; 
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetInstance
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Creates the first instance of this class and returns it's address.
//
//////////////////////////////////////////////////////////////////////////
Timer *Timer::GetInstance()
{
	if(!m_pInstance)
		m_pInstance = new Timer;

	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitTimer
//
//	Last Modified: 	2006/01/15
//
//	Purpose:		Initializes the frequency and counter
//
//////////////////////////////////////////////////////////////////////////
void Timer::InitTimer()
{
	LARGE_INTEGER	liFrequency;

	//get frequency, this will only be done once as it will never change while the computer is on
	QueryPerformanceFrequency(&liFrequency);

	//set our longlong frequency (will never change)
	if(!m_llFrequency)
		m_llFrequency = liFrequency.QuadPart;

	//set all to 0
	m_nFrameCount			= 0;
	m_nFrameRate			= 0;
	m_fFractionOfSeconds	= 0.0f;

	//set both counters to the latest value
	QueryPerformanceCounter(&m_liCounter);
	QueryPerformanceCounter(&m_liFPSCounter);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		RefreshFPS
//
//	Last Modified: 	2006/01/15
//
//	Purpose:		Updates the fps
//
//////////////////////////////////////////////////////////////////////////
void Timer::UpdateFPS()
{
	static LARGE_INTEGER liNow;
	QueryPerformanceCounter(&liNow);

	//subject counters and then check to see if 1 second passed
	if((liNow.QuadPart - m_liFPSCounter.QuadPart) > m_llFrequency)
	{
		//set frame rate to current frame count
		m_nFrameRate = m_nFrameCount;

		//set frame count back to 0
		m_nFrameCount = 0;

		//make a nice pretty char[] for displaying the fps
		sprintf(m_szFrameRate, "FPS %d", m_nFrameRate);

		//update fps counter with the latest value
		QueryPerformanceCounter(&m_liFPSCounter);
	}

	//increment frame count by 1
	m_nFrameCount++;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		RefreshCounter
//
//	Last Modified: 	2006/01/15
//
//	Purpose:		Updates the general counter
//
//////////////////////////////////////////////////////////////////////////
void Timer::Update()
{
	static LARGE_INTEGER liNow;

	liNow = m_liCounter;

	//update the counter with the latest value
	QueryPerformanceCounter(&m_liCounter);

	//calculate amount of time that the cycle took and store the value as a double
	m_fFractionOfSeconds =  ((m_liCounter.QuadPart - liNow.QuadPart)/(double)m_llFrequency);
}