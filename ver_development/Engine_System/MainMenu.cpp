#include "../BaseHeader.h"

CMainMenu::CMainMenu(int id):COrganEntity(id){
	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/UserInterface/MainMenu/MainMenu.txt", this);
}

CMainMenu::~CMainMenu(){

}

void CMainMenu::TransformOrgan(float timeDelta){
	// 부속물 계산
	for(int i = 0; i < _attachment.GetSize(); i++){
		_attachment[i]->TransformInMainMenu(_attachment[i]->GetAttType(), timeDelta);
	}
}

void CMainMenu::CalculationOrgan(float timeDelta){
	// 이곳에서 각각의 Entity에서 신체에 대한 각종 연산을 한다, (회전 등등)
	TransformOrgan(timeDelta);

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
			GetMessage()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			GetMessage()->RenderLine();
		}
	}

	InitChainVector();
}