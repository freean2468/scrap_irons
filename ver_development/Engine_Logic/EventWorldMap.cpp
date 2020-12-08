#include "../BaseHeader.h"

CEventWorldMap::CEventWorldMap(int id):COrganEntity(id), _timer(NULL){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CEventWorldMap>(this);

	LoadEntityData("./script/Event/Event/EventWorldMap.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(EventWorldMapStageClear->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
	
	_pFont = d3d::IniFont(30, 15, 1000, false, "맑은 고딕");

	_timer = new CTimer();

	_ending = false;
}

CEventWorldMap::~CEventWorldMap(){
	d3d::Delete< CStateMachine<CEventWorldMap>* >(m_pStateMachine);
	d3d::Delete<CTimer*>(_timer);
}

void CEventWorldMap::RenderOrgan(){
	if(GetBody()->GetMtrlArray()->Get(0, 0).Diffuse.a > 0.0f){
		BodySetting();
		GetBody()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
	}
	
	InitChainVector();

	if(GetAttachmentArray()->GetSize()){
		for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
			if(GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(0, 0).Diffuse.a > 0.0f){
				BodySetting();
				GetAttachmentArray()->Get(i)->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
				InitChainVector();
			}
		}
	}

	InitChainVector();

	if(GetMessage()){
		if(GetMessage()->GetUse()){
			BodyOnlyPosSetting();
			GetMessage()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			GetMessage()->RenderLine(_pFont);
		}
	}

	InitChainVector();
}