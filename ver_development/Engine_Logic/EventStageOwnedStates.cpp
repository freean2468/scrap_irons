#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// 전역상태
// 어떠한 상태에서도 카메라를 따라디니게 하기 위함.
///////////////////////////////////////////////////////////
void CEventStageGlobal::Enter(CEventStage* p_pEvent){
	
}

void CEventStageGlobal::Execute(CEventStage* p_pEvent){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CBody* t_pBody = p_pEvent->GetBody();

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_vPos.x;
	t_pBody->GetPriPos()->y = t_vPos.y;
	t_pBody->GetPriPos()->z = 700.0f + t_vPos.z;
}

void CEventStageGlobal::Exit(CEventStage* p_pEvent){
	
}

///////////////////////////////////////////////////////////
// Stage Event
///////////////////////////////////////////////////////////
void CEventStageCheck::Enter(CEventStage* p_pEvent){
	
}

void CEventStageCheck::Execute(CEventStage* p_pEvent){
	if(StageMgr->GetStageType() == CStageManager::HOME && p_pEvent->_firstMeeting == false){
		p_pEvent->GetFSM()->ChangeState(EventStageFirstMeeting->Instance());
		p_pEvent->_firstMeeting = true;
		StageMgr->_homeClear = true;
	}

	if(StageMgr->GetStageType() == CStageManager::SCRAPMOUNTAIN){
		switch(StageMgr->GetAreaNumber()){
			case 0:
				if(p_pEvent->_firstArea == false){
					p_pEvent->GetFSM()->ChangeState(EventStageFirstArea->Instance());
					p_pEvent->_firstArea = true;
				}
				break;
			case 1:
				if(p_pEvent->_secondArea == false){
					p_pEvent->GetFSM()->ChangeState(EventStageSecondArea->Instance());
					p_pEvent->_secondArea = true;
				}
				break;
			case 2:
				if(p_pEvent->_thirdArea == false){
					p_pEvent->GetFSM()->ChangeState(EventStageThirdArea->Instance());
					p_pEvent->_thirdArea = true;
				}
				break;
		}
	}

	if(StageMgr->GetStageType() == CStageManager::FURNACE && p_pEvent->_furnace == false){
		p_pEvent->GetFSM()->ChangeState(EventStageFurnace->Instance());
		p_pEvent->_furnace = true;
	}

	if(StageMgr->GetStageType() == CStageManager::CHIMNEY && p_pEvent->_chimney == false){
		p_pEvent->GetFSM()->ChangeState(EventStageChimney->Instance());
		p_pEvent->_chimney = true;
		StageMgr->_chimneyClear = true;
	}

	if(StageMgr->GetStageType() == CStageManager::DUSTBRIDGE && p_pEvent->_dustbridge == false){
		p_pEvent->GetFSM()->ChangeState(EventStageDustBridge->Instance());
		p_pEvent->_dustbridge = true;
	}

	if(StageMgr->GetStageType() == CStageManager::GOODHOPE && p_pEvent->_goodHopeIntro == false){
		p_pEvent->GetFSM()->ChangeState(EventStageGoodHopeIntro->Instance());
		p_pEvent->_goodHopeIntro = true;
	}

	if(StageMgr->GetStageType() == CStageManager::GOODHOPE && p_pEvent->_goodHopeIntro == true && p_pEvent->_goodHope == false){
		if(AIMgr->GetHero()->GetBody()->GetPriPos()->x <= StageMgr->GetStage()->GetPriPos()->x){
			p_pEvent->GetFSM()->ChangeState(EventStageGoodHope->Instance());
			p_pEvent->_goodHope = true;
		}
	}
}

void CEventStageCheck::Exit(CEventStage* p_pEvent){
	
}

///////////////////////////////////////////////////////////
// RunAway 이벤트
///////////////////////////////////////////////////////////
void CEventStageRunAway::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(AIMgr->GetHero()->GetBody()->GetPriPos()->x, AIMgr->GetHero()->GetBody()->GetPriPos()->y + 200.0f, -710.0f);

	CameraMgr->GetCamera()->GetPosition(&_cameraPos);

	CameraMgr->SetDestination(&t_vPos);

	EventMgr->ReadText("./script/Event/RunAway.txt");
}

void CEventStageRunAway::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	if(EventMgr->NextText()){
		p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
		CameraMgr->SetMode(CCameraManager::RELAX);
		CameraMgr->SetDestination(&_cameraPos);
		AIMgr->GetHero()->GetFSM()->ChangeState(HeroEscape->Instance());
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_CART, Msg_Pull, NO_ADDITIONAL_INFO);
	}

	p_pEvent->RenderOrgan();
}

void CEventStageRunAway::Exit(CEventStage* p_pEvent){
	
}

bool CEventStageRunAway::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// 첫만남 이벤트
///////////////////////////////////////////////////////////
void CEventStageFirstMeeting::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	EventMgr->ReadText("./script/Event/FirstMetting.txt");

	AIMgr->GetFlower()->GetBody()->GetPriPos()->x = StageMgr->GetStage()->GetPriPos()->x + 700;
	AIMgr->GetFlower()->GetBody()->GetPriPos()->y = StageMgr->GetStage()->GetPriPos()->y + 200;

	AIMgr->GetCart()->GetBody()->GetPriPos()->x = StageMgr->GetStage()->GetPriPos()->x + StageMgr->GetStage()->GetWidthHalf() - 200.0f;
	AIMgr->GetCart()->GetBody()->SetRow(CBaseObject::LEFT);
	AIMgr->GetFlower()->SetDestination(AIMgr->GetHero()->GetBody()->GetPriPos());
	AIMgr->GetFlower()->SetDestinationX(AIMgr->GetFlower()->GetDestination()->x + 70.0f);
	AIMgr->GetHero()->GetBody()->GetPriPos()->x = StageMgr->GetStage()->GetPriPos()->x - 50.0f;

	AIMgr->GetOurForceEntityFromID(ID_WAGOO)->GetBody()->GetPriPos()->x = StageMgr->GetStage()->GetPriPos()->x - 250.0f;

	CameraMgr->SetDestinationX(AIMgr->GetCart()->GetBody()->GetPriPos()->x);
}

void CEventStageFirstMeeting::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();
	CAttachment* t_pAtt;

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	switch(EventMgr->GetIndex()){
		case 0:
			CameraMgr->CameraVibration();
			EventMgr->NextText();
			break;
		case 1:
			if(AIMgr->GetHero()->GetBody()->GetPriPos()->x <= AIMgr->GetCart()->GetBody()->GetPriPos()->x - 200.0f){
				AIMgr->GetHero()->SetCanMove(true);
				AIMgr->GetHero()->GetBody()->SetVelocity(200.0f);
				AIMgr->GetHero()->EntityMove();
			}
			else{
				EventMgr->NextText();
			}
			break;
		case 4:
			if(AIMgr->GetOurForceEntityFromID(ID_WAGOO)->GetBody()->GetPriPos()->x <= AIMgr->GetCart()->GetBody()->GetPriPos()->x - 300.0f){
				AIMgr->GetOurForceEntityFromID(ID_WAGOO)->SetCanMove(true);
				AIMgr->GetOurForceEntityFromID(ID_WAGOO)->GetBody()->SetVelocity(120.0f);
				AIMgr->GetOurForceEntityFromID(ID_WAGOO)->EntityMove();
				CameraMgr->SetDestinationX(AIMgr->GetOurForceEntityFromID(ID_WAGOO)->GetBody()->GetPriPos()->x);
			}
			else{
				CameraMgr->SetDestinationX(AIMgr->GetHero()->GetBody()->GetPriPos()->x);
				EventMgr->NextText();
			}
			break;
		case 15:
			AIMgr->GetFlower()->FaceToDestination();

			if(AIMgr->GetHero()->ComputeEntityBound(AIMgr->GetFlower())){			
				t_pAtt = p_pEvent->GetAttachmentFromType(CEventStage::FIRST);

					switch(t_pAtt->GetAlphaState()){
						case true:							
							if(t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a >= 0.0f && t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a < 1.0f){
								t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.02f;
								if(t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a >= 1.0f){
									t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a = 1.0f;
									p_pEvent->SetTimer(2000);	
								}
							}

							if(p_pEvent->GetTimer()->IsElapseTimer()){
								EventMgr->NextText();
							}
							break;
					}
			}
			break;
		case 17:
			t_pAtt = p_pEvent->GetAttachmentFromType(CEventStage::FIRST);

			switch(t_pAtt->GetAlphaState()){
				case true:
					t_pAtt->SetAlphaState(false);
					AIMgr->GetHero()->GetBody()->GetPriPos()->x = AIMgr->GetCart()->GetBody()->GetPriPos()->x + 70.0f;
					AIMgr->GetHero()->GetBody()->SetRow(CBaseObject::LEFT);
					AIMgr->GetFlower()->GetFSM()->ChangeState(FlowerMove->Instance());
					break;
				case false:							
					t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a -= 0.02f;
					if(t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.0f)
						EventMgr->NextText();
					break;
			}
			break;
		case 18:
			if(AIMgr->GetHero()->GetBody()->GetPriPos()->x >= AIMgr->GetCart()->GetBody()->GetPriPos()->x - 200.0f){
				AIMgr->GetHero()->SetCanMove(true);
				AIMgr->GetHero()->GetBody()->SetVelocity(60.0f);
				AIMgr->GetHero()->EntityMove();
			}
			else{
				AIMgr->GetHero()->GetBody()->SetRow(CBaseObject::RIGHT);
				EventMgr->NextText();
			}
			break;
		default:
			if(EventMgr->NextText()){
				p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
				CameraMgr->SetMode(CCameraManager::RELAX);
			}
			break;
	}

	p_pEvent->RenderOrgan();
}

void CEventStageFirstMeeting::Exit(CEventStage* p_pEvent){
	
}

bool CEventStageFirstMeeting::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// 첫번째 Area 이벤트
///////////////////////////////////////////////////////////
void CEventStageFirstArea::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	AIMgr->GetDustKid()->SetDestinationX(0.0f);

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(AIMgr->GetHero()->GetBody()->GetPriPos()->x, AIMgr->GetHero()->GetBody()->GetPriPos()->y + 250.0f, -710.0f);

	CameraMgr->GetCamera()->GetPosition(&_cameraPos);

	CameraMgr->SetDestination(&t_vPos);

	EventMgr->ReadText("./script/Event/FirstArea.txt");
}

void CEventStageFirstArea::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	switch(EventMgr->GetIndex()){
		case 12:
			p_pEvent->SetTimer(3000);
			EventMgr->NextText();
			break;
		case 13:
			CameraMgr->SetDestinationX(AIMgr->GetDustKid()->GetBody()->GetPriPos()->x);
			if(p_pEvent->GetTimer()->IsElapseTimer()){
				CameraMgr->SetDestinationX(AIMgr->GetHero()->GetBody()->GetPriPos()->x);
				CameraMgr->GetCamera()->GetPosition(&t_vPos);

				if(t_vPos.x <= CameraMgr->GetDestination()->x + 200.0f)
					EventMgr->NextText();
			}
			break;
		default:
			if(EventMgr->NextText()){
				p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
				CameraMgr->SetMode(CCameraManager::RELAX);
				CameraMgr->SetDestination(&_cameraPos);
			}
			break;
	}

	p_pEvent->RenderOrgan();
}

void CEventStageFirstArea::Exit(CEventStage* p_pEvent){
	
}

bool CEventStageFirstArea::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// DustKidDie 이벤트
///////////////////////////////////////////////////////////
void CEventStageDustKidDie::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(AIMgr->GetHero()->GetBody()->GetPriPos()->x, AIMgr->GetHero()->GetBody()->GetPriPos()->y + 200.0f, -710.0f);

	CameraMgr->GetCamera()->GetPosition(&_cameraPos);

	CameraMgr->SetDestination(&t_vPos);

	EventMgr->ReadText("./script/Event/DustKidDie.txt");
}

void CEventStageDustKidDie::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	if(EventMgr->NextText()){
		p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
		CameraMgr->SetMode(CCameraManager::RELAX);
		CameraMgr->SetDestination(&_cameraPos);
	}

	p_pEvent->RenderOrgan();
}

void CEventStageDustKidDie::Exit(CEventStage* p_pEvent){
	
}

bool CEventStageDustKidDie::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// 두번째 Area 이벤트
///////////////////////////////////////////////////////////
void CEventStageSecondArea::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	AIMgr->GetDustKid()->SetDestinationX(0.0f);

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(AIMgr->GetHero()->GetBody()->GetPriPos()->x, AIMgr->GetHero()->GetBody()->GetPriPos()->y + 200.0f, -710.0f);

	CameraMgr->GetCamera()->GetPosition(&_cameraPos);

	CameraMgr->SetDestination(&t_vPos);

	EventMgr->ReadText("./script/Event/SecondArea.txt");
}

void CEventStageSecondArea::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	switch(EventMgr->GetIndex()){
		case 0:
			p_pEvent->SetTimer(3000);
			EventMgr->NextText();
			break;
		case 1:
			CameraMgr->SetDestinationX(AIMgr->GetMiniWorker()->GetBody()->GetPriPos()->x);
			if(p_pEvent->GetTimer()->IsElapseTimer()){
				CameraMgr->SetDestinationX(AIMgr->GetHero()->GetBody()->GetPriPos()->x);
				EventMgr->NextText();

				CameraMgr->GetCamera()->GetPosition(&t_vPos);

				if(t_vPos.x <= CameraMgr->GetDestination()->x + 100.0f)
					EventMgr->NextText();
			}
			break;
		default:
			if(EventMgr->NextText()){
				p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
				CameraMgr->SetMode(CCameraManager::RELAX);
				CameraMgr->SetDestination(&_cameraPos);
			}
			break;
	}

	p_pEvent->RenderOrgan();
}

void CEventStageSecondArea::Exit(CEventStage* p_pEvent){
	
}

bool CEventStageSecondArea::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// 세번째 Area 이벤트
///////////////////////////////////////////////////////////
void CEventStageThirdArea::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	AIMgr->GetDustKid()->SetDestinationX(0.0f);

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(AIMgr->GetHero()->GetBody()->GetPriPos()->x, AIMgr->GetHero()->GetBody()->GetPriPos()->y + 200.0f, -710.0f);

	CameraMgr->GetCamera()->GetPosition(&_cameraPos);

	CameraMgr->SetDestination(&t_vPos);

	EventMgr->ReadText("./script/Event/ThirdArea.txt");
}

void CEventStageThirdArea::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	switch(EventMgr->GetIndex()){
		case 4:
			p_pEvent->SetTimer(3000);
			EventMgr->NextText();
			break;
		case 5:
			CameraMgr->SetDestinationX(AIMgr->GetWorker()->GetBody()->GetPriPos()->x - 150.0f);
			EventMgr->NextText();
			break;
		case 7:
			CameraMgr->SetDestinationX(AIMgr->GetHero()->GetBody()->GetPriPos()->x);
			EventMgr->NextText();
			break;
		default:
			if(EventMgr->NextText()){
				p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
				CameraMgr->SetMode(CCameraManager::RELAX);
				CameraMgr->SetDestination(&_cameraPos);
			}
			break;
	}

	p_pEvent->RenderOrgan();
}

void CEventStageThirdArea::Exit(CEventStage* p_pEvent){
	
}

bool CEventStageThirdArea::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// WorkerDie 이벤트
///////////////////////////////////////////////////////////
void CEventStageWorkerDie::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(AIMgr->GetHero()->GetBody()->GetPriPos()->x, AIMgr->GetHero()->GetBody()->GetPriPos()->y + 200.0f, -710.0f);

	CameraMgr->GetCamera()->GetPosition(&_cameraPos);

	CameraMgr->SetDestination(&t_vPos);

	EventMgr->ReadText("./script/Event/WorkerDie.txt");
}

void CEventStageWorkerDie::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	if(EventMgr->NextText()){
		p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
		CameraMgr->SetMode(CCameraManager::RELAX);
		CameraMgr->SetDestination(&_cameraPos);
	}

	p_pEvent->RenderOrgan();
}

void CEventStageWorkerDie::Exit(CEventStage* p_pEvent){
	
}

bool CEventStageWorkerDie::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// Furnace 이벤트
///////////////////////////////////////////////////////////
void CEventStageFurnace::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	AIMgr->GetDustKid()->SetDestinationX(0.0f);

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(AIMgr->GetHero()->GetBody()->GetPriPos()->x, AIMgr->GetHero()->GetBody()->GetPriPos()->y + 700.0f, -800.0f);

	CameraMgr->GetCamera()->GetPosition(&_cameraPos);

	CameraMgr->SetDestination(&t_vPos);

	EventMgr->ReadText("./script/Event/Furnace.txt");

	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_GATEKEEPER, Msg_Event, NO_ADDITIONAL_INFO);
}

void CEventStageFurnace::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	switch(EventMgr->GetIndex()){
		case 4:
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_GATEKEEPER, Msg_Event, NO_ADDITIONAL_INFO);
			EventMgr->NextText();
			break;
		case 5:
			CameraMgr->SetDestinationX(AIMgr->GetGateKeeper()->GetBody()->GetPriPos()->x - 100.0f);

			if(t_vPos.x >= AIMgr->GetGateKeeper()->GetBody()->GetPriPos()->x - 150.0f){
				EventMgr->NextText();
			}			
			break;
		case 7:
			CameraMgr->SetDestinationX(AIMgr->GetHero()->GetBody()->GetPriPos()->x);
			CameraMgr->GetCamera()->GetPosition(&t_vPos);

			if(t_vPos.x <= CameraMgr->GetDestination()->x + 200.0f)
				EventMgr->NextText();
			break;
		default:
			if(EventMgr->NextText()){
				p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
				CameraMgr->SetMode(CCameraManager::RELAX);
				CameraMgr->SetDestination(&_cameraPos);
			}
			break;
	}

	p_pEvent->RenderOrgan();
}

void CEventStageFurnace::Exit(CEventStage* p_pEvent){
	
}

bool CEventStageFurnace::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// GateKeeperDie 이벤트
///////////////////////////////////////////////////////////
void CEventStageGateKeeperDie::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(AIMgr->GetHero()->GetBody()->GetPriPos()->x, AIMgr->GetHero()->GetBody()->GetPriPos()->y + 200.0f, -710.0f);

	CameraMgr->GetCamera()->GetPosition(&_cameraPos);

	CameraMgr->SetDestination(&t_vPos);

	EventMgr->ReadText("./script/Event/GateKeeperDie.txt");
}

void CEventStageGateKeeperDie::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	if(EventMgr->NextText()){
		p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
		CameraMgr->SetMode(CCameraManager::RELAX);
		CameraMgr->SetDestination(&_cameraPos);
	}

	p_pEvent->RenderOrgan();
}

void CEventStageGateKeeperDie::Exit(CEventStage* p_pEvent){
	
}

bool CEventStageGateKeeperDie::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// Chimney 이벤트
///////////////////////////////////////////////////////////
void CEventStageChimney::Enter(CEventStage* p_pEvent){
	AIMgr->GetDustKid()->SetDestinationX(0.0f);

	CameraMgr->GetCamera()->GetPosition(&_cameraPos);

	EventMgr->ReadText("./script/Event/Chimney.txt");
}

void CEventStageChimney::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();
	CBody* t_pCartBody = AIMgr->GetCart()->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	switch(EventMgr->GetIndex()){
		case 3:
			AIMgr->GetHero()->GetBody()->SetRow(CBaseObject::RIGHT);
			t_pCartBody->SetRow(CBaseObject::RIGHT);

			if(t_pCartBody->GetRow() == CBaseObject::RIGHT){
				t_pOrgan->GetPriPos()->x = t_pCartBody->GetPriPos()->x - 29.0f;
				t_pOrgan->GetPriPos()->y = t_pCartBody->GetPriPos()->y + 47.0f;
			}
			else if(t_pCartBody->GetRow() == CBaseObject::LEFT){
				t_pOrgan->GetPriPos()->x = t_pCartBody->GetPriPos()->x + 29.0f;
				t_pOrgan->GetPriPos()->y = t_pCartBody->GetPriPos()->y + 47.0f;
			}

			EventMgr->NextText();
			break;
		default:
			if(EventMgr->NextText()){
				p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
				CameraMgr->SetMode(CCameraManager::RELAX);
				CameraMgr->SetDestination(&_cameraPos);
			}
			break;
	}

	p_pEvent->RenderOrgan();
}

void CEventStageChimney::Exit(CEventStage* p_pEvent){
	
}

bool CEventStageChimney::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// DustBridge 이벤트
///////////////////////////////////////////////////////////
void CEventStageDustBridge::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	AIMgr->GetDustKid()->SetDestinationX(0.0f);

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(AIMgr->GetHero()->GetBody()->GetPriPos()->x, AIMgr->GetHero()->GetBody()->GetPriPos()->y + 300.0f, -700.0f);

	CameraMgr->GetCamera()->GetPosition(&_cameraPos);

	CameraMgr->SetDestination(&t_vPos);

	EventMgr->ReadText("./script/Event/DustBridge.txt");

	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_DUSTKING, Msg_Event, NO_ADDITIONAL_INFO);
}

void CEventStageDustBridge::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	switch(EventMgr->GetIndex()){
		case 0:
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_DUSTKING, Msg_Event, NO_ADDITIONAL_INFO);
			EventMgr->NextText();
			break;
		case 4:
			p_pEvent->SetTimer(3000);
			EventMgr->NextText();
			break;
		case 5:
			CameraMgr->SetDestinationX(AIMgr->GetDustKing()->GetBody()->GetPriPos()->x);
			if(p_pEvent->GetTimer()->IsElapseTimer()){
				CameraMgr->SetDestinationX(AIMgr->GetHero()->GetBody()->GetPriPos()->x);
				CameraMgr->GetCamera()->GetPosition(&t_vPos);

				if(t_vPos.x <= CameraMgr->GetDestination()->x + 200.0f)
					EventMgr->NextText();
			}
			break;
		default:
			if(EventMgr->NextText()){
				p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
				CameraMgr->SetMode(CCameraManager::RELAX);
				CameraMgr->SetDestination(&_cameraPos);
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_DUSTKING, Msg_Ready, NO_ADDITIONAL_INFO);
			}
			break;
	}

	p_pEvent->RenderOrgan();
}

void CEventStageDustBridge::Exit(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::RELAX);
}

bool CEventStageDustBridge::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// DustKingDie 이벤트
///////////////////////////////////////////////////////////
void CEventStageDustKingDie::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(AIMgr->GetHero()->GetBody()->GetPriPos()->x, AIMgr->GetHero()->GetBody()->GetPriPos()->y + 200.0f, -710.0f);

	CameraMgr->GetCamera()->GetPosition(&_cameraPos);

	CameraMgr->SetDestination(&t_vPos);

	EventMgr->ReadText("./script/Event/DustKingDie.txt");
}

void CEventStageDustKingDie::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	if(EventMgr->NextText()){
		p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
		CameraMgr->SetMode(CCameraManager::RELAX);
		CameraMgr->SetDestination(&_cameraPos);
	}

	p_pEvent->RenderOrgan();
}

void CEventStageDustKingDie::Exit(CEventStage* p_pEvent){
	
}

bool CEventStageDustKingDie::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// GoodHope Intro 이벤트
///////////////////////////////////////////////////////////
void CEventStageGoodHopeIntro::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	EventMgr->ReadText("./script/Event/GoodHopeIntro.txt");

	p_pEvent->SetTimer(3500);
}

void CEventStageGoodHopeIntro::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	switch(EventMgr->GetIndex()){
		case 0:
			CameraMgr->SetDestinationX(StageMgr->GetStage()->GetPriPos()->x - StageMgr->GetStage()->GetWidthHalf() + 400.0f);
			if(p_pEvent->GetTimer()->IsElapseTimer()){
				CameraMgr->SetDestinationX(AIMgr->GetHero()->GetBody()->GetPriPos()->x - 200.0f);
				EventMgr->NextText();	
			}
			break;
		default:
			if(EventMgr->NextText()){
				p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
				CameraMgr->SetMode(CCameraManager::RELAX);
			}
			break;
	}

	p_pEvent->RenderOrgan();
}

void CEventStageGoodHopeIntro::Exit(CEventStage* p_pEvent){
	EventMgr->EntityInEvent();

	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_HERO, Msg_Usual, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_CART, Msg_Usual, NO_ADDITIONAL_INFO);
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_EVENTSTAGE, ID_FLOWER, Msg_Usual, NO_ADDITIONAL_INFO);
	CameraMgr->SetMode(CCameraManager::RELAX);
}

bool CEventStageGoodHopeIntro::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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
// GoodHope 이벤트
///////////////////////////////////////////////////////////
void CEventStageGoodHope::Enter(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::EVENT);

	EventMgr->ReadText("./script/Event/GoodHope.txt");

	EventMgr->EntityInEvent();
}

void CEventStageGoodHope::Execute(CEventStage* p_pEvent){
	COrgan* t_pOrgan = AIMgr->GetFlower()->GetBody();

	AIMgr->GetHero()->SetCanMove(false);
	AIMgr->GetHero()->GetBody()->SetVelocity(0.0f);

	switch(EventMgr->GetIndex()){
		case 0:
			AIMgr->GetHero()->GetBody()->SetRow(CBaseObject::RIGHT);
			EventMgr->NextText();
			break;
		case 5:
			CameraMgr->SetDestinationX(AIMgr->GetFlower()->GetBody()->GetPriPos()->x);
			EventMgr->NextText();
			break;
		default:
			if(EventMgr->NextText()){
				EventMgr->GetEventWorldMap()->_ending = true;
				EventMgr->GetEventWorldMap()->GetFSM()->ChangeState(EventWorldMapEnding->Instance());
				p_pEvent->GetFSM()->ChangeState(EventStageCheck->Instance());
				StageMgr->SetbIsGetOutStage(true);
				EffectMgr->SetPlaneUse(true);
				EffectMgr->SetPlaneType(CEffectManager::BLACK);
				StageMgr->SetbIsFadeInOut(true);
			}
			break;
	}

	p_pEvent->RenderOrgan();
}

void CEventStageGoodHope::Exit(CEventStage* p_pEvent){
	CameraMgr->SetMode(CCameraManager::RELAX);
	EventMgr->EntityInEvent();
}

bool CEventStageGoodHope::OnMessage(CEventStage* agent, const Telegram& msg){
	switch(msg.Msg){
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