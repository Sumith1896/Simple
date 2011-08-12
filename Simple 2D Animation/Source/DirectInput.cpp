//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	DirectInput.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the input system
//
//////////////////////////////////////////////////////////////////////////
#include "DirectInput.h"

//	Initialize the static variable member.
CDirectInput *CDirectInput::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Constructor
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		you know what this does =p
//
//////////////////////////////////////////////////////////////////////////
CDirectInput::CDirectInput()
{
	m_pDIObject			= NULL;
	m_pDIKey			= NULL;
	m_pDIMouse			= NULL;
	m_dwAxes			= 0;
	m_dwButtons			= 0;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Delete the instance of the class, and set the pointer to NULL
//
//////////////////////////////////////////////////////////////////////////
void CDirectInput::DeleteInstance()
{
	SAFE_DELETE(m_pInstance);
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
CDirectInput *CDirectInput::GetInstance()
{
	if(!m_pInstance)
		m_pInstance = new CDirectInput;

	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitDirectInput
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Initializes the input class (keyboard & mouse)
//
//////////////////////////////////////////////////////////////////////////
bool CDirectInput::InitDirectInput(HWND hWnd, HINSTANCE hInstance, bool bExclusive)
{
	//	Make sure DirectInput, the mouse or keyboard hasn't already been initialized.
	if(m_pDIObject || m_pDIMouse || m_pDIKey)	
		return false;

	//	Initialize the Direct Input COM object.
	if(FAILED(DirectInput8Create(hInstance, DIRECTINPUT_VERSION, IID_IDirectInput8, (void**)&m_pDIObject, NULL)))
	{
		return false;
	}

	//	Create the Mouse Device.
	m_pDIObject->CreateDevice(GUID_SysMouse, &m_pDIMouse, NULL);

	//	Set the Cooperative Level for the Mouse.
	if(bExclusive)
		m_pDIMouse->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	else
		m_pDIMouse->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);


	//	Set the Data format for the mouse.
	m_pDIMouse->SetDataFormat(&c_dfDIMouse2);

	//	Acquire the mouse.
	m_pDIMouse->Acquire();

	//device capabilities
	DIDEVCAPS MouseCaps;

	MouseCaps.dwSize = sizeof(DIDEVCAPS);

	//get the mouse caps
	m_pDIMouse->GetCapabilities(&MouseCaps);

	//save the button and axes count
	m_dwAxes = MouseCaps.dwAxes;
	m_dwButtons = MouseCaps.dwButtons;

	//	Create the Keyboard Device.
	m_pDIObject->CreateDevice(GUID_SysKeyboard, &m_pDIKey, NULL);

	//	Set the Cooperative level for the keyboard.
	if (bExclusive)
		m_pDIKey->SetCooperativeLevel(hWnd, DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	else
		m_pDIKey->SetCooperativeLevel(hWnd, DISCL_BACKGROUND | DISCL_NONEXCLUSIVE);

	//Set the Data Format for the keyboard.
	m_pDIKey->SetDataFormat(&c_dfDIKeyboard);

	//Acquire the Keyboard.
	m_pDIKey->Acquire();

	//	Return Success.
	return true;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Shutdown
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Shuts down the Input objects
//
//////////////////////////////////////////////////////////////////////////
void CDirectInput::Shutdown(void)
{
	//Release the Mouse.
	if(m_pDIMouse)
	{
		m_pDIMouse->Unacquire();
		SAFE_RELEASE(m_pDIMouse);
	}

	//Release the Keyboard
	if(m_pDIKey)
	{
		m_pDIKey->Unacquire();
		SAFE_RELEASE(m_pDIKey);
	}

	//Release the Direct Input Device.
	SAFE_RELEASE(m_pDIObject);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		ReadInput
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Reads the keyboard and mouse
//
//////////////////////////////////////////////////////////////////////////
bool CDirectInput::ReadInput(void)
{
	//copy the old data to the keyboard buffer
	memcpy(m_KeyBuffered, m_KeyBuffer, 256 * sizeof(char));

	//copy old data into the mouse buffer
	memcpy(m_MouseBuffered, m_diMouseState.rgbButtons, 8 * sizeof(char));

	//acquire the keyboard
	m_pDIKey->Acquire();

	//get the keyboard state
	m_pDIKey->GetDeviceState(sizeof(m_KeyBuffer), (LPVOID)&m_KeyBuffer);

	//acquire the mouse
	m_pDIMouse->Acquire();

	//get the mouse state
	m_pDIMouse->GetDeviceState(sizeof(m_diMouseState), (LPVOID)&m_diMouseState);

	//Return Success.
	return true;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		KeyPressed
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Checks if the key was pushed
//
//////////////////////////////////////////////////////////////////////////
bool CDirectInput::GetKeyPressed(int Key)
{
	//Check to see if the key was pressed.
	if (m_KeyBuffer[Key] & 0x80)
		return true;

	//The Key was not Pressed.
	return false;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		KeyPressed
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Checks if the key was pushed
//
//////////////////////////////////////////////////////////////////////////
bool CDirectInput::GetKeyPressedBuffered(int Key)
{
	//check to see if it was checked before
	if(m_KeyBuffered[Key] & 0x80)
		return false;

	//Check to see if the key was pressed.
	if (m_KeyBuffer[Key] & 0x80)
		return true;

	//The Key was not Pressed.
	return false;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetMouseButton
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Checks if the mouse button was pushed
//
//////////////////////////////////////////////////////////////////////////
bool CDirectInput::GetMouseButton(int Button)
{
	//	Check to see if the Mouse Button was pressed.
	if (m_diMouseState.rgbButtons[Button] & 0x80)
		return true;

	//	Button Not Pressed.
	return false;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetMouseButtonBuffered
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Checks if the mouse button was pushed (buffered)
//
//////////////////////////////////////////////////////////////////////////
bool CDirectInput::GetMouseButtonBuffered(int Button)
{
	//Check to see if the Mouse Button was pressed before.
	if(m_MouseBuffered[Button] & 0x80)
		return false;

	//Check to see if the key was pressed.
	if(m_diMouseState.rgbButtons[Button] & 0x80)
		return true;

	//Button Not Pressed.
	return false;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetMouseAxis
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Return the value from an axis
//
//////////////////////////////////////////////////////////////////////////
long CDirectInput::GetMouseAxis(long lAxis)
{
	//Check the Axis and return its state.
	switch (lAxis)
	{
	case XAXIS:
		{
			return m_diMouseState.lX;
			break;
		}
	case YAXIS:
		{
			return m_diMouseState.lY;
			break;
		}
	case ZAXIS:
		{
			return m_diMouseState.lZ;
			break;
		}
	};

	return 0;
}