#include "../BaseHeader.h"

CAIManager::CAIManager(){
	_hero = new CHero(ID_HERO);
	EntityDB->RegisterEntity(_hero);

	_cart = new CCart(ID_CART);
	EntityDB->RegisterEntity(_cart);

	_flower = new CFlower(ID_FLOWER);
	EntityDB->RegisterEntity(_flower);

	AIMgr->InsertOurForce(CBluePrint::WAGOO); // WagooWagoo Iron 생성하고 시작

	_moveRange._min = D3DXVECTOR3(-400.0f, -200.0f, 0.0f);
	_moveRange._max = D3DXVECTOR3(400.0f, 200.0f, 0.0f);

	_attackRange._min = D3DXVECTOR3(0.0f, -200.0f, 0.0f);
	_attackRange._max = D3DXVECTOR3(600.0f, -200.0f, 0.0f);

	CreateDustKid();
	CreateWorker();
	CreateMiniWorker();
	CreateGateKeeper();
	CreateDustKing();

	_commandType = RUNAWAY;

	_attackTimeGap = 4000;
	_avoidTimeGap = 3000;
	_defenseTimeGap = 2000;

	SetCommandTime(GetAttackTimeGap());
	SetCommandTimeGap(GetCommandTimeGap());
}

CAIManager::~CAIManager(){
	// 반복자 생성
	CDListIterator<CCharacterEntity*> itr;
	
	// 초기화
	itr = GetOurForceList()->GetIterator();
	
	for(itr.Start(); itr.Valid(); itr.Forth()){
		GetOurForceList()->Remove(itr);
	}

//	d3d::Delete<CWorker*>(_worker);	// 오류가 난다?
}

void CAIManager::HeroUpdate(){
	GetHero()->BoundUpdate();
	GetHero()->Update();
	//GetHero()->BoundRender();
}

void CAIManager::CartUpdate(){
	GetCart()->BoundUpdate();
	GetCart()->Update();
}

void CAIManager::FlowerUpdate(){
	GetFlower()->BoundUpdate();
	GetFlower()->Update();
//	GetFlower()->BoundRender();
}

void CAIManager::DustKidUpdate(){
	GetDustKid()->ComputeDamageBound();
	GetDustKid()->ComputeEntityBound();
	GetDustKid()->BoundUpdate();
	GetDustKid()->Update();
	//GetDustKid()->BoundRender();
}

void CAIManager::DustKingUpdate(){
	GetDustKing()->ComputeDamageBound();
	GetDustKing()->ComputeEntityBound();
	GetDustKing()->BoundUpdate();
	GetDustKing()->Update();
	//GetDustKing()->BoundRender();
}

void CAIManager::WorkerUpdate(){
	GetWorker()->ComputeDamageBound();
	GetWorker()->ComputeEntityBound();
	GetWorker()->BoundUpdate();
	GetWorker()->Update();
	//GetWorker()->BoundRender();
}

void CAIManager::MiniWorkerUpdate(){
	GetMiniWorker()->ComputeDamageBound();
	GetMiniWorker()->ComputeEntityBound();
	GetMiniWorker()->BoundUpdate();
	GetMiniWorker()->Update();
	//GetMiniWorker()->BoundRender();
}

void CAIManager::GateKeeperUpdate(){
	GetGateKeeper()->ComputeDamageBound();
	GetGateKeeper()->ComputeEntityBound();
	GetGateKeeper()->BoundUpdate();
	GetGateKeeper()->Update();
	//GetGateKeeper()->BoundRender();
}

void CAIManager::AIUpdate(){
	CDListIterator<CCharacterEntity*> itr;
	
	// 초기화
	itr = GetOurForceList()->GetIterator();
	
	for(itr.Start(); itr.Valid(); itr.Forth()){
		itr.Item()->BoundUpdate();
		itr.Item()->Update();
		//itr.Item()->BoundRender();
	}
}

bool CAIManager::AILiveCheckToYawoAndKirit(){
	CDListIterator<CCharacterEntity*> itr = _OurForceList.GetIterator();

	bool t_yawoIsLive;
	bool t_kiritIsLive;
	bool t_otherIsLive = false;

	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(itr.Item()->GetOwner() == CBaseObject::YAWO)
			t_yawoIsLive = itr.Item()->GetLive();
		else if(itr.Item()->GetOwner() == CBaseObject::KIRIT)
			t_kiritIsLive = itr.Item()->GetLive();
		else if(itr.Item()->GetOwner() == CBaseObject::TINKLE)
			continue;
		else if(t_otherIsLive == false)
			t_otherIsLive = itr.Item()->GetLive();
	}

	if(t_otherIsLive)
		return false;
	else if(t_yawoIsLive || t_kiritIsLive && !t_otherIsLive)
		return true;
	else
		return false;
}

void CAIManager::AIIsLive(){
	CDListIterator<CCharacterEntity*> itr;
	
	// 초기화
	itr = GetOurForceList()->GetIterator();
	
	static int t_nDeath = 0;
	static int t_nCount = 0;

	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(itr.Item()->GetOwner() == CBaseObject::TINKLE) continue;

		if(!itr.Item()->GetLive())
			t_nDeath++;
		t_nCount++;		
	}

	if(t_nDeath == t_nCount){
		t_nDeath = 0;
		t_nCount = 0;

		EventMgr->GetEventStage()->GetFSM()->ChangeState(EventStageRunAway->Instance());
	}
	else{
		t_nDeath = 0;
		t_nCount = 0;
	}
}

void CAIManager::InitOurForce(){
	CDListIterator<CCharacterEntity*> itr;
	
	// 초기화
	itr = GetOurForceList()->GetIterator();
	
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(itr.Item()->GetLive())
			itr.Item()->SetHealthy((int)itr.Item()->GetMaxHealthy());
		else{
			CBaseObject::OWNER t_eOwner;

			t_eOwner = itr.Item()->GetOwner();

			EntityDB->RemoveEntity(itr.Item());
			d3d::Delete<CCharacterEntity*>(itr.Item());

			switch(t_eOwner){
				case CBaseObject::WAGOO:
					itr.Item() = new CWagoo(ID_WAGOO);
					break;
				case CBaseObject::KIRIT:
					itr.Item() = new CKirit(ID_KIRIT);
					break;
				case CBaseObject::WOOWO:
					itr.Item() = new CWoowo(ID_WOOWO);
					break;
				case CBaseObject::YAWO:
					itr.Item() = new CYawo(ID_YAWO);
					break;
				default:
					break;
			}

			EntityDB->RegisterEntity(itr.Item());

			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, 0, itr.Item()->ID(), Msg_Usual, NO_ADDITIONAL_INFO);
		}
	}
}

void CAIManager::OrderToAI(){
	switch(StageMgr->GetStageType()){
		case CStageManager::SCRAPMOUNTAIN:
		case CStageManager::FURNACE:
		case CStageManager::DUSTBRIDGE:
			if(this->GetCommandTime()->IsElapseTimer()){
				if(::GetAsyncKeyState('A') == 0xffff8001 && EffectMgr->GetCommand(ATTACK)->GetMtrlArray()->Get(0,0).Diffuse.a >= 1.0f && !EffectMgr->GetCommandUse()){
					_commandType = ATTACK;

					CheckAttackRange();
					EffectMgr->SetCommandEffect(_commandType);
					SetCommandTimeGap(GetAttackTimeGap());
					SetCommandTime(GetCommandTimeGap());
				}
				if(::GetAsyncKeyState('S') == 0xffff8001 && EffectMgr->GetCommand(RUNAWAY)->GetMtrlArray()->Get(0,0).Diffuse.a >= 1.0f && !EffectMgr->GetCommandUse()){
					_commandType = RUNAWAY;

					CDListIterator<CCharacterEntity*> itr;
				
					// 초기화
					itr = GetOurForceList()->GetIterator();
					
					for(itr.Start(); itr.Valid(); itr.Forth()){
						itr.Item()->SetLookEnemy(false);
						Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_HERO, itr.Item()->ID(), Msg_RunAway, NO_ADDITIONAL_INFO);
					}
					EffectMgr->SetCommandEffect(_commandType);
					SetCommandTimeGap(GetAvoidTimeGap());
					SetCommandTime(GetCommandTimeGap());
				}
				if(::GetAsyncKeyState('D') == 0xffff8001 && EffectMgr->GetCommand(DEFENSE)->GetMtrlArray()->Get(0,0).Diffuse.a >= 1.0f && !EffectMgr->GetCommandUse()){
					_commandType = DEFENSE;

					CDListIterator<CCharacterEntity*> itr;
				
					// 초기화
					itr = GetOurForceList()->GetIterator();
					
					for(itr.Start(); itr.Valid(); itr.Forth()){
						itr.Item()->SetLookEnemy(false);
						Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_HERO, itr.Item()->ID(), Msg_Defense, NO_ADDITIONAL_INFO);
					}
					EffectMgr->SetCommandEffect(_commandType);
					SetCommandTimeGap(GetDefenseTimeGap());
					SetCommandTime(GetCommandTimeGap());
				}
			}
			break;
	}
}

int CAIManager::ComputeAverageDamage(float p_fMin, float p_fMax){
	float t_fTemp = p_fMax - p_fMin;

    t_fTemp = (float)(rand() % (int)t_fTemp);

	if(this->BuffCharacterCheck()) return (int)((p_fMin + t_fTemp) * 1.3f);
	else return (int)(p_fMin + t_fTemp);
}

void CAIManager::CheckAttackRange(){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CDListIterator<CCharacterEntity*> itrOur = GetOurForceList()->GetIterator();;
	CBody* t_pBody = NULL;

	switch(StageMgr->GetStageType()){
		case CStageManager::DUSTBRIDGE:
			t_pBody = GetDustKing()->GetBody();
			break;
		case CStageManager::SCRAPMOUNTAIN:
			switch(StageMgr->GetAreaNumber()){
				case 0:					
					t_pBody = GetDustKid()->GetBody();
					break;
				case 1:
					t_pBody = GetMiniWorker()->GetBody();
					break;
				case 2:
					t_pBody = GetWorker()->GetBody();					
					break;
			}
			break;
		case CStageManager::FURNACE:
			t_pBody = GetGateKeeper()->GetBody();
			break;
	}

	for(itrOur.Start(); itrOur.Valid(); itrOur.Forth()){
		if(!itrOur.Item()->GetLookEnemy()){
			if(t_pHeroBody->GetPriPos()->x < t_pBody->GetPriPos()->x){
				if(t_pHeroBody->GetPriPos()->x + _attackRange._max.x > t_pBody->GetPriPos()->x){
					itrOur.Item()->SetLookEnemy(true);
					itrOur.Item()->GetBody()->SetRow(CBaseObject::RIGHT);	
					Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_HERO, itrOur.Item()->ID(), Msg_Attack, NO_ADDITIONAL_INFO);
				}
				else{
					itrOur.Item()->SetLookEnemy(false);
					EffectMgr->InsertQuestionMark(itrOur.Item()->GetBody());
				}
			}
			else{
				if(t_pHeroBody->GetPriPos()->x - _attackRange._max.x < t_pBody->GetPriPos()->x){
					itrOur.Item()->SetLookEnemy(true);
					itrOur.Item()->GetBody()->SetRow(CBaseObject::LEFT);	
					Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_HERO, itrOur.Item()->ID(), Msg_Attack, NO_ADDITIONAL_INFO);
				}
				else{
					itrOur.Item()->SetLookEnemy(false);
					EffectMgr->InsertQuestionMark(itrOur.Item()->GetBody());
				}
			}
		}
	}
}

void CAIManager::CheckMoveRange(){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CDListIterator<CCharacterEntity*> itr;
	
	// 초기화
	itr = GetOurForceList()->GetIterator();
	
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(t_pHeroBody->GetPriPos()->x + _moveRange._min.x > itr.Item()->GetBody()->GetPriPos()->x){
			itr.Item()->GetBody()->SetRow(CBaseObject::RIGHT);	
		}
		if(t_pHeroBody->GetPriPos()->x + _moveRange._max.x < itr.Item()->GetBody()->GetPriPos()->x){
			itr.Item()->GetBody()->SetRow(CBaseObject::LEFT);	
		}
	}
}

void CAIManager::CheckMoveRange(CBody* p_pBody){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();

	if(t_pHeroBody->GetPriPos()->x + _moveRange._min.x > p_pBody->GetPriPos()->x){
		p_pBody->SetRow(CBaseObject::RIGHT);	
	}
	if(t_pHeroBody->GetPriPos()->x + _moveRange._max.x < p_pBody->GetPriPos()->x){
		p_pBody->SetRow(CBaseObject::LEFT);	
	}
}

void CAIManager::InsertOurForce(CBluePrint::BLUEPRINTTYPE p_eBluePrintType){
	switch(p_eBluePrintType){
		case CBluePrint::WAGOO:
			GetOurForceList()->Append(new CWagoo(ID_WAGOO));
			EntityDB->RegisterEntity(GetOurForceEntityFromOwner(CBaseObject::WAGOO));
			break;
		case CBluePrint::WOOWO:
			GetOurForceList()->Append(new CWoowo(ID_WOOWO));
			EntityDB->RegisterEntity(GetOurForceEntityFromOwner(CBaseObject::WOOWO));
			break;
		case CBluePrint::YAWO:
			GetOurForceList()->Append(new CYawo(ID_YAWO));
			EntityDB->RegisterEntity(GetOurForceEntityFromOwner(CBaseObject::YAWO));
			break;
		case CBluePrint::KIRIT:
			GetOurForceList()->Append(new CKirit(ID_KIRIT));
			EntityDB->RegisterEntity(GetOurForceEntityFromOwner(CBaseObject::KIRIT));
			break;
		case CBluePrint::TINKLE:
			GetOurForceList()->InsertBefore(GetOurForceList()->GetIterator(), new CTinkle(ID_TINKLE));
			EntityDB->RegisterEntity(GetOurForceEntityFromOwner(CBaseObject::TINKLE));
			break;
		default:
			break;
	}
}

CCharacterEntity* CAIManager::GetOurForceEntityFromOwner(CBaseObject::Owner p_eOwner){
	CDListIterator<CCharacterEntity*> itr;

	itr = _OurForceList.GetIterator();
	
	for(itr.Start(); itr.Valid(); itr.Forth()){
		// 찾으려는 Owner 타입을 찾아서 COrganEntity*로 리턴
		if(itr.Item()->GetOwner() == p_eOwner){
			return itr.Item();
		}
	}
	return false;
}

CCharacterEntity* CAIManager::GetOurForceEntityFromID(int p_nID){
	CDListIterator<CCharacterEntity*> itr;
	
	itr = _OurForceList.GetIterator();
	
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(itr.Item()->ID() == p_nID){
			return itr.Item();
		}
	}
	return false;
}

bool CAIManager::BuffCharacterCheck(){
	// 버프 캐릭 확인
	CDListIterator<CCharacterEntity*> itrEntity = AIMgr->GetOurForceList()->GetIterator();

	for(itrEntity.Start(); itrEntity.Valid(); itrEntity.Forth()){			
		if(itrEntity.Item()->ID() == ID_TINKLE){
			return true;
		}
	}
	return false;
}