#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CAreaUsual::Enter(CArea* pArea){
	
}

void CAreaUsual::Execute(CArea* pArea){
	pArea->RenderOrgan();
}

void CAreaUsual::Exit(CArea* pArea){

}

bool CAreaUsual::OnMessage(CArea* agent, const Telegram& msg){
	return false;
}