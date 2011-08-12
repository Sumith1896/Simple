//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	BMPFont.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the BMP Font system
//
//////////////////////////////////////////////////////////////////////////
#include "BMPFont.h"

//Initialize the static variable member.
CBMPFont *CBMPFont::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetInstance
//
//	Last Modified: 	2007/01/22
//
//	Purpose:		Creates the first instance of this class and returns it's address.
//
//	Out:			pointer to this instance
//
//////////////////////////////////////////////////////////////////////////
CBMPFont *CBMPFont::GetInstance()
{
	//if the pointer is NULL call new
	if(!m_pInstance)
		m_pInstance = new CBMPFont;

	//Return the address of the instance.
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
//
//	Last Modified: 	2007/01/22
//
//	Purpose:		Delete the instance of the class, and set the pointer to NULL
//
//////////////////////////////////////////////////////////////////////////
void CBMPFont::DeleteInstance()
{
	//delete the pointer, and set it to NULL
	SAFE_DELETE(m_pInstance);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Shutdown
//
//	Last Modified: 	2007/01/22
//
//	Purpose:		Initializes the SpriteManager class
//
//////////////////////////////////////////////////////////////////////////
void CBMPFont::Shutdown()
{
	m_vFontTiles.clear();
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitBMPFont
//
//	Last Modified: 	2007/01/22
//
//	Purpose:		Initializes the BMPFont class
//
//	In:				size of each character
//
//////////////////////////////////////////////////////////////////////////
void CBMPFont::InitBMPFont(const float &fSize)
{
	m_pSpriteManager	= CSpriteManager::GetInstance();
	m_fFontSize			= fSize;

	RECT rPadding;
	rPadding.top = rPadding.bottom = rPadding.right = rPadding.left = 0;

	//fill the vector with dummy RECTs =p
	m_vFontTiles.resize(255, rPadding);

	for(int i = 0; i < 16; i++)
	{
		for(int j = 0; j < 16; j++)
		{
			if((i * 16 + j) > 159)
				continue;

			//create a RECT and values for it, then push it into the vector
			RECT rFontTile;

			rFontTile.top		=	(long)(i * fSize);
			rFontTile.bottom	=	(long)(rFontTile.top + fSize);
			rFontTile.left		=	(long)(j * fSize);
			rFontTile.right		=	(long)(rFontTile.left + fSize);

			m_vFontTiles[(i * 16 + j) + 32] = rFontTile;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DrawString
//
//	Last Modified: 	2007/01/22
//
//	Purpose:		Draws a string of characters directly to the screen
//
//	In:				the string to display to the screen and the position
//					and the image file to use as the font
//
//	Notes:			needs to be called after CLEAR() and before PRESENT()
//
//////////////////////////////////////////////////////////////////////////
void CBMPFont::DrawString(const int &nFontSprite, const char *szText, const float &nPosX, const float &nPosY, const D3DXCOLOR &d3dColor, const float &nScale, const float &fSpace)
{
	//check the character pointer before trying to use it
	assert(szText);

	//make sure the center is what it should be
	m_pSpriteManager->SetCenter(nFontSprite, 0.0f, 0.0f);

	//save the X position
	float X = nPosX;
	for(unsigned int i = 0; i < strlen(szText); i++)
	{
		//some simple error checking
		if(szText[i] < (char)0)
			continue;

		//scale, translate and then draw the font to the screen
		m_pSpriteManager->ScaleSprite(nFontSprite, nScale, nScale);
		m_pSpriteManager->TranslateSprite(nFontSprite, X, nPosY);
		m_pSpriteManager->DrawSprite(nFontSprite, m_vFontTiles[szText[i]], d3dColor);

		X += ((m_fFontSize * nScale)-fSpace);
	}
}