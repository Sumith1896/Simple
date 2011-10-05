//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	CTerrain.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the terrain
//
//////////////////////////////////////////////////////////////////////////
#include "Terrain.h"
#include <D3dx9math.h>

//initialize the static variable member(s)
CTerrain *CTerrain::m_pinstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Delete the instance of the class, and set the pointer to NULL
//
//////////////////////////////////////////////////////////////////////////
void CTerrain::DeleteInstance()
{
	SAFE_DELETE(m_pinstance);

	COUT << "CTerrain::DeleteInstance() - SUCCESS" << endl; 

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
CTerrain *CTerrain::GetInstance()
{
	if(!m_pinstance)
		m_pinstance = new CTerrain;

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
void CTerrain::InitTerrain()
{
	//Set the directx device pointer

	m_pDirectx			= CDirectX9::GetInstance()->GetD3DDevice();
	m_pTextureManager	= CTextureManager::GetInstance();
	m_pEffectsManager	= CEffectsManager::GetInstance();
	m_Switch			= true;
	m_pEffectsManager->InitEffectsManager(m_pDirectx);

	m_pEffectsManager->LoadEffect("SimpleSample.fx");

	m_pEffectsManager->SetDispatch(1);

	
	D3DXMatrixIdentity(&m_3d3GroundMatrix);

	m_dwTerrainVertices		= ((TERRAIN_X + 1) * (TERRAIN_Y + 1));
	m_dwTerrainPrimitives	= (TERRAIN_X * TERRAIN_Y * 2);

	m_pTex0 = m_pTextureManager->LoadTexture("textures\\ground\\grass01.dds");
	m_pTex1 = m_pTextureManager->LoadTexture("textures\\ground\\lava01.dds");
	m_pTex2 = m_pTextureManager->LoadTexture("textures\\ground\\dirt01.dds");
	m_pTex3 = m_pTextureManager->LoadTexture("textures\\ground\\grass04.dds");

	m_pAlpha0 = m_pTextureManager->LoadTexture("textures\\ground\\alphamap1.tga");
	m_pAlpha1 = m_pTextureManager->LoadTexture("textures\\ground\\alphamap2.tga");
	m_pAlpha2 = m_pTextureManager->LoadTexture("textures\\ground\\alphamap3.tga");
	m_pAlpha3 = m_pTextureManager->LoadTexture("textures\\ground\\alphamap4.tga");

	CreateTerrain();
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		CreateTerrain
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Creates terrain
//
//////////////////////////////////////////////////////////////////////////
void CTerrain::CreateTerrain()
{
	COUT << "CTerrain::CreateTerrain() - START" << endl;

	NormalTexVertex *pGrass = NULL;

	unsigned short	*nTempHeightMap = new unsigned short[(TERRAIN * TERRAIN)];	

	ifstream File;

	//Load height information from file
	File.open(TERRIANFILENAME,ios::binary);

	//Read the whole file in a short array
	for(int i = 0; i < (TERRAIN * TERRAIN); i++)
	{
		unsigned short temp = (File.get() << 8);
		unsigned short temp2 = File.get();
		temp += temp2;
		nTempHeightMap[i] = temp;
		m_d3dNormals[i].x = 0.0;
		m_d3dNormals[i].y = 1.0f;
		m_d3dNormals[i].z = 0.0f;
	}

	//close the heightmap file
	File.close();

	CalculateNormals(nTempHeightMap);

	int offsety = 0;
	int offsetx = 0;
	int offsety2 = TERRAIN_Y;
	int offsetx2 = TERRAIN_X;

	for(int i = 0; i < PIECES; i++)
	{		
		offsetx = 0;
		for(int j = 0; j < PIECES; j++)
		{
			m_TerrainArray[j + (i * PIECES)] = MakeTerrain(offsetx, offsety, offsetx2, offsety2, nTempHeightMap);
			offsetx += TERRAIN_X;
			offsetx2 += TERRAIN_X;
		}
		offsety += TERRAIN_Y;
		offsety2 += TERRAIN_Y;
	}

	delete [] nTempHeightMap;

	COUT << "CTerrain::CreateTerrain() - END" << endl;
}

TerrainChunk CTerrain::MakeTerrain(int &nOffsetX, int &nOffsetY, int &nSizeX, int &nSizeY, unsigned short *nHeightMap)
{
	NormalTex2Vertex *pVertexData = NULL;
	short *pIndexData = NULL;
	TerrainChunk tChunk;
	unsigned short aHeightMap[TERRAIN_X + 1][TERRAIN_X + 1];
	D3DXVECTOR3 tempNormals[TERRAIN_X + 1][TERRAIN_X + 1];

	//Fill up the arrays with the height values
	for(int i = 0; i < TERRAIN_X + 1; i++)
	{
		for(int j = 0; j < TERRAIN_X + 1; j++)
		{
			aHeightMap[i][j] = nHeightMap[(j + nOffsetY) + ((i + nOffsetX) * TERRAIN)];
			tempNormals[i][j] = m_d3dNormals[(j + nOffsetY) + ((i + nOffsetX) * TERRAIN)];
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//TERRAIN TIME!!!
	//////////////////////////////////////////////////////////////////////////
	m_pDirectx->CreateVertexBuffer(sizeof(NormalTex2Vertex) * m_dwTerrainVertices, D3DUSAGE_WRITEONLY, FVF_NORMAL_TEX2, D3DPOOL_MANAGED, &tChunk.pTerrainVB, NULL);
	tChunk.pTerrainVB->Lock(0,0,(void**)&pVertexData,0);

	int x2 = 0;
	int z2 = 0;

	for(int z = 0, z2 = 0; z < (TERRAIN_Y + 1); z++, z2+= STRETCH)
	{
		for(int x = 0, x2 = 0; x < (TERRAIN_X + 1); x++, x2+= STRETCH)
		{
			pVertexData[x + z * (TERRAIN_X + 1)]._x = (float)x2 + (nOffsetX * STRETCH);
			pVertexData[x + z * (TERRAIN_X + 1)]._y = (float)(aHeightMap[x][z] * 0.01f);	//make it a value between 0.0f - 100.0f 1310.72f
			pVertexData[x + z * (TERRAIN_X + 1)]._z = (float)z2 + (nOffsetY * STRETCH);
			pVertexData[x + z * (TERRAIN_X + 1)]._nx = (float)tempNormals[x][z].x;
			pVertexData[x + z * (TERRAIN_X + 1)]._ny = (float)tempNormals[x][z].y;
			pVertexData[x + z * (TERRAIN_X + 1)]._nz = (float)tempNormals[x][z].z;
			pVertexData[x + z * (TERRAIN_X + 1)]._u1 = 0.0f;
			pVertexData[x + z * (TERRAIN_X + 1)]._v1 = 0.0f;
			pVertexData[x + z * (TERRAIN_X + 1)]._u2 = 0.0f;
			pVertexData[x + z * (TERRAIN_X + 1)]._v2 = 0.0f;
		}
	}

	//////////////////////////////////////////////////////////////////////////
	//TEXTURE CORDS - START
	//////////////////////////////////////////////////////////////////////////
	for(int z = 0; z < TERRAIN_X; z++)
	{
		for(int x = 0; x < TERRAIN_X; x++)
		{
			//////////////////////////////////////////////////////////////////////////
			//1
			//////////////////////////////////////////////////////////////////////////
			//set the texture cords tex0
			pVertexData[x + z * (TERRAIN_X + 1)]._u1 = (float)((x + nOffsetX) * -(1.0f/512.0f));
			pVertexData[x + z * (TERRAIN_X + 1)]._v1 = (float)((z + nOffsetY) * (1.0f/512.0f));

			//set the texture cords tex1
			pVertexData[x + z * (TERRAIN_X + 1)]._u2 = (float)x;
			pVertexData[x + z * (TERRAIN_X + 1)]._v2 = (float)z;


			//////////////////////////////////////////////////////////////////////////
			//2
			//////////////////////////////////////////////////////////////////////////
			//set the texture cords tex0
			pVertexData[x + 1 + z * (TERRAIN_X + 1)]._u1 = (float)((x + 1 + nOffsetX) * -(1.0f/512.0f));
			pVertexData[x + 1 + z * (TERRAIN_X + 1)]._v1 = (float)((z + nOffsetY) * (1.0f/512.0f));


			//set the texture cords tex1
			pVertexData[x + 1 + z * (TERRAIN_X + 1)]._u2 = (float)x + 1.0f;
			pVertexData[x + 1 + z * (TERRAIN_X + 1)]._v2 = (float)z;


			//////////////////////////////////////////////////////////////////////////
			//3
			//////////////////////////////////////////////////////////////////////////
			//set the texture cords tex0
			pVertexData[x + (z + 1) * (TERRAIN_X + 1)]._u1 = (float)((x + nOffsetX) * -(1.0f/512.0f));
			pVertexData[x + (z + 1) * (TERRAIN_X + 1)]._v1 = (float)((z + 1 + nOffsetY) * (1.0f/512.0f));

			//set the texture cords tex1
			pVertexData[x + (z + 1) * (TERRAIN_X + 1)]._u2 = (float)x;
			pVertexData[x + (z + 1) * (TERRAIN_X + 1)]._v2 = (float)z + 1.0f;


			//////////////////////////////////////////////////////////////////////////
			//4
			//////////////////////////////////////////////////////////////////////////
			//set the texture cords tex0
			pVertexData[x + 1 + (z + 1) * (TERRAIN_X + 1)]._u1 = (float)((x + 1 + nOffsetX) * -(1.0f/512.0f));
			pVertexData[x + 1 + (z + 1) * (TERRAIN_X + 1)]._v1 = (float)((z + 1 + nOffsetY) * (1.0f/512.0f));

			//set the texture cords tex1
			pVertexData[x + 1 + (z + 1) * (TERRAIN_X + 1)]._u2 = (float)x + 1.0f;
			pVertexData[x + 1 + (z + 1) * (TERRAIN_X + 1)]._v2 = (float)z + 1.0f;
		}
	}
	//////////////////////////////////////////////////////////////////////////
	//TEXTURE CORDS - END
	//////////////////////////////////////////////////////////////////////////

	tChunk.pTerrainVB->Unlock();

	//////////////////////////////////////////////////////////////////////////
	//create index buffer and fill in indices
	//////////////////////////////////////////////////////////////////////////
	m_pDirectx->CreateIndexBuffer(sizeof(short) * m_dwTerrainPrimitives * 3, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &tChunk.pTerrainIB, NULL);
	tChunk.pTerrainIB->Lock(0,0,(void**)&pIndexData,0);

	for(int y = 0; y < TERRAIN_Y; y++)
	{
		for(int x = 0; x < TERRAIN_X; x++)
		{
			*pIndexData++ = x + y * (TERRAIN_X + 1);
			*pIndexData++ = x + 1 + (y + 1) * (TERRAIN_X + 1);
			*pIndexData++ = x + 1 + y * (TERRAIN_X + 1);

			*pIndexData++ = x + y * (TERRAIN_X + 1);
			*pIndexData++ = x + (y + 1) * (TERRAIN_X + 1);
			*pIndexData++ = x + 1 + (y + 1) * (TERRAIN_X + 1);
		}
	}

	tChunk.pTerrainIB->Unlock();

	return tChunk;
}

void CTerrain::CalculateNormals(unsigned short *nHeightMap)
{
	for(int z = 0; z < (TERRAIN - 1); z++)
	{
		for(int x = 0; x < (TERRAIN - 1); x++)
		{
			D3DXVECTOR3 d3dEdge01;
			D3DXVECTOR3 d3dEdge02;

			D3DXVECTOR3 d3dPoint01;
			D3DXVECTOR3 d3dPoint02;
			D3DXVECTOR3 d3dPoint03;

			D3DXVECTOR3 d3dNormal;

			int nVert01 = x + z * (TERRAIN);
			int nVert02 = x + 1 + z * (TERRAIN);
			int nVert03 = x + (z + 1) * (TERRAIN);
			int nVert04 = x + 1 + (z + 1) * (TERRAIN);

			d3dPoint01.x = (float)x;
			d3dPoint01.y = (nHeightMap[nVert01] / 655.36f);
			d3dPoint01.z = (float)z;

			d3dPoint02.x = (float)x + 1.0f;
			d3dPoint02.y = (nHeightMap[nVert02] / 655.36f);
			d3dPoint02.z = (float)z;

			d3dPoint03.x = (float)x + 1.0f;
			d3dPoint03.y = (nHeightMap[nVert03] / 655.36f);
			d3dPoint03.z = (float)z + 1.0f;

			D3DXVec3Subtract(&d3dEdge01, &d3dPoint01 , &d3dPoint02); 
			D3DXVec3Subtract(&d3dEdge02, &d3dPoint01 , &d3dPoint03);

			D3DXVec3Cross(&d3dNormal, &d3dEdge02, &d3dEdge01);

			D3DXVec3Normalize(&d3dNormal, &d3dNormal);

			//1
			m_d3dNormals[nVert01].x += d3dNormal.x;
			m_d3dNormals[nVert01].y += d3dNormal.y;
			m_d3dNormals[nVert01].z += d3dNormal.z;

			//2
			m_d3dNormals[nVert02].x += d3dNormal.x;
			m_d3dNormals[nVert02].y += d3dNormal.y;
			m_d3dNormals[nVert02].z += d3dNormal.z;

			//3
			m_d3dNormals[nVert03].x += d3dNormal.x;
			m_d3dNormals[nVert03].y += d3dNormal.y;
			m_d3dNormals[nVert03].z += d3dNormal.z;

			//1
			D3DXVec3Normalize(&m_d3dNormals[nVert01], &m_d3dNormals[nVert01]);
			//2
			D3DXVec3Normalize(&m_d3dNormals[nVert02], &m_d3dNormals[nVert02]);
			//3
			D3DXVec3Normalize(&m_d3dNormals[nVert03], &m_d3dNormals[nVert03]);
			//4
			D3DXVec3Normalize(&m_d3dNormals[nVert04], &m_d3dNormals[nVert04]);


			d3dPoint01.x = (float)x;
			d3dPoint01.y = (nHeightMap[nVert01] / 655.36f);
			d3dPoint01.z = (float)z;

			d3dPoint02.x = (float)x + 1.0f;
			d3dPoint02.y = (nHeightMap[nVert03] / 655.36f);
			d3dPoint02.z = (float)z + 1.0f;

			d3dPoint03.x = (float)x;
			d3dPoint03.y = (nHeightMap[nVert04] / 655.36f);
			d3dPoint03.z = (float)z + 1.0f;

			D3DXVec3Subtract(&d3dEdge01, &d3dPoint01 , &d3dPoint02); 
			D3DXVec3Subtract(&d3dEdge02, &d3dPoint01 , &d3dPoint03);

			D3DXVec3Cross(&d3dNormal, &d3dEdge02, &d3dEdge01);

			D3DXVec3Normalize(&d3dNormal, &d3dNormal);
			
			//1
			m_d3dNormals[nVert01].x += d3dNormal.x;
			m_d3dNormals[nVert01].y += d3dNormal.y;
			m_d3dNormals[nVert01].z += d3dNormal.z;

			//3
			m_d3dNormals[nVert03].x += d3dNormal.x;
			m_d3dNormals[nVert03].y += d3dNormal.y;
			m_d3dNormals[nVert03].z += d3dNormal.z;

			//4
			m_d3dNormals[nVert04].x += d3dNormal.x;
			m_d3dNormals[nVert04].y += d3dNormal.y;
			m_d3dNormals[nVert04].z += d3dNormal.z;


			//1
			D3DXVec3Normalize(&m_d3dNormals[nVert01], &m_d3dNormals[nVert01]);
			//2
			D3DXVec3Normalize(&m_d3dNormals[nVert02], &m_d3dNormals[nVert02]);
			//3
			D3DXVec3Normalize(&m_d3dNormals[nVert03], &m_d3dNormals[nVert03]);
			//4
			D3DXVec3Normalize(&m_d3dNormals[nVert04], &m_d3dNormals[nVert04]);
		}
	}
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
void CTerrain::Draw()
{
	//Take the color from the texture and take the alpha from the previous stage
	m_pDirectx->SetTextureStageState(1, D3DTSS_ALPHAOP, D3DTOP_SELECTARG1);
	m_pDirectx->SetTextureStageState(1, D3DTSS_ALPHAARG1, D3DTA_CURRENT);
	m_pDirectx->SetTextureStageState(1, D3DTSS_COLOROP, D3DTOP_MODULATE);

	//Set the vertex format
	m_pDirectx->SetFVF(FVF_NORMAL_TEX2);

	//m_pDirectx->SetTransform( D3DTS_WORLD, &m_3d3GroundMatrix );

	m_pEffectsManager->Begin(1, 1);

	m_pEffectsManager->BeginPass(1, 1);

	for(int i = 0; i < (PIECES * PIECES); i++)
	{
		//Set the stream source
		m_pDirectx->SetStreamSource(0, m_TerrainArray[i].pTerrainVB, 0, sizeof(NormalTex2Vertex));
		m_pDirectx->SetIndices(m_TerrainArray[i].pTerrainIB);

		//1st layer
		m_pDirectx->SetTexture(0, m_pTextureManager->GetTexture(m_pAlpha0));
		m_pDirectx->SetTexture(1, m_pTextureManager->GetTexture(m_pTex0));
		m_pDirectx->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwTerrainVertices, 0, m_dwTerrainPrimitives);

		//////2nd layer
		//m_pDirectx->SetTexture(0, m_pTextureManager->GetTexture(m_pAlpha1) );
		//m_pDirectx->SetTexture(1,m_pTextureManager->GetTexture(m_pTex1) );
		//m_pDirectx->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwTerrainVertices, 0, m_dwTerrainPrimitives);

		////3rd layer
		m_pDirectx->SetTexture(0, m_pTextureManager->GetTexture(m_pAlpha2) );
		m_pDirectx->SetTexture(1,m_pTextureManager->GetTexture(m_pTex2) );
		m_pDirectx->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwTerrainVertices, 0, m_dwTerrainPrimitives);

		//////4th layer
		//m_pDirectx->SetTexture(0, m_pTextureManager->GetTexture(m_pAlpha2) );
		//m_pDirectx->SetTexture(1,m_pTextureManager->GetTexture(m_pTex2) );
		//m_pDirectx->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, m_dwTerrainVertices, 0, m_dwTerrainPrimitives);

		m_pDirectx->SetTexture(0, NULL);
		m_pDirectx->SetTexture(1, NULL);
	}

	m_pEffectsManager->EndPass(1);
	m_pEffectsManager->End(1);
}