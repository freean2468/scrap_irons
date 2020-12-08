#include "../BaseHeader.h"

CProduction::CProduction(int id):COrganEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CProduction>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/UserInterface/Production/Production.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(ProductionMinimize->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_pFont = d3d::IniFont(25, 21, 500, false, "맑은 고딕");
	_completeState = false;
}

CProduction::~CProduction(){
	d3d::Delete< CStateMachine<CProduction>* >(m_pStateMachine);
}