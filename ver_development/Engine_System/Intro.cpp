#include "../BaseHeader.h"

CIntro::CIntro(int _id) : COrganEntity(_id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CIntro>(this);

	LoadEntityData("./script/UserInterface/Intro/Intro.txt", this);
			
	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(IntroUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CIntro::~CIntro(){
	d3d::Delete< CStateMachine<CIntro>* >(m_pStateMachine);
}