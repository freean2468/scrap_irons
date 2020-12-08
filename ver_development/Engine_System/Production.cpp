#include "../BaseHeader.h"

CProduction::CProduction(int id):COrganEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CProduction>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/UserInterface/Production/Production.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(ProductionMinimize->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_pFont = d3d::IniFont(25, 21, 500, false, "���� ���");
	_completeState = false;
}

CProduction::~CProduction(){
	d3d::Delete< CStateMachine<CProduction>* >(m_pStateMachine);
}