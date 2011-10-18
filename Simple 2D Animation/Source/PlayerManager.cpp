//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	PlayerManager.cpp
//
//	Purpose:	Controls all the players in the game
//
//////////////////////////////////////////////////////////////////////////
#include "PlayerManager.h"

//initialize the static variable member(s)
PlayerManager *PlayerManager::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
//
//	Purpose:		Delete the instance of the class, and set the pointer to NULL
//
//////////////////////////////////////////////////////////////////////////
void PlayerManager::DeleteInstance()
{
	SAFE_DELETE(m_pInstance);

	COUT << "PlayerManager::DeleteInstance() - SUCCESS" << endl; 
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetInstance
//
//	Purpose:		Creates the first instance of this class and returns it's address.
//
//////////////////////////////////////////////////////////////////////////
PlayerManager *PlayerManager::GetInstance()
{
	if(!m_pInstance)
	{
		m_pInstance = new PlayerManager;
	}

	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Init
//
//	Purpose:		Initializes the player manager
//
//////////////////////////////////////////////////////////////////////////
bool PlayerManager::Init()
{
	//zero out the player struct
	memset(&m_vPlayers, 0, sizeof(Player) * PLAYERS_MAX);


	//zero players to start
	m_nPlayers = 0;

	return true;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Create Player
//
//	Purpose:		Creates a player for the world
//
//	Return;			-1 means it failed to create another player
//
//////////////////////////////////////////////////////////////////////////
int PlayerManager::CreatePlayer(Player &newPlayer)
{
	//no room for more player
	if(m_nPlayers > PLAYERS_MAX)
	{
		return -1;
	}

	//copy the values over
	memcpy(&m_vPlayers[m_nPlayers], &newPlayer, sizeof(Player));

	//return the current player index
	return m_nPlayers++;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		SendPacket
//
//	Purpose:		Calling this will insert a player packet into the list
//
//////////////////////////////////////////////////////////////////////////
void PlayerManager::SendPacket(const PlayerPacket &Packet)
{
	//check to make sure this isn't bad
	if(&Packet == NULL)
	{
		return;
	}

	//push the packet into the list
	m_vPlayerPackets.push_front(Packet);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		UpdatePlayers
//
//	Purpose:		Goes through the list and updates the players
//
//////////////////////////////////////////////////////////////////////////
void PlayerManager::UpdatePlayers()
{
	PlayerPacket tempPlayerPacket;

	//loop through the list grabbing the values and popping them off
	while(!m_vPlayerPackets.empty())
	{
		tempPlayerPacket = m_vPlayerPackets.back();
		m_vPlayerPackets.pop_back();

		//all the different player packets
		switch(tempPlayerPacket.nType)
		{
			//move player forward
		case 1: 
			{
				m_vPlayers[tempPlayerPacket.nPlayer].d3dPosition.z += tempPlayerPacket.fValue;
				break;
			}
			//move player backwards
		case 2: 
			{
				m_vPlayers[tempPlayerPacket.nPlayer].d3dPosition.z -= tempPlayerPacket.fValue;
				break;
			}
			//move player left
		case 3: 
			{
				m_vPlayers[tempPlayerPacket.nPlayer].d3dPosition.x -= tempPlayerPacket.fValue;
				break;
			}
			//move player right
		case 4: 
			{
				m_vPlayers[tempPlayerPacket.nPlayer].d3dPosition.x += tempPlayerPacket.fValue;
				break;
			}
		default :
			{
				break;
			}
		}
		//////////////////////////////////////////////////////////////////
		//update position

		//////////////////////////////////////////////////////////////////
		//update lookat

	}
}