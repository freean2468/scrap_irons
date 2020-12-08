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

// 체인 벡터는 계속 쌓이고 쌓인다.
void CBody::SettingOrgan(D3DXVECTOR3* p_pChainPos, D3DXVECTOR3* p_pChainSca, D3DXVECTOR3* p_pChainRot, D3DXVECTOR3* p_pChainCen){
	// 현재 신체기관에 연결된 신체기관에 넘겨줄 Transform 양
	// 체인 벡터에서 신체 기관이 바꿔야할 중점 위치를 전달시킨다.
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

// 오브젝트를 그린다.
void CBody::Render(D3DXVECTOR3* p_vPos, D3DXVECTOR3* p_vSca, D3DXVECTOR3* p_vRot, D3DXVECTOR3* p_vCen){
	preRender(p_vRot);

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&_pos, p_vPos->x, p_vPos->y, p_vPos->z);

	D3DXMatrixScaling(&_scale, p_vSca->x, p_vSca->y, p_vSca->z);

	// own 계산은 자기만의 회전 각도를 적용할 때 쓰인다.
	D3DXMATRIXA16 ownRotationX, ownRotationY, ownRotationZ;
	D3DXVECTOR3* vOwnRotation = this->GetPriRot();
	D3DXMatrixRotationZ(&ownRotationZ, vOwnRotation->z);
	D3DXMatrixRotationY(&ownRotationY, vOwnRotation->y);
	D3DXMatrixRotationX(&ownRotationX, vOwnRotation->x);
	D3DXMATRIXA16 ownRotation;
	ownRotation = ownRotationX * ownRotationY * ownRotationZ;

	// 방향에 맞는 고유한 pos를 구한다.
	D3DXVECTOR3* vOwnPosition;
	vOwnPosition = GetPriPos();
	
	// 고유한 center를 구한다.
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

	// 재질과 텍스처를 활성화한다.
	_pDevice->SetMaterial(&_Mtrl.Get(0, 0));
	_pDevice->SetTexture(0, _pTexture.Get(0, 0));

	_pDevice->SetTextureStageState(0, D3DTSS_TEXTURETRANSFORMFLAGS, D3DTTFF_COUNT2);	// 2차원 텍스처 사용
//	_pDevice->SetTextureStageState( 0, D3DTSS_TEXCOORDINDEX, D3DTSS_TCI_CAMERASPACEPOSITION );	/// 카메라 좌표계 변환

	_pDevice->SetStreamSource(0, _pQuad, 0, sizeof(Vertex));
	_pDevice->SetFVF(Vertex::FVF);

	// 활성화된 텍스처를 이용해 기본형을 그린다.
	//_pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 2);	
	_pDevice->SetIndices(_pIndex);
	_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 6, 0, 2);

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	postRender();
}