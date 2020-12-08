#include "../BaseHeader.h"

CBGEffect::CBGEffect(int id, CBaseObject::OWNER p_eOwner, CBGEffect::BGEFFECTATTTYPE p_eType, d3d::BoundingBox* p_pbox):COrganEntity(id){
	nEffectType = p_eType;
	eBGType = p_eOwner;
	_box = *p_pbox;

	// ��� ����
	// ĳ���� ������ �������� ���� ���� ���� �������� �Ѵ�.
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
	// organ ��뿩�� Ȯ��
	// bool�� ���� ����
	int bIsOrgan = false;
	char cAdress[64];      // �ؽ�ó �ּ�
	int nWidth;		       // �ؽ�ó ���� ����
	int nHeight;		   // �ؽ�ó ���� ����
	float fAlpha = 0.0f;

	FILE* fp = fopen(name, "r");
	if(fp==NULL)return;
	// Entity Type Load
	fgets(line, 256, fp);	
	sscanf(line, "%s %d", string, &Owner);
	p_pEntity->SetOwner(Owner);

	// Pos Rot Sca Cen
	fgets(line, 256, fp);	

	// � �ؽ�ó�� ���� �� ��ũ��Ʈ �󿡼� ��� ���� �� �ִ�.
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

	D3DXVECTOR3 t_vSca = D3DXVECTOR3(vSca.x, vSca.y, vSca.z);	// Body�� �����ϸ� ������ �ӽ÷� ���� �� �μӹ��� ����

	int nIndex = 0;
	int nType = 0;

	// attachment
	fgets(line, 256, fp);	
	sscanf(line, "%s %d %f %f %f %f %f %f %f %f %f %f %f %f %f %s %d %d %d", string, &nIndex, &vPos.x, &vPos.y, &vPos.z, 
		&vSca.x, &vSca.y, &vSca.z, &vRot.x, &vRot.y, &vRot.z, &vCen.x, &vCen.y, &vCen.z, &fAlpha, cAdress, &nWidth, &nHeight, &nType);
	_attachment.Resize(1);

	int t_nCount = 0;

	for(int i = 0; i < nIndex; i++){
		vPos.x *= t_vSca.x;		vPos.y *= t_vSca.y;		vPos.z *= t_vSca.z;	// �����ϸ��� ���� ���� ����
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

	// �μӹ� ���
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
	// �̰����� ������ Entity���� ��ü�� ���� ���� ������ �Ѵ�, (ȸ�� ���)
	TransformOrgan(timeDelta);

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