#include "../BaseHeader.h"

CYawo::CYawo(int id):CCharacterEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CYawo>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Character/Serve/YawoYawo/YawoYawo.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(YawoCreate->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	SetTribeType(CCharacterEntity::IRON);
	InitHealthy(50);
	SetDef(1.0f);
	_body->SetVelocity(35.5f);
	SetMinDamage(5.0f);
	SetMaxDamage(8.0f);
	SetAttackTimeGap(2000);
	SetAttackTime(GetAttackTimeGap());

	UIMgr->GetSmallInfoList()->Append(new CSmallInfo(this));
}

CYawo::~CYawo(){
	d3d::Delete< CStateMachine<CYawo>* >(m_pStateMachine);

	CDListIterator<CSmallInfo*> itr;
	CDListIterator<CLightEffect*> itrEffect;

	itr = UIMgr->GetSmallInfoList()->GetIterator();
	itrEffect = EffectMgr->GetLightEffectList()->GetIterator();

	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(GetOwner() == itr.Item()->GetOrigin()->GetOwner()){
			UIMgr->GetSmallInfoList()->Remove(itr);

			for(itrEffect.Start(); itrEffect.Valid(); itrEffect.Forth()){
				if(GetOwner() == itrEffect.Item()->GetOrgan()->GetOwner()){
					EffectMgr->GetLightEffectList()->Remove(itrEffect);
				}
			}
			break;
		}
	}
}

void CYawo::RenderOrgan(){
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

void CYawo::BoundUpdate(){
	if(GetBody()->GetRow() == CBaseObject::RIGHT){
		SetAttackBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x + 30.0f, GetBody()->GetPriPos()->y + 45, 0.0f),
			&D3DXVECTOR3(GetBody()->GetPriPos()->x + 430.0f, GetBody()->GetPriPos()->y + 85.0f, 0.0f));
	}
	else{
		SetAttackBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x - 430.0f, GetBody()->GetPriPos()->y + 45, 0.0f),
			&D3DXVECTOR3(GetBody()->GetPriPos()->x - 30.0f, GetBody()->GetPriPos()->y + 85.0f, 0.0f));
	}

	SetEntityBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x - GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y - GetBody()->GetHeightHalf(), 0.0f),
		&D3DXVECTOR3(GetBody()->GetPriPos()->x + GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y + GetBody()->GetHeightHalf(), 0.0f));
}

void CYawo::ApplyDamageOurForceToEnemy(){
	int t_nDamage = AIMgr->ComputeAverageDamage(GetMinDamage(), GetMaxDamage());
	float t_fPosX, t_fPosY = 0.0f;

	if(_body->GetRow() == CBaseObject::LEFT){
		EffectMgr->InsertRayEffect(&D3DXVECTOR3(GetAttackBound()->_max.x - GetDistance() * 0.5f, GetAttackBound()->_min.y + 20.0f, 0.0f), GetDistance() - 40.0f);
		t_fPosX = GetAttackBound()->_max.x - GetDistance();
		t_fPosY = GetAttackBound()->_min.y + 20.0f;
	}
	else{
		EffectMgr->InsertRayEffect(&D3DXVECTOR3(GetAttackBound()->_min.x + GetDistance() * 0.5f, GetAttackBound()->_min.y + 20.0f, 0.0f), GetDistance() - 40.0f);
		t_fPosX = GetAttackBound()->_min.x + GetDistance();
		t_fPosY = GetAttackBound()->_min.y + 20.0f;
	}

	switch(StageMgr->GetStageType()){
		case CStageManager::SCRAPMOUNTAIN:
			switch(StageMgr->GetAreaNumber()){
				case 0:
					AIMgr->GetDustKid()->Damaged(t_fPosX, t_fPosY, t_nDamage);
					break;
				case 1:
					AIMgr->GetMiniWorker()->Damaged(t_fPosX, t_fPosY, t_nDamage);
					break;
				case 2:
					AIMgr->GetWorker()->Damaged(t_fPosX, t_fPosY, t_nDamage);
					break;
			}
			break;
		case CStageManager::FURNACE:
			AIMgr->GetGateKeeper()->Damaged(t_fPosX, t_fPosY, t_nDamage);
			break;
		case CStageManager::DUSTBRIDGE:
			AIMgr->GetDustKing()->Damaged(t_fPosX, t_fPosY, t_nDamage);
			break;
	}
}