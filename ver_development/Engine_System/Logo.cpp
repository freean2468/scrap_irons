#include "../BaseHeader.h"

CLogo::CLogo(int id):COrganEntity(id){
	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/UserInterface/Logo/Logo.txt", this);
}

CLogo::~CLogo(){

}

void CLogo::CalculationOrgan(float timeDelta){
	if(GetBody()->GetMtrlArray()->Get(0, 0).Diffuse.a <= 1.0f){
		GetBody()->GetMtrlArray()->Get(0, 0).Diffuse.a += 0.004f;
	}

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