#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Ready State
///////////////////////////////////////////////////////////
void CGateKeeperReady::Enter(CGateKeeper* pGateKeeper){
	pGateKeeper->GetBody()->SetVelocity(50.0f);

	_setTimer = false;
}

void CGateKeeperReady::Execute(CGateKeeper* pGateKeeper){
	CBody* t_pBody = pGateKeeper->GetBody();
	
	pGateKeeper->CheckHealthState();

	if(pGateKeeper->GetDestination()->x + 250.0f < t_pBody->GetPriPos()->x){
		pGateKeeper->GetBody()->SetVelocity(50.0f);
		t_pBody->SetRow(CBaseObject::LEFT);
		pGateKeeper->SetCanMove(true);
		pGateKeeper->EntityMove();
	}
	else if(pGateKeeper->GetDestination()->x  + 200.0f > t_pBody->GetPriPos()->x){
		pGateKeeper->GetBody()->SetVelocity(50.0f);
		t_pBody->SetRow(CBaseObject::RIGHT);
		pGateKeeper->SetCanMove(true);
		pGateKeeper->EntityMove();
	}
	else{
		if(_setTimer == false && CameraMgr->GetMode() == CCameraManager::COMBAT){
			pGateKeeper->SetAttackTime(pGateKeeper->GetAttackTimeGap());
			_setTimer = true;
		}

		pGateKeeper->SetCanMove(false);
		t_pBody->SetRow(CBaseObject::LEFT);
		t_pBody->SetVelocity(0.0f);

		if(pGateKeeper->GetAttackTime()->IsElapseTimer()){
			if(CameraMgr->GetMode() == CCameraManager::COMBAT){
				pGateKeeper->GetBody()->SetVelocity(0.0f);
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pGateKeeper->ID(), pGateKeeper->ID(), Msg_Attack, NO_ADDITIONAL_INFO);
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

	switch(t_pBody->GetMoveState()){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.2f;
			pGateKeeper->SetDeltaY(pGateKeeper->GetDeltaY() + 0.2f);
			if(pGateKeeper->GetDeltaY() >= 60.0f)
				t_pBody->SetMoveState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.2f;
			pGateKeeper->SetDeltaY(pGateKeeper->GetDeltaY() - 0.2f);
			if(pGateKeeper->GetDeltaY() <= 40.0f)
				t_pBody->SetMoveState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pGateKeeper->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pGateKeeper->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CGateKeeper::FIRST:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.010f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.010f;
						if(t_Att->GetPriRot()->z <= 0)
							t_Att->SetAngleState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:	
						t_Att->GetPriSca()->y += 0.01f;					

						if(t_Att->GetPriSca()->y >= 1.0f){
							t_Att->SetScaleState(false);
						}
						break;
					case false:
						t_Att->GetPriSca()->y -= 0.01f;					

						if(t_Att->GetPriSca()->y <= 0.8f){
							t_Att->SetScaleState(true);
						}
						break;
				}
				break;
			case CGateKeeper::SECOND:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.010f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.010f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.01f)
							t_Att->SetAngleState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:	
						t_Att->GetPriSca()->y += 0.012f;					

						if(t_Att->GetPriSca()->y >= 1.0f){
							t_Att->SetScaleState(false);
						}
						break;
					case false:
						t_Att->GetPriSca()->y -= 0.01f;					

						if(t_Att->GetPriSca()->y <= 0.75f){
							t_Att->SetScaleState(true);
						}
						break;
				}
				break;
			case CGateKeeper::THIRD:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.010f;
						if(t_Att->GetPriRot()->z >= 0)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.010f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
							t_Att->SetAngleState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:	
						t_Att->GetPriSca()->y += 0.014f;					

						if(t_Att->GetPriSca()->y >= 1.05f){
							t_Att->SetScaleState(false);
						}
						break;
					case false:
						t_Att->GetPriSca()->y -= 0.011f;					

						if(t_Att->GetPriSca()->y <= 0.9f){
							t_Att->SetScaleState(true);
						}
						break;
				}
				break;
			case CGateKeeper::ARM:
				if(t_Att->GetPriRot()->z > 0.01f){
					t_Att->GetPriRot()->z -= 0.01f;
				}
				else if(t_Att->GetPriRot()->z < -0.01f){
					t_Att->GetPriRot()->z += 0.01f;
				}
				break;
			default:
				break;
		}
	}

	pGateKeeper->RenderOrgan();
}

void CGateKeeperReady::Exit(CGateKeeper* pGateKeeper){
	
}

bool CGateKeeperReady::OnMessage(CGateKeeper* agent, const Telegram& msg){
	int t_nTemp = rand() % 10;

	switch(msg.Msg){
		case Msg_Event:
			agent->GetFSM()->ChangeState(GateKeeperEvent->Instance());
			return true;
		case Msg_Attack:
			if(t_nTemp < 4)
				agent->GetFSM()->ChangeState(GateKeeperNormalAttack->Instance());
			else if (t_nTemp < 7)
				agent->GetFSM()->ChangeState(GateKeeperUnderAttack->Instance());	
			else
				agent->GetFSM()->ChangeState(GateKeeperSideAttack->Instance());
			return true;
		case Msg_Healthful:
			agent->SetHealthState(CCharacterEntity::HEALTHFUL);
			agent->GetFSM()->ChangeState(GateKeeperEscape->Instance());
			return true;
		case Msg_Normal:
			agent->SetHealthState(CCharacterEntity::NORMAL);
			agent->GetFSM()->ChangeState(GateKeeperEscape->Instance());
			return true;
		case Msg_Weak:
			agent->SetHealthState(CCharacterEntity::WEAK);
			agent->GetFSM()->ChangeState(GateKeeperEscape->Instance());
			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(GateKeeperDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Event State
///////////////////////////////////////////////////////////
void CGateKeeperEvent::Enter(CGateKeeper* pGateKeeper){
	
}

void CGateKeeperEvent::Execute(CGateKeeper* pGateKeeper){
	// 바디 계산
	CBody* t_pBody = pGateKeeper->GetBody();

	if(t_pBody->GetRow() == CBaseObject::LEFT){
		if(t_pBody->GetPriRot()->y < D3DX_PI){
			t_pBody->GetPriRot()->y += 0.1f;
			if(t_pBody->GetPriRot()->y > D3DX_PI)
				t_pBody->GetPriRot()->y = D3DX_PI;
		}
	}

	switch(t_pBody->GetMoveState()){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.2f;
			pGateKeeper->SetDeltaY(pGateKeeper->GetDeltaY() + 0.2f);
			if(pGateKeeper->GetDeltaY() >= 60.0f)
				t_pBody->SetMoveState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.2f;
			pGateKeeper->SetDeltaY(pGateKeeper->GetDeltaY() - 0.2f);
			if(pGateKeeper->GetDeltaY() <= 40.0f)
				t_pBody->SetMoveState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pGateKeeper->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pGateKeeper->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CGateKeeper::FIRST:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.010f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.010f;
						if(t_Att->GetPriRot()->z <= 0)
							t_Att->SetAngleState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:	
						t_Att->GetPriSca()->y += 0.01f;					

						if(t_Att->GetPriSca()->y >= 1.0f){
							t_Att->SetScaleState(false);
						}
						break;
					case false:
						t_Att->GetPriSca()->y -= 0.01f;					

						if(t_Att->GetPriSca()->y <= 0.8f){
							t_Att->SetScaleState(true);
						}
						break;
				}
				break;
			case CGateKeeper::SECOND:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.010f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.010f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.01f)
							t_Att->SetAngleState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:	
						t_Att->GetPriSca()->y += 0.012f;					

						if(t_Att->GetPriSca()->y >= 1.0f){
							t_Att->SetScaleState(false);
						}
						break;
					case false:
						t_Att->GetPriSca()->y -= 0.01f;					

						if(t_Att->GetPriSca()->y <= 0.75f){
							t_Att->SetScaleState(true);
						}
						break;
				}
				break;
			case CGateKeeper::THIRD:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.010f;
						if(t_Att->GetPriRot()->z >= 0)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.010f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
							t_Att->SetAngleState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:	
						t_Att->GetPriSca()->y += 0.014f;					

						if(t_Att->GetPriSca()->y >= 1.05f){
							t_Att->SetScaleState(false);
						}
						break;
					case false:
						t_Att->GetPriSca()->y -= 0.011f;					

						if(t_Att->GetPriSca()->y <= 0.9f){
							t_Att->SetScaleState(true);
						}
						break;
				}
				break;
			case CGateKeeper::ARM:
				if(t_Att->GetPriRot()->z > 0.01f){
					t_Att->GetPriRot()->z -= 0.01f;
				}
				else if(t_Att->GetPriRot()->z < -0.01f){
					t_Att->GetPriRot()->z += 0.01f;
				}
				break;
			default:
				break;
		}
	}

	pGateKeeper->RenderOrgan();
}

void CGateKeeperEvent::Exit(CGateKeeper* pGateKeeper){

}

bool CGateKeeperEvent::OnMessage(CGateKeeper* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(GateKeeperReady->Instance());
			return true;
		case Msg_Senario:
			agent->GetMessage()->SetUse(true);
			agent->GetMessage()->SetLine((char*)msg.ExtraInfo);
			return true;
		case Msg_SenarioEnd:
			agent->GetMessage()->SetUse(false);
			agent->GetMessage()->SetLine(NULL);
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Normal Attack State
///////////////////////////////////////////////////////////
void CGateKeeperNormalAttack::Enter(CGateKeeper* pGateKeeper){
	_moveDistance = 0.0f;

	pGateKeeper->SetMinDamage(16.0f);
	pGateKeeper->SetMaxDamage(25.0f);

	if(AIMgr->AILiveCheckToYawoAndKirit()){
		_requireDistance = 300.0f;
	}
	else
		_requireDistance = 0.0f;
}

void CGateKeeperNormalAttack::Execute(CGateKeeper* pGateKeeper){
	CBody* t_pBody = pGateKeeper->GetBody();
	
	pGateKeeper->CheckHealthState();

	static float t_fDeltaX = 0.0f;

	switch(t_pBody->GetMoveState()){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.2f;
			pGateKeeper->SetDeltaY(pGateKeeper->GetDeltaY() + 0.2f);
			if(pGateKeeper->GetDeltaY() >= 60.0f)
				t_pBody->SetMoveState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.2f;
			pGateKeeper->SetDeltaY(pGateKeeper->GetDeltaY() - 0.2f);
			if(pGateKeeper->GetDeltaY() <= 40.0f)
				t_pBody->SetMoveState(true);
			break;
	}

	if(_moveDistance <= _requireDistance){
		t_pBody->SetVelocity(50.0f);
		pGateKeeper->SetCanMove(true);

		float t_Distance = 0.0f;
		_moveDistance += pGateKeeper->EntityMove(&t_Distance);

		if(pGateKeeper->GetCanAttack())
			_moveDistance = _requireDistance + 1.0f;

		// 부속품 계산
		for(int i = 0; i < pGateKeeper->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pGateKeeper->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CGateKeeper::FIRST:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= 0)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.01f;					

							if(t_Att->GetPriSca()->y >= 1.0f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.01f;					

							if(t_Att->GetPriSca()->y <= 0.8f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::SECOND:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.01f)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.012f;					

							if(t_Att->GetPriSca()->y >= 1.0f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.01f;					

							if(t_Att->GetPriSca()->y <= 0.75f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::THIRD:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= 0)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.014f;					

							if(t_Att->GetPriSca()->y >= 1.05f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.011f;					

							if(t_Att->GetPriSca()->y <= 0.9f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::ARM:
					if(t_Att->GetPriRot()->z > 0.01f){
						t_Att->GetPriRot()->z -= 0.01f;
					}
					else if(t_Att->GetPriRot()->z < -0.01f){
						t_Att->GetPriRot()->z += 0.01f;
					}
					break;
				default:
					break;
			}
		}
	}
	else{
		t_pBody->SetVelocity(0.0f);
		pGateKeeper->SetCanMove(false);

		// 부속품 계산
		for(int i = 0; i < pGateKeeper->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pGateKeeper->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CGateKeeper::FIRST:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.01f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.01f;
							if(t_Att->GetPriRot()->z <= 0)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.01f;					

							if(t_Att->GetPriSca()->y >= 1.0f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.01f;					

							if(t_Att->GetPriSca()->y <= 0.8f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::SECOND:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.01f)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.012f;					

							if(t_Att->GetPriSca()->y >= 1.0f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.01f;					

							if(t_Att->GetPriSca()->y <= 0.75f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::THIRD:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= 0)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.014f;					

							if(t_Att->GetPriSca()->y >= 1.05f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.011f;					

							if(t_Att->GetPriSca()->y <= 0.9f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::ARM:
					switch(t_Att->GetAngleState()){
						case true:
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f){
									switch(t_Att->GetMoveState()){
										case true:
											// Max라면
											t_Att->GetPriPos()->x += _aceX;
											t_fDeltaX += _aceX;

											pGateKeeper->ApplyDamageEnemyToOurForce(CCharacterEntity::SPRINGUP, 1500);

											if(t_fDeltaX >= 100.0f)
												t_Att->SetMoveState(false);
											break;
										case false:
											// Min라면
											t_Att->GetPriPos()->x -= 0.8f;
											t_fDeltaX -= 0.8f;
											if(t_fDeltaX <= 0.0f){
												t_Att->SetMoveState(true);
												//t_Att->GetPriPos()->x = 0.0f;
												t_fDeltaX = 0.0f;
												pGateKeeper->GetFSM()->ChangeState(GateKeeperReady->Instance());
											}
											break;
									}
									_aceX += 0.05f;
							}
							else{
								t_Att->SetAngleState(false);
							}
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.01f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.13f){
								t_Att->SetAngleState(true);
								_aceX = 0.1f;
							}
							break;
					}
					break;
				default:
					break;
			}
		}
	}

	pGateKeeper->RenderOrgan();
}

void CGateKeeperNormalAttack::Exit(CGateKeeper* pGateKeeper){

}

bool CGateKeeperNormalAttack::OnMessage(CGateKeeper* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(GateKeeperReady->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(GateKeeperDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Under Attack State
///////////////////////////////////////////////////////////
void CGateKeeperUnderAttack::Enter(CGateKeeper* pGateKeeper){
	_moveDistance = 0.0f;

	pGateKeeper->SetMinDamage(23.0f);
	pGateKeeper->SetMaxDamage(27.0f);

	if(AIMgr->AILiveCheckToYawoAndKirit()){
		_requireDistance = 300.0f;
	}
	else
		_requireDistance = 0.0f;
}

void CGateKeeperUnderAttack::Execute(CGateKeeper* pGateKeeper){
	CBody* t_pBody = pGateKeeper->GetBody();
	
	static float t_fDeltaX = 0.0f;

	pGateKeeper->CheckHealthState();

	switch(t_pBody->GetMoveState()){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.2f;
			pGateKeeper->SetDeltaY(pGateKeeper->GetDeltaY() + 0.2f);
			if(pGateKeeper->GetDeltaY() >= 60.0f)
				t_pBody->SetMoveState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.2f;
			pGateKeeper->SetDeltaY(pGateKeeper->GetDeltaY() - 0.2f);
			if(pGateKeeper->GetDeltaY() <= 40.0f)
				t_pBody->SetMoveState(true);
			break;
	}

	if(_moveDistance <= _requireDistance){
		t_pBody->SetVelocity(50.0f);
		pGateKeeper->SetCanMove(true);

		float t_Distance = 0.0f;
		_moveDistance += pGateKeeper->EntityMove(&t_Distance);

		if(pGateKeeper->GetCanAttack())
			_moveDistance = _requireDistance + 1.0f;

		// 부속품 계산
		for(int i = 0; i < pGateKeeper->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pGateKeeper->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CGateKeeper::FIRST:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= 0)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.01f;					

							if(t_Att->GetPriSca()->y >= 1.0f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.01f;					

							if(t_Att->GetPriSca()->y <= 0.8f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::SECOND:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.01f)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.012f;					

							if(t_Att->GetPriSca()->y >= 1.0f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.01f;					

							if(t_Att->GetPriSca()->y <= 0.75f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::THIRD:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= 0)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.014f;					

							if(t_Att->GetPriSca()->y >= 1.05f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.011f;					

							if(t_Att->GetPriSca()->y <= 0.9f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::ARM:
					if(t_Att->GetPriRot()->z > 0.01f){
						t_Att->GetPriRot()->z -= 0.01f;
					}
					else if(t_Att->GetPriRot()->z < -0.01f){
						t_Att->GetPriRot()->z += 0.01f;
					}
					break;
				default:
					break;
			}
		}
	}
	else{
		t_pBody->SetVelocity(0.0f);
		pGateKeeper->SetCanMove(false);

		// 부속품 계산
		for(int i = 0; i < pGateKeeper->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pGateKeeper->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CGateKeeper::FIRST:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.01f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.01f;
							if(t_Att->GetPriRot()->z <= 0)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.01f;					

							if(t_Att->GetPriSca()->y >= 1.0f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.01f;					

							if(t_Att->GetPriSca()->y <= 0.8f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::SECOND:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.01f)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.012f;					

							if(t_Att->GetPriSca()->y >= 1.0f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.01f;					

							if(t_Att->GetPriSca()->y <= 0.75f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::THIRD:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= 0)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.014f;					

							if(t_Att->GetPriSca()->y >= 1.05f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.011f;					

							if(t_Att->GetPriSca()->y <= 0.9f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::ARM:
					switch(t_Att->GetAngleState()){
						case true:	
							switch(t_Att->GetMoveState()){
								case true:
									// Max라면
									t_Att->GetPriPos()->x += _aceX;
									t_fDeltaX += _aceX;

									if(t_fDeltaX >= 100.0f)
										t_Att->SetMoveState(false);
									break;
								case false:
									// Min라면
									t_Att->GetPriRot()->z += 0.01f;
									if(t_Att->GetPriRot()->z >= D3DX_PI * 0.3f){
										t_Att->SetAngleState(false);
									}	
							}
							_aceX += 0.02f;																			
							break;					
						case false:
							if(t_Att->GetPriRot()->z > -D3DX_PI * 0.13f)
								t_Att->GetPriRot()->z -= 0.024f;

							if(t_Att->GetPriRot()->z <= 0.0f){
								if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.13f){
									switch(t_Att->GetMoveState()){	
										case true:

											break;
										case false:
											// Min라면
											t_Att->GetPriPos()->x -= 0.8f;
											t_fDeltaX -= 0.8f;
											if(t_fDeltaX <= 0.0f){
												t_Att->SetMoveState(true);
												//t_Att->GetPriPos()->x = 0.0f;
												t_fDeltaX = 0.0f;
												t_Att->SetAngleState(true);
												pGateKeeper->GetFSM()->ChangeState(GateKeeperReady->Instance());
											}
											break;
									}		
								}
								else
									pGateKeeper->ApplyDamageEnemyToOurForce(CCharacterEntity::SPRINGUP, 1500);
							}	
							break;
					}
					break;
				default:
					break;
			}
		}
	}

	pGateKeeper->RenderOrgan();
}

void CGateKeeperUnderAttack::Exit(CGateKeeper* pGateKeeper){

}

bool CGateKeeperUnderAttack::OnMessage(CGateKeeper* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(GateKeeperReady->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(GateKeeperDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Side Attack State
///////////////////////////////////////////////////////////
void CGateKeeperSideAttack::Enter(CGateKeeper* pGateKeeper){
	_moveDistance = 0.0f;

	pGateKeeper->SetMinDamage(18.0f);
	pGateKeeper->SetMaxDamage(24.0f);

	if(AIMgr->AILiveCheckToYawoAndKirit()){
		_requireDistance = 300.0f;
	}
	else
		_requireDistance = 0.0f;
}

void CGateKeeperSideAttack::Execute(CGateKeeper* pGateKeeper){
	CBody* t_pBody = pGateKeeper->GetBody();

	pGateKeeper->CheckHealthState();

	switch(t_pBody->GetMoveState()){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.2f;
			pGateKeeper->SetDeltaY(pGateKeeper->GetDeltaY() + 0.2f);
			if(pGateKeeper->GetDeltaY() >= 60.0f)
				t_pBody->SetMoveState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.2f;
			pGateKeeper->SetDeltaY(pGateKeeper->GetDeltaY() - 0.2f);
			if(pGateKeeper->GetDeltaY() <= 40.0f)
				t_pBody->SetMoveState(true);
			break;
	}

	if(_moveDistance <= _requireDistance){
		t_pBody->SetVelocity(50.0f);
		pGateKeeper->SetCanMove(true);

		float t_Distance = 0.0f;
		_moveDistance += pGateKeeper->EntityMove(&t_Distance);

		if(pGateKeeper->GetCanAttack())
			_moveDistance = _requireDistance + 1.0f;

		// 부속품 계산
		for(int i = 0; i < pGateKeeper->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pGateKeeper->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CGateKeeper::FIRST:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= 0)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.01f;					

							if(t_Att->GetPriSca()->y >= 1.0f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.01f;					

							if(t_Att->GetPriSca()->y <= 0.8f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::SECOND:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.01f)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.012f;					

							if(t_Att->GetPriSca()->y >= 1.0f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.01f;					

							if(t_Att->GetPriSca()->y <= 0.75f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::THIRD:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= 0)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.014f;					

							if(t_Att->GetPriSca()->y >= 1.05f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.011f;					

							if(t_Att->GetPriSca()->y <= 0.9f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::ARM:
					if(t_Att->GetPriRot()->z > 0.01f){
						t_Att->GetPriRot()->z -= 0.01f;
					}
					else if(t_Att->GetPriRot()->z < -0.01f){
						t_Att->GetPriRot()->z += 0.01f;
					}
					break;
				default:
					break;
			}
		}
	}
	else{
		t_pBody->SetVelocity(0.0f);
		pGateKeeper->SetCanMove(false);

		// 부속품 계산
		for(int i = 0; i < pGateKeeper->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pGateKeeper->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CGateKeeper::FIRST:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.01f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.01f;
							if(t_Att->GetPriRot()->z <= 0)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.01f;					

							if(t_Att->GetPriSca()->y >= 1.0f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.01f;					

							if(t_Att->GetPriSca()->y <= 0.8f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::SECOND:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.01f)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.012f;					

							if(t_Att->GetPriSca()->y >= 1.0f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.01f;					

							if(t_Att->GetPriSca()->y <= 0.75f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::THIRD:
					switch(t_Att->GetAngleState()){
						case true:
							// Max라면
							t_Att->GetPriRot()->z += 0.010f;
							if(t_Att->GetPriRot()->z >= 0)
								t_Att->SetAngleState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriRot()->z -= 0.010f;
							if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
								t_Att->SetAngleState(true);
							break;
					}

					switch(t_Att->GetScaleState()){
						case true:	
							t_Att->GetPriSca()->y += 0.014f;					

							if(t_Att->GetPriSca()->y >= 1.05f){
								t_Att->SetScaleState(false);
							}
							break;
						case false:
							t_Att->GetPriSca()->y -= 0.011f;					

							if(t_Att->GetPriSca()->y <= 0.9f){
								t_Att->SetScaleState(true);
							}
							break;
					}
					break;
				case CGateKeeper::ARM:
					switch(t_Att->GetAngleState()){
						case true:								
							// Min라면
							t_Att->GetPriRot()->y -= 0.005f;
							if(t_Att->GetPriRot()->y <= -D3DX_PI * 0.225f){
								t_Att->SetAngleState(false);
							}																							
							break;					
						case false:							
							t_Att->GetPriRot()->y += 0.03f;

							if(t_Att->GetPriRot()->y >= -D3DX_PI * 0.05f){
								pGateKeeper->ApplyDamageEnemyToOurForce(CCharacterEntity::SPRINGUP, 1500);
								if(t_Att->GetPriRot()->y >= 0.0f){									
									t_Att->SetAngleState(true);
									pGateKeeper->GetFSM()->ChangeState(GateKeeperReady->Instance());
								}
							}	
							break;
					}
					break;
				default:
					break;
			}
		}
	}

	pGateKeeper->RenderOrgan();
}

void CGateKeeperSideAttack::Exit(CGateKeeper* pGateKeeper){

}

bool CGateKeeperSideAttack::OnMessage(CGateKeeper* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Ready:
			agent->GetFSM()->ChangeState(GateKeeperReady->Instance());
			return true;
		case Msg_Defense:

			return true;
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(GateKeeperDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Escape State
///////////////////////////////////////////////////////////
void CGateKeeperEscape::Enter(CGateKeeper* pGateKeeper){
	
}

void CGateKeeperEscape::Execute(CGateKeeper* pGateKeeper){
	CBody* t_pBody = pGateKeeper->GetBody();
	
	pGateKeeper->CheckHealthState();

	if(pGateKeeper->GetDestination()->x + AIMgr->GetAttackRange()->_max.x - 200.0f < t_pBody->GetPriPos()->x){
		pGateKeeper->GetBody()->SetVelocity(50.0f);
		t_pBody->SetRow(CBaseObject::LEFT);
		pGateKeeper->SetCanMove(true);
		pGateKeeper->EntityMove();
	}
	else if(pGateKeeper->GetDestination()->x  + 200.0f > t_pBody->GetPriPos()->x){
		pGateKeeper->GetBody()->SetVelocity(50.0f);
		t_pBody->SetRow(CBaseObject::RIGHT);
		pGateKeeper->SetCanMove(true);
		pGateKeeper->EntityMove();
	}
	else{
		pGateKeeper->GetFSM()->ChangeState(GateKeeperReady->Instance());
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

	switch(t_pBody->GetMoveState()){
		case true:
			// Max라면
			t_pBody->GetPriPos()->y += 0.2f;
			pGateKeeper->SetDeltaY(pGateKeeper->GetDeltaY() + 0.2f);
			if(pGateKeeper->GetDeltaY() >= 60.0f)
				t_pBody->SetMoveState(false);
			break;
		case false:
			// Min라면
			t_pBody->GetPriPos()->y -= 0.2f;
			pGateKeeper->SetDeltaY(pGateKeeper->GetDeltaY() - 0.2f);
			if(pGateKeeper->GetDeltaY() <= 40.0f)
				t_pBody->SetMoveState(true);
			break;
	}

	// 부속품 계산
	for(int i = 0; i < pGateKeeper->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pGateKeeper->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CGateKeeper::FIRST:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.010f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.010f;
						if(t_Att->GetPriRot()->z <= 0)
							t_Att->SetAngleState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:	
						t_Att->GetPriSca()->y += 0.01f;					

						if(t_Att->GetPriSca()->y >= 1.0f){
							t_Att->SetScaleState(false);
						}
						break;
					case false:
						t_Att->GetPriSca()->y -= 0.01f;					

						if(t_Att->GetPriSca()->y <= 0.8f){
							t_Att->SetScaleState(true);
						}
						break;
				}
				break;
			case CGateKeeper::SECOND:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.010f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.010f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.01f)
							t_Att->SetAngleState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:	
						t_Att->GetPriSca()->y += 0.012f;					

						if(t_Att->GetPriSca()->y >= 1.0f){
							t_Att->SetScaleState(false);
						}
						break;
					case false:
						t_Att->GetPriSca()->y -= 0.01f;					

						if(t_Att->GetPriSca()->y <= 0.75f){
							t_Att->SetScaleState(true);
						}
						break;
				}
				break;
			case CGateKeeper::THIRD:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.010f;
						if(t_Att->GetPriRot()->z >= 0)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.010f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
							t_Att->SetAngleState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:	
						t_Att->GetPriSca()->y += 0.014f;					

						if(t_Att->GetPriSca()->y >= 1.05f){
							t_Att->SetScaleState(false);
						}
						break;
					case false:
						t_Att->GetPriSca()->y -= 0.011f;					

						if(t_Att->GetPriSca()->y <= 0.9f){
							t_Att->SetScaleState(true);
						}
						break;
				}
				break;
			case CGateKeeper::ARM:
				if(t_Att->GetPriRot()->z > 0.01f){
					t_Att->GetPriRot()->z -= 0.01f;
				}
				else if(t_Att->GetPriRot()->z < -0.01f){
					t_Att->GetPriRot()->z += 0.01f;
				}
				break;
			default:
				break;
		}
	}

	pGateKeeper->RenderOrgan();
}

void CGateKeeperEscape::Exit(CGateKeeper* pGateKeeper){

}

bool CGateKeeperEscape::OnMessage(CGateKeeper* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Die:
			agent->SetLive(false);
			agent->GetFSM()->ChangeState(GateKeeperDie->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Die State
///////////////////////////////////////////////////////////
void CGateKeeperDie::Enter(CGateKeeper* pGateKeeper){
	_aceX = 0.1f;
	_aceY = 0.1f;
}

void CGateKeeperDie::Execute(CGateKeeper* pGateKeeper){
	CBody* t_pBody = pGateKeeper->GetBody();

	t_pBody->GetPriRot()->z += 0.1f;
	t_pBody->GetPriPos()->x += _aceX;
	t_pBody->GetPriPos()->y += _aceY;

	_aceY += 0.2f;
	_aceX += 0.1f;

	// 부속품 계산
	for(int i = 0; i < pGateKeeper->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pGateKeeper->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CGateKeeper::FIRST:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.010f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.02f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.010f;
						if(t_Att->GetPriRot()->z <= 0)
							t_Att->SetAngleState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:	
						t_Att->GetPriSca()->y += 0.01f;					

						if(t_Att->GetPriSca()->y >= 1.0f){
							t_Att->SetScaleState(false);
						}
						break;
					case false:
						t_Att->GetPriSca()->y -= 0.01f;					

						if(t_Att->GetPriSca()->y <= 0.8f){
							t_Att->SetScaleState(true);
						}
						break;
				}
				break;
			case CGateKeeper::SECOND:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.010f;
						if(t_Att->GetPriRot()->z >= D3DX_PI * 0.01f)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.010f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.01f)
							t_Att->SetAngleState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:	
						t_Att->GetPriSca()->y += 0.012f;					

						if(t_Att->GetPriSca()->y >= 1.0f){
							t_Att->SetScaleState(false);
						}
						break;
					case false:
						t_Att->GetPriSca()->y -= 0.01f;					

						if(t_Att->GetPriSca()->y <= 0.75f){
							t_Att->SetScaleState(true);
						}
						break;
				}
				break;
			case CGateKeeper::THIRD:
				switch(t_Att->GetAngleState()){
					case true:
						// Max라면
						t_Att->GetPriRot()->z += 0.010f;
						if(t_Att->GetPriRot()->z >= 0)
							t_Att->SetAngleState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriRot()->z -= 0.010f;
						if(t_Att->GetPriRot()->z <= -D3DX_PI * 0.02f)
							t_Att->SetAngleState(true);
						break;
				}

				switch(t_Att->GetScaleState()){
					case true:	
						t_Att->GetPriSca()->y += 0.014f;					

						if(t_Att->GetPriSca()->y >= 1.05f){
							t_Att->SetScaleState(false);
						}
						break;
					case false:
						t_Att->GetPriSca()->y -= 0.011f;					

						if(t_Att->GetPriSca()->y <= 0.9f){
							t_Att->SetScaleState(true);
						}
						break;
				}
				break;
			case CGateKeeper::ARM:

				break;
			default:
				break;
		}
	}

	pGateKeeper->RenderOrgan();
}

void CGateKeeperDie::Exit(CGateKeeper* pGateKeeper){

}

bool CGateKeeperDie::OnMessage(CGateKeeper* agent, const Telegram& msg){
	return false;
}