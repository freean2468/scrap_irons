#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CStageGoodHopeUsual::Enter(CStageGoodHope* pGoodHope){
	
}

void CStageGoodHopeUsual::Execute(CStageGoodHope* pGoodHope){
	// 바디 계산
	CBody* t_pBody = pGoodHope->GetBody();	
	

	// 부속물 계산
	for(int i = 0; i < pGoodHope->GetAttachmentArray()->GetSize(); i++){

	}	

	pGoodHope->RenderOrgan();
}

void CStageGoodHopeUsual::Exit(CStageGoodHope* pGoodHope){

}

bool CStageGoodHopeUsual::OnMessage(CStageGoodHope* agent, const Telegram& msg){
	return false;
}