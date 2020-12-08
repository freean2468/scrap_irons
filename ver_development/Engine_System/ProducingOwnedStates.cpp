#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Producing State
///////////////////////////////////////////////////////////
void CProducingMinimize::Enter(CProducing* pProducing){
	
}

void CProducingMinimize::Execute(CProducing* pProducing){
	// 바디 계산

	// 부속물 계산
	
}

void CProducingMinimize::Exit(CProducing* pProducing){

}

bool CProducingMinimize::OnMessage(CProducing* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Activate:
			agent->GetFSM()->ChangeState(ProducingActive->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
void CProducingActive::Enter(CProducing* pProducing){
	
}

void CProducingActive::Execute(CProducing* pProducing){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	// 각종 계산

	// 바디 계산
	pProducing->GetBody()->GetPriPos()->x = t_vPos.x;
	pProducing->GetBody()->GetPriPos()->y = t_vPos.y;

	// 부속물 계산	
	static float t_fNeedleRot = 0.0f;
	static float t_fNeedleAlpha = 1.0f;
	static float t_fVelocity = 1.0f;

	for(int i = 0; i < pProducing->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pProducing->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CProducing::NEEDLE:			
				if(t_Att->GetPriRot()->z >= D3DX_PI*2.0f){
					if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a > 0.00f){
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.01f;
						t_fNeedleAlpha = t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a;
					}
				}
				else{
					t_Att->GetPriRot()->z += D3DX_PI * (0.04f * t_fVelocity);
					t_fNeedleRot = t_Att->GetPriRot()->z;
					t_Att->GetPriSca()->x += 0.01f;
					t_Att->GetPriSca()->y += 0.01f;
				}
				break;
			case CProducing::DOORLEFT:				
				if(t_fNeedleAlpha <= 0.0f){
					if(t_Att->GetPriRot()->y <= D3DX_PI * 0.42f)
						t_Att->GetPriRot()->y += D3DX_PI * 0.002f;
				}
				break;
			case CProducing::DOORRIGHT:
				if(t_fNeedleAlpha <= 0.0f){
					if(t_Att->GetPriRot()->y >= -D3DX_PI * 0.42f)
						t_Att->GetPriRot()->y -= D3DX_PI * 0.002f;
				}
				break;
			default:
				break;
		}
	}	

	t_fVelocity += 0.0001f;

	pProducing->RenderOrgan();
}

void CProducingActive::Exit(CProducing* pProducing){
	for(int i = 0; i < pProducing->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pProducing->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CProducing::NEEDLE:			
				t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a = 1.0f;
				t_Att->GetPriRot()->z = 0.0f;
				t_Att->GetPriSca()->x = 1.0f;
				t_Att->GetPriSca()->y = 1.0f;				
				break;
			case CProducing::DOORLEFT:								
			case CProducing::DOORRIGHT:
				t_Att->GetPriRot()->y = 0.0f;
				break;
			default:
				break;
		}
	}	
}

bool CProducingActive::OnMessage(CProducing* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Close:
			agent->GetFSM()->ChangeState(ProducingMinimize->Instance());
			return true;
		default:
			return false;
	}
}