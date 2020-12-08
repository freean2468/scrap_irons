#include "../BaseHeader.h"

CInteract::CInteract(int id):COrganEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CInteract>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/UserInterface/Interact/Interact.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(InteractActive->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CInteract::~CInteract(){
	d3d::Delete< CStateMachine<CInteract>* >(m_pStateMachine);
}