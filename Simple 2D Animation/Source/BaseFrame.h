#pragma once
#include <Windows.h>
#include <d3d9.h>
#include <d3dx9.h>
#include "SpriteManager.h"
#include "Helpers.h"
#include "Timer.h"
#include <fstream>
#include <vector>
using namespace std;

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")

class CBaseFrame
{
private:

	struct tPiece
	{
		int					nSpriteID;		//id for the sprite used
		double				fRotate;		//highest rotation value
		double				fOffsetX;		//offset from the center
		double				fOffsetY;		//offset from the center
		double				fScaleX;		//amount to scale it in the X
		double				fScaleY;		//amount to scale it in the Y
		tPiece				*pNode;			//next node
		bool				bBehind;		//whether it's in front of behind the base/torso
	};

	D3DXMATRIX			m_d3dMat;			//matrix for the whole frame
	D3DXVECTOR3			m_d3dHiBound;		//high bounding box values
	D3DXVECTOR3			m_d3dLoBound;		//high bounding box values
	int					m_nSpriteID;		//sprite id for the base/torso
	double				m_fRotate;			//rotation for the base/torso
	double				m_fScaleX;			//amount to scale it in the X
	double				m_fScaleY;			//amount to scale it in the Y

	int					m_nArrayPos;		//used for selecting	
	int					m_nPiecePos;		//used for selecting
	double				m_fInterTime;
	bool				m_bUpdateComplete;	//true if the update thread is done
	HANDLE				m_hDrawThreadHandle;	//handle to the drawing thread
	HANDLE				m_hUpdateThreadHandle;	//handle to the drawing thread

	vector<double>	m_vDefault;	
	vector<double>	m_vDefault2;
	vector<double>	m_vDefault3;	
	vector<double>	m_vDefault4;
	vector<double>	m_vDefault5;

	vector<tPiece*>		m_vNodes;			//all the pieces that connect to the base
	
	Timer				*m_pTimer;
	CSpriteManager		*m_pSpriteManager;	//pointer to the texture manager

public:
	CBaseFrame();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitFrame
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		starts the frame by creating a torso/base
	//
	//////////////////////////////////////////////////////////////////////////
	void InitFrame(const char *szFileName);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		AddOne
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Adds a one piece to the base/torso
	//
	//	Note:			fPosX/fPosY is a ratio between -1.0 <--> 1.0 of
	//					how far on the base to attach the leg
	//
	//////////////////////////////////////////////////////////////////////////
	void AddOne(const char *szFileName01, const double &fPosX, const double &fPosY, bool bBehind);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		AddThree
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Adds a 3piece to the base/torso
	//
	//	Note:			fPosX/fPosY is a ratio between -1.0 <--> 1.0 of
	//					how far on the base to attach the leg
	//
	//////////////////////////////////////////////////////////////////////////
	void AddThree(const char *szFileName01, const char *szFileName02, const char *szFileName03, const double &fPosX, const double &fPosY, bool bBehind);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Draw
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		draws the tree
	//
	//////////////////////////////////////////////////////////////////////////
	void Draw();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Update
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Updates the tree
	//
	//////////////////////////////////////////////////////////////////////////
	void Update();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		SelectPiece
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		selects the next piece of the frame
	//
	//////////////////////////////////////////////////////////////////////////
	void SelectNextPiece();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		SelectPrevArray
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		selects the prev array of the frame
	//
	//////////////////////////////////////////////////////////////////////////
	void SelectPrevArray();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		SelectNextArray
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		selects the previous array of the frame
	//
	//////////////////////////////////////////////////////////////////////////
	void SelectNextArray();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		RotatePiece
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		rotates the selected piece
	//
	//////////////////////////////////////////////////////////////////////////
	void RotatePiece(const double &fRotate);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		ScalePiece
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		scales the selected piece
	//
	//////////////////////////////////////////////////////////////////////////
	void ScalePiece(const double &fScaleX = 0.0f, const double &fScaleY = 0.0f);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		SaveValues
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		saves all the matrix values
	//
	//////////////////////////////////////////////////////////////////////////
	void SaveValues();

	void Interpolate();
};