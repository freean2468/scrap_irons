#include "../BaseHeader.h"

CStageDustBridge::CStageDustBridge(int id):COrganEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CStageDustBridge>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Map/StageDustBridge.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(StageDustBridgeUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CStageDustBridge::~CStageDustBridge(){
	d3d::Delete< CStateMachine<CStageDustBridge>* >(m_pStateMachine);
}