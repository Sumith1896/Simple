//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	TextureManager.h
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

class CACHE_ALIGN CTextureManager
{
private:

	//texture structure
	struct CACHE_ALIGN tTexture
	{
		char				*szFileName;	//name of the texture
		IDirect3DTexture9	*d3dTexture;	//pointer to a texture
	};

	IDirect3DDevice9				*m_d3dDevice;				//pointer to the direct3d device

	vector<tTexture *>				m_vTextures;				//vector of all the the loaded textures
	vector<char *>					m_vFileNames;				//vector of all the the texture filenames

	static CTextureManager			*m_pInstance;				//the instance of this class.

	//constructor, copy constructor, destructor and = operator all in teh private!!!
	CTextureManager(){};
	CTextureManager(const CTextureManager &a){};
	CTextureManager &operator=(const CTextureManager &a){};
	~CTextureManager(){};

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		LoadTexture
	//
	//	Last Modified: 	03/08/2007
	//
	//	Purpose:		Loads a texture into memory and returns the index of
	//					where it is in the vector
	//
	//	Notes:			don't touch! =o)
	//
	//////////////////////////////////////////////////////////////////////////
	int LoadTexture(const char *szFileName, IDirect3DTexture9 **d3dTexture);

public:

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Inline Functions
	//
	//	Last Modified: 	03/08/2007
	//
	//	Purpose:		Inline functions to get Texture information. 
	//
	//////////////////////////////////////////////////////////////////////////
	inline IDirect3DTexture9 *GetTexture(const unsigned int &nTexture)
	{
		//check if the index is out of the array bounds
		if(nTexture > (m_vTextures.size() - 1))
			return m_vTextures[0]->d3dTexture;

		if(!m_vTextures[nTexture])
			return m_vTextures[0]->d3dTexture;

		return m_vTextures[nTexture]->d3dTexture;
	}

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
	static CTextureManager *GetInstance();

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
	//	Purpose:		Shuts down TextureManager class
	//
	//////////////////////////////////////////////////////////////////////////
	void Shutdown();


	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitTextureManager
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the TextureManager class
	//
	//	In:				DirectX Device pointer
	//
	//////////////////////////////////////////////////////////////////////////
	void InitTextureManager(IDirect3DDevice9 *d3dDevice);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		LoadTexture
	//
	//	Last Modified: 	2006/09/16
	//
	//	Purpose:		Loads a texture into memory and returns the index of
	//					where it is in the vector
	//
	//	In:				filename of the texture to load into memory
	//
	//	Out:			index of the texture loaded
	//
	//////////////////////////////////////////////////////////////////////////
	int LoadTexture(const char *szFileName);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		UnloadTextures
	//
	//	Last Modified:	03/08/2007
	//
	//	Purpose:		Unloads all loaded textures
	//
	//////////////////////////////////////////////////////////////////////////
	void UnloadTextures();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		ReloadTextures
	//
	//	Last Modified:	03/08/2007
	//
	//	Purpose:		Reloads all unloaded textures
	//
	//////////////////////////////////////////////////////////////////////////
	void ReloadTextures();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DeleteTextures
	//
	//	Last Modified:	03/08/2007
	//
	//	Purpose:		Deletes all loaded textures
	//
	//	Notes:			***this is permanent***
	//
	//////////////////////////////////////////////////////////////////////////
	void CTextureManager::DeleteTextures();
};
