#include "../BaseHeader.h"

CStageHome::CStageHome(int id):COrganEntity(id){
	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Map/StageHome.txt", this);
}

CStageHome::~CStageHome(){

}

void CStageHome::TransformOrgan(float timeDelta){	
	// �μӹ� ���
	for(int i = 0; i < _attachment.GetSize(); i++){
		_attachment[i]->TransformInStageHome(_attachment[i]->GetAttType(), timeDelta);
	}
}

void CStageHome::CalculationOrgan(float timeDelta){
	// �̰����� ������ Entity���� ��ü�� ���� ���� ������ �Ѵ�, (ȸ�� ���)
	TransformOrgan(timeDelta);

	if(StageMgr->GetbIsHomeInOut()){
		BodySetting();
		GetBody()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
	}

	InitChainVector();

	// ��-> �μӹ�
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