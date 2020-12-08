#include "../BaseHeader.h"

COrganEntity::COrganEntity(int id):CBaseObject(id){
	_body = 0;

	_vChainPos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vChainSca = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	_vChainRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vChainCen = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	
	//// �ִϸ��̼� ����
	//_dwDelaytime = 300;

	//_timer.InitTimer(_dwDelaytime);
}

COrganEntity::~COrganEntity(){
	d3d::Delete<CBody*>(_body);
	for(int i = _attachment.GetCount(); i > 0; i--){
		d3d::Delete<CAttachment*>(_attachment[i-1]);
	}
}

void COrganEntity::LoadEntityData(char* name, COrganEntity* p_pEntity){
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
		p_pEntity->GetBody()->InitObject(EngineMgr->GetpDevice(), cAdress, nWidth, nHeight, fAlpha, 0);
	}

	// Message
	fgets(line, 256, fp);	
	sscanf(line, "%s %d %f %f %f %f %f %f %f %f %f %f %f %f %f %s %d %d", string, &bIsOrgan, &vPos.x, &vPos.y, &vPos.z, 
		&vSca.x, &vSca.y, &vSca.z, &vRot.x, &vRot.y, &vRot.z, &vCen.x, &vCen.y, &vCen.z, &fAlpha, cAdress, &nWidth, &nHeight);
	if(bIsOrgan){
		p_pEntity->SetMessage(new CMessage(p_pEntity->GetBody(), ID_MESSAGE, Owner, vPos, vSca, vRot, vCen));
		p_pEntity->GetMessage()->InitObject(EngineMgr->GetpDevice(), cAdress, nWidth, nHeight, fAlpha, 0);
	}
	else p_pEntity->SetMessage(NULL);

	D3DXVECTOR3 t_vSca = D3DXVECTOR3(vSca.x, vSca.y, vSca.z);	// Body�� �����ϸ� ������ �ӽ÷� ���� �� �μӹ��� ����

	int nIndex = 0;
	int nType = 0;

	// attachment
	fgets(line, 256, fp);	
	sscanf(line, "%s %d %f %f %f %f %f %f %f %f %f %f %f %f %f %s %d %d %d", string, &nIndex, &vPos.x, &vPos.y, &vPos.z, 
		&vSca.x, &vSca.y, &vSca.z, &vRot.x, &vRot.y, &vRot.z, &vCen.x, &vCen.y, &vCen.z, &fAlpha, cAdress, &nWidth, &nHeight, &nType);
	_attachment.Resize(nIndex);
	for(int i = 0; i < nIndex; i++){
		vPos.x *= t_vSca.x;		vPos.y *= t_vSca.y;		vPos.z *= t_vSca.z;	// �����ϸ��� ���� ���� ����
		vCen.x *= t_vSca.x;		vCen.y *= t_vSca.y;		vCen.z *= t_vSca.z;

		p_pEntity->SetAttachment(new CAttachment(ID_ATTACHMENT, Owner, vPos, vSca, vRot, vCen, nType), i);
		p_pEntity->GetAttachment(i)->InitObject(EngineMgr->GetpDevice(), cAdress, nWidth, nHeight, fAlpha, 0);

		fgets(line, 256, fp);	
		sscanf(line, "%s %f %f %f %f %f %f %f %f %f %f %f %f %f %s %d %d %d", string, &vPos.x, &vPos.y, &vPos.z, 
			&vSca.x, &vSca.y, &vSca.z, &vRot.x, &vRot.y, &vRot.z, &vCen.x, &vCen.y, &vCen.z, &fAlpha, cAdress, &nWidth, &nHeight, &nType);
	}
	
	fclose(fp);
}

void COrganEntity::RenderOrgan(){
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

CAttachment* COrganEntity::GetAttachmentFromType(int p_nType){
	for(int i = 0; i < _attachment.GetSize(); i++){
		if(_attachment[i]->GetAttType() == p_nType)
			return _attachment[i];
	}
	return NULL;
}

CAttachment* COrganEntity::GetAttachment(int index){
	return _attachment[index];
}

CArray<CAttachment*>* COrganEntity::GetAttachmentArray(){
	return &_attachment;
}

int COrganEntity::GetAttachmentIndex(int p_nType){
	for(int i = 0; i < _attachment.GetSize(); i++){
		if(_attachment.Get(i)->GetAttType() == p_nType)
			return i;
	}
	return -1;
}

void COrganEntity::RotationZOrgan(D3DXVECTOR3* p_vRot, float p_fScalar){
	p_vRot->z += p_fScalar;
}

void COrganEntity::RotationYOrgan(D3DXVECTOR3* p_vRot, float p_fScalar){
	p_vRot->y += p_fScalar;
}

void COrganEntity::RotationXOrgan(D3DXVECTOR3* p_vRot, float p_fScalar){
	p_vRot->x += p_fScalar;
}

void COrganEntity::TranslationXOrgan(D3DXVECTOR3* p_vPos, float p_fScalar){
	p_vPos->x += p_fScalar;
}

void COrganEntity::TranslationYOrgan(D3DXVECTOR3* p_vPos, float p_fScalar){
	p_vPos->y += p_fScalar;
}

void COrganEntity::TranslationZOrgan(D3DXVECTOR3* p_vPos, float p_fScalar){
	p_vPos->z += p_fScalar;
}

void COrganEntity::TranslationCenXOrgan(D3DXVECTOR3* p_vCen, float p_fScalar){
	p_vCen->x += p_fScalar;
}

void COrganEntity::TranslationCenYOrgan(D3DXVECTOR3* p_vCen, float p_fScalar){
	p_vCen->y += p_fScalar;
}

void COrganEntity::TranslationCenZOrgan(D3DXVECTOR3* p_vCen, float p_fScalar){
	p_vCen->z += p_fScalar;
}