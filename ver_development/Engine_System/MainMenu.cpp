#include "../BaseHeader.h"

CMainMenu::CMainMenu(int id):COrganEntity(id){
	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
	LoadEntityData("./script/UserInterface/MainMenu/MainMenu.txt", this);
}

CMainMenu::~CMainMenu(){

}

void CMainMenu::TransformOrgan(float timeDelta){
	// �μӹ� ���
	for(int i = 0; i < _attachment.GetSize(); i++){
		_attachment[i]->TransformInMainMenu(_attachment[i]->GetAttType(), timeDelta);
	}
}

void CMainMenu::CalculationOrgan(float timeDelta){
	// �̰����� ������ Entity���� ��ü�� ���� ���� ������ �Ѵ�, (ȸ�� ���)
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