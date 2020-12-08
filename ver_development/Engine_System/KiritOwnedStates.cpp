#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Usual State
///////////////////////////////////////////////////////////
void CKiritUsual::Enter(CKirit* pKirit){
	CBody* t_pBody = pKirit->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	
	t_pBody->SetVelocity(87.0f);
	pKirit->SetLookEnemy(false);
}

void CKiritUsual::Execute(CKirit* pKirit){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pKirit->GetBody();

	pKirit->CheckHealthState();
	pKirit->EntityMove();

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

	t_pBody->GetPriRot()->z -= 0.04f;

	pKirit->RenderOrgan();
}

void CKiritUsual::Exit(CKirit* pKirit){

}

bool CKiritUsual::OnMessage(CKirit* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Attack:
			agent->GetFSM()->ChangeState(KiritAttack->Instance());
			return true;
		case Msg_Defense:
			agent->GetFSM()->ChangeState(KiritDefense->Instance());
			return true;
		case Msg_RunAway:
			agent->GetFSM()->ChangeState(KiritRunAway->Instance());
			return true;
		case Msg_NotRender:
			agent->GetFSM()->ChangeState(KiritNotRender->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(KiritSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(KiritShock->Instance());
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
			agent->GetFSM()->ChangeState(KiritDie->Instance());
			return true;
		case Msg_Event:
			agent->GetFSM()->ChangeState(KiritEvent->Instance());
			return true;
		default:
			return false;
	}
}

//////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
void CKiritEvent::Enter(CKirit* pKirit){

}

void CKiritEvent::Execute(CKirit* pKirit){
	pKirit->RenderOrgan();
}

void CKiritEvent::Exit(CKirit* pKirit){

}

bool CKiritEvent::OnMessage(CKirit* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(KiritUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Create State
///////////////////////////////////////////////////////////
void CKiritCreate::Enter(CKirit* pKirit){
	
}

void CKiritCreate::Execute(CKirit* pKirit){
	// 바디 계산
	CBody* t_pBody = pKirit->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_vPos.x;
	t_pBody->GetPriPos()->y = t_vPos.y;
	t_pBody->GetPriPos()->z = 700 + t_vPos.z;

	t_pBody->GetPriRot()->z -= 0.02f;

	pKirit->RenderOrgan();
}

void CKiritCreate::Exit(CKirit* pKirit){

}

bool CKiritCreate::OnMessage(CKirit* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			if(AIMgr->BuffCharacterCheck())
				EffectMgr->InsertLightEffect(agent->GetBody());

			agent->GetFSM()->ChangeState(KiritUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Not Render State
///////////////////////////////////////////////////////////
void CKiritNotRender::Enter(CKirit* pKirit){
	
}

void CKiritNotRender::Execute(CKirit* pKirit){
	
}

void CKiritNotRender::Exit(CKirit* pKirit){

}

bool CKiritNotRender::OnMessage(CKirit* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(KiritUsual->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Attack State
///////////////////////////////////////////////////////////
void CKiritAttack::Enter(CKirit* pKirit){
	pKirit->GetBody()->SetVelocity(222.0f);
}

void CKiritAttack::Execute(CKirit* pKirit){
	CBody* t_pBody = pKirit->GetBody();
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();

	pKirit->EntityMove();

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.25f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
		
		// 공격범위 체크
		if(t_pHeroBody->GetPriPos()->x - AIMgr->GetAttackRange()->_max.x > t_pBody->GetPriPos()->x)
			pKirit->GetFSM()->ChangeState(KiritShock->Instance());
	}
	else if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.25f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}

		// 공격범위 체크
		if(t_pHeroBody->GetPriPos()->x + AIMgr->GetAttackRange()->_max.x < t_pBody->GetPriPos()->x)
			pKirit->GetFSM()->ChangeState(KiritUsual->Instance());
	}

	t_pBody->GetPriRot()->z -= 0.8f;

	// 부속품 계산
	for(int i = 0; i < pKirit->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pKirit->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CKirit::EFFECTONE:							
				t_Att->GetPriRot()->z -= 0.2f;
				if(t_Att->GetPriSca()->x < 1.0f){
					t_Att->GetPriSca()->x += 0.1f;
					t_Att->GetPriSca()->y += 0.1f;
				}
				else{
					if(pKirit->EntityAttackToEnemy()){
						pKirit->GetFSM()->ChangeState(KiritSpringUp->Instance());
					}
				}
				break;
			case CKirit::EFFECTTWO:							
				t_Att->GetPriRot()->z -= 0.14f;
				if(t_Att->GetPriSca()->x < 1.0f){
					t_Att->GetPriSca()->x += 0.1f;
					t_Att->GetPriSca()->y += 0.1f;
				}
				break;
			case CKirit::EFFECTTHREE:							
				t_Att->GetPriRot()->z -= 0.18f;
				if(t_Att->GetPriSca()->x < 1.0f){
					t_Att->GetPriSca()->x += 0.1f;
					t_Att->GetPriSca()->y += 0.1f;
				}
				break;
			default:
				break;
		}
	}

	pKirit->RenderOrgan();
}

void CKiritAttack::Exit(CKirit* pKirit){
	// 부속품 계산
	for(int i = 0; i < pKirit->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pKirit->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CKirit::EFFECTONE:		
			case CKirit::EFFECTTWO:		
			case CKirit::EFFECTTHREE:			
					t_Att->GetPriSca()->x = 0.1f;
					t_Att->GetPriSca()->y = 0.1f;
				break;
			default:
				break;
		}
	}

}

bool CKiritAttack::OnMessage(CKirit* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(KiritUsual->Instance());
			return true;
		case Msg_Defense:
			agent->GetFSM()->ChangeState(KiritDefense->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(KiritSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(KiritShock->Instance());
			return true;
		case Msg_Die:
			agent->GetFSM()->ChangeState(KiritDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Defense State
///////////////////////////////////////////////////////////
void CKiritDefense::Enter(CKirit* pKirit){
	CBody* t_pBody = pKirit->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	
	t_pBody->SetVelocity(87.0f);
	pKirit->SetLookEnemy(false);

	pKirit->SetDef(pKirit->GetDef() * 2.0f);
}

void CKiritDefense::Execute(CKirit* pKirit){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pKirit->GetBody();

	pKirit->EntityMove();

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

	t_pBody->GetPriRot()->z -= 0.04f;

	pKirit->RenderOrgan();
}

void CKiritDefense::Exit(CKirit* pKirit){
	pKirit->SetDef(pKirit->GetDef() * 0.5f);
}

bool CKiritDefense::OnMessage(CKirit* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(KiritUsual->Instance());
			return true;
		case Msg_Attack:
			agent->GetFSM()->ChangeState(KiritAttack->Instance());
			return true;
		case Msg_NotRender:
			agent->GetFSM()->ChangeState(KiritNotRender->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(KiritSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(KiritShock->Instance());
			return true;
		case Msg_Die:
			agent->GetFSM()->ChangeState(KiritDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// RunAway State
///////////////////////////////////////////////////////////
void CKiritRunAway::Enter(CKirit* pKirit){
	CBody* t_pBody = pKirit->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	
	t_pBody->SetVelocity(87.0f);
	pKirit->SetLookEnemy(false);

	switch(StageMgr->GetStageType()){
		case CStageManager::DUSTBRIDGE:
			t_pBody->SetRow(CBaseObject::RIGHT);
			break;
		default:
			t_pBody->SetRow(CBaseObject::LEFT);
			break;
	}
}

void CKiritRunAway::Execute(CKirit* pKirit){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = pKirit->GetBody();

	pKirit->EntityMove();

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

	t_pBody->GetPriRot()->z -= 0.04f;

	pKirit->RenderOrgan();
}

void CKiritRunAway::Exit(CKirit* pKirit){
	
}

bool CKiritRunAway::OnMessage(CKirit* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Usual:
			agent->GetFSM()->ChangeState(KiritUsual->Instance());
			return true;
		case Msg_Defense:
			agent->GetFSM()->ChangeState(KiritDefense->Instance());
			return true;
		case Msg_Attack:
			agent->GetFSM()->ChangeState(KiritAttack->Instance());
			return true;
		case Msg_NotRender:
			agent->GetFSM()->ChangeState(KiritNotRender->Instance());
			return true;
		case Msg_SpringUp:
			agent->GetFSM()->ChangeState(KiritSpringUp->Instance());
			return true;
		case Msg_Shock:
			agent->GetFSM()->ChangeState(KiritShock->Instance());
			return true;
		case Msg_Die:
			agent->GetFSM()->ChangeState(KiritDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Shock State
///////////////////////////////////////////////////////////
void CKiritShock::Enter(CKirit* pKirit){
	_shockTime = new CTimer(3000);
	EffectMgr->InsertDiggyEffect(pKirit->GetBody(), 3000);
	pKirit->GetBody()->SetVelocity(0.0f);
}

void CKiritShock::Execute(CKirit* pKirit){
	CBody* t_pBody = pKirit->GetBody();

	pKirit->EntityMove();

	pKirit->RenderOrgan();

	if(_shockTime->IsElapseTimer())
		pKirit->GetFSM()->ChangeState(KiritUsual->Instance());
}

void CKiritShock::Exit(CKirit* pKirit){
    
}

bool CKiritShock::OnMessage(CKirit* agent, const Telegram& msg){
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
void CKiritSpringUp::Enter(CKirit* pKirit){
	CBody* t_pBody = pKirit->GetBody();

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

void CKiritSpringUp::Execute(CKirit* pKirit){
	CBody* t_pBody = pKirit->GetBody();

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
				pKirit->GetFSM()->ChangeState(KiritShock->Instance());
				break;
		}
	}

	pKirit->RenderOrgan();
}

void CKiritSpringUp::Exit(CKirit* pKirit){
    
}

bool CKiritSpringUp::OnMessage(CKirit* agent, const Telegram& msg){
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
void CKiritDie::Enter(CKirit* pKirit){
	CBody* t_pBody = pKirit->GetBody();

	t_pBody->GetPriPos()->y = StageMgr->GetStageHeight() + t_pBody->GetHeightHalf();
	
	t_pBody->SetVelocity(87.0f);
	pKirit->SetLookEnemy(false);
}

void CKiritDie::Execute(CKirit* pKirit){
	CBody* t_pBody = pKirit->GetBody();

	if(t_pBody->GetPriPos()->y - t_pBody->GetHeightHalf() * 0.5f > StageMgr->GetStageHeight())
		t_pBody->GetPriPos()->y -= 0.6f;

	if(t_pBody->GetPriRot()->x > -D3DX_PI*0.25f)
		t_pBody->GetPriRot()->x -= 0.02f;

	// 부속품 계산
	for(int i = 0; i < pKirit->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pKirit->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CKirit::EFFECTONE:							
			case CKirit::EFFECTTWO:	
			case CKirit::EFFECTTHREE:							
				t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.0f;
				break;
			default:
				break;
		}
	}

	pKirit->RenderOrgan();
}

void CKiritDie::Exit(CKirit* pKirit){

}

bool CKiritDie::OnMessage(CKirit* agent, const Telegram& msg){
	return false;	
}