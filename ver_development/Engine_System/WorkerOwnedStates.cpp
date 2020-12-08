#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Ready State
///////////////////////////////////////////////////////////
void CWorkerReady::Enter(CWorker* pWorker){
	pWorker->GetBody()->SetVelocity(20.0f);

	_setTimer = false;
}

void CWorkerReady::Execute(CWorker* pWorker){
	CBody* t_pBody = pWorker->GetBody();
	
	pWorker->CheckHealthState();

	if(pWorker->GetDestination()->x + 250.0f < t_pBody->GetPriPos()->x){
		pWorker->GetBody()->SetVelocity(30.0f);
		t_pBody->SetRow(CBaseObject::LEFT);
		pWorker->SetCanMove(true);
		pWorker->EntityMove();
	}
	else if(pWorker->GetDestination()->x  + 200.0f > t_pBody->GetPriPos()->x){
		pWorker->GetBody()->SetVelocity(30.0f);
		t_pBody->SetRow(CBaseObject::RIGHT);
		pWorker->SetCanMove(true);
		pWorker->EntityMove();
	}
	else{
		if(_setTimer == false && CameraMgr->GetMode() == CCameraManager::COMBAT){
			pWorker->SetAttackTime(pWorker->GetAttackTimeGap());
			_setTimer = true;
		}

		pWorker->SetCanMove(false);
		t_pBody->SetRow(CBaseObject::LEFT);
		t_pBody->SetVelocity(0.0f);

		if(pWorker->GetAttackTime()->IsElapseTimer()){
			if(CameraMgr->GetMode() == CCameraManager::COMBAT){
				pWorker->GetBody()->SetVelocity(0.0f);
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pWorker->ID(), pWorker->ID(), Msg_Attack, NO_ADDITIONAL_INFO);
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
	for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWorker::MOUSEUNDER:			
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
			case CWorker::LIGHTONE:		
				if(!pWorker->GetAttackTime()->GetElapseTime() == 0){
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = -((float)pWorker->GetAttackTime()->GetElapseTime() * (1.0f/pWorker->GetAttackTimeGap()));
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = -((float)pWorker->GetAttackTime()->GetElapseTime() * (1.0f/pWorker->GetAttackTimeGap()));
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
			case CWorker::LIGHTTWO:			
				if(!pWorker->GetAttackTime()->GetElapseTime() == 0){					
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = -((float)pWorker->GetAttackTime()->GetElapseTime() * (1.0f/pWorker->GetAttackTimeGap()));
					t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = -((float)pWorker->GetAttackTime()->GetElapseTime() * (1.0f/pWorker->GetAttackTimeGap()));
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
			case CWorker::LEFT:
			case CWorker::RIGHT:
				if(t_pBody->GetRow() == CBaseObject::LEFT)
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				else
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pWorker->RenderOrgan();
}

void CWorkerReady::Exit(CWorker* pWorker){
	
}

bool CWorkerReady::OnMessage(CWorker* agent, const Telegram& msg){
	int t_nTemp = rand() % 10;

	switch(msg.Msg){
		case Msg_Event:
			agent->GetFSM()->ChangeState(WorkerEvent->Instance());
			return true;
		case Msg_Attack:
			if(t_nTemp < 4)
				agent->GetFSM()->ChangeState(WorkerChinAttack->Instance());
			else if(t_nTemp < 7)
				agent->GetFSM()->ChangeState(WorkerWalkingChinAttack->Instance());
			else if(t_nTemp < 10)
				agent->GetFSM()->ChangeState(WorkerChargeAttack->Instance());

			return true;
		case Msg_Healthful:
			agent->SetHealthState(CCharacterEntity::HEALTHFUL);
			agent->GetFSM()->ChangeState(WorkerEscape->Instance());
			return true;
		case Msg_Normal:
			agent->SetHealthState(CCharacterEntity::NORMAL);
			agent->GetFSM()->ChangeState(WorkerEscape->Instance());
			return true;
		case Msg_Weak:
			agent->SetHealthState(CCharacterEntity::WEAK);
			agent->GetFSM()->ChangeState(WorkerEscape->Instance());
			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(WorkerDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
void CWorkerEvent::Enter(CWorker* pWorker){
	
}

void CWorkerEvent::Execute(CWorker* pWorker){
	// 바디 계산
	CBody* t_pBody = pWorker->GetBody();
	
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
	for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWorker::MOUSEUNDER:			
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
			case CWorker::LIGHTONE:			
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
			case CWorker::LIGHTTWO:			
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
			case CWorker::LEFT:
			case CWorker::RIGHT:
				if(t_pBody->GetRow() == CBaseObject::LEFT)
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				else
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pWorker->RenderOrgan();
}

void CWorkerEvent::Exit(CWorker* pWorker){

}

bool CWorkerEvent::OnMessage(CWorker* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(WorkerReady->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Normal Attack State
///////////////////////////////////////////////////////////
void CWorkerChinAttack::Enter(CWorker* pWorker){
	_moveDistance = 0.0f;

	pWorker->SetMinDamage(9.0f);
	pWorker->SetMaxDamage(13.0f);

	if(AIMgr->AILiveCheckToYawoAndKirit()){
		_requireDistance = 300.0f;
	}
	else
		_requireDistance = 30.0f;
}

void CWorkerChinAttack::Execute(CWorker* pWorker){
	CBody* t_pBody = pWorker->GetBody();
	
	pWorker->CheckHealthState();

	// 아이템 먹기
	if(pWorker->ComputeBoundMouseAndItem())
		pWorker->GetFSM()->ChangeState(WorkerItemEat->Instance());

	static bool _bAlpha = false;

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
		float t_Distance = 0.0f;
		pWorker->SetCanMove(true);
		_moveDistance += pWorker->EntityMove(&t_Distance);

		if(pWorker->GetCanAttack())
			_moveDistance = _requireDistance + 1.0f;

		// 부속품 계산
		for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CWorker::MOUSEUNDER:			
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
				case CWorker::LIGHTONE:		
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
				case CWorker::LIGHTTWO:			
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
				case CWorker::LEFT:
				case CWorker::RIGHT:
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

		static int _nCount = 0;
		static float _mouseAngle = 0.0f;

		// 부속품 계산
		for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CWorker::MOUSEUNDER:		
					if(_nCount < 3){					
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
									pWorker->ApplyDamageEnemyToOurForce(CCharacterEntity::SPRINGUP, 1000);

								if(t_Att->GetPriRot()->z >= D3DX_PI * 0.5f){								
									t_Att->SetAngleState(true);
									_nCount++;
								}
								break;
						}
					}
					else{
						pWorker->GetFSM()->ChangeState(WorkerReady->Instance());
						_nCount = 0;
						_mouseAngle = 0.0f;
					}
					break;
				case CWorker::LIGHTONE:		
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
				case CWorker::LIGHTTWO:	
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
				case CWorker::LEFT:
				case CWorker::RIGHT:
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
					break;
				default:
					break;
			}
		}
	}

	pWorker->RenderOrgan();
}

void CWorkerChinAttack::Exit(CWorker* pWorker){
	// 부속품 계산
	for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWorker::LIGHTONE:			
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = 0.0f;
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = 0.0f;				
				break;
			case CWorker::LIGHTTWO:		
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = 0.0f;
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = 0.0f;
				break;
			default:
				break;
		}
	}
}

bool CWorkerChinAttack::OnMessage(CWorker* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(WorkerReady->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(WorkerDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Walking Attack State
///////////////////////////////////////////////////////////
void CWorkerWalkingChinAttack::Enter(CWorker* pWorker){
	_moveDistance = 0.0f;

	pWorker->SetMinDamage(6.0f);
	pWorker->SetMaxDamage(9.0f);

	if(AIMgr->AILiveCheckToYawoAndKirit()){
		_requireDistance = 500.0f;
	}
	else
		_requireDistance = 30.0f;

	pWorker->GetBody()->SetVelocity(20.0f);
}

void CWorkerWalkingChinAttack::Execute(CWorker* pWorker){
	CBody* t_pBody = pWorker->GetBody();
	
	static bool _bAlpha = false;

	pWorker->CheckHealthState();

	// 아이템 먹기
	if(pWorker->ComputeBoundMouseAndItem())
		pWorker->GetFSM()->ChangeState(WorkerItemEat->Instance());

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
		pWorker->SetCanMove(true);

		if(pWorker->GetCanAttack())
			_moveDistance = _requireDistance + 1.0f;

		float t_Distance = 0.0f;
		_moveDistance += pWorker->EntityMove(&t_Distance);

		// 부속품 계산
		for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CWorker::MOUSEUNDER:			
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
				case CWorker::LIGHTONE:			
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
				case CWorker::LIGHTTWO:		
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
				case CWorker::LEFT:
				case CWorker::RIGHT:
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
		pWorker->GetBody()->SetVelocity(20.0f);
		t_pBody->SetRow(CBaseObject::LEFT);
		pWorker->SetCanMove(true);
		pWorker->EntityMove();

		static int _nCount = 0;
		static float _mouseAngle = 0.0f;

		// 부속품 계산
		for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CWorker::MOUSEUNDER:		
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
									pWorker->ApplyDamageEnemyToOurForce(CCharacterEntity::SPRINGUP, 1000);

								if(t_Att->GetPriRot()->z >= D3DX_PI * 0.5f){								
									t_Att->SetAngleState(true);
									_nCount++;
								}
								break;
						}
					}
					else{
						pWorker->GetFSM()->ChangeState(WorkerReady->Instance());
						_nCount = 0;
						_mouseAngle = 0.0f;
					}
					break;
				case CWorker::LIGHTONE:	
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
				case CWorker::LIGHTTWO:	
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
				case CWorker::LEFT:
				case CWorker::RIGHT:
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
					break;
				default:
					break;
			}
		}
	}

	pWorker->RenderOrgan();
}

void CWorkerWalkingChinAttack::Exit(CWorker* pWorker){
	// 부속품 계산
	for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWorker::LIGHTONE:			
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = 0.0f;
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = 0.0f;				
				break;
			case CWorker::LIGHTTWO:		
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = 0.0f;
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = 0.0f;
				break;
			default:
				break;
		}
	}
}

bool CWorkerWalkingChinAttack::OnMessage(CWorker* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(WorkerReady->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(WorkerDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Charge Attack State
///////////////////////////////////////////////////////////
void CWorkerChargeAttack::Enter(CWorker* pWorker){
	_moveDistance = 0.0f;

	pWorker->SetMinDamage(23.0f);
	pWorker->SetMaxDamage(34.0f);

	if(AIMgr->AILiveCheckToYawoAndKirit()){
		_requireDistance = 300.0f;
	}
	else
		_requireDistance = 30.0f;

	_timer = NULL;
}

void CWorkerChargeAttack::Execute(CWorker* pWorker){
	CBody* t_pBody = pWorker->GetBody();
	
	pWorker->CheckHealthState();

	static bool _bAlpha = false;

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
		float t_Distance = 0.0f;
		pWorker->SetCanMove(true);
		_moveDistance += pWorker->EntityMove(&t_Distance);

		if(pWorker->GetCanAttack())
			_moveDistance = _requireDistance + 1.0f;

		// 부속품 계산
		for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CWorker::MOUSEUNDER:			
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
				case CWorker::LIGHTONE:		
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
				case CWorker::LIGHTTWO:			
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
				case CWorker::LEFT:
				case CWorker::RIGHT:
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
		t_pBody->SetVelocity(90.0f);

		if(_timer != NULL){
			if(!_timer->IsElapseTimer()){
				pWorker->ApplyDamageEnemyToOurForce(CCharacterEntity::SPRINGUP, 1000);
				pWorker->SetCanMove(true);
				pWorker->EntityMove();
			}
		}

		static CTimer* t_timer = NULL;
		static float _mouseAngle = 0.0f;

		// 부속품 계산
		for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CWorker::MOUSEUNDER:		
					if(_timer == NULL){					
						switch(t_Att->GetAngleState()){
							case true:
								if(t_timer->IsElapseTimer()){
									_timer = new CTimer(1000);
								}
								break;
							case false:
								// Max라면
								t_Att->GetPriRot()->z += 0.04f;

								if(t_Att->GetPriRot()->z >= D3DX_PI * 0.3f){								
									t_Att->SetAngleState(true);
									t_timer = new CTimer(500);
								}
								break;
						}
					}
					else{
						if(_timer->IsElapseTimer()){
							switch(t_Att->GetAngleState()){
								case true:
									// Min라면
									t_Att->GetPriRot()->z -= 0.04f;
									if(t_Att->GetPriRot()->z <= D3DX_PI * 0.1f)
										t_Att->SetAngleState(false);
									break;
								case false:
									pWorker->GetFSM()->ChangeState(WorkerReady->Instance());
									_mouseAngle = 0.0f;
									break;
							}	
						}
					}
					break;
				case CWorker::LIGHTONE:		
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
				case CWorker::LIGHTTWO:	
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
				case CWorker::LEFT:
				case CWorker::RIGHT:
					t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
					break;
				default:
					break;
			}
		}
	}

	pWorker->RenderOrgan();
}

void CWorkerChargeAttack::Exit(CWorker* pWorker){
	delete _timer;
	_timer = NULL;

	// 부속품 계산
	for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWorker::LIGHTONE:			
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = 0.0f;
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = 0.0f;				
				break;
			case CWorker::LIGHTTWO:		
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.g = 0.0f;
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.b = 0.0f;
				break;
			default:
				break;
		}
	}
}

bool CWorkerChargeAttack::OnMessage(CWorker* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(WorkerReady->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(WorkerDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Escape State
///////////////////////////////////////////////////////////
void CWorkerEscape::Enter(CWorker* pWorker){
	
}

void CWorkerEscape::Execute(CWorker* pWorker){
	CBody* t_pBody = pWorker->GetBody();
	
	pWorker->CheckHealthState();

	if(pWorker->GetDestination()->x + AIMgr->GetAttackRange()->_max.x - 250.0f < t_pBody->GetPriPos()->x){
		pWorker->GetBody()->SetVelocity(150.0f);
		t_pBody->SetRow(CBaseObject::LEFT);
		pWorker->SetCanMove(true);
		pWorker->EntityMove();
	}
	else if(pWorker->GetDestination()->x  + 200.0f > t_pBody->GetPriPos()->x){
		pWorker->GetBody()->SetVelocity(150.0f);
		t_pBody->SetRow(CBaseObject::RIGHT);
		pWorker->SetCanMove(true);
		pWorker->EntityMove();
	}
	else{
		pWorker->GetFSM()->ChangeState(WorkerReady->Instance());
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
	for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWorker::MOUSEUNDER:			
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
			case CWorker::LIGHTONE:			
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
			case CWorker::LIGHTTWO:			
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
			case CWorker::LEFT:
			case CWorker::RIGHT:
				t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pWorker->RenderOrgan();
}

void CWorkerEscape::Exit(CWorker* pWorker){

}

bool CWorkerEscape::OnMessage(CWorker* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(WorkerDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
void CWorkerDie::Enter(CWorker* pWorker){
	
}

void CWorkerDie::Execute(CWorker* pWorker){
	CBody* t_pBody = pWorker->GetBody();
		
	if(t_pBody->GetPriRot()->x >= -D3DX_PI * 0.30f){
		t_pBody->GetPriRot()->x -= 0.008f;
		t_pBody->GetPriPos()->z -= 0.8f;
		t_pBody->GetPriPos()->y -= 1.1f;
	}
	
	static bool _bAlpha = false;

	// 부속품 계산
	for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWorker::BODY:
				if(t_pBody->GetPriRot()->x >= -D3DX_PI * 0.25f){
					t_Att->GetPriSca()->x -= 0.003f;
					t_Att->GetPriSca()->y -= 0.003f;
				}
				break;
			case CWorker::MOUSEOVER:
			case CWorker::MOUSEUNDER:
				if(t_pBody->GetPriRot()->x >= -D3DX_PI * 0.25f){
					t_Att->GetPriSca()->x -= 0.003f;
					t_Att->GetPriSca()->y -= 0.003f;
				}
				break;
			case CWorker::LIGHTONE:		
			case CWorker::LIGHTTWO:			
				t_Att->GetMtrlArray()->Get(0,0).Diffuse.a -= 0.01f;
				break;
			case CWorker::LEFT:
			case CWorker::RIGHT:
				if(t_pBody->GetPriRot()->x >= -D3DX_PI * 0.25f){
					t_Att->GetPriSca()->x -= 0.003f;
					t_Att->GetPriSca()->y -= 0.003f;
				}
				break;
			case CWorker::PIPE:
				if(t_pBody->GetPriRot()->x >= -D3DX_PI * 0.25f){
					t_Att->GetPriSca()->x -= 0.003f;
					t_Att->GetPriSca()->y -= 0.003f;
					t_Att->GetPriPos()->y -= 0.8f;
				}
				break;
			default:
				break;
		}
	}

	pWorker->RenderOrgan();
}

void CWorkerDie::Exit(CWorker* pWorker){

}

bool CWorkerDie::OnMessage(CWorker* agent, const Telegram& msg){
	return false;
}

////////////////////////////////////////////////////
// ItemEat State
///////////////////////////////////////////////////////////
void CWorkerItemEat::Enter(CWorker* pWorker){
	_nCount = 0;
}

void CWorkerItemEat::Execute(CWorker* pWorker){
	CBody* t_pBody = pWorker->GetBody();

	t_pBody->SetVelocity(0.0f);
	pWorker->SetCanMove(false);

	// 부속품 계산
	for(int i = 0; i < pWorker->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pWorker->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CWorker::MOUSEUNDER:
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
						pWorker->GetFSM()->ChangeState(WorkerReady->Instance());
				}
				break;					
			case CWorker::LIGHTONE:			
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
			case CWorker::LIGHTTWO:		
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
			case CWorker::LEFT:
			case CWorker::RIGHT:
				t_Att->GetPriRot()->z -= D3DX_PI * 0.02f;
				break;
			default:
				break;
		}
	}

	pWorker->RenderOrgan();
}

void CWorkerItemEat::Exit(CWorker* pWorker){

}

bool CWorkerItemEat::OnMessage(CWorker* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Event:
//			agent->GetFSM()->ChangeState(WorkerInEvent->Instance());
			return true;
		case Msg_Attack:
//			agent->GetFSM()->ChangeState(WorkerAttack->Instance());
			return true;
		default:
			return false;
	}
}