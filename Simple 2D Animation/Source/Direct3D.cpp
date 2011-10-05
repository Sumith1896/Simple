//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	DirectX9.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the directx device, object, present and caps
//
//////////////////////////////////////////////////////////////////////////
#include "Direct3D.h"

//Initialize the static member variable.
CDirectX9 *CDirectX9::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetInstance
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Creates the first instance of this class and returns it's address.
//
//////////////////////////////////////////////////////////////////////////
CDirectX9 *CDirectX9::GetInstance()
{
	//Check to see if one hasn't been made yet.
	if (!m_pInstance)
		m_pInstance = new CDirectX9;

	//Return the address of the instance.
	return m_pInstance;
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
void CDirectX9::DeleteInstance()
{
	//safely delete the instance pointer
	SAFE_DELETE(m_pInstance);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitDirectX9
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Initialize DirectX9 
//
//////////////////////////////////////////////////////////////////////////
bool CDirectX9::InitDirectX9(HWND hWnd, unsigned const int &nWidth, unsigned const int &nHeight, bool bWindowed, bool bVSync)
{
	//	Make sure the hWnd is valid.
	if(!hWnd)
		return false;

	//load some defaults
	m_nWidth	= 1024;
	m_nHeight	= 768;
	m_bWindowed = 0;

	//load settings from config file
	LoadSettings();

	m_hWnd		= hWnd;
	m_nGammaRamp= 0;

	//set the default gamma levels
	for(int i = 0; i < 256; i++) 
	{ 
		d3dGamma.red[i]		= (257 * i);
		d3dGamma.green[i]	= (257 * i); 
		d3dGamma.blue[i]	= (257 * i); 
	}

	//create the directx object using the latest SDK version installed
	m_d3dObj = Direct3DCreate9(D3D_SDK_VERSION);

	//make sure the object was created successfully
	if(!m_d3dObj)
		return false;

	//set the device capabilities
	memset(&m_d3dCaps, 0, sizeof(m_d3dCaps));

	// get our device caps
	m_d3dObj->GetDeviceCaps(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, &m_d3dCaps);

	//Setup the parameters for using Direct3D.
	memset(&m_d3dPresent, 0, sizeof(m_d3dPresent));

	m_d3dPresent.BackBufferWidth			= m_nWidth;
	m_d3dPresent.BackBufferHeight			= m_nHeight;
	m_d3dPresent.BackBufferFormat			= (m_bWindowed) ? D3DFMT_UNKNOWN : D3DFMT_X8R8G8B8;
	m_d3dPresent.BackBufferCount			= 2;
	m_d3dPresent.MultiSampleType			= D3DMULTISAMPLE_NONE;
	m_d3dPresent.MultiSampleQuality			= 0;

	//check to see if the device can do alpha at fullscreen
	if(m_d3dCaps.DevCaps & D3DCAPS3_ALPHA_FULLSCREEN_FLIP_OR_DISCARD)
	{
		m_d3dPresent.SwapEffect				= D3DSWAPEFFECT_DISCARD;
	}
	else
	{
		m_d3dPresent.SwapEffect				= D3DSWAPEFFECT_COPY;
	}

	m_d3dPresent.hDeviceWindow				= m_hWnd;
	m_d3dPresent.Windowed					= m_bWindowed;
	m_d3dPresent.EnableAutoDepthStencil		= true;
	m_d3dPresent.AutoDepthStencilFormat		= D3DFMT_D24X8;
	m_d3dPresent.FullScreen_RefreshRateInHz	= (m_bWindowed) ? 0 : 60;
	m_d3dPresent.Flags						= D3DPRESENTFLAG_LOCKABLE_BACKBUFFER;
	m_d3dPresent.PresentationInterval		= D3DPRESENT_INTERVAL_IMMEDIATE;

	//check to see if hardware vertex processing is supported
	if(m_d3dCaps.DevCaps & D3DDEVCAPS_HWTRANSFORMANDLIGHT)
	{
		//Create the Direct3D Device with hardware TnL.
		if (FAILED(m_d3dObj->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &m_d3dPresent, &m_d3dDevice)))
		{
			return false;
		}
	}
	else
	{
		//Create the Direct3D Device with software TnL.
		if (FAILED(m_d3dObj->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, m_hWnd, D3DCREATE_SOFTWARE_VERTEXPROCESSING, &m_d3dPresent, &m_d3dDevice)))
		{
			return false;
		}
	}

	//	Create Sprite Object.
	D3DXCreateSprite(m_d3dDevice, &m_d3dSprite);

	//check to see if ranged bases vertex fog is supported
	if(m_d3dCaps.DevCaps & D3DPRASTERCAPS_FOGRANGE)
	{
		float fFogStart = 0.0f;
		float fFogEnd	= 25000.0f;

		m_d3dDevice->SetRenderState(D3DRS_FOGENABLE,true);
		m_d3dDevice->SetRenderState(D3DRS_RANGEFOGENABLE,true);
		m_d3dDevice->SetRenderState(D3DRS_FOGCOLOR,D3DCOLOR_XRGB(0,0,0));
		m_d3dDevice->SetRenderState(D3DRS_FOGVERTEXMODE, D3DFOG_LINEAR);
		m_d3dDevice->SetRenderState(D3DRS_FOGSTART,*(DWORD*)(&fFogStart));
		m_d3dDevice->SetRenderState(D3DRS_FOGEND,*(DWORD*)(&fFogEnd));
	}

	//adjust the window the new resolution
	SetWindowPos
		(
		m_hWnd, 
		HWND_TOP,	
		(GetSystemMetrics(SM_CXSCREEN)>>1) - (m_nWidth>>1),
		(GetSystemMetrics(SM_CYSCREEN)>>1) - (m_nHeight>>1),
		m_nWidth, 
		m_nHeight, 
		SWP_SHOWWINDOW);

	//Return Success.
	return true;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		ShutdownDirectX9
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Shuts down DirectX9
//
//////////////////////////////////////////////////////////////////////////
void CDirectX9::ShutdownDirectX9(void)
{
	SaveSettings();

	//release all directx objects
	SAFE_RELEASE(m_d3dDevice);
	SAFE_RELEASE(m_d3dObj);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		CheckDevCaps
//
//	Last Modified: 	03/07/2007
//
//	Purpose:		Checks to see if the device supports a feature
//
//////////////////////////////////////////////////////////////////////////
bool CDirectX9::CheckDevCaps(int nCap)
{
	if(m_d3dCaps.DevCaps & nCap)
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		CheckCaps
//
//	Last Modified: 	03/07/2007
//
//	Purpose:		Checks to see if the driver supports a feature
//
//////////////////////////////////////////////////////////////////////////
bool CDirectX9::CheckCaps(int nCap)
{
	if(m_d3dCaps.Caps & nCap)
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		CheckCaps2
//
//	Last Modified: 	03/07/2007
//
//	Purpose:		Checks to see if the driver supports a feature
//
//////////////////////////////////////////////////////////////////////////
bool CDirectX9::CheckCaps2(int nCap)
{
	if(m_d3dCaps.Caps2 & nCap)
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		CheckCaps3
//
//	Last Modified: 	03/07/2007
//
//	Purpose:		Checks to see if the driver supports a feature
//
//////////////////////////////////////////////////////////////////////////
bool CDirectX9::CheckCaps3(int nCap)
{
	if(m_d3dCaps.Caps3 & nCap)
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		CheckCapsTextureFiltering
//
//	Last Modified: 	03/07/2007
//
//	Purpose:		Checks to see if the texture filtering is supported
//
//////////////////////////////////////////////////////////////////////////
bool CDirectX9::CheckCapsTextureFiltering(int nCap)
{
	if(m_d3dCaps.TextureFilterCaps & nCap)
		return true;
	else
		return false;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		LoadVertexShader
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Loads a vertex shader from a vertex assemble file
//
//////////////////////////////////////////////////////////////////////////
void CDirectX9::LoadVertexShader( char* strShader, IDirect3DVertexShader9* hShader )
{
	ID3DXBuffer *pShaderBuf = NULL;
	HRESULT hr;

	hr = D3DXAssembleShaderFromFile( strShader, NULL, NULL, 0, &pShaderBuf, NULL);
	if( SUCCEEDED( hr ) )
		if( pShaderBuf )
			hr = m_d3dDevice->CreateVertexShader((DWORD*)pShaderBuf->GetBufferPointer(), &hShader);

	SAFE_RELEASE( pShaderBuf );
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		LoadPixelShader
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Loads a pixel shader from a vertex assemble file
//
//////////////////////////////////////////////////////////////////////////
void CDirectX9::LoadPixelShader( char* strShader, IDirect3DPixelShader9* hShader )
{
	ID3DXBuffer *pShaderBuf = NULL;
	HRESULT hr;

	hr = D3DXAssembleShaderFromFile( strShader, NULL, NULL, 0, &pShaderBuf, NULL);
	if( SUCCEEDED( hr ) )
		if( pShaderBuf ) 
			hr = m_d3dDevice->CreatePixelShader( (DWORD*)pShaderBuf->GetBufferPointer(), &hShader );

	SAFE_RELEASE( pShaderBuf );
}

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
void CDirectX9::TakeScreenShot(char* szFileName, int nWidth, int nHeight, D3DXIMAGE_FILEFORMAT nFormat)
{
	//surface to hold our screenshot data
	LPDIRECT3DSURFACE9 d3dFrontBuffer = NULL;

	//saves the data from the front buffer to the surface we made
	m_d3dDevice->GetBackBuffer(0, 0, D3DBACKBUFFER_TYPE_MONO, &d3dFrontBuffer);

	//output our surface to a file
	D3DXSaveSurfaceToFile(szFileName, nFormat, d3dFrontBuffer, NULL, NULL);

	//release the surface
	SAFE_RELEASE(d3dFrontBuffer);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GammaUp
//
//	Last Modified: 	03/07/2007
//
//	Purpose:		sets the gamma value up
//
//////////////////////////////////////////////////////////////////////////
void CDirectX9::GammaUp()
{
	m_nGammaRamp += 256; 

	//check to see if fullscreen gamma is supported
	if(!CheckCaps2(D3DCAPS2_FULLSCREENGAMMA))
		return;

	for(int i = 0; i < 256; i++) 
	{ 
		int tempColor;

		tempColor	= (m_nGammaRamp + (256 * i));

		if(tempColor > 65535)
			tempColor = 65535;

		if(tempColor < 0)
			tempColor = 0;

		d3dGamma.red[i]		= tempColor;
		d3dGamma.green[i]	= tempColor; 
		d3dGamma.blue[i]	= tempColor; 
	}

	//set the new gamma
	if(CheckCaps2(D3DCAPS2_CANCALIBRATEGAMMA))
		m_d3dDevice->SetGammaRamp(0, D3DSGR_CALIBRATE , &d3dGamma);
	else
		m_d3dDevice->SetGammaRamp(0, D3DSGR_NO_CALIBRATION , &d3dGamma);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GammaDown
//
//	Last Modified: 	03/07/2007
//
//	Purpose:		sets the gamma value down
//
//////////////////////////////////////////////////////////////////////////
void CDirectX9::GammaDown()
{
	m_nGammaRamp -= 256; 

	//check to see if fullscreen gamma is supported
	if(!CheckCaps2(D3DCAPS2_FULLSCREENGAMMA))
		return;

	for(int i = 0; i < 256; i++) 
	{ 
		int tempColor;

		tempColor	= (m_nGammaRamp + (256 * i));

		if(tempColor > 65535)
			tempColor = 65535;

		if(tempColor < 0)
			tempColor = 0;

		d3dGamma.red[i]		= tempColor;
		d3dGamma.green[i]	= tempColor; 
		d3dGamma.blue[i]	= tempColor; 
	}

	//set the new gamma
	if(CheckCaps2(D3DCAPS2_CANCALIBRATEGAMMA))
		m_d3dDevice->SetGammaRamp(0, D3DSGR_CALIBRATE , &d3dGamma);
	else
		m_d3dDevice->SetGammaRamp(0, D3DSGR_NO_CALIBRATION , &d3dGamma);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		ResetGamma
//
//	Last Modified: 	03/07/2007
//
//	Purpose:		resets the gamma back to the deault levels
//
//////////////////////////////////////////////////////////////////////////
void CDirectX9::GammaReset()
{
	//check to see if fullscreen gamma is supported
	if(!CheckCaps2(D3DCAPS2_FULLSCREENGAMMA))
		return;

	m_nGammaRamp = 0; 

	//check to see if fullscreen gamma is supported
	if(!CheckCaps2(D3DCAPS2_FULLSCREENGAMMA))
		return;

	for(int i = 0; i < 256; i++) 
	{ 
		int tempColor;

		tempColor	= (m_nGammaRamp + (256 * i));

		if(tempColor < 0)
			tempColor = 0;

		d3dGamma.red[i]		= tempColor;
		d3dGamma.green[i]	= tempColor; 
		d3dGamma.blue[i]	= tempColor; 
	}

	//set the new gamma
	if(CheckCaps2(D3DCAPS2_CANCALIBRATEGAMMA))
		m_d3dDevice->SetGammaRamp(0, D3DSGR_CALIBRATE , &d3dGamma);
	else
		m_d3dDevice->SetGammaRamp(0, D3DSGR_NO_CALIBRATION , &d3dGamma);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		CheckMultiSample
//
//	Last Modified: 	03/07/2007
//
//	Purpose:		checks if the display device supports that type 
//					of multi-sampling
//
//////////////////////////////////////////////////////////////////////////
bool CDirectX9::CheckMultiSample(D3DMULTISAMPLE_TYPE d3dMultiSampleType)
{
	//check if the back buffer supports it
	if(SUCCEEDED(m_d3dObj->CheckDeviceMultiSampleType
		(
		D3DADAPTER_DEFAULT,
		D3DDEVTYPE_HAL,
		D3DFMT_X8R8G8B8,
		m_bWindowed,
		d3dMultiSampleType,
		NULL
		)))

		//check if the depth buffer supports it
		if(SUCCEEDED(m_d3dObj->CheckDeviceMultiSampleType
			(
			D3DADAPTER_DEFAULT,
			D3DDEVTYPE_HAL,
			D3DFMT_D24X8,
			m_bWindowed,
			d3dMultiSampleType,
			NULL
			)))
			return true;


	//if they don't, return false
	return false;
}

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
void CDirectX9::ChangeMode(const unsigned int &nWidth, const unsigned int &nHeight, bool bWindowed, D3DMULTISAMPLE_TYPE d3dMultiSampleType, D3DTEXTUREFILTERTYPE d3dTextureFiltering, unsigned int nAniso)
{
	// Set the new Presentation Parameters.
	m_d3dPresent.BackBufferFormat			= (bWindowed) ? D3DFMT_UNKNOWN : D3DFMT_X8R8G8B8;
	m_d3dPresent.Windowed					= bWindowed;
	m_d3dPresent.BackBufferWidth			= nWidth;
	m_d3dPresent.BackBufferHeight			= nHeight;
	m_d3dPresent.FullScreen_RefreshRateInHz	= (bWindowed) ? 0 : 60;

	//save the settings
	m_bWindowed = bWindowed;			
	m_nWidth	= nWidth;
	m_nHeight	= nHeight;

	//Reset the device.
	m_d3dSprite->OnLostDevice();
	m_d3dDevice->Reset(&m_d3dPresent);
	m_d3dSprite->OnResetDevice();

	//Set the window to the middle of the screen.
	if (bWindowed)
	{
		SetWindowPos
			(
			m_hWnd, 
			HWND_TOP,	
			(GetSystemMetrics(SM_CXSCREEN)>>1) - (nWidth>>1),
			(GetSystemMetrics(SM_CYSCREEN)>>1) - (nHeight>>1),
			nWidth, 
			nHeight, 
			SWP_SHOWWINDOW);
	}
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		SaveSettings
//
//	Last Modified: 	03/07/2007
//
//	Purpose:		saves the video settings
//
//////////////////////////////////////////////////////////////////////////
void CDirectX9::SaveSettings()
{
	fstream ConfigFile;

	//Open the config.ini file
	ConfigFile.open("config.ini", ios_base::out | ios_base::trunc);

	//output the width, height and windowed
	ConfigFile << m_d3dPresent.BackBufferWidth << endl;	
	ConfigFile << m_d3dPresent.BackBufferHeight << endl;	
	ConfigFile << m_d3dPresent.Windowed << endl;	

	//close the file
	ConfigFile.close();
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		LoadSettings
//
//	Last Modified: 	03/07/2007
//
//	Purpose:		loads the video settings
//
//////////////////////////////////////////////////////////////////////////
void CDirectX9::LoadSettings()
{
	fstream ConfigFile;

	//Open the config.ini file
	ConfigFile.open("config.ini", ios_base::in);

	//input the width, height and windowed
	ConfigFile >> m_nWidth;
	ConfigFile >> m_nHeight;
	ConfigFile >> m_bWindowed;

	//close the file
	ConfigFile.close();
}