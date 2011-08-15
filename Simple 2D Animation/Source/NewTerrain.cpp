//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	NewTerrain.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the terrain
//
//////////////////////////////////////////////////////////////////////////
#include "NewTerrain.h"
#include <D3dx9math.h>

IDirect3DVertexBuffer9*         g_pVBInstanceData = 0;

//Here is the format of the box positions within the pile:
struct BOX_INSTANCEDATA_POS
{
    D3DCOLOR color;
    BYTE x;
    BYTE y;
    BYTE z;
    BYTE rotation;
};

//initialize the static variable member(s)
NewTerrain *NewTerrain::m_pinstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Delete the instance of the class, and set the pointer to NULL
//
//////////////////////////////////////////////////////////////////////////
void NewTerrain::DeleteInstance()
{
	SAFE_DELETE(m_pinstance);

	COUT << "NewTerrain::DeleteInstance() - SUCCESS" << endl; 

}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetInstance
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Creates the first instance of this class and returns it's address.
//
//////////////////////////////////////////////////////////////////////////
NewTerrain *NewTerrain::GetInstance()
{
	if(!m_pinstance)
		m_pinstance = new NewTerrain;

	return m_pinstance;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitTerrain
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Initializes the terrain class
//
//////////////////////////////////////////////////////////////////////////
void NewTerrain::InitTerrain()
{
	COUT << "NewTerrain::InitTerrain() - START" << endl;

	//Set the directx device pointer
	m_pDirectx			= CDirectX9::GetInstance()->GetD3DDevice();
	m_pTextureManager	= CTextureManager::GetInstance();
	m_pCamera			= CCamera::GetInstance();
	
	D3DXMatrixIdentity(&m_3d3GroundMatrix);

	int ntxt = m_pTextureManager->LoadTexture("textures\\ground\\test.dds");
	CreateBlock(1, "Nick Test", ntxt);
	ntxt = m_pTextureManager->LoadTexture("textures\\ground\\gravel02.dds");
	CreateBlock(1, "Nick Simple", ntxt);
	CreateBlock(1, "Nick Ground", ntxt);

		//Set the vertex format
	m_pDirectx->SetFVF(FVF_NORMAL_TEX2);
	m_pDirectx->SetTexture(0, m_pTextureManager->GetTexture(m_vBlocks[0]->pTexture01));
	m_pDirectx->SetTexture(1, m_pTextureManager->GetTexture(m_vBlocks[0]->pTexture01));


	COUT << "NewTerrain::InitTerrain() - END" << endl;
}

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
int NewTerrain::CreateBlock(const unsigned int nSize, const char *szName, const unsigned nTextureID)
{
	//make sure szName isn't bad
	if(!szName)
	{
		//anything less than 0 is junk
		return -1;
	}


	//loop through all of our currently loaded blocks
	for(int i = 0; i < (int)m_vBlocks.size(); i++)
	{
		//if we find the block is already loaded
		if(strcmp(m_vBlocks[i]->szName, szName) == 0)
		{
			//anything less than 0 is junk
			return -1;
		}
	}

	//time to make the new block
	//for now all blocks are square and 6*6 prims
	tTerrainBlock *NewBlock = new tTerrainBlock;

	NewBlock->pTerrainVB	= NULL;			//Terrain vertex buffer
	NewBlock->pTerrainIB	= NULL;			//Terrain index buffer
	NewBlock->pTexture01	= nTextureID;   //terrain texture0
	NewBlock->nNumVerts		= 4*6;			//number of verts
	NewBlock->nNumPrims		= 6*6;			//number of prims
	D3DXMatrixIdentity(&NewBlock->d3dBlockMatrix);

	NormalTex2Vertex *pVertexData = NULL;
	short *pIndexData = NULL;

	//////////////////////////////////////////////////////////////////////////
	//TERRAIN TIME!!!
	//////////////////////////////////////////////////////////////////////////
	m_pDirectx->CreateVertexBuffer(sizeof(NormalTex2Vertex) * NewBlock->nNumVerts, D3DUSAGE_WRITEONLY, FVF_NORMAL_TEX2, D3DPOOL_MANAGED, &NewBlock->pTerrainVB, NULL);
	NewBlock->pTerrainVB->Lock(0,0,(void**)&pVertexData,0);


	//////////////////////////////////////////////////////////////////////////
	//FRONT FACE START
	//////////////////////////////////////////////////////////////////////////
	pVertexData[0]._x = 0.0f;
	pVertexData[0]._y = 0.0f;	
	pVertexData[0]._z = 0.0f;
	pVertexData[0]._nx = 0.0f;
	pVertexData[0]._ny = 0.0f;
	pVertexData[0]._nz = -1.0f;
	pVertexData[0]._u1 = 0.0f;
	pVertexData[0]._v1 = 1.0f;
	pVertexData[0]._u2 = 0.0f;
	pVertexData[0]._v2 = 1.0f;

	pVertexData[1]._x = 0.0f;
	pVertexData[1]._y = 1.0f * nSize;	
	pVertexData[1]._z = 0.0f;
	pVertexData[1]._nx = 0.0f;
	pVertexData[1]._ny = 0.0f;
	pVertexData[1]._nz = -1.0f;
	pVertexData[1]._u1 = 0.0f;
	pVertexData[1]._v1 = 0.0f;
	pVertexData[1]._u2 = 0.0f;
	pVertexData[1]._v2 = 0.0f;

	pVertexData[2]._x = 1.0f * nSize;
	pVertexData[2]._y = 1.0f * nSize;	
	pVertexData[2]._z = 0.0f;
	pVertexData[2]._nx = 0.0f;
	pVertexData[2]._ny = 0.0f;
	pVertexData[2]._nz = -1.0f;
	pVertexData[2]._u1 = 1.0f;
	pVertexData[2]._v1 = 0.0f;
	pVertexData[2]._u2 = 1.0f;
	pVertexData[2]._v2 = 0.0f;

	pVertexData[3]._x = 1.0f * nSize;
	pVertexData[3]._y = 0.0f;	
	pVertexData[3]._z = 0.0f;
	pVertexData[3]._nx = 0.0f;
	pVertexData[3]._ny = 0.0f;
	pVertexData[3]._nz = -1.0f;
	pVertexData[3]._u1 = 1.0f;
	pVertexData[3]._v1 = 1.0f;
	pVertexData[3]._u2 = 1.0f;
	pVertexData[3]._v2 = 1.0f;
	//////////////////////////////////////////////////////////////////////////
	//FRONT FACE END
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//RIGHT FACE START
	//////////////////////////////////////////////////////////////////////////
	pVertexData[4]._x = 1.0f * nSize;
	pVertexData[4]._y = 0.0f;	
	pVertexData[4]._z = 0.0f;
	pVertexData[4]._nx = 1.0f;
	pVertexData[4]._ny = 0.0f;
	pVertexData[4]._nz = 0.0f;
	pVertexData[4]._u1 = 0.0f;
	pVertexData[4]._v1 = 1.0f;
	pVertexData[4]._u2 = 0.0f;
	pVertexData[4]._v2 = 1.0f;

	pVertexData[5]._x = 1.0f * nSize;
	pVertexData[5]._y = 1.0f * nSize;	
	pVertexData[5]._z = 0.0f;
	pVertexData[5]._nx = 1.0f;
	pVertexData[5]._ny = 0.0f;
	pVertexData[5]._nz = 0.0f;
	pVertexData[5]._u1 = 0.0f;
	pVertexData[5]._v1 = 0.0f;
	pVertexData[5]._u2 = 0.0f;
	pVertexData[5]._v2 = 0.0f;

	pVertexData[6]._x = 1.0f * nSize;
	pVertexData[6]._y = 1.0f * nSize;	
	pVertexData[6]._z = 1.0f * nSize;
	pVertexData[6]._nx = 1.0f;
	pVertexData[6]._ny = 0.0f;
	pVertexData[6]._nz = 0.0f;
	pVertexData[6]._u1 = 1.0f;
	pVertexData[6]._v1 = 0.0f;
	pVertexData[6]._u2 = 1.0f;
	pVertexData[6]._v2 = 0.0f;

	pVertexData[7]._x = 1.0f * nSize;
	pVertexData[7]._y = 0.0f;	
	pVertexData[7]._z = 1.0f * nSize;
	pVertexData[7]._nx = 1.0f;
	pVertexData[7]._ny = 0.0f;
	pVertexData[7]._nz = 0.0f;
	pVertexData[7]._u1 = 1.0f;
	pVertexData[7]._v1 = 1.0f;
	pVertexData[7]._u2 = 1.0f;
	pVertexData[7]._v2 = 1.0f;
	//////////////////////////////////////////////////////////////////////////
	//RIGHT FACE END
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//BACK FACE START
	//////////////////////////////////////////////////////////////////////////
	pVertexData[8]._x = 1.0f * nSize;
	pVertexData[8]._y = 0.0f;	
	pVertexData[8]._z = 1.0f * nSize;
	pVertexData[8]._nx = 0.0f;
	pVertexData[8]._ny = 0.0f;
	pVertexData[8]._nz = 1.0f;
	pVertexData[8]._u1 = 0.0f;
	pVertexData[8]._v1 = 1.0f;
	pVertexData[8]._u2 = 0.0f;
	pVertexData[8]._v2 = 1.0f;

	pVertexData[9]._x = 1.0f * nSize;
	pVertexData[9]._y = 1.0f * nSize;	
	pVertexData[9]._z = 1.0f * nSize;
	pVertexData[9]._nx = 0.0f;
	pVertexData[9]._ny = 0.0f;
	pVertexData[9]._nz = 1.0f;
	pVertexData[9]._u1 = 0.0f;
	pVertexData[9]._v1 = 0.0f;
	pVertexData[9]._u2 = 0.0f;
	pVertexData[9]._v2 = 0.0f;

	pVertexData[10]._x = 0.0f;
	pVertexData[10]._y = 1.0f * nSize;	
	pVertexData[10]._z = 1.0f * nSize;
	pVertexData[10]._nx = 0.0f;
	pVertexData[10]._ny = 0.0f;
	pVertexData[10]._nz = 1.0f;
	pVertexData[10]._u1 = 1.0f;
	pVertexData[10]._v1 = 0.0f;
	pVertexData[10]._u2 = 1.0f;
	pVertexData[10]._v2 = 0.0f;

	pVertexData[11]._x = 0.0f;
	pVertexData[11]._y = 0.0f;	
	pVertexData[11]._z = 1.0f * nSize;
	pVertexData[11]._nx = 0.0f;
	pVertexData[11]._ny = 0.0f;
	pVertexData[11]._nz = 1.0f;
	pVertexData[11]._u1 = 1.0f;
	pVertexData[11]._v1 = 1.0f;
	pVertexData[11]._u2 = 1.0f;
	pVertexData[11]._v2 = 1.0f;
	//////////////////////////////////////////////////////////////////////////
	//BACK FACE END
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//LEFT FACE START
	//////////////////////////////////////////////////////////////////////////
	pVertexData[12]._x = 0.0f;
	pVertexData[12]._y = 0.0f;	
	pVertexData[12]._z = 1.0f * nSize;
	pVertexData[12]._nx = -1.0f;
	pVertexData[12]._ny = 0.0f;
	pVertexData[12]._nz = 0.0f;
	pVertexData[12]._u1 = 0.0f;
	pVertexData[12]._v1 = 1.0f;
	pVertexData[12]._u2 = 0.0f;
	pVertexData[12]._v2 = 1.0f;

	pVertexData[13]._x = 0.0f;
	pVertexData[13]._y = 1.0f * nSize;	
	pVertexData[13]._z = 1.0f * nSize;
	pVertexData[13]._nx = -1.0f;
	pVertexData[13]._ny = 0.0f;
	pVertexData[13]._nz = 0.0f;
	pVertexData[13]._u1 = 0.0f;
	pVertexData[13]._v1 = 0.0f;
	pVertexData[13]._u2 = 0.0f;
	pVertexData[13]._v2 = 0.0f;

	pVertexData[14]._x = 0.0f;
	pVertexData[14]._y = 1.0f * nSize;	
	pVertexData[14]._z = 0.0f;
	pVertexData[14]._nx = -1.0f;
	pVertexData[14]._ny = 0.0f;
	pVertexData[14]._nz = 0.0f;
	pVertexData[14]._u1 = 1.0f;
	pVertexData[14]._v1 = 0.0f;
	pVertexData[14]._u2 = 1.0f;
	pVertexData[14]._v2 = 0.0f;

	pVertexData[15]._x = 0.0f;
	pVertexData[15]._y = 0.0f;	
	pVertexData[15]._z = 0.0f;
	pVertexData[15]._nx = -1.0f;
	pVertexData[15]._ny = 0.0f;
	pVertexData[15]._nz = 0.0f;
	pVertexData[15]._u1 = 1.0f;
	pVertexData[15]._v1 = 1.0f;
	pVertexData[15]._u2 = 1.0f;
	pVertexData[15]._v2 = 1.0f;
	//////////////////////////////////////////////////////////////////////////
	//LEFT FACE END
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//TOP FACE START
	//////////////////////////////////////////////////////////////////////////
	pVertexData[16]._x = 0.0f;
	pVertexData[16]._y = 1.0f * nSize;	
	pVertexData[16]._z = 0.0f;
	pVertexData[16]._nx = 0.0f;
	pVertexData[16]._ny = 1.0f;
	pVertexData[16]._nz = 0.0f;
	pVertexData[16]._u1 = 0.0f;
	pVertexData[16]._v1 = 1.0f;
	pVertexData[16]._u2 = 0.0f;
	pVertexData[16]._v2 = 1.0f;

	pVertexData[17]._x = 0.0f;
	pVertexData[17]._y = 1.0f * nSize;	
	pVertexData[17]._z = 1.0f * nSize;
	pVertexData[17]._nx = 0.0f;
	pVertexData[17]._ny = 1.0f;
	pVertexData[17]._nz = 0.0f;
	pVertexData[17]._u1 = 0.0f;
	pVertexData[17]._v1 = 0.0f;
	pVertexData[17]._u2 = 0.0f;
	pVertexData[17]._v2 = 0.0f;

	pVertexData[18]._x = 1.0f * nSize;
	pVertexData[18]._y = 1.0f * nSize;	
	pVertexData[18]._z = 1.0f * nSize;
	pVertexData[18]._nx = 0.0f;
	pVertexData[18]._ny = 1.0f;
	pVertexData[18]._nz = 0.0f;
	pVertexData[18]._u1 = 1.0f;
	pVertexData[18]._v1 = 0.0f;
	pVertexData[18]._u2 = 1.0f;
	pVertexData[18]._v2 = 0.0f;

	pVertexData[19]._x = 1.0f * nSize;
	pVertexData[19]._y = 1.0f * nSize;	
	pVertexData[19]._z = 0.0f;
	pVertexData[19]._nx = 0.0f;
	pVertexData[19]._ny = 1.0f;
	pVertexData[19]._nz = 0.0f;
	pVertexData[19]._u1 = 1.0f;
	pVertexData[19]._v1 = 1.0f;
	pVertexData[19]._u2 = 1.0f;
	pVertexData[19]._v2 = 1.0f;
	//////////////////////////////////////////////////////////////////////////
	//TOP FACE END
	//////////////////////////////////////////////////////////////////////////


	//////////////////////////////////////////////////////////////////////////
	//BOTTOM FACE START
	//////////////////////////////////////////////////////////////////////////
	pVertexData[20]._x = 0.0f;
	pVertexData[20]._y = 0.0f;	
	pVertexData[20]._z = 1.0f * nSize;
	pVertexData[20]._nx = 0.0f;
	pVertexData[20]._ny = -1.0f;
	pVertexData[20]._nz = 0.0f;
	pVertexData[20]._u1 = 0.0f;
	pVertexData[20]._v1 = 1.0f;
	pVertexData[20]._u2 = 0.0f;
	pVertexData[20]._v2 = 1.0f;

	pVertexData[21]._x = 0.0f;
	pVertexData[21]._y = 0.0f;	
	pVertexData[21]._z = 0.0f;
	pVertexData[21]._nx = 0.0f;
	pVertexData[21]._ny = -1.0f;
	pVertexData[21]._nz = 0.0f;
	pVertexData[21]._u1 = 0.0f;
	pVertexData[21]._v1 = 0.0f;
	pVertexData[21]._u2 = 0.0f;
	pVertexData[21]._v2 = 0.0f;

	pVertexData[22]._x = 1.0f * nSize;
	pVertexData[22]._y = 0.0f;	
	pVertexData[22]._z = 0.0f;
	pVertexData[22]._nx = 0.0f;
	pVertexData[22]._ny = -1.0f;
	pVertexData[22]._nz = 0.0f;
	pVertexData[22]._u1 = 1.0f;
	pVertexData[22]._v1 = 0.0f;
	pVertexData[22]._u2 = 1.0f;
	pVertexData[22]._v2 = 0.0f;

	pVertexData[23]._x = 1.0f * nSize;
	pVertexData[23]._y = 0.0f;	
	pVertexData[23]._z = 1.0f * nSize;
	pVertexData[23]._nx = 0.0f;
	pVertexData[23]._ny = -1.0f;
	pVertexData[23]._nz = 0.0f;
	pVertexData[23]._u1 = 1.0f;
	pVertexData[23]._v1 = 1.0f;
	pVertexData[23]._u2 = 1.0f;
	pVertexData[23]._v2 = 1.0f;
	//////////////////////////////////////////////////////////////////////////
	//BOTTOM FACE END
	//////////////////////////////////////////////////////////////////////////
	
	NewBlock->pTerrainVB->Unlock();

	////////////////////////////////////////////////////////////////////////////
	////create index buffer and fill in indices
	////////////////////////////////////////////////////////////////////////////
	m_pDirectx->CreateIndexBuffer(sizeof(short) * NewBlock->nNumPrims * 3, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &NewBlock->pTerrainIB, NULL);
	NewBlock->pTerrainIB->Lock(0,0,(void**)&pIndexData,0);

	//FRONT FACE
	*pIndexData++ = 0;
	*pIndexData++ = 1;
	*pIndexData++ = 2;

	*pIndexData++ = 3;
	*pIndexData++ = 0;
	*pIndexData++ = 2;

	//RIGHT FACE
	*pIndexData++ = 4;
	*pIndexData++ = 5;
	*pIndexData++ = 6;

	*pIndexData++ = 7;
	*pIndexData++ = 4;
	*pIndexData++ = 6;

	//BACK FACE
	*pIndexData++ = 8;
	*pIndexData++ = 9;
	*pIndexData++ = 10;

	*pIndexData++ = 11;
	*pIndexData++ = 8;
	*pIndexData++ = 10;

	//LEFT FACE
	*pIndexData++ = 12;
	*pIndexData++ = 13;
	*pIndexData++ = 14;

	*pIndexData++ = 15;
	*pIndexData++ = 12;
	*pIndexData++ = 14;

	//TOP FACE
	*pIndexData++ = 16;
	*pIndexData++ = 17;
	*pIndexData++ = 18;

	*pIndexData++ = 19;
	*pIndexData++ = 16;
	*pIndexData++ = 18;

	//BOTTOM FACE
	*pIndexData++ = 20;
	*pIndexData++ = 21;
	*pIndexData++ = 22;

	*pIndexData++ = 23;
	*pIndexData++ = 20;
	*pIndexData++ = 22;
	
	NewBlock->pTerrainIB->Unlock();

	//save the name of the block
	NewBlock->szName = new char[128];
	strcpy(NewBlock->szName, szName);

	//push the new block into vector
	m_vBlocks.push_back(NewBlock);

	return ((int)m_vBlocks.size() - 1);
}

void NewTerrain::CalculateNormals(unsigned short *nHeightMap)
{
	//for(int z = 0; z < (TERRAIN - 1); z++)
	//{
	//	for(int x = 0; x < (TERRAIN - 1); x++)
	//	{
	//		D3DXVECTOR3 d3dEdge01;
	//		D3DXVECTOR3 d3dEdge02;

	//		D3DXVECTOR3 d3dPoint01;
	//		D3DXVECTOR3 d3dPoint02;
	//		D3DXVECTOR3 d3dPoint03;

	//		D3DXVECTOR3 d3dNormal;

	//		int nVert01 = x + z * (TERRAIN);
	//		int nVert02 = x + 1 + z * (TERRAIN);
	//		int nVert03 = x + (z + 1) * (TERRAIN);
	//		int nVert04 = x + 1 + (z + 1) * (TERRAIN);

	//		d3dPoint01.x = (float)x;
	//		d3dPoint01.y = (nHeightMap[nVert01] / 655.36f);
	//		d3dPoint01.z = (float)z;

	//		d3dPoint02.x = (float)x + 1.0f;
	//		d3dPoint02.y = (nHeightMap[nVert02] / 655.36f);
	//		d3dPoint02.z = (float)z;

	//		d3dPoint03.x = (float)x + 1.0f;
	//		d3dPoint03.y = (nHeightMap[nVert03] / 655.36f);
	//		d3dPoint03.z = (float)z + 1.0f;

	//		D3DXVec3Subtract(&d3dEdge01, &d3dPoint01 , &d3dPoint02); 
	//		D3DXVec3Subtract(&d3dEdge02, &d3dPoint01 , &d3dPoint03);

	//		D3DXVec3Cross(&d3dNormal, &d3dEdge02, &d3dEdge01);

	//		D3DXVec3Normalize(&d3dNormal, &d3dNormal);

	//		//1
	//		m_d3dNormals[nVert01].x += d3dNormal.x;
	//		m_d3dNormals[nVert01].y += d3dNormal.y;
	//		m_d3dNormals[nVert01].z += d3dNormal.z;

	//		//2
	//		m_d3dNormals[nVert02].x += d3dNormal.x;
	//		m_d3dNormals[nVert02].y += d3dNormal.y;
	//		m_d3dNormals[nVert02].z += d3dNormal.z;

	//		//3
	//		m_d3dNormals[nVert03].x += d3dNormal.x;
	//		m_d3dNormals[nVert03].y += d3dNormal.y;
	//		m_d3dNormals[nVert03].z += d3dNormal.z;

	//		//1
	//		D3DXVec3Normalize(&m_d3dNormals[nVert01], &m_d3dNormals[nVert01]);
	//		//2
	//		D3DXVec3Normalize(&m_d3dNormals[nVert02], &m_d3dNormals[nVert02]);
	//		//3
	//		D3DXVec3Normalize(&m_d3dNormals[nVert03], &m_d3dNormals[nVert03]);
	//		//4
	//		D3DXVec3Normalize(&m_d3dNormals[nVert04], &m_d3dNormals[nVert04]);


	//		d3dPoint01.x = (float)x;
	//		d3dPoint01.y = (nHeightMap[nVert01] / 655.36f);
	//		d3dPoint01.z = (float)z;

	//		d3dPoint02.x = (float)x + 1.0f;
	//		d3dPoint02.y = (nHeightMap[nVert03] / 655.36f);
	//		d3dPoint02.z = (float)z + 1.0f;

	//		d3dPoint03.x = (float)x;
	//		d3dPoint03.y = (nHeightMap[nVert04] / 655.36f);
	//		d3dPoint03.z = (float)z + 1.0f;

	//		D3DXVec3Subtract(&d3dEdge01, &d3dPoint01 , &d3dPoint02); 
	//		D3DXVec3Subtract(&d3dEdge02, &d3dPoint01 , &d3dPoint03);

	//		D3DXVec3Cross(&d3dNormal, &d3dEdge02, &d3dEdge01);

	//		D3DXVec3Normalize(&d3dNormal, &d3dNormal);
	//		
	//		//1
	//		m_d3dNormals[nVert01].x += d3dNormal.x;
	//		m_d3dNormals[nVert01].y += d3dNormal.y;
	//		m_d3dNormals[nVert01].z += d3dNormal.z;

	//		//3
	//		m_d3dNormals[nVert03].x += d3dNormal.x;
	//		m_d3dNormals[nVert03].y += d3dNormal.y;
	//		m_d3dNormals[nVert03].z += d3dNormal.z;

	//		//4
	//		m_d3dNormals[nVert04].x += d3dNormal.x;
	//		m_d3dNormals[nVert04].y += d3dNormal.y;
	//		m_d3dNormals[nVert04].z += d3dNormal.z;


	//		//1
	//		D3DXVec3Normalize(&m_d3dNormals[nVert01], &m_d3dNormals[nVert01]);
	//		//2
	//		D3DXVec3Normalize(&m_d3dNormals[nVert02], &m_d3dNormals[nVert02]);
	//		//3
	//		D3DXVec3Normalize(&m_d3dNormals[nVert03], &m_d3dNormals[nVert03]);
	//		//4
	//		D3DXVec3Normalize(&m_d3dNormals[nVert04], &m_d3dNormals[nVert04]);
	//	}
	//}
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Draw
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Draws our terrain
//
//////////////////////////////////////////////////////////////////////////
void NewTerrain::Draw(const unsigned int nBlockID, D3DXMATRIX *d3dBlockMatrix)
{
	COUT << "NewTerrain::Draw() - START" << endl;

	#ifdef _DEBUG

	//check the bounds of the array
	if(nBlockID > (unsigned int)(m_vBlocks.size() - 1))
	{
		COUT << "NewTerrain::Draw() - FAIL(block id out of array bounds)" << endl; 
		return;
	}

	//check the bounds of the array
	if(d3dBlockMatrix == NULL)
	{
		COUT << "NewTerrain::Draw() - FAIL(d3dBlockMatrix == NULL)" << endl; 
		return;
	}
	
	#endif
	//Take the color from the texture and take the alpha from the previous stage
	//m_pDirectx->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	//m_pDirectx->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
	//m_pDirectx->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);
		m_pDirectx->SetTexture(0, m_pTextureManager->GetTexture(m_vBlocks[nBlockID]->pTexture01));
	m_pDirectx->SetTexture(1, m_pTextureManager->GetTexture(m_vBlocks[nBlockID]->pTexture01));

	//m_pDirectx->SetTexture(0, m_pTextureManager->GetTexture(m_vBlocks[nBlockID]->pTexture01));

	//set the matrix for the mesh
	m_pDirectx->SetTransform(D3DTS_WORLD , d3dBlockMatrix);

	//	D3DXMatrixIdentity(&m_vMeshes[nMesh]->d3dMat);



	m_pDirectx->SetStreamSource(0, m_vBlocks[nBlockID]->pTerrainVB, 0, sizeof(NormalTex2Vertex));
	m_pDirectx->SetIndices(m_vBlocks[nBlockID]->pTerrainIB);


	m_pDirectx->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_vBlocks[nBlockID]->nNumVerts, 0, m_vBlocks[nBlockID]->nNumPrims);


	//m_pDirectx->SetTexture(0, NULL);
	//m_pDirectx->SetTexture(1, NULL);

	//m_pDirectx->SetTransform(D3DTS_WORLD , m_pCamera->GetViewMatrix());
}