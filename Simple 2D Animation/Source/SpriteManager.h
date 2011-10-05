//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	SpriteManager.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the creation. drawing, and destroying 
//				of all sprites
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Helpers.h"
#include "TextureManager.h"
#include <vector>
using std::vector;

class CACHE_ALIGN CSpriteManager
{
private:

	struct CACHE_ALIGN tSprite
	{
		int					nTexture;		//index of the texture being used
		D3DXVECTOR3			d3dCenter;		//the center of the sprite
		D3DXMATRIX			d3dMat;			//matrix for the sprite
		D3DXCOLOR			d3dColor;		//color of the sprite (ARGB)
		bool				bDynamic;		//false if static, true if dynamic
	};

	IDirect3DDevice9		*m_d3dDevice;		//pointer to the direct3d device
	ID3DXSprite				*m_d3dSprite;		//pointer to the sprite device
	CTextureManager			*m_pTextureManager;	//pointer to the texture manager

	vector<tSprite *>		m_vSprites;			//vector of loaded Sprites.

	static CSpriteManager *m_pInstance;			//	The instance of this class.

	//constructor, copy constructor, destructor and = operator all in teh private!!!
	CSpriteManager(){};
	CSpriteManager(const CSpriteManager &a){};
	CSpriteManager &operator=(const CSpriteManager &a){};
	~CSpriteManager(){};

public:

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Inline Functions
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		Inline functions to get Sprite information. 
	//
	//////////////////////////////////////////////////////////////////////////
	inline D3DXMATRIX GetMatrix(const int &nSprite){return m_vSprites[nSprite]->d3dMat;}

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetInstance
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		Creates the first instance of this class and returns it's address.
	//
	//////////////////////////////////////////////////////////////////////////
	static CSpriteManager *GetInstance();

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
	//	Purpose:		All clean up code is here
	//
	//////////////////////////////////////////////////////////////////////////
	void Shutdown();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitSpriteManager
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the SpriteManager class
	//
	//	In:				DirectX Device pointer and Sprite object pointer
	//
	//////////////////////////////////////////////////////////////////////////
	void InitSpriteManager(IDirect3DDevice9 *d3dDevice, ID3DXSprite *d3dSprite);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		LoadSprite
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Loads a sprite from an index to a texture from the
	//					texture manager
	//
	//	In:				index to a texture from the texturemanager and bool if
	//					it's static or not
	//
	//	Out:			index to the sprite being loaded
	//
	//////////////////////////////////////////////////////////////////////////
	int LoadSprite(const int &nTexture, bool bStatic);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		LoadSprite
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Loads a sprite from a file
	//	
	//	In:				filename of the texture to load as a sprite and bool if
	//					it's static or not
	//
	//	Out:			index to the sprite being loaded
	//
	//////////////////////////////////////////////////////////////////////////
	int LoadSprite(const char *szFileName, bool bStatic);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DrawSprite
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Draws a sprite based on the ID passed
	//
	//	In:				index to the sprite
	//
	//////////////////////////////////////////////////////////////////////////
	void DrawSprite(const unsigned int &nSpriteID);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DrawSprite
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Draws a sprite based on the ID passed
	//
	//	In:				index to the sprite and color to tint it
	//
	//////////////////////////////////////////////////////////////////////////
	void DrawSprite(const unsigned int &nSpriteID, const D3DXCOLOR &d3dColor);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DrawSprite
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Draws a sprite based on the ID passed
	//
	//	In:				index to the sprite and rect of the section to draw
	//					also the color to tint the sprite
	//
	//////////////////////////////////////////////////////////////////////////
	void DrawSprite(const unsigned int &nSpriteID, const RECT &spriteRect, const D3DXCOLOR &d3dColor);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		RotateSprite
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Rotates a sprite based on the rotate amount
	//
	//	In:				index to the sprite and rotation amount
	//
	//////////////////////////////////////////////////////////////////////////
	void RotateSprite(const unsigned int &nSpriteID, const float &fRotate);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		ScaleSprite
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Scales a sprite based on amount passed over
	//
	//	In:				index to sprite and amount to scale it by
	//
	//////////////////////////////////////////////////////////////////////////
	void ScaleSprite(const unsigned int &nSpriteID, const float &fScaleWidth, const float &fScaleHeight);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		TranslateSprite
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Translate a sprite based on amount passed over
	//
	//	In:				index to sprite and amount to translate
	//
	//////////////////////////////////////////////////////////////////////////
	void TranslateSprite(const unsigned int &nSpriteID, const float &fPositionX, const float &fPositionY);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetWidth
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Returns the width of the sprite back
	//
	//	In:				index to sprite
	//
	//	Out:			width of the sprite
	//
	//////////////////////////////////////////////////////////////////////////
	int GetWidth(const unsigned int &nSpriteID);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetHeight
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Returns the width of the sprite back
	//
	//	In:				index to sprite
	//
	//	Out:			height of the sprite
	//
	//////////////////////////////////////////////////////////////////////////
	int GetHeight(const unsigned int &nSpriteID);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		SetCenter
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Sets the center point of the sprite
	//
	//	In:				index to sprite and posistion to set as the center
	//
	//////////////////////////////////////////////////////////////////////////
	D3DXVECTOR3 GetCenter(const unsigned int &nSpriteID);


	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		SetCenter
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Sets the center point of the sprite
	//
	//	In:				index to sprite and posistion to set as the center
	//
	//////////////////////////////////////////////////////////////////////////
	void SetCenter(const unsigned int &nSpriteID, const float &fCenterX, const float &fCenterY);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		SetColor
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Sets the color tint of the sprite
	//
	//	In:				index of sprite and color to set the sprite to
	//
	//////////////////////////////////////////////////////////////////////////
	void SetColor(const unsigned int &fSpriteID, const float &fColorRed, const float &fColorGreen, const float &fColorBlue, const float &fColorAlpha);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		SetMatrix
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Sets the matrix of the sprite
	//
	//	In:				index to sprite and new matrix the sprite will have
	//
	//////////////////////////////////////////////////////////////////////////
	void SetMatrix(const unsigned int &nSpriteID, D3DXMATRIX d3dMat);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetMatrix
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Gets the matrix of the sprite
	//
	//	In:				index to sprite
	//
	//	Out:			matrix of the sprite
	//
	//////////////////////////////////////////////////////////////////////////
	D3DXMATRIX GetMatrix(const unsigned int &nSpriteID);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		UnloadSprite
	//
	//	Last Modified: 	02/14/2007
	//
	//	Purpose:		Gets the matrix of the sprite
	//
	//////////////////////////////////////////////////////////////////////////
	void UnloadSprite(const unsigned int &nSpriteID);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		UnloadAllSprites
	//
	//	Last Modified: 	02/14/2007
	//
	//	Purpose:		Gets the matrix of the sprite
	//
	//////////////////////////////////////////////////////////////////////////
	void UnloadAllSprites();
};