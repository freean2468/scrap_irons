#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CBoostEffectUsual::Enter(CBoostEffect* pBoostEffect){

}

void CBoostEffectUsual::Execute(CBoostEffect* pBoostEffect){
	CBody* t_pBody = pBoostEffect->GetBody();

	t_pBody->GetPriPos()->x = pBoostEffect->GetOrigin()->GetPriPos()->x;
	t_pBody->GetPriPos()->y = pBoostEffect->GetOrigin()->GetPriPos()->y + 110.0f;

	pBoostEffect->RenderOrgan();
}

void CBoostEffectUsual::Exit(CBoostEffect* pBoostEffect){

}

bool CBoostEffectUsual::OnMessage(CBoostEffect* agent, const Telegram& msg){
	return false;
}