//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	CMeshManager.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls all the meshes being used
//
//////////////////////////////////////////////////////////////////////////
#include "MeshManager.h"

//	Initialize the static variable member.
CMeshManager *CMeshManager::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		LoadMesh
//%
//	Last Modified:	03/19/2007
//
//	Purpose:		loads a mesh into memory
//
//	Notes:			if you think about touching this you're gonna get stabbed
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::LoadMesh(const char *szFileName, ID3DXMesh **d3dMesh, bool bUnique)
{
	if(!szFileName)
		return;

	int nFound = -1;

	if(!bUnique)
	{
		for(int i = 0; i < (int)m_vFileNames.size(); i++)
		{
			//if we find the file is already loaded
			if(strcmp(m_vFileNames[i], szFileName) == 0)
			{
				//increment the reference count
				m_vXfiles[i]->nReferences++;
				nFound = i;
				*d3dMesh = m_vXfiles[i]->d3dMesh;
			}
		}
	}

	//if the Xfile hasn't been loaded; load it into memory
	if(nFound < 0)
	{
		tXFile *XFileMesh = new tXFile;
		ID3DXBuffer	*pD3DXMtrlBuffer;			//holds the materials

		//Load the Xfile
		if(FAILED(D3DXLoadMeshFromX
			(
			szFileName,				//filename
			D3DXMESH_DYNAMIC,		//flags
			m_pDirectx,				//D3D Device
			NULL,					//adjacency
			&pD3DXMtrlBuffer,		//material buffer
			NULL, 					//effect instances
			&XFileMesh->dwMeshParts,//material count
			&XFileMesh->d3dMesh		//returned mesh pointer
			)))
		{
			delete XFileMesh;

			//release the material buffer
			SAFE_RELEASE(pD3DXMtrlBuffer);

			return;
		}

		//turn the buffer into some materials
		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

		XFileMesh->d3dMaterial.Ambient.r	= 1.0f;
		XFileMesh->d3dMaterial.Ambient.g	= 1.0f;
		XFileMesh->d3dMaterial.Ambient.b	= 1.0f;
		XFileMesh->d3dMaterial.Ambient.a	= 1.0f;

		XFileMesh->d3dMaterial.Diffuse.r	= 1.0f;
		XFileMesh->d3dMaterial.Diffuse.g	= 1.0f;
		XFileMesh->d3dMaterial.Diffuse.b	= 1.0f;
		XFileMesh->d3dMaterial.Diffuse.a	= 1.0f;

		XFileMesh->d3dMaterial.Specular.r	= 0.0f;
		XFileMesh->d3dMaterial.Specular.g	= 0.0f;
		XFileMesh->d3dMaterial.Specular.b	= 0.0f;
		XFileMesh->d3dMaterial.Specular.a	= 1.0f;

		XFileMesh->d3dMaterial.Power		= 0.0f;

		XFileMesh->d3dMaterial.Emissive.r	= 0.0f;
		XFileMesh->d3dMaterial.Emissive.g	= 0.0f;
		XFileMesh->d3dMaterial.Emissive.b	= 0.0f;
		XFileMesh->d3dMaterial.Emissive.a	= 1.0f;

		XFileMesh->nTexture01 = m_pTexturemanager->LoadTexture(d3dxMaterials[0].pTextureFilename);
		XFileMesh->nTexture02 = 0;

		//release the material buffer
		SAFE_RELEASE(pD3DXMtrlBuffer);

		XFileMesh->nReferences = 1;

		//push the new mesh into the Xfile mesh vector
		m_vXfiles.push_back(XFileMesh);

		//save the position in the vector
		nFound = (int)(m_vXfiles.size() - 1);

		//Save Filename in a seperate stucture
		char *FileName = new char[128];
		strcpy(FileName, szFileName);

		//Push filename into vector
		m_vFileNames.push_back(FileName);
	}

	//save the xfile mesh pointer
	*d3dMesh	= m_vXfiles[nFound]->d3dMesh;
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
void CMeshManager::DeleteInstance()
{
	SAFE_DELETE(m_pInstance);

	COUT << "CMeshManager::DeleteInstance()" << endl;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetInstance
//
//	Last Modified: 	2006/09/17
//
//	Purpose:		Creates the first instance of this class and returns it's address.
//
//////////////////////////////////////////////////////////////////////////
CMeshManager *CMeshManager::GetInstance()
{
	if(!m_pInstance)
		m_pInstance = new CMeshManager;

	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Shutdown
//
//	Last Modified: 	2006/09/17
//
//	Purpose:		Initializes the MeshManager class
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::Shutdown()
{
	DeleteMeshes();
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitTextureManager
//
//	Last Modified:	2006/09/17
//
//	Purpose:		Initializes the MeshManager class
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::InitMeshManager(IDirect3DDevice9 *d3dDirectx)
{
	//check the pointer passed over
	assert(d3dDirectx);

	//set the d3d device pointer
	m_pDirectx			= d3dDirectx;
	m_pTexturemanager	= CTextureManager::GetInstance();
	m_pCamera			= CCamera::GetInstance();

	D3DXMatrixIdentity(&m_d3dBadMatrix);
	D3DXMatrixIdentity(&m_d3dGoodMatrix);
	m_d3dBadVector.x = 0.0f;
	m_d3dBadVector.y = 0.0f;
	m_d3dBadVector.z = 0.0f;

	m_d3dGoodVector.x = 0.0f;
	m_d3dGoodVector.y = 0.0f;
	m_d3dGoodVector.z = 0.0f;

	//set the texture states for some old skool FF action
	m_pDirectx->SetTextureStageState(0, D3DTSS_COLOROP,		D3DTOP_MODULATE);
	m_pDirectx->SetTextureStageState(0, D3DTSS_COLORARG1,	D3DTA_TEXTURE);
	m_pDirectx->SetTextureStageState(0, D3DTSS_COLORARG2,	D3DTA_CURRENT);
	m_pDirectx->SetTextureStageState(0, D3DTSS_ALPHAOP,		D3DTOP_SELECTARG1);
	m_pDirectx->SetTextureStageState(0, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE);
	m_pDirectx->SetTextureStageState(0, D3DTSS_ALPHAARG2,	D3DTA_CURRENT);

	m_pDirectx->SetTextureStageState(1, D3DTSS_COLOROP,		D3DTOP_BLENDTEXTUREALPHA);
	m_pDirectx->SetTextureStageState(1, D3DTSS_COLORARG1,	D3DTA_TEXTURE);
	m_pDirectx->SetTextureStageState(1, D3DTSS_COLORARG2,	D3DTA_CURRENT);
	m_pDirectx->SetTextureStageState(1, D3DTSS_ALPHAOP,		D3DTOP_BLENDTEXTUREALPHA);
	m_pDirectx->SetTextureStageState(1, D3DTSS_ALPHAARG1,	D3DTA_TEXTURE);
	m_pDirectx->SetTextureStageState(1, D3DTSS_ALPHAARG2,	D3DTA_CURRENT);

	//clear all the vectors
	m_vMeshes.clear();
	m_vFileNames.clear();
	m_vXfiles.clear();
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		LoadMesh
//
//	Last Modified:	2006/09/17
//
//	Purpose:		loads a mesh into memory
//
//////////////////////////////////////////////////////////////////////////
int CMeshManager::LoadMesh(const char *szFileName, bool bUnique)
{
	if(!szFileName)
		return -1;

	int nFound = -1;

	//if it's unique there's no reason to check for it
	if(!bUnique)
	{
		for(int i = 0; i < (int)m_vFileNames.size(); i++)
		{
			//if we find the file is already loaded
			if(strcmp(m_vFileNames[i], szFileName) == 0)
			{
				//increment the reference count
				m_vXfiles[i]->nReferences++;
				nFound = i;
			}
		}
	}

	tStaticMesh	*Mesh = new tStaticMesh;	//new mesh container

	//if the Xfile hasn't been loaded; load it into memory
	if(nFound < 0)
	{
		tXFile *XFileMesh = new tXFile;
		ID3DXBuffer	*pD3DXMtrlBuffer;			//holds the materials

		//Load the Xfile
		if(FAILED(D3DXLoadMeshFromX
			(
			szFileName,				//filename
			D3DXMESH_DYNAMIC,		//flags
			m_pDirectx,				//D3D Device
			NULL,					//adjacency
			&pD3DXMtrlBuffer,		//material buffer
			NULL, 					//effect instances
			&XFileMesh->dwMeshParts,//material count
			&XFileMesh->d3dMesh		//returned mesh pointer
			)))
		{
			delete XFileMesh;
			delete Mesh;

			return 0;
		}

		//turn the buffer into some materials
		D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)pD3DXMtrlBuffer->GetBufferPointer();

		XFileMesh->d3dMaterial.Ambient.r	= 1.0f;
		XFileMesh->d3dMaterial.Ambient.g	= 1.0f;
		XFileMesh->d3dMaterial.Ambient.b	= 1.0f;
		XFileMesh->d3dMaterial.Ambient.a	= 1.0f;

		XFileMesh->d3dMaterial.Diffuse.r	= 1.0f;
		XFileMesh->d3dMaterial.Diffuse.g	= 1.0f;
		XFileMesh->d3dMaterial.Diffuse.b	= 1.0f;
		XFileMesh->d3dMaterial.Diffuse.a	= 1.0f;

		XFileMesh->d3dMaterial.Specular.r	= 0.0f;
		XFileMesh->d3dMaterial.Specular.g	= 0.0f;
		XFileMesh->d3dMaterial.Specular.b	= 0.0f;
		XFileMesh->d3dMaterial.Specular.a	= 1.0f;

		XFileMesh->d3dMaterial.Power		= 0.0f;

		XFileMesh->d3dMaterial.Emissive.r	= 0.0f;
		XFileMesh->d3dMaterial.Emissive.g	= 0.0f;
		XFileMesh->d3dMaterial.Emissive.b	= 0.0f;
		XFileMesh->d3dMaterial.Emissive.a	= 1.0f;

		XFileMesh->nTexture01 = m_pTexturemanager->LoadTexture(d3dxMaterials[0].pTextureFilename);
		XFileMesh->nTexture02 = 0;

		XFileMesh->nReferences = 1;

		//release the material buffer
		SAFE_RELEASE(pD3DXMtrlBuffer);

		//push the new mesh into the Xfile mesh vector
		m_vXfiles.push_back(XFileMesh);

		//save the position in the vector
		nFound = (int)(m_vXfiles.size() - 1);

		//Save Filename in a seperate stucture
		char *FileName = new char[128];
		strcpy(FileName, szFileName);

		//Push filename into vector
		m_vFileNames.push_back(FileName);
	}

	//set the matrix to the identity
	D3DXMatrixIdentity(&Mesh->d3dMat);

	//save the Xfile mesh pointer
	Mesh->d3dMesh		= m_vXfiles[nFound]->d3dMesh;
	Mesh->dwMeshParts	= m_vXfiles[nFound]->dwMeshParts;
	Mesh->d3dMaterial	= m_vXfiles[nFound]->d3dMaterial;
	Mesh->nTexture01	= m_vXfiles[nFound]->nTexture01;
	Mesh->nTexture02	= m_vXfiles[nFound]->nTexture02;
	Mesh->bUnique		= bUnique;

	//Save Filename in the mesh structure
	Mesh->szFileName = new char[128];
	strcpy(Mesh->szFileName, szFileName);

	//push the static mesh into the vector
	m_vMeshes.push_back(Mesh);

	//return the index to the static mesh
	return (int)(m_vMeshes.size() - 1);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		ResetMatrices
//
//	Last Modified:	03/24/2007
//
//	Purpose:		<3 hugs & kisses <3
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::ResetMatrices()
{
	for(int i = 0; i < (int)m_vMeshes.size(); i++)
	{
		if(m_vMeshes[i])
			D3DXMatrixIdentity(&m_vMeshes[i]->d3dMat);
	}
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DrawMesh
//
//	Last Modified:	2006/09/17
//
//	Purpose:		draws a mesh based on the index passed over
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::DrawMesh(const unsigned int &nMesh, bool bBillboard)
{
	//check the bounds of the array
	if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
		return;

	//make sure there's a mesh to mess with
	if(!m_vMeshes[nMesh])
		return;

	//check to see if we need to billboard this mesh
	if(bBillboard)
	{
		D3DXMATRIX	d3dNewMatrix;
		D3DXMatrixInverse(&d3dNewMatrix, NULL, m_pCamera->GetViewMatrix());

		d3dNewMatrix._41 = m_vMeshes[nMesh]->d3dMat._41;
		d3dNewMatrix._42 = m_vMeshes[nMesh]->d3dMat._42;
		d3dNewMatrix._43 = m_vMeshes[nMesh]->d3dMat._43;

		D3DXMatrixMultiply(&m_vMeshes[nMesh]->d3dMat, &m_vMeshes[nMesh]->d3dMat, &d3dNewMatrix);
	}

	//set the matrix for the mesh
	m_pDirectx->SetTransform(D3DTS_WORLD , &m_vMeshes[nMesh]->d3dMat);

	D3DXMatrixIdentity(&m_vMeshes[nMesh]->d3dMat);

	//set the material and texture for the static mesh
	m_pDirectx->SetMaterial(&m_vMeshes[nMesh]->d3dMaterial);

	//check if there is a texture
	m_pDirectx->SetTexture(0, m_pTexturemanager->GetTexture(m_vMeshes[nMesh]->nTexture01));

	//check if there is a texture
	if(m_vMeshes[nMesh]->nTexture02 > 0)
		m_pDirectx->SetTexture(1, m_pTexturemanager->GetTexture(m_vMeshes[nMesh]->nTexture02));
	else
		m_pDirectx->SetTexture(1, NULL);

	//draw all the pieces of the static mesh
	for(unsigned int i = 0; i < m_vMeshes[nMesh]->dwMeshParts; i++)
		m_vMeshes[nMesh]->d3dMesh->DrawSubset(i);

	m_pDirectx->SetTransform(D3DTS_WORLD , m_pCamera->GetViewMatrix());
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		TranslateMesh
//
//	Last Modified:	2006/09/17
//
//	Purpose:		translate a mesh
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::TranslateMesh(const unsigned int &nMesh, const float &fTranslateX, const float &fTranslateY, const float &fTranslateZ)
{
	//check the bounds of the array
	if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
		return;

	D3DXMatrixTranslation(&m_d3dGoodMatrix, fTranslateX, fTranslateY, fTranslateZ);
	m_vMeshes[nMesh]->d3dMat *= m_d3dGoodMatrix;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		TranslateMesh
//
//	Last Modified:	2006/09/17
//
//	Purpose:		translate a mesh
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::TranslateMesh(const unsigned int &nMesh, const D3DXVECTOR3 &fTranslate)
{
	//check the bounds of the array
	if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
		return;

	D3DXMatrixTranslation(&m_d3dGoodMatrix, fTranslate.x, fTranslate.y, fTranslate.z);
	m_vMeshes[nMesh]->d3dMat *= m_d3dGoodMatrix;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		ScaleMesh
//
//	Last Modified:	2006/09/17
//
//	Purpose:		scales a mesh
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::ScaleMesh(const unsigned int &nMesh, const float &fScaleX, const float &fScaleY, const float &fScaleZ)
{
	//check the bounds of the array
	if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
		return;

	D3DXMatrixScaling(&m_d3dGoodMatrix, fScaleX, fScaleY, fScaleZ);
	m_vMeshes[nMesh]->d3dMat *= m_d3dGoodMatrix;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		RotateMeshX
//
//	Last Modified:	2006/09/17
//
//	Purpose:		roates a mesh on the X
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::RotateMeshX(const unsigned int &nMesh, const float &fRotate)
{
	//check the bounds of the array
	if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
		return;

	D3DXMatrixRotationX(&m_d3dGoodMatrix, fRotate);
	m_vMeshes[nMesh]->d3dMat *= m_d3dGoodMatrix;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		RotateMeshY
//
//	Last Modified:	2006/09/17
//
//	Purpose:		roates a mesh on the Y
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::RotateMeshY(const unsigned int &nMesh, const float &fRotate)
{
	//check the bounds of the array
	if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
		return;

	D3DXMatrixRotationY(&m_d3dGoodMatrix, fRotate);
	m_vMeshes[nMesh]->d3dMat *= m_d3dGoodMatrix;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		RotateMeshZ
//
//	Last Modified:	2006/09/17
//
//	Purpose:		roates a mesh on the Z
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::RotateMeshZ(const unsigned int &nMesh, const float &fRotate)
{
	//check the bounds of the array
	if(nMesh > (unsigned int)(m_vMeshes.size() - 1))
		return;

	D3DXMatrixRotationZ(&m_d3dGoodMatrix, fRotate);
	m_vMeshes[nMesh]->d3dMat *= m_d3dGoodMatrix;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		UnloadMeshes
//
//	Last Modified:	03/09/2007
//
//	Purpose:		Unloads all the xfiles, but keeps the mesh structures 
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::UnloadMeshes()
{
	//loop through all the xfiles and release them from memory
	for(int i = 0; i < (int)m_vXfiles.size(); i++)
		SAFE_RELEASE(m_vXfiles[i]->d3dMesh);

	//loop through all the xfiles and delete them from memory
	for(int i = 0; i < (int)m_vXfiles.size(); i++)
		SAFE_DELETE(m_vXfiles[i]);

	//loop through all the filenames and delete them
	for(int i = 0; i < (int)m_vFileNames.size(); i++)
		SAFE_DELETE_ARRAY(m_vFileNames[i]);

	//clear the arrays
	m_vFileNames.clear();
	m_vXfiles.clear();
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		ReloadMeshes
//
//	Last Modified:	03/09/2007
//
//	Purpose:		Reloads all the xfiles, based on the mesh vector 
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::ReloadMeshes()
{
	//time to load these textures back it memory
	for(int i = 0; i < (int)m_vMeshes.size(); i++)
		LoadMesh(m_vMeshes[i]->szFileName, &m_vMeshes[i]->d3dMesh,  m_vMeshes[i]->bUnique);

	int temp = 0;

}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteMeshes
//
//	Last Modified:	03/09/2007
//
//	Purpose:		deletes all the meshes, this is permanent...
//
//////////////////////////////////////////////////////////////////////////
void CMeshManager::DeleteMeshes()
{
	//loop through all the xfiles and release them from memory
	for(int i = 0; i < (int)m_vXfiles.size(); i++)
		SAFE_RELEASE(m_vXfiles[i]->d3dMesh);

	//loop through all the xfiles and delete them from memory
	for(int i = 0; i < (int)m_vXfiles.size(); i++)
		SAFE_DELETE(m_vXfiles[i]);

	//loop through all the filenames and delete them
	for(int i = 0; i < (int)m_vFileNames.size(); i++)
		SAFE_DELETE_ARRAY(m_vFileNames[i]);

	//loop through all the filenames and delete them
	for(int i = 0; i < (int)m_vMeshes.size(); i++)
		SAFE_DELETE_ARRAY(m_vMeshes[i]->szFileName);

	//loop through all the filenames and delete them
	for(int i = 0; i < (int)m_vMeshes.size(); i++)
		SAFE_DELETE(m_vMeshes[i]);

	//clear the arrays
	m_vFileNames.clear();
	m_vXfiles.clear();
	m_vMeshes.clear();
}