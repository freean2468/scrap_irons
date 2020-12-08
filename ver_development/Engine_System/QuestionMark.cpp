#include "../BaseHeader.h"

CQuestionMark::CQuestionMark(COrgan* p_pOrgan):CBaseEffect(QUESTIONMARK){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CQuestionMark>(this);

	LoadEntityData("./script/Effect/QuestionMark.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(QuestionMarkUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_origin = p_pOrgan;
	_bOnOff = true;
}

CQuestionMark::~CQuestionMark(){
	d3d::Delete<CStateMachine<CQuestionMark>*>(m_pStateMachine);
}