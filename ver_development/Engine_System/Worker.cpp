#include "../BaseHeader.h"

CWorker::CWorker(int id):CCharacterEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CWorker>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Character/Enemy/Worker/Worker.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(WorkerReady->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	SetTribeType(CCharacterEntity::IRON);
	InitHealthy(280);
	SetDef(1.3f);

	SetAttackTimeGap(5500);
	SetAttackTime(GetAttackTimeGap());

	SetDestinationX(-400.0f);

	_body->SetRow(CBaseObject::LEFT);
	_body->SetVelocity(15.0f);
}

CWorker::~CWorker(){
	d3d::Delete< CStateMachine<CWorker>* >(m_pStateMachine);
}

void CWorker::RenderOrgan(){
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

void CWorker::BoundUpdate(){
	SetEntityBound(&D3DXVECTOR3(_body->GetPriPos()->x - GetAttachmentFromType(BODY)->GetRight() + 120.0f, GetBody()->GetPriPos()->y + GetAttachmentFromType(BODY)->GetBottom(), 0.0f),
		&D3DXVECTOR3(_body->GetPriPos()->x - GetAttachmentFromType(BODY)->GetLeft() - 80.0f, GetBody()->GetPriPos()->y + GetAttachmentFromType(BODY)->GetTop(), 0.0f));

	_mouseUnder._min = D3DXVECTOR3(GetBody()->GetPriPos()->x - GetAttachmentFromType(MOUSEUNDER)->GetRight() + 20.0f, GetBody()->GetPriPos()->y + GetAttachmentFromType(MOUSEUNDER)->GetBottom(), 0.0f);
	_mouseUnder._max = D3DXVECTOR3(GetBody()->GetPriPos()->x - GetAttachmentFromType(MOUSEUNDER)->GetLeft() - 60.0f , GetBody()->GetPriPos()->y + GetAttachmentFromType(MOUSEUNDER)->GetTop(), 0.0f);

	SetAttackBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x - GetAttachmentFromType(MOUSEUNDER)->GetRight() + 60.0f, GetBody()->GetPriPos()->y + GetAttachmentFromType(MOUSEUNDER)->GetBottom() + 30.0f, 0.0f),
		&D3DXVECTOR3(GetBody()->GetPriPos()->x + GetAttachmentFromType(MOUSEUNDER)->GetLeft() - 100.0f, GetBody()->GetPriPos()->y + GetAttachmentFromType(MOUSEUNDER)->GetTop() + 20.0f, 0.0f));
}

bool CWorker::ComputeBoundMouseAndItem(){	
		// 반복자 생성
	CDListIterator<CItem*> itr;
	
	// _itemList로부터 반복자 초기화
	itr = ObjectMgr->GetItemList()->GetIterator();

	bool t_bDestroy = false;

	// _entityList를 훑으며
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

void CWorker::BoundRender(){
	EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

	D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
	D3DXVECTOR3 _vRotate;		// 회전 벡터

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

	// Text 출력
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "1", -1, &rect, DT_LEFT | DT_TOP , 0xffff0000);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "2", -1, &rect, DT_RIGHT | DT_TOP , 0xffff0000);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "3", -1, &rect, DT_LEFT | DT_BOTTOM , 0xffff0000);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "4", -1, &rect, DT_RIGHT | DT_BOTTOM , 0xffff0000);      

	rect.right = (long)(GetEntityBound()->_max.x);
	rect.left = (long)(GetEntityBound()->_min.x);
	rect.top = -(long)(GetEntityBound()->_max.y);
	rect.bottom = -(long)(GetEntityBound()->_min.y);

	// Text 출력
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "1", -1, &rect, DT_LEFT | DT_TOP , 0xff00ff11);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "2", -1, &rect, DT_RIGHT | DT_TOP , 0xff00ff11);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "3", -1, &rect, DT_LEFT | DT_BOTTOM , 0xff00ff11);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "4", -1, &rect, DT_RIGHT | DT_BOTTOM , 0xff00ff11);      

	rect.right = (long)(_mouseUnder._max.x);
	rect.left = (long)(_mouseUnder._min.x);
	rect.top = -(long)(_mouseUnder._max.y);
	rect.bottom = -(long)(_mouseUnder._min.y);

	// Text 출력
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "1", -1, &rect, DT_LEFT | DT_TOP , 0xffffffff);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "2", -1, &rect, DT_RIGHT | DT_TOP , 0xffffffff);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "3", -1, &rect, DT_LEFT | DT_BOTTOM , 0xffffffff);      
	GetBoundFont()->DrawText(EngineMgr->GetpSprite(), "4", -1, &rect, DT_RIGHT | DT_BOTTOM , 0xffffffff);         

	EngineMgr->GetpSprite()->End();

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);
}