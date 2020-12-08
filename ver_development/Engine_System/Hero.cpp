#include "../BaseHeader.h"

CHero::CHero(int id):CCharacterEntity(id), _timer(NULL){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CHero>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Character/Main/Hero.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(HeroStand->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	SetHealthy(100);

	_body->SetVelocity(72.0f);
	_bodyRotVelocity = 0.005f;
	_armRotVelocity = 0.05f;
	_pupilRotVelocity = 0.02f;
}

CHero::~CHero(){
	d3d::Delete< CStateMachine<CHero>* >(m_pStateMachine);
	d3d::Delete<CTimer*>(_timer);
}

void CHero::BoundUpdate(){
	SetEntityBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x - GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y - GetBody()->GetHeightHalf(), 0.0f),
		&D3DXVECTOR3(GetBody()->GetPriPos()->x + GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y + GetBody()->GetHeightHalf(), 0.0f));
}