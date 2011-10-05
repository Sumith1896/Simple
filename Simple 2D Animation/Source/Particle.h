//////////////////////////////////////////////////////////////////////////
//
//	Filename: 	Particle.h
//
//	Author:		Nicholas Legg
//
//	Purpose:	Controls the individual particles.
//
//////////////////////////////////////////////////////////////////////////
#pragma once

#include "Helpers.h"

CACHE_ALIGN class CParticle
{
private:

	D3DXCOLOR m_CurrentColor;	//current color
	D3DXVECTOR3 m_d3dPosition;	//current position				

	double m_fLifeTimeElapsed;	//time elapsed
	double m_fLifeSpan;			//total time the particle is alive

	double m_fSizeStart;			//starting size
	double m_fSizeEnd;			//ending size
	double m_fCurrentSize;		//current size

public:
	CParticle(){};
	CParticle(const CParticle &a){};
	CParticle &operator=(const CParticle &a){};
	~CParticle(){};

	bool Shutdown();

	void CreateParticle(const D3DXCOLOR &d3dStartColor, const D3DXCOLOR &d3dEndColor, const D3DXVECTOR3 &d3dPosition, const D3DXVECTOR3 &d3dVelocity, const D3DXVECTOR3 &d3dAcceleration, double fLifeSpan,	double fSizeStart, double fSizeEnd);

	//inline void Run(double lastFrameDuration, const double delta)
	//{	
	//	//static double fractionSecond;
	//	//static double percentComplete;
	//	//static double tempDelta;

	//	//m_fLifeTimeElapsed += lastFrameDuration;
	//	//percentComplete = NO_DIV_0(m_fLifeTimeElapsed) / NO_DIV_0(m_fLifeSpan);
	//	//fractionSecond	= NO_DIV_0(lastFrameDuration) / 1000.0f;
	//	//m_Acceleration.y += (fractionSecond * fractionSecond);

	//	////interpolate the size
	//	//m_fCurrentSize = Interpolate(m_fSizeStart, m_fSizeEnd, percentComplete);

	//	////interpolate the color
	//	//InterpolateColor(m_CurrentColor, m_StartColor, m_EndColor, percentComplete);

	//	////make sure it is not zero
	//	//tempDelta = NO_DIV_0(delta);

	//	//m_Velocity.x += (NO_DIV_0(m_Acceleration.x) / tempDelta);
	//	//m_Velocity.y += (NO_DIV_0(m_Acceleration.y) / tempDelta);
	//	//m_Velocity.z += (NO_DIV_0(m_Acceleration.z) / tempDelta);

	//	//m_d3dPosition.x += (NO_DIV_0(m_Velocity.x) / tempDelta);
	//	//m_d3dPosition.y += (NO_DIV_0(m_Velocity.y) / tempDelta);
	//	//m_d3dPosition.z += (NO_DIV_0(m_Velocity.z) / tempDelta);
	//}

	//inline double Interpolate(const double fValue1, const double fValue2, const double fPercent)
	//{
	//	//some badass fast interpolation
	//	return (fValue1 + (fPercent * (fValue2 - fValue1)));
	//}

	//inline void InterpolateColor(D3DXCOLOR &d3dOutput, const D3DXCOLOR &d3dValue1, const D3DXCOLOR &d3dValue2, const double fPercent)
	//{
	//	//some badass fast interpolation
	//	d3dOutput.r = (d3dValue1.r + (fPercent * (d3dValue2.r - d3dValue1.r)));
	//	d3dOutput.g = (d3dValue1.g + (fPercent * (d3dValue2.g - d3dValue1.g)));
	//	d3dOutput.b = (d3dValue1.b + (fPercent * (d3dValue2.b - d3dValue1.b)));
	//	d3dOutput.a = (d3dValue1.a + (fPercent * (d3dValue2.a - d3dValue1.a)));
	//}

	//inline void SetPosition(D3DXVECTOR3& newPos)
	//{
	//	m_d3dPosition = newPos;
	//}

	//inline void SetVelocity(D3DXVECTOR3& newVel)
	//{
	//	//m_Velocity = newVel;
	//}

	//inline void SetAcceleration(D3DXVECTOR3& newAcc)
	//{
	//	m_Acceleration = newAcc;
	//}

	//inline bool IsDead()
	//{
	//	return (bool)(m_fLifeTimeElapsed > m_fLifeSpan);
	//}

	//inline void SetDead(bool bDead)
	//{
	//	if(!bDead)
	//	{
	//		m_fLifeTimeElapsed = 0.0f;
	//	}
	//	else
	//	{
	//		m_fLifeTimeElapsed = m_fLifeSpan + 0.1f;
	//	}
	//}

	//inline void SetLifeSpan(double milliseconds)
	//{
	//	m_fLifeTimeElapsed = 0.0f;
	//	m_fLifeSpan = milliseconds;
	//}

	//inline void Start()
	//{
	//	// Add init code here
	//}

	//inline D3DXVECTOR3 GetPosition()
	//{
	//	return m_d3dPosition;
	//}

	//inline D3DXCOLOR& GetColor()
	//{
	//	return m_CurrentColor;
	//}

	//inline double GetSize()
	//{
	//	return m_fCurrentSize;
	//}

	//inline void SetSize(double newSizeStart, double newSizeEnd)
	//{
	//	m_fSizeStart = newSizeStart;
	//	m_fCurrentSize = newSizeStart;
	//	m_fSizeEnd = newSizeEnd;		
	//}

	//inline void SetStartColor(D3DXCOLOR& newColor)
	//{
	//	m_StartColor = newColor;
	//	m_CurrentColor = m_StartColor;
	//}

	//inline void SetEndColor(D3DXCOLOR& newColor)
	//{
	//	m_EndColor = newColor;
	//}												
};