#include "BaseFrame.h"

CBaseFrame::CBaseFrame()
{
	D3DXMatrixIdentity(&m_d3dMat);
	m_pSpriteManager	= CSpriteManager::GetInstance();
	m_pTimer			= Timer::GetInstance();

	m_d3dHiBound.x		= 0.0f;	
	m_d3dHiBound.y		= 0.0f;
	m_d3dHiBound.z		= 0.0f;
	m_d3dLoBound.x		= 0.0f;		
	m_d3dLoBound.y		= 0.0f;	
	m_d3dLoBound.z		= 0.0f;	
	m_nSpriteID			= 0;
	m_fRotate			= 0.0f;
	m_fScaleX			= 1.0f;
	m_fScaleY			= 1.0f;

	m_nArrayPos			= 0;
	m_nPiecePos			= 0;
	m_fInterTime		= 5.0f;

	m_bUpdateComplete	= false;

	m_hDrawThreadHandle		= NULL;
	m_hUpdateThreadHandle	= NULL;

	fstream MatrixFile;

	//Load height information from file
	MatrixFile.open("matrix.txt", ios_base::trunc);

	MatrixFile.close();
		
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		InitFrame
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		starts the frame by creating a torso/base
//
//	Note:			szFileName is the texture to use for the torso piece
//
//////////////////////////////////////////////////////////////////////////
void CBaseFrame::InitFrame(const char *szFileName)
{
	if(!szFileName)
		return;

	m_vDefault2.push_back(0.29f);
	m_vDefault2.push_back(-0.912992f);
	m_vDefault2.push_back(0.985991f);
	m_vDefault2.push_back(0.314999f);
	m_vDefault2.push_back(-0.468998f);
	m_vDefault2.push_back(-0.536997f);
	m_vDefault2.push_back(-0.378999f);
	m_vDefault2.push_back(-0.282f);
	m_vDefault2.push_back(-0.634995f);
	m_vDefault2.push_back(-0.507997f);
	m_vDefault2.push_back(0.331999f);
	m_vDefault2.push_back(-0.19f);
	m_vDefault2.push_back(-0.121f);

	m_vDefault3.push_back(0.168);
	m_vDefault3.push_back(-1.06099);
	m_vDefault3.push_back(0.667995);
	m_vDefault3.push_back(-0.026);
	m_vDefault3.push_back(-1.00699);
	m_vDefault3.push_back(-0.872992);
	m_vDefault3.push_back(-0.726994);
	m_vDefault3.push_back(-0.579996);
	m_vDefault3.push_back(-0.654995);
	m_vDefault3.push_back(-0.798993);
	m_vDefault3.push_back(0.790993);
	m_vDefault3.push_back(0.403998);
	m_vDefault3.push_back(0.322999);

	m_vDefault4.push_back(0.104);
	m_vDefault4.push_back(0.511997);
	m_vDefault4.push_back(0.457998);
	m_vDefault4.push_back(0.097);
	m_vDefault4.push_back(-0.642995);
	m_vDefault4.push_back(-1.30901);
	m_vDefault4.push_back(-0.530997);
	m_vDefault4.push_back(-0.348999);
	m_vDefault4.push_back(-0.725994);
	m_vDefault4.push_back(-0.954991);
	m_vDefault4.push_back(-0.760994);
	m_vDefault4.push_back(0.729994);
	m_vDefault4.push_back(0.138);

	//save the sprite id
	m_nSpriteID = m_pSpriteManager->LoadSprite(szFileName, false);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		AddOne
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Adds a one piece to the base/torso
//
//	Note:			fPosX/fPosY is a ratio between -1.0 <--> 1.0 of
//					how far on the base to attach the leg
//
//////////////////////////////////////////////////////////////////////////
void CBaseFrame::AddOne(const char *szFileName01, const double &fPosX, const double &fPosY, bool bBehind)
{
	if(!szFileName01)
		return;

	tPiece *pPiece01 = new tPiece;

	//////////////////////////////////////////////////////////////////////////
	//PIECE01
	//////////////////////////////////////////////////////////////////////////

	pPiece01->nSpriteID	= m_pSpriteManager->LoadSprite(szFileName01, false);
	pPiece01->fRotate	= 0.0f;
	pPiece01->bBehind	= bBehind;
	pPiece01->fOffsetX	= (double)(m_pSpriteManager->GetWidth(m_nSpriteID)/2.0f) * fPosX;
	pPiece01->fOffsetY	= (double)(m_pSpriteManager->GetHeight(m_nSpriteID)/2.0f) * fPosY;
	pPiece01->fScaleX	= 1.0f;
	pPiece01->fScaleY	= 1.0f;
	pPiece01->pNode		= NULL;

	m_pSpriteManager->SetCenter(pPiece01->nSpriteID, (double)m_pSpriteManager->GetWidth(pPiece01->nSpriteID)/2.0f, (double)m_pSpriteManager->GetHeight(pPiece01->nSpriteID));

	m_vDefault.push_back(pPiece01->fRotate);

	m_vNodes.push_back(pPiece01);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		AddThree
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Adds a 3piece to the base/torso
//
//	Note:			fPosX/fPosY is a ratio between -1.0 <--> 1.0 of
//					how far on the base to attach the leg
//
//////////////////////////////////////////////////////////////////////////
void CBaseFrame::AddThree(const char *szFileName01, const char *szFileName02, const char *szFileName03, const double &fPosX, const double &fPosY, bool bBehind)
{
	if(!szFileName01 || !szFileName02 || !szFileName03)
		return;

	tPiece *pPiece01 = new tPiece;
	tPiece *pPiece02 = new tPiece;
	tPiece *pPiece03 = new tPiece;

	//////////////////////////////////////////////////////////////////////////
	//PIECE01
	//////////////////////////////////////////////////////////////////////////
	
	pPiece01->nSpriteID	= m_pSpriteManager->LoadSprite(szFileName01, false);
	pPiece01->fRotate	= 0.0f;
	pPiece01->bBehind	= bBehind;
	pPiece01->fOffsetX	= (double)(m_pSpriteManager->GetWidth(m_nSpriteID)/2.0f) * fPosX;
	pPiece01->fOffsetY	= (double)(m_pSpriteManager->GetHeight(m_nSpriteID)/2.0f) * fPosY;
	pPiece01->fScaleX	= 1.0f;
	pPiece01->fScaleY	= 1.0f;
	pPiece01->pNode		= pPiece02;
	
	m_pSpriteManager->SetCenter(pPiece01->nSpriteID,m_pSpriteManager->GetWidth(pPiece01->nSpriteID)/2.0f, 0.0f);

	m_vDefault.push_back(pPiece01->fRotate);

	//////////////////////////////////////////////////////////////////////////
	//PIECE02
	//////////////////////////////////////////////////////////////////////////

	pPiece02->nSpriteID	= m_pSpriteManager->LoadSprite(szFileName02, false);
	pPiece02->fRotate	= 0.0f;
	pPiece02->bBehind	= bBehind;
	pPiece02->fOffsetX	= 0.0f;
	pPiece02->fOffsetY	= (double)m_pSpriteManager->GetHeight(pPiece01->nSpriteID);
	pPiece02->fScaleX	= 1.0f;
	pPiece02->fScaleY	= 1.0f;
	pPiece02->pNode		= pPiece03;

	m_pSpriteManager->SetCenter(pPiece02->nSpriteID,m_pSpriteManager->GetWidth(pPiece02->nSpriteID)/2.0f, 0.0f);

	m_vDefault.push_back(pPiece02->fRotate);

	//////////////////////////////////////////////////////////////////////////
	//PIECE03
	//////////////////////////////////////////////////////////////////////////

	pPiece03->nSpriteID	= m_pSpriteManager->LoadSprite(szFileName03, false);
	pPiece03->fRotate	= 0.0f;
	pPiece01->bBehind	= bBehind;
	pPiece03->fOffsetX	= 0.0f;
	pPiece03->fOffsetY	= (double)m_pSpriteManager->GetHeight(pPiece02->nSpriteID);
	pPiece03->fScaleX	= 1.0f;
	pPiece03->fScaleY	= 1.0f;
	pPiece03->pNode		= NULL;

	m_pSpriteManager->SetCenter(pPiece03->nSpriteID,m_pSpriteManager->GetWidth(pPiece03->nSpriteID)/2.0f, 0.0f);

	m_vDefault.push_back(pPiece02->fRotate);

	m_vNodes.push_back(pPiece01);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Draw
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		draws the tree
//
//////////////////////////////////////////////////////////////////////////
void CBaseFrame::Draw()
{
	int nTempPiecePos = 0;
	int nTempArrayPos = -1;
	//draw all the pieces in the back/behind
	for(int i = 0; i < (int)m_vNodes.size(); i++)
	{
		nTempPiecePos = 0;
		nTempArrayPos++;

		if(!m_vNodes[i]->bBehind)
			continue;

		if(nTempArrayPos == m_nArrayPos && nTempPiecePos == m_nPiecePos)
			m_pSpriteManager->DrawSprite(m_vNodes[i]->nSpriteID, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		else
			m_pSpriteManager->DrawSprite(m_vNodes[i]->nSpriteID);

		//set the node
		tPiece *pNextNode = m_vNodes[i]->pNode;

		//rip thru all the nodes
		while(pNextNode)
		{
			nTempPiecePos++;

			if(nTempArrayPos == m_nArrayPos && nTempPiecePos == m_nPiecePos)
				m_pSpriteManager->DrawSprite(pNextNode->nSpriteID, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			else
				m_pSpriteManager->DrawSprite(pNextNode->nSpriteID);

			pNextNode = pNextNode->pNode;
		}
	}

	//draw the base/torso
	if(m_nArrayPos == m_vNodes.size())
		m_pSpriteManager->DrawSprite(m_nSpriteID, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
	else
		m_pSpriteManager->DrawSprite(m_nSpriteID);

	nTempPiecePos = 0;
	nTempArrayPos = -1;

	//draw all the pieces in the front
	for(int i = 0; i < (int)m_vNodes.size(); i++)
	{
		nTempPiecePos = 0;
		nTempArrayPos++;

		if(m_vNodes[i]->bBehind)
			continue;

		if(nTempArrayPos == m_nArrayPos && nTempPiecePos == m_nPiecePos)
			m_pSpriteManager->DrawSprite(m_vNodes[i]->nSpriteID, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
		else
			m_pSpriteManager->DrawSprite(m_vNodes[i]->nSpriteID);


		//set the node
		tPiece *pNextNode = m_vNodes[i]->pNode;

		//rip thru all the nodes
		while(pNextNode)
		{

			nTempPiecePos++;

			if(nTempArrayPos == m_nArrayPos && nTempPiecePos == m_nPiecePos)
				m_pSpriteManager->DrawSprite(pNextNode->nSpriteID, D3DXCOLOR(1.0f, 0.0f, 0.0f, 1.0f));
			else
				m_pSpriteManager->DrawSprite(pNextNode->nSpriteID);

			pNextNode = pNextNode->pNode;
		}
	}
}

//unsigned int __stdcall Main2(void *pData)

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Update
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Updates the tree
//
//////////////////////////////////////////////////////////////////////////
void CBaseFrame::Update()
{
	//m_ThreadHandle = (HANDLE)_beginthreadex(NULL, 0, Main2, 0, 0,  (unsigned int *)&m_ThreadHandle);
	
	Interpolate();

	m_pSpriteManager->ScaleSprite(m_nSpriteID, m_fScaleX, m_fScaleY);
	m_pSpriteManager->RotateSprite(m_nSpriteID, m_fRotate);

	m_pSpriteManager->TranslateSprite(m_nSpriteID, 512, 512);

	for(int i = 0; i < (int)m_vNodes.size(); i++)
	{
		m_pSpriteManager->ScaleSprite(m_vNodes[i]->nSpriteID, m_vNodes[i]->fScaleX, m_vNodes[i]->fScaleY);
		m_pSpriteManager->RotateSprite(m_vNodes[i]->nSpriteID, m_vNodes[i]->fRotate);
		m_pSpriteManager->TranslateSprite(m_vNodes[i]->nSpriteID, m_vNodes[i]->fOffsetX, m_vNodes[i]->fOffsetY);
		m_pSpriteManager->SetMatrix(m_vNodes[i]->nSpriteID, m_pSpriteManager->GetMatrix(m_vNodes[i]->nSpriteID) * m_pSpriteManager->GetMatrix(m_nSpriteID));

		//set the node
		tPiece *pNextNode = m_vNodes[i]->pNode;
		tPiece *pPrevNode = m_vNodes[i];

		//rip through all the nodes
		while(pNextNode)
		{
			m_pSpriteManager->ScaleSprite(pNextNode->nSpriteID, pNextNode->fScaleX, pNextNode->fScaleY);
			m_pSpriteManager->RotateSprite(pNextNode->nSpriteID, pNextNode->fRotate);
			m_pSpriteManager->TranslateSprite(pNextNode->nSpriteID, pNextNode->fOffsetX, pNextNode->fOffsetY);
			m_pSpriteManager->SetMatrix(pNextNode->nSpriteID, m_pSpriteManager->GetMatrix(pNextNode->nSpriteID) * m_pSpriteManager->GetMatrix(pPrevNode->nSpriteID));

			pPrevNode = pNextNode;
			pNextNode = pNextNode->pNode;
		}
	}
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		SelectPiece
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		selects the next piece of the frame
//
//////////////////////////////////////////////////////////////////////////
void CBaseFrame::SelectNextPiece()
{
	//increment the position
	m_nPiecePos++;

	//check if we have the base selected
	if(m_nArrayPos == m_vNodes.size())
	{
		m_nArrayPos = 0;
		m_nPiecePos = 0;
	}
		
	//set the node
	tPiece *pNode = m_vNodes[m_nArrayPos];

	//go to the pointer we want to check
	for(int i = 0; i < m_nPiecePos; i++)
	{
		pNode = pNode->pNode;
	}

	//check of the pointer is valid
	if(!pNode)
	{
		//if not, set the piece position to 0 and increment the array position
		m_nPiecePos = 0;
		m_nArrayPos++;

		//check the array position
		if(m_nArrayPos > (int)m_vNodes.size())
			m_nArrayPos = 0;
	}
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		SelectPrevPiece
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		selects the previous array of the frame
//
//////////////////////////////////////////////////////////////////////////
void CBaseFrame::SelectPrevArray()
{
	//increment the position
	m_nArrayPos--;
	m_nPiecePos = 0;

	//check the array position
	if(m_nArrayPos < 0)
		m_nArrayPos = (int)m_vNodes.size();
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		SelectPrevPiece
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		selects the previous array of the frame
//
//////////////////////////////////////////////////////////////////////////
void CBaseFrame::SelectNextArray()
{
	//increment the position
	m_nArrayPos++;
	m_nPiecePos = 0;

	//check the array position
	if(m_nArrayPos > (int)m_vNodes.size())
		m_nArrayPos = 0;

	//output some info to the console window
	COUT << "PIECE POSITION " << m_nPiecePos << "  ARRAY POSITION " << m_nArrayPos << endl;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		RotatePiece
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		rotates the selected piece
//
//////////////////////////////////////////////////////////////////////////
void CBaseFrame::RotatePiece(const double &fRotate)
{
	//check if it's the base
	if(m_nArrayPos == (int)m_vNodes.size())
	{
		m_fRotate += fRotate;

		return;
	}

	//set the node
	tPiece *pNode = m_vNodes[m_nArrayPos];

	//go to the pointer we want to check
	for(int i = 0; i < m_nPiecePos; i++)
		pNode = pNode->pNode;

	//check of the pointer is valid
	if(!pNode)
		return;

	pNode->fRotate += fRotate;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		ScalePiece
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		scales the selected piece
//
//////////////////////////////////////////////////////////////////////////
void CBaseFrame::ScalePiece(const double &fScaleX, const double &fScaleY)
{
	//check if it's the base
	if(m_nArrayPos == (int)m_vNodes.size())
	{
		m_fScaleX += fScaleX;
		m_fScaleY += fScaleY;

		return;
	}

	//set the node
	tPiece *pNode = m_vNodes[m_nArrayPos];

	//go to the pointer we want to check
	for(int i = 0; i < m_nPiecePos; i++)
		pNode = pNode->pNode;

	//check of the pointer is valid
	if(!pNode)
		return;

	pNode->fScaleX += fScaleX;
	pNode->fScaleY += fScaleY;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		SaveValues
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		saves all the matrix values
//
//////////////////////////////////////////////////////////////////////////
void CBaseFrame::SaveValues()
{
	fstream MatrixFile;

	//Load height information from file
	MatrixFile.open("matrix.txt", ios_base::out | ios_base::app);

	int k = 0;
	for(int j = 0; j < (int)m_vNodes.size(); j++)
	{
		k++; 

		//set the node
		tPiece *pNextNode = m_vNodes[j]->pNode;
		tPiece *pPrevNode = m_vNodes[j];

		//rip through all the nodes
		while(pNextNode)
		{
			k++; 

			pPrevNode = pNextNode;
			pNextNode = pNextNode->pNode;
		}
	}

	MatrixFile << k << endl;

	for(int i = 0; i < (int)m_vNodes.size(); i++)
	{
		MatrixFile << m_vNodes[i]->fRotate << endl;

		//set the node
		tPiece *pNextNode = m_vNodes[i]->pNode;
		tPiece *pPrevNode = m_vNodes[i];

		//rip through all the nodes
		while(pNextNode)
		{
			MatrixFile << pNextNode->fRotate << endl;

			pPrevNode = pNextNode;
			pNextNode = pNextNode->pNode;
		}
	}

	//close the file
	MatrixFile.close();
}

void CBaseFrame::Interpolate()
{
	static int switchy = 0;

	if(switchy == 0)
	{
		if(m_fInterTime < 0.0f)
		{
			m_fInterTime = 1.0f;
			switchy = 1;
		}

		m_fInterTime -= m_pTimer->GetFractionOfSecondsPassed(0);

		int k = 0;
		for(int i = 0; i < (int)m_vNodes.size(); i++)
		{
			m_vNodes[i]->fRotate += ((m_vDefault2[k++] - m_vNodes[i]->fRotate) / m_fInterTime) * m_pTimer->GetFractionOfSecondsPassed(0);

			//set the node
			tPiece *pNextNode = m_vNodes[i]->pNode;
			tPiece *pPrevNode = m_vNodes[i];

			//rip through all the nodes
			while(pNextNode)
			{
				pNextNode->fRotate += ((m_vDefault2[k++] - pNextNode->fRotate)  / m_fInterTime) * m_pTimer->GetFractionOfSecondsPassed(0);

				pPrevNode = pNextNode;
				pNextNode = pNextNode->pNode;
			}
		}
	}
	else if(switchy == 1)
	{
		if(m_fInterTime < 0.0f)
		{
			m_fInterTime = 1.0f;
			switchy = 2;
		}

		m_fInterTime -= m_pTimer->GetFractionOfSecondsPassed(0);

		int k = 0;
		for(int i = 0; i < (int)m_vNodes.size(); i++)
		{
			m_vNodes[i]->fRotate += ((m_vDefault3[k++] - m_vNodes[i]->fRotate) / m_fInterTime) * m_pTimer->GetFractionOfSecondsPassed(0);

			//set the node
			tPiece *pNextNode = m_vNodes[i]->pNode;
			tPiece *pPrevNode = m_vNodes[i];

			//rip through all the nodes
			while(pNextNode)
			{
				pNextNode->fRotate += ((m_vDefault3[k++] - pNextNode->fRotate)  / m_fInterTime) * m_pTimer->GetFractionOfSecondsPassed(0);

				pPrevNode = pNextNode;
				pNextNode = pNextNode->pNode;
			}
		}
	}
	else if(switchy == 2)
	{
		if(m_fInterTime < 0.0f)
		{
			m_fInterTime = 1.0f;
			switchy = 0;
		}

		m_fInterTime -= m_pTimer->GetFractionOfSecondsPassed(0);

		int k = 0;
		for(int i = 0; i < (int)m_vNodes.size(); i++)
		{
			m_vNodes[i]->fRotate += ((m_vDefault4[k++] - m_vNodes[i]->fRotate) / m_fInterTime) * m_pTimer->GetFractionOfSecondsPassed(0);

			//set the node
			tPiece *pNextNode = m_vNodes[i]->pNode;
			tPiece *pPrevNode = m_vNodes[i];

			//rip through all the nodes
			while(pNextNode)
			{
				pNextNode->fRotate += ((m_vDefault4[k++] - pNextNode->fRotate)  / m_fInterTime) * m_pTimer->GetFractionOfSecondsPassed(0);

				pPrevNode = pNextNode;
				pNextNode = pNextNode->pNode;
			}
		}
	}
}