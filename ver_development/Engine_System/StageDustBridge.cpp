#include "../BaseHeader.h"

CStageDustBridge::CStageDustBridge(int id):COrganEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CStageDustBridge>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Map/StageDustBridge.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(StageDustBridgeUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CStageDustBridge::~CStageDustBridge(){
	d3d::Delete< CStateMachine<CStageDustBridge>* >(m_pStateMachine);
}