#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Ready State
///////////////////////////////////////////////////////////
void CMiniWorkerReady::Enter(CMiniWorker* pMiniWorker){
	pMiniWorker->GetBody()->SetVelocity(20.0f);

	_setTimer = false;
	pMiniWorker->SetCanMove(true);
}

void CMiniWorkerReady::Execute(CMiniWorker* pMiniWorker){
	CBody* t_pBody = pMiniWorker->GetBody();
	
	pMiniWorker->CheckHealthState();

	if(pMiniWorker->GetDestination()->x + 250.0f < t_pBody->GetPriPos()->x){
		pMiniWorker->GetBody()->SetVelocity(30.0f);
		t_pBody->SetRow(CBaseObject::LEFT);
		pMiniWorker->SetCanMove(true);
		pMiniWorker->EntityMove();
	}
	else if(pMiniWorker->GetDestination()->x  + 200.0f > t_pBody->GetPriPos()->x){
		pMiniWorker->GetBody()->SetVelocity(30.0f);
		t_pBody->SetRow(CBaseObject::RIGHT);
		pMiniWorker->SetCanMove(true);
		pMiniWorker->EntityMove();
	}
	else{
		if(_setTimer == false && CameraMgr->GetMode() == CCameraManager::COMBAT){
			pMiniWorker->SetAttackTime(pMiniWorker->GetAttackTimeGap());
			_setTimer = true;
		}

		pMiniWorker->SetCanMove(false);
		t_pBody->SetRow(CBaseObject::LEFT);
		t_pBody->SetVelocity(0.0f);

		if(pMiniWorker->GetAttackTime()->IsElapseTimer()){
			if(CameraMgr->GetMode() == CCameraManager::COMBAT){
				t_pBody->SetVelocity(0.0f);
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pMiniWorker->ID(), pMiniWorker->ID(), Msg_Attack, NO_ADDITIONAL_INFO);
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

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.001f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.005f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.001f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.005f)
				t_pBody->SetAngleState(true);
			break;
	}

	static bool _bAlpha = false;

	// 부속품 계산
	for(int i = 0; i < pMiniWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pMiniWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CMiniWorker::MOUSEUNDER:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.005f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.05f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.005f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CMiniWorker::LIGHTONE:			
				if(!pMiniWorker->GetAttackTime()->GetElapseTime() == 0){
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = -((float)pMiniWorker->GetAttackTime()->GetElapseTime() * (1.0f/pMiniWorker->GetAttackTimeGap()));
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = -((float)pMiniWorker->GetAttackTime()->GetElapseTime() * (1.0f/pMiniWorker->GetAttackTimeGap()));
				}

				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.002f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.002f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
							t_Att->SetAngleState(true);
						break;
				}
				if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
					_bAlpha = !_bAlpha;

				if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
				else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
				break;
			case CMiniWorker::LIGHTTWO:		
				if(!pMiniWorker->GetAttackTime()->GetElapseTime() == 0){
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = -((float)pMiniWorker->GetAttackTime()->GetElapseTime() * (1.0f/pMiniWorker->GetAttackTimeGap()));
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = -((float)pMiniWorker->GetAttackTime()->GetElapseTime() * (1.0f/pMiniWorker->GetAttackTimeGap()));
				}

				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z -= 0.001f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.008f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z += 0.001f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.008f)
							t_Att->SetAngleState(true);
						break;
				}
				if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
					_bAlpha = !_bAlpha;

				if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
				else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
				break;
			case CMiniWorker::LEFT:
			case CMiniWorker::RIGHT:
				if(t_pBody->GetRow() == CBaseObject::LEFT)
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				else
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pMiniWorker->RenderOrgan();
}

void CMiniWorkerReady::Exit(CMiniWorker* pMiniWorker){
	
}

bool CMiniWorkerReady::OnMessage(CMiniWorker* agent, const Telegram& msg){
	int t_nTemp = rand() % 10;

	switch(msg.Msg){
		case Msg_Event:
			agent->GetFSM()->ChangeState(MiniWorkerEvent->Instance());
			return true;
		case Msg_Attack:
			if(t_nTemp < 7)
				agent->GetFSM()->ChangeState(MiniWorkerChinAttack->Instance());
			else
				agent->GetFSM()->ChangeState(MiniWorkerWalkingChinAttack->Instance());
			return true;
		case Msg_Healthful:
			agent->SetHealthState(CCharacterEntity::HEALTHFUL);
			agent->GetFSM()->ChangeState(MiniWorkerEscape->Instance());
			return true;
		case Msg_Normal:
			agent->SetHealthState(CCharacterEntity::NORMAL);
			agent->GetFSM()->ChangeState(MiniWorkerEscape->Instance());
			return true;
		case Msg_Weak:
			agent->SetHealthState(CCharacterEntity::WEAK);
			agent->GetFSM()->ChangeState(MiniWorkerEscape->Instance());
			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(MiniWorkerDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
void CMiniWorkerEvent::Enter(CMiniWorker* pMiniWorker){
	
}

void CMiniWorkerEvent::Execute(CMiniWorker* pMiniWorker){
	// 바디 계산
	CBody* t_pBody = pMiniWorker->GetBody();

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.001f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.005f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.001f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.005f)
				t_pBody->SetAngleState(true);
			break;
	}

	static bool _bAlpha = false;

	// 부속품 계산
	for(int i = 0; i < pMiniWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pMiniWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CMiniWorker::MOUSEUNDER:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.005f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.05f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.005f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CMiniWorker::LIGHTONE:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.002f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.002f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
							t_Att->SetAngleState(true);
						break;
				}
				if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
					_bAlpha = !_bAlpha;

				if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
				else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
				break;
			case CMiniWorker::LIGHTTWO:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z -= 0.001f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.008f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z += 0.001f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.008f)
							t_Att->SetAngleState(true);
						break;
				}
				if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
					_bAlpha = !_bAlpha;

				if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
				else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
				break;
			case CMiniWorker::LEFT:
			case CMiniWorker::RIGHT:
				if(t_pBody->GetRow() == CBaseObject::LEFT)
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				else
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pMiniWorker->RenderOrgan();
}

void CMiniWorkerEvent::Exit(CMiniWorker* pMiniWorker){

}

bool CMiniWorkerEvent::OnMessage(CMiniWorker* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(MiniWorkerReady->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Normal Attack State
///////////////////////////////////////////////////////////
void CMiniWorkerChinAttack::Enter(CMiniWorker* pMiniWorker){
	_moveDistance = 0.0f;

	pMiniWorker->SetMinDamage(6.0f);
	pMiniWorker->SetMaxDamage(9.0f);

	if(AIMgr->AILiveCheckToYawoAndKirit()){
		_requireDistance = 500.0f;
	}
	else
		_requireDistance = 30.0f;
}

void CMiniWorkerChinAttack::Execute(CMiniWorker* pMiniWorker){
	CBody* t_pBody = pMiniWorker->GetBody();
	
	static bool _bAlpha = false;

	pMiniWorker->CheckHealthState();

	// 아이템 먹기
	if(pMiniWorker->ComputeBoundMouseAndItem())
		pMiniWorker->GetFSM()->ChangeState(MiniWorkerItemEat->Instance());

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.001f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.005f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.001f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.005f)
				t_pBody->SetAngleState(true);
			break;
	}

	if(_moveDistance <= _requireDistance){
		t_pBody->SetVelocity(40.0f);
		pMiniWorker->SetCanMove(true);

		if(pMiniWorker->GetCanAttack())
			_moveDistance = _requireDistance + 1.0f;

		float t_Distance = 0.0f;
		_moveDistance += pMiniWorker->EntityMove(&t_Distance);

		// 부속품 계산
		for(int i = 0; i < pMiniWorker->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pMiniWorker->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CMiniWorker::MOUSEUNDER:			
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.005f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.05f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.005f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
								t_Att->SetAngleState(true);
							break;
					}
					break;
				case CMiniWorker::LIGHTONE:			
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = -1.0f;
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = -1.0f;

					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.002f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.002f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
								t_Att->SetAngleState(true);
							break;
					}
					if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
						_bAlpha = !_bAlpha;

					if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
					else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
					break;
				case CMiniWorker::LIGHTTWO:		
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = -1.0f;
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = -1.0f;

					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z -= 0.001f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.008f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z += 0.001f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.008f)
								t_Att->SetAngleState(true);
							break;
					}
					if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
						_bAlpha = !_bAlpha;

					if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
					else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
					break;
				case CMiniWorker::LEFT:
				case CMiniWorker::RIGHT:
					if(t_pBody->GetRow() == CBaseObject::LEFT)
						t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
					else
						t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
					break;
				default:
					break;
			}
		}
	}
	else{
		t_pBody->SetVelocity(0.0f);
		pMiniWorker->SetCanMove(false);

		static int _nCount = 0;
		static float _mouseAngle = 0.0f;

		// 부속품 계산
		for(int i = 0; i < pMiniWorker->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pMiniWorker->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CMiniWorker::MOUSEUNDER:		
					if(_nCount < 4){					
						switch(t_Att->GetAngleState()){
							case true:
								// Min라면
								t_Att->GetPriRot()->z -= 0.04f;
								if(t_Att->GetPriRot()->z <= D3DX_PI * 0.1f)
									t_Att->SetAngleState(false);
								break;
							case false:
								// Max라면
								t_Att->GetPriRot()->z += 0.04f;

								if(t_Att->GetPriRot()->z >= D3DX_PI * 0.3f && t_Att->GetPriRot()->z <= D3DX_PI * 0.3f + 0.04f)
									pMiniWorker->ApplyDamageEnemyToOurForce(CCharacterEntity::SPRINGUP, 500);

								if(t_Att->GetPriRot()->z >= D3DX_PI * 0.5f){								
									t_Att->SetAngleState(true);
									_nCount++;
								}
								break;
						}
					}
					else{
						pMiniWorker->GetFSM()->ChangeState(MiniWorkerReady->Instance());
						_nCount = 0;
						_mouseAngle = 0.0f;
					}
					break;
				case CMiniWorker::LIGHTONE:	
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = -1.0f;
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = -1.0f;

					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.002f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.002f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
								t_Att->SetAngleState(true);
							break;
					}
					if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
						_bAlpha = !_bAlpha;

					if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
					else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
					break;
				case CMiniWorker::LIGHTTWO:	
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = -1.0f;
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = -1.0f;

					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z -= 0.001f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.008f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z += 0.001f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.008f)
								t_Att->SetAngleState(true);
							break;
					}
					if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
						_bAlpha = !_bAlpha;

					if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
					else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
					break;
				case CMiniWorker::LEFT:
				case CMiniWorker::RIGHT:
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
					break;
				default:
					break;
			}
		}
	}

	pMiniWorker->RenderOrgan();
}

void CMiniWorkerChinAttack::Exit(CMiniWorker* pMiniWorker){
	// 부속품 계산
	for(int i = 0; i < pMiniWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pMiniWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CMiniWorker::LIGHTONE:			
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = 0.0f;
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = 0.0f;				
				break;
			case CMiniWorker::LIGHTTWO:		
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = 0.0f;
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = 0.0f;
				break;
			default:
				break;
		}
	}
}

bool CMiniWorkerChinAttack::OnMessage(CMiniWorker* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(MiniWorkerReady->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(MiniWorkerDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Walking Attack State
///////////////////////////////////////////////////////////
void CMiniWorkerWalkingChinAttack::Enter(CMiniWorker* pMiniWorker){
	_moveDistance = 0.0f;

	pMiniWorker->SetMinDamage(6.0f);
	pMiniWorker->SetMaxDamage(9.0f);

	if(AIMgr->AILiveCheckToYawoAndKirit()){
		_requireDistance = 500.0f;
	}
	else
		_requireDistance = 30.0f;

	pMiniWorker->GetBody()->SetVelocity(30.0f);
}

void CMiniWorkerWalkingChinAttack::Execute(CMiniWorker* pMiniWorker){
	CBody* t_pBody = pMiniWorker->GetBody();
	
	static bool _bAlpha = false;

	pMiniWorker->CheckHealthState();

	// 아이템 먹기
	if(pMiniWorker->ComputeBoundMouseAndItem())
		pMiniWorker->GetFSM()->ChangeState(MiniWorkerItemEat->Instance());

	switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.001f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.005f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.001f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.005f)
				t_pBody->SetAngleState(true);
			break;
	}

	if(_moveDistance <= _requireDistance){
		t_pBody->SetVelocity(30.0f);
		pMiniWorker->SetCanMove(true);

		if(pMiniWorker->GetCanAttack())
			_moveDistance = _requireDistance + 1.0f;

		float t_Distance = 0.0f;
		_moveDistance += pMiniWorker->EntityMove(&t_Distance);

		// 부속품 계산
		for(int i = 0; i < pMiniWorker->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pMiniWorker->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CMiniWorker::MOUSEUNDER:			
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.005f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.05f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.005f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
								t_Att->SetAngleState(true);
							break;
					}
					break;
				case CMiniWorker::LIGHTONE:			
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = -1.0f;
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = -1.0f;

					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.002f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.002f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
								t_Att->SetAngleState(true);
							break;
					}
					if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
						_bAlpha = !_bAlpha;

					if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
					else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
					break;
				case CMiniWorker::LIGHTTWO:		
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = -1.0f;
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = -1.0f;

					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z -= 0.001f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.008f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z += 0.001f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.008f)
								t_Att->SetAngleState(true);
							break;
					}
					if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
						_bAlpha = !_bAlpha;

					if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
					else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
					break;
				case CMiniWorker::LEFT:
				case CMiniWorker::RIGHT:
					if(t_pBody->GetRow() == CBaseObject::LEFT)
						t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
					else
						t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
					break;
				default:
					break;
			}
		}
	}
	else{
		pMiniWorker->GetBody()->SetVelocity(30.0f);
		t_pBody->SetRow(CBaseObject::LEFT);
		pMiniWorker->SetCanMove(true);
		pMiniWorker->EntityMove();

		static int _nCount = 0;
		static float _mouseAngle = 0.0f;

		// 부속품 계산
		for(int i = 0; i < pMiniWorker->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pMiniWorker->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CMiniWorker::MOUSEUNDER:		
					if(_nCount < 4){					
						switch(t_Att->GetAngleState()){
							case true:
								// Min라면
								t_Att->GetPriRot()->z -= 0.04f;
								if(t_Att->GetPriRot()->z <= D3DX_PI * 0.1f)
									t_Att->SetAngleState(false);
								break;
							case false:
								// Max라면
								t_Att->GetPriRot()->z += 0.04f;

								if(t_Att->GetPriRot()->z >= D3DX_PI * 0.3f && t_Att->GetPriRot()->z <= D3DX_PI * 0.3f + 0.04f)
									pMiniWorker->ApplyDamageEnemyToOurForce(CCharacterEntity::SPRINGUP, 500);

								if(t_Att->GetPriRot()->z >= D3DX_PI * 0.5f){								
									t_Att->SetAngleState(true);
									_nCount++;
								}
								break;
						}
					}
					else{
						pMiniWorker->GetFSM()->ChangeState(MiniWorkerReady->Instance());
						_nCount = 0;
						_mouseAngle = 0.0f;
					}
					break;
				case CMiniWorker::LIGHTONE:	
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = -1.0f;
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = -1.0f;

					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.002f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.002f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
								t_Att->SetAngleState(true);
							break;
					}
					if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
						_bAlpha = !_bAlpha;

					if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
					else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
					break;
				case CMiniWorker::LIGHTTWO:	
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = -1.0f;
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = -1.0f;

					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z -= 0.001f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.008f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z += 0.001f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.008f)
								t_Att->SetAngleState(true);
							break;
					}
					if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
						_bAlpha = !_bAlpha;

					if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
					else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
					break;
				case CMiniWorker::LEFT:
				case CMiniWorker::RIGHT:
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
					break;
				default:
					break;
			}
		}
	}

	pMiniWorker->RenderOrgan();
}

void CMiniWorkerWalkingChinAttack::Exit(CMiniWorker* pMiniWorker){
	// 부속품 계산
	for(int i = 0; i < pMiniWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pMiniWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CMiniWorker::LIGHTONE:			
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = 0.0f;
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = 0.0f;				
				break;
			case CMiniWorker::LIGHTTWO:		
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = 0.0f;
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = 0.0f;
				break;
			default:
				break;
		}
	}
}

bool CMiniWorkerWalkingChinAttack::OnMessage(CMiniWorker* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(MiniWorkerReady->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(MiniWorkerDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Escape State
///////////////////////////////////////////////////////////
void CMiniWorkerEscape::Enter(CMiniWorker* pMiniWorker){
	
}

void CMiniWorkerEscape::Execute(CMiniWorker* pMiniWorker){
	CBody* t_pBody = pMiniWorker->GetBody();
	
	pMiniWorker->CheckHealthState();

	if(pMiniWorker->GetDestination()->x + AIMgr->GetAttackRange()->_max.x - 250.0f < t_pBody->GetPriPos()->x){
		pMiniWorker->GetBody()->SetVelocity(150.0f);
		t_pBody->SetRow(CBaseObject::LEFT);
		pMiniWorker->SetCanMove(true);
		pMiniWorker->EntityMove();
	}
	else if(pMiniWorker->GetDestination()->x  + 200.0f > t_pBody->GetPriPos()->x){
		pMiniWorker->GetBody()->SetVelocity(150.0f);
		t_pBody->SetRow(CBaseObject::RIGHT);
		pMiniWorker->SetCanMove(true);
		pMiniWorker->EntityMove();
	}
	else{
		pMiniWorker->GetFSM()->ChangeState(MiniWorkerReady->Instance());
		t_pBody->SetVelocity(0.0f);
	}

	// 바디 계산
	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.05f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
	}

		switch(t_pBody->GetAngleState()){
		case true:
			// Max라면
			t_pBody->GetPriRot()->z += 0.001f;
			if(t_pBody->GetPriRot()->z >= D3DX_PI * 0.005f)
				t_pBody->SetAngleState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriRot()->z -= 0.001f;
			if(t_pBody->GetPriRot()->z <= -D3DX_PI * 0.005f)
				t_pBody->SetAngleState(true);
			break;
	}

	static bool _bAlpha = false;

	// 부속품 계산
	for(int i = 0; i < pMiniWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pMiniWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CMiniWorker::MOUSEUNDER:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.005f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.05f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.005f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CMiniWorker::LIGHTONE:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.002f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.002f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
							t_Att->SetAngleState(true);
						break;
				}
				if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
					_bAlpha = !_bAlpha;

				if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
				else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
				break;
			case CMiniWorker::LIGHTTWO:			
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z -= 0.001f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.008f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z += 0.001f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.008f)
							t_Att->SetAngleState(true);
						break;
				}
				if(t_Att->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.9f || t_Att->GetMtrlArray()->Get(0,0).Diffuse.a <= 0.4f)
					_bAlpha = !_bAlpha;

				if(_bAlpha)	t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
				else t_Att->GetMtrlArray()->Get(0,0).Diffuse.a += 0.01f;
				break;
			case CMiniWorker::LEFT:
			case CMiniWorker::RIGHT:
				t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pMiniWorker->RenderOrgan();
}

void CMiniWorkerEscape::Exit(CMiniWorker* pMiniWorker){

}

bool CMiniWorkerEscape::OnMessage(CMiniWorker* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(MiniWorkerDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
void CMiniWorkerDie::Enter(CMiniWorker* pMiniWorker){
	
}

void CMiniWorkerDie::Execute(CMiniWorker* pMiniWorker){
	CBody* t_pBody = pMiniWorker->GetBody();
		
	if(t_pBody->GetPriRot()->x >= -D3DX_PI * 0.30f){
		t_pBody->GetPriRot()->x -= 0.01f;
		t_pBody->GetPriPos()->z -= 0.4f;
		t_pBody->GetPriPos()->y -= 0.3f;
	}
	
	static bool _bAlpha = false;

	// 부속품 계산
	for(int i = 0; i < pMiniWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pMiniWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CMiniWorker::BODY:
				if(t_pBody->GetPriRot()->x >= -D3DX_PI * 0.25f){
					t_Att->GetPriSca()->x -= 0.003f;
					t_Att->GetPriSca()->y -= 0.003f;
				}
				break;
			case CMiniWorker::MOUSEOVER:
			case CMiniWorker::MOUSEUNDER:
				if(t_pBody->GetPriRot()->x >= -D3DX_PI * 0.25f){
					t_Att->GetPriSca()->x -= 0.003f;
					t_Att->GetPriSca()->y -= 0.003f;
					t_Att->GetPriPos()->y -= 0.2f;
				}
				break;
			case CMiniWorker::LIGHTONE:		
			case CMiniWorker::LIGHTTWO:			
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
				break;
			case CMiniWorker::LEFT:
			case CMiniWorker::RIGHT:
				if(t_pBody->GetPriRot()->x >= -D3DX_PI * 0.25f){
					t_Att->GetPriSca()->x -= 0.003f;
					t_Att->GetPriSca()->y -= 0.003f;
				}
				break;
			case CMiniWorker::PIPE:
				if(t_pBody->GetPriRot()->x >= -D3DX_PI * 0.25f){
					t_Att->GetPriSca()->x -= 0.003f;
					t_Att->GetPriSca()->y -= 0.003f;
					t_Att->GetPriPos()->y -= 1.0f;
				}
				break;
			default:
				break;
		}
	}

	pMiniWorker->RenderOrgan();
}

void CMiniWorkerDie::Exit(CMiniWorker* pMiniWorker){

}

bool CMiniWorkerDie::OnMessage(CMiniWorker* agent, const Telegram& msg){
	return false;
}

////////////////////////////////////////////////////
// ItemEat State
///////////////////////////////////////////////////////////
void CMiniWorkerItemEat::Enter(CMiniWorker* pMiniWorker){
	_nCount = 0;
}

void CMiniWorkerItemEat::Execute(CMiniWorker* pMiniWorker){
	CBody* t_pBody = pMiniWorker->GetBody();

	t_pBody->SetVelocity(0.0f);
	pMiniWorker->SetCanMove(false);

	// 부속품 계산
	for(int i = 0; i < pMiniWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pMiniWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CMiniWorker::MOUSEUNDER:
				if(_nCount < 4){
					if(_mouseAngle < D3DX_PI * 0.5f){
						t_Att->GetPriRot()->z += 0.03f;
						_mouseAngle += 0.03f;
					}
					else{
						switch(t_Att->GetAngleState()){
							case true:
								// Min라면
								t_Att->GetPriRot()->z -= 0.02f;
								if(t_Att->GetPriRot()->z <= D3DX_PI * 0.4f)
									t_Att->SetAngleState(false);
								break;
							case false:
								// Max라면
								t_Att->GetPriRot()->z += 0.02f;
								if(t_Att->GetPriRot()->z >= D3DX_PI * 0.5f){
									t_Att->SetAngleState(true);
									_nCount++;
								}
								break;
						}
					}
				}
				else{
					t_Att->GetPriRot()->z -= 0.03f;
					if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.05f)
						pMiniWorker->GetFSM()->ChangeState(MiniWorkerReady->Instance());
				}
				break;					
			case CMiniWorker::LIGHTONE:		
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.002f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.002f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CMiniWorker::LIGHTTWO:	
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z -= 0.001f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.008f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z += 0.001f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.008f)
							t_Att->SetAngleState(true);
						break;
				}
				break;
			case CMiniWorker::LEFT:
			case CMiniWorker::RIGHT:
				t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pMiniWorker->RenderOrgan();
}

void CMiniWorkerItemEat::Exit(CMiniWorker* pMiniWorker){

}

bool CMiniWorkerItemEat::OnMessage(CMiniWorker* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Event:
//			agent->GetFSM()->ChangeState(MiniWorkerInEvent->Instance());
			return true;
		case Msg_Attack:
//			agent->GetFSM()->ChangeState(MiniWorkerAttack->Instance());
			return true;
		default:
			return false;
	}
}