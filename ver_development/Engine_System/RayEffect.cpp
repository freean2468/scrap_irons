#include "../BaseHeader.h"

CRayEffect::CRayEffect(D3DXVECTOR3* p_pPos, float p_fDistance):CBaseEffect(RAY){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CRayEffect>(this);

	LoadEntityData("./script/Effect/RayEffect.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(RayEffectUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_body->GetPriPos()->x = p_pPos->x;
	_body->GetPriPos()->y = p_pPos->y;
	_body->GetPriPos()->z = p_pPos->z;

	while(_body->GetWidth() < p_fDistance){
		_body->GetPriSca()->x += 0.01f;
	}
}

CRayEffect::~CRayEffect(){
	d3d::Delete<CStateMachine<CRayEffect>*>(m_pStateMachine);
}