#include "../BaseHeader.h"

CBoostEffect::CBoostEffect(CBody* p_pOrgan):CBaseEffect(BOOST){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CBoostEffect>(this);

	LoadEntityData("./script/Effect/BoostEffect.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(BoostEffectUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_origin = NULL;
	_origin = p_pOrgan;
}

CBoostEffect::~CBoostEffect(){

}