//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	BMPFont.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the BMP Font drawing
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Helpers.h"
#include "SpriteManager.h"
#include <vector>
using std::vector;

class CBMPFont
{
private:

	float					m_fFontSize;		//size of the characters of the font
	vector<RECT>			m_vFontTiles;		//all the rects for the font
	IDirect3DDevice9		*m_d3dDevice;		//pointer to the direct3d device
	CSpriteManager			*m_pSpriteManager;	//pointer to the sprite manager

	static CBMPFont			*m_pInstance;		//	The instance of this class.

	//constructor, copy constructor, destructor and = operator all in teh private!!!
	CBMPFont(){};
	CBMPFont(const CBMPFont &a){};
	CBMPFont &operator=(const CBMPFont &a){};
	~CBMPFont(){};

public:

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetInstance
	//
	//	Last Modified: 	2007/01/22
	//
	//	Purpose:		Creates the first instance of this class and returns it's address.
	//
	//////////////////////////////////////////////////////////////////////////
	static CBMPFont *GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DeleteInstance
	//
	//	Last Modified: 	2007/01/22
	//
	//	Purpose:		Delete the instance of the class, and set the pointer to NULL
	//
	//////////////////////////////////////////////////////////////////////////
	static void DeleteInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Shutdown
	//
	//	Last Modified: 	2007/01/22
	//
	//	Purpose:		All clean up code is here
	//
	//////////////////////////////////////////////////////////////////////////
	void Shutdown();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitBMPFont
	//
	//	Last Modified: 	2007/01/22
	//
	//	Purpose:		Initializes the BMPFont class
	//
	//	In:				the filename of the BMP font, and the size of each character
	//
	//////////////////////////////////////////////////////////////////////////
	void InitBMPFont(const float &fSize);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DrawString
	//
	//	Last Modified: 	2007/01/22
	//
	//	Purpose:		Draws a string of characters directly to the screen
	//
	//	In:				the string to display to the screen and the position
	//
	//	Notes:			needs to be called after CLEAR() and before PRESENT()
	//
	//////////////////////////////////////////////////////////////////////////
	void DrawString(const int &nFontSprite, const char *szText, const float &nPosX, const float &nPosY, const D3DXCOLOR &d3dColor, const float &nScale, const float &fSpace = 0.0f);
};
