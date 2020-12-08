#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CWagooUsual::Enter(CWagoo* pWagoo){
	CBody* t_pBody = pWagoo->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	pWagoo->SetLookEnemy(false);

	t_pBody->SetVelocity(104.5f);
}

void CWagooUsual::Execute(CWagoo* pWagoo){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pWagoo->GetBody();

	pWagoo->CheckHealthState();
	pWagoo->EntityMove();

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.25f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}

		//이동범위 체크
		if(t_pHeroBody->GetPriPos()->x - AIMgr->GetMoveRange()->_max.x > t_pBody->GetPriPos()->x)
			t_pBody->SetRow(CBaseObject::RIGHT);
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.25f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	
		// 이동범위 체크
		if(t_pHeroBody->GetPriPos()->x + AIMgr->GetMoveRange()->_max.x < t_pBody->GetPriPos()->x)
			t_pBody->SetRow(CBaseObject::LEFT);
	}
	
	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.005f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.01f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.005f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.01f)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pWagoo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWagoo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWagoo::HEAD:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.015f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.15f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.015f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWagoo::EYE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.01f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.01f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWagoo::LEFT:
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			case CWagoo::RIGHT:
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pWagoo->RenderOrgan();
}

void CWagooUsual::Exit(CWagoo* pWagoo){

}

bool CWagooUsual::OnMessage(CWagoo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Attack:
			agent->GetFSM()->ChangeState(WagooAttack->Instance());
			return true;
		case Msg_Defense:
			agent->GetFSM()->ChangeState(WagooDefense->Instance());
			return true;
		case Msg_RunAway:
			agent->GetFSM()->ChangeState(WagooRunAway->Instance());
			return true;
		case Msg_NotRender:
			agent->GetFSM()->ChangeState(WagooNotRender->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(WagooSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(WagooShock->Instance());
			return true;
		case Msg_Healthful:
			agent->SetHealthState(CCharacterEntity::HEALTHFUL);
			return true;
		case Msg_Normal:
			agent->SetHealthState(CCharacterEntity::NORMAL);
			return true;
		case Msg_Weak:
			agent->SetHealthState(CCharacterEntity::WEAK);
			return true;
		case Msg_Die:
			agent->GetFSM()->ChangeState(WagooDie->Instance());
			return true;
		case Msg_Event:
			agent->GetFSM()->ChangeState(WagooEvent->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
void CWagooEvent::Enter(CWagoo* pWagoo){
	
}

void CWagooEvent::Execute(CWagoo* pWagoo){
	CBody* t_pBody = pWagoo->GetBody();
	
	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.25f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.25f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.005f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.01f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.005f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.01f)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pWagoo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWagoo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWagoo::HEAD:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.015f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.15f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.015f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWagoo::EYE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.01f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.01f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			default:
				break;
		}
	}

	pWagoo->RenderOrgan();
}

void CWagooEvent::Exit(CWagoo* pWagoo){

}

bool CWagooEvent::OnMessage(CWagoo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(WagooUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Create State
///////////////////////////////////////////////////////////
void CWagooCreate::Enter(CWagoo* pWagoo){
	
}

void CWagooCreate::Execute(CWagoo* pWagoo){
	// 바디 계산
	CBody* t_pBody = pWagoo->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_vPos.x;
	t_pBody->GetPriPos()->y = t_vPos.y;
	t_pBody->GetPriPos()->z = 700 + t_vPos.z;

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.002f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.01f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.002f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.01f)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pWagoo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWagoo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWagoo::HEAD:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.03f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.15f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.03f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.04f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWagoo::EYE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.02f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.03f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.02f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.03f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWagoo::LEFT:
				if(::GetAsyncKeyState(VK_LEFT) & 0xffff8000)
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				if(::GetAsyncKeyState(VK_RIGHT) & 0xffff8000)
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			case CWagoo::RIGHT:
				if(::GetAsyncKeyState(VK_LEFT) & 0xffff8000)
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				if(::GetAsyncKeyState(VK_RIGHT) & 0xffff8000)
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pWagoo->RenderOrgan();
}

void CWagooCreate::Exit(CWagoo* pWagoo){

}

bool CWagooCreate::OnMessage(CWagoo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			if(AIMgr->BuffCharacterCheck())
				EffectMgr->InsertLightEffect(agent->GetBody());

			agent->GetFSM()->ChangeState(WagooUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Not Render State
///////////////////////////////////////////////////////////
void CWagooNotRender::Enter(CWagoo* pWagoo){
	
}

void CWagooNotRender::Execute(CWagoo* pWagoo){
	
}

void CWagooNotRender::Exit(CWagoo* pWagoo){

}

bool CWagooNotRender::OnMessage(CWagoo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(WagooUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Attack State
///////////////////////////////////////////////////////////
void CWagooAttack::Enter(CWagoo* pWagoo){

}

void CWagooAttack::Execute(CWagoo* pWagoo){
	CBody* t_pBody = pWagoo->GetBody();
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();

	pWagoo->EntityMove();

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.25f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
		
		// 공격범위 체크
		if(t_pHeroBody->GetPriPos()->x - AIMgr->GetAttackRange()->_max.x > t_pBody->GetPriPos()->x)
			pWagoo->GetFSM()->ChangeState(WagooUsual->Instance());
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.25f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	
		// 공격범위 체크
		if(t_pHeroBody->GetPriPos()->x + AIMgr->GetAttackRange()->_max.x < t_pBody->GetPriPos()->x)
			pWagoo->GetFSM()->ChangeState(WagooUsual->Instance());
	}

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.002f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.01f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.002f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.01f)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pWagoo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWagoo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWagoo::HEAD:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.03f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.15f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.04f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f){
							t_Att->SetAngleState(true);
							if(pWagoo->EntityAttackToEnemy()){
								pWagoo->SetLookEnemy(true);
							}
						}
						break;
				}
				break;
			case CWagoo::EYE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.02f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.03f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.02f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.03f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWagoo::LEFT:
				if(::GetAsyncKeyState(VK_LEFT) & 0xffff8000)
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				if(::GetAsyncKeyState(VK_RIGHT) & 0xffff8000)
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			case CWagoo::RIGHT:
				if(::GetAsyncKeyState(VK_LEFT) & 0xffff8000)
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				if(::GetAsyncKeyState(VK_RIGHT) & 0xffff8000)
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pWagoo->RenderOrgan();
}

void CWagooAttack::Exit(CWagoo* pWagoo){

}

bool CWagooAttack::OnMessage(CWagoo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(WagooUsual->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(WagooSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(WagooShock->Instance());
			return true;
		case Msg_Die:
			agent->GetFSM()->ChangeState(WagooDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Defense State
///////////////////////////////////////////////////////////
void CWagooDefense::Enter(CWagoo* pWagoo){
	CBody* t_pBody = pWagoo->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	pWagoo->SetLookEnemy(false);

	pWagoo->SetDef(pWagoo->GetDef() * 2.0f);
}

void CWagooDefense::Execute(CWagoo* pWagoo){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pWagoo->GetBody();

	pWagoo->EntityMove();

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.25f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}

		//이동범위 체크
		if(t_pHeroBody->GetPriPos()->x - AIMgr->GetMoveRange()->_max.x > t_pBody->GetPriPos()->x)
			t_pBody->SetRow(CBaseObject::RIGHT);
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.25f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	
		// 이동범위 체크
		if(t_pHeroBody->GetPriPos()->x + AIMgr->GetMoveRange()->_max.x < t_pBody->GetPriPos()->x)
			t_pBody->SetRow(CBaseObject::LEFT);
	}
	
	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.005f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.01f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.005f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.01f)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pWagoo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWagoo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWagoo::HEAD:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.015f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.15f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.015f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWagoo::EYE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.01f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.01f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWagoo::LEFT:
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			case CWagoo::RIGHT:
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pWagoo->RenderOrgan();
}

void CWagooDefense::Exit(CWagoo* pWagoo){
	pWagoo->SetDef(pWagoo->GetDef() * 0.5f);
}

bool CWagooDefense::OnMessage(CWagoo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(WagooUsual->Instance());
			return true;
		case Msg_Attack:
			agent->GetFSM()->ChangeState(WagooAttack->Instance());
			return true;
		case Msg_NotRender:
			agent->GetFSM()->ChangeState(WagooNotRender->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(WagooSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(WagooShock->Instance());
			return true;
		case Msg_Die:
			agent->GetFSM()->ChangeState(WagooDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// RunAway State
///////////////////////////////////////////////////////////
void CWagooRunAway::Enter(CWagoo* pWagoo){
	CBody* t_pBody = pWagoo->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	pWagoo->SetLookEnemy(false);

	t_pBody->SetVelocity(104.5f);

	switch(StageMgr->GetStageType()){
		case CStageManager::DUSTBRIDGE:
			t_pBody->SetRow(CBaseObject::RIGHT);
			break;
		default:
			t_pBody->SetRow(CBaseObject::LEFT);
			break;
	}
}

void CWagooRunAway::Execute(CWagoo* pWagoo){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pWagoo->GetBody();

	pWagoo->EntityMove();

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.25f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}

		//이동범위 체크
		if(t_pHeroBody->GetPriPos()->x - AIMgr->GetMoveRange()->_max.x > t_pBody->GetPriPos()->x)
			t_pBody->SetRow(CBaseObject::RIGHT);
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.25f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	
		// 이동범위 체크
		if(t_pHeroBody->GetPriPos()->x + AIMgr->GetMoveRange()->_max.x < t_pBody->GetPriPos()->x)
			t_pBody->SetRow(CBaseObject::LEFT);
	}
	
	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.005f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.01f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.005f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.01f)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pWagoo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWagoo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWagoo::HEAD:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.015f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.15f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.015f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWagoo::EYE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.01f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.01f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWagoo::LEFT:
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			case CWagoo::RIGHT:
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pWagoo->RenderOrgan();
}

void CWagooRunAway::Exit(CWagoo* pWagoo){
	
}

bool CWagooRunAway::OnMessage(CWagoo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(WagooUsual->Instance());
			return true;
		case Msg_Defense:
			agent->GetFSM()->ChangeState(WagooDefense->Instance());
			return true;
		case Msg_Attack:
			agent->GetFSM()->ChangeState(WagooAttack->Instance());
			return true;
		case Msg_NotRender:
			agent->GetFSM()->ChangeState(WagooNotRender->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(WagooSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(WagooShock->Instance());
			return true;
		case Msg_Die:
			agent->GetFSM()->ChangeState(WagooDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Shock State
///////////////////////////////////////////////////////////
void CWagooShock::Enter(CWagoo* pWagoo){
	_shockTime = new CTimer(3000);
	EffectMgr->InsertDiggyEffect(pWagoo->GetBody(), 3000);

	pWagoo->GetBody()->SetVelocity(0.0f);
}

void CWagooShock::Execute(CWagoo* pWagoo){
	CBody* t_pBody = pWagoo->GetBody();

	pWagoo->EntityMove();

	pWagoo->RenderOrgan();

	if(_shockTime->IsElapseTimer())
		pWagoo->GetFSM()->ChangeState(WagooUsual->Instance());
}

void CWagooShock::Exit(CWagoo* pWagoo){
    
}

bool CWagooShock::OnMessage(CWagoo* agent, const Telegram& msg){
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
void CWagooSpringUp::Enter(CWagoo* pWagoo){
	CBody* t_pBody = pWagoo->GetBody();

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
}

void CWagooSpringUp::Execute(CWagoo* pWagoo){
	CBody* t_pBody = pWagoo->GetBody();

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
				pWagoo->GetFSM()->ChangeState(WagooShock->Instance());
				break;
		}
	}

	pWagoo->RenderOrgan();
}

void CWagooSpringUp::Exit(CWagoo* pWagoo){
    
}

bool CWagooSpringUp::OnMessage(CWagoo* agent, const Telegram& msg){
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
// Die State
///////////////////////////////////////////////////////////
void CWagooDie::Enter(CWagoo* pWagoo){
	CBody* t_pBody = pWagoo->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	pWagoo->SetLookEnemy(false);

	t_pBody->SetVelocity(0.0f);
}

void CWagooDie::Execute(CWagoo* pWagoo){
	CBody* t_pBody = pWagoo->GetBody();

	// 부속품 계산
	for(int i = 0; i < pWagoo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWagoo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWagoo::HEAD:			
				if(t_Att->GetPriRot()->z > -D3DX_PI * 0.1)
					t_Att->GetPriRot()->z -= 0.015f;
				break;
			case CWagoo::EYE:				
				if(t_Att->GetPriRot()->z > -D3DX_PI * 0.1)
					t_Att->GetPriRot()->z -= 0.015f;
				break;
			default:
				break;
		}
	}

	pWagoo->RenderOrgan();
}

void CWagooDie::Exit(CWagoo* pWagoo){

}

bool CWagooDie::OnMessage(CWagoo* agent, const Telegram& msg){
	return false;
}