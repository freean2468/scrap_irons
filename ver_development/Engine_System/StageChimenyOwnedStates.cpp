#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CStageChimneyUsual::Enter(CStageChimney* pChimney){
	
}

void CStageChimneyUsual::Execute(CStageChimney* pChimney){
	// �ٵ� ���
	CBody* t_pBody = pChimney->GetBody();	
	

	// �μӹ� ���
	for(int i = 0; i < pChimney->GetAttachmentArray()->GetSize(); i++){

	}	

	pChimney->RenderOrgan();
}

void CStageChimneyUsual::Exit(CStageChimney* pChimney){

}

bool CStageChimneyUsual::OnMessage(CStageChimney* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Senario:
			agent->GetMessage()->SetUse(true);
			agent->GetMessage()->SetLine((char*)msg.ExtraInfo);
			return true;
		case Msg_SenarioEnd:
			agent->GetMessage()->SetUse(false);
			agent->GetMessage()->SetLine(NULL);
			return true;
		default:
            return false;
	}
}