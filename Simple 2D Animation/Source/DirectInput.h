//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	DirectInput.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the input system
//
//////////////////////////////////////////////////////////////////////////
#pragma once

//tell directx what version we want...
#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#include "Helpers.h"

#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

class CDirectInput
{
private:

	LPDIRECTINPUT8 			m_pDIObject;				//	Direct Input Object.
	LPDIRECTINPUTDEVICE8	m_pDIKey;					//	Direct Input Device for the Keyboard.
	LPDIRECTINPUTDEVICE8	m_pDIMouse;					//	Direct Input Device for the Mouse.

	DIMOUSESTATE2			m_diMouseState;				//holds mouse info
	DWORD					m_dwAxes;					//number of mouse axes
	DWORD					m_dwButtons;				//number of mouse buttons
	char					m_KeyBuffer[256];			//used for keyboard buffering
	char					m_KeyBuffered[256];			//used for keyboard buffering
	char					m_MouseBuffered[8];			//used for buffered mouse input

	static CDirectInput *m_pInstance;					//	The instance of this class.

	//Constructor, copy constructor and assignment operator... all in private... ZOMG!!!  
	CDirectInput();
	CDirectInput(const CDirectInput &a){};
	CDirectInput &operator=(const CDirectInput &a){};

public:

	//	Destructor.
	virtual ~CDirectInput(){};

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
	static CDirectInput *GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Shutdown
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the input class
	//
	//////////////////////////////////////////////////////////////////////////
	void Shutdown(void);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitDirectInput
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the input class (keyboard & mouse)
	//
	//////////////////////////////////////////////////////////////////////////
	bool InitDirectInput(HWND hWnd, HINSTANCE hInstance, bool bExclusive);


	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		ReadInput
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the input class
	//
	//////////////////////////////////////////////////////////////////////////
	bool ReadInput(void);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		KeyPressed
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Checks to see if that key was pressed
	//
	//////////////////////////////////////////////////////////////////////////
	bool GetKeyPressed(int Key);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		KeyPressed
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Checks to see if that key was pressed
	//
	//////////////////////////////////////////////////////////////////////////
	bool GetKeyPressedBuffered(int Key);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetMouseButton
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the input class
	//
	//////////////////////////////////////////////////////////////////////////
	bool GetMouseButton(int Button);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetMouseButtonBuffered
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the input class
	//
	//////////////////////////////////////////////////////////////////////////
	bool GetMouseButtonBuffered(int Button);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetMouseAxis
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Return the value from an axis
	//
	//////////////////////////////////////////////////////////////////////////
	long CDirectInput::GetMouseAxis(long lAxis);
};
