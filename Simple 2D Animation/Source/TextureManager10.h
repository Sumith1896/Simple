//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	TextureManager10.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the creation and deleting of all textures
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Direct3D10.h"
#include "Helpers.h"
#include <vector>
using std::vector;

class CACHE_ALIGN CTextureManager10
{
private:

	//texture structure
	struct CACHE_ALIGN tTexture
	{
		char				*szFileName;	//name of the texture
		ID3D10Resource		*d3dTexture;	//pointer to a texture
	};

	vector<tTexture *>				m_vTextures;				//vector of all the the loaded textures
	vector<char *>					m_vFileNames;				//vector of all the the texture filenames

	static CTextureManager10			*m_pInstance;				//the instance of this class.

	//constructor, copy constructor, destructor and = operator all in teh private!!!
	CTextureManager10(){};
	CTextureManager10(const CTextureManager10 &a){};
	CTextureManager10 &operator=(const CTextureManager10 &a){};
	~CTextureManager10(){};

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
	int LoadTexture(const char *szFileName, ID3D10Resource **d3dTexture);

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
	inline ID3D10Resource *GetTexture(const unsigned int &nTexture)
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
	static CTextureManager10 *GetInstance();

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
	//	Purpose:		Shuts down TextureManager10 class
	//
	//////////////////////////////////////////////////////////////////////////
	void Shutdown();


	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitTextureManager
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the TextureManager10 class
	//
	//	In:				DirectX Device pointer
	//
	//////////////////////////////////////////////////////////////////////////
	void InitTextureManager();

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
	void CTextureManager10::DeleteTextures();
};
