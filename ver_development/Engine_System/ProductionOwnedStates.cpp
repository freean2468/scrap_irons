#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Production State
///////////////////////////////////////////////////////////
void CProductionMinimize::Enter(CProduction* pProduction){
	MouseMgr->SetUseCursor(false);
}

void CProductionMinimize::Execute(CProduction* pProduction){
	// 바디 계산

	// 부속물 계산
	
}

void CProductionMinimize::Exit(CProduction* pProduction){

}

bool CProductionMinimize::OnMessage(CProduction* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Activate:
			agent->GetFSM()->ChangeState(ProductionActive->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Active State
///////////////////////////////////////////////////////////
void CProductionActive::Enter(CProduction* pProduction){
	MouseMgr->SetUseCursor(true);
}

void CProductionActive::Execute(CProduction* pProduction){
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	// 각종 계산
	if(UIMgr->ComputeBoundProductionCloseAndMouse()){
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pProduction->ID(), ID_PRODUCTION, Msg_Close, NO_ADDITIONAL_INFO);
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pProduction->ID(), ID_HERO, Msg_Usual, NO_ADDITIONAL_INFO);
	}

	// 바디 계산
	pProduction->GetBody()->GetPriPos()->x = t_vPos.x;
	pProduction->GetBody()->GetPriPos()->y = t_vPos.y;

	// 부속물 계산	
	pProduction->RenderOrgan();

	char line[16];
	CBody* t_pBody = pProduction->GetBody();
	CAttachment* t_pAtt = pProduction->GetAttachmentFromType(CProduction::BUTTON);

	if(pProduction->GetCompleteState() == false){
		if(UIMgr->GetBluePrintList()->GetSelectionList() == true){
			if(UIMgr->GetBluePrintList()->GetCompleteCollection() == true){
				if(UIMgr->GetBluePrintList()->GetOverap()){
					t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.r = -1.0f;
					t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.g =  1.0f;
					t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.b = -1.0f;
					strcpy(line, "제작 완료");
				}
				else{
					t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.r = -1.0f;
					t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.g =  1.0f;
					t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.b = -1.0f;
					strcpy(line, "제작");
				}
			}
			else if(UIMgr->GetBluePrintList()->GetCompleteCollection() == false){
				t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.r =  1.0f;
				t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.g = -1.0f;
				t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.b = -1.0f;
				strcpy(line, "제작 불가");
			}
		}
		else if(UIMgr->GetBluePrintList()->GetSelectionList() == false){
			t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.r = -1.0f;
			t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.g = -1.0f;
			t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.b = -1.0f;
			strcpy(line, "선택 없음");
		}
	}
	else if(pProduction->GetCompleteState() == true){
		t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.r = -1.0f;
		t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.g =  1.0f;
		t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.b = -1.0f;
		strcpy(line, "완료");
	}

	line[15] = '\0';

	EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

	D3DXVECTOR3 _vPos;			// 위치 벡터
	D3DXMATRIXA16 _pos;			// 위치 변환 행렬
	D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
	D3DXVECTOR3 _vRotate;		// 회전 벡터

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&_pos, t_pBody->GetPriPos()->x + t_pAtt->GetPriPos()->x, t_pBody->GetPriPos()->y + t_pAtt->GetPriPos()->y, t_pBody->GetPriPos()->z);

	D3DXMATRIXA16 rX;
	D3DXMatrixIdentity(&rX);
	D3DXMatrixRotationX(&rX, D3DX_PI);
	_rotation = rX;

	mtMatrix *= _rotation * _pos;

	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

	RECT rect;

	rect.right = (long)100.0f;
	rect.left = (long)-100.0f;
	rect.top = (long)-100.0f;
	rect.bottom = (long)100.0f;

	// Text 출력      
	pProduction->GetFont()->DrawText(EngineMgr->GetpSprite(), line, -1, &rect, DT_CENTER | DT_VCENTER , 0xffffffff);      

	EngineMgr->GetpSprite()->End();

	float t_fMX = EngineMgr->GetpInformation()->GetAdjustedX();
	float t_fMY = EngineMgr->GetpInformation()->GetAdjustedY();

	if(113.0f + t_pBody->GetPriPos()->x + t_pAtt->GetPriPos()->x > t_fMX  && -130.0f + t_pBody->GetPriPos()->x + t_pAtt->GetPriPos()->x < t_fMX &&
		57.0f + t_pBody->GetPriPos()->y + t_pAtt->GetPriPos()->y > t_fMY && -11.0f + t_pBody->GetPriPos()->y + t_pAtt->GetPriPos()->y < t_fMY &&
		EngineMgr->GetLButtonState() == 1 && UIMgr->GetBluePrintList()->GetCompleteCollection() && !pProduction->GetCompleteState() && UIMgr->GetBluePrintList()->GetSelectionList() && !UIMgr->GetBluePrintList()->GetOverap()){
		// 제작
		MusicMgr->PlayMP3FileForEffect("./Sound/Producing.mp3");

		t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.r = 1.0f;
		t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.g = 1.0f;
		t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.b = 1.0f;
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pProduction->ID(), ID_PRODUCING, Msg_Activate, NO_ADDITIONAL_INFO);

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pProduction->ID(), ID_INVENTORY, Msg_Close, NO_ADDITIONAL_INFO);
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pProduction->ID(), ID_BLUEPRINTLIST, Msg_Close, NO_ADDITIONAL_INFO);

		// 반복자 생성
		CDListIterator<CItem*> itrType;
		CDListIterator<int> itrCount;
		CArray<CItem*>* InvenArray = UIMgr->GetInventory()->GetThingsList();		// 소지품
		CArray<int>* InvenCount = UIMgr->GetInventory()->GetThingsCount();

		CDListIterator<CBluePrintScroll*> itr = UIMgr->GetBluePrintList()->GetScrollList()->GetIterator();

		UIMgr->GetBluePrintList()->SetSelectionList(false);
		for(itr.Start(); itr.Valid(); itr.Forth()){
			itr.Item()->GetFSM()->ChangeState(BluePrintScrollMinimize->Instance());
			if(itr.Item()->GetIndex() == UIMgr->GetBluePrintList()->GetSelectIndex()){
				AIMgr->InsertOurForce(itr.Item()->GetOurForceType()); // OurForce 추가
				// 반복자 초기화
				itrType = itr.Item()->GetIngredients()->GetIterator();
				itrCount = itr.Item()->GetIngredientsCount()->GetIterator();
			}
		}

		// 인벤 아이템 정리
		for(itrType.Start(), itrCount.Start(); itrCount.Valid(); itrType.Forth(), itrCount.Forth()){
			for(int i = 0; i < INVENLIMIT; i++){
				if(InvenArray->Get(i)){
					if(InvenArray->Get(i)->GetItemType() == itrType.Item()->GetItemType()){
						InvenCount->Get(i) += -itrCount.Item();
						break;
					}
				}
			}
		}

		// Count가 0이 된 아이템이 있다면 인벤토리에서 삭제
		UIMgr->GetInventory()->DeleteItem();

		pProduction->SetCompleteState(true);
	}
	else if(113.0f + t_pBody->GetPriPos()->x + t_pAtt->GetPriPos()->x > t_fMX  && -130.0f + t_pBody->GetPriPos()->x + t_pAtt->GetPriPos()->x < t_fMX &&
		57.0f + t_pBody->GetPriPos()->y + t_pAtt->GetPriPos()->y > t_fMY && -11.0f + t_pBody->GetPriPos()->y + t_pAtt->GetPriPos()->y < t_fMY &&
		EngineMgr->GetLButtonState() == 1 && pProduction->GetCompleteState()){
		// 완료
		t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.r = 1.0f;
		t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.g = 1.0f;
		t_pAtt->GetMtrlArray()->Get(0, 0).Diffuse.b = 1.0f;
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pProduction->ID(), ID_PRODUCING, Msg_Close, NO_ADDITIONAL_INFO);

		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pProduction->ID(), ID_INVENTORY, Msg_Activate, NO_ADDITIONAL_INFO);
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pProduction->ID(), ID_BLUEPRINTLIST, Msg_InProduction, NO_ADDITIONAL_INFO);
		
		// 제작된 아군 활성화
		CDListIterator<CCharacterEntity*> itrEntity = AIMgr->GetOurForceList()->GetIterator();

		for(itrEntity.Start(); itrEntity.Valid(); itrEntity.Forth()){			
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pProduction->ID(), itrEntity.Item()->ID(), Msg_NotRender, NO_ADDITIONAL_INFO);
		}

		CDListIterator<CBluePrintScroll*> itr = UIMgr->GetBluePrintList()->GetScrollList()->GetIterator();

		UIMgr->GetBluePrintList()->SetSelectionList(false);
		for(itr.Start(); itr.Valid(); itr.Forth()){
			if(itr.Item()->GetIndex() == UIMgr->GetBluePrintList()->GetSelectIndex()){
				itr.Item()->GetFSM()->ChangeState(BluePrintScrollMinimize->Instance());
				break;
			}
		}
		pProduction->SetCompleteState(false);
	}

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

	pProduction->InitChainVector();
}

void CProductionActive::Exit(CProduction* pProduction){

}

bool CProductionActive::OnMessage(CProduction* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Close:
			agent->GetFSM()->ChangeState(ProductionMinimize->Instance());
			return true;
		default:
			return false;
	}
}