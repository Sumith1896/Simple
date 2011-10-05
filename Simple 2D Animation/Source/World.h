//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	World.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	controls all the objects in the world
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Windows.h>
#include <stdio.h>
#include "Helpers.h"
#include "BlockObject.h"
#include "NewTerrain.h"
#include "Camera.h"
#include <vector>
#include <list>
using std::vector;
using std::list;

static const unsigned int arrayX = 16;
static const unsigned int arrayY = 16;
static const unsigned int arrayZ = 16;

static const unsigned int worldarray = 8;

struct CACHE_ALIGN WorldChunk
{
	BlockObject				BlockArray[arrayX][arrayY][arrayZ];
	list<BlockObject*>		VisibleArray;
	D3DXVECTOR3		d3dHigh;		//high values of the bounding
	D3DXVECTOR3		d3dLow;			//low values of the bounding
};

class CACHE_ALIGN World  
{
private:

	CCamera			*m_pCamera;
	NewTerrain		*m_pNewTerrain;
	WorldChunk		chunk[worldarray][worldarray][worldarray];

	D3DXMATRIX		VisibleArrayDirt[arrayX*arrayY*arrayZ*3];
	D3DXMATRIX		VisibleArrayGravel[arrayX*arrayY*arrayZ*3];
	int drawcountdirt;
	int drawcountgravel;
	static	World *m_pInstance;			//instance to the singleton	

	World(){};
	World(const World &a){};
	World &operator=(const World &a){};

public:
	int draw;
	//	~World: Destructor
	~World(){};

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
	static World *GetInstance();

	void Init();

	void Cull();

	void Draw();

	void LoadChunk();

	BlockObject *GetBlock(int x, int y, int z)
	{
		int nX = (x/arrayX);
		int nY = (y/arrayY);
		int nZ = (z/arrayZ);

		return &chunk[nX][nY][nZ].BlockArray[(x%arrayX)][(y%arrayY)][(z%arrayZ)];
	}
};