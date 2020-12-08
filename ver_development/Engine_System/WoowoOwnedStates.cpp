#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CWoowoUsual::Enter(CWoowo* pWoowo){
	CBody* t_pBody = pWoowo->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	pWoowo->SetLookEnemy(false);
}

void CWoowoUsual::Execute(CWoowo* pWoowo){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pWoowo->GetBody();

	pWoowo->CheckHealthState();
	pWoowo->EntityMove();

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
			t_pBody->GetPriRot()->z += 0.001f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.01f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.001f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.01f)
				t_pBody->SetAngleState(true);
			break;
	}

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){							
		//이동범위 체크
		if(t_pHeroBody->GetPriPos()->x - AIMgr->GetMoveRange()->_max.x > t_pBody->GetPriPos()->x)
			t_pBody->SetRow(CBaseObject::RIGHT);
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		// 이동범위 체크
		if(t_pHeroBody->GetPriPos()->x + AIMgr->GetMoveRange()->_max.x < t_pBody->GetPriPos()->x)
			t_pBody->SetRow(CBaseObject::LEFT);
	}

	// 부속품 계산
	for(int i = 0; i < pWoowo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWoowo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWoowo::LEFT:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.01f;
						t_pBody->GetPriRot()->z -= 0.01f;	
						t_pBody->SetVelocity(47.5f);
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.01f;
						t_pBody->GetPriRot()->z += 0.01f;
						t_pBody->SetVelocity(0.0f);
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWoowo::EYE:				
				
				break;
			case CWoowo::BODY:
				
				break;
			case CWoowo::RIGHT:
				switch(t_Att->GetAngleState()){
					case false:
						// Max라면
						t_Att->GetPriRot()->z += 0.012f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.12f)
							t_Att->SetAngleState(true);
						break;
					case true:
						// Min라면
						t_Att->GetPriRot()->z -= 0.012f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.12f)
							t_Att->SetAngleState(false);

						if(t_Att->GetPriRot()->z > -D3DX_PI * 0.06f && t_Att->GetPriRot()->z <= 0.0f)
							t_pBody->GetPriPos()->y += 0.2f;
						else if(t_Att->GetPriRot()->z > -D3DX_PI * 0.12f && t_Att->GetPriRot()->z <= -D3DX_PI * 0.06f)
							t_pBody->GetPriPos()->y -= 0.2f;
						break;
				}
				break;
			default:
				break;
		}
	}

	pWoowo->RenderOrgan();
}

void CWoowoUsual::Exit(CWoowo* pWoowo){

}

bool CWoowoUsual::OnMessage(CWoowo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Attack:
			if(agent->GetAttackTime()->IsElapseTimer()){
				agent->GetFSM()->ChangeState(WoowoAttack->Instance());
				agent->SetAttackTime(agent->GetAttackTimeGap());
				return true;
			}
			else{
				agent->SetLookEnemy(false);
			}
			return false;
		case Msg_Defense:
			agent->GetFSM()->ChangeState(WoowoDefense->Instance());
			return true;
		case Msg_RunAway:
			agent->GetFSM()->ChangeState(WoowoRunAway->Instance());
			return true;
		case Msg_NotRender:
			agent->GetFSM()->ChangeState(WoowoNotRender->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(WoowoSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(WoowoShock->Instance());
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
			agent->GetFSM()->ChangeState(WoowoDie->Instance());
			return true;
		case Msg_Event:
			agent->GetFSM()->ChangeState(WoowoEvent->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
void CWoowoEvent::Enter(CWoowo* pWoowo){
	
}

void CWoowoEvent::Execute(CWoowo* pWoowo){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pWoowo->GetBody();

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
			t_pBody->GetPriRot()->z += 0.001f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.01f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.001f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.01f)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pWoowo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWoowo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWoowo::LEFT:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.01f;
						t_pBody->GetPriRot()->z -= 0.01f;	
						t_pBody->SetVelocity(47.5f);
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.01f;
						t_pBody->GetPriRot()->z += 0.01f;
						t_pBody->SetVelocity(0.0f);
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWoowo::EYE:				
				
				break;
			case CWoowo::BODY:
				
				break;
			case CWoowo::RIGHT:
				switch(t_Att->GetAngleState()){
					case false:
						// Max라면
						t_Att->GetPriRot()->z += 0.012f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.12f)
							t_Att->SetAngleState(true);
						break;
					case true:
						// Min라면
						t_Att->GetPriRot()->z -= 0.012f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.12f)
							t_Att->SetAngleState(false);

						if(t_Att->GetPriRot()->z > -D3DX_PI * 0.06f && t_Att->GetPriRot()->z <= 0.0f)
							t_pBody->GetPriPos()->y += 0.2f;
						else if(t_Att->GetPriRot()->z > -D3DX_PI * 0.12f && t_Att->GetPriRot()->z <= -D3DX_PI * 0.06f)
							t_pBody->GetPriPos()->y -= 0.2f;
						break;
				}
				break;
			default:
				break;
		}
	}

	pWoowo->RenderOrgan();
}

void CWoowoEvent::Exit(CWoowo* pWoowo){

}

bool CWoowoEvent::OnMessage(CWoowo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(WoowoUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Create State
///////////////////////////////////////////////////////////
void CWoowoCreate::Enter(CWoowo* pWoowo){
	
}

void CWoowoCreate::Execute(CWoowo* pWoowo){
	// 바디 계산
	CBody* t_pBody = pWoowo->GetBody();

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
	for(int i = 0; i < pWoowo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWoowo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWoowo::LEFT:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.01f;
						t_pBody->GetPriRot()->z -= 0.01f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.01f;
						t_pBody->GetPriRot()->z += 0.01f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWoowo::EYE:				
				
				break;
			case CWoowo::BODY:
				
				break;
			case CWoowo::RIGHT:
				switch(t_Att->GetAngleState()){
					case false:
						// Max라면
						t_Att->GetPriRot()->z += 0.01f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
					case true:
						// Min라면
						t_Att->GetPriRot()->z -= 0.01f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
				}
			default:
				break;
		}
	}

	pWoowo->RenderOrgan();
}

void CWoowoCreate::Exit(CWoowo* pWoowo){

}

bool CWoowoCreate::OnMessage(CWoowo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			if(AIMgr->BuffCharacterCheck())
				EffectMgr->InsertLightEffect(agent->GetBody());

			agent->GetFSM()->ChangeState(WoowoUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Not Render State
///////////////////////////////////////////////////////////
void CWoowoNotRender::Enter(CWoowo* pWoowo){
	
}

void CWoowoNotRender::Execute(CWoowo* pWoowo){
	
}

void CWoowoNotRender::Exit(CWoowo* pWoowo){

}

bool CWoowoNotRender::OnMessage(CWoowo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(WoowoUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Attack State
///////////////////////////////////////////////////////////
void CWoowoAttack::Enter(CWoowo* pWoowo){
	
}

void CWoowoAttack::Execute(CWoowo* pWoowo){
	CBody* t_pBody = pWoowo->GetBody();
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();

	pWoowo->EntityMove();

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.25f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}

		// 공격범위 체크
		if(t_pHeroBody->GetPriPos()->x - AIMgr->GetAttackRange()->_max.x > t_pBody->GetPriPos()->x)
			pWoowo->GetFSM()->ChangeState(WoowoUsual->Instance());
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.25f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}

		// 공격범위 체크
		if(t_pHeroBody->GetPriPos()->x + AIMgr->GetAttackRange()->_max.x < t_pBody->GetPriPos()->x)
			pWoowo->GetFSM()->ChangeState(WoowoUsual->Instance());
	}

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.004f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.02f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.004f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.02f)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pWoowo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWoowo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWoowo::LEFT:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.04f;
						t_pBody->GetPriRot()->z -= 0.04f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.2f){							
							t_Att->SetAngleState(false);
						}
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.04f;
						t_pBody->GetPriRot()->z += 0.04f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.2f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWoowo::EYE:				
				
				break;
			case CWoowo::BODY:
				
				break;
			case CWoowo::RIGHT:
				switch(t_Att->GetAngleState()){
					case false:
						// Max라면
						t_Att->GetPriRot()->z += 0.04f;

						pWoowo->GetBody()->SetVelocity(0.0f);

						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.2f)
							t_Att->SetAngleState(true);
						break;
					case true:
						// Min라면
						t_Att->GetPriRot()->z -= 0.04f;

						pWoowo->GetBody()->SetVelocity(125.0f);

						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.2f){
							if(pWoowo->EntityAttackToEnemy()){
								pWoowo->GetFSM()->ChangeState(WoowoAttackAfter->Instance());
							}
							t_Att->SetAngleState(false);
						}

						if(t_Att->GetPriRot()->z > -D3DX_PI * 0.1f && t_Att->GetPriRot()->z <= 0.0f)
							t_pBody->GetPriPos()->y += 1.0f;
						else if(t_Att->GetPriRot()->z > -D3DX_PI * 0.2f && t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_pBody->GetPriPos()->y -= 1.0f;
						break;
				}
				break;
			default:
				break;
		}
	}

	pWoowo->RenderOrgan();
}

void CWoowoAttack::Exit(CWoowo* pWoowo){

}

bool CWoowoAttack::OnMessage(CWoowo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(WoowoUsual->Instance());
			return true;
		case Msg_Defense:
			agent->GetFSM()->ChangeState(WoowoDefense->Instance());
			return true;
		case Msg_RunAway:
			agent->GetFSM()->ChangeState(WoowoRunAway->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(WoowoSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(WoowoShock->Instance());
			return true;
		case Msg_Die:
			agent->GetFSM()->ChangeState(WoowoDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Defense State
///////////////////////////////////////////////////////////
void CWoowoDefense::Enter(CWoowo* pWoowo){
	CBody* t_pBody = pWoowo->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	pWoowo->SetLookEnemy(false);

	pWoowo->SetDef(pWoowo->GetDef() * 2.0f);
}

void CWoowoDefense::Execute(CWoowo* pWoowo){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pWoowo->GetBody();

	pWoowo->EntityMove();

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
			t_pBody->GetPriRot()->z += 0.001f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.01f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.001f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.01f)
				t_pBody->SetAngleState(true);
			break;
	}

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){							
		//이동범위 체크
		if(t_pHeroBody->GetPriPos()->x - AIMgr->GetMoveRange()->_max.x > t_pBody->GetPriPos()->x)
			t_pBody->SetRow(CBaseObject::RIGHT);
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		// 이동범위 체크
		if(t_pHeroBody->GetPriPos()->x + AIMgr->GetMoveRange()->_max.x < t_pBody->GetPriPos()->x)
			t_pBody->SetRow(CBaseObject::LEFT);
	}

	// 부속품 계산
	for(int i = 0; i < pWoowo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWoowo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWoowo::LEFT:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.01f;
						t_pBody->GetPriRot()->z -= 0.01f;	
						t_pBody->SetVelocity(47.5f);
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.01f;
						t_pBody->GetPriRot()->z += 0.01f;
						t_pBody->SetVelocity(0.0f);
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWoowo::EYE:				
				
				break;
			case CWoowo::BODY:
				
				break;
			case CWoowo::RIGHT:
				switch(t_Att->GetAngleState()){
					case false:
						// Max라면
						t_Att->GetPriRot()->z += 0.012f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.12f)
							t_Att->SetAngleState(true);
						break;
					case true:
						// Min라면
						t_Att->GetPriRot()->z -= 0.012f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.12f)
							t_Att->SetAngleState(false);

						if(t_Att->GetPriRot()->z > -D3DX_PI * 0.06f && t_Att->GetPriRot()->z <= 0.0f)
							t_pBody->GetPriPos()->y += 0.2f;
						else if(t_Att->GetPriRot()->z > -D3DX_PI * 0.12f && t_Att->GetPriRot()->z <= -D3DX_PI * 0.06f)
							t_pBody->GetPriPos()->y -= 0.2f;
						break;
				}
				break;
			default:
				break;
		}
	}

	pWoowo->RenderOrgan();
}

void CWoowoDefense::Exit(CWoowo* pWoowo){
	pWoowo->SetDef(pWoowo->GetDef() * 0.5f);
}

bool CWoowoDefense::OnMessage(CWoowo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(WoowoUsual->Instance());
			return true;
		case Msg_Attack:
			if(agent->GetAttackTime()->IsElapseTimer()){
				agent->GetFSM()->ChangeState(WoowoAttack->Instance());
				agent->SetAttackTime(agent->GetAttackTimeGap());
				return true;
			}
			else{
				agent->SetLookEnemy(false);
			}
			return false;
		case Msg_NotRender:
			agent->GetFSM()->ChangeState(WoowoNotRender->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(WoowoSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(WoowoShock->Instance());
			return true;
		case Msg_Die:
			agent->GetFSM()->ChangeState(WoowoDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// RunAway State
///////////////////////////////////////////////////////////
void CWoowoRunAway::Enter(CWoowo* pWoowo){
	CBody* t_pBody = pWoowo->GetBody();

	switch(StageMgr->GetStageType()){
		case CStageManager::DUSTBRIDGE:
			t_pBody->SetRow(CBaseObject::RIGHT);
			break;
		default:
			t_pBody->SetRow(CBaseObject::LEFT);
			break;
	}
}

void CWoowoRunAway::Execute(CWoowo* pWoowo){
	CBody* t_pBody = pWoowo->GetBody();
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();

	pWoowo->EntityMove();

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.25f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}

		// 공격범위 체크
		if(t_pHeroBody->GetPriPos()->x - AIMgr->GetAttackRange()->_max.x > t_pBody->GetPriPos()->x)
			pWoowo->GetFSM()->ChangeState(WoowoUsual->Instance());
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.25f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}

		// 공격범위 체크
		if(t_pHeroBody->GetPriPos()->x + AIMgr->GetAttackRange()->_max.x < t_pBody->GetPriPos()->x)
			pWoowo->GetFSM()->ChangeState(WoowoUsual->Instance());
	}

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.004f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.02f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.004f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.02f)
				t_pBody->SetAngleState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pWoowo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWoowo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWoowo::LEFT:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.04f;
						t_pBody->GetPriRot()->z -= 0.04f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.2f){							
							t_Att->SetAngleState(false);
						}
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.04f;
						t_pBody->GetPriRot()->z += 0.04f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.2f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CWoowo::EYE:				
				
				break;
			case CWoowo::BODY:
				
				break;
			case CWoowo::RIGHT:
				switch(t_Att->GetAngleState()){
					case false:
						// Max라면
						t_Att->GetPriRot()->z += 0.04f;

						pWoowo->GetBody()->SetVelocity(0.0f);

						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.2f)
							t_Att->SetAngleState(true);
						break;
					case true:
						// Min라면
						t_Att->GetPriRot()->z -= 0.04f;

						pWoowo->GetBody()->SetVelocity(125.0f);

						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.2f){
							if(pWoowo->EntityAttackToEnemy()){
								pWoowo->GetFSM()->ChangeState(WoowoAttackAfter->Instance());
							}
							t_Att->SetAngleState(false);
						}

						if(t_Att->GetPriRot()->z > -D3DX_PI * 0.1f && t_Att->GetPriRot()->z <= 0.0f)
							t_pBody->GetPriPos()->y += 1.0f;
						else if(t_Att->GetPriRot()->z > -D3DX_PI * 0.2f && t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_pBody->GetPriPos()->y -= 1.0f;
						break;
				}
				break;
			default:
				break;
		}
	}

	pWoowo->RenderOrgan();
}

void CWoowoRunAway::Exit(CWoowo* pWoowo){

}

bool CWoowoRunAway::OnMessage(CWoowo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(WoowoUsual->Instance());
			return true;
		case Msg_Attack:
			agent->GetFSM()->ChangeState(WoowoAttack->Instance());
			return true;
		case Msg_Defense:
			agent->GetFSM()->ChangeState(WoowoDefense->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(WoowoSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(WoowoShock->Instance());
			return true;
		case Msg_Die:
			agent->GetFSM()->ChangeState(WoowoDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// AttackAfter State
///////////////////////////////////////////////////////////
void CWoowoAttackAfter::Enter(CWoowo* pWoowo){
	CBody* t_pBody = pWoowo->GetBody();

	pWoowo->SetLookEnemy(false);
}

void CWoowoAttackAfter::Execute(CWoowo* pWoowo){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pWoowo->GetBody();
	
	int t_nCount = 0;

	pWoowo->EntityMove();

	if(t_pBody->GetPriPos()->y > StageMgr->GetStageHeight() + t_pBody->GetHeightHalf() + 0.5f)
		t_pBody->GetPriPos()->y -= 0.05f;
	else if(t_pBody->GetPriPos()->y < StageMgr->GetStageHeight() + t_pBody->GetHeightHalf() - 0.5f)
		t_pBody->GetPriPos()->y += 0.05f;
	else
		t_nCount++;

	if(t_pBody->GetPriRot()->z > 0.01f)
		t_pBody->GetPriRot()->z -= 0.01f;
	else if(t_pBody->GetPriRot()->z < -0.01f)
		t_pBody->GetPriRot()->z += 0.01f;
	else{
		t_pBody->SetAngleState(true);
		t_pBody->GetPriRot()->z = 0.0f;
		t_nCount++;
	}

	// 부속품 계산
	for(int i = 0; i < pWoowo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWoowo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWoowo::LEFT:			
				if(t_Att->GetPriRot()->z > 0.01f)
					t_Att->GetPriRot()->z -= 0.01f;
				else if(t_Att->GetPriRot()->z < -0.01f)
					t_Att->GetPriRot()->z += 0.01f;
				else{
					t_Att->GetPriRot()->z = 0.0f;
					t_nCount++;
					t_Att->SetAngleState(true);
				}
				break;
			case CWoowo::EYE:

				break;
			case CWoowo::BODY:
				
				break;
			case CWoowo::RIGHT:
				if(t_Att->GetPriRot()->z > 0.01f)
					t_Att->GetPriRot()->z -= 0.01f;
				else if(t_Att->GetPriRot()->z < -0.01f)
					t_Att->GetPriRot()->z += 0.01f;
				else{
					t_Att->GetPriRot()->z = 0.0f;
					t_nCount++;
					t_Att->SetAngleState(true);
				}
				break;
			default:
				break;
		}
	}

	if(t_nCount == 4)
		pWoowo->GetFSM()->ChangeState(WoowoUsual->Instance());

	pWoowo->RenderOrgan();
}

void CWoowoAttackAfter::Exit(CWoowo* pWoowo){

}

bool CWoowoAttackAfter::OnMessage(CWoowo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(WoowoSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(WoowoShock->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Shock State
///////////////////////////////////////////////////////////
void CWoowoShock::Enter(CWoowo* pWoowo){
	_shockTime = new CTimer(3000);
	EffectMgr->InsertDiggyEffect(pWoowo->GetBody(), 3000);

	pWoowo->GetBody()->SetVelocity(0.0f);
}

void CWoowoShock::Execute(CWoowo* pWoowo){
	CBody* t_pBody = pWoowo->GetBody();
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();

	pWoowo->EntityMove();

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.25f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
		// 공격범위 체크
		if(t_pHeroBody->GetPriPos()->x - AIMgr->GetAttackRange()->_max.x > t_pBody->GetPriPos()->x)
			pWoowo->GetFSM()->ChangeState(WoowoShock->Instance());
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.25f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
		// 공격범위 체크
		if(t_pHeroBody->GetPriPos()->x + AIMgr->GetAttackRange()->_max.x < t_pBody->GetPriPos()->x)
			pWoowo->GetFSM()->ChangeState(WoowoUsual->Instance());
	}

	pWoowo->RenderOrgan();

	if(_shockTime->IsElapseTimer())
		pWoowo->GetFSM()->ChangeState(WoowoUsual->Instance());
}

void CWoowoShock::Exit(CWoowo* pWoowo){
    
}

bool CWoowoShock::OnMessage(CWoowo* agent, const Telegram& msg){
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
void CWoowoSpringUp::Enter(CWoowo* pWoowo){
	CBody* t_pBody = pWoowo->GetBody();

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

void CWoowoSpringUp::Execute(CWoowo* pWoowo){
	CBody* t_pBody = pWoowo->GetBody();
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	
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
				pWoowo->GetFSM()->ChangeState(WoowoShock->Instance());
				break;
		}
	}

	pWoowo->RenderOrgan();
}

void CWoowoSpringUp::Exit(CWoowo* pWoowo){
    
}

bool CWoowoSpringUp::OnMessage(CWoowo* agent, const Telegram& msg){
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
void CWoowoDie::Enter(CWoowo* pWoowo){
	CBody* t_pBody = pWoowo->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	pWoowo->SetLookEnemy(false);
}

void CWoowoDie::Execute(CWoowo* pWoowo){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pWoowo->GetBody();

	if(t_pBody->GetPriPos()->y - t_pBody->GetHeightHalf() * 0.5f > StageMgr->GetStageHeight())
		t_pBody->GetPriPos()->y -= 0.6f;

	// 부속품 계산
	for(int i = 0; i < pWoowo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWoowo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWoowo::LEFT:			
				if(t_Att->GetPriRot()->z > -D3DX_PI*0.5f)
					t_Att->GetPriRot()->z -= 0.02f;
				break;
			case CWoowo::EYE:				
				if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.0f)
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.02f;
				break;
			case CWoowo::BODY:
				
				break;
			case CWoowo::RIGHT:
				if(t_Att->GetPriRot()->z < D3DX_PI*0.5f)
					t_Att->GetPriRot()->z += 0.02f;
				break;
			default:
				break;
		}
	}

	pWoowo->RenderOrgan();
}

void CWoowoDie::Exit(CWoowo* pWoowo){

}

bool CWoowoDie::OnMessage(CWoowo* agent, const Telegram& msg){
	return false;
}