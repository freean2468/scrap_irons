#include "../BaseHeader.h"

CQuestionMark::CQuestionMark(COrgan* p_pOrgan):CBaseEffect(QUESTIONMARK){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CQuestionMark>(this);

	LoadEntityData("./script/Effect/QuestionMark.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(QuestionMarkUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_origin = p_pOrgan;
	_bOnOff = true;
}

CQuestionMark::~CQuestionMark(){
	d3d::Delete<CStateMachine<CQuestionMark>*>(m_pStateMachine);
}