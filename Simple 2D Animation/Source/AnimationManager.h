#pragma once

#include <Windows.h>
#include <stdio.h>
#include "Helpers.h"	//some helpful defines
#include <fstream>
#include <vector>
using std::fstream;
using std::vector;
using std::ios_base;

class CAnimationManager
{
private:

	struct tKeyFrame
	{
		vector<double>	vRotations;		//vector of all the rotation values
		double			fTime;			//amount of time between this frame and the next
		int				nSize;			//used in error checking
	};

	struct tAnimation
	{
		vector<tKeyFrame *>		m_vKeyFrames;	//all the key frames that make up the animation
		double					nSize;			//...something
		int						nType;			//type of animation (2D, 3D, other....)
	};
	
	vector<tAnimation *>	m_vAnimations;

	static CAnimationManager *m_pInstance;			//	The instance of this class.

	CAnimationManager();
	CAnimationManager(const CAnimationManager &a){};
	CAnimationManager &operator=(const CAnimationManager &a){};

public:

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetInstance
	//
	//	Last Modified: 	07/08/2006
	//
	//	Purpose:		Creates the first instance of this class and returns it's address.
	//
	//////////////////////////////////////////////////////////////////////////
	static CAnimationManager *GetInstance();

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
	//	Function: 		Shutdown
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		All clean up code is here
	//
	//////////////////////////////////////////////////////////////////////////
	void Shutdown();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		InitSpriteManager
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Initializes the AnimationManager class
	//
	//////////////////////////////////////////////////////////////////////////
	void InitAnimationManager();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Load2DAnimaton
	//
	//	Last Modified: 	2006/08/04
	//
	//	Purpose:		Loads data for 2D animation from a file
	//
	//////////////////////////////////////////////////////////////////////////
	int Load2DAnimaton(const char *szFileName);
};