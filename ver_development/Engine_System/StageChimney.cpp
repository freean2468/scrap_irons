#include "../BaseHeader.h"

CStageChimney::CStageChimney(int id):COrganEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CStageChimney>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Map/StageChimney.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(StageChimneyUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CStageChimney::~CStageChimney(){
	d3d::Delete< CStateMachine<CStageChimney>* >(m_pStateMachine);
}