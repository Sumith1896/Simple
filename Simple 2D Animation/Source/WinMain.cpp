//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	WinMain.cpp
//
//	Author:		 
//
//	Purpose:	Basic Windows Shell
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include <windows.h>
#include "resource.h"
#include <ctime>
#include <process.h>
#include "SimpleMain.h"
#include "WorldGod.h"

//console window includes
#ifdef _DEBUG
#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <iostream>
#include <fstream>
using namespace std;
#endif

//global constants
#define WINDOW_WIDTH	1024					//window width
#define WINDOW_HEIGHT	768				//window height
#define CLASSNAME "Simple Shell"			//window class name
#define MAX_CONSOLE_LINES 500				//maxium lines a console window will have

LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam);
int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow);

unsigned int __stdcall ThreadGameUpdate(void *pData);
HANDLE hThreadWorldUpdate;
unsigned int nThreadGameStatus = 0;
unsigned int __stdcall ThreadWorldUpdate(void *pData);
HANDLE hThreadGameUpdate;
unsigned int nThreadWorldStatus = 0;

WNDCLASS	winclass;		//this will hold the class we create
MSG			msg;			//generic message
HWND		hWnd;			//main Window Handle.
HINSTANCE	hInstance;

//console window redirect function
#ifdef _DEBUG
void RedirectIOToConsole();
#endif

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		WindowProc
//
//	Last Modified: 	07/07/2006
//
//	Purpose:		windows message callback loop 
//
//////////////////////////////////////////////////////////////////////////
LRESULT CALLBACK WindowProc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
{
	//check to see if we need to close the app
	if(msg == WM_DESTROY || msg == WM_CLOSE)
	{
		PostQuitMessage(0);
		return(0);
	}

	//process any messages that we didn't take care of 
	return (DefWindowProc(hwnd, msg, wparam, lparam));
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		WinMain
//
//	Last Modified: 	07/07/2006
//
//	Purpose:		initial entry point for a Windows-based application 
//
//////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(	HINSTANCE hinstance, HINSTANCE hprevinstance, LPSTR lpcmdline, int ncmdshow)
{
	//first fill in the window class structure
	winclass.style			= CS_DBLCLKS | CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
	winclass.lpfnWndProc	= WindowProc;
	winclass.cbClsExtra		= 0;
	winclass.cbWndExtra		= 0;
	winclass.hInstance		= hinstance;
	winclass.hIcon			= LoadIcon(hinstance, MAKEINTRESOURCE(IDI_ICON1));
	winclass.hCursor		= LoadCursor(NULL, IDC_ARROW);
	winclass.hbrBackground	= (HBRUSH)GetStockObject(BLACK_BRUSH);
	winclass.lpszMenuName	= NULL; 
	winclass.lpszClassName	= CLASSNAME;

	//save the hInstance
	hInstance = hinstance;

	//start up the console window
	#ifdef _DEBUG
	RedirectIOToConsole();
	#endif

	//register the window class
	if(!RegisterClass(&winclass))
		return(0);

	//create the window
	if(!(hWnd = CreateWindow(	
		CLASSNAME,													//class Name.
		CLASSNAME,													//title of the Window.
		WS_OVERLAPPEDWINDOW | WS_VISIBLE,							//window Flags
		GetSystemMetrics(SM_CXSCREEN) - WINDOW_WIDTH,				//window Start Point (lower right corner) 
		GetSystemMetrics(SM_CYSCREEN) - (WINDOW_HEIGHT + 32),
		WINDOW_WIDTH,												//width of Window.
		WINDOW_HEIGHT,												//height of Window.
		NULL,														//handle to parent.
		NULL,														//handle to menu.
		hinstance,													//application Instance.
		NULL)))														//creation params.
		return(0);

	//seed random
	srand((unsigned)time(0));

	hThreadGameUpdate = (HANDLE)_beginthreadex(NULL, 0, ThreadGameUpdate, 0, 0,  (unsigned int *)&hThreadGameUpdate);

	Sleep(10);

	hThreadWorldUpdate = (HANDLE)_beginthreadex(NULL, 0, ThreadWorldUpdate, 0, 0,  (unsigned int *)&hThreadWorldUpdate);

	Sleep(10);

	//enter main event loop
	while(true)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{ 
			//test if this is a quit
			if (msg.message == WM_QUIT)
			{
				break;
			}

			//translate any accelerator keys
			TranslateMessage(&msg);

			//send the message to the window proc
			DispatchMessage(&msg);
		}

		if(nThreadGameStatus == 0)
		{
			CloseHandle(hThreadGameUpdate);
			CloseHandle(hThreadWorldUpdate);
			break;
		}
		else if(nThreadWorldStatus == 0)
		{
			CloseHandle(hThreadGameUpdate);
			CloseHandle(hThreadWorldUpdate);
			break;
		}
	}

	//Return to Windows like this
	return (int)(msg.wParam);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		RedirectIOToConsole
//
//	Purpose:		console window redirect function 
//
//////////////////////////////////////////////////////////////////////////
#ifdef _DEBUG
void RedirectIOToConsole()
{
	long hConHandle;
	long lStdHandle;
	CONSOLE_SCREEN_BUFFER_INFO coninfo;
	FILE *fp;

	//allocate a console for this app
	AllocConsole();

	//set the screen buffer to be big enough to let us scroll text
	GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),	&coninfo);

	coninfo.dwSize.Y = MAX_CONSOLE_LINES;

	SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE),	coninfo.dwSize);

	//redirect unbuffered STDOUT to the console
	lStdHandle = PtrToUlong(GetStdHandle(STD_OUTPUT_HANDLE));

	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen(hConHandle, "w");

	*stdout = *fp;

	setvbuf(stdout, NULL, _IONBF, 0);

	//redirect unbuffered STDIN to the console
	lStdHandle = PtrToUlong(GetStdHandle(STD_INPUT_HANDLE));

	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen(hConHandle, "r");

	*stdin = *fp;

	setvbuf(stdin, NULL, _IONBF, 0);

	//redirect unbuffered STDERR to the console
	lStdHandle = PtrToUlong(GetStdHandle(STD_ERROR_HANDLE));

	hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);

	fp = _fdopen(hConHandle, "w");

	*stderr = *fp;

	setvbuf( stderr, NULL, _IONBF, 0);

	//make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog work!
	ios::sync_with_stdio();
}
#endif

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		ThreadGameUpdate
//
//	Purpose:		this is the thread for the game update
//
//////////////////////////////////////////////////////////////////////////
unsigned int __stdcall ThreadGameUpdate(void *pData)
{
	//pointer to the CSimpleMain singleton
	CSimpleMain	*g_pSimple = CSimpleMain::GetInstance();

	//status
	nThreadGameStatus = 1;

	//initialize the CSimpleMain singleton
	g_pSimple->InitCSimpleMain(hWnd, hInstance, WINDOW_WIDTH, WINDOW_HEIGHT, true);

	//some more init lovin
	g_pSimple->Inits();

	//enter main event loop
	while(true)
	{
		//if update returns false, exit the loop
		if(g_pSimple->UpdateCSimpleMain() == false)
		{
			break;
		}
	}

	//clean up time!
	g_pSimple->ShutDowns();

	nThreadGameStatus = 0;

	_endthreadex(0);
	return 0;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		ThreadWorldUpdate
//
//	Purpose:		this is the thread for the world update
//
//////////////////////////////////////////////////////////////////////////
unsigned int __stdcall ThreadWorldUpdate(void *pData)
{
	//pointer to the CSimpleMain singleton
	WorldGod *pWorldGod = WorldGod::GetInstance();

	//status
	nThreadWorldStatus = 1;

	//initialize the WorldGod singleton
	pWorldGod->Init();

	//enter main event loop
	while(true)
	{
		//if update returns false, exit the loop
		//false basically means something went bad
		//and we need to close the app
		if(pWorldGod->Update() == false)
		{
			break;
		}
	}

	//clean up time!
	pWorldGod->Shutdown();

	nThreadWorldStatus = 0;

	_endthreadex(0);
	return 0;
}