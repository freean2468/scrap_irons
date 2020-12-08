#include "../BaseHeader.h"

CStageGoodHope::CStageGoodHope(int id):COrganEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CStageGoodHope>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Map/StageGoodHope.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(StageGoodHopeUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CStageGoodHope::~CStageGoodHope(){
	d3d::Delete< CStateMachine<CStageGoodHope>* >(m_pStateMachine);
}