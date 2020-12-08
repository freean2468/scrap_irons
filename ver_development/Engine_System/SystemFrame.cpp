#include "../BaseHeader.h"

CSystemFrame::CSystemFrame(void){
	m_fCurrTimeOfOrigin = 0.0f;
	m_fLastTimeOfOrigin = (float)timeGetTime();

	m_fTimeDeltaOfOrigin = 0.0f;

	m_fAdjustedCurrTime = 0.0f;
	m_fAdjustedLastTime = (float)timeGetTime();

	m_fAdjustedTimeDelta = 0.0f;
}

CSystemFrame::~CSystemFrame(void){

}

void CSystemFrame::CalculationTimeDeltaOfOrigin(){
	m_fCurrTimeOfOrigin  = (float)timeGetTime();
	m_fTimeDeltaOfOrigin = (m_fCurrTimeOfOrigin - m_fLastTimeOfOrigin) * 0.001f;

	m_fLastTimeOfOrigin = m_fCurrTimeOfOrigin;
}

float CSystemFrame::GetTimeDeltaOfOrigin(){
	return m_fTimeDeltaOfOrigin;
}

void CSystemFrame::CalculationAdjustedTimeDelta(){
	m_fAdjustedCurrTime  = (float)timeGetTime();
	m_fAdjustedTimeDelta = (m_fAdjustedCurrTime - m_fAdjustedLastTime) * 0.001f;

	m_fAdjustedLastTime = m_fAdjustedCurrTime;
}

float CSystemFrame::GetAdjustedTimeDelta(){
	return m_fAdjustedTimeDelta;
}

void CSystemFrame::SetFramePerSec(float fFPS){
	if(fFPS != 0.0f)
	{
		m_fSecPerFrame = 1.0f / fFPS;
	}
	else if(fFPS == 0.0f)
	{
		m_fSecPerFrame = 0.0f; // No Lock
	}

	m_fLimitFPS = fFPS;
	m_fFPS = 0.0f;

	m_iFrameCount = 0;

	m_fTimer = 0.0f;
	m_fAcculTime = 0.0f;
}

bool CSystemFrame::Update(float timeDelta) {
	m_fTimer += timeDelta; // 진행되는 시간
	m_fAcculTime += timeDelta; // 실제 시간

	if(m_fSecPerFrame != 0.0f)
	{
		if(m_fTimer < 0.0f) // Frame이 너무 빠를 경우 (지정한 FPS를 넘길경우)
		{
			// FPS 계산
			if((float)m_iFrameCount / m_fAcculTime != 0.0f)
			{
				m_fFPS = (float)m_iFrameCount / m_fAcculTime;
				m_fAcculTime = 0;
				m_iFrameCount = 0;
			}

			return false;
		}
	}
	else if(m_fSecPerFrame == 0.0f) // No Lock (그냥 계산)
	{
		// FPS 계산
		if(m_fAcculTime >= 1.0f)
		{
			if((float)m_iFrameCount / m_fAcculTime != 0.0f)
			{
				m_fFPS = (float)m_iFrameCount / m_fAcculTime;
				m_fAcculTime = 0;
				m_iFrameCount = 0;
			}
		}
	}

	// 한프레임에 해당하는 시간을 뺀다.
	m_fTimer -= m_fSecPerFrame;

	// Frame 수를 올린다.
	m_iFrameCount += 1;

	return true;
} 

bool CSystemFrame::IsFrameSkip(){ 
	// Update 후 Skip 이 일어나는지 확인
	// Skip이 일어나지 않을때 Render 한다
	
	if(m_fSecPerFrame != 0.0f)
	{
		EngineMgr->GetpInformation()->FPSAdjustedCalculation(EngineMgr->GetAdjustedTimeDelta());
		return m_fTimer >= 0;
	}
	else if(m_fSecPerFrame == 0.0f) // No Lock (Skip 하지 않음)
	{
		EngineMgr->GetpInformation()->FPSAdjustedCalculation(EngineMgr->GetAdjustedTimeDelta());
		return false;
	}

	return true;
} 
