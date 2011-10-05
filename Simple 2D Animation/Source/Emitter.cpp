//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	Emitter.cpp
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the emitter
//
//////////////////////////////////////////////////////////////////////////

#include "Emitter.h"

bool CEmitter::CreateEmitter(const int nNumberofParticles, const double fTimeAlive)
{
	//set the starting variables
	m_nNumberOfParticles	= nNumberofParticles;
	m_fTime					= fTimeAlive;

	return true;
}