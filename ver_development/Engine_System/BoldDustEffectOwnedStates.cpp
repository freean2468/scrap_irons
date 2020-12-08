#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CBoldDustEffectUsual::Enter(CBoldDustEffect* pBoldDustEffect){

}

void CBoldDustEffectUsual::Execute(CBoldDustEffect* pBoldDustEffect){
	CBody* t_pBody = pBoldDustEffect->GetBody();

	t_pBody->GetPriPos()->x += pBoldDustEffect->GetAceX();
	t_pBody->GetPriPos()->y += pBoldDustEffect->GetAceY();

	t_pBody->GetPriSca()->x += 0.01f;
	t_pBody->GetPriSca()->y += 0.01f;

	AIMgr->GetDustKing()->ApplyDamageEnemyToOurForceByEntity(t_pBody,CCharacterEntity::PAT, 500);

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a > 0.0f)
		t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.01f;

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.0f)
		pBoldDustEffect->SetIsDie(true);

	pBoldDustEffect->RenderOrgan();
}

void CBoldDustEffectUsual::Exit(CBoldDustEffect* pBoldDustEffect){

}

bool CBoldDustEffectUsual::OnMessage(CBoldDustEffect* agent, const Telegram& msg){
	return false;
}