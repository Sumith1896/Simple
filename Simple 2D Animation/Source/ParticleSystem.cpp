//#include "ParticleSystem.h"
//
//namespace ParticleSystem
//{
//
//	cParticleSystem::cParticleSystem(char* filename)
//	{
//		m_pTexture = 0;
//		m_pSystemVertexBuffer = 0;
//		m_NumParticles = 0;	
//		m_SpawnTime = 0;
//
//		m_SizeInitialLow = 0.5f;
//		m_SizeInitialHigh = 0.5f;
//		m_SizeFinalLow = 1.0f;
//		m_SizeFinalHigh = 1.0f;
//
//		m_bSystemDead = false;
//		m_EmitRate = 1000;
//		m_LastParticleEmitTime = 0;
//
//		m_StartRadius = D3DXVECTOR3(0,0,0);
//
//		m_MassInitialLow = 0.1f;
//		m_MassInitialHigh = 0.2f;
//
//		m_PositionInitial = D3DXVECTOR3(0,0,0);
//		m_EmitterPosition = D3DXVECTOR3(0,0,0);
//
//		m_ColorInitialLow = D3DXCOLOR(1,1,0.2f,1);
//		m_ColorInitialHigh = D3DXCOLOR(1,1,0.2f,1);
//		m_ColorFinalLow = D3DXCOLOR(1,0,0,0.1f);
//		m_ColorFinalHigh = D3DXCOLOR(1,0,0,0.1f);
//
//		m_VelocityInitialLow = D3DXVECTOR3(-0.2f, 0.0f, -0.2f);
//		m_VelocityInitialHigh = D3DXVECTOR3(0.2f, 0.5f, 0.2f);
//
//		m_AccelerationInitialLow = D3DXVECTOR3(0, 0, 0);
//		m_AccelerationInitialHigh = D3DXVECTOR3(0, 0, 0);
//
//		m_LifeInitialLow = 3000;
//		m_LifeInitialHigh = 4000;
//
//		m_SystemLife = 0;
//
//		m_SystemName[0] = 0;
//		m_FeatureFile[0] = 0;
//
//		m_bTrackCamera = false;
//
//		m_pParticleArray = 0;
//
//		strcpy(m_Texture, "media\\Particle_Blob.tga");
//		strcpy(m_Effect, "default_particle.fx");
//		if(filename)
//		{
//			strcpy(m_FeatureFile, filename);
//			ParseFeatureFile(m_FeatureFile);
//		}
//		else
//			assert(0); // Must have a feature file
//
//
//	}
//
//	cParticleSystem::cParticleSystem(const cParticleSystem& otherSystem)
//	{
//		QueryPerformanceCounter((LARGE_INTEGER*)&m_SpawnTime);
//		m_NumParticles = otherSystem.m_NumParticles;
//		m_pParticleArray = new cParticle[m_NumParticles];
//		if(!m_pParticleArray)
//		{
//			assert(0);
//		}
//
//		m_LastParticleEmitTime = 0;
//		m_bSystemDead = false;
//		m_EmitRate = otherSystem.m_EmitRate;
//		m_bTrackCamera = otherSystem.m_bTrackCamera;
//
//		m_pTexture = otherSystem.m_pTexture;
//		m_pTexture->AddRef();
//
//		m_pSystemVertexBuffer = 0;
//		m_EffectID = otherSystem.m_EffectID;
//
//
//		m_EmitterPosition = otherSystem.m_EmitterPosition;
//		m_PositionInitial = otherSystem.m_EmitterPosition;
//
//		m_SizeInitialLow = otherSystem.m_SizeInitialLow;
//		m_SizeInitialHigh = otherSystem.m_SizeInitialHigh;
//		m_SizeFinalLow = otherSystem.m_SizeFinalLow;
//		m_SizeFinalHigh = otherSystem.m_SizeFinalHigh;
//
//		m_MassInitialLow = otherSystem.m_MassInitialLow;
//		m_MassInitialHigh = otherSystem.m_MassInitialHigh;
//		m_LifeInitialLow = otherSystem.m_LifeInitialLow;
//		m_LifeInitialHigh = otherSystem.m_LifeInitialHigh;
//
//		m_ColorInitialLow = otherSystem.m_ColorInitialLow;
//		m_ColorInitialHigh = otherSystem.m_ColorInitialHigh;
//		m_ColorFinalLow = otherSystem.m_ColorFinalLow;
//		m_ColorFinalHigh = otherSystem.m_ColorFinalHigh;
//
//		m_VelocityInitialLow = otherSystem.m_VelocityInitialLow;
//		m_VelocityInitialHigh = otherSystem.m_VelocityInitialHigh;
//		m_AccelerationInitialLow = otherSystem.m_AccelerationInitialLow;
//		m_AccelerationInitialHigh = otherSystem.m_AccelerationInitialHigh;
//
//		m_SystemLife = otherSystem.m_SystemLife;
//
//		m_StartRadius = otherSystem.m_StartRadius;
//
//		strcpy(m_Texture, otherSystem.m_Texture);
//		strcpy(m_SystemName, otherSystem.m_SystemName);
//		strcpy(m_FeatureFile, otherSystem.m_FeatureFile);
//		strcpy(m_Effect, otherSystem.m_Effect);
//	}
//
//	cParticleSystem::~cParticleSystem(void)
//	{		
//		Shutdown();
//	}
//
//	bool cParticleSystem::ParseFeatureFile(const char* featureFile)
//	{
//		FILE* pFile = fopen(featureFile, "r");
//		if(!pFile)
//		{
//			OutputDebugString("ERROR opening particle system feature file\n");
//			assert(0);
//			return false;
//		}
//
//		char inputString[512];
//		
//		fclose(pFile);
//		pFile = 0;
//
//		for(unsigned int i = 0 ; i < m_NumParticles ; i++)
//		{
//			m_pParticleArray[i].Start();
//			ResetParticle(m_pParticleArray[i]);
//		}
//
//		return false;
//	}
//
//	bool cParticleSystem::Start()
//	{
//		QueryPerformanceCounter((LARGE_INTEGER*)&m_LastParticleEmitTime);
//		HRESULT hr = D3DXCreateTextureFromFileEx(GAMEENGINE->GetDevice(), m_Texture, 
//			D3DX_DEFAULT, D3DX_DEFAULT,
//			D3DX_DEFAULT, 0, D3DFMT_FROM_FILE, D3DPOOL_MANAGED, D3DTEXF_LINEAR, 
//			D3DTEXF_LINEAR, 0, 0, 0, &m_pTexture);
//		if(FAILED(hr))
//		{
//			assert(0);
//			return false;
//		}
//
//		indUInt length = sizeof(PARTICLE_VERTEX) * m_NumParticles * 6;
//
//		GAMEENGINE->GetDevice()->CreateVertexBuffer(
//			length, D3DUSAGE_WRITEONLY, PARTICLE_VERTEXFORMAT, D3DPOOL_SYSTEMMEM, &m_pSystemVertexBuffer, 0);
//
//		m_EffectID = EFFECTMANAGER->FindEffect(m_Effect);
//
//		return true;
//	}
//
//	void cParticleSystem::ResetParticle(cParticle& particle)
//	{
//		particle.Start();
//
//		D3DXVECTOR3 startRange(0,0,0);
//		startRange.x = CalculateRandomValueBetween(-m_StartRadius.x, m_StartRadius.x);
//		startRange.y = CalculateRandomValueBetween(-m_StartRadius.y, m_StartRadius.y);
//		startRange.z = CalculateRandomValueBetween(-m_StartRadius.z, m_StartRadius.z);
//
//		D3DXVECTOR3 camPos = CAMERA->GetPosition();
//		m_PositionInitial = m_EmitterPosition;
//		if(m_bTrackCamera)
//		{
//			m_PositionInitial += camPos;
//		}
//
//		m_PositionInitial.x += startRange.x;
//		m_PositionInitial.y += startRange.y;
//		m_PositionInitial.z += startRange.z;
//
//		particle.SetPosition(m_PositionInitial);
//		particle.SetDead(false);
//
//		// Calculate velocity
//		static D3DXVECTOR3 velocity;
//		velocity.x = CalculateRandomValueBetween(m_VelocityInitialLow.x, m_VelocityInitialHigh.x);
//		velocity.y = CalculateRandomValueBetween(m_VelocityInitialLow.y, m_VelocityInitialHigh.y);
//		velocity.z = CalculateRandomValueBetween(m_VelocityInitialLow.z, m_VelocityInitialHigh.z);
//		particle.SetVelocity(velocity);
//
//		static D3DXVECTOR3 acceleration;
//		acceleration.x = CalculateRandomValueBetween(m_AccelerationInitialLow.x, m_AccelerationInitialHigh.x);
//		acceleration.y = CalculateRandomValueBetween(m_AccelerationInitialLow.y, m_AccelerationInitialHigh.y);
//		acceleration.z = CalculateRandomValueBetween(m_AccelerationInitialLow.z, m_AccelerationInitialHigh.z);
//		particle.SetAcceleration(acceleration);
//
//		static double life;
//		life = CalculateRandomValueBetween(m_LifeInitialLow, m_LifeInitialHigh);
//		particle.SetLifeSpan(life);
//
//		static double mass;
//		mass = CalculateRandomValueBetween(m_MassInitialLow, m_MassInitialHigh);
//		particle.SetMass(mass);
//
//		static D3DXCOLOR startColor;
//		static D3DXCOLOR endColor;
//		startColor.r = CalculateRandomValueBetween(m_ColorInitialLow.r, m_ColorInitialHigh.r);
//		startColor.g = CalculateRandomValueBetween(m_ColorInitialLow.g, m_ColorInitialHigh.g);
//		startColor.b = CalculateRandomValueBetween(m_ColorInitialLow.b, m_ColorInitialHigh.b);
//		startColor.a = CalculateRandomValueBetween(m_ColorInitialLow.a, m_ColorInitialHigh.a);
//		particle.SetStartColor(startColor);
//
//		endColor.r = CalculateRandomValueBetween(m_ColorFinalLow.r, m_ColorFinalHigh.r);
//		endColor.g = CalculateRandomValueBetween(m_ColorFinalLow.g, m_ColorFinalHigh.g);
//		endColor.b = CalculateRandomValueBetween(m_ColorFinalLow.b, m_ColorFinalHigh.b);
//		endColor.a = CalculateRandomValueBetween(m_ColorFinalLow.a, m_ColorFinalHigh.a);
//		particle.SetEndColor(endColor);
//
//		static double startSize;
//		static double endSize;
//		startSize = CalculateRandomValueBetween(m_SizeInitialLow, m_SizeInitialHigh);
//		endSize = CalculateRandomValueBetween(m_SizeFinalLow, m_SizeFinalHigh);
//		particle.SetSize(startSize, endSize);
//	}
//
//	bool cParticleSystem::Run()
//	{
//		indInt64 currentCount = 0;
//		indInt64 freq = 0;
//
//		QueryPerformanceFrequency((LARGE_INTEGER*)&freq);
//		QueryPerformanceCounter((LARGE_INTEGER*)&currentCount);
//
//		if(m_SystemLife != -1 && double((currentCount - m_SpawnTime)*1000/freq) > m_SystemLife)
//		{
//			m_bSystemDead = true;
//		}
//
//		UpdatePosition();
//
//		PARTICLE_VERTEX* pVertices = 0;
//		m_pSystemVertexBuffer->Lock(0, 0, (void**)&pVertices, 0);
//		indUInt currentVertex = 0;
//
//		double lastframeDur = GAMEENGINE->GetLastFrameDurationMS();
//		double delta = GAMEENGINE->GetTimeDelta();
//
//		D3DXVECTOR3 particlePos(0,0,0);
//		D3DXVECTOR3 camPos(0,0,0);
//		D3DXVECTOR3 upVec(0,1,0);
//		D3DXVECTOR3 rightVec(1,0,0);
//		D3DXVECTOR3 camToParticleVec(0,0,0);
//		D3DXVECTOR3 leftSide, rightSide;
//		D3DCOLOR curParticleColor;
//
//		double particleSize = 0;
//
//		for(int i = m_NumParticles-1 ; i > -1 ; --i)
//		{
//			if(m_pParticleArray[i].IsDead())
//			{
//				double millisecondsPerParticle = 1000.0f / m_EmitRate;
//
//				double timeDiff = (double)((long double)currentCount - (long double)m_LastParticleEmitTime) / (long double)freq;
//
//				//if((double)(timeDiff*1000.0) >= millisecondsPerParticle)
//				{
//					ResetParticle(m_pParticleArray[i]);
//					QueryPerformanceCounter((LARGE_INTEGER*)&m_LastParticleEmitTime);
//				}
//
//				continue;
//			}
//
//			m_pParticleArray[i].Run(lastframeDur, delta);
//
//			curParticleColor = ConvertD3DXCOLORToD3DCOLORFast(m_pParticleArray[i].GetColor());
//			m_PositionInitial = m_EmitterPosition;
//			particlePos = m_pParticleArray[i].GetPosition();
//			camPos = CAMERA->GetPosition();
//
//			camToParticleVec = particlePos - camPos;
//			D3DXVec3Normalize(&camToParticleVec, &camToParticleVec);
//			D3DXVec3Cross(&rightVec, &camToParticleVec, &upVec);
//			D3DXVec3Normalize(&rightVec, &rightVec);
//
//			particleSize = m_pParticleArray[i].GetSize();
//			rightVec *= particleSize;
//
//			leftSide  = (particlePos - rightVec);
//			rightSide = (particlePos + rightVec);
//
//			pVertices[currentVertex].position.x = leftSide.x;
//			pVertices[currentVertex].position.y = leftSide.y + particleSize;
//			pVertices[currentVertex].position.z = leftSide.z;
//			pVertices[currentVertex].color = curParticleColor;
//			pVertices[currentVertex].tx = 0.0f;
//			pVertices[currentVertex].ty = 0.0f;
//
//			currentVertex++;
//
//			pVertices[currentVertex].position.x = rightSide.x;
//			pVertices[currentVertex].position.y = rightSide.y + particleSize;
//			pVertices[currentVertex].position.z = rightSide.z;
//			pVertices[currentVertex].color = curParticleColor;
//			pVertices[currentVertex].tx = 1.0f;
//			pVertices[currentVertex].ty = 0.0f;
//
//			currentVertex++;
//
//			pVertices[currentVertex].position.x = rightSide.x;
//			pVertices[currentVertex].position.y = rightSide.y - particleSize;
//			pVertices[currentVertex].position.z = rightSide.z;
//			pVertices[currentVertex].color = curParticleColor;
//			pVertices[currentVertex].tx = 1.0f;
//			pVertices[currentVertex].ty = 1.0f;
//
//			currentVertex++;
//
//			pVertices[currentVertex].position.x = rightSide.x;
//			pVertices[currentVertex].position.y = rightSide.y - particleSize;
//			pVertices[currentVertex].position.z = rightSide.z;
//			pVertices[currentVertex].color = curParticleColor;
//			pVertices[currentVertex].tx = 1.0f;
//			pVertices[currentVertex].ty = 1.0f;
//
//			currentVertex++;
//
//			pVertices[currentVertex].position.x = leftSide.x;
//			pVertices[currentVertex].position.y = leftSide.y - particleSize;
//			pVertices[currentVertex].position.z = leftSide.z;
//			pVertices[currentVertex].color = curParticleColor;
//			pVertices[currentVertex].tx = 0.0f;
//			pVertices[currentVertex].ty = 1.0f;
//
//			currentVertex++;
//
//			pVertices[currentVertex].position.x = leftSide.x;
//			pVertices[currentVertex].position.y = leftSide.y + particleSize;
//			pVertices[currentVertex].position.z = leftSide.z;
//			pVertices[currentVertex].color = curParticleColor;
//			pVertices[currentVertex].tx = 0.0f;
//			pVertices[currentVertex].ty = 0.0f;
//
//			currentVertex++;
//		}
//
//		m_pSystemVertexBuffer->Unlock();
//
//		Render();
//
//		return true;
//	}
//
//	bool cParticleSystem::Render()
//	{
//		GAMEENGINE->GetDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
//		GAMEENGINE->GetDevice()->SetRenderState(D3DRS_LIGHTING, FALSE);
//		GAMEENGINE->GetDevice()->SetFVF(PARTICLE_VERTEXFORMAT);
//		GAMEENGINE->GetDevice()->SetStreamSource(0, m_pSystemVertexBuffer, 0, sizeof(PARTICLE_VERTEX));
//
//		GAMEENGINE->GetDevice()->SetRenderState(D3DRS_ZENABLE, FALSE);
//
//		VisualEffects::cEffect* pCurrentEffect;
//
//		if(!GAMEENGINE->IsWireframe())
//		{
//			pCurrentEffect = EFFECTMANAGER->GetEffect(m_EffectID);
//		}
//		else
//		{
//			indUInt effectID = EFFECTMANAGER->FindEffect("debugging.fx");
//			pCurrentEffect = EFFECTMANAGER->GetEffect(effectID);
//		}
//
//		D3DXMATRIX world;
//		D3DXMatrixIdentity(&world);
//
//		//if(m_bTrackCamera == TRUE)
//		//{
//		//	D3DXVECTOR3 camPos = CAMERA->GetPosition();
//		//	D3DXMatrixTranslation(&world, camPos.x, camPos.y, camPos.z);
//		//}
//
//		pCurrentEffect->SetTransforms(
//			world, CAMERA->GetViewMatrix(), CAMERA->GetProjectionMatrix());
//		pCurrentEffect->Dispatch();
//
//		indUInt numPasses = 0;
//		pCurrentEffect->Begin(numPasses);
//
//		for(indUInt passCount = 0 ; passCount < numPasses ; passCount++)
//		{
//			pCurrentEffect->BeginPass(passCount);
//
//			GAMEENGINE->GetDevice()->SetTexture(0, GetTexture());
//			GAMEENGINE->GetDevice()->DrawPrimitive(D3DPT_TRIANGLELIST, 0, m_NumParticles);
//
//			pCurrentEffect->EndPass();			
//		}
//
//		pCurrentEffect->End();
//		return true;
//	}
//
//	bool cParticleSystem::Shutdown()
//	{
//		delete[] m_pParticleArray;
//		m_pParticleArray = 0;
//		SAFE_RELEASE(m_pTexture);
//
//		SAFE_RELEASE(m_pSystemVertexBuffer);
//
//		return true;
//	}
//
//}