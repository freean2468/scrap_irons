#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Ready State
///////////////////////////////////////////////////////////
void CDustKingReady::Enter(CDustKing* pDustKing){
	pDustKing->GetBody()->SetVelocity(50.0f);

	_setTimer = false;
}

void CDustKingReady::Execute(CDustKing* pDustKing){
	CBody* t_pBody = pDustKing->GetBody();
	
	pDustKing->CheckHealthState();
	
	if(pDustKing->GetDestination()->x - 100.0f < t_pBody->GetPriPos()->x){
		pDustKing->GetBody()->SetVelocity(50.0f);
		t_pBody->SetRow(CBaseObject::LEFT);
		pDustKing->SetCanMove(true);
		pDustKing->EntityMove();
	}
	else if(pDustKing->GetDestination()->x - 150.0f > t_pBody->GetPriPos()->x){
		pDustKing->GetBody()->SetVelocity(50.0f);
		t_pBody->SetRow(CBaseObject::RIGHT);
		pDustKing->SetCanMove(true);
		pDustKing->EntityMove();
	}
	else{
		if(_setTimer == false && CameraMgr->GetMode() == CCameraManager::COMBAT){
			pDustKing->SetAttackTime(pDustKing->GetAttackTimeGap());
			_setTimer = true;
		}

		pDustKing->SetCanMove(false);
		t_pBody->SetRow(CBaseObject::RIGHT);
		t_pBody->SetVelocity(0.0f);

		if(pDustKing->GetAttackTime()->IsElapseTimer()){
			if(CameraMgr->GetMode() == CCameraManager::COMBAT){
				pDustKing->GetBody()->SetVelocity(0.0f);
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pDustKing->ID(), pDustKing->ID(), Msg_Attack, NO_ADDITIONAL_INFO);
			}
		}
	}
	
	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.05f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	static float t_fDeltaY = 0.0f;

	switch(t_pBody->GetMoveState()){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.2f;
			t_fDeltaY += 0.2f;
			if(t_fDeltaY >= 10.0f)
				t_pBody->SetMoveState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.2f;
			t_fDeltaY -= 0.2f;
			if(t_fDeltaY <= 0.0f)
				t_pBody->SetMoveState(true);
			break;
	}

	switch(t_pBody->GetAlphaState()){
		case true:
			// Max라면
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.07f;
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
				t_pBody->SetAlphaState(false);
			break;
		case false:
			// Max라면
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.04f;
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
				t_pBody->SetAlphaState(true);
			break;
	}

	static bool _bAlpha = false;

	static float t_fEyeY = 0.0f;

	// 부속품 계산
	for(int i = 0; i < pDustKing->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pDustKing->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CDustKing::SUB:			
				t_Att->GetPriRot()->z += 0.04f;
				switch(t_Att->GetAlphaState()){
					case true:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.01f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
							t_Att->SetAlphaState(false);
						break;
					case false:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.015f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
							t_Att->SetAlphaState(true);
						break;
				}
				break;
			case CDustKing::CORE:		
				t_Att->GetPriRot()->z -= 0.02f;

				switch(t_Att->GetAlphaState()){
					case true:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.003f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.3f)
							t_Att->SetAlphaState(false);
						break;
					case false:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.002f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.8f)
							t_Att->SetAlphaState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:						
						if(t_Att->GetPriSca()->x >= 1.0f){
							t_Att->SetScaleState(false);
						}
						else{
							t_Att->GetPriSca()->x += 0.01f;
							t_Att->GetPriSca()->y += 0.01f;
						}
						break;
					case false:
						t_Att->SetScaleState(true);
						break;
				}
				break;
			case CDustKing::EYE:
				switch(t_Att->GetMoveState()){
					case true:
						// Max라면
						t_Att->GetPriPos()->y += 0.2f;
						t_fEyeY += 0.2f;
						if(t_fEyeY >= 5.0f)
							t_Att->SetMoveState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriPos()->y -= 0.2f;
						t_fEyeY -= 0.2f;
						if(t_fEyeY <= 0.0f)
							t_Att->SetMoveState(true);
						break;
				}
				break;
			case CDustKing::HAND:				
				if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 1.0f){
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.02f;
				}							
				break;
			default:
				break;
		}
	}

	pDustKing->RenderOrgan();
}

void CDustKingReady::Exit(CDustKing* pDustKing){
	
}

bool CDustKingReady::OnMessage(CDustKing* agent, const Telegram& msg){
	int t_nTemp = rand() % 10;

	switch(msg.Msg){
		case Msg_Event:
			agent->GetFSM()->ChangeState(DustKingEvent->Instance());
			return true;
		case Msg_Attack:
			if(t_nTemp < 4)
				agent->GetFSM()->ChangeState(DustKingNormalAttack->Instance());
			else if (t_nTemp < 7)
				agent->GetFSM()->ChangeState(DustKingHandAttack->Instance());
			else
				agent->GetFSM()->ChangeState(DustKingDustAttack->Instance());
			return true;
		case Msg_Healthful:
			agent->SetHealthState(CCharacterEntity::HEALTHFUL);
			agent->GetFSM()->ChangeState(DustKingEscape->Instance());
			return true;
		case Msg_Normal:
			agent->SetHealthState(CCharacterEntity::NORMAL);
			agent->GetFSM()->ChangeState(DustKingEscape->Instance());
			return true;
		case Msg_Weak:
			agent->SetHealthState(CCharacterEntity::WEAK);
			agent->GetFSM()->ChangeState(DustKingEscape->Instance());
			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(DustKingDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
void CDustKingEvent::Enter(CDustKing* pDustKing){
	
}

void CDustKingEvent::Execute(CDustKing* pDustKing){
	// 바디 계산
	CBody* t_pBody = pDustKing->GetBody();

	static float t_fDeltaY = 0.0f;

	switch(t_pBody->GetMoveState()){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.2f;
			t_fDeltaY += 0.2f;
			if(t_fDeltaY >= 10.0f)
				t_pBody->SetMoveState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.2f;
			t_fDeltaY -= 0.2f;
			if(t_fDeltaY <= 0.0f)
				t_pBody->SetMoveState(true);
			break;
	}

	switch(t_pBody->GetAlphaState()){
		case true:
			// Max라면
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.07f;
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
				t_pBody->SetAlphaState(false);
			break;
		case false:
			// Max라면
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.04f;
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
				t_pBody->SetAlphaState(true);
			break;
	}

	static bool _bAlpha = false;

	static float t_fEyeY = 0.0f;

	// 부속품 계산
	for(int i = 0; i < pDustKing->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pDustKing->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CDustKing::SUB:			
				t_Att->GetPriRot()->z += 0.04f;
				switch(t_Att->GetAlphaState()){
					case true:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.01f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
							t_Att->SetAlphaState(false);
						break;
					case false:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.015f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
							t_Att->SetAlphaState(true);
						break;
				}
				break;
			case CDustKing::CORE:		
				t_Att->GetPriRot()->z -= 0.02f;

				switch(t_Att->GetAlphaState()){
					case true:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.003f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.3f)
							t_Att->SetAlphaState(false);
						break;
					case false:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.002f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.8f)
							t_Att->SetAlphaState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:						
						if(t_Att->GetPriSca()->x >= 1.0f){
							t_Att->SetScaleState(false);
						}
						else{
							t_Att->GetPriSca()->x += 0.01f;
							t_Att->GetPriSca()->y += 0.01f;
						}
						break;
					case false:
						t_Att->SetScaleState(true);
						break;
				}
				break;
			case CDustKing::EYE:
				switch(t_Att->GetMoveState()){
					case true:
						// Max라면
						t_Att->GetPriPos()->y += 0.2f;
						t_fEyeY += 0.2f;
						if(t_fEyeY >= 5.0f)
							t_Att->SetMoveState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriPos()->y -= 0.2f;
						t_fEyeY -= 0.2f;
						if(t_fEyeY <= 0.0f)
							t_Att->SetMoveState(true);
						break;
				}
				break;
			default:
				break;
		}
	}

	pDustKing->RenderOrgan();
}

void CDustKingEvent::Exit(CDustKing* pDustKing){

}

bool CDustKingEvent::OnMessage(CDustKing* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(DustKingReady->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Normal Attack State
///////////////////////////////////////////////////////////
void CDustKingNormalAttack::Enter(CDustKing* pDustKing){
	_moveDistance = 0.0f;

	pDustKing->SetMinDamage(31.0f);
	pDustKing->SetMaxDamage(42.0f);

	if(AIMgr->AILiveCheckToYawoAndKirit()){
		_requireDistance = 300.0f;
	}
	else
		_requireDistance = 30.0f;
}

void CDustKingNormalAttack::Execute(CDustKing* pDustKing){
	CBody* t_pBody = pDustKing->GetBody();
	
	pDustKing->CheckHealthState();

	static float t_fDeltaY = 0.0f;

	static bool _bAlpha = false;

	static float t_fEyeY = 0.0f;

	switch(t_pBody->GetMoveState()){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.1f;
			t_fDeltaY += 0.1f;
			if(t_fDeltaY >= 5.0f){
				t_pBody->SetMoveState(false);
			}
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.1f;
			t_fDeltaY -= 0.1f;
			if(t_fDeltaY <= 0.0f)
				t_pBody->SetMoveState(true);
			break;
	}

	switch(t_pBody->GetAlphaState()){
		case true:
			// Max라면
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.07f;
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
				t_pBody->SetAlphaState(false);
			break;
		case false:
			// Max라면
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.04f;
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
				t_pBody->SetAlphaState(true);
			break;
	}

	if(_moveDistance <= _requireDistance){
		t_pBody->SetVelocity(40.0f);
		float t_Distance = 0.0f;
		pDustKing->SetCanMove(true);
		_moveDistance += pDustKing->EntityMove(&t_Distance);

		if(pDustKing->GetCanAttack())
			_moveDistance = _requireDistance + 1.0f;

		// 부속품 계산
		for(int i = 0; i < pDustKing->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pDustKing->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CDustKid::SUB:			
					t_Att->GetPriRot()->z += 0.04f;
					switch(t_Att->GetAlphaState()){
						case true:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.01f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
								t_Att->SetAlphaState(false);
							break;
						case false:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.015f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
								t_Att->SetAlphaState(true);
							break;
					}
					break;
				case CDustKid::CORE:		
					t_Att->GetPriRot()->z -= 0.02f;

					switch(t_Att->GetAlphaState()){
						case true:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.003f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.3f)
								t_Att->SetAlphaState(false);
							break;
						case false:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.002f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.8f)
								t_Att->SetAlphaState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:						
							if(t_Att->GetPriSca()->x >= 1.0f){
								t_Att->SetScaleState(false);
							}
							else{
								t_Att->GetPriSca()->x += 0.01f;
								t_Att->GetPriSca()->y += 0.01f;
							}
							break;
						case false:
							t_Att->SetScaleState(true);
							break;
					}
					break;
				case CDustKid::EYE:
					switch(t_Att->GetMoveState()){
						case true:
							// Max라면
							t_Att->GetPriPos()->y += 0.2f;
							t_fEyeY += 0.2f;
							if(t_fEyeY >= 5.0f)
								t_Att->SetMoveState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriPos()->y -= 0.2f;
							t_fEyeY -= 0.2f;
							if(t_fEyeY <= 0.0f)
								t_Att->SetMoveState(true);
							break;
					}
					break;
				default:
					break;
			}
		}		
	}
	else{
		t_pBody->SetVelocity(0.0f);

		// 부속품 계산
		for(int i = 0; i < pDustKing->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pDustKing->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CDustKing::SUB:			
					t_Att->GetPriRot()->z += 0.2f;

					switch(t_Att->GetAlphaState()){
						case true:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.005f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.8f)
								t_Att->SetAlphaState(false);
							break;
						case false:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.005f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
								t_Att->SetAlphaState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:
							t_Att->GetPriSca()->x += 0.005f;
							t_Att->GetPriSca()->y += 0.005f;
							if(t_Att->GetPriSca()->x >= 1.4f){
								pDustKing->ApplyDamageEnemyToOurForce(CCharacterEntity::SPRINGUP, 1000);
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->x -= 0.0025f;
							t_Att->GetPriSca()->y -= 0.0025f;
							if(t_Att->GetPriSca()->x <= 1.0f){
								pDustKing->GetFSM()->ChangeState(DustKingReady->Instance());
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CDustKing::CORE:		
					t_Att->GetPriRot()->z -= 0.02f;
					switch(t_Att->GetAlphaState()){
						case true:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.003f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.3f)
								t_Att->SetAlphaState(false);
							break;
						case false:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.002f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.8f)
								t_Att->SetAlphaState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:
							t_Att->SetScaleState(false);
							break;
						case false:						
							if(t_Att->GetPriSca()->x <= 0.6f){
								t_Att->SetScaleState(true);
							}
							else{
								t_Att->GetPriSca()->x -= 0.01f;
								t_Att->GetPriSca()->y -= 0.01f;
							}
							break;
					}
					break;
				case CDustKing::EYE:
					switch(t_Att->GetMoveState()){
						case true:
							// Max라면
							t_Att->GetPriPos()->y += 0.2f;
							t_fEyeY += 0.2f;
							if(t_fEyeY >= 5.0f)
								t_Att->SetMoveState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriPos()->y -= 0.2f;
							t_fEyeY -= 0.2f;
							if(t_fEyeY <= 0.0f)
								t_Att->SetMoveState(true);
							break;
					}
					break;
				default:
					break;
			}
		}
	}

	pDustKing->RenderOrgan();
}

void CDustKingNormalAttack::Exit(CDustKing* pDustKing){

}

bool CDustKingNormalAttack::OnMessage(CDustKing* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(DustKingReady->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(DustKingDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Hand Attack State
///////////////////////////////////////////////////////////
void CDustKingHandAttack::Enter(CDustKing* pDustKing){
	_moveDistance = 0.0f;

	pDustKing->SetMinDamage(28.0f);
	pDustKing->SetMaxDamage(34.0f);

	if(AIMgr->AILiveCheckToYawoAndKirit()){
		_requireDistance = 300.0f;
	}
	else
		_requireDistance = 30.0f;

	_vHandOrigin.x = pDustKing->GetAttachmentFromType(CDustKing::HAND)->GetPriPos()->x;
	_vHandOrigin.y = pDustKing->GetAttachmentFromType(CDustKing::HAND)->GetPriPos()->y;
	_vHandOrigin.z = pDustKing->GetAttachmentFromType(CDustKing::HAND)->GetPriPos()->z;
}

void CDustKingHandAttack::Execute(CDustKing* pDustKing){
	CBody* t_pBody = pDustKing->GetBody();
	
	pDustKing->CheckHealthState();

	static float t_fAceX = 1.0f;

	static float t_fDeltaY = 0.0f;

	static bool _bAlpha = false;

	static float t_fEyeY = 0.0f;

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.05f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	switch(t_pBody->GetMoveState()){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.2f;
			t_fDeltaY += 0.2f;
			if(t_fDeltaY >= 10.0f)
				t_pBody->SetMoveState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.2f;
			t_fDeltaY -= 0.2f;
			if(t_fDeltaY <= 0.0f)
				t_pBody->SetMoveState(true);
			break;
	}

	switch(t_pBody->GetAlphaState()){
		case true:
			// Max라면
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.07f;
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
				t_pBody->SetAlphaState(false);
			break;
		case false:
			// Max라면
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.04f;
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
				t_pBody->SetAlphaState(true);
			break;
	}

	if(_moveDistance <= _requireDistance){
		t_pBody->SetVelocity(40.0f);
		float t_Distance = 0.0f;
		pDustKing->SetCanMove(true);
		_moveDistance += pDustKing->EntityMove(&t_Distance);

		if(pDustKing->GetCanAttack())
			_moveDistance = _requireDistance + 1.0f;

		// 부속품 계산
		for(int i = 0; i < pDustKing->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pDustKing->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
					case CDustKing::SUB:			
					t_Att->GetPriRot()->z += 0.04f;
					switch(t_Att->GetAlphaState()){
						case true:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.01f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
								t_Att->SetAlphaState(false);
							break;
						case false:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.015f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
								t_Att->SetAlphaState(true);
							break;
					}
					break;
				case CDustKing::CORE:		
					t_Att->GetPriRot()->z -= 0.02f;

					switch(t_Att->GetAlphaState()){
						case true:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.003f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.3f)
								t_Att->SetAlphaState(false);
							break;
						case false:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.002f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.8f)
								t_Att->SetAlphaState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:						
							if(t_Att->GetPriSca()->x >= 1.0f){
								t_Att->SetScaleState(false);
							}
							else{
								t_Att->GetPriSca()->x += 0.01f;
								t_Att->GetPriSca()->y += 0.01f;
							}
							break;
						case false:
							t_Att->SetScaleState(true);
							break;
					}
					break;
				case CDustKid::EYE:
					switch(t_Att->GetMoveState()){
						case true:
							// Max라면
							t_Att->GetPriPos()->y += 0.2f;
							t_fEyeY += 0.2f;
							if(t_fEyeY >= 5.0f)
								t_Att->SetMoveState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriPos()->y -= 0.2f;
							t_fEyeY -= 0.2f;
							if(t_fEyeY <= 0.0f)
								t_Att->SetMoveState(true);
							break;
					}
					break;
				default:
					break;
			}
		}		
	}
	else{
		t_pBody->SetVelocity(0.0f);

		// 부속품 계산
		for(int i = 0; i < pDustKing->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pDustKing->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CDustKing::SUB:			
					t_Att->GetPriRot()->z += 0.04f;
					switch(t_Att->GetAlphaState()){
						case true:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.01f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
								t_Att->SetAlphaState(false);
							break;
						case false:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.015f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
								t_Att->SetAlphaState(true);
							break;
					}
					break;
				case CDustKing::CORE:		
					t_Att->GetPriRot()->z -= 0.02f;

					switch(t_Att->GetAlphaState()){
						case true:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.003f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.3f)
								t_Att->SetAlphaState(false);
							break;
						case false:
							// Max라면
							t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.002f;
							if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.8f)
								t_Att->SetAlphaState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:						
							if(t_Att->GetPriSca()->x >= 1.0f){
								t_Att->SetScaleState(false);
							}
							else{
								t_Att->GetPriSca()->x += 0.01f;
								t_Att->GetPriSca()->y += 0.01f;
							}
							break;
						case false:
							t_Att->SetScaleState(true);
							break;
					}
					break;
				case CDustKing::EYE:
					switch(t_Att->GetMoveState()){
						case true:
							// Max라면
							t_Att->GetPriPos()->y += 0.2f;
							t_fEyeY += 0.2f;
							if(t_fEyeY >= 5.0f)
								t_Att->SetMoveState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriPos()->y -= 0.2f;
							t_fEyeY -= 0.2f;
							if(t_fEyeY <= 0.0f)
								t_Att->SetMoveState(true);
							break;
					}
					break;
				case CDustKing::HAND:
					switch(t_Att->GetMoveState()){
						case true:
							t_Att->GetPriPos()->x -= t_fAceX;
							t_fAceX *= 1.015f;

							if(t_pBody->GetPriPos()->x + t_Att->GetPriPos()->x <= t_pBody->GetPriPos()->x - 150.0f){
								t_Att->SetMoveState(false);
								t_fAceX = 1.5f;
							}
							break;
						case false:	
							if(t_pBody->GetPriPos()->x + t_Att->GetPriPos()->x >= t_pBody->GetPriPos()->x + 170.0f){								
								pDustKing->ApplyDamageEnemyToOurForce(CCharacterEntity::SPRINGUP, 1500);								
								t_fAceX = 1.0f;
								if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.0f){
									t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.02f;
								}
								else{
									t_Att->SetMoveState(true);
									pDustKing->GetFSM()->ChangeState(DustKingReady->Instance());
									t_Att->GetPriPos()->x = _vHandOrigin.x;
									t_Att->GetPriPos()->y = _vHandOrigin.y;
								}
							}
							else{
								t_Att->GetPriPos()->x += t_fAceX;
								t_fAceX *= 1.04f;
							}
							break;
					}
					break;
				default:
					break;
			}
		}
	}

	pDustKing->RenderOrgan();
}

void CDustKingHandAttack::Exit(CDustKing* pDustKing){

}

bool CDustKingHandAttack::OnMessage(CDustKing* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(DustKingReady->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(DustKingDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Dust Attack State
///////////////////////////////////////////////////////////
void CDustKingDustAttack::Enter(CDustKing* pDustKing){
	_timer = new CTimer(200);
	_nCount = 0;

	pDustKing->SetMinDamage(4.0f);
	pDustKing->SetMaxDamage(6.0f);

	_vHandOrigin.x = pDustKing->GetAttachmentFromType(CDustKing::HAND)->GetPriPos()->x;
	_vHandOrigin.y = pDustKing->GetAttachmentFromType(CDustKing::HAND)->GetPriPos()->y;
}

void CDustKingDustAttack::Execute(CDustKing* pDustKing){
	CBody* t_pBody = pDustKing->GetBody();
	
	pDustKing->CheckHealthState();

	static float t_fDeltaY = 0.0f;

	static bool _bAlpha = false;

	static float t_fEyeY = 0.0f;

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.05f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	switch(t_pBody->GetMoveState()){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.2f;
			t_fDeltaY += 0.2f;
			if(t_fDeltaY >= 10.0f)
				t_pBody->SetMoveState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.2f;
			t_fDeltaY -= 0.2f;
			if(t_fDeltaY <= 0.0f)
				t_pBody->SetMoveState(true);
			break;
	}

	switch(t_pBody->GetAlphaState()){
		case true:
			// Max라면
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.07f;
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
				t_pBody->SetAlphaState(false);
			break;
		case false:
			// Max라면
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.04f;
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
				t_pBody->SetAlphaState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pDustKing->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pDustKing->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
				case CDustKing::SUB:			
				t_Att->GetPriRot()->z += 0.04f;
				switch(t_Att->GetAlphaState()){
					case true:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.01f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
							t_Att->SetAlphaState(false);
						break;
					case false:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.015f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
							t_Att->SetAlphaState(true);
						break;
				}
				break;
			case CDustKing::CORE:		
				t_Att->GetPriRot()->z -= 0.02f;

				switch(t_Att->GetAlphaState()){
					case true:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.003f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.3f)
							t_Att->SetAlphaState(false);
						break;
					case false:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.002f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.8f)
							t_Att->SetAlphaState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:						
						if(t_Att->GetPriSca()->x >= 1.0f){
							t_Att->SetScaleState(false);
						}
						else{
							t_Att->GetPriSca()->x += 0.01f;
							t_Att->GetPriSca()->y += 0.01f;
						}
						break;
					case false:
						t_Att->SetScaleState(true);
						break;
				}
				break;
			case CDustKid::EYE:
				switch(t_Att->GetMoveState()){
					case true:
						// Max라면
						t_Att->GetPriPos()->y += 0.2f;
						t_fEyeY += 0.2f;
						if(t_fEyeY >= 5.0f)
							t_Att->SetMoveState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriPos()->y -= 0.2f;
						t_fEyeY -= 0.2f;
						if(t_fEyeY <= 0.0f)
							t_Att->SetMoveState(true);
						break;
				}
				break;
			case CDustKing::HAND:
				switch(t_Att->GetAlphaState()){
					case true:
						if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.0f)
							t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.015f;

						if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.0f){
							t_Att->GetPriPos()->x = AIMgr->GetHero()->GetBody()->GetPriPos()->x - t_pBody->GetPriPos()->x;
							t_Att->GetPriPos()->y = -200.0f;
							t_Att->SetAlphaState(false);
						}
						break;
					case false:	
						if(_nCount <= 16){
							if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 1.0f){
								t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
							}
							else{							
								if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 1.0f){
									if(_timer->IsElapseTimer()){
										EffectMgr->InsertBoldDustEffect(&D3DXVECTOR3(t_pBody->GetPriPos()->x + t_Att->GetPriPos()->x, t_pBody->GetPriPos()->y - 200.0f, 0.0f));
										_timer = new CTimer(200);
										_nCount++;
									}
								}
							}
						}
						else{
							if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.0f){
								t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.02f;
							}
							else{							
								t_Att->GetPriPos()->x = _vHandOrigin.x;
								t_Att->GetPriPos()->y = _vHandOrigin.y;
								t_Att->SetAlphaState(true);
								pDustKing->GetFSM()->ChangeState(DustKingReady->Instance());
							}
						}
						break;
				}
				break;
			default:
				break;
		}
	}

	pDustKing->RenderOrgan();
}

void CDustKingDustAttack::Exit(CDustKing* pDustKing){
	delete _timer;
}

bool CDustKingDustAttack::OnMessage(CDustKing* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(DustKingReady->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(DustKingDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Escape State
///////////////////////////////////////////////////////////
void CDustKingEscape::Enter(CDustKing* pDustKing){
	
}

void CDustKingEscape::Execute(CDustKing* pDustKing){
	CBody* t_pBody = pDustKing->GetBody();
	
	pDustKing->CheckHealthState();

	if(pDustKing->GetDestination()->x - 100.0f < t_pBody->GetPriPos()->x){
		pDustKing->GetBody()->SetVelocity(100.0f);
		t_pBody->SetRow(CBaseObject::LEFT);
		pDustKing->SetCanMove(true);
		pDustKing->EntityMove();
	}
	else if(pDustKing->GetDestination()->x - AIMgr->GetAttackRange()->_max.x + 200.0f > t_pBody->GetPriPos()->x){
		pDustKing->GetBody()->SetVelocity(100.0f);
		t_pBody->SetRow(CBaseObject::RIGHT);
		pDustKing->SetCanMove(true);
		pDustKing->EntityMove();
	}
	else{
		pDustKing->GetFSM()->ChangeState(DustKingReady->Instance());
		t_pBody->SetVelocity(0.0f);
	}

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::RIGHT){
		if(t_pBody->GetPriRot()->y > 0.0f){
			t_pBody->GetPriRot()->y -= 0.05f;
			if(t_pBody->GetPriRot()->y < 0.0f)
				t_pBody->GetPriRot()->y = 0.0f;
		}
	}

	static float t_fDeltaY = 0.0f;

	switch(t_pBody->GetMoveState()){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.2f;
			t_fDeltaY += 0.2f;
			if(t_fDeltaY >= 10.0f)
				t_pBody->SetMoveState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.2f;
			t_fDeltaY -= 0.2f;
			if(t_fDeltaY <= 0.0f)
				t_pBody->SetMoveState(true);
			break;
	}

	switch(t_pBody->GetAlphaState()){
		case true:
			// Max라면
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.07f;
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
				t_pBody->SetAlphaState(false);
			break;
		case false:
			// Max라면
			t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.04f;
			if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
				t_pBody->SetAlphaState(true);
			break;
	}

	static bool _bAlpha = false;

	static float t_fEyeY = 0.0f;

	// 부속품 계산
	for(int i = 0; i < pDustKing->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pDustKing->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CDustKing::SUB:			
				t_Att->GetPriRot()->z += 0.04f;
				switch(t_Att->GetAlphaState()){
					case true:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.01f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.2f)
							t_Att->SetAlphaState(false);
						break;
					case false:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.015f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f)
							t_Att->SetAlphaState(true);
						break;
				}
				break;
			case CDustKing::CORE:		
				t_Att->GetPriRot()->z -= 0.02f;
				switch(t_Att->GetAlphaState()){
					case true:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.003f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.3f)
							t_Att->SetAlphaState(false);
						break;
					case false:
						// Max라면
						t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.002f;
						if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.8f)
							t_Att->SetAlphaState(true);
						break;
				}
				break;
			case CDustKing::EYE:
				switch(t_Att->GetMoveState()){
					case true:
						// Max라면
						t_Att->GetPriPos()->y += 0.2f;
						t_fEyeY += 0.2f;
						if(t_fEyeY >= 5.0f)
							t_Att->SetMoveState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriPos()->y -= 0.2f;
						t_fEyeY -= 0.2f;
						if(t_fEyeY <= 0.0f)
							t_Att->SetMoveState(true);
						break;
				}
				break;
			default:
				break;
		}
	}

	pDustKing->RenderOrgan();
}

void CDustKingEscape::Exit(CDustKing* pDustKing){

}

bool CDustKingEscape::OnMessage(CDustKing* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(DustKingDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
void CDustKingDie::Enter(CDustKing* pDustKing){
	
}

void CDustKingDie::Execute(CDustKing* pDustKing){
	CBody* t_pBody = pDustKing->GetBody();
		
	static float t_fDeltaY = 0.0f;

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.0f){
		t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.004f;
		t_pBody->GetPriSca()->x += 0.005f;
		t_pBody->GetPriSca()->y += 0.005f;
	}

	static bool _bAlpha = false;

	static float t_fEyeY = 0.0f;

	// 부속품 계산
	for(int i = 0; i < pDustKing->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pDustKing->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CDustKing::SUB:			
				if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.0f){
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.004f;
					t_Att->GetPriSca()->x += 0.005f;
					t_Att->GetPriSca()->y += 0.005f;

					t_Att->GetPriRot()->z += 0.04f;					
				}
				break;
			case CDustKing::CORE:	
				if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.0f){
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.004f;
					t_Att->GetPriSca()->x -= 0.005f;
					t_Att->GetPriSca()->y -= 0.005f;

					t_Att->GetPriRot()->z -= 0.02f;					
				}
				break;
			case CDustKing::EYE:
				if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.0f){
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.004f;

					switch(t_Att->GetMoveState()){
						case true:
							// Max라면
							t_Att->GetPriPos()->y += 0.2f;
							t_fEyeY += 0.2f;
							if(t_fEyeY >= 5.0f)
								t_Att->SetMoveState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriPos()->y -= 0.2f;
							t_fEyeY -= 0.2f;
							if(t_fEyeY <= 0.0f)
								t_Att->SetMoveState(true);
							break;
					}
				}
				break;
			case CDustKing::PUPIL:
				if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.0f){
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.004f;
				}
				break;
			case CDustKing::TIARA:
				if(t_Att->GetPriPos()->y > StageMgr->GetStageHeight())
					t_Att->GetPriPos()->y -= 0.8f;
				break;
			case CDustKing::HAND:
				if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.0f){
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.004f;
					t_Att->GetPriSca()->x -= 0.005f;
					t_Att->GetPriSca()->y -= 0.005f;

					t_Att->GetPriRot()->z -= 0.02f;					
				}
				break;
			default:
				break;
		}
	}

	pDustKing->RenderOrgan();
}

void CDustKingDie::Exit(CDustKing* pDustKing){

}

bool CDustKingDie::OnMessage(CDustKing* agent, const Telegram& msg){
	return false;
}