#include "../BaseHeader.h"

CThroat::CThroat(Type p_type, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen){
	SetType(p_type);

	// 방향을 바꾸면 x 축 대칭이 일어난다.
	_vPrimitivePos[0] = p_vPos;
	_vPrimitivePos[1].x = -p_vPos.x;
	_vPrimitivePos[1].y = p_vPos.y;
	_vPrimitivePos[1].z = p_vPos.z;
	_vPrimitiveSca[0] = p_vSca;
	_vPrimitiveSca[1] = p_vSca;
	_vPrimitiveRot[0] = p_vRot;
	_vPrimitiveRot[1].x = -p_vRot.x;
	_vPrimitiveRot[1].y = p_vRot.y;
	_vPrimitiveRot[1].z = p_vRot.z;

	_vPrimitiveCen[0] = p_vCen;
	_vPrimitiveCen[1].x = -p_vCen.x;
	_vPrimitiveCen[1].y = p_vCen.y;
	_vPrimitiveCen[1].z = p_vCen.z;
}

CThroat::~CThroat(){

}