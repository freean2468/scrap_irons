#include "../BaseHeader.h"

CStageMountain::CStageMountain(int id): COrganEntity(id){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CStageMountain>(this);

	LoadEntityData("./script/Map/StageMountain.txt", this);

	// Area 초기화
	_area[0] = new CArea(0, "./script/UserInterface/Area/Mt.Scrap/1.txt");
	_area[1] = new CArea(1, "./script/UserInterface/Area/Mt.Scrap/2.txt");
	_area[2] = new CArea(2, "./script/UserInterface/Area/Mt.Scrap/3.txt");

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(StageMountainAreaSelection->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);
}

CStageMountain::~CStageMountain(){
	d3d::Delete< CStateMachine<CStageMountain>* >(m_pStateMachine);
}

void CStageMountain::RenderOrgan(){
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