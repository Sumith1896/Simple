//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	TextureManager.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls all the textures being used
//
//////////////////////////////////////////////////////////////////////////
#include "TextureManager.h"
#include "resource.h"

//Initialize the static variable member.
CTextureManager *CTextureManager::m_pInstance = NULL;

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
int CTextureManager::LoadTexture(const char *szFileName, IDirect3DTexture9 **d3dTexture)
{
	//check teh filename pointer
	if(!szFileName)
	{
		//set it to the default texture if the pointer is bad
		*d3dTexture = m_vTextures[0]->d3dTexture;
		return 0;
	}

	//Loop through the Filename vector
	for(int i = 0; i < (int)m_vFileNames.size(); i++)
	{
		//if we find the file is already loaded, just return the index
		if(strcmp(m_vFileNames[i], szFileName) == 0)
		{
			*d3dTexture =  m_vTextures[i]->d3dTexture;
			return i;
		}
	}

	//Create the texture, if it fails return 0 and the default texture
	if(FAILED(D3DXCreateTextureFromFile(m_d3dDevice, szFileName , d3dTexture)))
	{
		*d3dTexture = m_vTextures[0]->d3dTexture;
		return 0;
	}

	char *szNewFileName		= new char[128];
	strcpy(szNewFileName, szFileName);

	//Push filename into the filename vector
	m_vFileNames.push_back(szNewFileName);

	//Return the index
	return (int)(m_vTextures.size() - 1);
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
CTextureManager *CTextureManager::GetInstance()
{
	//if the pointer is NULL call new
	if (!m_pInstance)
		m_pInstance = new CTextureManager;

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
void CTextureManager::DeleteInstance()
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
//	Purpose:		Initializes the TextureManager class
//
//////////////////////////////////////////////////////////////////////////
void CTextureManager::Shutdown()
{
	DeleteTextures();
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitTextureManager
//
//	Last Modified: 	03/08/2007
//
//	Purpose:		Initializes the TextureManager class
//
//	In:				DirectX Device pointer
//
//////////////////////////////////////////////////////////////////////////
void CTextureManager::InitTextureManager(IDirect3DDevice9 *d3dDevice)
{
	assert(d3dDevice);

	//clear the vectors
	m_vTextures.clear();
	m_vFileNames.clear();

	//set the Direct3D device pointer
	m_d3dDevice = d3dDevice;

	//////////////////////////////////////////////////////////////////////////
	//Load texture into memory from exe
	//////////////////////////////////////////////////////////////////////////

	////load default texture from the .exe
	//tTexture *pNewTexture = new tTexture;
	//D3DXCreateTextureFromResource(m_d3dDevice, NULL, (LPCSTR)IDB_BITMAP1 , &pNewTexture->d3dTexture);

	//char *szNewFileName		= new char[128];
	//pNewTexture->szFileName = new char[128];
	//strcpy(szNewFileName, "default.bmp");
	//strcpy(pNewTexture->szFileName,  "default.bmp");

	////Push texture pointer into the texture vector
	//m_vTextures.push_back(pNewTexture);

	////Push filename into the filename vector
	//m_vFileNames.push_back(szNewFileName);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		LoadTexture
//
//	Last Modified: 	03/08/2007
//
//	Purpose:		Loads a texture into memory and returns the index of
//					where it is in the vector
//
//	In:				filename of the texture to load into memory
//
//	Out:			index of the texture loaded
//
//////////////////////////////////////////////////////////////////////////
int CTextureManager::LoadTexture(const char *szFileName)
{
	//check teh filename pointer
	if(!szFileName)
		return 0;

	//Loop through the Filename vector
	for(int i = 0; i < (int)m_vFileNames.size(); i++)
	{
		//if we find the file is already loaded, just return the index
		if(strcmp(m_vFileNames[i], szFileName) == 0)
			return i;
	}

	IDirect3DTexture9	*pTempTexture;

	//Create the texture, if it fails return 0
	if(FAILED(D3DXCreateTextureFromFile(m_d3dDevice, szFileName , &pTempTexture)))
		return 0;

	//setup the new texture
	tTexture *pNewTexture = new tTexture;
	pNewTexture->d3dTexture = pTempTexture;

	char *szNewFileName		= new char[128];
	pNewTexture->szFileName = new char[128];
	strcpy(szNewFileName, szFileName);
	strcpy(pNewTexture->szFileName, szFileName);

	//Push texture pointer into the texture vector
	m_vTextures.push_back(pNewTexture);

	//Push filename into the filename vector
	m_vFileNames.push_back(szNewFileName);

	//Return the index
	return (int)(m_vTextures.size() - 1);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		UnloadTextures
//
//	Last Modified:	03/08/2007
//
//	Purpose:		Unloads all loaded textures from memory
//
//////////////////////////////////////////////////////////////////////////
void CTextureManager::UnloadTextures()
{
	//Loop through the Filename vector and delete them...
	for(int i = 0; i < (int)m_vFileNames.size(); i++)
		SAFE_DELETE_ARRAY(m_vFileNames[i]);

	//safely release the textures
	for(int i = 0; i < (int)m_vTextures.size(); i++)
		SAFE_RELEASE(m_vTextures[i]->d3dTexture);

	//clear the array
	m_vFileNames.clear();
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		ReloadTextures
//
//	Last Modified:	03/08/2007
//
//	Purpose:		Reloads all unloaded textures back into memory
//
//////////////////////////////////////////////////////////////////////////
void CTextureManager::ReloadTextures()
{
	//////////////////////////////////////////////////////////////////////////
	//for the exe bitmap
	//////////////////////////////////////////////////////////////////////////

	////load default texture from the .exe
	//D3DXCreateTextureFromResource(m_d3dDevice, NULL, (LPCSTR)IDB_BITMAP1 , &m_vTextures[0]->d3dTexture);

	//char *szNewFileName		= new char[128];
	//strcpy(szNewFileName, "default.bmp");

	////Push filename into the filename vector
	//m_vFileNames.push_back(szNewFileName);

	//time to load these textures back it memory
	for(int i = 1; i < (int)m_vTextures.size(); i++)
		LoadTexture(m_vTextures[i]->szFileName, &m_vTextures[i]->d3dTexture);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteTextures
//
//	Last Modified:	03/08/2007
//
//	Purpose:		Deletes all loaded textures from memory
//
//	Notes:			***this is permanent***
//
//////////////////////////////////////////////////////////////////////////
void CTextureManager::DeleteTextures()
{
	//Loop through the Filename vector and delete them...
	for(int i = 0; i < (int)m_vFileNames.size(); i++)
		SAFE_DELETE_ARRAY(m_vFileNames[i]);

	//safely release the textures
	for(int i = 0; i < (int)m_vTextures.size(); i++)
	{
		SAFE_RELEASE(m_vTextures[i]->d3dTexture);
		SAFE_DELETE_ARRAY(m_vTextures[i]->szFileName);
		SAFE_DELETE(m_vTextures[i]);
	}

	//clear the arrays
	m_vFileNames.clear();
	m_vTextures.clear();
}