#include "../BaseHeader.h"

CIntro::CIntro(int _id) : COrganEntity(_id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CIntro>(this);

	LoadEntityData("./script/UserInterface/Intro/Intro.txt", this);
			
	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(IntroUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CIntro::~CIntro(){
	d3d::Delete< CStateMachine<CIntro>* >(m_pStateMachine);
}