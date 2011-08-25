//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	SimpleMain.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	CSimpleMain is the main part of this Simple Shell program
//
//////////////////////////////////////////////////////////////////////////
#include "SimpleMain.h"





//initialize the static variable members
CSimpleMain *CSimpleMain::m_pinstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
//
//	Last Modified: 	10/04/2006
//
//	Purpose:		Delete the instance, and set the pointer to NULL
//
//////////////////////////////////////////////////////////////////////////
void CSimpleMain::DeleteInstance()
{
	//delete the pointer, and set it to NULL
	SAFE_DELETE(m_pinstance);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetInstance
//
//	Last Modified: 	10/04/2006
//
//	Purpose:		Creates the first instance and returns it's address.
//
//////////////////////////////////////////////////////////////////////////
CSimpleMain *CSimpleMain::GetInstance()
{
	//if the pointer is NULL call new
	if(!m_pinstance)
		m_pinstance = new CSimpleMain;

	//return the pointer
	return m_pinstance;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitCSimpleMain
//
//	Last Modified: 	10/04/2006
//
//	Purpose:		Initializes the Simple shell module
//
//////////////////////////////////////////////////////////////////////////
void CSimpleMain::InitCSimpleMain(HWND hWnd, HINSTANCE hInstance, int nWidth, int nHeight, bool bWindowed, bool bVsync)
{
	m_hWnd = hWnd;

	//setup all the singletons
	m_pDirect3D			= CDirectX9::GetInstance();
	m_pTextureManager	= CTextureManager::GetInstance();
	m_pSpriteManager	= CSpriteManager::GetInstance();
	m_pDirectInput		= CDirectInput::GetInstance();
	m_pTimer			= Timer::GetInstance();
	m_pAnimationManager	= CAnimationManager::GetInstance();
	m_pBMPFont			= CBMPFont::GetInstance();
	m_pCamera			= CCamera::GetInstance();
	m_pTerrain			= CTerrain::GetInstance();
	m_pWorld			= World::GetInstance();

	m_pNewTerrain			= NewTerrain::GetInstance();


	//init all the singletons
	m_pDirect3D->InitDirectX9(hWnd, nWidth, nHeight, bWindowed, true);
	m_pTextureManager->InitTextureManager(m_pDirect3D->GetD3DDevice());
	m_pSpriteManager->InitSpriteManager(m_pDirect3D->GetD3DDevice(), m_pDirect3D->GetD3DSprite());
	m_pDirectInput->InitDirectInput(hWnd, hInstance, true);
	m_pCamera->InitCamera();
	m_pTimer->Init();
	m_pBMPFont->InitBMPFont(128);
	//m_pTerrain->InitTerrain();
	m_pWorld->Init();

	m_pNewTerrain->InitTerrain();

	m_pAnimationManager->Load2DAnimaton("test.txt");


	m_pTimer->CreateTimer();

	SetStates();

	SetDefaultLights();
}

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
bool CSimpleMain::UpdateCSimpleMain()
{
	//check for any mouse and keyboard action
	m_pDirectInput->ReadInput();
	m_pTimer->UpdateFPS(0);
	m_pTimer->Update(0);
	m_pCamera->Update();

	if(!Inputs())
		return false;

	if(!Updates())
		return false;

	m_pDirect3D->Clear();

	if(!Draws())
		return false;

	m_pDirect3D->EndScene();

	m_pDirect3D->Present();

	return true;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Inits
//
//	Last Modified: 	10/04/2006
//
//	Purpose:		All the inits
//
//	Notes:			-This function is called once.
//					-This function is called right after "InitCSimpleMain".
//					-This is where all inits to your variables or objects 
//					 need to go. 
//					-DO NOT use the constructor or "InitCSimpleMain" to
//					 initialize your variables.
//
//////////////////////////////////////////////////////////////////////////
void CSimpleMain::Inits()
{
	m_fTickFPS = 1.0f;
	m_fTimer = 0.0f;
	m_bWireframe = false;

	nBMP = m_pSpriteManager->LoadSprite("bmpfont.dds", false);

	m_Base.InitFrame("torso.dds");
	m_Base.AddOne("head.dds", 0.0f, -1.0f, false);
	m_Base.AddThree("left_leg01.dds", "left_leg02.dds", "left_foot.dds", -0.1f, 1.0f, false);
	m_Base.AddThree("left_arm01.dds", "left_arm02.dds", "left_hand.dds", 0.0f, -0.75f, false);

	m_Base.AddThree("left_arm01.dds", "left_arm02.dds", "left_hand.dds", 0.0f, -0.75f, true);
	m_Base.AddThree("left_leg01.dds", "left_leg02.dds", "left_foot.dds", 0.1f, 1.0f, true);

	//turn the buffer into some materials
	D3DMATERIAL9 d3dxMaterial;

	d3dxMaterial.Ambient.r	= 1.0f;
	d3dxMaterial.Ambient.g	= 1.0f;
	d3dxMaterial.Ambient.b	= 1.0f;
	d3dxMaterial.Ambient.a	= 1.0f;

	d3dxMaterial.Diffuse.r	= 1.0f;
	d3dxMaterial.Diffuse.g	= 1.0f;
	d3dxMaterial.Diffuse.b	= 1.0f;
	d3dxMaterial.Diffuse.a	= 1.0f;

	d3dxMaterial.Specular.r	= 0.0f;
	d3dxMaterial.Specular.g	= 0.0f;
	d3dxMaterial.Specular.b	= 0.0f;
	d3dxMaterial.Specular.a	= 1.0f;

	d3dxMaterial.Power		= 0.0f;

	d3dxMaterial.Emissive.r	= 0.0f;
	d3dxMaterial.Emissive.g	= 0.0f;
	d3dxMaterial.Emissive.b	= 0.0f;
	d3dxMaterial.Emissive.a	= 1.0f;
	D3DXVECTOR3 testpos(200.0f,0.0f,0.0f);
	D3DXVECTOR3 testpos0(200.0f,0.0f,0.0f);
	testblock1.SetPos(testpos0);

	D3DXVECTOR3 testpos1(0.0f,0.0f,0.0f);
	testblock2.SetPos(testpos1);

	D3DXVECTOR3 testpos2(0.0f,200.0f,0.0f);
	testblock3.SetPos(testpos2);

	m_pDirect3D->GetD3DDevice()->SetMaterial(&d3dxMaterial);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Uodates
//
//	Last Modified: 	10/04/2006
//
//	Purpose:		All the updates
//
//	Notes:			-This function is called every frame.
//					-This is where all updates to your variables or objects
//					 need to go. 
//
//////////////////////////////////////////////////////////////////////////
bool CSimpleMain::Updates()
{
	m_fTimer += m_pTimer->GetFractionOfSecondsPassed(0);
	m_fTickFPS -= m_pTimer->GetFractionOfSecondsPassed(0);

	if(m_fTickFPS < 0.0f)
	{
		m_fTickFPS = 1.0f;
	}
	//m_Base.Update();

	m_pWorld->Cull();

	return true;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Draws
//
//	Last Modified: 	10/04/2006
//
//	Notes:			-This function is called every frame.
//					-This is where all the drawing calls for sprites go. 
//
//////////////////////////////////////////////////////////////////////////
bool CSimpleMain::Draws()
{

	m_pDirect3D->Begin3D();

	//m_pTerrain->Draw();

	//m_pNewTerrain->Draw(1, &testblock1.GetMatrix());
	//m_pNewTerrain->Draw(1, &testblock2.GetMatrix());
	//m_pNewTerrain->Draw(1, &testblock3.GetMatrix());

	m_pWorld->Draw();

	m_pDirect3D->BeginSprite();
	D3DXCOLOR temp;
	temp.a = 1.0f;
	temp.r = 1.0f;
	temp.g = 1.0f;
	temp.b = 1.0f;
	//m_Base.Draw();

	char buffer[64];
	sprintf(buffer, "Draw Count: %d", m_pWorld->draw);

	m_pBMPFont->DrawString(nBMP, m_pTimer->GetFrameRateChar(1), 0.0f, 0.0f, temp, 0.25f);
	m_pBMPFont->DrawString(nBMP, m_pTimer->GetFrameRateChar(0), 0.0f, 32.0f, temp, 0.25f);
	m_pBMPFont->DrawString(nBMP, buffer, 0.0f, 64.0f, temp, 0.25f);

	

	return true;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Shutdown
//
//	Last Modified: 	10/04/2006
//
//	Purpose:		All the shut downs
//
//	Notes:			-This function is called once.
//					-This function is called after the main event loop
//					 has exited.
//					-All "shut down" or "clean up" code needs to be here.
//					-DO NOT use the destructor to shut down.
//
//////////////////////////////////////////////////////////////////////////
void CSimpleMain::ShutDowns()
{
	//shut down all the singletons in reverse order
	m_pDirectInput->Shutdown();
	Sleep(50);
	m_pSpriteManager->Shutdown();
	Sleep(50);
	m_pTextureManager->Shutdown();
	Sleep(50);
	m_pDirect3D->ShutdownDirectX9();
	Sleep(50);

	//delete the pointers
	m_pDirectInput->DeleteInstance();
	Sleep(50);
	m_pSpriteManager->DeleteInstance();
	Sleep(50);
	m_pTextureManager->DeleteInstance();
	Sleep(50);
	m_pDirect3D->DeleteInstance();
	Sleep(200);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Inputs
//
//	Last Modified: 	10/04/2006
//
//	Purpose:		All input checking
//
//	Notes:			Check the "Helper.h" file for all mouse button defines.
//
//////////////////////////////////////////////////////////////////////////
bool CSimpleMain::Inputs()
{
	static double move = 0.0f;
	if(m_pDirectInput->GetKeyPressedBuffered(DIK_ESCAPE))
	{
		return false;
	}

	if(m_pDirectInput->GetKeyPressedBuffered(DIK_NUMPADENTER))
	{
		m_Base.SaveValues();
	}

	if(m_pDirectInput->GetKeyPressed(DIK_UPARROW))
	{
		m_Base.RotatePiece(0.0005f);
	}

	if(m_pDirectInput->GetKeyPressed(DIK_DOWNARROW))
	{
		m_Base.RotatePiece(-0.0005f);
	}

	if(m_pDirectInput->GetKeyPressed(DIK_RIGHTARROW))
	{
		m_Base.ScalePiece(0.0005f, 0.0005f);
	}

	if(m_pDirectInput->GetKeyPressed(DIK_LEFTARROW))
	{
		m_Base.ScalePiece(-0.0005f, -0.0005f);
	}

	if(m_pDirectInput->GetKeyPressedBuffered(DIK_ADD))
	{
		m_Base.SelectNextArray();
	}

	if(m_pDirectInput->GetKeyPressedBuffered(DIK_SUBTRACT))
	{
		m_Base.SelectPrevArray();
	}

	if(m_pDirectInput->GetKeyPressedBuffered(DIK_NUMPADSTAR))
	{
		m_Base.SelectNextPiece();
	}

	if(m_pDirectInput->GetKeyPressedBuffered(DIK_O))
	{
		if(m_bWireframe = !m_bWireframe)
		{
			m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
		}else
		{
			m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
		}
	}
	
	return true;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		SetStates
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		sets the starting rendering states
//
//////////////////////////////////////////////////////////////////////////
void CSimpleMain::SetStates()
{
	m_fFieldOfView	= 0.80f;
	m_fNearPlane	= 1.0f;
	m_fFarPlane		= 2500.0f;
	m_fAspectRatio	= (float)1680/(float)1050;

	D3DXMatrixPerspectiveFovLH(&m_matProjection, m_fFieldOfView, m_fAspectRatio, m_fNearPlane, m_fFarPlane);
	m_pDirect3D->GetD3DDevice()->SetTransform(D3DTS_PROJECTION, &m_matProjection);

	m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_AMBIENT, RGB(128, 128, 128));
	m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_LIGHTING, true);

	m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_ZENABLE, D3DZB_TRUE);
	m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW );

	m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
	m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_SHADEMODE, D3DSHADE_GOURAUD);

	m_pDirect3D->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDirect3D->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDirect3D->GetD3DDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	m_pDirect3D->GetD3DDevice()->SetSamplerState(1, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	m_pDirect3D->GetD3DDevice()->SetSamplerState(1, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	m_pDirect3D->GetD3DDevice()->SetSamplerState(1, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);

	COUT << "RenderMain::SetStates() - SUCCESS" << endl; 
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		SetDefaultLights
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		sets the starting lights
//
//////////////////////////////////////////////////////////////////////////
void CSimpleMain::SetDefaultLights()
{
	//////////////////////////////////////////////////////////////////////////
	//SUN LIGHT
	//////////////////////////////////////////////////////////////////////////
	ZeroMemory(&m_Light, sizeof(m_Light));
	m_Light.Type = D3DLIGHT_DIRECTIONAL;

	m_Light.Direction.x = 0.95f;
	m_Light.Direction.y = -0.55f;
	m_Light.Direction.z = 0.34f;

	D3DXVec3Normalize(&D3DXVECTOR3(m_Light.Direction.x, m_Light.Direction.y, m_Light.Direction.z), &D3DXVECTOR3(m_Light.Direction.x, m_Light.Direction.y, m_Light.Direction.z));

	m_Light.Diffuse.r = 1.0f;
	m_Light.Diffuse.g = 1.0f;
	m_Light.Diffuse.b = 1.0f;

	m_pDirect3D->GetD3DDevice()->SetLight(0, &m_Light);  
	m_pDirect3D->GetD3DDevice()->LightEnable(0, true);


	////////////////////////////////////////////////////////////////////////////
	////LAVA LIGHT 01
	////////////////////////////////////////////////////////////////////////////
	//ZeroMemory(&m_LavaLight01, sizeof(m_LavaLight01));
	//m_LavaLight01.Type = D3DLIGHT_DIRECTIONAL;

	//m_LavaLight01.Direction.x = 0.0f;
	//m_LavaLight01.Direction.y = 1.0f;
	//m_LavaLight01.Direction.z = 0.0f;

	//D3DXVec3Normalize(&D3DXVECTOR3(m_LavaLight01.Direction.x, m_LavaLight01.Direction.y, m_LavaLight01.Direction.z), &D3DXVECTOR3(m_LavaLight01.Direction.x, m_LavaLight01.Direction.y, m_LavaLight01.Direction.z));

	//m_LavaLight01.Diffuse.r = 1.0f;
	//m_LavaLight01.Diffuse.g = 0.0f;
	//m_LavaLight01.Diffuse.b = 0.0f;

	//m_pDirect3D->GetD3DDevice()->SetLight(1, &m_LavaLight01);  
	//m_pDirect3D->GetD3DDevice()->LightEnable(1, true);

	////////////////////////////////////////////////////////////////////////////
	////LAVA LIGHT 02
	////////////////////////////////////////////////////////////////////////////
	//ZeroMemory(&m_LavaLight02, sizeof(m_LavaLight02));
	//m_LavaLight02.Type = D3DLIGHT_DIRECTIONAL;

	//m_LavaLight02.Direction.x = -1.0f;
	//m_LavaLight02.Direction.y = 0.0f;
	//m_LavaLight02.Direction.z = 0.0f;

	//D3DXVec3Normalize(&D3DXVECTOR3(m_LavaLight02.Direction.x, m_LavaLight02.Direction.y, m_LavaLight02.Direction.z), &D3DXVECTOR3(m_LavaLight02.Direction.x, m_LavaLight02.Direction.y, m_LavaLight02.Direction.z));

	//m_LavaLight02.Diffuse.r = 1.0;
	//m_LavaLight02.Diffuse.g = 0.25f;
	//m_LavaLight02.Diffuse.b = 0.25f;

	//m_pDirect3D->GetD3DDevice()->SetLight(2, &m_LavaLight02);  
	//m_pDirect3D->GetD3DDevice()->LightEnable(2, false);

	COUT << "RenderMain::SetLight()" << endl; 
}
