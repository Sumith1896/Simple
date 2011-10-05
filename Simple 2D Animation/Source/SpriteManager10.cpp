////////////////////////////////////////////////////////////////////////////
////
////	Filename: 	SpriteManager10.h
////
////	Author:		Nicholas Legg
////
////	Purpose:	Controls all the sprites being used
////
////////////////////////////////////////////////////////////////////////////
//#include "SpriteManager10.h"
//
////	Initialize the static variable member.
//CSpriteManager10 *CSpriteManager10::m_pInstance = NULL;
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		GetInstance
////
////	Last Modified: 	07/08/2006
////
////	Purpose:		Creates the first instance of this class and returns it's address.
////
////	Out:			pointer to this instance
////
////////////////////////////////////////////////////////////////////////////
//CSpriteManager10 *CSpriteManager10::GetInstance()
//{
//	//if the pointer is NULL call new
//	if (!m_pInstance)
//		m_pInstance = new CSpriteManager10;
//
//	//Return the address of the instance.
//	return m_pInstance;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		DeleteInstance
////
////	Last Modified: 	07/08/2006
////
////	Purpose:		Delete the instance of the class, and set the pointer to NULL
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::DeleteInstance()
//{
//	//delete the pointer, and set it to NULL
//	SAFE_DELETE(m_pInstance);
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		Shutdown
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Initializes the SpriteManager10 class
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::Shutdown()
//{
//	UnloadAllSprites();
//	m_vSprites.clear();
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		InitSpriteManager
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Initializes the SpriteManager10 class
////
////	In:				DirectX Device pointer and Sprite object pointer
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::InitSpriteManager(ID3DXSprite *d3dSprite)
//{
//	//check the pointers passed over
//	assert(g_pd3dDevice);
//	assert(d3dSprite);
//
//	//save the pointers
//	m_d3dSprite = d3dSprite;
//
//	//clear the vector
//	m_vSprites.clear();
//
//	//m_pTextureManager	= CTextureManager10::GetInstance();
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		LoadSprite
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Loads a sprite from an index to a texture from the
////					texture manager
////
////	In:				index to a texture from the texturemanager and bool if
////					it's static or not
////
////	Out:			index to the sprite being loaded
////
////////////////////////////////////////////////////////////////////////////
//int CSpriteManager10::LoadSprite(const int &nTexture, bool bStatic)
//{
//	//create a new sprite
//	tSprite *pSprite = new tSprite;
//
//	//surface description 
//	D3D10_TEXTURE2D_DESC	d3dsd;
//	memset(&d3dsd, 0, sizeof(d3dsd));
//
//	//ID3D10Resource* pTexture = NULL;
//	ID3D10Texture2D *pTexture2D = (ID3D10Texture2D*)m_pTextureManager->GetTexture(nTexture);
//
//	//get texture surface description
//	pTexture2D->GetDesc(&d3dsd);
//
//	//setup the sprite
//	pSprite->d3dColor.a		= 1.0f;							//alpha channel 0-255 
//	pSprite->d3dColor.r		= 1.0f;							//red channel 0-255
//	pSprite->d3dColor.g		= 1.0f;							//green channel 0-255
//	pSprite->d3dColor.b		= 1.0f;							//blue channel 0-255
//	pSprite->d3dCenter.x	= (float)(d3dsd.Width / 2.0f);	//set the center of the sprite X
//	pSprite->d3dCenter.y	= (float)(d3dsd.Height / 2.0f);	//set the center of the sprite Y
//	pSprite->d3dCenter.z	= 0.0f;							//set the center of the sprite Z
//	pSprite->bDynamic		= !bStatic;						//set whether the sprite is dynamic
//
//	//apply the identity matrix.
//	D3DXMatrixIdentity(&pSprite->d3dMat);
//
//	//push the sprite into the vector
//	m_vSprites.push_back(pSprite);
//
//	//return the ID
//	return (int)(m_vSprites.size() - 1);
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		LoadSprite
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Loads a sprite from a file
////	
////	In:				filename of the texture to load as a sprite and bool if
////					it's static or not
////
////	Out:			index to the sprite being loaded
////
////////////////////////////////////////////////////////////////////////////
//int CSpriteManager10::LoadSprite(const char *szFileName, bool bStatic)
//{
//	//create a new sprite
//	tSprite *pSprite = new tSprite;
//
//	pSprite->nTexture = m_pTextureManager->LoadTexture(szFileName);
//
//	//surface description 
//	D3D10_TEXTURE2D_DESC	d3dsd;
//	memset(&d3dsd, 0, sizeof(d3dsd));
//
//	//ID3D10Resource* pTexture = NULL;
//	ID3D10Texture2D *pTexture2D = (ID3D10Texture2D*)m_pTextureManager->GetTexture(pSprite->nTexture);
//
//	//get texture surface description
//	pTexture2D->GetDesc(&d3dsd);
//
//	//setup the sprite
//	pSprite->d3dColor.a		= 1.0f;							//alpha channel 0-255 
//	pSprite->d3dColor.r		= 1.0f;							//red channel 0-255
//	pSprite->d3dColor.g		= 1.0f;							//green channel 0-255
//	pSprite->d3dColor.b		= 1.0f;							//blue channel 0-255
//	pSprite->d3dCenter.x	= (float)(d3dsd.Width / 2.0f);	//set the center of the sprite X
//	pSprite->d3dCenter.y	= (float)(d3dsd.Height / 2.0f);	//set the center of the sprite Y
//	pSprite->d3dCenter.z	= 0.0f;							//set the center of the sprite Z
//	pSprite->bDynamic		= !bStatic;						//set whether the sprite is dynamic
//
//	//apply the identity matrix.
//	D3DXMatrixIdentity(&pSprite->d3dMat);
//
//	//push the sprite into the vector
//	m_vSprites.push_back(pSprite);
//
//	//return the ID
//	return (int)(m_vSprites.size() - 1);
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		DrawSprite
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Draws a sprite based on the ID passed
////
////	In:				index to the sprite
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::DrawSprite(const unsigned int &nSpriteID)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return;
//
//	//apply the world matrix.
//	m_d3dSprite->SetTransform(&m_vSprites[nSpriteID]->d3dMat);
//
//	//draw the sprite!
//	//m_d3dSprite->Draw(m_pTextureManager->GetTexture(m_vSprites[nSpriteID]->nTexture), NULL, &m_vSprites[nSpriteID]->d3dCenter, NULL, m_vSprites[nSpriteID]->d3dColor);
//
//	//apply the identity matrix.
//	if(m_vSprites[nSpriteID]->bDynamic)
//		D3DXMatrixIdentity(&m_vSprites[nSpriteID]->d3dMat);
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		DrawSprite
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Draws a sprite based on the ID passed
////
////	In:				index to the sprite and color to tint it
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::DrawSprite(const unsigned int &nSpriteID, const D3DXCOLOR &d3dColor)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return;
//
//	//apply the world matrix.
//	m_d3dSprite->SetTransform(&m_vSprites[nSpriteID]->d3dMat);
//
//	//draw the sprite!
//	//m_d3dSprite->Draw(m_pTextureManager->GetTexture(m_vSprites[nSpriteID]->nTexture), NULL, &m_vSprites[nSpriteID]->d3dCenter, NULL, d3dColor);
//
//	//apply the identity matrix.
//	if(m_vSprites[nSpriteID]->bDynamic)
//		D3DXMatrixIdentity(&m_vSprites[nSpriteID]->d3dMat);
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		DrawSprite
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Draws a sprite based on the ID passed
////
////	In:				index to the sprite and rect of the section to draw
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::DrawSprite(const unsigned int &nSpriteID, const RECT &spriteRect, const D3DXCOLOR &d3dColor)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return;
//
//	//apply the world matrix.
//	m_d3dSprite->SetTransform(&m_vSprites[nSpriteID]->d3dMat);
//
//	//draw the sprite!
//	//m_d3dSprite->Draw(m_pTextureManager->GetTexture(m_vSprites[nSpriteID]->nTexture), &spriteRect, &m_vSprites[nSpriteID]->d3dCenter, NULL, d3dColor);
//
//	//apply the identity matrix.
//	if(m_vSprites[nSpriteID]->bDynamic)
//		D3DXMatrixIdentity(&m_vSprites[nSpriteID]->d3dMat);
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		RotateSprite
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Rotates a sprite based on the rotate amount
////
////	In:				index to the sprite and rotation amount
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::RotateSprite(const unsigned int &nSpriteID, const float &fRotate)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return;
//
//	//temp matrix to use
//	D3DXMATRIX d3dMat;
//
//	//rotate that matrix
//	D3DXMatrixRotationZ(&d3dMat, fRotate);
//
//	//apply the matrix
//	m_vSprites[nSpriteID]->d3dMat *= d3dMat;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		ScaleSprite
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Scales a sprite based on amount passed over
////
////	In:				index to sprite and amount to scale it by
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::ScaleSprite(const unsigned int &nSpriteID, const float &fScaleWidth, const float &fScaleHeight)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return;
//
//	//temp matrix to use
//	D3DXMATRIX	d3dMat;
//
//	//scale the matrix
//	D3DXMatrixScaling(&d3dMat, fScaleWidth, fScaleHeight, 0.0f);
//
//	//apply the matrix
//	m_vSprites[nSpriteID]->d3dMat *= d3dMat;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		TranslateSprite
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Translate a sprite based on amount passed over
////
////	In:				index to sprite and amount to translate
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::TranslateSprite(const unsigned int &nSpriteID, const float &fPositionX, const float &fPositionY)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return;
//
//	//temp matrix to use
//	D3DXMATRIX	d3dMat;
//
//	////translate the matrix
//	D3DXMatrixTranslation(&d3dMat, fPositionX, fPositionY, 0);
//
//	//apply the matrix
//	m_vSprites[nSpriteID]->d3dMat *= d3dMat;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		GetWidth
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Returns the width of the sprite back
////
////	In:				index to sprite
////
////	Out:			width of the sprite
////
////////////////////////////////////////////////////////////////////////////
//int CSpriteManager10::GetWidth(const unsigned int &nSpriteID)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return 0;
//
//	//surface description 
//	D3DSURFACE_DESC	d3dsd;
//	memset(&d3dsd, 0, sizeof(d3dsd));
//
//	//get texture surface description
//	//m_pTextureManager->GetTexture(m_vSprites[nSpriteID]->nTexture)->GetLevelDesc(0, &d3dsd);
//
//	//returns the sprite width
//	return (int)d3dsd.Width;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		GetHeight
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Returns the width of the sprite back
////
////	In:				index to sprite
////
////	Out:			height of the sprite
////
////////////////////////////////////////////////////////////////////////////
//int CSpriteManager10::GetHeight(const unsigned int &nSpriteID)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return 0;
//
//	//surface description 
//	D3DSURFACE_DESC	d3dsd;
//	memset(&d3dsd, 0, sizeof(d3dsd));
//
//	//get texture surface description
//	//m_pTextureManager->GetTexture(m_vSprites[nSpriteID]->nTexture)->GetLevelDesc(0, &d3dsd);
//
//	//return the sprite height
//	return (int)d3dsd.Height;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		SetCenter
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Sets the center point of the sprite
////
////	In:				index to sprite and posistion to set as the center
////
////////////////////////////////////////////////////////////////////////////
//D3DXVECTOR3 CSpriteManager10::GetCenter(const unsigned int &nSpriteID)
//{
//	D3DXVECTOR3 temp;
//
//	temp.x = 0.0f;
//	temp.y = 0.0f;
//	temp.z = 0.0f;
//
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return temp;
//
//	//get texture surface description
//	return m_vSprites[nSpriteID]->d3dCenter;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		SetCenter
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Sets the center point of the sprite
////
////	In:				index to sprite and posistion to set as the center
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::SetCenter(const unsigned int &nSpriteID, const float &fCenterX, const float &fCenterY)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return;
//
//	//set the new center point
//	m_vSprites[nSpriteID]->d3dCenter.x = fCenterX;
//	m_vSprites[nSpriteID]->d3dCenter.y = fCenterY;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		SetColor
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Sets the color tint of the sprite
////
////	In:				index of sprite and color to set the sprite to
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::SetColor(const unsigned int &nSpriteID, const float &fColorRed, const float &fColorGreen, const float &fColorBlue, const float &fColorAlpha)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return;
//
//	//set the new color 
//	m_vSprites[nSpriteID]->d3dColor.r = fColorRed;
//	m_vSprites[nSpriteID]->d3dColor.g = fColorGreen;
//	m_vSprites[nSpriteID]->d3dColor.b = fColorBlue;
//	m_vSprites[nSpriteID]->d3dColor.a = fColorAlpha;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		SetMatrix
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Sets the matrix of the sprite
////
////	In:				index to sprite and new matrix the sprite will have
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::SetMatrix(const unsigned int &nSpriteID, D3DXMATRIX d3dMat)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return;
//
//	//set the new matrix 
//	m_vSprites[nSpriteID]->d3dMat = d3dMat;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		GetMatrix
////
////	Last Modified: 	2006/08/04
////
////	Purpose:		Gets the matrix of the sprite
////
////	In:				index to sprite
////
////	Out:			matrix of the sprite
////
////////////////////////////////////////////////////////////////////////////
//D3DXMATRIX CSpriteManager10::GetMatrix(const unsigned int &nSpriteID)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//	{
//		//temp matrix to use
//		D3DXMATRIX d3dBadMatrix;
//
//		//set temp the the identity
//		D3DXMatrixIdentity(&d3dBadMatrix);
//
//		//return the identity
//		return d3dBadMatrix;
//	}
//
//	//return the matrix 
//	return m_vSprites[nSpriteID]->d3dMat;
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		UnloadSprite
////
////	Last Modified: 	02/14/2007
////
////	Purpose:		Gets the matrix of the sprite
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::UnloadSprite(const unsigned int &nSpriteID)
//{
//	//check if the index is out of the array bounds
//	if(nSpriteID > (m_vSprites.size() - 1) || !m_vSprites[nSpriteID])
//		return;
//
//	//delete the sprite
//	SAFE_DELETE(m_vSprites[nSpriteID]);
//}
//
////////////////////////////////////////////////////////////////////////////
//// 
////	Function: 		UnloadAllSprites
////
////	Last Modified: 	02/14/2007
////
////	Purpose:		Gets the matrix of the sprite
////
////////////////////////////////////////////////////////////////////////////
//void CSpriteManager10::UnloadAllSprites()
//{
//	//loop through all the sprites and delete them
//	for(int i = 0; i < (int)m_vSprites.size(); i++)
//		UnloadSprite(i);
//
//	m_vSprites.clear();
//}