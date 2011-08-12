//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	Emitter.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the emitter
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Helpers.h"
#include "Particle.h"

CACHE_ALIGN struct CParticleStates
{
	D3DXCOLOR	m_d3dColor;			//starting color, ending color is in the next state
	D3DXVECTOR3	m_d3dVelocity;		//speed and direction
	double		m_fAcceleration;	//acceleration
	double		m_fTime;			//time between this state and the next
};

CACHE_ALIGN class CEmitter
{
private:

	CParticle		*m_Particles;		//pointer to the array of particles
	CParticleStates	*m_ParticleStates;	//pointer to all the particle states

	D3DXVECTOR3 m_d3dPosition;		//current position				
	D3DXVECTOR3 m_d3dVelocity;		//current velocity
	double		m_fAcceleration;	//current acceleration
	double		m_fRotation;		//amount to rotate the particles
	double		m_fTime;			//amount of time the emitter is alive

	int			m_nNumberOfParticles;	//the number of particles
	int			m_nNumberOfStates;		//the number of particle states

public:

	CEmitter(){};
	CEmitter(const CEmitter &a){};
	CEmitter &operator=(const CEmitter &a){};
	~CEmitter(){};

	//////////////////////////////////////////////////////////////////////////
	//INLINE FUNCTIONS
	//////////////////////////////////////////////////////////////////////////
	inline void SetPosition(D3DXVECTOR3 &d3dPosition){ memcpy(m_d3dPosition, d3dPosition, sizeof(D3DXVECTOR3) ); };

	bool CreateEmitter(const int nNumberofParticles, const double fTimeAlive);
};