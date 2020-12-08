#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Ready State
///////////////////////////////////////////////////////////
void CDustKidReady::Enter(CDustKid* pDustKid){
	pDustKid->GetBody()->SetVelocity(70.0f);

	_setTimer = false;
}

void CDustKidReady::Execute(CDustKid* pDustKid){
	CBody* t_pBody = pDustKid->GetBody();
	
	pDustKid->CheckHealthState();

	if(pDustKid->GetDestination()->x + 250.0f < t_pBody->GetPriPos()->x){
		pDustKid->GetBody()->SetVelocity(70.0f);
		t_pBody->SetRow(CBaseObject::LEFT);
		pDustKid->EntityMove();
	}
	else if(pDustKid->GetDestination()->x  + 200.0f > t_pBody->GetPriPos()->x){
		pDustKid->GetBody()->SetVelocity(70.0f);
		t_pBody->SetRow(CBaseObject::RIGHT);
		pDustKid->EntityMove();
	}
	else{
		if(_setTimer == false && CameraMgr->GetMode() == CCameraManager::COMBAT){
			pDustKid->SetAttackTime(pDustKid->GetAttackTimeGap());
			_setTimer = true;
		}

		t_pBody->SetRow(CBaseObject::LEFT);
		t_pBody->SetVelocity(0.0f);

		if(pDustKid->GetAttackTime()->IsElapseTimer()){
			if(CameraMgr->GetMode() == CCameraManager::COMBAT){
				pDustKid->GetBody()->SetVelocity(0.0f);
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pDustKid->ID(), pDustKid->ID(), Msg_Attack, NO_ADDITIONAL_INFO);
			}
		}
	}

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.1f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
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
	for(int i = 0; i < pDustKid->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pDustKid->GetAttachmentArray()->Get(i);
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

	pDustKid->RenderOrgan();
}

void CDustKidReady::Exit(CDustKid* pDustKid){
	
}

bool CDustKidReady::OnMessage(CDustKid* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Event:
			agent->GetFSM()->ChangeState(DustKidEvent->Instance());
			return true;
		case Msg_Attack:
			agent->GetFSM()->ChangeState(DustKidNormalAttack->Instance());
			return true;
		case Msg_Healthful:
			agent->SetHealthState(CCharacterEntity::HEALTHFUL);
			agent->GetFSM()->ChangeState(DustKidEscape->Instance());
			return true;
		case Msg_Normal:
			agent->SetHealthState(CCharacterEntity::NORMAL);
			agent->GetFSM()->ChangeState(DustKidEscape->Instance());
			return true;
		case Msg_Weak:
			agent->SetHealthState(CCharacterEntity::WEAK);
			agent->GetFSM()->ChangeState(DustKidEscape->Instance());
			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(DustKidDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
void CDustKidEvent::Enter(CDustKid* pDustKid){
	
}

void CDustKidEvent::Execute(CDustKid* pDustKid){
	// 바디 계산
	CBody* t_pBody = pDustKid->GetBody();
	
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
	for(int i = 0; i < pDustKid->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pDustKid->GetAttachmentArray()->Get(i);
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

	pDustKid->RenderOrgan();
}

void CDustKidEvent::Exit(CDustKid* pDustKid){

}

bool CDustKidEvent::OnMessage(CDustKid* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(DustKidReady->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Normal Attack State
///////////////////////////////////////////////////////////
void CDustKidNormalAttack::Enter(CDustKid* pDustKid){
	_requireDistance = 0.0f;

	pDustKid->SetMinDamage(14.0f);
	pDustKid->SetMaxDamage(18.0f);
}

void CDustKidNormalAttack::Execute(CDustKid* pDustKid){
	CBody* t_pBody = pDustKid->GetBody();
	
	static float t_fDeltaY = 0.0f;
	static bool _bAlpha = false;
	static float t_fEyeY = 0.0f;

	pDustKid->CheckHealthState();

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

	if(_requireDistance <= 30.0f){
		t_pBody->SetVelocity(40.0f);

		float t_Distance = 0.0f;
		_requireDistance += pDustKid->EntityMove(&t_Distance);

		// 부속품 계산
		for(int i = 0; i < pDustKid->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pDustKid->GetAttachmentArray()->Get(i);
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
		pDustKid->GetBody()->SetVelocity(0.0f);

		// 부속품 계산
		for(int i = 0; i < pDustKid->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pDustKid->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CDustKid::SUB:			
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
							if(t_Att->GetPriSca()->x >= 1.5f){
								pDustKid->ApplyDamageEnemyToOurForce(CCharacterEntity::SPRINGUP, 500);
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->x -= 0.0025f;
							t_Att->GetPriSca()->y -= 0.0025f;
							if(t_Att->GetPriSca()->x <= 1.0f){
								pDustKid->GetFSM()->ChangeState(DustKidReady->Instance());
								t_Att->SetScaleState(true);
							}
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
		

	pDustKid->RenderOrgan();
}

void CDustKidNormalAttack::Exit(CDustKid* pDustKid){

}

bool CDustKidNormalAttack::OnMessage(CDustKid* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(DustKidReady->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(DustKidDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Escape State
///////////////////////////////////////////////////////////
void CDustKidEscape::Enter(CDustKid* pDustKid){
	
}

void CDustKidEscape::Execute(CDustKid* pDustKid){
	CBody* t_pBody = pDustKid->GetBody();
	
	pDustKid->CheckHealthState();

	if(pDustKid->GetDestination()->x + AIMgr->GetAttackRange()->_max.x - 300.0f < t_pBody->GetPriPos()->x){
		pDustKid->GetBody()->SetVelocity(150.0f);
		t_pBody->SetRow(CBaseObject::LEFT);
		pDustKid->SetCanMove(true);
		pDustKid->EntityMove();
	}
	else if(pDustKid->GetDestination()->x  + 100.0f > t_pBody->GetPriPos()->x){
		pDustKid->GetBody()->SetVelocity(150.0f);
		t_pBody->SetRow(CBaseObject::RIGHT);
		pDustKid->SetCanMove(true);
		pDustKid->EntityMove();
	}
	else{
		pDustKid->GetFSM()->ChangeState(DustKidReady->Instance());
		t_pBody->SetVelocity(0.0f);
	}

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.1f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
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
	for(int i = 0; i < pDustKid->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pDustKid->GetAttachmentArray()->Get(i);
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

	pDustKid->RenderOrgan();
}

void CDustKidEscape::Exit(CDustKid* pDustKid){

}

bool CDustKidEscape::OnMessage(CDustKid* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(DustKidDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
void CDustKidDie::Enter(CDustKid* pDustKid){
	
}

void CDustKidDie::Execute(CDustKid* pDustKid){
	CBody* t_pBody = pDustKid->GetBody();
		
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

	if(t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.0f){
		t_pBody->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.004f;
		t_pBody->GetPriSca()->x += 0.005f;
		t_pBody->GetPriSca()->y += 0.005f;
	}

	static bool _bAlpha = false;

	static float t_fEyeY = 0.0f;

	// 부속품 계산
	for(int i = 0; i < pDustKid->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pDustKid->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CDustKid::SUB:			
				if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.0f){
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.004f;
					t_Att->GetPriSca()->x += 0.005f;
					t_Att->GetPriSca()->y += 0.005f;

					t_Att->GetPriRot()->z += 0.04f;					
				}
				break;
			case CDustKid::CORE:	
				if(t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.0f){
					t_Att->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.004f;
					t_Att->GetPriSca()->x -= 0.005f;
					t_Att->GetPriSca()->y -= 0.005f;

					t_Att->GetPriRot()->z -= 0.02f;					
				}
				break;
			case CDustKid::EYE:
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
			default:
				break;
		}
	}

	pDustKid->RenderOrgan();
}

void CDustKidDie::Exit(CDustKid* pDustKid){

}

bool CDustKidDie::OnMessage(CDustKid* agent, const Telegram& msg){
	return false;
}