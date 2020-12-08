#include "../BaseHeader.h"

CBoldDustEffect::CBoldDustEffect(D3DXVECTOR3* p_pPos):CBaseEffect(DUST){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CBoldDustEffect>(this);

	LoadEntityData("./script/Effect/BoldDustEffect.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(BoldDustEffectUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_body->GetPriPos()->x = p_pPos->x;
	_body->GetPriPos()->y = p_pPos->y;

	_body->GetPriRot()->z = (float)(rand() % 100);
	_body->GetPriRot()->x = (float)(rand() % 50) * 0.01f;
	_body->GetPriRot()->y = (float)(rand() % 50) * 0.01f;

	_aceX = (float)(rand() % 2) * 0.5f;
	if(rand() % 2 == 0) _aceX *= -1;
	_aceY = ((float)(rand() % 2) + 2)* 1.1f;
}

CBoldDustEffect::~CBoldDustEffect(){
	d3d::Delete<CStateMachine<CBoldDustEffect>*>(m_pStateMachine);
}