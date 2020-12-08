#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Show State
///////////////////////////////////////////////////////////
void CBluePrintListShow::Enter(CBluePrintList* pList){
	
}

void CBluePrintListShow::Execute(CBluePrintList* pList){
	// 바디 계산
	CBody* t_pBody = pList->GetBody();
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_vPos.x - 190.0f;
	t_pBody->GetPriPos()->y = t_vPos.y + 90.0f;
	t_pBody->GetPriPos()->z = 700.0f + t_vPos.z;
	
	// 설계도 목록 창 렌더
	pList->RenderOrgan();

	char line[64];

	// 반복자 생성
	CDListIterator<CBluePrintScroll*> itr;
	
	// _entityList로부터 반복자 초기화
	itr = pList->GetScrollList()->GetIterator();

	// 설계도 인덱스 텍스트
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(itr.Item()->GetDeltaY() + t_pBody->GetPriPos()->y < t_pBody->GetTop() &&
			itr.Item()->GetDeltaY() + t_pBody->GetPriPos()->y > t_pBody->GetBottom() + 50.0f){
			pList->BodySetting();			
			
			strcpy(line, itr.Item()->GetTitle());
			line[63] = '\0';

			EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

			D3DXVECTOR3 _vPos;			// 위치 벡터
			D3DXMATRIXA16 _pos;			// 위치 변환 행렬
			D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
			D3DXVECTOR3 _vRotate;		// 회전 벡터

			D3DXMATRIXA16 mtMatrix;
			D3DXMatrixIdentity(&mtMatrix);

			D3DXMatrixTranslation(&_pos, t_pBody->GetPriPos()->x, t_pBody->GetPriPos()->y  + itr.Item()->GetDeltaY(), t_pBody->GetPriPos()->z);

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
			pList->GetFont()->DrawText(EngineMgr->GetpSprite(), line, -1, &rect, DT_CENTER | DT_VCENTER , 0xffffffff);      

			EngineMgr->GetpSprite()->End();

			float t_fMX = EngineMgr->GetpInformation()->GetAdjustedX();
			float t_fMY = EngineMgr->GetpInformation()->GetAdjustedY();

			if(120.0f + t_pBody->GetPriPos()->x > t_fMX  && -140.0f + t_pBody->GetPriPos()->x < t_fMX &&
				50.0f + t_pBody->GetPriPos()->y + itr.Item()->GetDeltaY() > t_fMY && -20.0f + t_pBody->GetPriPos()->y + itr.Item()->GetDeltaY() < t_fMY &&
				EngineMgr->GetLButtonState() == 1){
					// 반복자 생성
					CDListIterator<CBluePrintScroll*> itrScroll;				
					itrScroll = pList->GetScrollList()->GetIterator();

					// 모든 스크롤을 최소화 시킨 후
					for(itrScroll.Start(); itrScroll.Valid(); itrScroll.Forth())
						itrScroll.Item()->GetFSM()->ChangeState(BluePrintScrollMinimize->Instance());

					pList->SetSelectionList(true);
					itr.Item()->GetFSM()->ChangeState(BluePrintScrollShow->Instance());
				}

			// 월드 좌표를 원점으로 되돌린다.
			D3DXMatrixIdentity(&mtMatrix);
			EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

			pList->InitChainVector();			
		}
		itr.Item()->Update();
	}

	UIMgr->ComputeBoundBluePirntScrollUpDown();
}

void CBluePrintListShow::Exit(CBluePrintList* pList){

}

bool CBluePrintListShow::OnMessage(CBluePrintList* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Close:
			agent->GetFSM()->ChangeState(BluePrintListMinimize->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
void CBluePrintListMinimize::Enter(CBluePrintList* pList){
	
}

void CBluePrintListMinimize::Execute(CBluePrintList* pList){

}

void CBluePrintListMinimize::Exit(CBluePrintList* pList){

}

bool CBluePrintListMinimize::OnMessage(CBluePrintList* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Activate:
			agent->GetFSM()->ChangeState(BluePrintListShow->Instance());
			return true;
		case Msg_InProduction:
			agent->GetFSM()->ChangeState(BluePrintListInProduction->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// InProduction State
///////////////////////////////////////////////////////////
void CBluePrintListInProduction::Enter(CBluePrintList* pList){
	
}

void CBluePrintListInProduction::Execute(CBluePrintList* pList){
	// 바디 계산	
	CBody* t_pBody = pList->GetBody();
	CBody* t_pProductionBody = UIMgr->GetUI(CBaseObject::PRODUCTION)->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_pProductionBody->GetPriPos()->x - 190.0f;
	t_pBody->GetPriPos()->y = t_pProductionBody->GetPriPos()->y + 70.0f;
	t_pBody->GetPriPos()->z = 700.0f + t_vPos.z;
	
	pList->RenderOrgan();	
	
	char line[64];

	// 반복자 생성
	CDListIterator<CBluePrintScroll*> itr;
	
	itr = pList->GetScrollList()->GetIterator();

	// 설계도 인덱스 텍스트
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(itr.Item()->GetDeltaY() + t_pBody->GetPriPos()->y < t_pBody->GetTop() &&
			itr.Item()->GetDeltaY() + t_pBody->GetPriPos()->y > t_pBody->GetBottom() + 50.0f){
			pList->BodySetting();			
			
			strcpy(line, itr.Item()->GetTitle());
			line[63] = '\0';

			EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

			D3DXVECTOR3 _vPos;			// 위치 벡터
			D3DXMATRIXA16 _pos;			// 위치 변환 행렬
			D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
			D3DXVECTOR3 _vRotate;		// 회전 벡터

			D3DXMATRIXA16 mtMatrix;
			D3DXMatrixIdentity(&mtMatrix);

			D3DXMatrixTranslation(&_pos, t_pBody->GetPriPos()->x, t_pBody->GetPriPos()->y + itr.Item()->GetDeltaY(), t_pBody->GetPriPos()->z);

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
			pList->GetFont()->DrawText(EngineMgr->GetpSprite(), line, -1, &rect, DT_CENTER | DT_VCENTER , 0xffffffff);      

			EngineMgr->GetpSprite()->End();

			float t_fMX = EngineMgr->GetpInformation()->GetAdjustedX();
			float t_fMY = EngineMgr->GetpInformation()->GetAdjustedY();

			if(100.0f + t_pBody->GetPriPos()->x > t_fMX  && -100.0f + t_pBody->GetPriPos()->x < t_fMX &&
				50.0f + t_pBody->GetPriPos()->y + itr.Item()->GetDeltaY() > t_fMY && -15.0f + t_pBody->GetPriPos()->y + itr.Item()->GetDeltaY()< t_fMY &&
				EngineMgr->GetLButtonState() == 1){
				CDListIterator<CCharacterEntity*> itrEntity = AIMgr->GetOurForceList()->GetIterator();

				// 반복자 생성
				CDListIterator<CBluePrintScroll*> itrScroll;				
				itrScroll = pList->GetScrollList()->GetIterator();

				// 모든 스크롤을 최소화 시킨 후
				for(itrScroll.Start(); itrScroll.Valid(); itrScroll.Forth())
					itrScroll.Item()->GetFSM()->ChangeState(BluePrintScrollMinimize->Instance());

				// 중복 체크
				for(itrEntity.Start(); itrEntity.Valid(); itrEntity.Forth()){			
					if(itrEntity.Item()->ID() == itr.Item()->GetOurForceTypeID()){
						pList->SetOverap(true);
						break;
					}
					else
						pList->SetOverap(false);

				}

				pList->SetSelectionList(true);
				pList->SetSelectIndex(itr.Item()->GetIndex());
				itr.Item()->GetFSM()->ChangeState(BluePrintScrollInProduction->Instance());
			}

			// 월드 좌표를 원점으로 되돌린다.
			D3DXMatrixIdentity(&mtMatrix);
			EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

			pList->InitChainVector();
		}
		itr.Item()->Update();
	}

	UIMgr->ComputeBoundBluePirntScrollUpDown();
}

void CBluePrintListInProduction::Exit(CBluePrintList* pList){
	
}

bool CBluePrintListInProduction::OnMessage(CBluePrintList* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Close:
			agent->GetFSM()->ChangeState(BluePrintListMinimize->Instance());
			return true;
		default:
			return false;
	}
}