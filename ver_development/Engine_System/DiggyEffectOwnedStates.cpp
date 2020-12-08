#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CDiggyEffectUsual::Enter(CDiggyEffect* pDiggyEffect){
	CBody* t_pBody = pDiggyEffect->GetBody();

	t_pBody->GetPriRot()->z = (float)(rand() % 100);
}

void CDiggyEffectUsual::Execute(CDiggyEffect* pDiggyEffect){
	CBody* t_pBody = pDiggyEffect->GetBody();

	t_pBody->GetPriPos()->x = pDiggyEffect->GetOrigin()->x;
	t_pBody->GetPriPos()->y = pDiggyEffect->GetOrigin()->y + 40.0f;

	t_pBody->GetPriRot()->z += 0.3f;

	pDiggyEffect->RenderOrgan();

	if(pDiggyEffect->GetTimer()->IsValidTimer())
		if(pDiggyEffect->GetTimer()->IsElapseTimer()){
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
			pDiggyEffect->SetIsDie(true);
		}
}

void CDiggyEffectUsual::Exit(CDiggyEffect* pDiggyEffect){

}

bool CDiggyEffectUsual::OnMessage(CDiggyEffect* agent, const Telegram& msg){
	return false;
}