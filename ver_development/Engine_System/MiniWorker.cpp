#include "../BaseHeader.h"

CMiniWorker::CMiniWorker(int id):CCharacterEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CMiniWorker>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Character/Enemy/Worker/MiniWorker.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(MiniWorkerReady->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	SetTribeType(CCharacterEntity::IRON);
	InitHealthy(190);
	SetDef(1.2f);

	SetAttackTimeGap(4300);
	SetAttackTime(GetAttackTimeGap());

	SetDestinationX(-400.0f);

	_body->SetRow(CBaseObject::LEFT);
	_body->SetVelocity(20.0f);
}

CMiniWorker::~CMiniWorker(){
	d3d::Delete< CStateMachine<CMiniWorker>* >(m_pStateMachine);
}

void CMiniWorker::RenderOrgan(){
	BodySetting();
	GetBody()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
	
	InitChainVector();

	if(GetAttachmentArray()->GetSize()){
		for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
			BodySetting();
			GetAttachmentArray()->Get(i)->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			InitChainVector();
		}
	}

	InitChainVector();

	if(GetMessage()){
		if(GetMessage()->GetUse()){
			BodyOnlyPosSetting();
			GetMessage()->SettingOrgan(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			GetMessage()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			GetMessage()->RenderLine();
		}
	}

	InitChainVector();
}

void CMiniWorker::BoundUpdate(){
	SetEntityBound(&D3DXVECTOR3(_body->GetPriPos()->x - GetAttachmentFromType(BODY)->GetRight() + 60.0f, GetBody()->GetPriPos()->y + GetAttachmentFromType(BODY)->GetBottom(), 0.0f),
		&D3DXVECTOR3(_body->GetPriPos()->x - GetAttachmentFromType(BODY)->GetLeft() - 40.0f, GetBody()->GetPriPos()->y + GetAttachmentFromType(BODY)->GetTop(), 0.0f));

	_mouseUnder._min = D3DXVECTOR3(GetBody()->GetPriPos()->x - GetAttachmentFromType(MOUSEUNDER)->GetRight() + 10.0f, GetBody()->GetPriPos()->y + GetAttachmentFromType(MOUSEUNDER)->GetBottom(), 0.0f);
	_mouseUnder._max = D3DXVECTOR3(GetBody()->GetPriPos()->x - GetAttachmentFromType(MOUSEUNDER)->GetLeft() - 15.0f, GetBody()->GetPriPos()->y + GetAttachmentFromType(MOUSEUNDER)->GetTop(), 0.0f);

	SetAttackBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x - GetAttachmentFromType(MOUSEUNDER)->GetRight() + 30.0f, GetBody()->GetPriPos()->y + GetAttachmentFromType(MOUSEUNDER)->GetBottom() + 30.0f, 0.0f),
		&D3DXVECTOR3(GetBody()->GetPriPos()->x + GetAttachmentFromType(MOUSEUNDER)->GetLeft() - 50.0f, GetBody()->GetPriPos()->y + GetAttachmentFromType(MOUSEUNDER)->GetTop() + 20.0f, 0.0f));
}

bool CMiniWorker::ComputeBoundMouseAndItem(){	
		// �ݺ��� ����
	CDListIterator<CItem*> itr;
	
	// _itemList�κ��� �ݺ��� �ʱ�ȭ
	itr = ObjectMgr->GetItemList()->GetIterator();

	bool t_bDestroy = false;

	// _entityList�� ������
	for(itr.Start(); itr.Valid(); itr.Forth()){
		CBody* t_pBody = itr.Item()->GetBody();
		
		if(_mouseUnder._min.x < t_pBody->GetRight() && _mouseUnder._max.x > t_pBody->GetLeft()){			
			itr.Item()->GetFSM()->ChangeState(ItemDestroyed->Instance());		
			t_bDestroy = true;
		}
	}
	
	if(t_bDestroy)
		return true;
	else
		return false;
}

void CMiniWorker::BoundRender(){
	EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D ������ �ؽ�Ʈ ���

	D3DXMATRIXA16 _rotation;	// ȸ�� ��ȯ ���
	D3DXVECTOR3 _vRotate;		// ȸ�� ����

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMATRIXA16 rX;
	D3DXMatrixIdentity(&rX);
	D3DXMatrixRotationX(&rX, D3DX_PI);
	_rotation = rX;

	mtMatrix *= _rotation;

	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

	RECT rect;

	rect.right = (long)(GetAttackBound()->_max.x);
	rect.left = (long)(GetAttackBound()->_min.x);
	rect.top = -(long)(GetAttackBound()->_max.y);
	rect.bottom = -(long)(GetAttackBound()->_min.y);

	// Text ���
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "1", -1, &rect, DT_LEFT | DT_TOP , 0xffff0000);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "2", -1, &rect, DT_RIGHT | DT_TOP , 0xffff0000);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "3", -1, &rect, DT_LEFT | DT_BOTTOM , 0xffff0000);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "4", -1, &rect, DT_RIGHT | DT_BOTTOM , 0xffff0000);      

	rect.right = (long)(GetEntityBound()->_max.x);
	rect.left = (long)(GetEntityBound()->_min.x);
	rect.top = -(long)(GetEntityBound()->_max.y);
	rect.bottom = -(long)(GetEntityBound()->_min.y);

	// Text ���
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "1", -1, &rect, DT_LEFT | DT_TOP , 0xff00ff11);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "2", -1, &rect, DT_RIGHT | DT_TOP , 0xff00ff11);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "3", -1, &rect, DT_LEFT | DT_BOTTOM , 0xff00ff11);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "4", -1, &rect, DT_RIGHT | DT_BOTTOM , 0xff00ff11);      

	rect.right = (long)(_mouseUnder._max.x);
	rect.left = (long)(_mouseUnder._min.x);
	rect.top = -(long)(_mouseUnder._max.y);
	rect.bottom = -(long)(_mouseUnder._min.y);

	// Text ���
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "1", -1, &rect, DT_LEFT | DT_TOP , 0xffffffff);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "2", -1, &rect, DT_RIGHT | DT_TOP , 0xffffffff);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "3", -1, &rect, DT_LEFT | DT_BOTTOM , 0xffffffff);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "4", -1, &rect, DT_RIGHT | DT_BOTTOM , 0xffffffff);         

	EngineMgr->GetpSprite()->End();

	// ���� ��ǥ�� �������� �ǵ�����.
	D3DXMatrixIdentity(&mtMatrix);
	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);
}