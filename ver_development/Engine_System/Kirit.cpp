#include "../BaseHeader.h"

CKirit::CKirit(int id):CCharacterEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CKirit>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Character/Serve/KiritKirit/KiritKirit.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(KiritCreate->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	SetTribeType(CCharacterEntity::IRON);
	InitHealthy(130);
	SetDef(1.0f);
	GetBody()->SetVelocity(87.0f);
	SetMinDamage(14.0f);
	SetMaxDamage(17.0f);

	UIMgr->GetSmallInfoList()->Append(new CSmallInfo(this));
}

CKirit::~CKirit(){
	d3d::Delete< CStateMachine<CKirit>* >(m_pStateMachine);

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

void CKirit::RenderOrgan(){
	if(GetAttachmentArray()->GetSize()){
		for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
			BodySetting();

			GetAttachmentArray()->Get(i)->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			InitChainVector();
		}
	}

	BodySetting();
	GetBody()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());

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

void CKirit::BoundUpdate(){
	SetEntityBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x - GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y - GetBody()->GetHeightHalf() + 20.0f, 0.0f),
		&D3DXVECTOR3(GetBody()->GetPriPos()->x + GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y + GetBody()->GetHeightHalf() - 20.0f, 0.0f));
	SetAttackBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x - GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y - GetBody()->GetHeightHalf(), 0.0f),
		&D3DXVECTOR3(GetBody()->GetPriPos()->x + GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y + GetBody()->GetHeightHalf(), 0.0f));
}