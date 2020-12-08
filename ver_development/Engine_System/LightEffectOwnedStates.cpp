#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CLightEffectUsual::Enter(CLightEffect* pLightEffect){

}

void CLightEffectUsual::Execute(CLightEffect* pLightEffect){
	CBody* t_pBody = pLightEffect->GetBody();

	if(pLightEffect->GetOrgan()){
		D3DXVECTOR3* t_pPos = pLightEffect->GetOrigin();

		t_pBody->GetPriPos()->x = t_pPos->x;
		t_pBody->GetPriPos()->y = t_pPos->y;
		t_pBody->GetPriPos()->z = t_pPos->z;

		t_pBody->GetPriRot()->z += 0.002f;

		static bool _bAlpha = false;

		if(t_pBody->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.8f || t_pBody->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.2f)
			_bAlpha = !_bAlpha;

		if(_bAlpha){
			t_pBody->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.005f;
			t_pBody->GetPriSca()->x += 0.008f;
			t_pBody->GetPriSca()->y += 0.008f;
		}
		else{
			t_pBody->GetMtrlArray()->Get(0,0).Diffuse.a += 0.005f;
			t_pBody->GetPriSca()->x -= 0.008f;
			t_pBody->GetPriSca()->y -= 0.008f;
		}

		if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.0f)
			pLightEffect->SetIsDie(true);

		pLightEffect->RenderOrgan();
	}
	else
		pLightEffect->SetIsDie(true);
}

void CLightEffectUsual::Exit(CLightEffect* pLightEffect){

}

bool CLightEffectUsual::OnMessage(CLightEffect* agent, const Telegram& msg){
	return false;
}