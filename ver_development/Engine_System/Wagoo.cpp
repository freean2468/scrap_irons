#include "../BaseHeader.h"

CWagoo::CWagoo(int id):CCharacterEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CWagoo>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Character/Serve/WagooWagoo/WagooWagoo.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(WagooCreate->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	SetTribeType(CCharacterEntity::IRON);
	InitHealthy(80);
	SetDef(1.0f);
	_body->SetVelocity(104.5f);
	SetMinDamage(4.0f);
	SetMaxDamage(6.0f);

	UIMgr->GetSmallInfoList()->Append(new CSmallInfo(this));
}

CWagoo::~CWagoo(){
	d3d::Delete< CStateMachine<CWagoo>* >(m_pStateMachine);

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

void CWagoo::RenderOrgan(){
	BodySetting();
	GetBody()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
	
	InitChainVector();

	CAttachment* t_pAtt = NULL;

	if(GetAttachmentArray()->GetSize()){
		for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
			BodySetting();

			if(GetAttachmentArray()->Get(i)->GetAttType() == CWagoo::EYE)
				t_pAtt->SettingJointOrgan(GetChainRot(), GetChainCen());

			GetAttachmentArray()->Get(i)->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			InitChainVector();
			
			if(GetAttachmentArray()->Get(i)->GetAttType() == CWagoo::HEAD){
				t_pAtt = GetAttachmentArray()->Get(i);
			}
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

void CWagoo::BoundUpdate(){
	if(GetBody()->GetRow() == CBaseObject::RIGHT){
		SetAttackBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x + 10.0f, GetBody()->GetPriPos()->y - 20.0f, 0.0f),
			&D3DXVECTOR3(GetBody()->GetPriPos()->x + 45.0f, GetBody()->GetPriPos()->y + 20.0f, 0.0f));
	}
	else{
		SetAttackBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x - 45.0f, GetBody()->GetPriPos()->y - 20.0f, 0.0f),
			&D3DXVECTOR3(GetBody()->GetPriPos()->x - 10.0f, GetBody()->GetPriPos()->y + 20.0f, 0.0f));
	}

	SetEntityBound(&D3DXVECTOR3(GetBody()->GetPriPos()->x - GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y - GetBody()->GetHeightHalf(), 0.0f),
		&D3DXVECTOR3(GetBody()->GetPriPos()->x + GetBody()->GetWidthHalf(), GetBody()->GetPriPos()->y + GetBody()->GetHeightHalf(), 0.0f));
}