#include "../BaseHeader.h"

CTinkle::CTinkle(int id):CCharacterEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CTinkle>(this);

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Character/Serve/TinkleTinkle/TinkleTinkle.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(TinkleCreate->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	// ���۵� �Ʊ� Ȱ��ȭ
	CDListIterator<CCharacterEntity*> itrEntity = AIMgr->GetOurForceList()->GetIterator();

	for(itrEntity.Start(); itrEntity.Valid(); itrEntity.Forth()){			
		EffectMgr->InsertLightEffect(itrEntity.Item()->GetBody());
	}

	InitHealthy(10000);
	SetTribeType(CCharacterEntity::IRON);

	UIMgr->GetSmallInfoList()->Append(new CSmallInfo(this));
}

CTinkle::~CTinkle(){
	d3d::Delete< CStateMachine<CTinkle>* >(m_pStateMachine);

	CDListIterator<CSmallInfo*> itr;

	itr = UIMgr->GetSmallInfoList()->GetIterator();

	for(itr.Start(); itr.Valid(); itr.Forth()){
		if(GetOwner() == itr.Item()->GetOrigin()->GetOwner()){
			UIMgr->GetSmallInfoList()->Remove(itr);
			break;
		}
	}
}