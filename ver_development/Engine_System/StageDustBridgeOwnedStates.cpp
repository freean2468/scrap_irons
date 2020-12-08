#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CStageDustBridgeUsual::Enter(CStageDustBridge* pDustBridge){
	
}

void CStageDustBridgeUsual::Execute(CStageDustBridge* pDustBridge){
	// 바디 계산
	CBody* t_pBody = pDustBridge->GetBody();	
	

	// 부속물 계산
	for(int i = 0; i < pDustBridge->GetAttachmentArray()->GetSize(); i++){

	}	

	pDustBridge->RenderOrgan();
}

void CStageDustBridgeUsual::Exit(CStageDustBridge* pDustBridge){

}

bool CStageDustBridgeUsual::OnMessage(CStageDustBridge* agent, const Telegram& msg){
	return false;
}