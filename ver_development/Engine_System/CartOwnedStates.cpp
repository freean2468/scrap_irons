#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CCartUsual::Enter(CCart* pCart){

}

void CCartUsual::Execute(CCart* pCart){
	CBody* t_pBody = pCart->GetBody();
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();

	if(!EventMgr->GetEventing() && t_pHeroBody->GetPriPos()->x > t_pBody->GetLeft() - 70.0f || t_pHeroBody->GetPriPos()->x > t_pBody->GetRight() + 70.0f){
		pCart->GetFSM()->ChangeState(PulledByHero->Instance());
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pCart->ID(),ID_HERO,Msg_Pull,NO_ADDITIONAL_INFO);
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pCart->ID(),ID_FLOWER,Msg_Pull,NO_ADDITIONAL_INFO);
	}

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.1f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.1f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	// 부속물 계산
	for(int i = 0; i < pCart->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pCart->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CCart::MOUSEUNDER:
				switch(t_Att->GetMoveState()){
						case true:
							// Max라면
							t_Att->GetPriPos()->y += 0.2f;
							if(t_Att->GetPriPos()->y >= -35.0f)	t_Att->SetMoveState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriPos()->y -= 0.2f;
							if(t_Att->GetPriPos()->y <= -42.0f) t_Att->SetMoveState(true);
							break;
					}
				break;
			case CCart::PUPIL:
				t_Att->GetPriRot()->z += pCart->GetRotVelocity() * 15.0f;
				break;
			default:
				break;
		}
	}	

	pCart->RenderOrgan();
}

void CCartUsual::Exit(CCart* pCart){

}

bool CCartUsual::OnMessage(CCart* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Pull:
			agent->GetFSM()->ChangeState(PulledByHero->Instance());
			return true;
		case Msg_Event:
			agent->GetFSM()->ChangeState(CartEvent->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
void CCartEvent::Enter(CCart* pCart){
	
}

void CCartEvent::Execute(CCart* pCart){
	CBody* t_pBody = pCart->GetBody();

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.1f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.1f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	// 부속물 계산
	for(int i = 0; i < pCart->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pCart->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CCart::MOUSEUNDER:
				switch(t_Att->GetMoveState()){
						case true:
							// Max라면
							t_Att->GetPriPos()->y += 0.2f;
							if(t_Att->GetPriPos()->y >= -35.0f)	t_Att->SetMoveState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriPos()->y -= 0.2f;
							if(t_Att->GetPriPos()->y <= -42.0f) t_Att->SetMoveState(true);
							break;
					}
				break;
			case CCart::PUPIL:
				t_Att->GetPriRot()->z += pCart->GetRotVelocity() * 15.0f;
				break;
			default:
				break;
		}
	}	

	pCart->RenderOrgan();
}

void CCartEvent::Exit(CCart* pCart){

}

bool CCartEvent::OnMessage(CCart* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Senario:
			agent->GetMessage()->SetUse(true);
			agent->GetMessage()->SetLine((char*)msg.ExtraInfo);
			return true;
		case Msg_SenarioEnd:
			agent->GetMessage()->SetUse(false);
			agent->GetMessage()->SetLine(NULL);
			return true;
		case Msg_Usual:
			agent->GetFSM()->ChangeState(CartUsual->Instance());
			return true;
		case Msg_Pull:
			agent->GetFSM()->ChangeState(PulledByHero->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Hero에게 끌려질 때
///////////////////////////////////////////////////////////
void CPulledByHero::Enter(CCart* pCart){
	
}

void CPulledByHero::Execute(CCart* pCart){
	// 바디 계산
	CBody* t_pBody = pCart->GetBody();
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();

	t_pBody->SetVelocity(t_pHeroBody->GetVelocity());
	pCart->EntityMove();

	if(t_pHeroBody->GetPriPos()->x > t_pBody->GetPriPos()->x){
		t_pBody->SetRow(CBaseObject::RIGHT);
	}
	else if(t_pHeroBody->GetPriPos()->x < t_pBody->GetPriPos()->x){
		t_pBody->SetRow(CBaseObject::LEFT);
	}

	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.1f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.1f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	if(t_pHeroBody->GetPriPos()->x < t_pBody->GetLeft() - 70.0f){
		pCart->SetCanMove(true);
	}
	else if(t_pHeroBody->GetPriPos()->x > t_pBody->GetRight() + 70.0f){		
		pCart->SetCanMove(true);
	}
	else{
		pCart->SetCanMove(false);
	}

	// 부속물 계산
	for(int i = 0; i < pCart->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pCart->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CCart::PIPE:
				if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f ||  ::GetAsyncKeyState(VK_RIGHT) & 0x8000f){					
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += pCart->GetRotVelocity() * 2.4f;
							if(t_Att->GetPriRot()->z >= D3DX_PI/15)	t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= pCart->GetRotVelocity() * 2.4f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI/15) t_Att->SetAngleState(true);
							break;
					}
				}
				break;
			case CCart::MOUSEUNDER:
				switch(t_Att->GetMoveState()){
						case true:
							// Max라면
							t_Att->GetPriPos()->y += 0.2f;
							if(t_Att->GetPriPos()->y >= -35.0f)	t_Att->SetMoveState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriPos()->y -= 0.2f;
							if(t_Att->GetPriPos()->y <= -42.0f) t_Att->SetMoveState(true);
							break;
					}
				break;
			case CCart::NAIL:
				if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f ||  ::GetAsyncKeyState(VK_RIGHT) & 0x8000f){					
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += pCart->GetRotVelocity() * 2.0f;
							if(t_Att->GetPriRot()->z >= D3DX_PI/20)	t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= pCart->GetRotVelocity() * 2.0f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI/20) t_Att->SetAngleState(true);
							break;
					}
				}
				break;
			case CCart::LUMBER:
				if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f ||  ::GetAsyncKeyState(VK_RIGHT) & 0x8000f){					
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += pCart->GetRotVelocity() * 3.0f;
							if(t_Att->GetPriRot()->z >= D3DX_PI/14) t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= pCart->GetRotVelocity() * 3.0f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI/14)	t_Att->SetAngleState(true);
							break;
					}
				}
				break;
			//case CCart::PLANTER:
			//	if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f ||  ::GetAsyncKeyState(VK_RIGHT) & 0x8000f){					
			//		switch(t_Att->GetAngleState()){
			//			case true:
			//				// Max라면
			//				t_Att->GetPriRot()->z += pCart->GetRotVelocity() * 0.3f;
			//				if(t_Att->GetPriRot()->z >= D3DX_PI/12) t_Att->SetAngleState(false);
			//				break;
			//			case false:
			//				// Min라면
			//				t_Att->GetPriRot()->z -= pCart->GetRotVelocity() * 0.3f;
			//				if(t_Att->GetPriRot()->z <= -D3DX_PI/12) t_Att->SetAngleState(true);
			//				break;
			//		}
			//	}
			//	break;
			case CCart::PUPIL:
				t_Att->GetPriRot()->z += pCart->GetRotVelocity() * 15.0f;
				break;
			case CCart::WHEELLEFT:
				if(::GetAsyncKeyState(VK_LEFT) & 0xffff8000)
					t_Att->GetPriRot()->z -= pCart->GetRotVelocity() * 20.0f;
				if(::GetAsyncKeyState(VK_RIGHT) & 0xffff8000)
					t_Att->GetPriRot()->z -= pCart->GetRotVelocity() * 20.0f;
				break;
			case CCart::WHEELRIGHT:
				if(::GetAsyncKeyState(VK_LEFT) & 0xffff8000)
					t_Att->GetPriRot()->z -= pCart->GetRotVelocity() * 45.0f;
				if(::GetAsyncKeyState(VK_RIGHT) & 0xffff8000)
					t_Att->GetPriRot()->z -= pCart->GetRotVelocity() * 45.0f;
				break;
			default:
				break;
		}
	}	

	pCart->RenderOrgan();
}

void CPulledByHero::Exit(CCart* pCart){

}

bool CPulledByHero::OnMessage(CCart* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Put:
			agent->GetFSM()->ChangeState(CartUsual->Instance());
			return true;
		case Msg_Event:
			agent->GetFSM()->ChangeState(CartEvent->Instance());
			return true;
		default:
			return false;
	}
}