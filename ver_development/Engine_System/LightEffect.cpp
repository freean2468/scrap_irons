#include "../BaseHeader.h"

CLightEffect::CLightEffect(COrgan* t_pOrgan):CBaseEffect(LIGHT){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CLightEffect>(this);

	LoadEntityData("./script/Effect/LightEffect.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(LightEffectUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_organ = t_pOrgan;
}

CLightEffect::~CLightEffect(){
	d3d::Delete<CStateMachine<CLightEffect>*>(m_pStateMachine);
}