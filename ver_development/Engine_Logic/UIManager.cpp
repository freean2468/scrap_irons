#include "../BaseHeader.h"

CUIManager::CUIManager(){
	_UIList.Append(new CProduction(ID_PRODUCTION));
	EntityDB->RegisterEntity(GetUI(CBaseObject::PRODUCTION));

	_UIList.Append(new CProducing(ID_PRODUCING));
	EntityDB->RegisterEntity(GetUI(CBaseObject::PRODUCING));

	_UIList.Append(new CInteract(ID_INTERACT));
	EntityDB->RegisterEntity(GetUI(CBaseObject::INTERACT));

	_inventory = new CInventory(ID_INVENTORY);
	EntityDB->RegisterEntity(_inventory);
	_UIList.Append(_inventory);

	_bluePrintList = new CBluePrintList(ID_BLUEPRINTLIST);
	EntityDB->RegisterEntity(_bluePrintList);
	_UIList.Append(_bluePrintList);

	_commander = new CCommander(ID_COMMANDER);
	EntityDB->RegisterEntity(_commander);

	// Test를 위한 활성화
	GetAndActivatedBluePrint(new CBluePrint(CBluePrint::WAGOO));
	GetAndActivatedBluePrint(new CBluePrint(CBluePrint::WOOWO));
	GetAndActivatedBluePrint(new CBluePrint(CBluePrint::YAWO));
	GetAndActivatedBluePrint(new CBluePrint(CBluePrint::KIRIT));
	GetAndActivatedBluePrint(new CBluePrint(CBluePrint::TINKLE));


	D3DXVECTOR3 _vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);			// 위치 벡터
	D3DXVECTOR3 _vScale = D3DXVECTOR3(1.0f, 1.0f, 1.0f);		// 크기 벡터
	D3DXVECTOR3 _vRotate = D3DXVECTOR3(0.0f, 0.0f, 0.0f);		// 회전 벡터

	// font 초기화
	_pFont = d3d::IniFont(13, 6, 400, false, "맑은 고딕");
}

CUIManager::~CUIManager(){
	// 반복자 생성
	CDListIterator<COrganEntity*> itr;
	
	// _UIList로부터 반복자 초기화
	itr = _UIList.GetIterator();
	
	// _UIList를 훑으며
	for(itr.Start(); itr.Valid();){
		_UIList.Remove(itr);
	}

	// 반복자 생성
	CDListIterator<CSmallInfo*> itrSmallInfo;
	
	// _UIList로부터 반복자 초기화
	itrSmallInfo = _smallInfoList.GetIterator();
	
	// _UIList를 훑으며
	for(itrSmallInfo.Start(); itrSmallInfo.Valid();){
		_smallInfoList.Remove(itrSmallInfo);
	}
}

void CUIManager::UIUpdate(){
	_commander->Update();
	SmallInfoUpdate();

	UIMgr->GetUI(ID_PRODUCTION)->Update();
	UIMgr->GetUI(ID_BLUEPRINTLIST)->Update();
	UIMgr->GetUI(ID_INVENTORY)->Update();
	UIMgr->GetUI(ID_PRODUCING)->Update();
}

void CUIManager::PutItemInInventory(CItem* p_pItem){
	CInventory* t_pInven = UIMgr->GetInventory();

	t_pInven->PutItem(p_pItem);
}

void CUIManager::ActiveCommander(){
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, _commander->ID(), _commander->ID(), Msg_Activate, NO_ADDITIONAL_INFO);
}

void CUIManager::MinimizeCommander(){
	Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, _commander->ID(), _commander->ID(), Msg_Close, NO_ADDITIONAL_INFO);
}

void CUIManager::GetAndActivatedBluePrint(CBluePrint* p_pBluePrint){
	CBluePrintList* t_pList = UIMgr->GetBluePrintList();

	t_pList->InsertNewScroll(p_pBluePrint);
}

bool CUIManager::ActivateProduction(){
	COrganEntity* t_pEntity = AIMgr->GetHero();

	if(t_pEntity->GetBody()->GetPriPos()->x <= -300.0f){
		UIMgr->ActivateInteract(-440.0f, -250.0f);

		if(::GetAsyncKeyState('E') & 0xffff8001){
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, t_pEntity->ID(), ID_PRODUCTION, Msg_Activate, NO_ADDITIONAL_INFO);
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, t_pEntity->ID(), ID_HERO, Msg_Event, NO_ADDITIONAL_INFO);
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, t_pEntity->ID(), ID_INVENTORY, Msg_Activate, NO_ADDITIONAL_INFO);
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, t_pEntity->ID(), ID_BLUEPRINTLIST, Msg_InProduction, NO_ADDITIONAL_INFO);
		}
		return true;
	}
	return false;
}

void CUIManager::ActivateInteract(float p_fX, float p_fY){
	CBody* t_pBody = UIMgr->GetUI(CBaseObject::INTERACT)->GetBody();

	t_pBody->GetPriPos()->x = p_fX;
	t_pBody->GetPriPos()->y = p_fY;

	UIMgr->GetUI(ID_INTERACT)->Update();
}

void CUIManager::SmallInfoUpdate(){
	// 반복자 생성
	CDListIterator<CSmallInfo*> itr;
	
	// _UIList로부터 반복자 초기화
	itr = _smallInfoList.GetIterator();
	
	CBody* t_pBody;
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	static float t_fDeltaX = 0.0f;

	// _UIList를 훑으며
	for(itr.Start(); itr.Valid(); itr.Forth()){
		t_pBody = itr.Item()->GetBody();

		switch(StageMgr->GetStageType()){
			case CStageManager::DUSTBRIDGE:
				t_pBody->GetPriPos()->x = t_vPos.x + (SYSTEMWIDTH * 0.5f) - 50.0f - t_fDeltaX;
				t_pBody->SetRow(CBaseObject::LEFT);
				break;
			default:
				t_pBody->GetPriPos()->x = t_vPos.x - (SYSTEMWIDTH * 0.5f) + 50.0f + t_fDeltaX;
				t_pBody->SetRow(CBaseObject::RIGHT);
				break;
		}

		t_pBody->GetPriPos()->y = t_vPos.y + (SYSTEMHEIGHT * 0.5f) - 50.0f;
		t_pBody->GetPriPos()->z = 700.0f + t_vPos.z;
	
		itr.Item()->Update();

		t_fDeltaX += 75.0f;
	}

	t_fDeltaX = 0.0f;
}

bool CUIManager::ComputeBoundProductionCloseAndMouse(){
	COrganEntity* t_pEntity = UIMgr->GetUI(CBaseObject::PRODUCTION);
	CBody* t_pBody = t_pEntity->GetBody();
	CAttachment* t_pAtt = t_pEntity->GetAttachmentFromType(CProduction::CLOSE);
	
	float t_fX = EngineMgr->GetpInformation()->GetAdjustedX();
	float t_fY = EngineMgr->GetpInformation()->GetAdjustedY();

	if(t_pAtt->GetLeft() + t_pBody->GetPriPos()->x < t_fX &&
		t_pAtt->GetRight() + t_pBody->GetPriPos()->x > t_fX &&
		t_pAtt->GetTop() + t_pBody->GetPriPos()->y > t_fY &&
		t_pAtt->GetBottom() + t_pBody->GetPriPos()->y + 10.0f < t_fY){
			if(t_pAtt->GetMtrlArray()->Get(t_pAtt->GetRow(), t_pAtt->GetCol()).Diffuse.g > -1.0f)
				t_pAtt->GetMtrlArray()->Get(t_pAtt->GetRow(), t_pAtt->GetCol()).Diffuse.g -= 0.1f;
			if(t_pAtt->GetMtrlArray()->Get(t_pAtt->GetRow(), t_pAtt->GetCol()).Diffuse.b > -1.0f)
				t_pAtt->GetMtrlArray()->Get(t_pAtt->GetRow(), t_pAtt->GetCol()).Diffuse.b -= 0.1f;

			if(EngineMgr->GetLButtonState() == 1){
				t_pAtt->GetMtrlArray()->Get(t_pAtt->GetRow(), t_pAtt->GetCol()).Diffuse.g = 0.0f;
				t_pAtt->GetMtrlArray()->Get(t_pAtt->GetRow(), t_pAtt->GetCol()).Diffuse.b = 0.0f;

				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_PRODUCTION, ID_PRODUCING, Msg_Close, NO_ADDITIONAL_INFO);
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_PRODUCTION, ID_INVENTORY, Msg_Close, NO_ADDITIONAL_INFO);
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_PRODUCTION, ID_BLUEPRINTLIST, Msg_Close, NO_ADDITIONAL_INFO);
				UIMgr->GetBluePrintList()->SetSelectionList(false);
				CDListIterator<CBluePrintScroll*> itr = UIMgr->GetBluePrintList()->GetScrollList()->GetIterator();

				for(itr.Start(); itr.Valid(); itr.Forth()){
					itr.Item()->GetFSM()->ChangeState(BluePrintScrollMinimize->Instance());
				}
				return true;
			}
			return false;
	}

	if(t_pAtt->GetMtrlArray()->Get(t_pAtt->GetRow(), t_pAtt->GetCol()).Diffuse.g < 0.0f)
		t_pAtt->GetMtrlArray()->Get(t_pAtt->GetRow(), t_pAtt->GetCol()).Diffuse.g += 0.1f;
	if(t_pAtt->GetMtrlArray()->Get(t_pAtt->GetRow(), t_pAtt->GetCol()).Diffuse.b < 0.0f)
		t_pAtt->GetMtrlArray()->Get(t_pAtt->GetRow(), t_pAtt->GetCol()).Diffuse.b += 0.1f;

	return false;
}

void CUIManager::ComputeBoundBluePirntScrollUpDown(){
	CBluePrintList* t_pEntity = UIMgr->GetBluePrintList();
	CBody* t_pBody = t_pEntity->GetBody();
	CAttachment* t_pUp = t_pEntity->GetAttachmentFromType(CBluePrintList::UP);
	CAttachment* t_pDown = t_pEntity->GetAttachmentFromType(CBluePrintList::DOWN);
	
	float t_fX = EngineMgr->GetpInformation()->GetAdjustedX();
	float t_fY = EngineMgr->GetpInformation()->GetAdjustedY();

	if(t_pEntity->GetIndex() > 2){
		if(t_pUp->GetLeft() + t_pBody->GetPriPos()->x - 10.0f < t_fX &&
			t_pUp->GetRight() + t_pBody->GetPriPos()->x - 10.0f > t_fX &&
			t_pUp->GetTop() + t_pBody->GetPriPos()->y + 20.0f > t_fY &&
			t_pUp->GetBottom() + t_pBody->GetPriPos()->y + 20.0f < t_fY){
				if(t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.r < 1.0f)
					t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.r += 0.1f;
				if(t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.g < 1.0f)
					t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.g += 0.1f;
				if(t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.b < 1.0f)
					t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.b += 0.1f;

				if(EngineMgr->GetLButtonState() == 1){
					t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.r = -1.0f;
					t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.g = -1.0f;
					t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.b = -1.0f;

					// 출력 인덱스 이동
					t_pEntity->SetIndex(t_pEntity->GetIndex()-1);

					CDListIterator<CBluePrintScroll*> itr;
		
					itr = t_pEntity->GetScrollList()->GetIterator();

					// 한 칸씩 위로 
					for(itr.Start(); itr.Valid(); itr.Forth()){
						itr.Item()->SetDeltaY(itr.Item()->GetDeltaY() - 65.0f);
					}
				}
				return;
		}
	}

	if(t_pEntity->GetIndex() < t_pEntity->GetCount() - 1){
		if(t_pDown->GetLeft() + t_pBody->GetPriPos()->x - 10.0f < t_fX &&
			t_pDown->GetRight() + t_pBody->GetPriPos()->x - 10.0f > t_fX &&
			t_pDown->GetTop() + t_pBody->GetPriPos()->y + 20.0f > t_fY &&
			t_pDown->GetBottom() + t_pBody->GetPriPos()->y + 20.0f < t_fY){
				if(t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.r < 1.0f)
					t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.r += 0.1f;
				if(t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.g < 1.0f)
					t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.g += 0.1f;
				if(t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.b < 1.0f)
					t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.b += 0.1f;

				if(EngineMgr->GetLButtonState() == 1){
					t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.r = -1.0f;
					t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.g = -1.0f;
					t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.b = -1.0f;

					// 출력 인덱스 이동
					t_pEntity->SetIndex(t_pEntity->GetIndex()+1);

					CDListIterator<CBluePrintScroll*> itr;
		
					itr = t_pEntity->GetScrollList()->GetIterator();

					for(itr.Start(); itr.Valid(); itr.Forth()){
						itr.Item()->SetDeltaY(itr.Item()->GetDeltaY() + 65.0f);
					}
				}
				return;
		}
	}

	t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.b = -1.0f;
	t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.r = -1.0f;
	t_pUp->GetMtrlArray()->Get(t_pUp->GetRow(), t_pUp->GetCol()).Diffuse.g = -1.0f;

	t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.b = -1.0f;
	t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.r = -1.0f;
	t_pDown->GetMtrlArray()->Get(t_pDown->GetRow(), t_pDown->GetCol()).Diffuse.g = -1.0f;
}

COrganEntity* CUIManager::GetUI(CBaseObject::Owner p_eOwner){
	// 반복자 생성
	CDListIterator<COrganEntity*> itr;
	
	// _entityList로부터 반복자 초기화
	itr = _UIList.GetIterator();
	
	// _entityList를 훑으며
	for(itr.Start(); itr.Valid(); itr.Forth()){
		// 찾으려는 Owner 타입을 찾아서 COrganEntity*로 리턴
		if(itr.Item()->GetOwner() == p_eOwner){
			return itr.Item();
		}
	}
	return false;
}