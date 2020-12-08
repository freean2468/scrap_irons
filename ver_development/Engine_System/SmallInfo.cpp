#include "../BaseHeader.h"

CSmallInfo::CSmallInfo(CCharacterEntity* p_pEntity):COrganEntity(ID_SMALLINFO){
	_origin = p_pEntity;

	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CSmallInfo>(this);

	switch(_origin->GetOwner()){
		case CBaseObject::WAGOO:
			this->LoadEntityData("./script/UserInterface/SmallInfo/Wagoo.txt", this);
			break;
		case CBaseObject::WOOWO:
			this->LoadEntityData("./script/UserInterface/SmallInfo/Woowo.txt", this);
			break;
		case CBaseObject::YAWO:
			this->LoadEntityData("./script/UserInterface/SmallInfo/Yawo.txt", this);
			break;
		case CBaseObject::KIRIT:
			this->LoadEntityData("./script/UserInterface/SmallInfo/Kirit.txt", this);
			break;
		case CBaseObject::TINKLE:
			this->LoadEntityData("./script/UserInterface/SmallInfo/Tinkle.txt", this);
			break;
	}

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(SmallInfoActive->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CSmallInfo::~CSmallInfo(){
	d3d::Delete< CStateMachine<CSmallInfo>* >(m_pStateMachine);
}