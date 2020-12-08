#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CTinkleUsual::Enter(CTinkle* pTinkle){
	
}

void CTinkleUsual::Execute(CTinkle* pTinkle){
	// 바디 계산
	CBody* t_pBody = pTinkle->GetBody();	
	CBody* t_pCartBody = AIMgr->GetCart()->GetBody();

	if(t_pCartBody->GetRow() == CBaseObject::RIGHT){
		t_pBody->GetPriPos()->x = t_pCartBody->GetPriPos()->x + 29.0f;
		t_pBody->GetPriPos()->y = t_pCartBody->GetPriPos()->y + 47.0f;
	}
	else if(t_pCartBody->GetRow() == CBaseObject::LEFT){
		t_pBody->GetPriPos()->x = t_pCartBody->GetPriPos()->x - 29.0f;
		t_pBody->GetPriPos()->y = t_pCartBody->GetPriPos()->y + 47.0f;
	}

	if(t_pCartBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){			
			t_pBody->GetPriRot()->y -= 0.05f;

			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
		if(t_pBody->GetPriRot()->y < D3DX_PI * 0.5f){
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a < 1.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;
				for(int i = 0; i < pTinkle->GetAttachmentArray()->GetSize(); i++){
					pTinkle->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;				
				}	
			}
		}
		else{
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a != 0.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
				for(int i = 0; i < pTinkle->GetAttachmentArray()->GetSize(); i++){
					pTinkle->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;				
				}	
			}
		}
	}
	else if(t_pCartBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){			
			t_pBody->GetPriRot()->y += 0.05f;
		
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;	
		}		
		if(t_pBody->GetPriRot()->y > D3DX_PI * 0.5f){
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a < 1.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;
				for(int i = 0; i < pTinkle->GetAttachmentArray()->GetSize(); i++){
					pTinkle->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;				
				}	
			}
		}
		else{
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a != 0.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
				for(int i = 0; i < pTinkle->GetAttachmentArray()->GetSize(); i++){
					pTinkle->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;				
				}	
			}
		}
	}

	static bool _bAlpha = false;

	// 부속물 계산
	for(int i = 0; i < pTinkle->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pTinkle->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CTinkle::EYE:							
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.002f;
						if(t_Att->GetPriRot()->z >= D3DX_PI/20)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.002f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI/20)
							t_Att->SetAngleState(true);
						break;
				}				
				break;
			case CTinkle::EFFECT:
				t_Att->GetPriRot()->z += 0.002f;

				if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.3f)
					_bAlpha = !_bAlpha;

				if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
				else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
				break;
			default:
				break;
		}
	}	

	pTinkle->RenderOrgan();
}

void CTinkleUsual::Exit(CTinkle* pTinkle){

}

bool CTinkleUsual::OnMessage(CTinkle* agent, const Telegram& msg){
	return false;
}

///////////////////////////////////////////////////////////
// Stand In Event State
///////////////////////////////////////////////////////////
void CTinkleCreate::Enter(CTinkle* pTinkle){
	
}

void CTinkleCreate::Execute(CTinkle* pTinkle){
	// 바디 계산
	CBody* t_pBody = pTinkle->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_vPos.x;
	t_pBody->GetPriPos()->y = t_vPos.y;
	t_pBody->GetPriPos()->z = 700 + t_vPos.z;

	static bool _bAlpha = false;

	// 부속물 계산
	for(int i = 0; i < pTinkle->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pTinkle->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CTinkle::EYE:							
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.002f;
						if(t_Att->GetPriRot()->z >= D3DX_PI/20)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.002f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI/20)
							t_Att->SetAngleState(true);
						break;
				}				
				break;
			case CTinkle::EFFECT:
				t_Att->GetPriRot()->z += 0.002f;

				if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.3f)
					_bAlpha = !_bAlpha;

				if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
				else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
				break;
			default:
				break;
		}
	}	

	pTinkle->RenderOrgan();
}

void CTinkleCreate::Exit(CTinkle* pTinkle){

}

bool CTinkleCreate::OnMessage(CTinkle* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(TinkleUsual->Instance());
			return true;
		default:
			return false;
	}
}