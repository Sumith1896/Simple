//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	InputInterp.cpp
//
//	Purpose:	Controls all the players in the game
//
//////////////////////////////////////////////////////////////////////////
#include "InputInterp.h"

//initialize the static variable member(s)
InputInterp *InputInterp::m_pInstance = NULL;
int InputInterp::m_nCounter = 0;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
//
//	Purpose:		Delete the instance of the class, and set the pointer to NULL
//
//////////////////////////////////////////////////////////////////////////
void InputInterp::DeleteInstance()
{
	SAFE_DELETE(m_pInstance);

	COUT << "InputInterp::DeleteInstance() - SUCCESS" << endl; 
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetInstance
//
//	Purpose:		Creates the first instance of this class and returns it's address.
//
//////////////////////////////////////////////////////////////////////////
InputInterp *InputInterp::GetInstance()
{
	if(!m_pInstance)
	{
		m_pInstance = new InputInterp;
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
void InputInterp::Init(HWND hWnd, HINSTANCE hInstance)
{
	if(m_nCounter == 0)
	{
		m_pDirectInput		= DirectInput::GetInstance();
		m_pPlayerManager	= PlayerManager::GetInstance();
		m_pDirectInput->InitDirectInput(hWnd, hInstance, true);

		m_pPlayerManager->Init();

		pt2Member = &InputInterp::StateNULL;
	}

	m_nCounter++;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Update
//
//	Purpose:		called every frame to check for inputs 
//
//////////////////////////////////////////////////////////////////////////
void InputInterp::Update()
{
	char nick = 'k';
	m_pDirectInput->ReadInput();

	(this->*pt2Member)(1.0f,nick,nick);

	// get current game state m_pGameState->GetState();



}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		MainGameFirstPerson
//
//	Purpose:		input update for the main game state 
//
//////////////////////////////////////////////////////////////////////////
void InputInterp::MainGameFirstPerson()
{
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		StateNULL
//
//	Purpose:		basically the starting state or maybe an error state 
//
//////////////////////////////////////////////////////////////////////////
int InputInterp::StateNULL(float a, int b, char c)
{ 
	//nothing to do here except change the state

	//basically if we are in a NULL state we should go and init
	pt2Member = &InputInterp::StateInit;
	return 1;
};

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		StateInit
//
//	Purpose:		Init anything needed for the functions / funtion pointers 
//
//////////////////////////////////////////////////////////////////////////
int InputInterp::StateInit(float a, int b, char c)
{ 
	//Init
	pt2Member = &InputInterp::StatePlayer;
	return 1; 
}; 

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		StatePlayer
//
//	Purpose:		Input will be directed to the player since the player
//					is currently being controlled
//
//////////////////////////////////////////////////////////////////////////
int InputInterp::StatePlayer(float a, int b, char c)
{ 
	//if(m_pDirectInput->GetKeyPressedBuffered(DIK_ESCAPE))
	//{
	//	return ;
	//}

	if(m_pDirectInput->GetKeyPressedBuffered(DIK_W))
	{
		PlayerPacket nick;
		nick.nType = PLAYERS_PACKET_MOVE_FORWARD;
		nick.nPlayer = 0;
		nick.fValue = 0.1f;
		m_pPlayerManager->SendPacket(nick);
	}

	//if(m_pDirectInput->GetKeyPressed(DIK_UPARROW))
	//{
	//	m_Base.RotatePiece(0.0005f);
	//}

	//if(m_pDirectInput->GetKeyPressed(DIK_DOWNARROW))
	//{
	//	m_Base.RotatePiece(-0.0005f);
	//}

	//if(m_pDirectInput->GetKeyPressed(DIK_RIGHTARROW))
	//{
	//	m_Base.ScalePiece(0.0005f, 0.0005f);
	//}

	//if(m_pDirectInput->GetKeyPressed(DIK_LEFTARROW))
	//{
	//	m_Base.ScalePiece(-0.0005f, -0.0005f);
	//}

	//if(m_pDirectInput->GetKeyPressedBuffered(DIK_ADD))
	//{
	//	m_Base.SelectNextArray();
	//}

	//if(m_pDirectInput->GetKeyPressedBuffered(DIK_SUBTRACT))
	//{
	//	m_Base.SelectPrevArray();
	//}

	//if(m_pDirectInput->GetKeyPressedBuffered(DIK_NUMPADSTAR))
	//{
	//	m_Base.SelectNextPiece();
	//}

	//if(m_pDirectInput->GetKeyPressedBuffered(DIK_O))
	//{
	//	if(m_bWireframe = !m_bWireframe)
	//	{
	//		m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_FILLMODE,D3DFILL_WIREFRAME);
	//	}else
	//	{
	//		m_pDirect3D->GetD3DDevice()->SetRenderState(D3DRS_FILLMODE,D3DFILL_SOLID);
	//	}
	//}
	//

	//Init
	return 1; 
}; 