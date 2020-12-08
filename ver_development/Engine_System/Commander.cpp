#include "../BaseHeader.h"

CCommander::CCommander(int id):COrganEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CCommander>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/UserInterface/Commander/Commander.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(CommanderMinimize->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CCommander::~CCommander(){
	d3d::Delete< CStateMachine<CCommander>* >(m_pStateMachine);
}