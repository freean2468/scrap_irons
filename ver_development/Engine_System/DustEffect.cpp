#include "../BaseHeader.h"

CDustEffect::CDustEffect(D3DXVECTOR3* p_pPos):CBaseEffect(DUST){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CDustEffect>(this);

	LoadEntityData("./script/Effect/DustEffect.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(DustEffectUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_body->GetPriPos()->x = p_pPos->x;
	_body->GetPriPos()->y = p_pPos->y;

	_body->GetPriRot()->z = (float)(rand() % 100);
	_body->GetPriRot()->x = (float)(rand() % 50) * 0.01f;
	_body->GetPriRot()->y = (float)(rand() % 50) * 0.01f;

	_aceX = (float)(rand() % 3) * 0.4f;
	if(rand() % 2 == 0) _aceX *= -1;
	_aceY = (float)(rand() % 3) * 0.4f;
}

CDustEffect::~CDustEffect(){
	d3d::Delete<CStateMachine<CDustEffect>*>(m_pStateMachine);
}