#include "../BaseHeader.h"

CCart::CCart(int id):CCharacterEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CCart>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Character/Main/Cart.txt", this);

	// ó�� ���¸� �ʱ�ȭ
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