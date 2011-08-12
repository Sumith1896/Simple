//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	Camera.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the camera
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Direct3D.h"
#include "Helpers.h"
#include "DirectInput.h"
#include "Timer.h"

class CCamera
{
private:

	CTimer						*m_pTimer;				//timer pointer
	CDirectX9					*m_pDirectX;			//directx9 pointer
	CDirectInput				*m_pDirectInput;		//directinput pointer

	
	D3DXVECTOR3					m_vEyePt;				//where the eye is in the world
	D3DXVECTOR3					m_vLookAtPt;			//at vector
	D3DXVECTOR3					m_vUp;					//up vector
	D3DXVECTOR3					m_vDirection;			//direction to move

	D3DXMATRIX					m_matView;				//the view matrix

	float						m_fSpeed;
	float						m_fDistance;

	static CCamera				*m_pinstance;			//instance to the singleton	

	CCamera(){};
	CCamera(const CCamera &a){};
	CCamera &operator=(const CCamera &a){};

public:

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
	static CCamera *GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitCamera
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the camera class
	//
	//////////////////////////////////////////////////////////////////////////
	void InitCamera();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitCamera
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the camera class
	//
	//////////////////////////////////////////////////////////////////////////
	void Update();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Move
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		moves the camera based on keyboard input
	//
	//////////////////////////////////////////////////////////////////////////
	void Move();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Rotate
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		rotate the camera based on mouse input (mouse-look)
	//
	//////////////////////////////////////////////////////////////////////////
	void Rotate();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Inline Functions
	//
	//	Last Modified: 	2006/01/15
	//
	//	Purpose:		Inline functions to get camera information. 
	//
	//////////////////////////////////////////////////////////////////////////
	inline D3DXVECTOR3	*GetEye(){return &m_vEyePt;}
	inline D3DXVECTOR3	*GetDirection(){return &m_vDirection;}
	inline D3DXMATRIX	*GetViewMatrix(){return &m_matView;}
};
