//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	Timer.cpp
//
//	Purpose:	high frequency timer
//
//////////////////////////////////////////////////////////////////////////
#include "Timer.h"

//initialize the static variable member(s)
Timer *Timer::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
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
//	Purpose:		Creates the first instance of this class and returns it's address.
//
//////////////////////////////////////////////////////////////////////////
Timer *Timer::GetInstance()
{
	if(!m_pInstance)
	{
		m_pInstance = new Timer;
		m_pInstance->m_bInit = false;
	}

	COUT << "Timer::GetInstance() - SUCCESS" << endl; 

	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Init
//
//	Purpose:		Initializes the frequency and counter
//
//////////////////////////////////////////////////////////////////////////
void Timer::Init()
{
	if(m_bInit)
	{
		return;
	}

	//we don't want to initialize this twice
	m_bInit = true;

	LARGE_INTEGER	liFrequency;

	m_nCurrentTimer = 0;

	//get frequency, this will only be done once as it will never change while the computer is on
	QueryPerformanceFrequency(&liFrequency);

	m_llFrequency = liFrequency.QuadPart;

	ZeroMemory(&m_Timers, (sizeof(tTimer)*MAXTIMERS));
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		CreateTimer
//
//	Purpose:		creates a new timer to use and returns the index of 
//					that timer, -1 will be returned if it fails
//
//////////////////////////////////////////////////////////////////////////
int Timer::CreateTimer()
{
	//no more timers can be made
	if(m_nCurrentTimer >= MAXTIMERS)
	{
		return -1;
	}

	//set both counters to the latest value
	QueryPerformanceCounter(&m_Timers[m_nCurrentTimer].liCounter);
	QueryPerformanceCounter(&m_Timers[m_nCurrentTimer].liFPSCounter);

	return m_nCurrentTimer++;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		UpdateFPS
//
//	Purpose:		Updates the fps
//
//////////////////////////////////////////////////////////////////////////
void Timer::UpdateFPS(unsigned int nTimer)
{
#ifdef _DEBUG
	if(nTimer > MAXTIMERS)
	{
		COUT << "Timer::UpdateFPS() - FAIL(nTimer id out of array bounds)" << endl;
		assert(false);
		return;
	}
#endif

	QueryPerformanceCounter(&m_liNow);

	//subject counters and then check to see if 1 second passed
	if((m_liNow.QuadPart - m_Timers[nTimer].liFPSCounter.QuadPart) > m_llFrequency)
	{
		//set frame rate to current frame count
		m_Timers[nTimer].nFrameRate = m_Timers[nTimer].nFrameCount;

		//set frame count back to 0
		m_Timers[nTimer].nFrameCount = 0;

		//make a nice pretty char[] for displaying the fps
		sprintf(m_Timers[nTimer].szFrameRate, "FPS %d", m_Timers[nTimer].nFrameRate);

		//update fps counter with the latest value
		QueryPerformanceCounter(&m_Timers[nTimer].liFPSCounter);
	}

	//increment frame count by 1
	m_Timers[nTimer].nFrameCount++;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Update
//
//	Purpose:		Updates the general counter
//
//////////////////////////////////////////////////////////////////////////
void Timer::Update(unsigned int nTimer)
{
#ifdef _DEBUG
	if(nTimer > MAXTIMERS)
	{
		COUT << "Timer::UpdateFPS() - FAIL(nTimer id out of array bounds)" << endl;
		assert(false);
		return;
	}
#endif

	m_liNow = m_Timers[nTimer].liCounter;

	//update the counter with the latest value
	QueryPerformanceCounter(&m_Timers[nTimer].liCounter);

	//calculate amount of time that the cycle took and store the value as a double
	m_Timers[nTimer].fFractionOfSeconds =  ((m_Timers[nTimer].liCounter.QuadPart - m_liNow.QuadPart)/(double)m_llFrequency);
}