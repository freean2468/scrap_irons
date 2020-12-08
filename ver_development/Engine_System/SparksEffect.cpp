#include "../BaseHeader.h"

CSparksEffect::CSparksEffect(D3DXVECTOR3* p_pPos):CBaseEffect(SPARKS){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CSparksEffect>(this);

	LoadEntityData("./script/Effect/SparksEffect.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(SparksEffectUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_body->GetPriPos()->x = p_pPos->x;
	_body->GetPriPos()->y = p_pPos->y;

	_body->GetPriRot()->z = (float)(rand() % 100);
	_body->GetPriRot()->x = (float)(rand() % 50) * 0.01f;
	_body->GetPriRot()->y = (float)(rand() % 50) * 0.01f;

	_scaAceX = (float)(rand() % 3) * 0.06f;
	if(rand() % 2 == 0) _scaAceX *= -1;
	_scaAceY = (float)(rand() % 3) * 0.06f;
	if(rand() % 2 == 0) _scaAceY *= -1;
}

CSparksEffect::~CSparksEffect(){
	d3d::Delete<CStateMachine<CSparksEffect>*>(m_pStateMachine);
}