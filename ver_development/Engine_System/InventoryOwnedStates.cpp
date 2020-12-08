#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Show State
///////////////////////////////////////////////////////////
void CInventoryShow::Enter(CInventory* pInventory){
	
}

void CInventoryShow::Execute(CInventory* pInventory){
	if(StageMgr->GetbIsHomeInOut()){
		pInventory->GetFSM()->ChangeState(InventoryMinimize->Instance());
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pInventory->ID(), ID_BLUEPRINTLIST, Msg_Close, NO_ADDITIONAL_INFO);
		
		CDListIterator<CBluePrintScroll*> itr = UIMgr->GetBluePrintList()->GetScrollList()->GetIterator();

		UIMgr->GetBluePrintList()->SetSelectionList(false);
		for(itr.Start(); itr.Valid(); itr.Forth()){
			itr.Item()->GetFSM()->ChangeState(BluePrintScrollMinimize->Instance());
		}
		return;
	}

	if(::GetAsyncKeyState('Q') == 0xffff8001){
		pInventory->GetFSM()->ChangeState(InventoryMinimize->Instance());
		Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pInventory->ID(), ID_BLUEPRINTLIST, Msg_Close, NO_ADDITIONAL_INFO);
		
		CDListIterator<CBluePrintScroll*> itr = UIMgr->GetBluePrintList()->GetScrollList()->GetIterator();

		UIMgr->GetBluePrintList()->SetSelectionList(false);
		for(itr.Start(); itr.Valid(); itr.Forth()){
			itr.Item()->GetFSM()->ChangeState(BluePrintScrollMinimize->Instance());
		}
		MouseMgr->SetUseCursor(false);
	}

	// 바디 계산
	CBody* t_pBody = pInventory->GetBody();
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_vPos.x - 180.0f;
	t_pBody->GetPriPos()->y = t_vPos.y - 160.0f;
	t_pBody->GetPriPos()->z = 700.0f + t_vPos.z;
	
	// 부속물 계산
	for(int i = 0; i < pInventory->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pInventory->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CInventory::UNDER:
				switch(t_Att->GetMoveState()){
					case true:
						// Max라면
						t_Att->GetPriPos()->y += 0.2f;
						if(t_Att->GetPriPos()->y >= -75.0f)	t_Att->SetMoveState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriPos()->y -= 0.2f;
						if(t_Att->GetPriPos()->y <= -85.0f) t_Att->SetMoveState(true);
						break;
				}
				break;
			default:
				break;
		}
	}	

	// 인벤토리 창 렌더
	pInventory->RenderOrgan();

	int t_nItemIndex;

	// 인벤 아이템 충돌체크
	for(int i = 0; i < INVENLIMIT; i++){
		if(pInventory->GetThingsList()->Get(i)){
			CItem* t_pItem = pInventory->GetThingsList()->Get(i);
			int t_nCount = pInventory->GetThingsCount()->Get(i);

			float t_fMX = EngineMgr->GetpInformation()->GetAdjustedX();
			float t_fMY = EngineMgr->GetpInformation()->GetAdjustedY();

			if(t_pBody->GetPriPos()->x + t_pItem->GetBody()->GetRight() - 4.0f > t_fMX  && t_pBody->GetPriPos()->x + t_pItem->GetBody()->GetLeft() - 4.0f < t_fMX &&
				t_pBody->GetPriPos()->y + t_pItem->GetBody()->GetTop() + 25.0f > t_fMY && t_pBody->GetPriPos()->y + t_pItem->GetBody()->GetBottom() + 25.0f < t_fMY){
					t_nItemIndex = i;
					pInventory->GetMessage()->SetUse(true);					
					break;
				}
			else{
				pInventory->GetMessage()->SetUse(false);
			}
		}
	}

	// 아이템 설명
	if(pInventory->GetMessage()->GetUse()){
		// 부속물 계산
		for(int i = 0; i < pInventory->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pInventory->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CInventory::UNDER:
					switch(t_Att->GetMoveState()){
						case true:
							// Max라면
							t_Att->GetPriPos()->y += 1.2f;
							if(t_Att->GetPriPos()->y >= -75.0f)	t_Att->SetMoveState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriPos()->y -= 1.2f;
							if(t_Att->GetPriPos()->y <= -85.0f) t_Att->SetMoveState(true);
							break;
					}
					break;
				default:
					break;
			}
		}	

		CItem* t_pItem = pInventory->GetThingsList()->Get(t_nItemIndex);

		EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

		D3DXVECTOR3 _vPos;			// 위치 벡터
		D3DXMATRIXA16 _pos;			// 위치 변환 행렬
		D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
		D3DXVECTOR3 _vRotate;		// 회전 벡터

		D3DXMATRIXA16 mtMatrix;
		D3DXMatrixIdentity(&mtMatrix);

		D3DXMatrixTranslation(&_pos, t_pBody->GetPriPos()->x + pInventory->GetMessage()->GetPriPos()->x , t_pBody->GetPriPos()->y + pInventory->GetMessage()->GetPriPos()->y, t_pBody->GetPriPos()->z + pInventory->GetMessage()->GetPriPos()->z);

		D3DXMATRIXA16 rX;
		D3DXMatrixIdentity(&rX);
		D3DXMatrixRotationX(&rX, D3DX_PI);
		_rotation = rX;

		mtMatrix *= _rotation * _pos;

		EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

		RECT rect;

		rect.right = (long)(pInventory->GetMessage()->GetWidthHalf()-23.0f);
		rect.left = (long)(-pInventory->GetMessage()->GetWidthHalf()+25.0f);
		rect.top = (long)(-pInventory->GetMessage()->GetHeightHalf()+20.0f);
		rect.bottom = (long)(pInventory->GetMessage()->GetHeightHalf()-20.0f);

		// Name 출력      
		pInventory->GetFontForName()->DrawText(EngineMgr->GetpSprite(), t_pItem->GetName(), -1, &rect, DT_CENTER | DT_WORDBREAK, 0xff000000);      

		rect.right = (long)(pInventory->GetMessage()->GetWidthHalf()-23.0f);
		rect.left = (long)(-pInventory->GetMessage()->GetWidthHalf()+25.0f);
		rect.top = (long)(-pInventory->GetMessage()->GetHeightHalf()+20.0f);
		rect.bottom = (long)(pInventory->GetMessage()->GetHeightHalf()-20.0f);

		// State 출력      
		pInventory->GetFontForState()->DrawText(EngineMgr->GetpSprite(), t_pItem->GetState(), -1, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK, 0xff000000);      

		EngineMgr->GetpSprite()->End();

		// 월드 좌표를 원점으로 되돌린다.
		D3DXMatrixIdentity(&mtMatrix);
		EngineMgr->GetpSprite()->SetTransform(&mtMatrix);
	}

	// 인벤토리 목록 렌더
	for(int i = 0; i < INVENLIMIT; i++){
		pInventory->BodySetting();
		if(pInventory->GetThingsList()->Get(i)){
			CItem* t_pItem = pInventory->GetThingsList()->Get(i);
			int t_nCount = pInventory->GetThingsCount()->Get(i);
			char line[8];

			line[7] = '\0';
			
			t_pItem->GetChainPos()->x = t_pBody->GetPriPos()->x; t_pItem->GetChainPos()->y = t_pBody->GetPriPos()->y; t_pItem->GetChainPos()->z = t_pBody->GetPriPos()->z; 

			t_pItem->BodySetting();
			t_pItem->GetBody()->Render(t_pItem->GetChainPos(), t_pItem->GetBody()->GetPriSca(), t_pItem->GetChainRot(), t_pItem->GetChainCen());

			if(t_nCount > 0){
				itoa(t_nCount, line, 10);

				EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

				D3DXVECTOR3 _vPos;			// 위치 벡터
				D3DXMATRIXA16 _pos;			// 위치 변환 행렬
				D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
				D3DXVECTOR3 _vRotate;		// 회전 벡터

				D3DXMATRIXA16 mtMatrix;
				D3DXMatrixIdentity(&mtMatrix);

				D3DXMatrixTranslation(&_pos, t_pItem->GetChainPos()->x - 4.0f, t_pItem->GetChainPos()->y + 5.0f, t_pItem->GetChainPos()->z);

				D3DXMATRIXA16 rX;
				D3DXMatrixIdentity(&rX);
				D3DXMatrixRotationX(&rX, D3DX_PI);
				_rotation = rX;

				mtMatrix *= _rotation * _pos;

				EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

				RECT rect;

				rect.right = (long)22.5f;
				rect.left = (long)-22.5f;
				rect.top = (long)-22.5f;
				rect.bottom = (long)22.5f;

				// Text 출력      
				pInventory->GetFont()->DrawText(EngineMgr->GetpSprite(), line, -1, &rect, DT_RIGHT | DT_BOTTOM , 0xffffffff);      

				EngineMgr->GetpSprite()->End();

				// 월드 좌표를 원점으로 되돌린다.
				D3DXMatrixIdentity(&mtMatrix);
				EngineMgr->GetpSprite()->SetTransform(&mtMatrix);
			}
		}
		pInventory->InitChainVector();
	}
}

void CInventoryShow::Exit(CInventory* pInventory){

}

bool CInventoryShow::OnMessage(CInventory* agent, const Telegram& msg){
	return false;
}

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
void CInventoryMinimize::Enter(CInventory* pInventory){
	
}

void CInventoryMinimize::Execute(CInventory* pInventory){
	if(!EventMgr->GetEventing()){
		if(!StageMgr->GetbIsHomeInOut() && ::GetAsyncKeyState('Q') == 0xffff8001){
			pInventory->GetFSM()->ChangeState(InventoryShow->Instance());
			Dispatch->DispatchMessage(SEND_MSG_IMMEDIATELY, pInventory->ID(), ID_BLUEPRINTLIST, Msg_Activate, NO_ADDITIONAL_INFO);
			MouseMgr->SetUseCursor(true);
		}	
	}
}

void CInventoryMinimize::Exit(CInventory* pInventory){

}

bool CInventoryMinimize::OnMessage(CInventory* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Activate:
			agent->GetFSM()->ChangeState(InventoryInProduction->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// InProduction State
///////////////////////////////////////////////////////////
void CInventoryInProduction::Enter(CInventory* pInventory){
	
}

void CInventoryInProduction::Execute(CInventory* pInventory){
	// 바디 계산
	CBody* t_pBody = pInventory->GetBody();
	CBody* t_pProductionBody = UIMgr->GetUI(CBaseObject::PRODUCTION)->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_pProductionBody->GetPriPos()->x - 180.0f;
	t_pBody->GetPriPos()->y = t_pProductionBody->GetPriPos()->y - 170.0f;
	t_pBody->GetPriPos()->z = 700.0f + t_vPos.z;
	
	// 부속물 계산
	for(int i = 0; i < pInventory->GetAttachmentArray()->GetSize(); i++){
		CAttachment* t_Att = pInventory->GetAttachmentArray()->Get(i);
		switch(t_Att->GetAttType()){
			case CInventory::UNDER:
				switch(t_Att->GetMoveState()){
					case true:
						// Max라면
						t_Att->GetPriPos()->y += 0.2f;
						if(t_Att->GetPriPos()->y >= -75.0f)	t_Att->SetMoveState(false);
						break;
					case false:
						// Min라면
						t_Att->GetPriPos()->y -= 0.2f;
						if(t_Att->GetPriPos()->y <= -85.0f) t_Att->SetMoveState(true);
						break;
				}
				break;
			default:
				break;
		}
	}	

	// 인벤토리 창 렌더
	pInventory->RenderOrgan();

	int t_nItemIndex;

	// 인벤 아이템 충돌체크
	for(int i = 0; i < INVENLIMIT; i++){
		if(pInventory->GetThingsList()->Get(i)){
			CItem* t_pItem = pInventory->GetThingsList()->Get(i);
			int t_nCount = pInventory->GetThingsCount()->Get(i);

			float t_fMX = EngineMgr->GetpInformation()->GetAdjustedX();
			float t_fMY = EngineMgr->GetpInformation()->GetAdjustedY();

			if(t_pBody->GetPriPos()->x + t_pItem->GetBody()->GetRight() - 4.0f > t_fMX  && t_pBody->GetPriPos()->x + t_pItem->GetBody()->GetLeft() - 4.0f < t_fMX &&
				t_pBody->GetPriPos()->y + t_pItem->GetBody()->GetTop() + 25.0f > t_fMY && t_pBody->GetPriPos()->y + t_pItem->GetBody()->GetBottom() + 25.0f < t_fMY){
					t_nItemIndex = i;
					pInventory->GetMessage()->SetUse(true);					
					break;
				}
			else{
				pInventory->GetMessage()->SetUse(false);
			}
		}
	}

	// 아이템 설명
	if(pInventory->GetMessage()->GetUse()){
		// 부속물 계산
		for(int i = 0; i < pInventory->GetAttachmentArray()->GetSize(); i++){
			CAttachment* t_Att = pInventory->GetAttachmentArray()->Get(i);
			switch(t_Att->GetAttType()){
				case CInventory::UNDER:
					switch(t_Att->GetMoveState()){
						case true:
							// Max라면
							t_Att->GetPriPos()->y += 1.2f;
							if(t_Att->GetPriPos()->y >= -75.0f)	t_Att->SetMoveState(false);
							break;
						case false:
							// Min라면
							t_Att->GetPriPos()->y -= 1.2f;
							if(t_Att->GetPriPos()->y <= -85.0f) t_Att->SetMoveState(true);
							break;
					}
					break;
				default:
					break;
			}
		}	

		CItem* t_pItem = pInventory->GetThingsList()->Get(t_nItemIndex);

		EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

		D3DXVECTOR3 _vPos;			// 위치 벡터
		D3DXMATRIXA16 _pos;			// 위치 변환 행렬
		D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
		D3DXVECTOR3 _vRotate;		// 회전 벡터

		D3DXMATRIXA16 mtMatrix;
		D3DXMatrixIdentity(&mtMatrix);

		D3DXMatrixTranslation(&_pos, t_pBody->GetPriPos()->x + pInventory->GetMessage()->GetPriPos()->x , t_pBody->GetPriPos()->y + pInventory->GetMessage()->GetPriPos()->y, t_pBody->GetPriPos()->z + pInventory->GetMessage()->GetPriPos()->z);

		D3DXMATRIXA16 rX;
		D3DXMatrixIdentity(&rX);
		D3DXMatrixRotationX(&rX, D3DX_PI);
		_rotation = rX;

		mtMatrix *= _rotation * _pos;

		EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

		RECT rect;

		rect.right = (long)(pInventory->GetMessage()->GetWidthHalf()-23.0f);
		rect.left = (long)(-pInventory->GetMessage()->GetWidthHalf()+25.0f);
		rect.top = (long)(-pInventory->GetMessage()->GetHeightHalf()+20.0f);
		rect.bottom = (long)(pInventory->GetMessage()->GetHeightHalf()-20.0f);

		// Name 출력      
		pInventory->GetFontForName()->DrawText(EngineMgr->GetpSprite(), t_pItem->GetName(), -1, &rect, DT_CENTER | DT_WORDBREAK, 0xff000000);      

		rect.right = (long)(pInventory->GetMessage()->GetWidthHalf()-23.0f);
		rect.left = (long)(-pInventory->GetMessage()->GetWidthHalf()+25.0f);
		rect.top = (long)(-pInventory->GetMessage()->GetHeightHalf()+40.0f);
		rect.bottom = (long)(pInventory->GetMessage()->GetHeightHalf()-20.0f);

		// State 출력      
		pInventory->GetFontForState()->DrawText(EngineMgr->GetpSprite(), t_pItem->GetState(), -1, &rect, DT_CENTER | DT_WORDBREAK, 0xff000000);      

		EngineMgr->GetpSprite()->End();

		// 월드 좌표를 원점으로 되돌린다.
		D3DXMatrixIdentity(&mtMatrix);
		EngineMgr->GetpSprite()->SetTransform(&mtMatrix);
	}

	// 인벤토리 목록 렌더
	for(int i = 0; i < INVENLIMIT; i++){
		pInventory->BodySetting();
		if(pInventory->GetThingsList()->Get(i)){
			CItem* t_pItem = pInventory->GetThingsList()->Get(i);
			int t_nCount = pInventory->GetThingsCount()->Get(i);
			char line[8];

			line[7] = '\0';
			
			t_pItem->GetChainPos()->x = t_pBody->GetPriPos()->x; t_pItem->GetChainPos()->y = t_pBody->GetPriPos()->y; t_pItem->GetChainPos()->z = t_pBody->GetPriPos()->z; 

			t_pItem->BodySetting();
			t_pItem->GetBody()->Render(t_pItem->GetChainPos(), t_pItem->GetBody()->GetPriSca(), t_pItem->GetChainRot(), t_pItem->GetChainCen());

			if(t_nCount > 0){
				itoa(t_nCount, line, 10);

				EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

				D3DXVECTOR3 _vPos;			// 위치 벡터
				D3DXMATRIXA16 _pos;			// 위치 변환 행렬
				D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
				D3DXVECTOR3 _vRotate;		// 회전 벡터

				D3DXMATRIXA16 mtMatrix;
				D3DXMatrixIdentity(&mtMatrix);

				D3DXMatrixTranslation(&_pos, t_pItem->GetChainPos()->x - 4.0f, t_pItem->GetChainPos()->y + 5.0f, t_pItem->GetChainPos()->z);

				D3DXMATRIXA16 rX;
				D3DXMatrixIdentity(&rX);
				D3DXMatrixRotationX(&rX, D3DX_PI);
				_rotation = rX;

				mtMatrix *= _rotation * _pos;

				EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

				RECT rect;

				rect.right = (long)22.5f;
				rect.left = (long)-22.5f;
				rect.top = (long)-22.5f;
				rect.bottom = (long)22.5f;

				// Text 출력      
				pInventory->GetFont()->DrawText(EngineMgr->GetpSprite(), line, -1, &rect, DT_RIGHT | DT_BOTTOM , 0xffffffff);      

				EngineMgr->GetpSprite()->End();

				// 월드 좌표를 원점으로 되돌린다.
				D3DXMatrixIdentity(&mtMatrix);
				EngineMgr->GetpSprite()->SetTransform(&mtMatrix);
			}
		}
		pInventory->InitChainVector();
	}
}

void CInventoryInProduction::Exit(CInventory* pInventory){
	
}

bool CInventoryInProduction::OnMessage(CInventory* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Close:
			agent->GetFSM()->ChangeState(InventoryMinimize->Instance());
			return true;
		default:
			return false;
	}
}