#include "../BaseHeader.h"

CArea::CArea(int p_nNum, char* p_pStr) : _areaNumber(p_nNum), COrganEntity(ID_AREA){
	// 상태기계를 설정한다.
	m_pStateMachine = new CStateMachine<CArea>(this);

	LoadEntityData(p_pStr, this);

	// 처음 상태를 초기화
	m_pStateMachine->SetCurrentState(AreaUsual->Instance());

	m_pStateMachine->CurrentState()->Enter(this);

	m_pStateMachine->SetGlobalState(NULL);

	_clear = false;
}

CArea::~CArea(){
	d3d::Delete< CStateMachine<CArea>* >(m_pStateMachine);
}

void CArea::RenderOrgan(){
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