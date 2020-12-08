#include "../BaseHeader.h"

CCart::CCart(int id):CCharacterEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CCart>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Character/Main/Cart.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(CartUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_body->SetVelocity(72.0f);
	_rotVelocity = 0.005f;
}

CCart::~CCart(){
	d3d::Delete< CStateMachine<CCart>* >(m_pStateMachine);
}

void CCart::BoundUpdate(){
	SetEntityBound(&D3DXVECTOR3(0.0f, 0.0f, 0.0f), &D3DXVECTOR3(0.0f, 0.0f, 0.0f));
}