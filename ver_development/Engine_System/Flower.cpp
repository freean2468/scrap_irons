#include "../BaseHeader.h"

CFlower::CFlower(int id):CCharacterEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CFlower>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Character/Main/Flower.txt", this);

	// ó�� ���¸� �ʱ�ȭ
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