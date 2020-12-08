#include "../BaseHeader.h"

CStageGoodHope::CStageGoodHope(int id):COrganEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CStageGoodHope>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Map/StageGoodHope.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(StageGoodHopeUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CStageGoodHope::~CStageGoodHope(){
	d3d::Delete< CStateMachine<CStageGoodHope>* >(m_pStateMachine);
}