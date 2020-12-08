#include "../BaseHeader.h"

CMessage::CMessage(COrgan* p_pOrgan, int id, OWNER p_owner, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen):COrgan(id){
	SetOwner(p_owner);

	_origin = p_pOrgan;

	_vPrimitivePos = p_vPos;
	_vPrimitiveSca = p_vSca;
	_vPrimitiveRot = p_vRot;

	_vPrimitiveCen = p_vCen;

	bUse = false;

	_pFont = d3d::IniFont(13, 6, 300, false, "맑은 고딕");

	line = NULL;
}

CMessage::~CMessage(){

}

void CMessage::ReadLine(char* p_pStr){
	strcpy(line,p_pStr);
	line[127] = '\0';

	bUse = true;
}

void CMessage::RenderLine(ID3DXFont* p_pFont){
	EngineMgr->GetpSprite()->Begin( D3DXSPRITE_ALPHABLEND | D3DXSPRITE_OBJECTSPACE); // 3D 공간상에 텍스트 출력

	D3DXVECTOR3 _vPos;			// 위치 벡터
	D3DXMATRIXA16 _pos;			// 위치 변환 행렬
	D3DXVECTOR3 _vScale;		// 크기 벡터
	D3DXMATRIXA16 _scale;		// 크기 변환 행렬
	D3DXMATRIXA16 _rotation;	// 회전 변환 행렬
	D3DXVECTOR3 _vRotate;		// 회전 벡터

	D3DXMATRIXA16 mtMatrix;
	D3DXMatrixIdentity(&mtMatrix);

	D3DXMatrixTranslation(&_pos, _origin->GetPriPos()->x + GetPriPos()->x, _origin->GetPriPos()->y + GetPriPos()->y, _origin->GetPriPos()->z + GetPriPos()->z);

	D3DXMATRIXA16 rX/*, rY, rZ*/;
	D3DXMatrixIdentity(&rX);
	//D3DXMatrixIdentity(&rY);
	//D3DXMatrixIdentity(&rZ);
	D3DXMatrixRotationX(&rX, D3DX_PI);
	//D3DXMatrixRotationY(&rY, D3DX_PI);
	//D3DXMatrixRotationZ(&rZ, ObjectMgr->GetEntity(_owner)->GetBody()->GetPriRot()->z);

	_rotation = rX/*,rY, rZ*/;

	//D3DXMatrixScaling(&_scale, ObjectMgr->GetEntity(_owner)->GetBody()->GetPriSca()->x, ObjectMgr->GetEntity(_owner)->GetBody()->GetPriSca()->y, ObjectMgr->GetEntity(_owner)->GetBody()->GetPriSca()->z);

	mtMatrix = mtMatrix * /*_scale*/_rotation * _pos;

	_matWorld = mtMatrix;

	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);

	rect.right = (long)(GetWidthHalf()-23.0f);
	rect.left = (long)(-GetWidthHalf()+25.0f);
	rect.top = (long)(-GetHeightHalf()+20.0f);
	rect.bottom = (long)(GetHeightHalf()-20.0f);

	// Text 출력
	if(p_pFont == NULL){
		_pFont->DrawText(EngineMgr->GetpSprite(), line, -1, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK , 0xff000000);     
	}
	else{  
		p_pFont->DrawText(EngineMgr->GetpSprite(), line, -1, &rect, DT_CENTER | DT_VCENTER | DT_WORDBREAK , 0xff000000);     
	}

	EngineMgr->GetpSprite()->End();

	// 월드 좌표를 원점으로 되돌린다.
	D3DXMatrixIdentity(&mtMatrix);
	EngineMgr->GetpSprite()->SetTransform(&mtMatrix);
}