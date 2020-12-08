#include "../BaseHeader.h"

CBGDarkEffect::CBGDarkEffect():COrganEntity(ID_BGEFFECT){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CBGDarkEffect>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Character/Serve/WagooWagoo/WagooWagoo.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(WagooInEvent->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CBGDarkEffect::~CBGDarkEffect(){
	d3d::Delete< CStateMachine<CBGDarkEffect>* >(m_pStateMachine);
}