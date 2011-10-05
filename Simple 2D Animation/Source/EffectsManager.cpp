//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	EffectsManager.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls all the textures being used
//
//////////////////////////////////////////////////////////////////////////
#include "EffectsManager.h"

//Initialize the static variable member.
CEffectsManager *CEffectsManager::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetInstance
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Creates the first instance of this class and returns it's address.
//
//	Out:			returns a pointer to this instance
//
//////////////////////////////////////////////////////////////////////////
CEffectsManager *CEffectsManager::GetInstance()
{
	//if the pointer is NULL call new
	if (!m_pInstance)
		m_pInstance = new CEffectsManager;

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
void CEffectsManager::DeleteInstance()
{
	//delete the pointer, and set it to NULL
	SAFE_DELETE(m_pInstance);
}

/////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Shutdown
//
//	Last Modified: 	03/08/2007
//
//	Purpose:		Initializes the EffectsManager class
//
//////////////////////////////////////////////////////////////////////////
void CEffectsManager::Shutdown()
{

}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitTextureManager
//
//	Last Modified: 	03/08/2007
//
//	Purpose:		Initializes the EffectsManager class
//
//	In:				DirectX Device pointer
//
//////////////////////////////////////////////////////////////////////////
void CEffectsManager::InitEffectsManager(IDirect3DDevice9 *d3dDevice)
{
	assert(d3dDevice);

	//clear the vectors
	m_vEffects.clear();
	m_vFileNames.clear();

	//set the Direct3D device pointer
	m_d3dDevice = d3dDevice;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitTextureManager
//
//	Last Modified: 	03/08/2007
//
//	Purpose:		Initializes the EffectsManager class
//
//	In:				DirectX Device pointer
//
//////////////////////////////////////////////////////////////////////////
int CEffectsManager::LoadEffect(const char *szFileName)
{
	//make sure the filename is valid
	if(!szFileName)
		return 0;

	//Loop through the Filename vector
	for(int i = 0; i < (int)m_vFileNames.size(); i++)
	{
		//if we find the file is already loaded, just return the index
		if(strcmp(m_vFileNames[i], szFileName) == 0)
			return i;
	}

	LPD3DXEFFECT	d3dTempEffect;
	LPD3DXBUFFER	d3dCompileErrors;

	//create the effect!
	D3DXCreateEffectFromFile(m_d3dDevice, szFileName, 0, 0, 0, 0, &d3dTempEffect, &d3dCompileErrors);

	//check if we have any ugly compiler errors
	if(d3dCompileErrors)
	{
		//OutputDebugString(d3dCompileErrors->GetBufferPointer());
		return 0;
	}

	D3DXHANDLE d3dTempTech;
	if(FAILED(d3dTempEffect->FindNextValidTechnique(NULL, &d3dTempTech)))
		return 0;

	//save the new effect and filename
	tEffect *pNewEffect		= new tEffect;
	pNewEffect->d3dEffect	= d3dTempEffect;
	pNewEffect->d3dTech		= d3dTempTech;

	char *szNewFileName		= new char[128];
	pNewEffect->szFileName	= new char[128];
	strcpy(szNewFileName, szFileName);
	strcpy(pNewEffect->szFileName, szFileName);

	//Push texture pointer into the texture vector
	m_vEffects.push_back(pNewEffect);

	//Push filename into the filename vector
	m_vFileNames.push_back(szNewFileName);

	//Return the index
	return (int)(m_vEffects.size() - 1);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitTextureManager
//
//	Last Modified: 	03/08/2007
//
//	Purpose:		Initializes the EffectsManager class
//
//	In:				DirectX Device pointer
//
//////////////////////////////////////////////////////////////////////////
void CEffectsManager::Begin(const int nEffectID, unsigned int nPasses)
{
	//check if the index is out of the array bounds
	if(nEffectID > (m_vEffects.size() - 1) || !m_vEffects[nEffectID])
		return;

	if(SUCCEEDED(m_vEffects[nEffectID]->d3dEffect->SetTechnique(m_vEffects[nEffectID]->d3dTech)))
		m_vEffects[nEffectID]->d3dEffect->Begin(&nPasses, D3DXFX_DONOTSAVESTATE);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitTextureManager
//
//	Last Modified: 	03/08/2007
//
//	Purpose:		Initializes the EffectsManager class
//
//	In:				DirectX Device pointer
//
//////////////////////////////////////////////////////////////////////////
void CEffectsManager::BeginPass(const int nEffectID, unsigned int nPass)
{
	//check if the index is out of the array bounds
	if(nEffectID > (m_vEffects.size() - 1) || !m_vEffects[nEffectID])
		return;

	m_vEffects[nEffectID]->d3dEffect->BeginPass(nPass);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitTextureManager
//
//	Last Modified: 	03/08/2007
//
//	Purpose:		Initializes the EffectsManager class
//
//	In:				DirectX Device pointer
//
//////////////////////////////////////////////////////////////////////////
void CEffectsManager::End(const int nEffectID)
{
	//check if the index is out of the array bounds
	if(nEffectID > (m_vEffects.size() - 1) || !m_vEffects[nEffectID])
		return;

	m_vEffects[nEffectID]->d3dEffect->End();
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitTextureManager
//
//	Last Modified: 	03/08/2007
//
//	Purpose:		Initializes the EffectsManager class
//
//	In:				DirectX Device pointer
//
//////////////////////////////////////////////////////////////////////////
void CEffectsManager::EndPass(const int nEffectID)
{
	//check if the index is out of the array bounds
	if(nEffectID > (m_vEffects.size() - 1) || !m_vEffects[nEffectID])
		return;

	m_vEffects[nEffectID]->d3dEffect->EndPass();
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitTextureManager
//
//	Last Modified: 	03/08/2007
//
//	Purpose:		Initializes the EffectsManager class
//
//	In:				DirectX Device pointer
//
//////////////////////////////////////////////////////////////////////////
void CEffectsManager::SetDispatch(const int nEffectID/*, D3DXMATRIX &world, D3DXMATRIX &view, D3DXMATRIX &proj*/)
{
	static float time = 0.0f;
	//check if the index is out of the array bounds
	if(nEffectID > (m_vEffects.size() - 1) || !m_vEffects[nEffectID])
		return;

	D3DXMATRIX temp;
	D3DXMatrixIdentity(&temp);

	time += 0.001f;

	m_vEffects[nEffectID]->d3dEffect->SetMatrix("g_mWorld", &temp);
	m_vEffects[nEffectID]->d3dEffect->SetFloat("g_fTime", time);
	m_vEffects[nEffectID]->d3dEffect->SetMatrix("g_mWorldViewProjection", &(temp * temp) );

}
