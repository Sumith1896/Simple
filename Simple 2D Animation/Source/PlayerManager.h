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

struct CACHE_ALIGN Player
{
	D3DXVECTOR3				d3dPosition;		//position of the player in the world
	D3DXVECTOR3				d3dLookAt;			//direction the player is looking
	float					fSpeedMax;			//max speed the player can move
	float					fAcceleration;		//rate at which the player increases speed
};

class CACHE_ALIGN PlayerManager  
{
private:

	Player		m_player;	//the player!

	static	PlayerManager *m_pInstance;			//instance to the singleton	

	PlayerManager(){};
	PlayerManager(const PlayerManager &a){};
	PlayerManager &operator=(const PlayerManager &a){};

public:

	//	~PlayerManager: Destructor
	~PlayerManager(){};

	//////////////////////////////////////////////////////////////////////////
	//INLINES
	//////////////////////////////////////////////////////////////////////////
	inline D3DXVECTOR3 GetPosition(){return m_player.d3dPosition;}
	inline D3DXVECTOR3 GetLookAt(){return m_player.d3dLookAt;}

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

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Init
	//
	//	Purpose:		Initializes the player manager
	//
	//////////////////////////////////////////////////////////////////////////
	bool Init();

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		Update
	//
	//	Purpose:		General update for the player.
	//					This will branch out into all the different ways a 
	//					player can be updated.
	//
	//////////////////////////////////////////////////////////////////////////
	void Update();
};