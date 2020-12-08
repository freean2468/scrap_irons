#include "../BaseHeader.h"

CFlower::CFlower(int id):CCharacterEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CFlower>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Character/Main/Flower.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(FlowerEvent->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_rotVelocity = 0.005f;
}

CFlower::~CFlower(){
	d3d::Delete< CStateMachine<CFlower>* >(m_pStateMachine);
}

void CFlower::BoundUpdate(){
	SetEntityBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x - GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y - GetBody()->GetHeightHalf(), 0.0f),
		&D3DXVECTOR3(GetBody()->GetPriPos()->x + GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y + GetBody()->GetHeightHalf(), 0.0f));
}