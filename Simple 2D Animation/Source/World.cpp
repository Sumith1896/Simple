//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	World.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	high frequency timer
//
//////////////////////////////////////////////////////////////////////////
#include "World.h"

//initialize the static variable member(s)
World *World::m_pInstance = NULL;

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Delete the instance of the class, and set the pointer to NULL
//
//////////////////////////////////////////////////////////////////////////
void World::DeleteInstance()
{
	SAFE_DELETE(m_pInstance);

	COUT << "World::DeleteInstance() - SUCCESS" << endl; 
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		GetInstance
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Creates the first instance of this class and returns it's address.
//
//////////////////////////////////////////////////////////////////////////
World *World::GetInstance()
{
	if(!m_pInstance)
		m_pInstance = new World;

	return m_pInstance;
}

void World::Init()
{
	m_pNewTerrain = NewTerrain::GetInstance();
	m_pCamera = CCamera::GetInstance();
	int inew = 0;
	int jnew = 0;
	int knew = 0;
	bool iseeyou = false;

	for(int i = 0; i < worldarray; i++)
	{
		for(int j = 0; j < worldarray; j++)
		{
			for(int k = 0; k < worldarray; k++)
			{
				for(int l = 0; l < arrayX; l++)
				{
					for(int m = 0; m < arrayY; m++)
					{
						for(int n = 0; n < arrayZ; n++)
						{
							inew = (l + (i * arrayX));
							jnew = (m + (j * arrayY));
							knew = (n + (k * arrayZ));

							chunk[i][j][k].BlockArray[l][m][n].SetVoxelPos(inew, jnew, knew);
							chunk[i][j][k].BlockArray[l][m][n].SetPos(D3DXVECTOR3(inew, jnew, knew));

							chunk[i][j][k].d3dLow.x = (i * arrayX);
							chunk[i][j][k].d3dLow.y = (j * arrayY);
							chunk[i][j][k].d3dLow.z = (k * arrayZ);

							chunk[i][j][k].d3dHigh.x = ((i * arrayX) + arrayX);
							chunk[i][j][k].d3dHigh.y = ((j * arrayY) + arrayY);
							chunk[i][j][k].d3dHigh.z = ((k * arrayZ) + arrayZ);

							if( (rand() % 100 + 1) <= 50)
							{
								chunk[i][j][k].BlockArray[l][m][n].SetType(BLOCK_DIRT);
							}
							else if( (rand() % 100 + 1) <= 50)
							{
								chunk[i][j][k].BlockArray[l][m][n].SetType(BLOCK_ROCK);
							}
							else
							{
								chunk[i][j][k].BlockArray[l][m][n].SetType(BLOCK_BLANK);
							}

							if(chunk[i][j][k].BlockArray[l][m][n].GetType() != BLOCK_BLANK)
							{
								BlockObject *newBlock = NULL;
								if(iseeyou == false)
								{
									if((l < arrayX) && (chunk[i][j][k].BlockArray[l+1][m][n].GetType() == BLOCK_BLANK))
									{
										iseeyou = true;
									}
									else if((l > 0) && (chunk[i][j][k].BlockArray[l-1][m][n].GetType() == BLOCK_BLANK))
									{
										iseeyou = true;
									}
								}
								
								if(iseeyou == false)
								{
									if((m < arrayY) && (chunk[i][j][k].BlockArray[l][m+1][n].GetType() == BLOCK_BLANK))
									{
										iseeyou = true;
									}
									else if((m > 0) && (chunk[i][j][k].BlockArray[l][m-1][n].GetType() == BLOCK_BLANK))
									{
										iseeyou = true;
									}
								}
				
								if(iseeyou == false)
								{
									if((n < arrayZ) && (chunk[i][j][k].BlockArray[l][m][n+1].GetType() == BLOCK_BLANK))
									{
										iseeyou = true;
									}
									else if((n > 0) && (chunk[i][j][k].BlockArray[l][m][n-1].GetType() == BLOCK_BLANK))
									{
										iseeyou = true;
									}
								}

								if(iseeyou)
								{
									newBlock = &chunk[i][j][k].BlockArray[l][m][n];
									chunk[i][j][k].BlockArray[l][m][n].SetVisible(true);
									chunk[i][j][k].VisibleArray.push_back(newBlock);

									iseeyou = false;
								}
							}
						}
					}
				}

			}
		}
	}
}

void World::Cull()
{
	D3DXVECTOR3 *nick = m_pCamera->GetEye();
	D3DXVECTOR3 fdistance;
	int drawcount = 0;
	drawcountgravel = 0;
	drawcountdirt = 0;

	ZeroMemory(&VisibleArrayDirt, sizeof(VisibleArrayDirt));
	ZeroMemory(&VisibleArrayGravel, sizeof(VisibleArrayGravel));

	int newcounter = 0;
	float distance = 0.0f;


	BlockObject *blockIter;
	for(list<BlockObject*>::iterator it=chunk[0][0][0].VisibleArray.begin(); it!=chunk[0][0][0].VisibleArray.end(); ++it)
	{
		// Extra stuff removed
		blockIter = *it;

		D3DXVec3Subtract(&fdistance, nick, &blockIter->GetPos());

		distance = D3DXVec3Length(&fdistance);

		if(FLOAT_EQLS(distance, 50.0f))
		{
			if(blockIter->GetType() != BLOCK_BLANK)
			{
				if(blockIter->GetType() == BLOCK_DIRT)
				{
					memcpy(&VisibleArrayDirt[newcounter++], &(blockIter->GetMatrix()), sizeof(D3DXMATRIX));
					drawcountdirt++;
				}
				else
				{
					memcpy(&VisibleArrayGravel[newcounter++], &(blockIter->GetMatrix()), sizeof(D3DXMATRIX));
					drawcountgravel++;
				}
				drawcount++;
			}
		}
	}

		for(list<BlockObject*>::iterator it=chunk[1][0][0].VisibleArray.begin(); it!=chunk[1][0][0].VisibleArray.end(); ++it)
	{
		// Extra stuff removed
		blockIter = *it;

		D3DXVec3Subtract(&fdistance, nick, &blockIter->GetPos());

		distance = D3DXVec3Length(&fdistance);

		if(FLOAT_EQLS(distance, 50.0f))
		{
			if(blockIter->GetType() != BLOCK_BLANK)
			{
				if(blockIter->GetType() == BLOCK_DIRT)
				{
					memcpy(&VisibleArrayDirt[newcounter++], &(blockIter->GetMatrix()), sizeof(D3DXMATRIX));
					drawcountdirt++;
				}
				else
				{
					memcpy(&VisibleArrayGravel[newcounter++], &(blockIter->GetMatrix()), sizeof(D3DXMATRIX));
					drawcountgravel++;
				}
				drawcount++;
			}
		}
	}

			for(list<BlockObject*>::iterator it=chunk[0][0][2].VisibleArray.begin(); it!=chunk[0][0][2].VisibleArray.end(); ++it)
	{
		// Extra stuff removed
		blockIter = *it;

		D3DXVec3Subtract(&fdistance, nick, &blockIter->GetPos());

		distance = D3DXVec3Length(&fdistance);

		if(FLOAT_EQLS(distance, 50.0f))
		{
			if(blockIter->GetType() != BLOCK_BLANK)
			{
				if(blockIter->GetType() == BLOCK_DIRT)
				{
					memcpy(&VisibleArrayDirt[newcounter++], &(blockIter->GetMatrix()), sizeof(D3DXMATRIX));
					drawcountdirt++;
				}
				else
				{
					memcpy(&VisibleArrayGravel[newcounter++], &(blockIter->GetMatrix()), sizeof(D3DXMATRIX));
					drawcountgravel++;
				}
				drawcount++;
			}
		}
	}
}

void World::Draw()
{
	draw = 0;
	//	for(int i = 0; i < blocksize; i++)
	//{
	//	for(int j = 0; j < blocksize; j++)
	//	{
	//		for(int k = 0; k < blocksize; k++)
	//		{
	//			m_pNewTerrain->Draw(1, &testblock[i][j][k].GetMatrix());
	//		}
	//	}
	//}

	for(int i = 0; i < drawcountdirt; i++)
	{
		m_pNewTerrain->Draw(2, &VisibleArrayDirt[i]);
		draw++;
	}
	for(int i = 0; i < drawcountgravel; i++)
	{
		m_pNewTerrain->Draw(1, &VisibleArrayGravel[i]);
		draw++;
	}
}

void World::LoadChunk()
{
	//load chunk from file
	if(false)
	{
	}
	//create chunk
	else
	{
	}
}