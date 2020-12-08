#include "../BaseHeader.h"

COrgan::COrgan(int id):CBaseObject(id){
	_vPrimitivePos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	_vPrimitiveSca = D3DXVECTOR3(1.0f, 1.0f, 1.0f);
	_vPrimitiveRot = D3DXVECTOR3(0.0f, 0.0f, 0.0f);	

	_vPrimitiveCen = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

	_angleState = true;
	_moveState = true;
	_alphaState = true;
	_scaleState = true;
	_velocity = ((float)(rand() % 10) + 4)/10.0f;
}

COrgan::~COrgan(){

}

float COrgan::GetLeft(){
	return GetPriPos()->x - GetWidthHalf();
}

float COrgan::GetRight(){
	return GetPriPos()->x + GetWidthHalf();
}

float COrgan::GetTop(){
	return GetPriPos()->y + GetHeightHalf();
}

float COrgan::GetBottom(){
	return GetPriPos()->y - GetHeightHalf();
}



// 체인 벡터는 계속 쌓이고 쌓인다.
void COrgan::SettingOrgan(D3DXVECTOR3* p_pChainPos, D3DXVECTOR3* p_pChainSca, D3DXVECTOR3* p_pChainRot, D3DXVECTOR3* p_pChainCen){
	// 현재 신체기관에 연결된 신체기관에 넘겨줄 Transform 양
	// 체인 벡터에서 신체 기관이 바꿔야할 중점 위치를 전달시킨다.
	// 오른쪽 방향이 기준이다.
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

// 체인 벡터는 계속 쌓이고 쌓인다.
void COrgan::SettingOrgan(D3DXVECTOR3* p_pChainPos, D3DXVECTOR3* p_pChainCen){
	// 현재 신체기관에 연결된 신체기관에 넘겨줄 Transform 양
	// 체인 벡터에서 신체 기관이 바꿔야할 중점 위치를 전달시킨다.
	// 오른쪽 방향이 기준이다.
	p_pChainCen->x = _vPrimitiveCen.x + p_pChainCen->x;
	p_pChainCen->y = _vPrimitiveCen.y + p_pChainCen->y;
	p_pChainCen->z = _vPrimitiveCen.z + p_pChainCen->z;

	p_pChainPos->x = _vPrimitivePos.x + p_pChainPos->x;
	p_pChainPos->y = _vPrimitivePos.y + p_pChainPos->y;
	p_pChainPos->z = _vPrimitivePos.z + p_pChainPos->z;
}

// 체인 벡터는 계속 쌓이고 쌓인다.
void COrgan::SettingJointOrgan(D3DXVECTOR3* p_pChainRot, D3DXVECTOR3* p_pChainCen){
	// 현재 신체기관에 연결된 신체기관에 넘겨줄 Transform 양
	// 체인 벡터에서 신체 기관이 바꿔야할 중점 위치를 전달시킨다.
	// 오른쪽 방향이 기준이다.
	p_pChainCen->x = _vPrimitiveCen.x + p_pChainCen->x;
	p_pChainCen->y = _vPrimitiveCen.y + p_pChainCen->y;
	p_pChainCen->z = _vPrimitiveCen.z + p_pChainCen->z;

	p_pChainRot->x = _vPrimitiveRot.x + p_pChainRot->x;
	p_pChainRot->y = _vPrimitiveRot.y + p_pChainRot->y;
	p_pChainRot->z = _vPrimitiveRot.z + p_pChainRot->z;
}

// 렌더링에 앞서 지정해야 할 초기 렌더 상태를 지정한다.
void COrgan::preRender(D3DXVECTOR3* p_vRot){
	// ZBuffer 연산 꺼줌
	_pDevice->SetRenderState(D3DRS_ZENABLE,FALSE);
	_pDevice->SetRenderState(D3DRS_ZWRITEENABLE,FALSE);

	_pDevice->SetRenderState(D3DRS_LIGHTING, true);

	_pDevice->SetRenderState(D3DRS_NORMALIZENORMALS, true);
	_pDevice->SetRenderState(D3DRS_SPECULARENABLE, true);

	_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);
	_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);
	_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_POINT);

	// 알파채널1 = 난반사 컬러로 알파 지정
	// 알파채널2 = Texture 컬러로 알파 지정
	_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG1, D3DTA_DIFFUSE);
	_pDevice->SetTextureStageState(0, D3DTSS_ALPHAARG2, D3DTA_TEXTURE);
	// 두 알파채널을 곱하여 조정하여 최종 결과물 결정
	_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);	

	// 블렌딩 인수를 지정하여 알파 성분이 투명도를 결정하도록 함
	_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	if(p_vRot->y > D3DX_PI*0.5f)
		_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CW);
	else
		_pDevice->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

// 오브젝트를 그린다.
void COrgan::Render(D3DXVECTOR3* p_vPos, D3DXVECTOR3* p_vSca, D3DXVECTOR3* p_vRot, D3DXVECTOR3* p_vCen){
	preRender(p_vRot);

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&_pos, p_vPos->x, p_vPos->y, p_vPos->z);

	D3DXMATRIXA16 pX;
	D3DXMATRIXA16 pY;
	D3DXMATRIXA16 pZ;
	D3DXMatrixIdentity(&pX);
	D3DXMatrixIdentity(&pY);
	D3DXMatrixIdentity(&pZ);

	D3DXMatrixTranslation(&pX, p_vPos->x, 0.0f, 0.0f);
	D3DXMatrixTranslation(&pY, 0.0f, p_vPos->y, 0.0f);
	D3DXMatrixTranslation(&pZ, 0.0f, 0.0f, p_vPos->z);

	// 원점을 바꾸기 위한 행렬
	D3DXMATRIXA16 _center;
	D3DXMatrixTranslation(&_center, p_vCen->x, p_vCen->y, p_vCen->z);

	D3DXMATRIXA16 rX, rY, rZ;
	D3DXMatrixIdentity(&rX);
	D3DXMatrixIdentity(&rY);
	D3DXMatrixIdentity(&rZ);
	D3DXMatrixRotationX(&rX, p_vRot->x);
	D3DXMatrixRotationY(&rY, p_vRot->y);
	D3DXMatrixRotationZ(&rZ, p_vRot->z);

	_rotation = rX*rY*rZ;

	D3DXMatrixScaling(&_scale, GetPriSca()->x, GetPriSca()->y, GetPriSca()->z);

	// own 계산은 자기만의 회전 각도를 적용할 때 쓰인다.
	D3DXMATRIXA16 ownRotationX, ownRotationY, ownRotationZ;
	D3DXVECTOR3* vOwnRotation = this->GetPriRot();
	D3DXMatrixRotationZ(&ownRotationZ, vOwnRotation->z);
	D3DXMatrixRotationY(&ownRotationY, vOwnRotation->y);
	D3DXMatrixRotationX(&ownRotationX, vOwnRotation->x);
	D3DXMATRIXA16 ownRotation;
	ownRotation = ownRotationX * ownRotationY * ownRotationZ;

	// 자신만의 Scaling
	D3DXMATRIXA16 ownScale;
	D3DXMatrixIdentity(&ownScale);
	D3DXMatrixTranslation(&ownScale, _vScale.x, _vScale.y, _vScale.z);

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

	D3DXMATRIXA16 Inverse1;
	D3DXMatrixIdentity(&Inverse1);
	D3DXMatrixInverse(&Inverse1, 0, &_center);

	D3DXMATRIXA16 Inverse3;
	D3DXMatrixIdentity(&Inverse3);
	D3DXMatrixInverse(&Inverse3, 0, &mOwnCen);

	mtMatrix *= _scale * ownScale * mOwnCen * ownRotation * mOwnPos * Inverse3 * _center * rZ * rX * Inverse1 * rY * pX * pY * pZ;

	_matWorld = mtMatrix;

	_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	// 재질과 텍스처를 활성화한다.
	_pDevice->SetMaterial(&_Mtrl.Get(0, 0));
	_pDevice->SetTexture(0, _pTexture.Get(0, _col));

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

void COrgan::RenderApplyScale(D3DXVECTOR3* p_vPos, D3DXVECTOR3* p_vSca, D3DXVECTOR3* p_vCen){
	preRender(&D3DXVECTOR3(0.0f, 0.0f, 0.0f));

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&_pos, p_vPos->x, p_vPos->y, p_vPos->z);

	D3DXMATRIXA16 pX;
	D3DXMATRIXA16 pY;
	D3DXMATRIXA16 pZ;
	D3DXMatrixIdentity(&pX);
	D3DXMatrixIdentity(&pY);
	D3DXMatrixIdentity(&pZ);

	D3DXMatrixTranslation(&pX, p_vPos->x, 0.0f, 0.0f);
	D3DXMatrixTranslation(&pY, 0.0f, p_vPos->y, 0.0f);
	D3DXMatrixTranslation(&pZ, 0.0f, 0.0f, p_vPos->z);

	// 원점을 바꾸기 위한 행렬
	D3DXMATRIXA16 _center;
	D3DXMatrixTranslation(&_center, p_vCen->x, p_vCen->y, p_vCen->z);

	D3DXMatrixScaling(&_scale, GetPriSca()->x, GetPriSca()->y, GetPriSca()->z);

	// own 계산은 자기만의 회전 각도를 적용할 때 쓰인다.
	D3DXMATRIXA16 ownRotationX, ownRotationY, ownRotationZ;
	D3DXVECTOR3* vOwnRotation = this->GetPriRot();
	D3DXMatrixRotationZ(&ownRotationZ, vOwnRotation->z);
	D3DXMatrixRotationY(&ownRotationY, vOwnRotation->y);
	D3DXMatrixRotationX(&ownRotationX, vOwnRotation->x);
	D3DXMATRIXA16 ownRotation;
	ownRotation = ownRotationX * ownRotationY * ownRotationZ;

	// 자신만의 Scaling
	D3DXMATRIXA16 ownScale;
	D3DXMatrixIdentity(&ownScale);
	D3DXMatrixTranslation(&ownScale, _vScale.x, _vScale.y, _vScale.z);

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

	D3DXMATRIXA16 Inverse1;
	D3DXMatrixIdentity(&Inverse1);
	D3DXMatrixInverse(&Inverse1, 0, &_center);

	D3DXMATRIXA16 Inverse3;
	D3DXMatrixIdentity(&Inverse3);
	D3DXMatrixInverse(&Inverse3, 0, &mOwnCen);

	mtMatrix *= mOwnCen * ownRotation * mOwnPos * Inverse3 * _scale * ownScale * pX * pY * pZ;

	_matWorld = mtMatrix;

	_pDevice->SetTransform(D3DTS_WORLD, &mtMatrix);

	// 재질과 텍스처를 활성화한다.
	_pDevice->SetMaterial(&_Mtrl.Get(0, 0));
	_pDevice->SetTexture(0, _pTexture.Get(0, _col));

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