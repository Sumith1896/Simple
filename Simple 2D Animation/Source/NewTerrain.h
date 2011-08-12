//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	NewTerrain.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the terrain
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Direct3D.h"
#include "TextureManager.h"
#include "Camera.h"
#include "Helpers.h"
#include <fstream>
#include <vector>
using namespace std;

////Terrain size
#define TERRAIN_X			16
#define TERRAIN_Y			16
#define TERRAIN				1025
#define PIECES				64
#define STRETCH				64
#define TERRIANFILENAME		"heightmap1024.raw"
#define TERRIANCHUNK		512	//8*8*8=512

struct CACHE_ALIGN tTerrainBlock
{
	IDirect3DVertexBuffer9		*pTerrainVB;			//Terrain vertex buffer
	IDirect3DIndexBuffer9		*pTerrainIB;			//Terrain index buffer
	int							pTexture01;				//terrain texture0
	DWORD						nNumVerts;				//number of verts
	DWORD						nNumPrims;				//number of prims
	char						*szName;				//name of the block

	D3DXMATRIX					d3dBlockMatrix;			//matrix for the block
};

class CACHE_ALIGN NewTerrain
{
private:

	tTerrainBlock				m_TestBlock;

	D3DXMATRIX					m_3d3GroundMatrix;

	CCamera						*m_pCamera;
	CTextureManager				*m_pTextureManager;			//Texturemanager pointer
	IDirect3DDevice9			*m_pDirectx;				//DirectX device pointer

	static NewTerrain			*m_pinstance;			//instance to the singleton	

	vector<tTerrainBlock *>		m_vBlocks;				//vector with all the different blocks


	NewTerrain(){};
	NewTerrain(const NewTerrain &a){};
	NewTerrain &operator=(const NewTerrain &a){};


public:

		bool	m_Switch;

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
	//	Function: 		GetInstance
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		Creates the first instance of this class and returns it's address.
	//
	//////////////////////////////////////////////////////////////////////////
	static NewTerrain *GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitTerrain
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the terrain class
	//
	//////////////////////////////////////////////////////////////////////////
	void InitTerrain();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		CreateBlock
	//
	//	Last Modified: 	07/19/2001
	//
	//	Purpose:		creates a new block and inserts it into the array
	//
	//	Returns:		index to the block created
	//
	//////////////////////////////////////////////////////////////////////////
	int CreateBlock(const unsigned int nSize, const char *szName, const unsigned nTextureID);

	void CalculateNormals(unsigned short *nHeightMap);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Draw
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Draws our terrain
	//
	//////////////////////////////////////////////////////////////////////////
	void NewTerrain::Draw(const unsigned int nBlockID, D3DXMATRIX *d3dBlockMatrix);
};