//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	SimpleMain.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	CSimpleMain is the main part of this Simple Shell program
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include <Windows.h>
#include <stdio.h>
#include "Helpers.h"	//some helpful defines
#include "Direct3D.h"
#include "TextureManager.h"
#include "DirectInput.h"
#include "SpriteManager.h"
#include "BaseFrame.h"
#include "Timer.h"
#include "AnimationManager.h"
#include "BMPFont.h"
#include "Terrain.h"
#include "Camera.h"
#include "NewTerrain.h"
#include "BlockObject.h"
#include "World.h"

const int blocksize = 8;

class CSimpleMain  
{
private:
		BlockObject testblock1;
	BlockObject testblock2;
	BlockObject testblock3;
	BlockObject testblock[blocksize][blocksize][blocksize];
	D3DXMATRIX			m_matProjection;
	float				m_fAspectRatio;
	float				m_fFieldOfView;
	float				m_fNearPlane;
	float				m_fFarPlane;

	HWND				m_hWnd;

	World				*m_pWorld;
	CBaseFrame			m_Base;
	CDirectX9			*m_pDirect3D;		//pointer to the d3d singleton
	CTextureManager		*m_pTextureManager;	//pointer to the texture manager singleton
	CDirectInput		*m_pDirectInput;	//pointer to the direct input singleton
	CSpriteManager		*m_pSpriteManager;	//pointer to the sprite manager singleton
	Timer				*m_pTimer;
	CAnimationManager	*m_pAnimationManager;	
	CBMPFont			*m_pBMPFont;
	CCamera				*m_pCamera;
	CTerrain			*m_pTerrain;

	NewTerrain			*m_pNewTerrain;

	double				m_fTickFPS;
	double				m_fTimer;

	bool				m_bWireframe;

	D3DLIGHT9			m_Light;						//direction light (like a sun)
	D3DLIGHT9			m_LavaLight01;					//direction light (like a sun)
	D3DLIGHT9			m_LavaLight02;					//direction light (like a sun)

	static	CSimpleMain	*m_pinstance;			//instance to the singleton	

	int nBMP;

	CSimpleMain(){};
	~CSimpleMain(){};
	CSimpleMain(const CSimpleMain &a){};
	CSimpleMain &operator=(const CSimpleMain &a){};

public:

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetInstance
	//
	//	Last Modified: 	10/04/2006
	//
	//	Purpose:		Creates the first instance and returns it's address.
	//
	//////////////////////////////////////////////////////////////////////////
	static CSimpleMain *GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DeleteInstance
	//
	//	Last Modified: 	10/04/2006
	//
	//	Purpose:		Delete the instance, and set the pointer to NULL
	//
	//////////////////////////////////////////////////////////////////////////
	static void DeleteInstance();

	void SetStates();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitCSimpleMain
	//
	//	Last Modified: 	10/04/2006
	//
	//	Purpose:		Initializes the Simple shell module
	//
	//////////////////////////////////////////////////////////////////////////
	void InitCSimpleMain(HWND hWnd, HINSTANCE hInstance, int nWidth, int nHeight, bool bWindowed, bool bVsync = false);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		UpdateCSimpleMain
	//
	//	Last Modified: 	10/04/2006
	//
	//	Purpose:		Updates all the modules each frame
	//
	//	Notes:			if this returns false the program will quit
	//
	//////////////////////////////////////////////////////////////////////////
	bool UpdateCSimpleMain();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Inits
	//
	//	Last Modified: 	10/04/2006
	//
	//	Purpose:		All the inits
	//
	//////////////////////////////////////////////////////////////////////////
	void Inits();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Uodates
	//
	//	Last Modified: 	10/04/2006
	//
	//	Purpose:		All the updates
	//
	//////////////////////////////////////////////////////////////////////////
	bool Updates();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Draws
	//
	//	Last Modified: 	10/04/2006
	//
	//	Purpose:		All the drawing
	//
	//////////////////////////////////////////////////////////////////////////
	bool Draws();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Shutdown
	//
	//	Last Modified: 	10/04/2006
	//
	//	Purpose:		Shuts down CSimpleMain class
	//
	//////////////////////////////////////////////////////////////////////////
	void ShutDowns();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Inputs
	//
	//	Last Modified: 	10/04/2006
	//
	//	Purpose:		All input checking happens here
	//
	//////////////////////////////////////////////////////////////////////////
	bool Inputs();

	void SetDefaultLights();
};