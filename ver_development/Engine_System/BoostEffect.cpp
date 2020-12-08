#include "../BaseHeader.h"

CBoostEffect::CBoostEffect(CBody* p_pOrgan):CBaseEffect(BOOST){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CBoostEffect>(this);

	LoadEntityData("./script/Effect/BoostEffect.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(BoostEffectUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_origin = NULL;
	_origin = p_pOrgan;
}

CBoostEffect::~CBoostEffect(){

}