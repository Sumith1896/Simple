//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	EffectsManager.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the creation and deleting of all textures
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Helpers.h"
#include <vector>
using std::vector;

class CACHE_ALIGN CEffectsManager
{
private:

	struct CACHE_ALIGN tEffect
	{
		char			*szFileName;	//name of the effect file
		LPD3DXEFFECT	d3dEffect;		//the Effect
		D3DXHANDLE		d3dTech;		//the technique to use
	};

	vector<tEffect *>				m_vEffects;					//vector of all the the loaded effects
	vector<char *>					m_vFileNames;				//vector of all the the effect filenames

	IDirect3DDevice9				*m_d3dDevice;				//pointer to the direct3d device

	static CEffectsManager			*m_pInstance;				//the instance of this class.

	//constructor, copy constructor, destructor and = operator all in teh private!!!
	CEffectsManager(){};
	CEffectsManager(const CEffectsManager &a){};
	CEffectsManager &operator=(const CEffectsManager &a){};
	~CEffectsManager(){};
public:

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
	static CEffectsManager *GetInstance();

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
	//	Function: 		Shutdown
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Shuts down EffectsManager class
	//
	//////////////////////////////////////////////////////////////////////////
	void Shutdown();


	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitTextureManager
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the EffectsManager class
	//
	//	In:				DirectX Device pointer
	//
	//////////////////////////////////////////////////////////////////////////
	void InitEffectsManager(IDirect3DDevice9 *d3dDevice);

	int LoadEffect(const char *szFileName);
	void Begin(const int nEffectID, unsigned int nPasses);
	void BeginPass(const int nEffectID, unsigned int nPass);
	void EndPass(const int nEffectID);
	void End(const int nEffectID);

	void SetDispatch(const int nEffectID/*, D3DXMATRIX &world, D3DXMATRIX &view, D3DXMATRIX &proj*/);

};
