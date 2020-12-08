#include "../BaseHeader.h"

CBGEffect::CBGEffect(int id, CBaseObject::OWNER p_eOwner, CBGEffect::BGEFFECTATTTYPE p_eType, d3d::BoundingBox* p_pbox):COrganEntity(id){
	nEffectType = p_eType;
	eBGType = p_eOwner;
	_box = *p_pbox;

	// 기관 설정
	// 캐릭터 방향이 오른쪽을 보고 있을 때를 기준으로 한다.
	LoadEntityData("./script/BGEffect.txt", this, p_eType);

	_body->GetPriPos()->x = (float)((abs(_box._max.x) + abs(_box._min.x)) * ((float)(rand() % 10) * 0.1f)) - (float)(ObjectMgr->GetEntity(eBGType)->GetBody()->GetWidthHalf());
	_body->GetPriPos()->y = (float)((abs(_box._max.y) + abs(_box._min.y)) * ((float)(rand() % 10) * 0.1f)) - (float)(ObjectMgr->GetEntity(eBGType)->GetBody()->GetHeightHalf());
	_body->GetPriPos()->z = (float)(rand () % 200 + 100) * -1.0f;
}

CBGEffect::~CBGEffect(){

}

void CBGEffect::LoadEntityData(char* name, COrganEntity* p_pEntity, int p_nType){
	char line[256];
	char string[256];

	D3DXVECTOR3 vPos;
	D3DXVECTOR3 vRot;
	D3DXVECTOR3 vSca;
	D3DXVECTOR3 vCen;
	OWNER Owner = BASE;
	// organ 사용여부 확인
	// bool을 사용시 오류
	int bIsOrgan = false;
	char cAdress[64];      // 텍스처 주소
	int nWidth;		       // 텍스처 가로 길이
	int nHeight;		   // 텍스처 세로 길이
	float fAlpha = 0.0f;

	FILE* fp = fopen(name, "r");
	if(fp==NULL)return;
	// Entity Type Load
	fgets(line, 256, fp);	
	sscanf(line, "%s %d", string, &Owner);
	p_pEntity->SetOwner(Owner);

	// Pos Rot Sca Cen
	fgets(line, 256, fp);	

	// 어떤 텍스처를 입힐 지 스크립트 상에서 모두 정할 수 있다.
	// Organ Load
	// Body
	fgets(line, 256, fp);	
	sscanf(line, "%s %d %f %f %f %f %f %f %f %f %f %f %f %f %f %s %d %d", string, &bIsOrgan, &vPos.x, &vPos.y, &vPos.z, 
		&vSca.x, &vSca.y, &vSca.z, &vRot.x, &vRot.y, &vRot.z, &vCen.x, &vCen.y, &vCen.z, &fAlpha, cAdress, &nWidth, &nHeight);
	if(bIsOrgan){
		p_pEntity->SetBody(new CBody(ID_BODY, Owner, vPos, vSca, vRot, vCen));
		p_pEntity->GetBody()->InitObject(EngineMgr->GetpDevice(), EngineMgr->GetpCamera(), cAdress, nWidth, nHeight, fAlpha, 0);
	}

	// Message
	fgets(line, 256, fp);	
	sscanf(line, "%s %d %f %f %f %f %f %f %f %f %f %f %f %f %f %s %d %d", string, &bIsOrgan, &vPos.x, &vPos.y, &vPos.z, 
		&vSca.x, &vSca.y, &vSca.z, &vRot.x, &vRot.y, &vRot.z, &vCen.x, &vCen.y, &vCen.z, &fAlpha, cAdress, &nWidth, &nHeight);
	if(bIsOrgan){
		p_pEntity->SetMessage(new CMessage(ID_MESSAGE, Owner, vPos, vSca, vRot, vCen));
		p_pEntity->GetMessage()->InitObject(EngineMgr->GetpDevice(), EngineMgr->GetpCamera(), cAdress, nWidth, nHeight, fAlpha, 0);
	}

	D3DXVECTOR3 t_vSca = D3DXVECTOR3(vSca.x, vSca.y, vSca.z);	// Body의 스케일링 비율을 임시로 저장 후 부속물에 전달

	int nIndex = 0;
	int nType = 0;

	// attachment
	fgets(line, 256, fp);	
	sscanf(line, "%s %d %f %f %f %f %f %f %f %f %f %f %f %f %f %s %d %d %d", string, &nIndex, &vPos.x, &vPos.y, &vPos.z, 
		&vSca.x, &vSca.y, &vSca.z, &vRot.x, &vRot.y, &vRot.z, &vCen.x, &vCen.y, &vCen.z, &fAlpha, cAdress, &nWidth, &nHeight, &nType);
	_attachment.Resize(1);

	int t_nCount = 0;

	for(int i = 0; i < nIndex; i++){
		vPos.x *= t_vSca.x;		vPos.y *= t_vSca.y;		vPos.z *= t_vSca.z;	// 스케일링에 따른 비율 조정
		vCen.x *= t_vSca.x;		vCen.y *= t_vSca.y;		vCen.z *= t_vSca.z;
		
		if(nType == p_nType){	
			p_pEntity->SetAttachment(new CAttachment(ID_ATTACHMENT, Owner, vPos, vSca, vRot, vCen, nType), t_nCount);
			p_pEntity->GetAttachment(t_nCount)->InitObject(EngineMgr->GetpDevice(), EngineMgr->GetpCamera(), cAdress, nWidth, nHeight, fAlpha, 0);
			t_nCount++;
		}

		fgets(line, 256, fp);	
		sscanf(line, "%s %f %f %f %f %f %f %f %f %f %f %f %f %f %s %d %d %d", string, &vPos.x, &vPos.y, &vPos.z, 
			&vSca.x, &vSca.y, &vSca.z, &vRot.x, &vRot.y, &vRot.z, &vCen.x, &vCen.y, &vCen.z, &fAlpha, cAdress, &nWidth, &nHeight, &nType);
	}

	fclose(fp);
}

void CBGEffect::TransformOrgan(float timeDelta){	
	_body->GetPriPos()->x += _body->GetVelocity();

	// 부속물 계산
	for(int i = 0; i < _attachment.GetSize(); i++){
		if(_body->GetPriPos()->x - _attachment[i]->GetWidthHalf() > _box._max.x){
			float t_fTemp = (float)(rand()%10 + 4);

			_body->SetVelocity(t_fTemp/10.0f);

			_body->GetPriPos()->x = _box._min.x - (float)(_attachment[i]->GetWidth());
			_body->GetPriPos()->y = (float)((abs(_box._max.y) + abs(_box._min.y))  * ((float)(rand() % 10) * 0.1f)) - (float)(ObjectMgr->GetEntity(GetBGType())->GetBody()->GetHeightHalf());
			_body->GetPriPos()->z = (float)(rand () % 200 + 100) * -1.0f;
		}
	}
}

void CBGEffect::CalculationOrgan(float timeDelta){
	// 이곳에서 각각의 Entity에서 신체에 대한 각종 연산을 한다, (회전 등등)
	TransformOrgan(timeDelta);

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