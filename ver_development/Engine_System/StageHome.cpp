#include "../BaseHeader.h"

CStageHome::CStageHome(int id):COrganEntity(id){
	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/Map/StageHome.txt", this);
}

CStageHome::~CStageHome(){

}

void CStageHome::TransformOrgan(float timeDelta){	
	// 부속물 계산
	for(int i = 0; i < _attachment.GetSize(); i++){
		_attachment[i]->TransformInStageHome(_attachment[i]->GetAttType(), timeDelta);
	}
}

void CStageHome::CalculationOrgan(float timeDelta){
	// 이곳에서 각각의 Entity에서 신체에 대한 각종 연산을 한다, (회전 등등)
	TransformOrgan(timeDelta);

	if(StageMgr->GetbIsHomeInOut()){
		BodySetting();
		GetBody()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
	}

	InitChainVector();

	// 몸-> 부속물
	if(GetAttachmentArray()->GetSize()){
		for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){			
			BodySetting();
			GetAttachmentArray()->Get(i)->SettingOrgan(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			GetAttachmentArray()->Get(i)->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
			InitChainVector();			
		}
	}

	InitChainVector();
}