#include "../BaseHeader.h"

CStageFurnace::CStageFurnace(int id):COrganEntity(id){
	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/Map/StageFurnace.txt", this);
}

CStageFurnace::~CStageFurnace(){

}

void CStageFurnace::TransformOrgan(float timeDelta){	
	// �μӹ� ���
	for(int i = 0; i < _attachment.GetSize(); i++){
		_attachment[i]->TransformInStageFurnace(_attachment[i]->GetAttType(), timeDelta);
	}
}

void CStageFurnace::CalculationOrgan(float timeDelta){
	// �̰����� ������ Entity���� ��ü�� ���� ���� ������ �Ѵ�, (ȸ�� ���)
	TransformOrgan(timeDelta);

	BodySetting();
	GetBody()->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
	
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