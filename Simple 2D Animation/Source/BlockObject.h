//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	BlockObject.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	the class for 3D blocks in the world
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Helpers.h"
#include "BaseWorldObject.h"


class CACHE_ALIGN BlockObject : public BaseWorldObject
{
private:

	BlockType					m_BlockType;		//type of block
	D3DXMATRIX					m_d3dBlockMatrix;	//matrix for the block
	D3DXVECTOR3					m_d3dGoodVector;	//used when returning vectors
	VoxelPosition				m_nVoxelPosition;	//poisiton in the voxel world
	bool						m_isVisible;		//visible to view

public:

	BlockObject()
	{
		m_BlockType		 = BLOCK_NULL;
		D3DXMatrixIdentity(&m_d3dBlockMatrix);
		m_d3dGoodVector.x = 0.0f;
		m_d3dGoodVector.y = 0.0f;
		m_d3dGoodVector.z = 0.0f;
		m_nVoxelPosition.nX = 0;
		m_nVoxelPosition.nY = 0;
		m_nVoxelPosition.nZ = 0;
		m_isVisible = false;
	}
	BlockObject(const BlockObject &a)
	{

	}
	BlockObject &operator=(const BlockObject &a)
	{

	}
	~BlockObject(){}

	//////////////////////////////////////////////////////////////////////////
	//INLINES
	//////////////////////////////////////////////////////////////////////////
	inline D3DXMATRIX GetMatrix()
	{
		//return the matrix 
		return m_d3dBlockMatrix;
	}

	inline D3DXVECTOR3 GetRight()
	{
		//get the right values from the matrix
		memcpy(&m_d3dGoodVector, &m_d3dBlockMatrix._11, sizeof(D3DXVECTOR3));

		//return the matrix 
		return m_d3dGoodVector;
	}

	inline D3DXVECTOR3 GetUp()
	{
		//get the up values from the matrix
		memcpy(&m_d3dGoodVector, &m_d3dBlockMatrix._21, sizeof(D3DXVECTOR3));

		//return the matrix 
		return m_d3dGoodVector;
	}

	inline D3DXVECTOR3 GetAt()
	{
		//get the at values from the matrix
		memcpy(&m_d3dGoodVector, &m_d3dBlockMatrix._31, sizeof(D3DXVECTOR3));

		//return the matrix 
		return m_d3dGoodVector;
	}

	inline D3DXVECTOR3 GetPos()
	{
		//get the pos values from the matrix
		memcpy(&m_d3dGoodVector, &m_d3dBlockMatrix._41, sizeof(D3DXVECTOR3));

		//return the matrix 
		return m_d3dGoodVector;
	}

	inline void SetMatrix(D3DXMATRIX &d3dMatrix)
	{
		//set the new matrix 
		memcpy(m_d3dBlockMatrix, d3dMatrix, sizeof(D3DXMATRIX));
	}

	inline void SetRight(D3DXVECTOR3 &d3dRightVector)
	{
		//get the at values from the matrix
		memcpy(&m_d3dBlockMatrix._11, &d3dRightVector, sizeof(D3DXVECTOR3));
	}

	inline void SetUp(D3DXVECTOR3 &d3dUpVector)
	{
		//get the at values from the matrix
		memcpy(&m_d3dBlockMatrix._21, &d3dUpVector, sizeof(D3DXVECTOR3));
	}

	inline void SetAt(D3DXVECTOR3 &d3dAtVector)
	{
		//get the at values from the matrix
		memcpy(&m_d3dBlockMatrix._31, &d3dAtVector, sizeof(D3DXVECTOR3));
	}

	inline void SetPos(D3DXVECTOR3 &d3dPosVector)
	{
		//get the pos values from the matrix
		memcpy(&m_d3dBlockMatrix._41, &d3dPosVector, sizeof(D3DXVECTOR3));
	}

	inline void SetVoxelPos(int nVoxelPosX, int nVoxelPosY, int nVoxelPosZ)
	{
		m_nVoxelPosition.nX = nVoxelPosX;
		m_nVoxelPosition.nY = nVoxelPosY;
		m_nVoxelPosition.nZ = nVoxelPosZ;
	}

	inline void SetVoxelPos(VoxelPosition &VoxelPos)
	{
		memcpy(&m_nVoxelPosition, &VoxelPos, sizeof(VoxelPosition));
	}

	inline void SetVisible(bool isVisible)
	{
		m_isVisible = isVisible;
	}

	inline bool GetVisible()
	{
		return m_isVisible;
	}

	inline void SetType(BlockType blockType)
	{
		m_BlockType = blockType;
	}

	inline BlockType GetType()
	{
		return m_BlockType;
	}
};