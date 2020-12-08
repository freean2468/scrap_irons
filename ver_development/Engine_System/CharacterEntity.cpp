#include "../BaseHeader.h"

CCharacterEntity::CCharacterEntity(int id):COrganEntity(id){
	_tribeType = NOTHING;

	_attackBound._min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_attackBound._max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_entityBound._min = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_entityBound._max = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	_minDamage = 0.0f;
	_maxDamage = 0.0f;

	_force = 0.0f;

	_destination = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	_canMove = true;
	_canAttack = false;

	_live = true;

	_maxHealthy = _nowHealthy = 0;
	_healthState = NONE;
	_def = 1.0f;

	_boundFont = d3d::IniFont(13, 6, 300, false, "맑은 고딕");

	_distance = 0.0f;

	_lookEnemy = false;

	_attackTimeGap = 0;
	_attackTime = new CTimer();

	_applyTime = new CTimer(0);
}

CCharacterEntity::~CCharacterEntity(){
	d3d::Release<ID3DXFont*>(_boundFont);	
	d3d::Delete< CTimer* >(_attackTime);
}

void CCharacterEntity::FaceToDestination(){
	// deltaS = v * deltaT
	// 벡터를 이용, 방향을 알아내야 한다.
	// 방향 = 벡터의 정규화
	float t_fDeltaX = _destination.x - GetBody()->GetPriPos()->x;
	float t_fDeltaY = _destination.y - GetBody()->GetPriPos()->y;
	float t_fDeltaZ = _destination.z - GetBody()->GetPriPos()->z;

	// 거리 == 벡터의 크기 == 힘
	float t_fDistance = 0.0f;
	D3DXVECTOR3 t_vHeading = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	t_fDistance = sqrt((t_fDeltaX * t_fDeltaX) + (t_fDeltaY * t_fDeltaY) + (t_fDeltaZ * t_fDeltaZ));

	if(t_fDistance > 0.0f){
		// a = f / m;
		float t_fAce = t_fDistance * 300.0f;

		float t_fVel = t_fAce * SYSTEM_FRAME_INTERVAL_VER_60;

		if(t_fVel >= 200.0f) t_fVel = 200.0f;

		t_vHeading.x = t_fDeltaX / t_fDistance;
		t_vHeading.y = t_fDeltaY / t_fDistance;
		t_vHeading.z = t_fDeltaZ / t_fDistance;

		GetBody()->GetPriPos()->x += (t_vHeading.x * t_fVel) * SYSTEM_FRAME_INTERVAL_VER_60;
		GetBody()->GetPriPos()->y += (t_vHeading.y * t_fVel) * SYSTEM_FRAME_INTERVAL_VER_60;
		GetBody()->GetPriPos()->z += (t_vHeading.z * t_fVel) * SYSTEM_FRAME_INTERVAL_VER_60;
	}	
}

void CCharacterEntity::CheckHealthState(){
	if(GetMaxHealthy() >= GetNowHealthy() && GetMaxHealthy() * (2.0f/3.0f) < GetNowHealthy() && GetHealthState() != HEALTHFUL){
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), ID(), Msg_Healthful, NO_ADDITIONAL_INFO);
	}
	else if(GetMaxHealthy() * (2.0f/3.0f) >= GetNowHealthy() && GetMaxHealthy() * (1.0f/3.0f) < GetNowHealthy() && GetHealthState() != NORMAL){
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), ID(), Msg_Normal, NO_ADDITIONAL_INFO);
	}
	else if(GetMaxHealthy() * (1.0f/3.0f) >= GetNowHealthy() && GetNowHealthy() > 0.0f && GetHealthState() != WEAK){
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), ID(), Msg_Weak, NO_ADDITIONAL_INFO);
	}
	else if(GetNowHealthy() <= 0.0f){
		SetLive(false);
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), ID(), Msg_Die, NO_ADDITIONAL_INFO);
	}
}

bool CCharacterEntity::ComputeEntityBound(CCharacterEntity* p_pEntity){
	if(GetBody()->GetPriPos()->x < p_pEntity->GetBody()->GetPriPos()->x){
		if(GetEntityBound()->_max.x >= p_pEntity->GetEntityBound()->_min.x &&
			GetEntityBound()->_max.y >= p_pEntity->GetEntityBound()->_min.y){
			return true;
		}
	}
	else{
		if(GetEntityBound()->_min.x <= p_pEntity->GetEntityBound()->_max.x &&
			GetEntityBound()->_max.y >= p_pEntity->GetEntityBound()->_min.y){
			return true;
		}
	}

	return false;
}

void CCharacterEntity::ComputeEntityBound(){
	CDListIterator<CCharacterEntity*> itrOur = AIMgr->GetOurForceList();

	CBody* t_pOurForceBody;
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	
	if(AIMgr->GetCommandType() == CAIManager::DEFENSE){
		for(itrOur.Start(); itrOur.Valid(); itrOur.Forth()){
			if(itrOur.Item()->GetLive() == true){
				t_pOurForceBody = itrOur.Item()->GetBody();

				switch(StageMgr->GetStageType()){
					case CStageManager::DUSTBRIDGE:
						if(t_pHeroBody->GetPriPos()->x > t_pOurForceBody->GetPriPos()->x)
							itrOur.Item()->SetForce(20.0f);
						else
							itrOur.Item()->SetForce(-20.0f);
						break;
					default:
						if(t_pHeroBody->GetPriPos()->x > t_pOurForceBody->GetPriPos()->x)
							itrOur.Item()->SetForce(20.0f);
						else
							itrOur.Item()->SetForce(-20.0f);
						break;
				}
				itrOur.Item()->SetCanMove(false);
			}
			else
				itrOur.Item()->SetCanMove(false);
		}
		return;
	}

	// 히어로 충돌 체크
	if(GetLive()){
		AIMgr->GetHero()->SetForce(0.0f);

		if(GetBody()->GetPriPos()->x > t_pHeroBody->GetPriPos()->x){						
			if(GetEntityBound()->_min.x <= AIMgr->GetHero()->GetEntityBound()->_max.x){							
				if(t_pHeroBody->GetRow() == GetBody()->GetRow()){
					AIMgr->GetHero()->SetForce(GetBody()->GetVelocity());
					AIMgr->GetHero()->SetCanMove(false);
				}
			}
			else if(GetEntityBound()->_min.x > AIMgr->GetHero()->GetEntityBound()->_max.x &&
				GetAttackBound()->_min.x <= AIMgr->GetHero()->GetEntityBound()->_max.x){
				if(GetBody()->GetRow() == CBaseObject::RIGHT){
					if(t_pHeroBody->GetRow() == CBaseObject::RIGHT){											
						if(GetBody()->GetVelocity() <= t_pHeroBody->GetVelocity()){							
							AIMgr->GetHero()->SetForce(GetBody()->GetVelocity());
							AIMgr->GetHero()->SetCanMove(false);
						}
					}
				}
				else if(GetBody()->GetRow() == CBaseObject::LEFT){
					if(t_pHeroBody->GetRow() == CBaseObject::RIGHT){
						AIMgr->GetHero()->SetForce(-GetBody()->GetVelocity());
						AIMgr->GetHero()->SetCanMove(false);
					}
					else{
						if(GetBody()->GetVelocity() >= t_pHeroBody->GetVelocity()){
							AIMgr->GetHero()->SetForce(-GetBody()->GetVelocity());
							AIMgr->GetHero()->SetCanMove(false);							
						}
					}
				}
			}
		}
		else{						
			if(GetEntityBound()->_max.x >= AIMgr->GetHero()->GetEntityBound()->_min.x){
				// AttackBound와 EntityBound사이에서 자연스러운 움직임 연출
				if(t_pHeroBody->GetRow() == GetBody()->GetRow()){
					AIMgr->GetHero()->SetForce(GetBody()->GetVelocity());
					AIMgr->GetHero()->SetCanMove(false);
				}
			}
			else if(GetAttackBound()->_max.x >= AIMgr->GetHero()->GetEntityBound()->_min.x &&
				GetEntityBound()->_max.x < AIMgr->GetHero()->GetEntityBound()->_min.x){
				if(GetBody()->GetRow() == CBaseObject::RIGHT){
					if(t_pHeroBody->GetRow() == CBaseObject::LEFT){	
						AIMgr->GetHero()->SetForce(GetBody()->GetVelocity());
						AIMgr->GetHero()->SetCanMove(false);
					}
				}
				else if(GetBody()->GetRow() == CBaseObject::LEFT){
					if(t_pHeroBody->GetRow() == CBaseObject::LEFT){	
						if(t_pHeroBody->GetVelocity() >= GetBody()->GetVelocity()){
							AIMgr->GetHero()->SetForce(-GetBody()->GetVelocity());
							AIMgr->GetHero()->SetCanMove(false);
						}
					}
				}
			}
		}
	}
	else{
		AIMgr->GetHero()->SetForce(0.0f);
	}

	// 아군 충돌 체크
	for(itrOur.Start(); itrOur.Valid(); itrOur.Forth()){
		if(itrOur.Item()->GetOwner() == CBaseObject::TINKLE) continue;
		if(itrOur.Item()->GetOwner() == CBaseObject::YAWO) continue;

		t_pOurForceBody = itrOur.Item()->GetBody();

		if(GetLive()){
			if(itrOur.Item()->GetLive()){
				switch(itrOur.Item()->GetOwner()){
					case CBaseObject::TINKLE:
						break;
					default:
						if(GetBody()->GetPriPos()->x > t_pOurForceBody->GetPriPos()->x){						
							if(GetEntityBound()->_min.x <= itrOur.Item()->GetEntityBound()->_max.x){							
								// AttackBound와 EntityBound사이에서 자연스러운 움직임 연출
								if(t_pOurForceBody->GetRow() == GetBody()->GetRow()){
									itrOur.Item()->SetForce(GetBody()->GetVelocity());
									itrOur.Item()->SetCanMove(false);
								}
								else{
									itrOur.Item()->SetForce(0.0f);
									itrOur.Item()->SetCanMove(true);
								}
								continue;	
							}
							else if(GetEntityBound()->_min.x > itrOur.Item()->GetEntityBound()->_max.x &&
								GetAttackBound()->_min.x <= itrOur.Item()->GetEntityBound()->_max.x){
								if(GetBody()->GetRow() == CBaseObject::RIGHT){
									if(t_pOurForceBody->GetRow() == CBaseObject::LEFT){								
										itrOur.Item()->SetForce(0.0f);
										itrOur.Item()->SetCanMove(true);
									}
									else{										
										if(GetBody()->GetVelocity() > t_pOurForceBody->GetVelocity()){
											itrOur.Item()->SetForce(0.0f);
											itrOur.Item()->SetCanMove(true);
										}
										else{
											if(itrOur.Item()->GetOwner() == CBaseObject::WOOWO){
												itrOur.Item()->SetForce(0.0f);
												itrOur.Item()->SetCanMove(true);
											}												
											else{
												itrOur.Item()->SetForce(GetBody()->GetVelocity());
												itrOur.Item()->SetCanMove(false);
											}
										}
									}
									continue;
								}
								else if(GetBody()->GetRow() == CBaseObject::LEFT){
									if(t_pOurForceBody->GetRow() == CBaseObject::LEFT){								
										itrOur.Item()->SetForce(0.0f);
										itrOur.Item()->SetCanMove(true);
									}
									else{										
										itrOur.Item()->SetForce(-GetBody()->GetVelocity());
										itrOur.Item()->SetCanMove(false);
									}
									continue;
								}
							}
						}
						else{						
							if(GetEntityBound()->_max.x >= itrOur.Item()->GetEntityBound()->_min.x){
								// AttackBound와 EntityBound사이에서 자연스러운 움직임 연출
								if(t_pOurForceBody->GetRow() == GetBody()->GetRow()){
									itrOur.Item()->SetForce(GetBody()->GetVelocity());
									itrOur.Item()->SetCanMove(false);
								}
								else{
									itrOur.Item()->SetForce(0.0f);
									itrOur.Item()->SetCanMove(true);
								}
								continue;
							}
							else if(GetAttackBound()->_max.x >= itrOur.Item()->GetEntityBound()->_min.x &&
								GetEntityBound()->_max.x < itrOur.Item()->GetEntityBound()->_min.x){
								if(GetBody()->GetRow() == CBaseObject::RIGHT){
									if(t_pOurForceBody->GetRow() == CBaseObject::LEFT){	
										itrOur.Item()->SetForce(GetBody()->GetVelocity());
										itrOur.Item()->SetCanMove(false);
									}
									else{																	
										itrOur.Item()->SetForce(0.0f);
										itrOur.Item()->SetCanMove(true);
									}
									continue;
								}
								else if(GetBody()->GetRow() == CBaseObject::LEFT){
									if(t_pOurForceBody->GetRow() == CBaseObject::LEFT){	
										if(t_pOurForceBody->GetVelocity() < GetBody()->GetVelocity()){
											itrOur.Item()->SetForce(0.0f);
											itrOur.Item()->SetCanMove(true);
										}
										else{
											itrOur.Item()->SetForce(-GetBody()->GetVelocity());
											itrOur.Item()->SetCanMove(false);
										}
									}
									else{									
										itrOur.Item()->SetForce(0.0f);
										itrOur.Item()->SetCanMove(true);
									}
									continue;
								}
							}
						}
						break;
				}	
				itrOur.Item()->SetCanMove(true);
			}
		}
		else{
			itrOur.Item()->SetCanMove(true);
		}
	}
}

void CCharacterEntity::ComputeDamageBound(){
	CDListIterator<CCharacterEntity*> itrOur = AIMgr->GetOurForceList();

	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pOurForceBody;
	
	SetCanAttack(false);

	// Hero
	if(GetLive()){
		if(GetBody()->GetPriPos()->x > t_pHeroBody->GetPriPos()->x){
			if(GetAttackBound()->_min.x <= AIMgr->GetHero()->GetEntityBound()->_max.x)
				SetCanAttack(true);
		}
		else{
			if(GetAttackBound()->_max.x >= AIMgr->GetHero()->GetEntityBound()->_min.x)
				SetCanAttack(true);
		}
	}

	// 아군
	for(itrOur.Start(); itrOur.Valid(); itrOur.Forth()){
		if(itrOur.Item()->GetOwner() == CBaseObject::TINKLE) continue;

		t_pOurForceBody = itrOur.Item()->GetBody();

		if(GetLive()){
			if(itrOur.Item()->GetLive()){
				switch(itrOur.Item()->GetOwner()){
					case CBaseObject::TINKLE:
						break;
					default:
						if(GetBody()->GetPriPos()->x > t_pOurForceBody->GetPriPos()->x){
							if(GetAttackBound()->_min.x <= itrOur.Item()->GetAttackBound()->_max.x){
								itrOur.Item()->SetCanAttack(true);

								itrOur.Item()->SetDistance(abs(GetAttackBound()->_min.x - t_pOurForceBody->GetPriPos()->x));

								if(itrOur.Item()->GetOwner() == CBaseObject::YAWO){
									if(GetAttackBound()->_min.x <= itrOur.Item()->GetEntityBound()->_max.x)
										SetCanAttack(true);
								}
								else
									SetCanAttack(true);
								
								continue;
							}
						}
						else{
							if(GetAttackBound()->_max.x >= itrOur.Item()->GetAttackBound()->_min.x){
								itrOur.Item()->SetCanAttack(true);

								itrOur.Item()->SetDistance(abs(GetAttackBound()->_max.x - t_pOurForceBody->GetPriPos()->x));

								if(itrOur.Item()->GetOwner() == CBaseObject::YAWO){
									if(GetAttackBound()->_max.x >= itrOur.Item()->GetEntityBound()->_min.x)
										SetCanAttack(true);
								}
								else
									SetCanAttack(true);
								
								continue;
							}
						}
						break;
				}		
				itrOur.Item()->SetCanAttack(false);
				itrOur.Item()->SetForce(0.0f);
			}
		}
		else{
			itrOur.Item()->SetCanAttack(false);
			SetCanAttack(false);
			itrOur.Item()->SetForce(0.0f);
		}
	}
}

bool CCharacterEntity::EntityMove(float* op_pDeltaDistance){
	// a = f / m;
	float t_fAce;

	float t_fVel;

	if(GetLive()){
		if(GetCanMove()){
			t_fAce = (_body->GetVelocity() + GetForce()) * 400.0f;

			t_fVel = t_fAce * SYSTEM_FRAME_INTERVAL_VER_60;

			if(_body->GetRow() == CBaseObject::LEFT){
				_body->GetPriPos()->x -= t_fVel * SYSTEM_FRAME_INTERVAL_VER_60;
			}
			else if(_body->GetRow() == CBaseObject::RIGHT){
				_body->GetPriPos()->x += t_fVel * SYSTEM_FRAME_INTERVAL_VER_60;
			}
			
			if(op_pDeltaDistance)
				*op_pDeltaDistance = t_fVel * SYSTEM_FRAME_INTERVAL_VER_60;

			return true;
		}
		else{
			t_fAce = GetForce() * 400.0f;

			t_fVel = t_fAce * SYSTEM_FRAME_INTERVAL_VER_60;

			_body->GetPriPos()->x += t_fVel * SYSTEM_FRAME_INTERVAL_VER_60;
		}
	}
	return false;
}

bool CCharacterEntity::EntityAttackToOurForce(){
	if(GetCanAttack()){
		ApplyDamageEnemyToOurForce();
		SetLookEnemy(false);
		return true;
	}
	return false;
}

bool CCharacterEntity::EntityAttackToEnemy(){
	if(GetCanAttack()){
		ApplyDamageOurForceToEnemy();
		SetLookEnemy(false);
		return true;
	}
	return false;
}

void CCharacterEntity::Damaged(float p_fX, float p_fY, int p_nDamage){
	if(GetApplyTime()->IsElapseTimer()){
		int t_nComputedDamage = (int)((1.0f/_def) * (float)p_nDamage); 
		_nowHealthy -= t_nComputedDamage;
		
		CheckHealthState();

		ApplyDamageWithEffect(p_fX, p_fY, t_nComputedDamage);
		SetApplyTime(0);
	}	
}

void CCharacterEntity::ApplyDamageEnemyToOurForceByEntity(COrgan* p_pEntity, DAMAGEDTYPE p_eType, DWORD p_dwApply){
	d3d::BoundingBox t_box;

	t_box._max = D3DXVECTOR3(p_pEntity->GetPriPos()->x + p_pEntity->GetWidthHalf(), p_pEntity->GetPriPos()->y + p_pEntity->GetHeightHalf(), 0.0f);
	t_box._min = D3DXVECTOR3(p_pEntity->GetPriPos()->x - p_pEntity->GetWidthHalf(), p_pEntity->GetPriPos()->y - p_pEntity->GetHeightHalf(), 0.0f);
	int t_nDamage = AIMgr->ComputeAverageDamage(GetMinDamage(), GetMaxDamage());
	float t_fPosX, t_fPosY = 0.0f;

	CDListIterator<CCharacterEntity*> itr = AIMgr->GetOurForceList()->GetIterator();
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pOurForceBody;
	
	if(p_pEntity->GetPriPos()->x > t_pHeroBody->GetPriPos()->x){
		if(t_box._min.x < AIMgr->GetHero()->GetEntityBound()->_max.x){
			if(t_box._max.y < AIMgr->GetHero()->GetEntityBound()->_max.y && t_box._max.y > AIMgr->GetHero()->GetEntityBound()->_min.y &&
			 t_box._min.y > AIMgr->GetHero()->GetEntityBound()->_min.y && t_box._min.y < AIMgr->GetHero()->GetEntityBound()->_max.y){
				t_fPosX = AIMgr->GetHero()->GetEntityBound()->_max.x;
				t_fPosY = AIMgr->GetHero()->GetEntityBound()->_max.y;

				// 먼저 한 번 적용 후,
				AIMgr->GetHero()->Damaged(t_fPosX, t_fPosY, t_nDamage);

				if(AIMgr->GetHero()->GetApplyTime()->IsElapseTimer())
					AIMgr->GetHero()->SetApplyTime(p_dwApply);

				switch(p_eType){
					case SPRINGUP:
						Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), AIMgr->GetHero()->ID(), Msg_SpringUp, NO_ADDITIONAL_INFO);
						break;
					case SHOCK:
						Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), AIMgr->GetHero()->ID(), Msg_Shock, NO_ADDITIONAL_INFO);
						break;
					case PAT:
					default:
						break;
				}
			}
		}
	}
	else{
		if(t_box._max.x > AIMgr->GetHero()->GetEntityBound()->_min.x && t_box._max.y > AIMgr->GetHero()->GetEntityBound()->_min.y){
			if(t_box._max.y < AIMgr->GetHero()->GetEntityBound()->_max.y && t_box._max.y > AIMgr->GetHero()->GetEntityBound()->_min.y &&
			 t_box._min.y > AIMgr->GetHero()->GetEntityBound()->_min.y && t_box._min.y < AIMgr->GetHero()->GetEntityBound()->_max.y){
				t_fPosX = AIMgr->GetHero()->GetEntityBound()->_min.x;
				t_fPosY = AIMgr->GetHero()->GetEntityBound()->_max.y;

				// 먼저 한 번 적용 후,
				AIMgr->GetHero()->Damaged(t_fPosX, t_fPosY, t_nDamage);

				if(AIMgr->GetHero()->GetApplyTime()->IsElapseTimer())
					AIMgr->GetHero()->SetApplyTime(p_dwApply);

				switch(p_eType){
					case SPRINGUP:
						Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), AIMgr->GetHero()->ID(), Msg_SpringUp, NO_ADDITIONAL_INFO);
						break;
					case SHOCK:
						Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), AIMgr->GetHero()->ID(), Msg_Shock, NO_ADDITIONAL_INFO);
						break;
					case PAT:
					default:
						break;
				}
			 }
		}
	}

	// 아군
	for(itr.Start(); itr.Valid(); itr.Forth()){	
		if(itr.Item()->GetOwner() == CBaseObject::TINKLE) continue;
		
		if(itr.Item()->GetLive()){
			t_pOurForceBody = itr.Item()->GetBody();

			if(p_pEntity->GetPriPos()->x > t_pOurForceBody->GetPriPos()->x){
				if(t_box._min.x < itr.Item()->GetEntityBound()->_max.x && t_box._max.y > AIMgr->GetHero()->GetEntityBound()->_min.y){
					if(t_box._max.y < itr.Item()->GetEntityBound()->_max.y && t_box._max.y > itr.Item()->GetEntityBound()->_min.y &&
					t_box._min.y > itr.Item()->GetEntityBound()->_min.y && t_box._min.y < itr.Item()->GetEntityBound()->_max.y){
						t_fPosX = itr.Item()->GetEntityBound()->_max.x;
						t_fPosY = itr.Item()->GetEntityBound()->_max.y;

						// 먼저 한 번 적용 후,
						itr.Item()->Damaged(t_fPosX, t_fPosY, t_nDamage);

						if(itr.Item()->GetApplyTime()->IsElapseTimer())
							itr.Item()->SetApplyTime(p_dwApply);

						switch(p_eType){
							case SPRINGUP:
								Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), itr.Item()->ID(), Msg_SpringUp, NO_ADDITIONAL_INFO);
								break;
							case SHOCK:
								Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), itr.Item()->ID(), Msg_Shock, NO_ADDITIONAL_INFO);
								break;
							case PAT:
							default:
								break;
						}
					}
				}
			}
			else{
				if(t_box._max.x > itr.Item()->GetEntityBound()->_min.x && t_box._max.y > AIMgr->GetHero()->GetEntityBound()->_min.y){
					if(t_box._max.y < itr.Item()->GetEntityBound()->_max.y && t_box._max.y > itr.Item()->GetEntityBound()->_min.y &&
					t_box._min.y > itr.Item()->GetEntityBound()->_min.y && t_box._min.y < itr.Item()->GetEntityBound()->_max.y){
						t_fPosX = itr.Item()->GetEntityBound()->_min.x;
						t_fPosY = itr.Item()->GetEntityBound()->_max.y;

						// 먼저 한 번 적용 후,
						itr.Item()->Damaged(t_fPosX, t_fPosY, t_nDamage);

						if(itr.Item()->GetApplyTime()->IsElapseTimer())
							itr.Item()->SetApplyTime(p_dwApply);

						switch(p_eType){
							case SPRINGUP:
								Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), itr.Item()->ID(), Msg_SpringUp, NO_ADDITIONAL_INFO);
								break;
							case SHOCK:
								Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), itr.Item()->ID(), Msg_Shock, NO_ADDITIONAL_INFO);
								break;
							case PAT:
							default:
								break;
						}
					}
				}
			}
		}
	}
}

void CCharacterEntity::ApplyDamageEnemyToOurForce(DAMAGEDTYPE p_eType, DWORD p_dwApply){
	int t_nDamage = AIMgr->ComputeAverageDamage(GetMinDamage(), GetMaxDamage());
	float t_fPosX, t_fPosY = 0.0f;

	CDListIterator<CCharacterEntity*> itr = AIMgr->GetOurForceList()->GetIterator();
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pOurForceBody;
	
	if(GetBody()->GetPriPos()->x > t_pHeroBody->GetPriPos()->x){
		if(GetAttackBound()->_min.x < AIMgr->GetHero()->GetEntityBound()->_max.x){
			t_fPosX = AIMgr->GetHero()->GetEntityBound()->_max.x;
			t_fPosY = AIMgr->GetHero()->GetEntityBound()->_max.y;

			// 먼저 한 번 적용 후,
			AIMgr->GetHero()->Damaged(t_fPosX, t_fPosY, t_nDamage);

			if(AIMgr->GetHero()->GetApplyTime()->IsElapseTimer())
				AIMgr->GetHero()->SetApplyTime(p_dwApply);

			switch(p_eType){
				case SPRINGUP:
					Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), AIMgr->GetHero()->ID(), Msg_SpringUp, NO_ADDITIONAL_INFO);
					break;
				case SHOCK:
					Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), AIMgr->GetHero()->ID(), Msg_Shock, NO_ADDITIONAL_INFO);
					break;
				case PAT:
				default:
					break;
			}
		}
	}
	else{
		if(GetAttackBound()->_max.x > AIMgr->GetHero()->GetEntityBound()->_min.x){
			t_fPosX = AIMgr->GetHero()->GetEntityBound()->_min.x;
			t_fPosY = AIMgr->GetHero()->GetEntityBound()->_max.y;

			// 먼저 한 번 적용 후,
			AIMgr->GetHero()->Damaged(t_fPosX, t_fPosY, t_nDamage);

			if(AIMgr->GetHero()->GetApplyTime()->IsElapseTimer())
				AIMgr->GetHero()->SetApplyTime(p_dwApply);

			switch(p_eType){
				case SPRINGUP:
					Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), AIMgr->GetHero()->ID(), Msg_SpringUp, NO_ADDITIONAL_INFO);
					break;
				case SHOCK:
					Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), AIMgr->GetHero()->ID(), Msg_Shock, NO_ADDITIONAL_INFO);
					break;
				case PAT:
				default:
					break;
			}
		}
	}

	// 아군
	for(itr.Start(); itr.Valid(); itr.Forth()){	
		if(itr.Item()->GetOwner() == CBaseObject::TINKLE) continue;
		
		if(itr.Item()->GetLive()){
			t_pOurForceBody = itr.Item()->GetBody();

			if(GetBody()->GetPriPos()->x > t_pOurForceBody->GetPriPos()->x){
				if(GetAttackBound()->_min.x < itr.Item()->GetEntityBound()->_max.x){
					t_fPosX = itr.Item()->GetEntityBound()->_max.x;
					t_fPosY = itr.Item()->GetEntityBound()->_max.y;

					// 먼저 한 번 적용 후,
					itr.Item()->Damaged(t_fPosX, t_fPosY, t_nDamage);

					if(itr.Item()->GetApplyTime()->IsElapseTimer())
						itr.Item()->SetApplyTime(p_dwApply);

					switch(p_eType){
						case SPRINGUP:
							Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), itr.Item()->ID(), Msg_SpringUp, NO_ADDITIONAL_INFO);
							break;
						case SHOCK:
							Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), itr.Item()->ID(), Msg_Shock, NO_ADDITIONAL_INFO);
							break;
						case PAT:
						default:
							break;
					}
				}
			}
			else{
				if(GetAttackBound()->_max.x > itr.Item()->GetEntityBound()->_min.x){
					t_fPosX = itr.Item()->GetEntityBound()->_min.x;
					t_fPosY = itr.Item()->GetEntityBound()->_max.y;

					// 먼저 한 번 적용 후,
					itr.Item()->Damaged(t_fPosX, t_fPosY, t_nDamage);

					if(itr.Item()->GetApplyTime()->IsElapseTimer())
						itr.Item()->SetApplyTime(p_dwApply);

					switch(p_eType){
						case SPRINGUP:
							Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), itr.Item()->ID(), Msg_SpringUp, NO_ADDITIONAL_INFO);
							break;
						case SHOCK:
							Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID(), itr.Item()->ID(), Msg_Shock, NO_ADDITIONAL_INFO);
							break;
						case PAT:
						default:
							break;
					}
				}
			}
		}
	}
}

void CCharacterEntity::ApplyDamageOurForceToEnemy(){
	int t_nDamage = AIMgr->ComputeAverageDamage(GetMinDamage(), GetMaxDamage());
	float t_fPosX, t_fPosY = 0.0f;

	if(_body->GetRow() == CBaseObject::LEFT){
		t_fPosX = GetAttackBound()->_min.x;
		t_fPosY = GetAttackBound()->_max.y;
	}
	else{
		t_fPosX = GetAttackBound()->_max.x;
		t_fPosY = GetAttackBound()->_max.y;
	}

	switch(StageMgr->GetStageType()){
		case CStageManager::SCRAPMOUNTAIN:
			switch(StageMgr->GetAreaNumber()){
				case 0:
					AIMgr->GetDustKid()->Damaged(t_fPosX, t_fPosY, t_nDamage);
					break;
				case 1:
					AIMgr->GetMiniWorker()->Damaged(t_fPosX, t_fPosY, t_nDamage);
					break;
				case 2:
					AIMgr->GetWorker()->Damaged(t_fPosX, t_fPosY, t_nDamage);
					break;
			}
			break;
		case CStageManager::FURNACE:
			AIMgr->GetGateKeeper()->Damaged(t_fPosX, t_fPosY, t_nDamage);
			break;
		case CStageManager::DUSTBRIDGE:
			AIMgr->GetDustKing()->Damaged(t_fPosX, t_fPosY, t_nDamage);
			break;
	}
}

void CCharacterEntity::ApplyDamageWithEffect(float p_fX, float p_fY, int p_nDamage){
	EffectMgr->InsertDamageEffect(&D3DXVECTOR3(p_fX, p_fY, 0.0f),p_nDamage);

	switch(_tribeType){
		case NOTHING:
			break;
		case IRON:
			EffectMgr->InsertSparksEffect(&D3DXVECTOR3(p_fX, p_fY, 0.0f));
			EffectMgr->InsertSparksEffect(&D3DXVECTOR3(p_fX, p_fY, 0.0f));
			EffectMgr->InsertSparksEffect(&D3DXVECTOR3(p_fX, p_fY, 0.0f));
			break;
		case DUST:
			EffectMgr->InsertDustEffect(&D3DXVECTOR3(p_fX, p_fY, 0.0f));
			EffectMgr->InsertDustEffect(&D3DXVECTOR3(p_fX, p_fY, 0.0f));
			EffectMgr->InsertDustEffect(&D3DXVECTOR3(p_fX, p_fY, 0.0f));
			break;
	}
}

void CCharacterEntity::BoundRender(){
	EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

	D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
	D3DXVECTOR3 _vRotate;		// 회전 벡터

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMATRIXA16 rX;
	D3DXMatrixIdentity(&rX);
	D3DXMatrixRotationX(&rX, D3DX_PI);
	_rotation = rX;

	mtMatrix *= _rotation;

	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

	RECT rect;

	rect.right = (long)(_attackBound._max.x);
	rect.left = (long)(_attackBound._min.x);
	rect.top = -(long)(_attackBound._max.y);
	rect.bottom = -(long)(_attackBound._min.y);

	_boundFont->DrawText(EngineMgr->GetpSprite(), "1", -1, &rect, DT_LEFT | DT_TOP , 0xffff0000);      
	_boundFont->DrawText(EngineMgr->GetpSprite(), "2", -1, &rect, DT_RIGHT | DT_TOP , 0xffff0000);      
	_boundFont->DrawText(EngineMgr->GetpSprite(), "3", -1, &rect, DT_LEFT | DT_BOTTOM , 0xffff0000);      
	_boundFont->DrawText(EngineMgr->GetpSprite(), "4", -1, &rect, DT_RIGHT | DT_BOTTOM , 0xffff0000);      

	rect.right = (long)(_entityBound._max.x);
	rect.left = (long)(_entityBound._min.x);
	rect.top = -(long)(_entityBound._max.y);
	rect.bottom = -(long)(_entityBound._min.y);

	_boundFont->DrawText(EngineMgr->GetpSprite(), "1", -1, &rect, DT_LEFT | DT_TOP , 0xff00ff00);      
	_boundFont->DrawText(EngineMgr->GetpSprite(), "2", -1, &rect, DT_RIGHT | DT_TOP , 0xff00ff00);      
	_boundFont->DrawText(EngineMgr->GetpSprite(), "3", -1, &rect, DT_LEFT | DT_BOTTOM , 0xff00ff00);      
	_boundFont->DrawText(EngineMgr->GetpSprite(), "4", -1, &rect, DT_RIGHT | DT_BOTTOM , 0xff00ff00);   

	EngineMgr->GetpSprite()->End();

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);
}