#include "../BaseHeader.h"

CStageChimney::CStageChimney(int id):COrganEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CStageChimney>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Map/StageChimney.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(StageChimneyUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CStageChimney::~CStageChimney(){
	d3d::Delete< CStateMachine<CStageChimney>* >(m_pStateMachine);
}