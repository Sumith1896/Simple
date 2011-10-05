#include "AnimationManager.h"

//	Initialize the static variable member.
CAnimationManager *CAnimationManager::m_pInstance = NULL;

CAnimationManager::CAnimationManager()
{

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
CAnimationManager *CAnimationManager::GetInstance()
{
	//if the pointer is NULL call new
	if (!m_pInstance)
		m_pInstance = new CAnimationManager;

	//Return the address of the instance.
	return m_pInstance;
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		DeleteInstance
//
//	Last Modified: 	07/08/2006
//
//	Purpose:		Delete the instance of the class, and set the pointer to NULL
//
//////////////////////////////////////////////////////////////////////////
void CAnimationManager::DeleteInstance()
{
	//delete the pointer, and set it to NULL
	SAFE_DELETE(m_pInstance);
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Shutdown
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Initializes the SpriteManager class
//
//////////////////////////////////////////////////////////////////////////
void CAnimationManager::Shutdown()
{
	
}

//////////////////////////////////////////////////////////////////////////
// 
//	Function: 		Load2DAnimaton
//
//	Last Modified: 	2006/08/04
//
//	Purpose:		Loads data for 2D animation from a file
//
//////////////////////////////////////////////////////////////////////////
int CAnimationManager::Load2DAnimaton(const char *szFileName)
{
	//make sure the pointer is valid
	if(!szFileName)
		return -1;

	fstream AnimationFile;

	//open the file
	AnimationFile.open(szFileName, ios_base::in);

	tAnimation *testanimation = new tAnimation;

	int frames;
	int size;

	AnimationFile >> frames;
	AnimationFile >> size;

	//loop through all the frames
	for(int i = 0; i < frames; i++)
	{
		tKeyFrame *testkey = new tKeyFrame;

		//loop through all the rotations for a given fram
		for(int j = 0; j < size; j++)
		{
			double temp;
			AnimationFile >> temp;

			//push the rotations into the vector
			testkey->vRotations.push_back(temp);
		}

		//save the key frame
		testanimation->m_vKeyFrames.push_back(testkey);
	}

	//save the whole animation
	m_vAnimations.push_back(testanimation);

	//return the ID for this animation
	return ((int)m_vAnimations.size() - 1);

}