//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	MeshManager.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls all the static meshes being used
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Helpers.h"
#include "TextureManager.h"
#include "Camera.h"
#include <vector>
using std::vector;

class CACHE_ALIGN CMeshManager
{
private:

	struct CACHE_ALIGN tXFile
	{
		ID3DXMesh			*d3dMesh;		//the mesh
		D3DMATERIAL9		d3dMaterial;	//the material the mesh needs
		DWORD				dwMeshParts;	//number of pieces
		int					nTexture01;		//the index of texture #1
		int					nTexture02;		//the index of texture #2
		int					nReferences;	//number of times this xfile is being used
	};

	struct CACHE_ALIGN tStaticMesh
	{
		ID3DXMesh			*d3dMesh;		//the mesh
		DWORD				dwMeshParts;	//number of pieces
		D3DMATERIAL9		d3dMaterial;	//the material the mesh needs
		D3DXMATRIX			d3dMat;			//matrix for the mesh
		char				*szFileName;	//filename of the xfile
		bool				bUnique;		//bool if the mesh is unique
		int					nTexture01;		//the index of texture #1
		int					nTexture02;		//the index of texture #2

	};

	D3DXMATRIX					m_d3dBadMatrix;		//bad matrix
	D3DXMATRIX					m_d3dGoodMatrix;	//good matrix
	D3DXVECTOR3					m_d3dBadVector;		//bad vector
	D3DXVECTOR3					m_d3dGoodVector;	//good vector
	CCamera						*m_pCamera;			//pointer to the camera
	CTextureManager				*m_pTexturemanager;	//texture manager pointer
	IDirect3DDevice9			*m_pDirectx;		//DirectX device pointer
	vector<char *>				m_vFileNames;		//vector of all the the Xfiles used
	vector<tXFile*>				m_vXfiles;			//all the loaded Xfile meshes (an xfile can only be loaded once)
	vector<tStaticMesh*>		m_vMeshes;			//All the loaded meshes	
	static CMeshManager			*m_pInstance;		//The instance of this class.

	//Constructor, copy constructor and assignment operator... all in private... ZOMG!!!  
	CMeshManager(){};
	~CMeshManager(){};
	CMeshManager(const CMeshManager &a){};
	CMeshManager &operator=(const CMeshManager &a){};

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		LoadMesh
	//
	//	Last Modified:	03/19/2007
	//
	//	Purpose:		loads a mesh into memory
	//
	//	Notes:			if you think about touching this you're gonna get stabbed
	//
	//////////////////////////////////////////////////////////////////////////
	void LoadMesh(const char *szFileName, ID3DXMesh **d3dMesh, bool bUnique = false);

public:

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Inline Functions
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		Inline functions to get/set Mesh information. 
	//
	//////////////////////////////////////////////////////////////////////////
	inline void SetMaterial(const unsigned int &nMesh, const D3DXCOLOR &d3dDiffuse, const D3DXCOLOR &d3dAmbient)
	{
		//check the bounds of the array
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return;

		//set the new diffuse color
		memcpy(&m_vMeshes[nMesh]->d3dMaterial.Diffuse, &d3dDiffuse, sizeof(D3DXCOLOR));
		memcpy(&m_vMeshes[nMesh]->d3dMaterial.Ambient, &d3dAmbient, sizeof(D3DXCOLOR));
	}

	inline void SetMaterial(const unsigned int &nMesh, const D3DMATERIAL9 &d3dMaterial)
	{
		//check the bounds of the array
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return;

		//copy over new material
		memcpy(&m_vMeshes[nMesh]->d3dMaterial, &d3dMaterial, sizeof(D3DMATERIAL9));
	}

	inline D3DXMATRIX GetMatrix(const unsigned int &nMesh)
	{
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return m_d3dBadMatrix;

		//return the matrix 
		return m_vMeshes[nMesh]->d3dMat;
	}

	inline D3DXVECTOR3 GetRight(const unsigned int &nMesh)
	{
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1) || !m_vMeshes[nMesh])
			return m_d3dBadVector;

		//get the right values from the matrix
		memcpy(&m_d3dGoodVector, &m_vMeshes[nMesh]->d3dMat._11, sizeof(D3DXVECTOR3));

		//return the matrix 
		return m_d3dGoodVector;
	}

	inline D3DXVECTOR3 GetUp(const unsigned int &nMesh)
	{
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return m_d3dBadVector;

		//get the up values from the matrix
		memcpy(&m_d3dGoodVector, &m_vMeshes[nMesh]->d3dMat._21, sizeof(D3DXVECTOR3));

		//return the matrix 
		return m_d3dGoodVector;
	}

	inline D3DXVECTOR3 GetAt(const unsigned int &nMesh)
	{
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return m_d3dBadVector;

		//get the at values from the matrix
		memcpy(&m_d3dGoodVector, &m_vMeshes[nMesh]->d3dMat._31, sizeof(D3DXVECTOR3));

		//return the matrix 
		return m_d3dGoodVector;
	}

	inline D3DXVECTOR3 GetPos(const unsigned int &nMesh)
	{
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return m_d3dBadVector;

		//get the pos values from the matrix
		memcpy(&m_d3dGoodVector, &m_vMeshes[nMesh]->d3dMat._41, sizeof(D3DXVECTOR3));

		//return the matrix 
		return m_d3dGoodVector;
	}

	inline ID3DXMesh *GetMesh(const unsigned int &nMesh)
	{
		//check the bounds of the array
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return NULL;

		return m_vMeshes[nMesh]->d3dMesh;
	}

	inline void SetMatrix(const unsigned int &nMesh, D3DXMATRIX &d3dMatrix)
	{
		//check the bounds of the array
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return;

		//set the new matrix 
		memcpy(m_vMeshes[nMesh]->d3dMat, d3dMatrix, sizeof(D3DXMATRIX));
	}

	inline void SetTexture01(const unsigned int &nMesh, const char *szFileName)
	{
		//check the bounds of the array
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return;

		//load a different texture and save it
		m_vMeshes[nMesh]->nTexture01 = m_pTexturemanager->LoadTexture(szFileName);
	}

	inline void SetTexture01(const unsigned int &nMesh, const int &nTexture)
	{
		//check the bounds of the array
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return;

		//load a different texture and save it
		m_vMeshes[nMesh]->nTexture01 = nTexture;
	}

	inline void SetTexture02(const unsigned int &nMesh, const char *szFileName)
	{
		//check the bounds of the array
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return;

		//load a different texture and save it
		m_vMeshes[nMesh]->nTexture02 = m_pTexturemanager->LoadTexture(szFileName);
	}

	inline void SetTexture02(const unsigned int &nMesh, const int &nTexture)
	{
		//check the bounds of the array
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return;
	
		//load a different texture and save it
		m_vMeshes[nMesh]->nTexture01 = nTexture;
	}

	inline void SetRight(const unsigned int &nMesh, D3DXVECTOR3 &d3dRightVector)
	{
		//check the bounds of the array
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return;

		//get the at values from the matrix
		memcpy(&m_vMeshes[nMesh]->d3dMat._11, &d3dRightVector, sizeof(D3DXVECTOR3));
	}

	inline void SetUp(const unsigned int &nMesh, D3DXVECTOR3 &d3dUpVector)
	{
		//check the bounds of the array
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return;

		//get the at values from the matrix
		memcpy(&m_vMeshes[nMesh]->d3dMat._21, &d3dUpVector, sizeof(D3DXVECTOR3));
	}

	inline void SetAt(const unsigned int &nMesh, D3DXVECTOR3 &d3dAtVector)
	{
		//check the bounds of the array
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return;

		//get the at values from the matrix
		memcpy(&m_vMeshes[nMesh]->d3dMat._31, &d3dAtVector, sizeof(D3DXVECTOR3));
	}

	inline void SetPos(const unsigned int &nMesh, D3DXVECTOR3 &d3dPosVector)
	{
		//check the bounds of the array
		if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
			return;

		//get the pos values from the matrix
		memcpy(&m_vMeshes[nMesh]->d3dMat._41, &d3dPosVector, sizeof(D3DXVECTOR3));
	}

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DeleteInstance
	//
	//	Last Modified: 	2006/09/17
	//
	//	Purpose:		Delete the instance of the class, and set the pointer to NULL
	//
	//////////////////////////////////////////////////////////////////////////
	static void DeleteInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetInstance
	//
	//	Last Modified: 	2006/09/17
	//
	//	Purpose:		Creates the first instance of this class and returns it's address.
	//
	//////////////////////////////////////////////////////////////////////////
	static CMeshManager *GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Shutdown
	//
	//	Last Modified: 	2006/09/17
	//
	//	Purpose:		Shuts down MeshManager class
	//
	//////////////////////////////////////////////////////////////////////////
	void Shutdown();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitTextureManager
	//
	//	Last Modified:	2006/09/17
	//
	//	Purpose:		Initializes the MeshManager class
	//
	//////////////////////////////////////////////////////////////////////////
	void InitMeshManager(IDirect3DDevice9 *d3dDirectx);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		LoadMesh
	//
	//	Last Modified:	2006/09/17
	//
	//	Purpose:		loads a mesh into memory
	//
	//////////////////////////////////////////////////////////////////////////
	int LoadMesh(const char *szFileName, bool bUnique = false);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DrawMesh
	//
	//	Last Modified:	2006/09/17
	//
	//	Purpose:		draws a mesh based on the index passed over
	//
	//////////////////////////////////////////////////////////////////////////
	void DrawMesh(const unsigned int &nMesh, bool bBillboard);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		ResetMatrices
	//
	//	Last Modified:	03/24/2007
	//
	//	Purpose:		<3 hugs & kisses <3
	//
	//////////////////////////////////////////////////////////////////////////
	void ResetMatrices();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		TranslateMesh
	//
	//	Last Modified:	2006/09/17
	//
	//	Purpose:		translate a mesh
	//
	//////////////////////////////////////////////////////////////////////////
	void TranslateMesh(const unsigned int &nMesh, const float &fTranslateX, const float &fTranslateY, const float &fTranslateZ);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		TranslateMesh
	//
	//	Last Modified:	2006/09/17
	//
	//	Purpose:		translate a mesh
	//
	//////////////////////////////////////////////////////////////////////////
	void TranslateMesh(const unsigned int &nMesh, const D3DXVECTOR3 &fTranslate);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		ScaleMesh
	//
	//	Last Modified:	2006/09/17
	//
	//	Purpose:		scales a mesh
	//
	//////////////////////////////////////////////////////////////////////////
	void ScaleMesh(const unsigned int &nMesh, const float &fScaleX, const float &fScaleY, const float &fScaleZ);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		RotateMeshX
	//
	//	Last Modified:	2006/09/17
	//
	//	Purpose:		roates a mesh on the X
	//
	//////////////////////////////////////////////////////////////////////////
	void RotateMeshX(const unsigned int &nMesh, const float &fRotate);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		RotateMeshY
	//
	//	Last Modified:	2006/09/17
	//
	//	Purpose:		roates a mesh on the Y
	//
	//////////////////////////////////////////////////////////////////////////
	void RotateMeshY(const unsigned int &nMesh, const float &fRotate);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		RotateMeshZ
	//
	//	Last Modified:	2006/09/17
	//
	//	Purpose:		roates a mesh on the Z
	//
	//////////////////////////////////////////////////////////////////////////
	void RotateMeshZ(const unsigned int &nMesh, const float &fRotate);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		UnloadMeshes
	//
	//	Last Modified:	03/09/2007
	//
	//	Purpose:		Unloads all the X-Files, but keeps the mesh structures 
	//
	//////////////////////////////////////////////////////////////////////////
	void UnloadMeshes();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		ReloadMeshes
	//
	//	Last Modified:	03/09/2007
	//
	//	Purpose:		Reloads all the xfiles, based on the mesh vector 
	//
	//////////////////////////////////////////////////////////////////////////
	void ReloadMeshes();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DeleteMeshes
	//
	//	Last Modified:	03/09/2007
	//
	//	Purpose:		deletes all the meshes, this is permanent...
	//
	//////////////////////////////////////////////////////////////////////////
	void DeleteMeshes();
};
