#include "../BaseHeader.h"

CTinkle::CTinkle(int id):CCharacterEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CTinkle>(this);

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Character/Serve/TinkleTinkle/TinkleTinkle.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(TinkleCreate->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	// 제작된 아군 활성화
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