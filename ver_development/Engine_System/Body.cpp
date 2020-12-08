#include "../BaseHeader.h"

CBody::CBody(int id, OWNER p_owner, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen):COrgan(id){
	SetOwner(p_owner);

	_vPrimitivePos = p_vPos;
	_vPrimitiveSca = p_vSca;
	_vPrimitiveRot = p_vRot;

	_vPrimitiveCen = p_vCen;

	_angleState = 1;
}

CBody::~CBody(){

}

// ü�� ���ʹ� ��� ���̰� ���δ�.
void CBody::SettingOrgan(D3DXVECTOR3* p_pChainPos, D3DXVECTOR3* p_pChainSca, D3DXVECTOR3* p_pChainRot, D3DXVECTOR3* p_pChainCen){
	// ���� ��ü����� ����� ��ü����� �Ѱ��� Transform ��
	// ü�� ���Ϳ��� ��ü ����� �ٲ���� ���� ��ġ�� ���޽�Ų��.
	p_pChainCen->x = _vPrimitiveCen.x + p_pChainCen->x;
	p_pChainCen->y = _vPrimitiveCen.y + p_pChainCen->y;
	p_pChainCen->z = _vPrimitiveCen.z + p_pChainCen->z;

	p_pChainPos->x = _vPrimitivePos.x + p_pChainPos->x;
	p_pChainPos->y = _vPrimitivePos.y + p_pChainPos->y;
	p_pChainPos->z = _vPrimitivePos.z + p_pChainPos->z;

	p_pChainSca->x = _vPrimitiveSca.x * p_pChainSca->x;
	p_pChainSca->y = _vPrimitiveSca.y * p_pChainSca->y;
	p_pChainSca->z = _vPrimitiveSca.z * p_pChainSca->z;

	p_pChainRot->x = _vPrimitiveRot.x + p_pChainRot->x;
	p_pChainRot->y = _vPrimitiveRot.y + p_pChainRot->y;
	p_pChainRot->z = _vPrimitiveRot.z + p_pChainRot->z;
}

// ������Ʈ�� �׸���.
void CBody::Render(D3DXVECTOR3* p_vPos, D3DXVECTOR3* p_vSca, D3DXVECTOR3* p_vRot, D3DXVECTOR3* p_vCen){
	preRender(p_vRot);

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&_pos, p_vPos->x, p_vPos->y, p_vPos->z);

	D3DXMatrixScaling(&_scale, p_vSca->x, p_vSca->y, p_vSca->z);

	// own ����� �ڱ⸸�� ȸ�� ������ ������ �� ���δ�.
	D3DXMATRIXA16 ownRotationX, ownRotationY, ownRotationZ;
	D3DXVECTOR3* vOwnRotation = this->GetPriRot();
	D3DXMatrixRotationZ(&ownRotationZ, vOwnRotation->z);
	D3DXMatrixRotationY(&ownRotationY, vOwnRotation->y);
	D3DXMatrixRotationX(&ownRotationX, vOwnRotation->x);
	D3DXMATRIXA16 ownRotation;
	ownRotation = ownRotationX * ownRotationY * ownRotationZ;

	// ���⿡ �´� ������ pos�� ���Ѵ�.
	D3DXVECTOR3* vOwnPosition;
	vOwnPosition = GetPriPos();
	
	// ������ center�� ���Ѵ�.
	D3DXVECTOR3* vOwnCenter = this->GetPriCen();
	D3DXMATRIXA16 mOwnPos;
	D3DXMATRIXA16 mOwnCen;
	D3DXMatrixIdentity(&mOwnPos);
	D3DXMatrixIdentity(&mOwnCen);

	D3DXMatrixTranslation(&mOwnPos, vOwnPosition->x, vOwnPosition->y, vOwnPosition->z);
	D3DXMatrixTranslation(&mOwnCen, vOwnCenter->x, vOwnCenter->y, vOwnCenter->z);

	mtMatrix *= _scale * ownRotationZ * ownRotationX * ownRotationY * _pos;

	_matWorld = mtMatrix;

	_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	// ������ �ؽ�ó�� Ȱ��ȭ�Ѵ�.
	_pDevice->SetMaterial(&_Mtrl.Get(0, 0));
	_pDevice->SetTexture(0, _pTexture.Get(0, 0));

	_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	// 2���� �ؽ�ó ���
//	_pDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );	/// ī�޶� ��ǥ�� ��ȯ

	_pDevice->SetStreamSource(0, _pQuad, 0, sizeof(Vertex));
	_pDevice->SetFVF(Vertex::FVF);

	// Ȱ��ȭ�� �ؽ�ó�� �̿��� �⺻���� �׸���.
	//_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);	
	_pDevice->SetIndices(_pIndex);
	_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);

	// ���� ��ǥ�� �������� �ǵ�����.
	D3DXMatrixIdentity(&mtMatrix);
	_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	postRender();
}