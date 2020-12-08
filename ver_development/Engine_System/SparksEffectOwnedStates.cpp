#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CSparksEffectUsual::Enter(CSparksEffect* pSparksEffect){

}

void CSparksEffectUsual::Execute(CSparksEffect* pSparksEffect){
	CBody* t_pBody = pSparksEffect->GetBody();

	t_pBody->GetPriPos()->y -= 0.01f;

	t_pBody->GetPriSca()->x += pSparksEffect->GetScaAceX();
	t_pBody->GetPriSca()->y += pSparksEffect->GetScaAceY();

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.0f)
		pSparksEffect->SetIsDie(true);

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a > 0.0f)
		t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.04f;	

	pSparksEffect->RenderOrgan();
}

void CSparksEffectUsual::Exit(CSparksEffect* pSparksEffect){

}

bool CSparksEffectUsual::OnMessage(CSparksEffect* agent, const Telegram& msg){
	return false;
}