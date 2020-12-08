#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Show State
///////////////////////////////////////////////////////////
void CBluePrintListShow::Enter(CBluePrintList* pList){
	
}

void CBluePrintListShow::Execute(CBluePrintList* pList){
	// �ٵ� ���
	CBody* t_pBody = pList->GetBody();
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_vPos.x - 190.0f;
	t_pBody->GetPriPos()->y = t_vPos.y + 90.0f;
	t_pBody->GetPriPos()->z = 700.0f + t_vPos.z;
	
	// ���赵 ��� â ����
	pList->RenderOrgan();

	char line[64];

	// �ݺ��� ����
	CDListIterator<CBluePrintScroll*> itr;
	
	// _entityList�κ��� �ݺ��� �ʱ�ȭ
	itr = pList->GetScrollList()->GetIterator();

	// ���赵 �ε��� �ؽ�Ʈ
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(itr.Item()->GetDeltaY() + t_pBody->GetPriPos()->y < t_pBody->GetTop() &&
			itr.Item()->GetDeltaY() + t_pBody->GetPriPos()->y > t_pBody->GetBottom() + 50.0f){
			pList->BodySetting();			
			
			strcpy(line, itr.Item()->GetTitle());
			line[63] = '\0';

			EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D ������ �ؽ�Ʈ ���

			D3DXVECTOR3 _vPos;			// ��ġ ����
			D3DXMATRIXA16 _pos;			// ��ġ ��ȯ ���
			D3DXMATRIXA16 _rotation;	// ȸ�� ��ȯ ���
			D3DXVECTOR3 _vRotate;		// ȸ�� ����

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

			// Text ���      
			pList->GetFont()->DrawText(EngineMgr->GetpSprite(), line, -1, &rect, DT_CENTER | DT_VCENTER , 0xffffffff);      

			EngineMgr->GetpSprite()->End();

			float t_fMX = EngineMgr->GetpInformation()->GetAdjustedX();
			float t_fMY = EngineMgr->GetpInformation()->GetAdjustedY();

			if(120.0f + t_pBody->GetPriPos()->x > t_fMX  && -140.0f + t_pBody->GetPriPos()->x < t_fMX &&
				50.0f + t_pBody->GetPriPos()->y + itr.Item()->GetDeltaY() > t_fMY && -20.0f + t_pBody->GetPriPos()->y + itr.Item()->GetDeltaY() < t_fMY &&
				EngineMgr->GetLButtonState() == 1){
					// �ݺ��� ����
					CDListIterator<CBluePrintScroll*> itrScroll;				
					itrScroll = pList->GetScrollList()->GetIterator();

					// ��� ��ũ���� �ּ�ȭ ��Ų ��
					for(itrScroll.Start(); itrScroll.Valid(); itrScroll.Forth())
						itrScroll.Item()->GetFSM()->ChangeState(BluePrintScrollMinimize->Instance());

					pList->SetSelectionList(true);
					itr.Item()->GetFSM()->ChangeState(BluePrintScrollShow->Instance());
				}

			// ���� ��ǥ�� �������� �ǵ�����.
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
	// �ٵ� ���	
	CBody* t_pBody = pList->GetBody();
	CBody* t_pProductionBody = UIMgr->GetUI(CBaseObject::PRODUCTION)->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_pProductionBody->GetPriPos()->x - 190.0f;
	t_pBody->GetPriPos()->y = t_pProductionBody->GetPriPos()->y + 70.0f;
	t_pBody->GetPriPos()->z = 700.0f + t_vPos.z;
	
	pList->RenderOrgan();	
	
	char line[64];

	// �ݺ��� ����
	CDListIterator<CBluePrintScroll*> itr;
	
	itr = pList->GetScrollList()->GetIterator();

	// ���赵 �ε��� �ؽ�Ʈ
	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(itr.Item()->GetDeltaY() + t_pBody->GetPriPos()->y < t_pBody->GetTop() &&
			itr.Item()->GetDeltaY() + t_pBody->GetPriPos()->y > t_pBody->GetBottom() + 50.0f){
			pList->BodySetting();			
			
			strcpy(line, itr.Item()->GetTitle());
			line[63] = '\0';

			EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D ������ �ؽ�Ʈ ���

			D3DXVECTOR3 _vPos;			// ��ġ ����
			D3DXMATRIXA16 _pos;			// ��ġ ��ȯ ���
			D3DXMATRIXA16 _rotation;	// ȸ�� ��ȯ ���
			D3DXVECTOR3 _vRotate;		// ȸ�� ����

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

			// Text ���      
			pList->GetFont()->DrawText(EngineMgr->GetpSprite(), line, -1, &rect, DT_CENTER | DT_VCENTER , 0xffffffff);      

			EngineMgr->GetpSprite()->End();

			float t_fMX = EngineMgr->GetpInformation()->GetAdjustedX();
			float t_fMY = EngineMgr->GetpInformation()->GetAdjustedY();

			if(100.0f + t_pBody->GetPriPos()->x > t_fMX  && -100.0f + t_pBody->GetPriPos()->x < t_fMX &&
				50.0f + t_pBody->GetPriPos()->y + itr.Item()->GetDeltaY() > t_fMY && -15.0f + t_pBody->GetPriPos()->y + itr.Item()->GetDeltaY()< t_fMY &&
				EngineMgr->GetLButtonState() == 1){
				CDListIterator<CCharacterEntity*> itrEntity = AIMgr->GetOurForceList()->GetIterator();

				// �ݺ��� ����
				CDListIterator<CBluePrintScroll*> itrScroll;				
				itrScroll = pList->GetScrollList()->GetIterator();

				// ��� ��ũ���� �ּ�ȭ ��Ų ��
				for(itrScroll.Start(); itrScroll.Valid(); itrScroll.Forth())
					itrScroll.Item()->GetFSM()->ChangeState(BluePrintScrollMinimize->Instance());

				// �ߺ� üũ
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

			// ���� ��ǥ�� �������� �ǵ�����.
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