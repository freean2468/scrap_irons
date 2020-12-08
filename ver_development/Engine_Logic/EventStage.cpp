#include "../BaseHeader.h"

CEventStage::CEventStage(int id):COrganEntity(id), _timer(NULL){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CEventStage>(this);

	LoadEntityData("./script/Event/Event/EventStage.txt", this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(EventStageCheck->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(EventStageGlobal->Instance());

	m_pStateMachine->GlobalState()->Enter(this);
	
	_pFont = d3d::IniFont(28, 14, 1000, false, "맑은 고딕");

	_timer = new CTimer();

	_firstMeeting = false;
	_firstArea = false;
	_secondArea = false;
	_thirdArea = false;
	_furnace = false;
	_chimney = false;
	_dustbridge = false;
	_goodHopeIntro = false;
	_goodHope = false;

	_dustKidDie = false;
	_workerDie = false;
	_gatekeeperDie = false;
	_dustKingDie = false;
}

CEventStage::~CEventStage(){
	d3d::Delete< CStateMachine<CEventStage>* >(m_pStateMachine);
	d3d::Delete<CTimer*>(_timer);
}

void CEventStage::RenderOrgan(){
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