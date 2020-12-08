#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CFlowerUsual::Enter(CFlower* pFlower){
	
}

void CFlowerUsual::Execute(CFlower* pFlower){
	// 바디 계산
	CBody* t_pBody = pFlower->GetBody();	
	CBody* t_pCartBody = AIMgr->GetCart()->GetBody();

	if(t_pCartBody->GetRow() == CBaseObject::RIGHT){
		t_pBody->GetPriPos()->x = t_pCartBody->GetPriPos()->x - 29.0f;
		t_pBody->GetPriPos()->y = t_pCartBody->GetPriPos()->y + 47.0f;
	}
	else if(t_pCartBody->GetRow() == CBaseObject::LEFT){
		t_pBody->GetPriPos()->x = t_pCartBody->GetPriPos()->x + 29.0f;
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
				for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
					pFlower->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;				
				}	
			}
		}
		else{
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a != 0.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
				for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
					pFlower->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;				
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
				for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
					pFlower->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;				
				}	
			}
		}
		else{
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a != 0.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
				for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
					pFlower->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;				
				}	
			}
		}
	}

	// 부속물 계산
	for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pFlower->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CFlower::ONE:							
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += pFlower->GetRotVelocity() * 0.8f;
						if(t_Att->GetPriRot()->z >= D3DX_PI/5)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= pFlower->GetRotVelocity() * 0.8f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI/5)
							t_Att->SetAngleState(true);
						break;
				}				
				break;
			case CFlower::TWO:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += pFlower->GetRotVelocity();
						if(t_Att->GetPriRot()->z >= D3DX_PI/7)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= pFlower->GetRotVelocity();
						if(t_Att->GetPriRot()->z <= -D3DX_PI/7)
							t_Att->SetAngleState(true);
						break;
				}		
				break;
			case CFlower::THREE:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z -= pFlower->GetRotVelocity() * 0.7f;
						if(t_Att->GetPriRot()->z <= D3DX_PI/4)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z += pFlower->GetRotVelocity() * 0.7f;
						if(t_Att->GetPriRot()->z >= -D3DX_PI/4)
							t_Att->SetAngleState(true);
						break;
				}		
				break;
			default:
				break;
		}
	}	

	pFlower->RenderOrgan();
}

void CFlowerUsual::Exit(CFlower* pFlower){

}

bool CFlowerUsual::OnMessage(CFlower* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Event:
			agent->GetFSM()->ChangeState(FlowerEvent->Instance());
			return true;
		case Msg_Pull:
			agent->GetFSM()->ChangeState(FlowerMove->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
void CFlowerEvent::Enter(CFlower* pFlower){
	
}

void CFlowerEvent::Execute(CFlower* pFlower){
		// 바디 계산
	CBody* t_pBody = pFlower->GetBody();	
	CBody* t_pCartBody = AIMgr->GetCart()->GetBody();

	if(t_pCartBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){			
			t_pBody->GetPriRot()->y -= 0.05f;

			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
		if(t_pBody->GetPriRot()->y < D3DX_PI * 0.5f){
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a < 1.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;
				for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
					pFlower->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;				
				}	
			}
		}
		else{
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a != 0.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
				for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
					pFlower->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;				
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
				for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
					pFlower->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;				
				}	
			}
		}
		else{
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a != 0.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
				for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
					pFlower->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;				
				}	
			}
		}
	}

	// 부속물 계산
	for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pFlower->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CFlower::ONE:							
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += pFlower->GetRotVelocity() * 0.8f;
						if(t_Att->GetPriRot()->z >= D3DX_PI/5)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= pFlower->GetRotVelocity() * 0.8f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI/5)
							t_Att->SetAngleState(true);
						break;
				}				
				break;
			case CFlower::TWO:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += pFlower->GetRotVelocity();
						if(t_Att->GetPriRot()->z >= D3DX_PI/7)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= pFlower->GetRotVelocity();
						if(t_Att->GetPriRot()->z <= -D3DX_PI/7)
							t_Att->SetAngleState(true);
						break;
				}		
				break;
			case CFlower::THREE:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z -= pFlower->GetRotVelocity() * 0.7f;
						if(t_Att->GetPriRot()->z <= D3DX_PI/4)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z += pFlower->GetRotVelocity() * 0.7f;
						if(t_Att->GetPriRot()->z >= -D3DX_PI/4)
							t_Att->SetAngleState(true);
						break;
				}		
				break;
			default:
				break;
		}
	}	

	pFlower->RenderOrgan();
}

void CFlowerEvent::Exit(CFlower* pFlower){

}

bool CFlowerEvent::OnMessage(CFlower* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(FlowerUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Move State
///////////////////////////////////////////////////////////
void CFlowerMove::Enter(CFlower* pFlower){
	
}

void CFlowerMove::Execute(CFlower* pFlower){
	// 바디 계산
	CBody* t_pBody = pFlower->GetBody();	
	CBody* t_pCartBody = AIMgr->GetCart()->GetBody();

	if(t_pCartBody->GetRow() == CBaseObject::RIGHT){
		t_pBody->GetPriPos()->x = t_pCartBody->GetPriPos()->x - 29.0f;
		t_pBody->GetPriPos()->y = t_pCartBody->GetPriPos()->y + 47.0f;

		if(t_pBody->GetPriRot()->y > 0.0f){			
			t_pBody->GetPriRot()->y -= 0.05f;

			if(t_pBody->GetPriRot()->y < 0.0f)
			t_pBody->GetPriRot()->y = 0.0f;
		}
		if(t_pBody->GetPriRot()->y < D3DX_PI * 0.5f){
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a < 1.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;
				for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
					pFlower->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;				
				}	
			}
		}
		else{
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a != 0.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
				for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
					pFlower->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;				
				}	
			}
		}		
	}
	else if(t_pCartBody->GetRow() == CBaseObject::LEFT){
		t_pBody->GetPriPos()->x = t_pCartBody->GetPriPos()->x + 29.0f;
		t_pBody->GetPriPos()->y = t_pCartBody->GetPriPos()->y + 47.0f;

		if(t_pBody->GetPriRot()->y < D3DX_PI){			
			t_pBody->GetPriRot()->y += 0.05f;
		
			if(t_pBody->GetPriRot()->y > D3DX_PI)
			t_pBody->GetPriRot()->y = D3DX_PI;	
		}
		if(t_pBody->GetPriRot()->y > D3DX_PI * 0.5f){
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a < 1.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;
				for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
					pFlower->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.05f;				
				}	
			}
		}
		else{
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a != 0.0f){
				t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
				for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
					pFlower->GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;				
				}	
			}
		}
	}

	// 부속물 계산
	for(int i = 0; i < pFlower->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pFlower->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CFlower::ONE:							
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += pFlower->GetRotVelocity() * 0.8f;
						if(t_Att->GetPriRot()->z >= D3DX_PI/5)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= pFlower->GetRotVelocity() * 0.8f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI/5)
							t_Att->SetAngleState(true);
						break;
				}				
				break;
			case CFlower::TWO:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += pFlower->GetRotVelocity();
						if(t_Att->GetPriRot()->z >= D3DX_PI/7)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= pFlower->GetRotVelocity();
						if(t_Att->GetPriRot()->z <= -D3DX_PI/7)
							t_Att->SetAngleState(true);
						break;
				}		
				break;
			case CFlower::THREE:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z -= pFlower->GetRotVelocity() * 0.7f;
						if(t_Att->GetPriRot()->z <= D3DX_PI/4)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z += pFlower->GetRotVelocity() * 0.7f;
						if(t_Att->GetPriRot()->z >= -D3DX_PI/4)
							t_Att->SetAngleState(true);
						break;
				}		
				break;
			default:
				break;
		}
	}	

	pFlower->RenderOrgan();
}

void CFlowerMove::Exit(CFlower* pFlower){

}

bool CFlowerMove::OnMessage(CFlower* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Event:
			agent->GetFSM()->ChangeState(FlowerEvent->Instance());
			return true;
		case Msg_Put:
			agent->GetFSM()->ChangeState(FlowerUsual->Instance());
			return true;
		default:
			return false;
	}
}
