//////////////////////////////////////////////////////////////////
//	Advanced Visual Effects with Direct3D
//	(C)2005 Peter Walsh
//////////////////////////////////////////////////////////////////
#pragma once

#include "Helpers.h"
#include "Particle.h"

namespace ParticleSystem
{
	class cParticle;
	class cParticleSystem;

	const DWORD PARTICLE_VERTEXFORMAT = D3DFVF_XYZ | D3DFVF_DIFFUSE | D3DFVF_TEX1;

	class cParticleSystem
	{
	public:
		cParticleSystem(char* filename);
		~cParticleSystem(void);
		cParticleSystem(const cParticleSystem& otherSystem);

		bool Start();
		bool Run();
		bool Shutdown();
		bool Render();

		LPDIRECT3DTEXTURE9 GetTexture()
		{
			return m_pTexture;
		}

		bool ParseFeatureFile(const TCHAR* featureFile);

		bool ReparseFeatureFile()
		{
			return ParseFeatureFile(m_FeatureFile);
		}

		char* GetName()
		{
			return m_SystemName;
		}
		bool IsSystemDead()
		{
			return m_bSystemDead;
		}

		void SetEmitterPosition(D3DXVECTOR3& position)
		{
			m_EmitterPosition = position;
		}
	protected:

		inline void ResetParticle(cParticle& particle);

		virtual void UpdatePosition()
		{
			//m_EmitterPosition.y = sin((double)timeGetTime() / 400.0f) * 10.0f;
		}

		inline double CalculateRandomValueBetween(double lowerValue, double higherValue)
		{
#ifdef _DEBUG	
			if(lowerValue > higherValue)
			{
				assert(0);
			}
#endif // _DEBUG

			return 	lowerValue + 
				((double)((double)rand() / (double)RAND_MAX) *
				(double)((higherValue) - (lowerValue)));
		}

		inline DWORD CalculateRandomValueBetween(DWORD lowerValue, DWORD higherValue)
		{
#ifdef _DEBUG	
			if(lowerValue > higherValue)
			{
				assert(0);
			}
#endif // _DEBUG
			return ConvertdoubleToDWORDFast(lowerValue + 
				((double)((long double)rand() / (long double)RAND_MAX) *
				(double)((higherValue) - (lowerValue))));
		}

		static inline DWORD ConvertdoubleToDWORDFast(const double incomingdouble) 
		{
			static DWORD outgoingDWORD;

			__asm 
			{
				fld		incomingdouble
					lea		eax, outgoingDWORD
					fistp	dword ptr[eax]
			}

			return outgoingDWORD;
		}

		static inline D3DCOLOR ConvertD3DXCOLORToD3DCOLORFast(D3DXCOLOR& color)
		{
			return D3DCOLOR_ARGB(
				ConvertdoubleToDWORDFast(color.a * 255.0f), ConvertdoubleToDWORDFast(color.r * 255.0f), 
				ConvertdoubleToDWORDFast(color.g * 255.0f), ConvertdoubleToDWORDFast(color.b * 255.0f));
		}

		CACHE_ALIGN cParticle*	m_pParticleArray;

		LPDIRECT3DTEXTURE9 m_pTexture;

		LPDIRECT3DVERTEXBUFFER9 m_pSystemVertexBuffer;
		unsigned int m_NumParticles;
		unsigned int m_EffectID;

		D3DXVECTOR3 m_EmitterPosition;
		D3DXVECTOR3 m_PositionInitial;

		double m_SizeInitialLow, m_SizeInitialHigh;
		double m_SizeFinalLow, m_SizeFinalHigh;

		double m_MassInitialLow, m_MassInitialHigh;
		double m_LifeInitialLow, m_LifeInitialHigh;

		D3DXCOLOR m_ColorInitialLow, m_ColorInitialHigh;
		D3DXCOLOR m_ColorFinalLow, m_ColorFinalHigh;

		BOOL m_bTrackCamera;

		D3DXVECTOR3 m_VelocityInitialLow, m_VelocityInitialHigh;
		D3DXVECTOR3 m_AccelerationInitialLow, m_AccelerationInitialHigh;

		D3DXVECTOR3 m_StartRadius;

		double m_SystemLife;
		double m_SpawnTime;
		bool m_bSystemDead;

		double m_LastParticleEmitTime;

		double m_EmitRate;

		char m_SystemName[MAX_PATH];
		char m_FeatureFile[MAX_PATH];
		char m_Texture[MAX_PATH];
		char m_Effect[MAX_PATH];
	};


}