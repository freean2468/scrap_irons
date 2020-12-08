#include "../BaseHeader.h"

///////////////////////////////////////////////////////////
// Show State
///////////////////////////////////////////////////////////
void CBluePrintScrollShow::Enter(CBluePrintScroll* pScroll){
	
}

void CBluePrintScrollShow::Execute(CBluePrintScroll* pScroll){
	// �ٵ� ���
	CBody* t_pBody = pScroll->GetBody();
	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_vPos.x + 150.0f;
	t_pBody->GetPriPos()->y = t_vPos.y;
	t_pBody->GetPriPos()->z = 700.0f + t_vPos.z;
	
	// ���赵 ��� â ����
	pScroll->RenderOrgan();

	float t_fDeltaX = -160.0f;
	float t_fDeltaY = -40.0f;
	char line[16];
	int nCount = 1;

	// �ݺ��� ����
	CDListIterator<CItem*> itrType;
	CDListIterator<int> itrCount;
	
	// _entityList�κ��� �ݺ��� �ʱ�ȭ
	itrType = pScroll->GetIngredients()->GetIterator();
	itrCount = pScroll->GetIngredientsCount()->GetIterator();

	// ���赵 �ε��� �ؽ�Ʈ
	for(itrType.Start(), itrCount.Start(); itrType.Valid(); itrType.Forth(), itrCount.Forth()){
		CBody* t_pItemBody = itrType.Item()->GetBody();
		switch(nCount % 4){
			case 1:
			case 2:	
			case 3:
				t_fDeltaX += 80.0f;
				break;
			case 0:					
				t_fDeltaX = - 80.0f;
				t_fDeltaY += -50.0f;
				break;
			default:
				break;
		}
		nCount++;

		itrType.Item()->GetBody()->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.7f;

		pScroll->BodySetting();	
		itrType.Item()->GetChainPos()->x = t_pBody->GetPriPos()->x + t_fDeltaX; itrType.Item()->GetChainPos()->y = t_pBody->GetPriPos()->y + t_fDeltaY; itrType.Item()->GetChainPos()->z = t_pBody->GetPriPos()->z;
		itrType.Item()->RenderOrgan();		
		
		itoa(itrCount.Item(), line, 10);
		line[15] = '\0';

		EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D ������ �ؽ�Ʈ ���

		D3DXVECTOR3 _vPos;			// ��ġ ����
		D3DXMATRIXA16 _pos;			// ��ġ ��ȯ ���
		D3DXMATRIXA16 _rotation;	// ȸ�� ��ȯ ���
		D3DXVECTOR3 _vRotate;		// ȸ�� ����

		D3DXMATRIXA16 mtMatrix;
		D3DXMatrixIdentity(&mtMatrix);

		D3DXMatrixTranslation(&_pos, t_pBody->GetPriPos()->x + t_fDeltaX + 35.0f, t_pBody->GetPriPos()->y + t_fDeltaY, t_pBody->GetPriPos()->z);

		D3DXMATRIXA16 rX;
		D3DXMatrixIdentity(&rX);
		D3DXMatrixRotationX(&rX, D3DX_PI);
		_rotation = rX;

		mtMatrix *= _rotation * _pos;

		EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

		RECT rect;

		rect.right = (long)10.0f;
		rect.left = (long)-10.0f;
		rect.top = (long)-10.0f;
		rect.bottom = (long)10.0f;

		// Text ���      
		pScroll->GetFont()->DrawText(EngineMgr->GetpSprite(), line, -1, &rect, DT_CENTER | DT_VCENTER , 0xff110000);      

		EngineMgr->GetpSprite()->End();

		float t_fMX = EngineMgr->GetpInformation()->GetAdjustedX();
		float t_fMY = EngineMgr->GetpInformation()->GetAdjustedY();

		// ���� ��ǥ�� �������� �ǵ�����.
		D3DXMatrixIdentity(&mtMatrix);
		EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

		pScroll->InitChainVector();
	}
}

void CBluePrintScrollShow::Exit(CBluePrintScroll* pScroll){

}

bool CBluePrintScrollShow::OnMessage(CBluePrintScroll* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Close:
			agent->GetFSM()->ChangeState(BluePrintScrollMinimize->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// Minimize State
///////////////////////////////////////////////////////////
void CBluePrintScrollMinimize::Enter(CBluePrintScroll* pScroll){
	
}

void CBluePrintScrollMinimize::Execute(CBluePrintScroll* pScroll){

}

void CBluePrintScrollMinimize::Exit(CBluePrintScroll* pScroll){

}

bool CBluePrintScrollMinimize::OnMessage(CBluePrintScroll* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Activate:
			agent->GetFSM()->ChangeState(BluePrintScrollShow->Instance());
			return true;
		case Msg_InProduction:
			agent->GetFSM()->ChangeState(BluePrintScrollInProduction->Instance());
			return true;
		default:
			return false;
	}
}

///////////////////////////////////////////////////////////
// InProduction State
///////////////////////////////////////////////////////////
void CBluePrintScrollInProduction::Enter(CBluePrintScroll* pScroll){
	
}

void CBluePrintScrollInProduction::Execute(CBluePrintScroll* pScroll){
	// �ٵ� ���	
	CBody* t_pBody = pScroll->GetBody();
	CBody* t_pProductionBody = UIMgr->GetUI(CBaseObject::PRODUCTION)->GetBody();

	D3DXVECTOR3 t_vPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	CameraMgr->GetCamera()->GetPosition(&t_vPos);

	t_pBody->GetPriPos()->x = t_pProductionBody->GetPriPos()->x + 160.0f;
	t_pBody->GetPriPos()->y = t_pProductionBody->GetPriPos()->y + 30.0f;
	t_pBody->GetPriPos()->z = 700.0f + t_vPos.z;
	
	// �κ��丮 â ����
	pScroll->RenderOrgan();	

	float t_fDeltaX = -160.0f;
	float t_fDeltaY = -40.0f;
	char line[16];
	char Inven[16];
	
	int nCount = 1;
	int t_nCompleteCount = 0;

	// �ݺ��� ����
	CDListIterator<CItem*> itrType;
	CDListIterator<int> itrCount;
	CArray<CItem*>* InvenArray = UIMgr->GetInventory()->GetThingsList();		// ����ǰ
	CArray<int>* InvenCount = UIMgr->GetInventory()->GetThingsCount();

	// _entityList�κ��� �ݺ��� �ʱ�ȭ
	itrType = pScroll->GetIngredients()->GetIterator();
	itrCount = pScroll->GetIngredientsCount()->GetIterator();

	// ���赵 �ε��� �ؽ�Ʈ
	for(itrType.Start(), itrCount.Start(); itrType.Valid(); itrType.Forth(), itrCount.Forth()){
		int InvenItemCount = 0;

		// �켱�� �� �������� �κ��丮�� �ִ��� Ȯ��
		for(int i = 0; i < INVENLIMIT; i++){
			if(InvenArray->Get(i)){
				if(InvenArray->Get(i)->GetItemType() == itrType.Item()->GetItemType()){
					InvenItemCount = InvenCount->Get(i);				
				}
			}
		}
		itoa(InvenItemCount, Inven, 10);

		CBody* t_pItemBody = itrType.Item()->GetBody();
		switch(nCount % 4){
			case 1:
			case 2:	
			case 3:
				t_fDeltaX += 80.0f;
				break;
			case 0:					
				t_fDeltaX = - 80.0f;
				t_fDeltaY += -50.0f;
				break;
			default:
				break;
		}
		nCount++;

		itrType.Item()->GetBody()->GetMtrlArray()->Get(0, 0).Diffuse.a = 0.7f;

		pScroll->BodySetting();	
		itrType.Item()->GetChainPos()->x = t_pBody->GetPriPos()->x + t_fDeltaX; itrType.Item()->GetChainPos()->y = t_pBody->GetPriPos()->y + t_fDeltaY; itrType.Item()->GetChainPos()->z = t_pBody->GetPriPos()->z;
		itrType.Item()->RenderOrgan();		
		
		itoa(itrCount.Item(), line, 10);
		line[15] = '\0';

		strcat(Inven, "/");
		strcat(Inven, line);

		EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D ������ �ؽ�Ʈ ���

		D3DXVECTOR3 _vPos;			// ��ġ ����
		D3DXMATRIXA16 _pos;			// ��ġ ��ȯ ���
		D3DXMATRIXA16 _rotation;	// ȸ�� ��ȯ ���
		D3DXVECTOR3 _vRotate;		// ȸ�� ����

		D3DXMATRIXA16 mtMatrix;
		D3DXMatrixIdentity(&mtMatrix);

		D3DXMatrixTranslation(&_pos, t_pBody->GetPriPos()->x + t_fDeltaX + 38.0f, t_pBody->GetPriPos()->y + t_fDeltaY, t_pBody->GetPriPos()->z);

		D3DXMATRIXA16 rX;
		D3DXMatrixIdentity(&rX);
		D3DXMatrixRotationX(&rX, D3DX_PI);
		_rotation = rX;

		mtMatrix *= _rotation * _pos;

		EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

		RECT rect;

		rect.right = (long)23.0f;
		rect.left = (long)-20.0f;
		rect.top = (long)-40.0f;
		rect.bottom = (long)40.0f;

		// Text ���      
		if(InvenItemCount < itrCount.Item()){
			pScroll->GetFont()->DrawText(EngineMgr->GetpSprite(), Inven, -1, &rect, DT_CENTER | DT_VCENTER , 0xffdd1010);      
			UIMgr->GetBluePrintList()->SetCompleteCollection(false);
		}
		else{
			t_nCompleteCount++;
			pScroll->GetFont()->DrawText(EngineMgr->GetpSprite(), Inven, -1, &rect, DT_CENTER | DT_VCENTER , 0xff22cc22);      
			if(t_nCompleteCount == pScroll->GetMaterialCount()){
				// ��� ���� �Ϸ�
				UIMgr->GetBluePrintList()->SetCompleteCollection(true);
			}
			else
				UIMgr->GetBluePrintList()->SetCompleteCollection(false);
		}

		EngineMgr->GetpSprite()->End();

		float t_fMX = EngineMgr->GetpInformation()->GetAdjustedX();
		float t_fMY = EngineMgr->GetpInformation()->GetAdjustedY();

		// ���� ��ǥ�� �������� �ǵ�����.
		D3DXMatrixIdentity(&mtMatrix);
		EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

		pScroll->InitChainVector();
	}
}

void CBluePrintScrollInProduction::Exit(CBluePrintScroll* pScroll){
	
}

bool CBluePrintScrollInProduction::OnMessage(CBluePrintScroll* agent, const Telegram& msg){
	switch(msg.Msg){
		case Msg_Close:
			agent->GetFSM()->ChangeState(BluePrintScrollMinimize->Instance());
			return true;
		default:
			return false;
	}
}