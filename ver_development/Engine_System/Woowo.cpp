#include "../BaseHeader.h"

CWoowo::CWoowo(int id):CCharacterEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CWoowo>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Character/Serve/WoowoWoowo/WoowoWoowo.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(WoowoCreate->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	SetTribeType(CCharacterEntity::IRON);
	InitHealthy(120);
	SetDef(1.0f);
	_body->SetVelocity(47.5f);
	SetMinDamage(12.0f);
	SetMaxDamage(15.0f);
	SetAttackTimeGap(4000);
	SetAttackTime(GetAttackTimeGap());

	UIMgr->GetSmallInfoList()->Append(new CSmallInfo(this));
}

CWoowo::~CWoowo(){
	d3d::Delete< CStateMachine<CWoowo>* >(m_pStateMachine);

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

void CWoowo::RenderOrgan(){
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

void CWoowo::BoundUpdate(){
	if(GetBody()->GetRow() == CBaseObject::RIGHT){
		SetAttackBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x + 30.0f, GetBody()->GetPriPos()->y, 0.0f),
			&D3DXVECTOR3(GetBody()->GetPriPos()->x + 80.0f, GetBody()->GetPriPos()->y + 40.0f, 0.0f));
	}
	else{
		SetAttackBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x - 80.0f, GetBody()->GetPriPos()->y, 0.0f),
			&D3DXVECTOR3(GetBody()->GetPriPos()->x - 30.0f, GetBody()->GetPriPos()->y + 40.0f, 0.0f));
	}

	SetEntityBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x - GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y - GetBody()->GetHeightHalf() + 20.0f, 0.0f),
		&D3DXVECTOR3(GetBody()->GetPriPos()->x + GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y + GetBody()->GetHeightHalf() - 40.0f, 0.0f));
}