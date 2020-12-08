#include "../BaseHeader.h"

CWorldMap::CWorldMap(int id):COrganEntity(id){
	// ���±�踦 �����Ѵ�.
	m_pStateMachine = new CStateMachine<CWorldMap>(this);

	LoadEntityData("./script/Map/WorldMap.txt", this);

	// ó�� ���¸� �ʱ�ȭ
	m_pStateMachine->SetCurrentState(WorldMapUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CWorldMap::~CWorldMap(){
	d3d::Delete< CStateMachine<CWorldMap>* >(m_pStateMachine);
}

void CWorldMap::RenderOrgan(){
	BodySetting();
	GetBody()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
	
	InitChainVector();

	if(GetAttachmentArray()->GetSize()){
		for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
			if(GetAttachmentArray()->Get(i)->GetAttType() == STAGEPOINT){
				continue;
			}
			else{
				BodySetting();
				GetAttachmentArray()->Get(i)->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
				InitChainVector();
			}
		}
	}

	if(!EventMgr->GetEventWorldMap()->_ending){
		// �ſ� ��ƼŬ
		EngineMgr->UpdateExhaust();	
		EngineMgr->RenderExhaust();	
	}

	InitChainVector();

	if(GetMessage()){
		if(GetMessage()->GetUse()){
			BodyOnlyPosSetting();
			GetMessage()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			GetMessage()->RenderLine();
		}
	}

	InitChainVector();
}
