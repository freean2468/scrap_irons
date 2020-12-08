#include "../BaseHeader.h"

CBGDarkEffect::CBGDarkEffect():COrganEntity(ID_BGEFFECT){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CBGDarkEffect>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Character/Serve/WagooWagoo/WagooWagoo.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(WagooInEvent->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CBGDarkEffect::~CBGDarkEffect(){
	d3d::Delete< CStateMachine<CBGDarkEffect>* >(m_pStateMachine);
}