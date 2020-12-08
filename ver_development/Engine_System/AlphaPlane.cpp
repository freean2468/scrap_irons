#include "../BaseHeader.h"

CAlphaPlane::CAlphaPlane(int id):COrganEntity(id){
	nPlaneType = -1;

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/AlphaPlane.txt", this);
}

CAlphaPlane::~CAlphaPlane(){

}

void CAlphaPlane::TransformOrgan(float timeDelta){	
	GetBody()->GetPriPos()->x = EngineMgr->GetpInformation()->GetCameraPos()->x;
	GetBody()->GetPriPos()->y = EngineMgr->GetpInformation()->GetCameraPos()->y;

	if(GetPlaneType() != -1){
		// 부속물 계산
		for(int i = 0; i < _attachment.GetSize(); i++){
			if(GetPlaneType() == GetAttachmentArray()->Get(i)->GetAttType()){
				_attachment[i]->TransformInAlphaPlane(_attachment[i]->GetAttType(), timeDelta);
				break;
			}
		}
	}
}

void CAlphaPlane::CalculationOrgan(float timeDelta){
	// 이곳에서 각각의 Entity에서 신체에 대한 각종 연산을 한다, (회전 등등)
	TransformOrgan(timeDelta);

	// 몸-> 부속물
	if(GetPlaneType() != -1){
		if(GetAttachmentArray()->GetSize()){
			for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
				if(GetPlaneType() == GetAttachmentArray()->Get(i)->GetAttType()){
					BodySetting();
					GetAttachmentArray()->Get(i)->SettingOrgan(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
					GetAttachmentArray()->Get(i)->Render(GetChainPos(), GetChainSca(), GetChainRot(), GetChainCen());
					InitChainVector();	
					break;
				}
			}
		}
	}

	InitChainVector();
}

CAttachment* CAlphaPlane::GetPlane(int p_nAttType){
	for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
		if(GetPlaneType() == GetAttachmentArray()->Get(i)->GetAttType()){
			return GetAttachment(i);
		}
	}	
	return NULL;
}

float CAlphaPlane::GetPlaneAlpha(int p_nAttType){
	for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
		if(GetPlaneType() == GetAttachmentArray()->Get(i)->GetAttType()){
			return GetAttachment(i)->GetMtrlArray()->Get(GetAttachment(i)->GetRow(), GetAttachment(i)->GetCol()).Diffuse.a;
		}
	}	
	return 0.0f;
}

void CAlphaPlane::AlphaPlaneInit(){
	SetPlaneType(-1);

	for(int i = 0; i < GetAttachmentArray()->GetSize(); i++){
		if(GetPlaneType() == GetAttachmentArray()->Get(i)->GetAttType()){
			GetAttachmentArray()->Get(i)->GetMtrlArray()->Get(GetAttachmentArray()->Get(i)->GetRow(), GetAttachmentArray()->Get(i)->GetCol()).Diffuse.a = 0.0f;	
			break;
		}
	}
}