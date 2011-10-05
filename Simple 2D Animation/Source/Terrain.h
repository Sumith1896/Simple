//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	CTerrain.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the terrain
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Direct3D.h"
#include "EffectsManager.h"
#include "TextureManager.h"
#include "Helpers.h"
#include <fstream>
#include <vector>
using namespace std;

//Terrain size
#define TERRAIN_X			16
#define TERRAIN_Y			16
#define TERRAIN				1025
#define PIECES				64
#define STRETCH				64
#define TERRIANFILENAME		"heightmap1024.raw"

struct TerrainChunk
{
	IDirect3DVertexBuffer9		*pTerrainVB;			//Terrain vertex buffer
	IDirect3DIndexBuffer9		*pTerrainIB;			//Terrain index buffer
	D3DXVECTOR3					m_d3dHighVector;		//highest zy
	D3DXVECTOR3					m_d3dLowVector;			//lowest xyz values
};

class CTerrain
{
private:

	D3DXVECTOR3					m_d3dNormals[(TERRAIN * TERRAIN)];
	TerrainChunk				m_TerrainArray[PIECES * PIECES];		//All the small pieces of terrain
	D3DXMATRIX					m_3d3GroundMatrix;


	CEffectsManager				*m_pEffectsManager;			//the effects manager
	CTextureManager				*m_pTextureManager;			//Texturemanager pointer
	IDirect3DDevice9			*m_pDirectx;				//DirectX device pointer

	int							m_pTex0;					//terrain texture0
	int							m_pTex1;					//terrain texture1
	int							m_pTex2;					//terrain texture2
	int							m_pTex3;					//terrain texture3

	int							m_pAlpha0;					//texture alpha0
	int							m_pAlpha1;					//texture alpha1
	int							m_pAlpha2;					//texture alpha2
	int							m_pAlpha3;					//texture alpha3

	DWORD						m_dwTerrainVertices;		//number of vertices 
	DWORD						m_dwTerrainPrimitives;		//number of primitives

	static CTerrain				*m_pinstance;			//instance to the singleton	


	CTerrain(){};
	CTerrain(const CTerrain &a){};
	CTerrain &operator=(const CTerrain &a){};


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
	static CTerrain *GetInstance();

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
	//	Function: 		CreateTerrain
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Creates terrain
	//
	//////////////////////////////////////////////////////////////////////////
	void CreateTerrain();

	TerrainChunk MakeTerrain(int &nOffsetX, int &nOffsetY, int &nSizeX, int &nSizeY, unsigned short *nHeightMap);

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
	void Draw();
};