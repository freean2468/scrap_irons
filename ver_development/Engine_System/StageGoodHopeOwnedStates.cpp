#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CStageGoodHopeUsual::Enter(CStageGoodHope* pGoodHope){
	
}

void CStageGoodHopeUsual::Execute(CStageGoodHope* pGoodHope){
	// �ٵ� ���
	CBody* t_pBody = pGoodHope->GetBody();	
	

	// �μӹ� ���
	for(int i = 0; i < pGoodHope->GetAttachmentArray()->GetSize(); i++){

	}	

	pGoodHope->RenderOrgan();
}

void CStageGoodHopeUsual::Exit(CStageGoodHope* pGoodHope){

}

bool CStageGoodHopeUsual::OnMessage(CStageGoodHope* agent, const Telegram& msg){
	return false;
}