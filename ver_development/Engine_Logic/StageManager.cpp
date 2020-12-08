#include "../BaseHeader.h"

CStageManager::CStageManager(){
	_vHeroStartPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_nStageType = -1;
	_nArea = -1;
	_fStageHeight = 0.0f;
	_bIsGetOutStage = false;
	_bIsFadeInOut = false;
	_stage = NULL;

	_bIsGetOutStage = false;

	_homeClear = false;
	_scrapMountainClear = false;
	_furnaceClear = false;
	_chimneyClear = false;
	_dustBridgeClear = false;
}

CStageManager::~CStageManager(){

}

void CStageManager::Update(CSection* pSection){
	CDListIterator<CCharacterEntity*> itr;

	// 주인공과 유닛들 스테이지 시작 좌표 초기화
	itr = AIMgr->GetOurForceList()->GetIterator();

	AIMgr->GetHero()->GetFSM()->ChangeState(HeroStand->Instance());
	AIMgr->GetCart()->GetFSM()->ChangeState(CartUsual->Instance());

	switch(_nStageType){
		case HOME:		
			pSection->GetFSM()->ChangeState(StageHomeShow->Instance());

			AIMgr->GetHero()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x + 350.0f;
			AIMgr->GetCart()->GetBody()->GetPriPos()->x = AIMgr->GetHero()->GetBody()->GetPriPos()->x + 100;
			AIMgr->GetCart()->GetBody()->SetRow(CBaseObject::LEFT);
			AIMgr->GetCart()->GetBody()->SetRow(CBaseObject::LEFT);

			for(itr.Start(); itr.Valid(); itr.Forth()){
				itr.Item()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x + 150.0f;
			}
			break;
		case SCRAPMOUNTAIN:
			pSection->GetFSM()->ChangeState(StageMountainShow->Instance());

			AIMgr->GetHero()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x - 800.0f;
			AIMgr->GetCart()->GetBody()->GetPriPos()->x = AIMgr->GetHero()->GetBody()->GetPriPos()->x - 100;
			AIMgr->GetCart()->GetBody()->SetRow(CBaseObject::RIGHT);
			AIMgr->GetCart()->GetBody()->SetRow(CBaseObject::RIGHT);

			for(itr.Start(); itr.Valid(); itr.Forth()){
				itr.Item()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x -600.0f;
			}

			switch(this->_nArea){
				case 0:
					// 꼬마먼지 위치 초기화	
					AIMgr->ResetDustKid();
					AIMgr->GetDustKid()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x - 100.0f;
					AIMgr->GetDustKid()->GetBody()->GetPriPos()->y = GetStageHeight() + AIMgr->GetDustKid()->GetBody()->GetHeightHalf();
					break;
				case 1:
					// 미니워커 위치 초기화
					AIMgr->ResetMiniWorker();
					AIMgr->GetMiniWorker()->GetBody()->GetPriPos()->y = GetStageHeight() + AIMgr->GetMiniWorker()->GetAttachmentFromType(CMiniWorker::BODY)->GetHeightHalf();
					AIMgr->GetMiniWorker()->GetBody()->SetRow(CBaseObject::LEFT);
					break;
				case 2:
					// 마더워커 위치 초기화
					AIMgr->ResetWorker();
					AIMgr->GetWorker()->GetBody()->GetPriPos()->y = GetStageHeight() + AIMgr->GetWorker()->GetAttachmentFromType(CWorker::BODY)->GetHeightHalf();
					AIMgr->GetWorker()->GetBody()->SetRow(CBaseObject::LEFT);
					break;
			}
			break;
		case FURNACE:
			AIMgr->ResetGateKeeper();
			AIMgr->GetGateKeeper()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x + 400.0f;
			AIMgr->GetGateKeeper()->GetBody()->GetPriPos()->y = GetStageHeight() + AIMgr->GetDustKid()->GetBody()->GetHeightHalf() + 20.0f;

			pSection->GetFSM()->ChangeState(StageFurnaceShow->Instance());

			AIMgr->GetHero()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x - 600.0f;
			AIMgr->GetCart()->GetBody()->GetPriPos()->x = AIMgr->GetHero()->GetBody()->GetPriPos()->x - 100;
			AIMgr->GetCart()->GetBody()->SetRow(CBaseObject::RIGHT);
			AIMgr->GetCart()->GetBody()->SetRow(CBaseObject::RIGHT);

			for(itr.Start(); itr.Valid(); itr.Forth()){
				itr.Item()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x - 400.0f;
			}
			break;
		case CHIMNEY:
			pSection->GetFSM()->ChangeState(StageChimneyShow->Instance());

			AIMgr->GetHero()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x - 200.0f;
			AIMgr->GetCart()->GetBody()->GetPriPos()->x = AIMgr->GetHero()->GetBody()->GetPriPos()->x + 100;
			AIMgr->GetCart()->GetBody()->SetRow(CBaseObject::LEFT);
			AIMgr->GetCart()->GetBody()->SetRow(CBaseObject::LEFT);

			for(itr.Start(); itr.Valid(); itr.Forth()){
				itr.Item()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x - 400.0f;
			}
			break;
		case DUSTBRIDGE:
			AIMgr->ResetDustKing();
			AIMgr->GetDustKing()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x;
			AIMgr->GetDustKing()->GetBody()->GetPriPos()->y = GetStageHeight() + AIMgr->GetDustKid()->GetBody()->GetHeightHalf();

			pSection->GetFSM()->ChangeState(StageDustBridgeShow->Instance());

			AIMgr->GetHero()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x + 850.0f;
			AIMgr->GetCart()->GetBody()->GetPriPos()->x = AIMgr->GetHero()->GetBody()->GetPriPos()->x + 100;
			AIMgr->GetHero()->GetBody()->SetRow(CBaseObject::LEFT);
			AIMgr->GetCart()->GetBody()->SetRow(CBaseObject::LEFT);

			for(itr.Start(); itr.Valid(); itr.Forth()){
				itr.Item()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x + 700.0f;
			}
			break;
		case GOODHOPE:
			pSection->GetFSM()->ChangeState(StageGoodHopeShow->Instance());

			AIMgr->GetHero()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x + 750.0f;
			AIMgr->GetCart()->GetBody()->GetPriPos()->x = AIMgr->GetHero()->GetBody()->GetPriPos()->x + 100;
			AIMgr->GetHero()->GetBody()->SetRow(CBaseObject::LEFT);
			AIMgr->GetCart()->GetBody()->SetRow(CBaseObject::LEFT);

			for(itr.Start(); itr.Valid(); itr.Forth()){
				itr.Item()->GetBody()->GetPriPos()->x = GetStage()->GetPriPos()->x + 550.0f;
			}
			break;
		default:
			break;
	}
	
	for(itr.Start(); itr.Valid(); itr.Forth()){
		itr.Item()->GetBody()->GetPriPos()->y = GetStageHeight() + itr.Item()->GetBody()->GetHeightHalf();
	}

	AIMgr->GetHero()->GetBody()->GetPriPos()->y = GetStageHeight() + AIMgr->GetHero()->GetBody()->GetHeightHalf();
	AIMgr->GetCart()->GetBody()->GetPriPos()->y = GetStageHeight() + AIMgr->GetCart()->GetBody()->GetHeightHalf();
	AIMgr->GetCart()->GetBody()->SetRow((CBaseObject::DIRECTION)AIMgr->GetHero()->GetBody()->GetRow());	
}

void CStageManager::SetStage(int p_nType){
	_nStageType = p_nType;

	switch(_nStageType){
		case WORLDMAP:
			_stage = ObjectMgr->GetEntity(CBaseObject::WORLDMAP)->GetBody();
			break;
		case HOME:		
			_stage = ObjectMgr->GetEntity(CBaseObject::STAGEHOME)->GetBody();
			SetStageHeight(_stage->GetPriPos()->y - 410.0f);
			break;
		case SCRAPMOUNTAIN:
			_stage = ObjectMgr->GetEntity(CBaseObject::STAGEMOUNTAIN)->GetBody();
			SetStageHeight(_stage->GetPriPos()->y - 470.0f);
			break;
		case FURNACE:
			_stage = ObjectMgr->GetEntity(CBaseObject::STAGEFURNACE)->GetBody();
			SetStageHeight(_stage->GetPriPos()->y - 470.0f);
			break;
		case CHIMNEY:
			_stage = ObjectMgr->GetEntity(CBaseObject::STAGECHIMNEY)->GetBody();
			SetStageHeight(_stage->GetPriPos()->y - 440.0f);
			break;
		case DUSTBRIDGE:
			_stage = ObjectMgr->GetEntity(CBaseObject::STAGEDUSTBRIDGE)->GetBody();
			SetStageHeight(_stage->GetPriPos()->y);
			break;
		case GOODHOPE:
			_stage = ObjectMgr->GetEntity(CBaseObject::STAGEGOODHOPE)->GetBody();
			SetStageHeight(_stage->GetPriPos()->y - 520.0f);
			break;
		case NOTHING:
			_stage = NULL;
			break;
		default:
			break;
	}
}

void CStageManager::ComputeMoveLimitStage(){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	switch(GetStageType()){
		case FURNACE:
			if(t_pHeroBody->GetPriPos()->x > GetStage()->GetPriPos()->x + GetStage()->GetWidthHalf() - 535.0f){
				if(t_pHeroBody->GetPriPos()->x > GetStage()->GetPriPos()->x + GetStage()->GetWidthHalf() - 430.0f){
					if(t_pHeroBody->GetRow() == CBaseObject::RIGHT){
						AIMgr->GetHero()->SetCanMove(false);
					}
					else{
						AIMgr->GetHero()->SetCanMove(true);
					}

					CDListIterator<CCharacterEntity*> itr = AIMgr->GetOurForceList()->GetIterator();

					for(itr.Start(); itr.Valid(); itr.Forth()){
						if(itr.Item()->GetBody()->GetPriPos()->x > GetStage()->GetPriPos()->x + GetStage()->GetWidthHalf() - 430.0f){
							itr.Item()->GetBody()->SetRow(CBaseObject::LEFT);
							itr.Item()->GetBody()->GetPriPos()->x -= itr.Item()->GetBody()->GetVelocity();
						}
					}
				}
			}
			break;
		case CHIMNEY:
			if(t_pHeroBody->GetPriPos()->x > StageMgr->GetStage()->GetPriPos()->x + StageMgr->GetStage()->GetWidthHalf() - 1019.0f){
				if(t_pHeroBody->GetPriPos()->x > StageMgr->GetStage()->GetPriPos()->x + StageMgr->GetStage()->GetWidthHalf() - 970.0f){
					if(t_pHeroBody->GetRow() == CBaseObject::RIGHT){
						AIMgr->GetHero()->SetCanMove(false);
					}
					else{
						AIMgr->GetHero()->SetCanMove(true);
					}

					CDListIterator<CCharacterEntity*> itr = AIMgr->GetOurForceList()->GetIterator();

					for(itr.Start(); itr.Valid(); itr.Forth()){
						if(itr.Item()->GetBody()->GetPriPos()->x > GetStage()->GetPriPos()->x + StageMgr->GetStage()->GetWidthHalf() - 970.0f){
							itr.Item()->GetBody()->SetRow(CBaseObject::LEFT);
							itr.Item()->GetBody()->GetPriPos()->x -= itr.Item()->GetBody()->GetVelocity();
						}
					}
				}
			}
			break;
		default:
			break;
	}
}