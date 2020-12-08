#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CRayEffectUsual::Enter(CRayEffect* pRayEffect){

}

void CRayEffectUsual::Execute(CRayEffect* pRayEffect){
	CBody* t_pBody = pRayEffect->GetBody();

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a > 0.0f)
		t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.02f;

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.0f)
		pRayEffect->SetIsDie(true);

	pRayEffect->RenderOrgan();
}

void CRayEffectUsual::Exit(CRayEffect* pRayEffect){

}

bool CRayEffectUsual::OnMessage(CRayEffect* agent, const Telegram& msg){
	return false;
}