#include "../BaseHeader.h"

CDustKing::CDustKing(int id):CCharacterEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CDustKing>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Character/Enemy/Dusts/King/King.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(DustKingReady->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	SetTribeType(CCharacterEntity::DUST);
	InitHealthy(360);
	SetDef(1.6f);

	SetAttackTimeGap(4000);
	SetAttackTime(GetAttackTimeGap());

	SetDestinationX(300.0f);

	_body->SetRow(CBaseObject::RIGHT);
}

CDustKing::~CDustKing(){
	d3d::Delete< CStateMachine<CDustKing>* >(m_pStateMachine);
}

void CDustKing::RenderOrgan(){
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

void CDustKing::BoundUpdate(){
	SetEntityBound(&D3DXVECTOR3(_body->GetPriPos()->x - _body->GetWidthHalf() + 60.0f, GetBody()->GetPriPos()->y - _body->GetHeightHalf(), 0.0f),
		&D3DXVECTOR3(_body->GetPriPos()->x + _body->GetWidthHalf() - 60.0f, GetBody()->GetPriPos()->y + _body->GetHeightHalf(), 0.0f));
	SetAttackBound(&D3DXVECTOR3(_body->GetPriPos()->x - _body->GetWidthHalf() + 30.0f, GetBody()->GetPriPos()->y - _body->GetHeightHalf(), 0.0f),
		&D3DXVECTOR3(_body->GetPriPos()->x + _body->GetWidthHalf() - 30.0f, GetBody()->GetPriPos()->y + _body->GetHeightHalf(), 0.0f));
}