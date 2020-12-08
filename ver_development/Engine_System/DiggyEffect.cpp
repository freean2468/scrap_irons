#include "../BaseHeader.h"

CDiggyEffect::CDiggyEffect(COrgan* p_pOrgan, float _fTime):CBaseEffect(DIGGY){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CDiggyEffect>(this);

	LoadEntityData("./script/Effect/DiggyEffect.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(DiggyEffectUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_timer = new CTimer((DWORD)_fTime);

	_organ = p_pOrgan;
}

CDiggyEffect::~CDiggyEffect(){
	d3d::Delete<CStateMachine<CDiggyEffect>*>(m_pStateMachine);
	d3d::Delete<CTimer*>(_timer);
}