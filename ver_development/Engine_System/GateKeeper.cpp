#include "../BaseHeader.h"

CGateKeeper::CGateKeeper(int id):CCharacterEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CGateKeeper>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Character/Enemy/GateKeeper/GateKeeper.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(GateKeeperReady->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	SetTribeType(CCharacterEntity::IRON);
	InitHealthy(300);
	SetDef(1.4f);

	SetAttackTimeGap(4700);
	SetAttackTime(GetAttackTimeGap());

	SetDestinationX(200.0f);

	_body->SetRow(CBaseObject::LEFT);

	_deltaY = 0.0f;
}

CGateKeeper::~CGateKeeper(){
	d3d::Delete< CStateMachine<CGateKeeper>* >(m_pStateMachine);
}

void CGateKeeper::RenderOrgan(){
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

void CGateKeeper::BoundUpdate(){
	SetEntityBound(&D3DXVECTOR3(_body->GetPriPos()->x - GetAttachmentFromType(ARM)->GetPriPos()->x - _body->GetWidthHalf() + 150.0f, GetBody()->GetPriPos()->y - _body->GetHeightHalf(), 0.0f),
		&D3DXVECTOR3(_body->GetPriPos()->x - GetAttachmentFromType(ARM)->GetPriPos()->x + _body->GetWidthHalf() - 150.0f, GetBody()->GetPriPos()->y + _body->GetHeightHalf(), 0.0f));

	SetAttackBound(&D3DXVECTOR3(_body->GetPriPos()->x - GetAttachmentFromType(ARM)->GetPriPos()->x - GetAttachmentFromType(ARM)->GetWidthHalf() + 50.0f, GetBody()->GetPriPos()->y - _body->GetHeightHalf(), 0.0f),
		&D3DXVECTOR3(_body->GetPriPos()->x - GetAttachmentFromType(ARM)->GetPriPos()->x + GetAttachmentFromType(ARM)->GetWidthHalf() - 50.0f, GetBody()->GetPriPos()->y + _body->GetHeightHalf(), 0.0f));
}