#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Stand State
///////////////////////////////////////////////////////////
void CHeroStand::Enter(CHero* pHero){
	pHero->GetBody()->SetVelocity(72.0f);
}

void CHeroStand::Execute(CHero* pHero){
	// 바디 계산
	CBody* t_pBody = pHero->GetBody();

	pHero->CheckHealthState();

	pHero->EntityMove();

	if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f){
		t_pBody->SetRow(CBaseObject::LEFT);

		pHero->SetCanMove(true);
		
		if(StageMgr->GetStageType() == CStageManager::HOME){
			if(t_pBody->GetPriPos()->x < -350.0f){
				pHero->SetForce(t_pBody->GetVelocity());
				pHero->SetCanMove(false);
			}
		}
		else{
			pHero->SetCanMove(true);
		}
	}
	else if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f){		
		t_pBody->SetRow(CBaseObject::RIGHT);

		pHero->SetCanMove(true);
	}
	else{
		pHero->SetCanMove(false);
	}

	if(t_pBody->GetPriPos()->x < -350.0f){
		pHero->SetForce(0.0f);
	}

	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.05f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.05f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += pHero->GetBodyRotVelocity();
			if(t_pBody->GetPriRot()->z >= D3DX_PI/50)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= pHero->GetBodyRotVelocity();
			if(t_pBody->GetPriRot()->z <= -D3DX_PI/50)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속물 계산
	for(int i = 0; i < pHero->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pHero->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CHero::ARM:
				if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f ||  ::GetAsyncKeyState(VK_RIGHT) & 0x8000f){					
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += pHero->GetArmRotVelocity();
							if(t_Att->GetPriRot()->z >= D3DX_PI/3)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= pHero->GetArmRotVelocity();
							if(t_Att->GetPriRot()->z <= -D3DX_PI/3)
								t_Att->SetAngleState(true);
							break;
					}
				}
				break;
			case CHero::PUPIL:
				t_Att->GetPriRot()->z += pHero->GetPupilRotVelocity();
				break;
			default:
				break;
		}
	}	

	pHero->RenderOrgan();

	AIMgr->OrderToAI();
	AIMgr->AIIsLive();
}

void CHeroStand::Exit(CHero* pHero){

}

bool CHeroStand::OnMessage(CHero* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Event:
			agent->GetFSM()->ChangeState(HeroEvent->Instance());
			return true;
		case Msg_Pull:
			agent->GetFSM()->ChangeState(PullToCart->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(HeroSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(HeroShock->Instance());
			return true;
		case Msg_Die:
			EventMgr->GetEventStage()->GetFSM()->ChangeState(EventStageRunAway->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
void CHeroEvent::Enter(CHero* pHero){
	
}

void CHeroEvent::Execute(CHero* pHero){
	// 바디 계산
	CBody* t_pBody = pHero->GetBody();

	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.05f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.05f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += pHero->GetBodyRotVelocity();
			if(t_pBody->GetPriRot()->z >= D3DX_PI/50)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= pHero->GetBodyRotVelocity();
			if(t_pBody->GetPriRot()->z <= -D3DX_PI/50)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속물 계산
	for(int i = 0; i < pHero->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pHero->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CHero::PUPIL:
				t_Att->GetPriRot()->z += pHero->GetPupilRotVelocity();
			case CHero::ARM:
				if(t_pBody->GetVelocity() != 0.0f){					
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += pHero->GetArmRotVelocity();
							if(t_Att->GetPriRot()->z >= D3DX_PI/3)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= pHero->GetArmRotVelocity();
							if(t_Att->GetPriRot()->z <= -D3DX_PI/3)
								t_Att->SetAngleState(true);
							break;
					}
				}
				break;
			default:
				break;
		}
	}	

	pHero->RenderOrgan();
}

void CHeroEvent::Exit(CHero* pHero){

}

bool CHeroEvent::OnMessage(CHero* agent, const Telegram& msg){
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
			agent->GetFSM()->ChangeState(HeroStand->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Pull To Cart State
///////////////////////////////////////////////////////////
void CPullToCart::Enter(CHero* pHero){
	pHero->GetBody()->SetVelocity(52.0f);
}

void CPullToCart::Execute(CHero* pHero){
	// 각종 계산
	CBody* t_pBody = pHero->GetBody();

	pHero->CheckHealthState();

	if(StageMgr->GetStageType() == CStageManager::HOME)
		if(t_pBody->GetPriPos()->x <= 80.0f){
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pHero->ID(), ID_HERO, Msg_Usual, NO_ADDITIONAL_INFO);
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pHero->ID(), ID_CART, Msg_Put, NO_ADDITIONAL_INFO);
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pHero->ID(), ID_FLOWER, Msg_Put, NO_ADDITIONAL_INFO);
		}

	pHero->EntityMove();

	if( ::GetAsyncKeyState(VK_LEFT) & 0x8000f){
		t_pBody->SetRow(CBaseObject::LEFT);
		pHero->SetCanMove(true);
		//t_pBody->GetPriPos()->x -= t_pBody->GetVelocity();
	}
	else if( ::GetAsyncKeyState(VK_RIGHT) & 0x8000f){		
		pHero->SetCanMove(true);
			t_pBody->SetRow(CBaseObject::RIGHT);
		//t_pBody->GetPriPos()->x += t_pBody->GetVelocity();
	}
	else
		pHero->SetCanMove(false);

	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.05f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.05f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += pHero->GetBodyRotVelocity();
			if(t_pBody->GetPriRot()->z >= D3DX_PI/50)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= pHero->GetBodyRotVelocity();
			if(t_pBody->GetPriRot()->z <= -D3DX_PI/50)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속물 계산
	for(int i = 0; i < pHero->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pHero->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CHero::ARM:
				t_Att->GetPriRot()->z = D3DX_PI * -0.35f;
				break;
			case CHero::PUPIL:
				t_Att->GetPriRot()->z += pHero->GetPupilRotVelocity();
				break;
			default:
				break;
		}
	}	

	pHero->RenderOrgan();

	AIMgr->OrderToAI();
	AIMgr->AIIsLive();
}

void CPullToCart::Exit(CHero* pHero){

}

bool CPullToCart::OnMessage(CHero* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(HeroStand->Instance());
			return true;
		case Msg_Pull:
			agent->GetFSM()->ChangeState(PullToCart->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(HeroSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(HeroShock->Instance());
			return true;
		case Msg_Event:
			agent->GetFSM()->ChangeState(HeroEvent->Instance());
			return true;
		case Msg_Die:
			EventMgr->GetEventStage()->GetFSM()->ChangeState(EventStageRunAway->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Shock State
///////////////////////////////////////////////////////////
void CHeroShock::Enter(CHero* pHero){
	_shockTime = new CTimer(3000);
	EffectMgr->InsertDiggyEffect(pHero->GetBody(), 3000);
}

void CHeroShock::Execute(CHero* pHero){
	CBody* t_pBody = pHero->GetBody();

	pHero->RenderOrgan();

	if(_shockTime->IsElapseTimer()){
		pHero->GetFSM()->ChangeState(HeroStand->Instance());
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pHero->ID(), ID_HERO, Msg_Usual, NO_ADDITIONAL_INFO);
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pHero->ID(), ID_CART, Msg_Put, NO_ADDITIONAL_INFO);
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pHero->ID(), ID_FLOWER, Msg_Put, NO_ADDITIONAL_INFO);
	}
}

void CHeroShock::Exit(CHero* pHero){
    
}

bool CHeroShock::OnMessage(CHero* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:

			return true;
		case Msg_Defense:

			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// SpringUp State
///////////////////////////////////////////////////////////
void CHeroSpringUp::Enter(CHero* pHero){
	CBody* t_pBody = pHero->GetBody();

	int t_nTemp = 0;
	float t_fAlpha = 0;

	t_fAlpha = (float)(rand() % 10);
	t_fAlpha *= 0.1f;

	t_nTemp = rand() % 2 + 2;

	switch(StageMgr->GetStageType()){
		case CStageManager::SCRAPMOUNTAIN:
		case CStageManager::FURNACE:
			t_pBody->SetRow(CBaseObject::RIGHT);
			break;
		default:
			t_pBody->SetRow(CBaseObject::LEFT);
			break;
	}

	if(t_pBody->GetRow() == CBaseObject::RIGHT){
		_accelarationX = -(float)t_nTemp - t_fAlpha;
	}
	else{
		_accelarationX = (float)t_nTemp + t_fAlpha;
	}

	t_fAlpha = (float)(rand() % 10);
	t_fAlpha *= 0.1f;
	t_nTemp = rand() % 4 + 3;

	_accelarationY = (float)t_nTemp + t_fAlpha;

	_boundCount = 0;

	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pHero->ID(), ID_HERO, Msg_Usual, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pHero->ID(), ID_CART, Msg_Put, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pHero->ID(), ID_FLOWER, Msg_Put, NO_ADDITIONAL_INFO);
}

void CHeroSpringUp::Execute(CHero* pHero){
	CBody* t_pBody = pHero->GetBody();

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.25f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
		_accelarationX += 0.2f;
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.25f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
		_accelarationX -= 0.2f;
	}

	_accelarationY -= 0.3f;

	t_pBody->GetPriPos()->x += _accelarationX;
	t_pBody->GetPriPos()->y += _accelarationY;

	if(t_pBody->GetPriPos()->y <= StageMgr->GetStageHeight() + t_pBody->GetHeightHalf()){
		_boundCount++;

		switch(_boundCount){
			case 1:
				_accelarationY = 2.0f;
				break;
			case 2:
				pHero->GetFSM()->ChangeState(HeroShock->Instance());
				break;
		}
	}

	pHero->RenderOrgan();
}

void CHeroSpringUp::Exit(CHero* pHero){
    
}

bool CHeroSpringUp::OnMessage(CHero* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:

			return true;
		case Msg_Defense:

			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Escape State
///////////////////////////////////////////////////////////
void CHeroEscape::Enter(CHero* pHero){
	pHero->GetBody()->SetVelocity(120.0f);
	pHero->SetLive(true);
	pHero->SetHealthy(100);
}

void CHeroEscape::Execute(CHero* pHero){
	// 각종 계산
	CBody* t_pBody = pHero->GetBody();

	pHero->EntityMove();

	switch(StageMgr->GetStageType()){
		case CStageManager::SCRAPMOUNTAIN:
		case CStageManager::FURNACE:
			t_pBody->SetRow(CBaseObject::LEFT);
			pHero->SetCanMove(true);
			break;
		default:
			pHero->SetCanMove(true);
			t_pBody->SetRow(CBaseObject::RIGHT);
			break;
	}

	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.05f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.05f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += pHero->GetBodyRotVelocity();
			if(t_pBody->GetPriRot()->z >= D3DX_PI/50)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= pHero->GetBodyRotVelocity();
			if(t_pBody->GetPriRot()->z <= -D3DX_PI/50)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속물 계산
	for(int i = 0; i < pHero->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pHero->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CHero::ARM:
				t_Att->GetPriRot()->z = D3DX_PI * -0.35f;
				break;
			case CHero::PUPIL:
				t_Att->GetPriRot()->z += pHero->GetPupilRotVelocity();
				break;
			default:
				break;
		}
	}	

	pHero->RenderOrgan();
}

void CHeroEscape::Exit(CHero* pHero){
	
}

bool CHeroEscape::OnMessage(CHero* agent, const Telegram& msg){	
	return false;
}