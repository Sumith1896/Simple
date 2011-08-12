//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	VoxelManager.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	high frequency timer
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include <Windows.h>
#include <stdio.h>
#include "Helpers.h"

class CACHE_ALIGN VoxelManager  
{
private:

	//individual block
	struct CACHE_ALIGN tVoxel
	{
		//position in the world
		int nPosX;
		int nPosY;
		int nPosZ;

		bool dirty;

		int type; //what type of block this is
	};

	////large chunk of voxels
	////used to cull out interaction
	//struct CACHE_ALIGH tChunk
	//{

	//};

	////super large chunk of chunks
	////used to cull out rendering
	//struct CACHE_ALIGH tSuperChunk
	//{

	//};

	static	VoxelManager *m_pInstance;			//instance to the singleton	

	VoxelManager(){};
	VoxelManager(const VoxelManager &a){};
	VoxelManager &operator=(const VoxelManager &a){};

public:

	//	~VoxelManager: Destructor
	~VoxelManager(){};

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
	static VoxelManager *GetInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitTimer
	//
	//	Last Modified: 	2006/01/15
	//
	//	Purpose:		Initializes the frequency and counter
	//
	//////////////////////////////////////////////////////////////////////////
	void Init();
};