#include "../BaseHeader.h"

CDustKid::CDustKid(int id):CCharacterEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CDustKid>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Character/Enemy/Dusts/Kid/DustKid.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(DustKidReady->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	SetTribeType(CCharacterEntity::DUST);
	InitHealthy(150);
	SetDef(1.0f);

	SetAttackTimeGap(5000);
	SetAttackTime(GetAttackTimeGap());

	SetDestinationX(-700.0f);

	_body->SetRow(CBaseObject::LEFT);

	GetBody()->SetVelocity(50.0f);
}

CDustKid::~CDustKid(){
	d3d::Delete< CStateMachine<CDustKid>* >(m_pStateMachine);
}

void CDustKid::RenderOrgan(){
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

void CDustKid::BoundUpdate(){
	SetEntityBound(&D3DXVECTOR3(_body->GetPriPos()->x - _body->GetWidthHalf() + 30.0f, GetBody()->GetPriPos()->y - _body->GetHeightHalf(), 0.0f),
		&D3DXVECTOR3(_body->GetPriPos()->x + _body->GetWidthHalf() - 30.0f, GetBody()->GetPriPos()->y + _body->GetHeightHalf(), 0.0f));
	SetAttackBound(&D3DXVECTOR3(_body->GetPriPos()->x - _body->GetWidthHalf(), GetBody()->GetPriPos()->y - _body->GetHeightHalf(), 0.0f),
		&D3DXVECTOR3(_body->GetPriPos()->x + _body->GetWidthHalf(), GetBody()->GetPriPos()->y + _body->GetHeightHalf(), 0.0f));
}