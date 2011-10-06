//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	PlayerManager.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls all the players in the game
//
//////////////////////////////////////////////////////////////////////////
#pragma once
#include "Helpers.h"

class CACHE_ALIGN PlayerManager  
{
private:

	static	PlayerManager *m_pInstance;			//instance to the singleton	

	PlayerManager(){};
	PlayerManager(const PlayerManager &a){};
	PlayerManager &operator=(const PlayerManager &a){};

public:

	//	~PlayerManager: Destructor
	~PlayerManager(){};

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		DeleteInstance
	//
	//	Purpose:		Delete the instance of the class, and set the pointer to NULL
	//
	//////////////////////////////////////////////////////////////////////////
	static void DeleteInstance();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		GetInstance
	//
	//	Purpose:		Creates the first instance of this class and returns it's address.
	//
	//////////////////////////////////////////////////////////////////////////
	static PlayerManager *GetInstance();

	void Init();
};