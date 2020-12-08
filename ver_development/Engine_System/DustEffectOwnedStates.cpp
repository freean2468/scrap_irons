#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CDustEffectUsual::Enter(CDustEffect* pDustEffect){

}

void CDustEffectUsual::Execute(CDustEffect* pDustEffect){
	CBody* t_pBody = pDustEffect->GetBody();

	t_pBody->GetPriPos()->x += pDustEffect->GetAceX();
	t_pBody->GetPriPos()->y += pDustEffect->GetAceY();

	t_pBody->GetPriSca()->x += 0.01f;
	t_pBody->GetPriSca()->y += 0.01f;

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a > 0.0f)
		t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.005f;

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.0f)
		pDustEffect->SetIsDie(true);

	pDustEffect->RenderOrgan();
}

void CDustEffectUsual::Exit(CDustEffect* pDustEffect){

}

bool CDustEffectUsual::OnMessage(CDustEffect* agent, const Telegram& msg){
	return false;
}