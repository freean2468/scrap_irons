#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CYawoUsual::Enter(CYawo* pYawo){
	CBody* t_pBody = pYawo->GetBody();

	t_pBody->SetVelocity(35.5f);
	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	pYawo->SetLookEnemy(false);
	pYawo->SetCanMove(true);
}

void CYawoUsual::Execute(CYawo* pYawo){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pYawo->GetBody();
	
	pYawo->CheckHealthState();
	pYawo->EntityMove();

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

	// 바디 계산
	// 항상 적의 반대편, 주인공의 뒤쪽에 위치.
	switch(StageMgr->GetStageType()){
		case CStageManager::CHIMNEY:
		case CStageManager::DUSTBRIDGE:
		case CStageManager::GOODHOPE:
			if(t_pBody->GetRow() == CBaseObject::LEFT){	
				//이동범위 체크
				if(t_pHeroBody->GetPriPos()->x > t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::RIGHT);
			}
			else if(t_pBody->GetRow() == CBaseObject::RIGHT){
				// 이동범위 체크
				if(t_pHeroBody->GetPriPos()->x + AIMgr->GetMoveRange()->_max.x < t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::LEFT);
			}
			break;
		default:
			if(t_pBody->GetRow() == CBaseObject::LEFT){	
				//이동범위 체크
				if(t_pHeroBody->GetPriPos()->x - AIMgr->GetMoveRange()->_max.x > t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::RIGHT);
			}
			else if(t_pBody->GetRow() == CBaseObject::RIGHT){
				// 이동범위 체크
				if(t_pHeroBody->GetPriPos()->x < t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::LEFT);
			}
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pYawo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pYawo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CYawo::HEAD:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.006f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.05f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.006f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::BODY:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.005f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.03f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.005f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.03f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGONE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.025f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.025f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGTWO:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.03f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.08f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.03f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.08f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGTHREE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.03f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.07f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.03f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.07f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGFOUR:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.029f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.08f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.031f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.08f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGFIVE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.026f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.025f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			default:
				break;
		}
	}

	pYawo->RenderOrgan();
}

void CYawoUsual::Exit(CYawo* pYawo){

}

bool CYawoUsual::OnMessage(CYawo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Attack:			
			if(agent->GetAttackTime()->IsElapseTimer()){
				agent->GetFSM()->ChangeState(YawoAttack->Instance());
				return true;
			}		
			else{
				agent->SetLookEnemy(false);
			}
			return true;
		case Msg_Defense:
			agent->GetFSM()->ChangeState(YawoDefense->Instance());
			return true;
		case Msg_RunAway:
			agent->GetFSM()->ChangeState(YawoRunAway->Instance());
			return true;
		case Msg_NotRender:
			agent->GetFSM()->ChangeState(YawoNotRender->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(YawoSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(YawoShock->Instance());
			return true;
		case Msg_Event:
			agent->GetFSM()->ChangeState(YawoEvent->Instance());
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
			agent->GetFSM()->ChangeState(YawoDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
void CYawoEvent::Enter(CYawo* pYawo){

}

void CYawoEvent::Execute(CYawo* pYawo){
	CBody* t_pBody = pYawo->GetBody();

	// 부속품 계산
	for(int i = 0; i < pYawo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pYawo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CYawo::HEAD:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.006f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.05f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.006f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::BODY:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.005f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.03f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.005f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.03f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			default:
				break;
		}
	}

	pYawo->RenderOrgan();
}

void CYawoEvent::Exit(CYawo* pYawo){

}

bool CYawoEvent::OnMessage(CYawo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(YawoUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Defense State
///////////////////////////////////////////////////////////
void CYawoDefense::Enter(CYawo* pYawo){
	CBody* t_pBody = pYawo->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	pYawo->SetLookEnemy(false);

	pYawo->SetDef(pYawo->GetDef() * 2.0f);
}

void CYawoDefense::Execute(CYawo* pYawo){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pYawo->GetBody();
	
	pYawo->EntityMove();

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

	// 바디 계산
	// 항상 적의 반대편, 주인공의 뒤쪽에 위치.
	switch(StageMgr->GetStageType()){
		case CStageManager::CHIMNEY:
		case CStageManager::DUSTBRIDGE:
		case CStageManager::GOODHOPE:
			if(t_pBody->GetRow() == CBaseObject::LEFT){	
				//이동범위 체크
				if(t_pHeroBody->GetPriPos()->x > t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::RIGHT);
			}
			else if(t_pBody->GetRow() == CBaseObject::RIGHT){
				// 이동범위 체크
				if(t_pHeroBody->GetPriPos()->x + AIMgr->GetMoveRange()->_max.x < t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::LEFT);
			}
			break;
		default:
			if(t_pBody->GetRow() == CBaseObject::LEFT){	
				//이동범위 체크
				if(t_pHeroBody->GetPriPos()->x - AIMgr->GetMoveRange()->_max.x > t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::RIGHT);
			}
			else if(t_pBody->GetRow() == CBaseObject::RIGHT){
				// 이동범위 체크
				if(t_pHeroBody->GetPriPos()->x < t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::LEFT);
			}
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pYawo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pYawo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CYawo::HEAD:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.006f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.05f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.006f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::BODY:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.005f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.03f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.005f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.03f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGONE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.025f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.025f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGTWO:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.03f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.08f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.03f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.08f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGTHREE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.03f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.07f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.03f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.07f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGFOUR:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.029f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.08f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.031f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.08f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGFIVE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.026f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.025f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			default:
				break;
		}
	}

	pYawo->RenderOrgan();
}

void CYawoDefense::Exit(CYawo* pYawo){
	pYawo->SetDef(pYawo->GetDef() * 0.5f);
}

bool CYawoDefense::OnMessage(CYawo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(YawoUsual->Instance());
			return true;
		case Msg_RunAway:
			agent->GetFSM()->ChangeState(YawoRunAway->Instance());
			return true;
		case Msg_Attack:			
			if(agent->GetAttackTime()->IsElapseTimer()){
				agent->GetFSM()->ChangeState(YawoAttack->Instance());
				return true;
			}		
			else{
				agent->SetLookEnemy(false);
			}
			return true;
		case Msg_NotRender:
			agent->GetFSM()->ChangeState(YawoNotRender->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(YawoSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(YawoShock->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// RunAway State
///////////////////////////////////////////////////////////
void CYawoRunAway::Enter(CYawo* pYawo){
	CBody* t_pBody = pYawo->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	pYawo->SetLookEnemy(false);

	t_pBody->SetVelocity(35.5f);

	switch(StageMgr->GetStageType()){
		case CStageManager::DUSTBRIDGE:
			t_pBody->SetRow(CBaseObject::RIGHT);
			break;
		default:
			t_pBody->SetRow(CBaseObject::LEFT);
			break;
	}
}

void CYawoRunAway::Execute(CYawo* pYawo){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pYawo->GetBody();
	
	pYawo->EntityMove();

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

	// 바디 계산
	// 항상 적의 반대편, 주인공의 뒤쪽에 위치.
	switch(StageMgr->GetStageType()){
		case CStageManager::CHIMNEY:
		case CStageManager::DUSTBRIDGE:
		case CStageManager::GOODHOPE:
			if(t_pBody->GetRow() == CBaseObject::LEFT){	
				//이동범위 체크
				if(t_pHeroBody->GetPriPos()->x > t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::RIGHT);
			}
			else if(t_pBody->GetRow() == CBaseObject::RIGHT){
				// 이동범위 체크
				if(t_pHeroBody->GetPriPos()->x + AIMgr->GetMoveRange()->_max.x < t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::LEFT);
			}
			break;
		default:
			if(t_pBody->GetRow() == CBaseObject::LEFT){	
				//이동범위 체크
				if(t_pHeroBody->GetPriPos()->x - AIMgr->GetMoveRange()->_max.x > t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::RIGHT);
			}
			else if(t_pBody->GetRow() == CBaseObject::RIGHT){
				// 이동범위 체크
				if(t_pHeroBody->GetPriPos()->x < t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::LEFT);
			}
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pYawo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pYawo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CYawo::HEAD:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.006f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.05f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.006f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::BODY:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.005f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.03f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.005f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.03f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGONE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.025f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.025f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGTWO:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.03f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.08f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.03f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.08f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGTHREE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.03f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.07f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.03f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.07f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGFOUR:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.029f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.08f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.031f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.08f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGFIVE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.026f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.025f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			default:
				break;
		}
	}

	pYawo->RenderOrgan();
}

void CYawoRunAway::Exit(CYawo* pYawo){
	
}

bool CYawoRunAway::OnMessage(CYawo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(YawoUsual->Instance());
			return true;
		case Msg_Defense:
			agent->GetFSM()->ChangeState(YawoDefense->Instance());
			return true;
		case Msg_Attack:			
			if(agent->GetAttackTime()->IsElapseTimer()){
				agent->GetFSM()->ChangeState(YawoAttack->Instance());
				return true;
			}		
			else{
				agent->SetLookEnemy(false);
			}
			return true;
		case Msg_NotRender:
			agent->GetFSM()->ChangeState(YawoNotRender->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(YawoSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(YawoShock->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Create State
///////////////////////////////////////////////////////////
void CYawoCreate::Enter(CYawo* pYawo){
	
}

void CYawoCreate::Execute(CYawo* pYawo){
	// 바디 계산
	CBody* t_pBody = pYawo->GetBody();

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
	for(int i = 0; i < pYawo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pYawo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CYawo::HEAD:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.006f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.05f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.006f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGONE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.015f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.015f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGTWO:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.02f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.08f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.02f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.08f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGTHREE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.022f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.07f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.022f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.07f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGFOUR:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.02f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.08f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.02f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.08f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGFIVE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.015f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.015f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			default:
				break;
		}
	}

	pYawo->RenderOrgan();
}

void CYawoCreate::Exit(CYawo* pYawo){

}

bool CYawoCreate::OnMessage(CYawo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			if(AIMgr->BuffCharacterCheck())
				EffectMgr->InsertLightEffect(agent->GetBody());

			agent->GetFSM()->ChangeState(YawoUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Not Render State
///////////////////////////////////////////////////////////
void CYawoNotRender::Enter(CYawo* pYawo){
	
}

void CYawoNotRender::Execute(CYawo* pYawo){
	
}

void CYawoNotRender::Exit(CYawo* pYawo){

}

bool CYawoNotRender::OnMessage(CYawo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(YawoUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Attack State
///////////////////////////////////////////////////////////
void CYawoAttack::Enter(CYawo* pYawo){
	
}

void CYawoAttack::Execute(CYawo* pYawo){
	CBody* t_pBody = pYawo->GetBody();
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();

	pYawo->EntityMove();

	// 부속품 계산
	for(int i = 0; i < pYawo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pYawo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CYawo::HEAD:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.006f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.05f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.006f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGONE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.015f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.015f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGTWO:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.02f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.08f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.02f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.08f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGTHREE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.022f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.07f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.022f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.07f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGFOUR:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.02f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.08f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.02f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.08f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CYawo::LEGFIVE:				
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.015f;						
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.1f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.015f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.1f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			default:
				break;
		}
	}

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.5f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}

		// 공격범위 체크
		if(t_pHeroBody->GetPriPos()->x - AIMgr->GetAttackRange()->_max.x > t_pBody->GetPriPos()->x){
			pYawo->GetFSM()->ChangeState(YawoUsual->Instance());
		}
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.5f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}

		// 공격범위 체크
		if(t_pHeroBody->GetPriPos()->x + AIMgr->GetAttackRange()->_max.x < t_pBody->GetPriPos()->x){
			pYawo->GetFSM()->ChangeState(YawoUsual->Instance());
		}
	}

	if(pYawo->GetAttackTime()->IsElapseTimer()){
		if(pYawo->EntityAttackToEnemy()){
			pYawo->SetAttackTime(pYawo->GetAttackTimeGap());
		}
	}

	// 바디 계산
	// 항상 적의 반대편, 주인공의 뒤쪽에 위치.
	switch(StageMgr->GetStageType()){
		case CStageManager::CHIMNEY:
		case CStageManager::DUSTBRIDGE:
		case CStageManager::GOODHOPE:
			if(t_pBody->GetRow() == CBaseObject::LEFT){	
				//이동범위 체크
				if(t_pHeroBody->GetPriPos()->x > t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::RIGHT);
			}
			else if(t_pBody->GetRow() == CBaseObject::RIGHT){
				// 이동범위 체크
				if(t_pHeroBody->GetPriPos()->x + AIMgr->GetMoveRange()->_max.x < t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::LEFT);
			}
			break;
		default:
			if(t_pBody->GetRow() == CBaseObject::LEFT){	
				//이동범위 체크
				if(t_pHeroBody->GetPriPos()->x - AIMgr->GetMoveRange()->_max.x > t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::RIGHT);
			}
			else if(t_pBody->GetRow() == CBaseObject::RIGHT){
				// 이동범위 체크
				if(t_pHeroBody->GetPriPos()->x < t_pBody->GetPriPos()->x)
					t_pBody->SetRow(CBaseObject::LEFT);
			}
			break;
	}

	pYawo->RenderOrgan();
}

void CYawoAttack::Exit(CYawo* pYawo){

}

bool CYawoAttack::OnMessage(CYawo* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(YawoUsual->Instance());
			return true;
		case Msg_Defense:
			agent->GetFSM()->ChangeState(YawoAttack->Instance());
			return true;
		case Msg_RunAway:
			agent->GetFSM()->ChangeState(YawoRunAway->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(YawoSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(YawoShock->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Shock State
///////////////////////////////////////////////////////////
void CYawoShock::Enter(CYawo* pYawo){
	_shockTime = new CTimer(3000);
	EffectMgr->InsertDiggyEffect(pYawo->GetBody(), 3000);
	pYawo->GetBody()->SetVelocity(0.0f);
}

void CYawoShock::Execute(CYawo* pYawo){
	CBody* t_pBody = pYawo->GetBody();

	pYawo->EntityMove();
	pYawo->RenderOrgan();

	if(_shockTime->IsElapseTimer())
		pYawo->GetFSM()->ChangeState(YawoUsual->Instance());
}

void CYawoShock::Exit(CYawo* pYawo){
    
}

bool CYawoShock::OnMessage(CYawo* agent, const Telegram& msg){
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
void CYawoSpringUp::Enter(CYawo* pYawo){
	CBody* t_pBody = pYawo->GetBody();

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

void CYawoSpringUp::Execute(CYawo* pYawo){
	CBody* t_pBody = pYawo->GetBody();

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
				pYawo->GetFSM()->ChangeState(YawoShock->Instance());
				break;
		}
	}

	pYawo->RenderOrgan();
}

void CYawoSpringUp::Exit(CYawo* pYawo){
    
}

bool CYawoSpringUp::OnMessage(CYawo* agent, const Telegram& msg){
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
void CYawoDie::Enter(CYawo* pYawo){
	CBody* t_pBody = pYawo->GetBody();

	t_pBody->SetVelocity(0.0f);
	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
}

void CYawoDie::Execute(CYawo* pYawo){
	CBody* t_pBody = pYawo->GetBody();

	// 부속품 계산
	for(int i = 0; i < pYawo->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pYawo->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CYawo::HEAD:			
				if(t_Att->GetPriPos()->y + t_Att->GetHeightHalf() * 0.5f > StageMgr->GetStageHeight())
					t_Att->GetPriPos()->y -= 0.6f;

				if(t_Att->GetPriRot()->z < D3DX_PI * 0.7f)
					t_Att->GetPriRot()->z += 0.05f;
				break;
			case CYawo::BODY:
				if(t_Att->GetPriPos()->y + t_Att->GetHeightHalf() * 0.5f > StageMgr->GetStageHeight())
					t_Att->GetPriPos()->y -= 0.6f;

				if(t_Att->GetPriPos()->y > StageMgr->GetStageHeight())
					t_Att->GetPriPos()->y -= 0.2f;
				break;
			case CYawo::LEGONE:				
				if(t_Att->GetPriPos()->y > StageMgr->GetStageHeight())
					t_Att->GetPriPos()->y -= 0.2f;
				
				if(t_Att->GetPriRot()->z < D3DX_PI * 0.7f)
					t_Att->GetPriRot()->z += 0.05f;
				break;
			case CYawo::LEGTWO:	
				if(t_Att->GetPriPos()->y > StageMgr->GetStageHeight())
					t_Att->GetPriPos()->y -= 0.2f;
				
				if(t_Att->GetPriRot()->z < -D3DX_PI * 0.7f)
					t_Att->GetPriRot()->z -= 0.05f;
				break;
			case CYawo::LEGTHREE:	
				if(t_Att->GetPriPos()->y > StageMgr->GetStageHeight())
					t_Att->GetPriPos()->y -= 0.2f;
				
				if(t_Att->GetPriRot()->z < D3DX_PI * 0.5f)
					t_Att->GetPriRot()->z += 0.045f;
				break;
			case CYawo::LEGFOUR:		
				if(t_Att->GetPriPos()->y > StageMgr->GetStageHeight())
					t_Att->GetPriPos()->y -= 0.2f;
				
				if(t_Att->GetPriRot()->z > -D3DX_PI * 0.7f)
					t_Att->GetPriRot()->z -= 0.06f;
				break;
			case CYawo::LEGFIVE:	
				if(t_Att->GetPriPos()->y > StageMgr->GetStageHeight())
					t_Att->GetPriPos()->y -= 0.2f;
				
				if(t_Att->GetPriRot()->z < D3DX_PI * 0.8f)
					t_Att->GetPriRot()->z += 0.055f;
				break;
			default:
				break;
		}
	}

	pYawo->RenderOrgan();
}

void CYawoDie::Exit(CYawo* pYawo){

}

bool CYawoDie::OnMessage(CYawo* agent, const Telegram& msg){
	return false;
}