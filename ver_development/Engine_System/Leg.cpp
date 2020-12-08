#include "../BaseHeader.h"

CLeg::CLeg(Type p_type, D3DXVECTOR3 p_vPos, D3DXVECTOR3 p_vSca, D3DXVECTOR3 p_vRot, D3DXVECTOR3 p_vCen){
	SetType(p_type);

	// �� ��ü�� ������ Entity�� ���� �ʱ�ȭ�� �ٸ��� ���ش�.
	// ������ �ٲٸ� x �� ��Ī�� �Ͼ��.
	switch(GetType()){
		case CART:
			_vPrimitivePos[1].x = p_vPos.x;
			break;
		default:					
			_vPrimitivePos[1].x = -p_vPos.x;
			
	}
	_vPrimitivePos[0] = p_vPos;
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

	_angleState = 1;
}

CLeg::~CLeg(){

}

void CLeg::Rotation(TYPE p_type, float timeDelta){
	switch(p_type){
		case HERO:
			switch(_angleState){
				case true:
					// Max���
					_vPrimitiveRot[GetRow()].z += timeDelta*1.9f;
					if(_vPrimitiveRot[GetRow()].z >= D3DX_PI/4)
						_angleState = false;
					break;
				case false:
					// Min���
					_vPrimitiveRot[GetRow()].z -= timeDelta*1.9f;
					if(_vPrimitiveRot[GetRow()].z <= -D3DX_PI/4)
						_angleState = true;
					break;
			}
			break;
		case LOGO:
			if(_vPrimitiveRot[GetRow()].z >= D3DX_PI*1.1f)
				break;
			else
				_vPrimitiveRot[GetRow()].z += timeDelta*0.3f;
			break;
		default:
			break;
	}
}