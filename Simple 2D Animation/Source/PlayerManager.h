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
#include <list>
using std::list;

#define PLAYERS_MAX 8
#define PLAYERS_PACKET_MOVE_FORWARD		1
#define PLAYERS_PACKET_MOVE_BACKWARD	2
#define PLAYERS_PACKET_MOVE_LEFT		3
#define PLAYERS_PACKET_MOVE_RIGHT		4

struct CACHE_ALIGN Player
{
	D3DXVECTOR3				d3dPosition;		//position of the player in the world
	D3DXVECTOR3				d3dLookAt;			//direction the player is looking
	float					fSpeedMax;			//max speed the player can move
	float					fAcceleration;		//rate at which the player increases speed
};

struct CACHE_ALIGN PlayerPacket
{
	unsigned int		nType;		//the type of packet we're receiving
	union
	{
		int					nValue;		//the value of the packet we're receiving
		unsigned int		uValue;		//the value of the packet we're receiving
		float				fValue;		//the value of the packet we're receiving
	};
	unsigned int		nStamp;		//number of this packet
	unsigned int		nPlayer;	//the player this packet is for
};

class CACHE_ALIGN PlayerManager  
{
private:

	Player		m_vPlayers[PLAYERS_MAX];		//the players!
	unsigned int m_nPlayers;					//number of players in the world
	list<PlayerPacket> m_vPlayerPackets;		//list of all the packets not processed
	unsigned int	m_nCurrentStamp;			//current number stamp for the packets
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
	inline D3DXVECTOR3 GetPosition(const unsigned int nPlayer){return m_vPlayers[nPlayer].d3dPosition;}
	inline D3DXVECTOR3 GetLookAt(const unsigned int nPlayer){return m_vPlayers[nPlayer].d3dLookAt;}

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
	//	Function: 		Create Player
	//
	//	Purpose:		Creates a player for the world
	//
	//	Return;			-1 means it failed to create another player
	//
	//////////////////////////////////////////////////////////////////////////
	int CreatePlayer(Player &newPlayer);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		SendPacket
	//
	//	Purpose:		Calling this will insert a player packet into the list
	//
	//////////////////////////////////////////////////////////////////////////
	void SendPacket(const PlayerPacket &Packet);

	//////////////////////////////////////////////////////////////////////////
	// 
	//	Function: 		UpdatePlayers
	//
	//	Purpose:		Goes through the list and updates the players
	//
	//////////////////////////////////////////////////////////////////////////
	void UpdatePlayers();
};