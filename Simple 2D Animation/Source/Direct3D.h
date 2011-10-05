//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	DirectX9.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the directx device, object, present and caps
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include <windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include <iostream>
#include <fstream>
#include "Helpers.h"
using namespace std;

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dxguid.lib")

class CACHE_ALIGN CDirectX9
{
private:

	bool					m_bWindowed;			//true if in a window, false for fullscreen
	int						m_nGammaRamp;			//current gamma level
	int						m_nWidth;				//width of buffer
	int						m_nHeight;				//height of buffer
	static CDirectX9		*m_pInstance;			//Static instance of this class.
	IDirect3D9				*m_d3dObj;				//the Direct3D Object.
	ID3DXSprite				*m_d3dSprite;			//Sprite Object
	IDirect3DDevice9		*m_d3dDevice;			//the Direct3D Device Object.
	HWND					m_hWnd;					//the main window Handle.
	D3DPRESENT_PARAMETERS	m_d3dPresent;			//structure to setup D3D.
	D3DCAPS9				m_d3dCaps;				//structure of device capabilities
	D3DGAMMARAMP			d3dGamma;				//current gamma

	//constructor, copy constructor, destructor and = operator all in teh private!!!
	CDirectX9(){};
	CDirectX9(const CDirectX9 &a){};
	CDirectX9 &operator=(const CDirectX9 &a){};
	~CDirectX9(){};

public:

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Inline Functions
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		Inline functions to get D3D information. 
	//
	//////////////////////////////////////////////////////////////////////////
	inline IDirect3D9*				GetD3DObject()	{ return m_d3dObj;		}
	inline IDirect3DDevice9*		GetD3DDevice()	{ return m_d3dDevice;	}
	inline ID3DXSprite*				GetD3DSprite()	{ return m_d3dSprite;	}
	inline D3DPRESENT_PARAMETERS	GetParameters() { return m_d3dPresent;	}

	inline int	GetDisplayWidth()	{ return m_nWidth;		}
	inline int	GetDisplayHeight()	{ return m_nHeight;		}
	inline bool	GetWindowed()		{ return m_bWindowed;	}
	inline HWND	GetDisplayHWnd()	{ return m_hWnd;		}

	inline bool Clear()
	{
		//make sure the Device is valid.
		if(!m_d3dDevice)
			return false;

		//clear the BackBuffer.
		m_d3dDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_XRGB(0, 0, 0), 1.0f, 0);

		//check for lost focus, or some other "bad" stuff
		if(m_d3dDevice->TestCooperativeLevel() == D3DERR_DEVICENOTRESET)
		{
			m_d3dSprite->OnLostDevice();
			m_d3dDevice->Reset(&m_d3dPresent);
			m_d3dSprite->OnResetDevice();
		}

		//return Success.
		return true;
	}

	inline bool Begin3D()
	{
		//begin drawing the 3d objects
		if(FAILED(m_d3dDevice->BeginScene()))
			return false;

		return true;
	}

	inline bool BeginSprite()
	{
		//begin drawing the sprite objects
		if(FAILED(m_d3dSprite->Begin(D3DXSPRITE_SORT_DEPTH_FRONTTOBACK)))
			return false;

		return true;
	}

	inline bool EndScene()
	{
		//Stop the drawing state.
		if(FAILED(m_d3dSprite->End()))
			return false;

		//Stop the drawing State.
		if(FAILED(m_d3dDevice->EndScene()))
			return false;

		//	Return Success.
		return true;
	}

	inline void Present()
	{
		m_d3dDevice->Present(NULL, NULL, NULL, NULL);
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
	static CDirectX9 *GetInstance();

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
	//	Function: 		InitDirectX9
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		Initialize DirectX9 
	//
	//////////////////////////////////////////////////////////////////////////
	bool InitDirectX9(HWND hWnd, unsigned const int &nWidth, unsigned const int &nHeight, bool bWindowed, bool bVSync);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		ShutdownDirectX9
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		Shuts down DirectX9
	//
	//////////////////////////////////////////////////////////////////////////
	void ShutdownDirectX9(void);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		CheckDevCaps
	//
	//	Last Modified: 	03/07/2007
	//
	//	Purpose:		Checks to see if the device supports a feature
	//
	//////////////////////////////////////////////////////////////////////////
	bool CheckDevCaps(int nCap);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		CheckCaps
	//
	//	Last Modified: 	03/07/2007
	//
	//	Purpose:		Checks to see if the driver supports a feature
	//
	//////////////////////////////////////////////////////////////////////////
	bool CheckCaps(int nCap);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		CheckCaps2
	//
	//	Last Modified: 	03/07/2007
	//
	//	Purpose:		Checks to see if the driver supports a feature
	//
	//////////////////////////////////////////////////////////////////////////
	bool CheckCaps2(int nCap);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		CheckCaps3
	//
	//	Last Modified: 	03/07/2007
	//
	//	Purpose:		Checks to see if the driver supports a feature
	//
	//////////////////////////////////////////////////////////////////////////
	bool CheckCaps3(int nCap);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		CheckCapsTextureFiltering
	//
	//	Last Modified: 	03/07/2007
	//
	//	Purpose:		Checks to see if the texture filtering is supported
	//
	//////////////////////////////////////////////////////////////////////////
	bool CheckCapsTextureFiltering(int nCap);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		LoadVertexShader
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		Loads a vertex shader from a vertex assemble file
	//
	//////////////////////////////////////////////////////////////////////////
	void LoadVertexShader( char* strShader, IDirect3DVertexShader9* hShader );

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		LoadPixelShader
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		Loads a pixel shader from a vertex assemble file
	//
	//////////////////////////////////////////////////////////////////////////
	void LoadPixelShader( char* strShader, IDirect3DPixelShader9* hShader );

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		TakeScreenShot
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		saves the current screen as a file(screenshot)
	//
	//					    D3DXIFF_BMP         = 0,
	//						D3DXIFF_JPG         = 1,
	//						D3DXIFF_TGA         = 2,
	//						D3DXIFF_PNG         = 3,
	//						D3DXIFF_DDS         = 4,
	//						D3DXIFF_PPM         = 5,
	//						D3DXIFF_DIB         = 6,
	//						high dynamic range formats
	//						D3DXIFF_HDR         = 7,       
	//						D3DXIFF_PFM         = 8,   
	//
	//////////////////////////////////////////////////////////////////////////
	void TakeScreenShot(char* szFileName, int nWidth, int nHeight, D3DXIMAGE_FILEFORMAT nFormat);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		ResetGamma
	//
	//	Last Modified: 	03/07/2007
	//
	//	Purpose:		resets the gamma back to the deault levels
	//
	//////////////////////////////////////////////////////////////////////////
	void GammaReset();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GammaUp
	//
	//	Last Modified: 	03/07/2007
	//
	//	Purpose:		sets the gamma value down
	//
	//////////////////////////////////////////////////////////////////////////
	void GammaUp();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GammaDown
	//
	//	Last Modified: 	03/07/2007
	//
	//	Purpose:		sets the gamma value down
	//
	//////////////////////////////////////////////////////////////////////////
	void GammaDown();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		CheckMultiSample
	//
	//	Last Modified: 	03/07/2007
	//
	//	Purpose:		checks if the display device supports that type 
	//					of multisampling
	//
	//////////////////////////////////////////////////////////////////////////
	bool CheckMultiSample(D3DMULTISAMPLE_TYPE d3dMultiSampleType);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		ChangeDisplay
	//
	//	Last Modified: 	03/07/2007
	//
	//	Purpose:		changes the settings of the display
	//
	//					D3DMULTISAMPLE_NONE	
	//					D3DMULTISAMPLE_2_SAMPLES
	//					D3DMULTISAMPLE_4_SAMPLES
	//					D3DMULTISAMPLE_6_SAMPLES
	//
	//					D3DTEXF_NONE
	//					D3DTEXF_POINT
	//					D3DTEXF_LINEAR
	//					D3DTEXF_ANISOTROPIC
	//
	//	Notes:			nAniso can only be between 1 - 16
	//					the higher the value the "better" the filtering
	//
	//////////////////////////////////////////////////////////////////////////
	void ChangeMode(const unsigned int &nWidth, const unsigned int &nHeight, bool bWindowed, D3DMULTISAMPLE_TYPE d3dMultiSampleType, D3DTEXTUREFILTERTYPE d3dTextureFiltering, unsigned int nAniso);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		SaveSettings
	//
	//	Last Modified: 	03/07/2007
	//
	//	Purpose:		saves the video settings
	//
	//////////////////////////////////////////////////////////////////////////
	void SaveSettings();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		SaveSettings
	//
	//	Last Modified: 	03/07/2007
	//
	//	Purpose:		saves the video settings
	//
	//////////////////////////////////////////////////////////////////////////
	void LoadSettings();

};

