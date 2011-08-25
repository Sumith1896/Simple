//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	CCamera.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the camera
//
//////////////////////////////////////////////////////////////////////////
#include "Camera.h"

//initialize the static variable member(s)
CCamera *CCamera::m_pinstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Delete the instance of the class, and set the pointer to NULL
//
//////////////////////////////////////////////////////////////////////////
void CCamera::DeleteInstance()
{
	SAFE_DELETE(m_pinstance);

	COUT << "CCamera::DeleteInstance() - SUCCESS" << endl;
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
CCamera *CCamera::GetInstance()
{
	if(!m_pinstance)
		m_pinstance = new CCamera;

	return m_pinstance;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitCamera
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Initializes the camera class
//
//////////////////////////////////////////////////////////////////////////
void CCamera::InitCamera()
{
	m_pDirectX		= CDirectX9::GetInstance();
	m_pDirectInput	= CDirectInput::GetInstance();
	m_pTimer		= Timer::GetInstance();

	m_vLookAtPt = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	m_vEyePt	= D3DXVECTOR3(0.0f, 0.0f, -25.0f);
	m_vUp		= D3DXVECTOR3(0.0f,1.0f,0.0f);

	m_fSpeed	= 25.0f;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Update
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Update the Camera
//
//////////////////////////////////////////////////////////////////////////
void CCamera::Update()
{
	Rotate();
	Move();

	D3DXMatrixLookAtLH(&m_matView,&m_vEyePt,&m_vLookAtPt,&m_vUp);
	m_pDirectX->GetD3DDevice()->SetTransform(D3DTS_VIEW,&m_matView);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Move
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Move the camera
//
//////////////////////////////////////////////////////////////////////////
void CCamera::Move()
{
	D3DXVECTOR3 vDirection;

	D3DXVec3Normalize(&vDirection,&(m_vLookAtPt - m_vEyePt));

	if(m_pDirectInput->GetKeyPressed(DIK_W))
	{
		m_vEyePt += vDirection * (m_fSpeed * m_pTimer->GetFractionOfSecondsPassed(0));
		m_vLookAtPt += vDirection * (m_fSpeed * m_pTimer->GetFractionOfSecondsPassed(0));
	}

	if(m_pDirectInput->GetKeyPressed(DIK_S))
	{
		m_vEyePt -= vDirection * (m_fSpeed * m_pTimer->GetFractionOfSecondsPassed(0));
		m_vLookAtPt -= vDirection * (m_fSpeed * m_pTimer->GetFractionOfSecondsPassed(0));
	}

	if(m_pDirectInput->GetKeyPressed(DIK_A))
	{
		D3DXVec3Cross(&vDirection,&vDirection,&m_vUp);
		D3DXVec3Normalize(&vDirection,&vDirection);

		m_vEyePt += vDirection * (m_fSpeed * m_pTimer->GetFractionOfSecondsPassed(0));
		m_vLookAtPt += vDirection * (m_fSpeed * m_pTimer->GetFractionOfSecondsPassed(0));
	}

	if(m_pDirectInput->GetKeyPressed(DIK_D))
	{
		D3DXVec3Cross(&vDirection,&vDirection,&m_vUp);
		D3DXVec3Normalize(&vDirection,&vDirection);

		m_vEyePt -= vDirection * (m_fSpeed * m_pTimer->GetFractionOfSecondsPassed(0));
		m_vLookAtPt -= vDirection * (m_fSpeed * m_pTimer->GetFractionOfSecondsPassed(0));
	}

	if(m_pDirectInput->GetKeyPressed(DIK_ADD))
	{
		m_fDistance -= (150.0f * m_pTimer->GetFractionOfSecondsPassed(0));
	}

	if(m_pDirectInput->GetKeyPressed(DIK_SUBTRACT))
	{
		m_fDistance += (50.0f * m_pTimer->GetFractionOfSecondsPassed(0));
	}
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Rotate
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Rotate the camera
//
//////////////////////////////////////////////////////////////////////////
void CCamera::Rotate()
{
	D3DXVECTOR3 vRotAxis;
	D3DXMATRIX matRotAxis,matRotZ;

	D3DXVec3Normalize(&m_vDirection,&(m_vLookAtPt - m_vEyePt));
	D3DXVec3Cross(&vRotAxis,&m_vDirection,&m_vUp);
	D3DXVec3Normalize(&vRotAxis,&vRotAxis);

	D3DXMatrixRotationAxis(&matRotAxis,&vRotAxis, (float)m_pDirectInput->GetMouseAxis(YAXIS)/360);
	D3DXMatrixRotationY(&matRotZ,(float)m_pDirectInput->GetMouseAxis(XAXIS)/360);

	D3DXVec3TransformCoord(&m_vDirection,&m_vDirection,&(matRotAxis * matRotZ));
	D3DXVec3TransformCoord(&m_vUp,&m_vUp,&(matRotAxis * matRotZ));
	m_vLookAtPt = m_vDirection + m_vEyePt;
}