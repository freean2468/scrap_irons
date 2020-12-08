#include "../BaseHeader.h"

CObjectManager::CObjectManager() : _itemLimit(8){
	_entityList.Append(new CLogo(ID_LOGO));
	EntityDB->RegisterEntity(GetEntity(CBaseObject::LOGO));

	_entityList.Append(new CWorldMap(ID_WORLDMAP));
	EntityDB->RegisterEntity(GetEntity(CBaseObject::WORLDMAP));

	_entityList.Append(new CIntro(ID_INTRO));
	EntityDB->RegisterEntity(GetEntity(CBaseObject::INTRO));

	_entityList.Append(new CMainMenu(ID_MAINMENU));
	EntityDB->RegisterEntity(GetEntity(CBaseObject::MAINMENU));

	_entityList.Append(new CStageHome(ID_STAGEHOME));
	EntityDB->RegisterEntity(GetEntity(CBaseObject::STAGEHOME));

	_entityList.Append(new CStageMountain(ID_STAGEMOUNTAIN));
	EntityDB->RegisterEntity(GetEntity(CBaseObject::STAGEMOUNTAIN));

	_entityList.Append(new CStageFurnace(ID_STAGEFURNACE));
	EntityDB->RegisterEntity(GetEntity(CBaseObject::STAGEFURNACE));

	_entityList.Append(new CStageChimney(ID_STAGECHIMNEY));
	EntityDB->RegisterEntity(GetEntity(CBaseObject::STAGECHIMNEY));

	_entityList.Append(new CStageDustBridge(ID_STAGEDUSTBRIDGE));
	EntityDB->RegisterEntity(GetEntity(CBaseObject::STAGEDUSTBRIDGE));

	_entityList.Append(new CStageGoodHope(ID_STAGEGOODHOPE));
	EntityDB->RegisterEntity(GetEntity(CBaseObject::STAGEGOODHOPE));

	for(int i = 0; i < 6; i++){
		UIMgr->PutItemInInventory(new CItem(ID_ITEM));
	}

	_itemCount = 0;
}

CObjectManager::~CObjectManager(){
	/*d3d::Delete<COrganEntity*>(_hero);
	d3d::Delete<COrganEntity*>(_flower);
	d3d::Delete<COrganEntity*>(_cart);
	d3d::Delete<COrganEntity*>(_logo);
	d3d::Delete<COrganEntity*>(_mainmenu);*/

	// �ݺ��� ����
	CDListIterator<COrganEntity*> itr;
	
	// _entityList�κ��� �ݺ��� �ʱ�ȭ
	itr = _entityList.GetIterator();
	
	// _entityList�� ������
	for(itr.Start(); itr.Valid();){
		_entityList.Remove(itr);
	}

	CDListIterator<CItem*> t_itemItr;
	t_itemItr = _itemList.GetIterator();

	// _itemList�� ������
	for(t_itemItr.Start(); t_itemItr.Valid();){
		_itemList.Remove(t_itemItr);
	}
}

void CObjectManager::SetStartInfo(COrganEntity* p_entity, float p_fX, CBaseObject::DIRECTION p_eDirection){
	p_entity->GetBody()->GetPriPos()->x = p_fX;
	p_entity->GetBody()->GetPriPos()->y = (float)(StageMgr->GetStageHeight() + p_entity->GetBody()->GetHeightHalf());
	
	p_entity->SetRow(p_eDirection);
}

void CObjectManager::CreatItem(){
	static int t_nCount = 0;
	if(t_nCount > 60){
		if(_itemCount <= _itemLimit){
			// �ݺ��� ����
			CDListIterator<CItem*> itr;
			
			itr = _itemList.GetIterator();

			_itemList.InsertBefore(itr, new CItem(ID_ITEM));
			_itemCount++;
		}
	}

	t_nCount++;
}

void CObjectManager::CreatBluePrint(){
	
}

void CObjectManager::UpdateItem(){
	InventoryUpdateAndDeleteItem();

	// �ݺ��� ����
	CDListIterator<CItem*> itr;
	
	itr = _itemList.GetIterator();

	for(itr.Start(); itr.Valid(); itr.Forth()){
		itr.Item()->Update();
	}
}

void CObjectManager::InventoryUpdateAndDeleteItem(){
	// �ݺ��� ����
	CDListIterator<CItem*> itr;
	
	itr = _itemList.GetIterator();

	for(itr.Start(); itr.Valid();){
		if(itr.Item()->GetBody()->GetMtrlArray()->Get(0, 0).Diffuse.a <= 0.0f){
			_itemList.Remove(itr);
		}
		else{
			itr.Forth();
		}
	}
}

// �簢 �浹
bool CObjectManager::ComputeBoundEntity(COrganEntity* p_pE1, COrganEntity* p_pE2){
	if(p_pE1->GetBody()->GetLeft() < p_pE2->GetBody()->GetRight() &&
		p_pE1->GetBody()->GetRight() > p_pE2->GetBody()->GetLeft() &&
		p_pE1->GetBody()->GetTop() > p_pE2->GetBody()->GetBottom() &&
		p_pE1->GetBody()->GetBottom() < p_pE2->GetBody()->GetTop()){
			return true;
	}
	else if(p_pE1->GetBody()->GetLeft() > p_pE2->GetBody()->GetRight() &&
		p_pE1->GetBody()->GetRight() < p_pE2->GetBody()->GetLeft() &&
		p_pE1->GetBody()->GetTop() < p_pE2->GetBody()->GetBottom() &&
		p_pE1->GetBody()->GetBottom() > p_pE2->GetBody()->GetTop()){
			return true;
	}
	
	return false;
}

void CObjectManager::ComputeBountItemAndHero(CItem* t_pItem){
	CBody* t_pHeroBody = AIMgr->GetHero()->GetBody();
	CBody* t_pBody = t_pItem->GetBody();

	if(t_pHeroBody->GetLeft() < t_pBody->GetRight() && t_pHeroBody->GetRight() > t_pBody->GetLeft()){
		UIMgr->ActivateInteract(t_pBody->GetPriPos()->x, t_pBody->GetPriPos()->y + 50.0f);

		if(::GetAsyncKeyState('E') == 0xffff8001){
			CInventory* t_pInventory = UIMgr->GetInventory();

			for(int i = 0; i < INVENLIMIT; i++){
				if(t_pInventory->GetThingsList()->Get(i) == NULL){
					t_pItem->GetFSM()->ChangeState(ItemGet->Instance());
					UIMgr->PutItemInInventory(t_pItem);
					return;
				}
			}	
		}
	}
}

// ���콺�� StagePoint���� �浹üũ �Լ�
float CObjectManager::ComputeBoundStagePointAndMouse(CSection* pSection){
	float fRadius;
	float fX1, fY1, fX2, fY2;
	float fDistance = 0.0f;
	int nStageCount = 0;

	// �ݺ��� ����
	CDListIterator<COrganEntity*> itr;
	
	// _entityList�κ��� �ݺ��� �ʱ�ȭ
	itr = _entityList.GetIterator();

	// _entityList�� ������
	for(itr.Start(); itr.Valid(); itr.Forth()){
		// EntityType�� WorldMap���
		if(itr.Item()->GetOwner() == CBaseObject::WORLDMAP){
			for(int i = 0; i < itr.Item()->GetAttachmentArray()->GetSize(); i++){
				if(nStageCount == 6) break;

				if(itr.Item()->GetAttachment(i)->GetAttType() == CWorldMap::STAGEPOINT){
					int j = 0;

					fRadius = itr.Item()->GetAttachment(i)->GetWidthHalf();

					fX1 = itr.Item()->GetAttachment(i)->GetPriPos()->x;
					fY1 = itr.Item()->GetAttachment(i)->GetPriPos()->y;

					fX2 = EngineMgr->GetpInformation()->GetAdjustedX();
					fY2 = EngineMgr->GetpInformation()->GetAdjustedY();

					fDistance = sqrt( ((fX2-fX1)*(fX2-fX1)) + ((fY2-fY1)*(fY2-fY1)) );

					if(fDistance <= fRadius){	
						// clear ���� Ȯ��
						switch(i){
							case 1:
								if(!StageMgr->_homeClear)
									continue;
								break;
							case 2:
								if(!StageMgr->_scrapMountainClear)
									continue;
								break;
							case 3:
								if(!StageMgr->_furnaceClear)
									continue;
								break;
							case 4:
								if(!StageMgr->_chimneyClear)
									continue;
								break;
							case 5:
								if(!StageMgr->_dustBridgeClear)
									continue;
								break;
							default:
								break;
						}

						j = itr.Item()->GetAttachmentIndex(CWorldMap::LIGHT);

						if(itr.Item()->GetAttachment(nStageCount+j)->GetMtrlArray()->Get(0,0).Diffuse.a < 0.8f){
							itr.Item()->GetAttachment(nStageCount+j)->GetMtrlArray()->Get(0,0).Diffuse.a += 0.008f;
							if(itr.Item()->GetAttachment(nStageCount+j)->GetMtrlArray()->Get(0,0).Diffuse.a >= 0.8f)
								itr.Item()->GetAttachment(nStageCount+j)->GetMtrlArray()->Get(0,0).Diffuse.a = 0.8f;
						}

						j = itr.Item()->GetAttachmentIndex(CWorldMap::TEXT);

						if(itr.Item()->GetAttachment(nStageCount+j)->GetPriSca()->x < 1.0f &&itr.Item()->GetAttachment(nStageCount+j)->GetPriSca()->y < 1.0f){
							itr.Item()->GetAttachment(nStageCount+j)->GetPriSca()->x+=0.02f;
							itr.Item()->GetAttachment(nStageCount+j)->GetPriSca()->y+=0.02f;
						}			

						if(EngineMgr->GetLButtonState() == 1){
							EffectMgr->SetPlaneType(CEffectManager::BLACK);
							EffectMgr->SetPlaneUse(true);
							StageMgr->SetbIsFadeInOut(true);
							StageMgr->SetStage(nStageCount);
						}

						break;
					}//if
					nStageCount++;
				}//if
			}//for
			break;
		}//if
	} // for
	return 1.0f;
}

// �� �ȿ� ���ΰ��� ���Դ��� ���
void CObjectManager::ComputeBoundStageHomeAndHero(){
	float t_fDoorPos = GetEntity(CBaseObject::STAGEHOME)->GetBody()->GetPriPosRight()->x - 136.0f;

	static int nCount = 0;

	if(AIMgr->GetHero()->GetBody()->GetPriPosRight()->x <= t_fDoorPos){
		if(nCount > 0){
			StageMgr->SetbIsHomeInOut(true);
		
			// �Ʊ� �׸��� ����
			CDListIterator<CCharacterEntity*> itrEntity = AIMgr->GetOurForceList()->GetIterator();

			for(itrEntity.Start(); itrEntity.Valid(); itrEntity.Forth()){			
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_HERO, itrEntity.Item()->ID(), Msg_NotRender, NO_ADDITIONAL_INFO);
			}
			nCount = 0;
		}
	}
	else{
		if(nCount < 1){
			nCount = 1;

			StageMgr->SetbIsHomeInOut(false);
			
			// �Ʊ� Ȱ��ȭ
			CDListIterator<CCharacterEntity*> itrEntity = AIMgr->GetOurForceList()->GetIterator();

			for(itrEntity.Start(); itrEntity.Valid(); itrEntity.Forth()){			
				Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, ID_HERO, itrEntity.Item()->ID(), Msg_Usual, NO_ADDITIONAL_INFO);
			}
		}
	}
}

// ĳ���Ͱ� ���������� �������� ���
void CObjectManager::ComputeGetOutStage(CBaseObject::OWNER p_eBG, CBody* p_pBody){
	switch(p_eBG){
		case CBaseObject::STAGECHIMNEY:
			if((GetEntity(p_eBG)->GetBody()->GetPriPos()->x - GetEntity(p_eBG)->GetBody()->GetWidthHalf()) > p_pBody->GetPriPos()->x){
				StageMgr->SetbIsGetOutStage(true);
				EffectMgr->SetPlaneUse(true);
				EffectMgr->SetPlaneType(CEffectManager::BLACK);
				StageMgr->SetbIsFadeInOut(true);
			}
			else if((GetEntity(p_eBG)->GetBody()->GetPriPos()->x + GetEntity(p_eBG)->GetBody()->GetWidthHalf()) - 1019.0f < p_pBody->GetPriPos()->x){
				StageMgr->SetbIsGetOutStage(true);
				EffectMgr->SetPlaneUse(true);
				EffectMgr->SetPlaneType(CEffectManager::BLACK);
				StageMgr->SetbIsFadeInOut(true);
			}
			break;
		case CBaseObject::STAGEFURNACE:
			if((GetEntity(p_eBG)->GetBody()->GetPriPos()->x - GetEntity(p_eBG)->GetBody()->GetWidthHalf()) > p_pBody->GetPriPos()->x){
				StageMgr->SetbIsGetOutStage(true);
				EffectMgr->SetPlaneUse(true);
				EffectMgr->SetPlaneType(CEffectManager::BLACK);
				StageMgr->SetbIsFadeInOut(true);
			}
			else if((GetEntity(p_eBG)->GetBody()->GetPriPos()->x + GetEntity(p_eBG)->GetBody()->GetWidthHalf()) - 535.0f < p_pBody->GetPriPos()->x){
				StageMgr->SetbIsGetOutStage(true);
				EffectMgr->SetPlaneUse(true);
				EffectMgr->SetPlaneType(CEffectManager::BLACK);
				StageMgr->SetbIsFadeInOut(true);
			}
			break;
		default:
			if((GetEntity(p_eBG)->GetBody()->GetPriPos()->x + GetEntity(p_eBG)->GetBody()->GetWidthHalf()) < abs(p_pBody->GetPriPos()->x)){
				StageMgr->SetbIsGetOutStage(true);
				EffectMgr->SetPlaneUse(true);
				EffectMgr->SetPlaneType(CEffectManager::BLACK);
				StageMgr->SetbIsFadeInOut(true);
			}
			break;
	}
}

// �޴� ���� ���
int CObjectManager::ComputeBoundMenu(){
	// ����Ʈ����Ʈ�� ���� �ȿ� �޴� ������Ʈ�� ���ƴٸ� �� �޴����� Ÿ���� ��ȯ�Ѵ�.
	// �� Ÿ�Կ� ���� ���ѻ��±�迡�� ���¸� �ٲ��ش�.

	// �޴��� ���ۺ��� �������� �浹 ���� ���� Ȯ��
	// �޴��� ������ ���� �¿� �簢 �浹 ���θ� Ȯ���Ѵ�.

	// �ݺ��� ����
	CDListIterator<COrganEntity*> itr;
	
	// _entityList�κ��� �ݺ��� �ʱ�ȭ
	itr = _entityList.GetIterator();
	
	// _entityList�� ������
	for(itr.Start(); itr.Valid(); itr.Forth()){
		// EntityType�� MainMenu���
		if(itr.Item()->GetOwner() == CBaseObject::MAINMENU){
			// MainMenu�� �޴��ǵ��� ���� �˻�
			for(int i = CMainMenu::START; i <= CMainMenu::EXIT; i++){
				if(itr.Item()->GetAttachmentFromType(CMainMenu::LIGHT)->GetLeft() + 200.0f < itr.Item()->GetAttachment(i)->GetLeft() &&
					itr.Item()->GetAttachmentFromType(CMainMenu::LIGHT)->GetRight() - 200.0f > itr.Item()->GetAttachment(i)->GetRight()){
						return itr.Item()->GetAttachment(i)->GetAttType();
				}
			}
		}
	}
	
	return -1;
}

COrganEntity* CObjectManager::GetEntity(CBaseObject::Owner p_eOwner){
	// �ݺ��� ����
	CDListIterator<COrganEntity*> itr;
	
	// _entityList�κ��� �ݺ��� �ʱ�ȭ
	itr = _entityList.GetIterator();
	
	// _entityList�� ������
	for(itr.Start(); itr.Valid(); itr.Forth()){
		// ã������ Owner Ÿ���� ã�Ƽ� COrganEntity*�� ����
		if(itr.Item()->GetOwner() == p_eOwner){
			return itr.Item();
		}
	}
	return false;
}